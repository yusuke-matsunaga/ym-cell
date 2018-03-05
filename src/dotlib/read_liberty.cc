
/// @file read_liberty.cc
/// @brief read_liberty の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiCell.h"
#include "ci/CiTiming.h"

#include "ym/ClibCellPin.h"
#include "ym/ClibTiming.h"
#include "ym/ClibArea.h"
#include "ym/ClibResistance.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibTime.h"
#include "ym/ClibLut.h"
#include "ym/ClibLutTemplate.h"

#include "DotlibParser.h"
#include "DotlibMgr.h"
#include "DotlibNode.h"
#include "DotlibLibrary.h"
#include "DotlibCell.h"
#include "DotlibFF.h"
#include "DotlibLatch.h"
#include "DotlibPin.h"
#include "DotlibTiming.h"
#include "DotlibTemplate.h"
#include "DotlibLut.h"

#include "ym/Expr.h"
#include "ym/TvFunc.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

BEGIN_NONAMESPACE

// 文字列を空白で区切る
void
split(const string& src_str,
      vector<string>& str_list)
{
  string tmp_str(src_str);
  for ( ; ; ) {
    string::size_type p = tmp_str.find_first_of(' ');
    if ( p == string::npos ) {
      str_list.push_back(tmp_str);
      return;
    }
    string tmp = tmp_str.substr(0, p);
    tmp_str = tmp_str.substr(p + 1, string::npos);
  }
}

// DotlibNode から Expr を作る．
Expr
dot2expr(const DotlibNode* node,
	 const HashMap<ShString, int>& pin_map)
{
  // 特例
  if ( node == nullptr ) {
    return Expr::const_zero();
  }

  if ( node->is_int() ) {
    int v = node->int_value();
    if ( v == 0 ) {
      return Expr::const_zero();
    }
    if ( v == 1 ) {
      return Expr::const_one();
    }
    ASSERT_NOT_REACHED;
    return Expr();
  }
  if ( node->is_string() ) {
    ShString name = node->string_value();
    int id;
    if ( !pin_map.find(name, id) ) {
      ostringstream buf;
      buf << name << ": No such pin-name.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      node->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      buf.str());
      return Expr();
    }
    return Expr::posi_literal(VarId(id));
  }
  if ( node->is_opr() ) {
    if ( node->type() == DotlibNode::kNot ) {
      Expr expr1 = dot2expr(node->opr1(), pin_map);
      return ~expr1;
    }
    else {
      Expr expr1 = dot2expr(node->opr1(), pin_map);
      Expr expr2 = dot2expr(node->opr2(), pin_map);
      switch ( node->type() ) {
      case DotlibNode::kAnd: return expr1 & expr2;
      case DotlibNode::kOr:  return expr1 | expr2;
      case DotlibNode::kXor: return expr1 ^ expr2;
      default: break;
      }
      ASSERT_NOT_REACHED;
      return Expr();
    }
  }
  ASSERT_NOT_REACHED;
  return Expr();
}

// LUT を読み込む．
ClibLut*
gen_lut(CiCellLibrary* library,
	const DotlibNode* lut_node)
{
  DotlibLut lut_info;
  if ( !lut_info.set_data(lut_node) ) {
    return nullptr;
  }
  const char* name = lut_info.template_name();
  const ClibLutTemplate* templ = library->lu_table_template(name);
  if ( templ == nullptr ) {
    ostringstream buf;
    buf << lut_info.template_name()
	<< ": No such lu_table template";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    lut_node->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  int d = templ->dimension();

  vector<double> value_array;
  int n = lut_info.value_list()->list_size();
  for ( int i = 0; i < n; ++ i ) {
    vector<double> tmp_array;
    lut_info.value_list()->list_elem(i)->get_vector(tmp_array);
    value_array.insert(value_array.end(), tmp_array.begin(), tmp_array.end());
  }

  vector<double> index1_array;
  if ( lut_info.index_1() ) {
    lut_info.index_1()->get_vector(index1_array);
  }
  vector<double> index2_array;
  if ( d >= 2 && lut_info.index_2() ) {
    lut_info.index_2()->get_vector(index2_array);
  }
  vector<double> index3_array;
  if ( d >= 3 && lut_info.index_3() ) {
    lut_info.index_3()->get_vector(index3_array);
  }

  ClibLut* lut = nullptr;
  if ( d == 1 ) {
    lut = library->new_lut1(templ, value_array,
			    index1_array);
  }
  else if ( d == 2 ) {
    lut = library->new_lut2(templ, value_array,
			    index1_array,
			    index2_array);
  }
  else if ( d == 3 ) {
    lut = library->new_lut3(templ, value_array,
			    index1_array,
			    index2_array,
			    index3_array);
  }
  return lut;
}

// 論理式を生成する．
Expr
gen_expr(const DotlibNode* expr_node,
	 const HashMap<ShString, int>& pin_map,
	 bool& has_expr)
{
  if ( expr_node ) {
    has_expr = true;
    return dot2expr(expr_node, pin_map);
  }
  else {
    has_expr = false;
    return Expr::const_zero();
  }
}

// ピンを生成する．
void
gen_pin(const vector<DotlibPin>& pin_info_array,
	const HashMap<ShString, int>& pin_map,
	CiCellLibrary* library,
	vector<CiInputPin*>& input_list,
	vector<CiOutputPin*>& output_list,
	vector<CiInoutPin*>& inout_list,
	vector<CiInternalPin*>& internal_list)
{
  for ( const DotlibPin& pin_info: pin_info_array ) {
    switch ( pin_info.direction() ) {
    case DotlibPin::kInput:
      // 入力ピンの生成
      {
	ClibCapacitance cap(pin_info.capacitance());
	ClibCapacitance rise_cap(pin_info.rise_capacitance());
	ClibCapacitance fall_cap(pin_info.fall_capacitance());
	for (  int i = 0; i < pin_info.num(); ++ i ) {
	  CiInputPin* pin = library->new_cell_input(pin_info.name(i),
						    cap, rise_cap, fall_cap);
	  input_list.push_back(pin);
	}
      }
      break;

    case DotlibPin::kOutput:
      // 出力の生成
      {
	bool has_logic;
	Expr logic_expr = gen_expr(pin_info.function(), pin_map, has_logic);
	bool dummy;
	Expr tristate_expr = gen_expr(pin_info.three_state(), pin_map, dummy);
	ClibCapacitance max_fanout(pin_info.max_fanout());
	ClibCapacitance min_fanout (pin_info.min_fanout());
	ClibCapacitance max_capacitance(pin_info.max_capacitance());
	ClibCapacitance min_capacitance(pin_info.min_capacitance());
	ClibTime max_transition(pin_info.max_transition());
	ClibTime min_transition(pin_info.min_transition());
	for ( int i = 0; i < pin_info.num(); ++ i ) {
	  CiOutputPin* pin = library->new_cell_output(pin_info.name(i),
						      has_logic,
						      logic_expr,
						      tristate_expr,
						      max_fanout, min_fanout,
						      max_capacitance, min_capacitance,
						      max_transition, min_transition);
	  output_list.push_back(pin);
	}
      }
      break;

    case DotlibPin::kInout:
      // 入出力ピンの生成
      {
	bool has_logic;
	Expr logic_expr = gen_expr(pin_info.function(), pin_map, has_logic);
	bool dummy;
	Expr tristate_expr = gen_expr(pin_info.three_state(), pin_map, dummy);
	ClibCapacitance cap(pin_info.capacitance());
	ClibCapacitance rise_cap(pin_info.rise_capacitance());
	ClibCapacitance fall_cap(pin_info.fall_capacitance());
	ClibCapacitance max_fanout(pin_info.max_fanout());
	ClibCapacitance min_fanout(pin_info.min_fanout());
	ClibCapacitance max_capacitance(pin_info.max_capacitance());
	ClibCapacitance min_capacitance(pin_info.min_capacitance());
	ClibTime max_transition(pin_info.max_transition());
	ClibTime min_transition(pin_info.min_transition());
	for ( int i = 0; i < pin_info.num(); ++ i ) {
	  CiInoutPin* pin = library->new_cell_inout(pin_info.name(i),
						    has_logic,
						    logic_expr,
						    tristate_expr,
						    cap, rise_cap, fall_cap,
						    max_fanout, min_fanout,
						    max_capacitance, min_capacitance,
						    max_transition, min_transition);
	  inout_list.push_back(pin);
	}
      }
      break;

    case DotlibPin::kInternal:
      // 内部ピンの生成
      for ( int i = 0; i < pin_info.num(); ++ i ) {
	CiInternalPin* pin = library->new_cell_internal(pin_info.name(i));
	internal_list.push_back(pin);
      }
      break;

    default:
      ASSERT_NOT_REACHED;
    }
  }
}

void
gen_timing_list(const vector<DotlibPin>& pin_info_array,
		const HashMap<ShString, int>& pin_map,
		CiCellLibrary* library,
		vector<CiTiming*>& timing_list,
		vector<vector<CiTiming*> >& timing_list_array)
{
  for ( const DotlibPin& pin_info: pin_info_array ) {
    const list<const DotlibNode*>& dt_timing_list = pin_info.timing_list();
    for ( auto dt_timing: dt_timing_list ) {
      DotlibTiming timing_info;
      if ( !timing_info.set_data(dt_timing) ) {
	continue;
      }
      ClibTimingType timing_type = timing_info.timing_type();
      const DotlibNode* when_node = timing_info.when();
      Expr cond;
      if ( when_node ) {
	cond = dot2expr(when_node, pin_map);
      }
      else {
	cond = Expr::const_one();
      }

      CiTiming* timing = nullptr;
      switch ( library->delay_model() ) {
      case kClibDelayGenericCmos:
	{
	  ClibTime intrinsic_rise(timing_info.intrinsic_rise()->float_value());
	  ClibTime intrinsic_fall(timing_info.intrinsic_fall()->float_value());
	  ClibTime slope_rise(timing_info.slope_rise()->float_value());
	  ClibTime slope_fall(timing_info.slope_fall()->float_value());
	  ClibResistance rise_res(timing_info.rise_resistance()->float_value());
	  ClibResistance fall_res(timing_info.fall_resistance()->float_value());
	  timing = library->new_timing_generic(timing_type, cond,
					       intrinsic_rise, intrinsic_fall,
					       slope_rise, slope_fall,
					       rise_res, fall_res);
	}
	break;

      case kClibDelayTableLookup:
	{
	  const DotlibNode* cr_node = timing_info.cell_rise();
	  const DotlibNode* rt_node = timing_info.rise_transition();
	  const DotlibNode* rp_node = timing_info.rise_propagation();

	  ClibLut* cr_lut = nullptr;
	  ClibLut* rt_lut = nullptr;
	  ClibLut* rp_lut = nullptr;
	  if ( cr_node != nullptr ) {
	    if ( rp_node != nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dt_timing->loc(),
			      kMsgError,
			      "DOTLIB_PARSER",
			      "cell_rise and rise_propagation are mutually exclusive.");
	      continue;
	    }
	    if ( rt_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dt_timing->loc(),
			      kMsgError,
			      "DOTLIB_PARSER",
			      "rise_transition is missing.");
	      continue;
	    }
	    cr_lut = gen_lut(library, cr_node);
	    rt_lut = gen_lut(library, rt_node);
	  }
	  else if ( rp_node != nullptr ) {
	    if ( rt_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dt_timing->loc(),
			      kMsgError,
			      "DOTLIB_PARSER",
			      "rise_transition is missing.");
	      continue;
	    }
	    rt_lut = gen_lut(library, rt_node);
	    rp_lut = gen_lut(library, rp_node);
	  }
	  else if ( rt_node != nullptr ) {
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    dt_timing->loc(),
			    kMsgError,
			    "DOTLIB_PARSER",
			    "Either cell_rise or rise_propagation should be present.");
	    continue;
	  }

	  const DotlibNode* cf_node = timing_info.cell_fall();
	  const DotlibNode* ft_node = timing_info.fall_transition();
	  const DotlibNode* fp_node = timing_info.fall_propagation();

	  ClibLut* cf_lut = nullptr;
	  ClibLut* ft_lut = nullptr;
	  ClibLut* fp_lut = nullptr;
	  if ( cf_node != nullptr ) {
	    if ( fp_node != nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dt_timing->loc(),
			      kMsgError,
			      "DOTLIB_PARSER",
			      "cell_fall and fall_propagation are mutually exclusive.");
	      continue;
	    }
	    if ( ft_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dt_timing->loc(),
			      kMsgError,
			      "DOTLIB_PARSER",
			      "fall_transition is missing.");
	      continue;
	    }
	    cf_lut = gen_lut(library, cf_node);
	    ft_lut = gen_lut(library, ft_node);
	  }
	  else if ( fp_node != nullptr ) {
	    if ( ft_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dt_timing->loc(),
			      kMsgError,
			      "DOTLIB_PARSER",
			      "fall_transition is missing.");
	      continue;
	    }
	    ft_lut = gen_lut(library, ft_node);
	    fp_lut = gen_lut(library, fp_node);
	  }
	  else if ( ft_node != nullptr ) {
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    dt_timing->loc(),
			    kMsgError,
			    "DOTLIB_PARSER",
			    "Either cell_fall or fall_propagation should be present.");
	    continue;
	  }

	  if ( cr_lut != nullptr || cf_lut != nullptr ) {
	    if ( fp_lut != nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dt_timing->loc(),
			      kMsgError,
			      "DOTLIB_PARSER",
			      "cell_rise and fall_propagation are mutually exclusive.");
	      continue;
	    }
	    timing = library->new_timing_lut1(timing_type, cond,
					      cr_lut, cf_lut,
					      rt_lut, ft_lut);
	  }
	  else { // cr_lut == nullptr && cf_lut == nullptr
	    timing = library->new_timing_lut2(timing_type, cond,
					      rt_lut, ft_lut,
					      rp_lut, fp_lut);
	  }
	}
	break;

      case kClibDelayPiecewiseCmos:
	// 未実装
	break;

      case kClibDelayCmos2:
	// 未実装
	break;

      case kClibDelayDcm:
	// 未実装
	break;
      }
      timing_list.push_back(timing);

      ClibTimingSense timing_sense = timing_info.timing_sense();

      // タイミング情報の設定
      if ( timing_info.related_pin() ) {
	ShString tmp_str = timing_info.related_pin()->string_value();
	vector<string> pin_name_list;
	split(tmp_str, pin_name_list);
	for ( auto pin_name: pin_name_list ) {
	  int id;
	  if ( !pin_map.find(ShString(pin_name), id) ) {
	    ostringstream buf;
	    buf << pin_name << ": no such pin";
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    dt_timing->loc(),
			    kMsgError,
			    "DOTLIB_PARSER",
			    buf.str());
	    continue;
	  }
	  switch ( timing_sense ) {
	  case kClibPosiUnate:
	    timing_list_array[id * 2 + 0].push_back(timing);
	    break;

	  case kClibNegaUnate:
	    timing_list_array[id * 2 + 1].push_back(timing);
	    break;

	  case kClibNonUnate:
	    timing_list_array[id * 2 + 0].push_back(timing);
	    timing_list_array[id * 2 + 1].push_back(timing);
	    break;

	  default:
	    ASSERT_NOT_REACHED;
	    break;
	  }
	}
      }
      else {
	MsgMgr::put_msg(__FILE__, __LINE__,
			dt_timing->loc(),
			kMsgError,
			"DOTLIB_PARSER",
			"No \"related_pin\"");
      }
    }
  }
}

// @brief DotlibNode から CiCellLibrary を生成する．
// @param[in] library_info ライブラリの情報を持つオブジェクト
// @param[in] library設定対象のライブラリ
void
set_library(const DotlibLibrary& library_info,
	    CiCellLibrary* library)
{
  // 'name' の設定
  library->set_name(library_info.name());

  // 'technology' の設定
  library->set_technology(library_info.technology());

  // 'delay_model' の設定
  library->set_delay_model(library_info.delay_model());

  // 'bus_naming_style' の設定
  if ( library_info.bus_naming_style() ) {
    ShString value = library_info.bus_naming_style()->string_value();
    library->set_attr("bus_naming_style", value);
  }

  // 'comment' の設定
  if ( library_info.comment() ) {
    ShString value = library_info.comment()->string_value();
    library->set_attr("comment", value);
  }

  // 'date' の設定
  if ( library_info.date() ) {
    ShString value = library_info.date()->string_value();
    library->set_attr("date", value);
  }

  // 'revision' の設定
  if ( library_info.revision() ) {
    ShString value = library_info.revision()->string_value();
    library->set_attr("revision", value);
  }

  // 'time_unit' の設定
  if ( library_info.time_unit() ) {
    ShString value = library_info.time_unit()->string_value();
    library->set_attr("time_unit", value);
  }

  // 'voltage_unit' の設定
  if ( library_info.voltage_unit() ) {
    ShString value = library_info.voltage_unit()->string_value();
    library->set_attr("voltage_unit", value);
  }

  // 'current_unit' の設定
  if ( library_info.current_unit() ) {
    ShString value = library_info.current_unit()->string_value();
    library->set_attr("current_unit", value);
  }

  // 'pulling_resistance_unit' の設定
  if ( library_info.pulling_resistance_unit() ) {
    ShString value = library_info.pulling_resistance_unit()->string_value();
    library->set_attr("pulling_resistance_unit", value);
  }

  // 'capacitive_load_unit' の設定
  if ( library_info.capacitive_load_unit() ) {
    double u = library_info.capacitive_load_unit();
    string ustr = library_info.capacitive_load_unit_str();
    library->set_capacitive_load_unit(u, ustr);
  }

  // 'leakage_power_unit' の設定
  if ( library_info.leakage_power_unit() ) {
    ShString value = library_info.leakage_power_unit()->string_value();
    library->set_attr("leakage_power_unit", value);
  }

  // 'lu_table_template' の設定
  const list<const DotlibNode*>& dt_lut_template_list =
    library_info.lut_template_list();
  vector<CiLutTemplate*> template_list;
  template_list.reserve(dt_lut_template_list.size());
  for ( auto dt_node: dt_lut_template_list ) {
    DotlibTemplate templ_info;
    if ( !templ_info.set_data(dt_node) ) {
      return;
    }

    CiLutTemplate* tmpl = nullptr;
    vector<double> index_1;
    vector<double> index_2;
    vector<double> index_3;
    int d = templ_info.dimension();
    switch ( d ) {
    case 1:
      templ_info.index_1()->get_vector(index_1);
      tmpl = library->new_lut_template1(templ_info.name(),
					templ_info.variable_1(), index_1);
      break;

    case 2:
      templ_info.index_1()->get_vector(index_1);
      templ_info.index_2()->get_vector(index_2);
      tmpl = library->new_lut_template2(templ_info.name(),
					templ_info.variable_1(), index_1,
					templ_info.variable_2(), index_2);
      break;

    case 3:
      templ_info.index_1()->get_vector(index_1);
      templ_info.index_2()->get_vector(index_2);
      templ_info.index_3()->get_vector(index_3);
      tmpl = library->new_lut_template3(templ_info.name(),
					templ_info.variable_1(), index_1,
					templ_info.variable_2(), index_2,
					templ_info.variable_3(), index_3);
      break;

    default:
      ASSERT_NOT_REACHED;
    }
    template_list.push_back(tmpl);
  }
  library->set_lu_table_template_list(template_list);

  // セルの内容の設定
  const list<const DotlibNode*>& dt_cell_list = library_info.cell_list();
  int nc = dt_cell_list.size();
  vector<CiCell*> cell_list;
  cell_list.reserve(nc);
  for ( const DotlibNode* dt_cell: dt_cell_list ) {
    // セル情報の読み出し
    DotlibCell cell_info;
    if ( !cell_info.set_data(dt_cell) ) {
      continue;
    }

    ShString cell_name = cell_info.name();
    ClibArea area(cell_info.area());
    const list<const DotlibNode*>& dt_pin_list = cell_info.pin_list();
    const list<const DotlibNode*>& dt_bus_list = cell_info.bus_list();
    const list<const DotlibNode*>& dt_bundle_list = cell_info.bundle_list();
    int npg = dt_pin_list.size();
    int nbus = dt_bus_list.size();
    int nbundle = dt_bundle_list.size();

    // ピン情報の読み出し
    vector<DotlibPin> pin_info_array(npg);
    {
      int i = 0;
      bool error = false;
      for ( const DotlibNode* dt_pin: dt_pin_list ) {
	// ピン情報の読み出し
	DotlibPin& pin_info = pin_info_array[i]; ++ i;
	if ( !pin_info.set_data(dt_pin) ) {
	  error = true;
	  break;
	}
      }
      if ( error ) {
	continue;
      }
      ASSERT_COND( i == npg );
    }

    // 各タイプの個数のカウント
    int ni = 0;
    int no = 0;
    int nio = 0;
    int nit = 0;
    for ( const DotlibPin& pin_info: pin_info_array ) {
      int nn = pin_info.num();
      switch ( pin_info.direction() ) {
      case DotlibPin::kInput:    ni += nn; break;
      case DotlibPin::kOutput:   no += nn; break;
      case DotlibPin::kInout:    nio += nn; break;
      case DotlibPin::kInternal: nit += nn; break;
      default: ASSERT_NOT_REACHED; break;
      }
    }

    int ni2 = ni + nio;
    int no2 = no + nio;

    // ピン名とピン番号の対応づけを行う．
    HashMap<ShString, int> pin_map;
    {
      int ipos = 0;
      int itpos = 0;
      for ( const DotlibPin& pin_info: pin_info_array ) {
	switch ( pin_info.direction() ) {
	case DotlibPin::kInput:
	case DotlibPin::kInout:
	  for ( int i = 0; i < pin_info.num(); ++ i ) {
	    pin_map.add(pin_info.name(i), ipos);
	    ++ ipos;
	  }
	  break;

	case DotlibPin::kInternal:
	  for ( int i = 0; i < pin_info.num(); ++ i ) {
	    pin_map.add(pin_info.name(i), itpos + ni2);
	    ++ itpos;
	  }
	  break;

	default:
	  break;
	}
      }
      ASSERT_COND( ipos == ni2 );
      ASSERT_COND( itpos == nit );
    }

    // FF情報の読み出し
    const DotlibNode* dt_ff = cell_info.ff();
    DotlibFF ff_info;
    if ( dt_ff != nullptr ) {
      if ( !ff_info.set_data(dt_ff) ) {
	continue;
      }
      ShString var1 = ff_info.var1_name();
      ShString var2 = ff_info.var2_name();
      // pin_map に登録しておく
      pin_map.add(var1, ni2 + 0);
      pin_map.add(var2, ni2 + 1);
    }

    // ラッチ情報の読み出し
    const DotlibNode* dt_latch = cell_info.latch();
    DotlibLatch latch_info;
    if ( dt_latch != nullptr) {
      if ( !latch_info.set_data(dt_latch) ) {
	continue;
      }
      ShString var1 = latch_info.var1_name();
      ShString var2 = latch_info.var2_name();
      // pin_map に登録しておく
      pin_map.add(var1, ni2 + 0);
      pin_map.add(var2, ni2 + 1);
    }

    // 遷移表情報の読み出し
    const DotlibNode* dt_fsm = cell_info.statetable();

    vector<CiInputPin*> input_list;
    vector<CiOutputPin*> output_list;
    vector<CiInoutPin*> inout_list;
    vector<CiInternalPin*> internal_list;
    vector<CiBus*> bus_list;
    vector<CiBundle*> bundle_list;

    input_list.reserve(ni);
    output_list.reserve(no);
    inout_list.reserve(nio);
    internal_list.reserve(nit);

    // ピンの生成
    gen_pin(pin_info_array, pin_map, library,
	    input_list,
	    output_list,
	    inout_list,
	    internal_list);

    // タイミング情報の生成
    vector<CiTiming*> timing_list;
    vector<vector<CiTiming*> > timing_list_array(ni2 * 2);
    gen_timing_list(pin_info_array, pin_map, library,
		    timing_list,
		    timing_list_array);

    // セルの生成
    CiCell* cell = nullptr;
    if ( dt_ff ) {
      Expr next_state = dot2expr(ff_info.next_state(), pin_map);
      Expr clocked_on = dot2expr(ff_info.clocked_on(), pin_map);
      Expr clocked_on_also = dot2expr(ff_info.clocked_on_also(), pin_map);
      Expr clear = dot2expr(ff_info.clear(), pin_map);
      Expr preset = dot2expr(ff_info.preset(), pin_map);
      int v1 = ff_info.clear_preset_var1();
      int v2 = ff_info.clear_preset_var2();
      cell = library->new_ff_cell(cell_name, area,
				  input_list,
				  output_list,
				  inout_list,
				  bus_list,
				  bundle_list,
				  timing_list,
				  next_state,
				  clocked_on, clocked_on_also,
				  clear, preset,
				  v1, v2);

    }
    else if ( dt_latch ) {
      Expr data_in = dot2expr(latch_info.data_in(), pin_map);
      Expr enable = dot2expr(latch_info.enable(), pin_map);
      Expr enable_also = dot2expr(latch_info.enable_also(), pin_map);
      Expr clear = dot2expr(latch_info.clear(), pin_map);
      Expr preset = dot2expr(latch_info.preset(), pin_map);
      int v1 = latch_info.clear_preset_var1();
      int v2 = latch_info.clear_preset_var2();
      cell = library->new_latch_cell(cell_name, area,
				     input_list,
				     output_list,
				     inout_list,
				     bus_list,
				     bundle_list,
				     timing_list,
				     data_in,
				     enable, enable_also,
				     clear, preset,
				     v1, v2);
    }
    else if ( dt_fsm ) {
      cell = library->new_fsm_cell(cell_name, area,
				   input_list,
				   output_list,
				   inout_list,
				   internal_list,
				   bus_list,
				   bundle_list,
				   timing_list);
    }
    else {
      cell = library->new_logic_cell(cell_name, area,
				     input_list,
				     output_list,
				     inout_list,
				     bus_list,
				     bundle_list,
				     timing_list);
    }
    cell_list.push_back(cell);

    // 個別の条件ごとのタイミング情報の設定
    for ( int oid = 0; oid < no2; ++ oid ) {
      const ClibCellPin* opin = cell->output(oid);
      ASSERT_COND( opin != nullptr );
      TvFunc tv_function;
      if ( opin->has_function() ) {
	Expr expr = opin->function();
	tv_function = expr.make_tv(ni2);
      }
      for ( int iid = 0; iid < ni2; ++ iid ) {
	TvFunc p_func = tv_function.cofactor(VarId(iid), false);
	TvFunc n_func = tv_function.cofactor(VarId(iid), true);

	const vector<CiTiming*>& timing_list_p = timing_list_array[iid * 2 + 0];
	if ( !timing_list_p.empty() ) {
	  CiTiming* timing = timing_list_p[0];
	  bool depend = true;
	  if ( timing->type() == kClibTimingCombinational ) {
	    if ( opin->has_function() && !(~n_func && p_func) ) {
	      depend = false;
	    }
	  }
	  if ( depend ) {
	    library->set_timing(cell, iid, oid, kClibPosiUnate, timing_list_p);
	  }
	}

	const vector<CiTiming*>& timing_list_n = timing_list_array[iid * 2 + 1];
	if ( !timing_list_n.empty() ) {
	  CiTiming* timing = timing_list_n[0];
	  bool depend = true;
	  if ( timing->type() == kClibTimingCombinational ) {
	    if ( opin->has_function() && !(~p_func && n_func) ) {
	      depend = false;
	    }
	  }
	  if ( depend ) {
	    library->set_timing(cell, iid, oid, kClibNegaUnate, timing_list_n);
	  }
	}
      }
    }
  }

  library->set_cell_list(cell_list);
}

END_NONAMESPACE

END_NAMESPACE_YM_DOTLIB


BEGIN_NAMESPACE_YM_CLIB

// @brief liberty 形式のファイルを読み込んでライブラリに設定する．
// @param[in] filename ファイル名
// @param[in] library 設定対象のライブラリ
// @return 読み込みが成功したら true を返す．
bool
CiCellLibrary::read_liberty(const string& filename)
{
  using namespace nsDotlib;

  DotlibMgr mgr;
  DotlibParser parser;
  if ( !parser.read_file(filename, mgr, false) ) {
    return false;
  }

  DotlibLibrary library_info;
  if ( !library_info.set_data(mgr.root_node()) ) {
    return false;
  }

  set_library(library_info, this);

  return true;
}

END_NAMESPACE_YM_CLIB
