
/// @file read_liberty.cc
/// @brief read_liberty の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/dotlib_nsdef.h"

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

#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstNode.h"
#include "dotlib/AstLibrary.h"
#include "dotlib/AstCell.h"
#include "dotlib/AstFF.h"
#include "dotlib/AstLatch.h"
#include "dotlib/AstPin.h"
#include "dotlib/AstTiming.h"
#include "dotlib/AstTemplate.h"
#include "dotlib/AstLut.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstFloatVector.h"
#include "dotlib/AstString.h"
#include "dotlib/AstUnit.h"
#include "dotlib/AstTechnology.h"
#include "dotlib/AstDelayModel.h"
#include "dotlib/AstPinDirection.h"
#include "dotlib/AstTimingSense.h"
#include "dotlib/AstTimingType.h"
#include "dotlib/AstVarType.h"

#include "ym/FileIDO.h"
#include "ym/Expr.h"
#include "ym/TvFunc.h"
#include "ym/MsgMgr.h"
#include "ym/Range.h"


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
    string tmp = tmp_str.substr(0, p);
    str_list.push_back(tmp);
    if ( p == string::npos ) {
      break;
    }
    tmp_str = tmp_str.substr(p + 1, string::npos);
  }
}

// lut を読み込む．
ClibLut*
gen_lut(CiCellLibrary* library,
	const AstLut* lut_node)
{
  const char* name = lut_node->template_name()->value();
  const ClibLutTemplate* templ = library->lu_table_template(name);
  if ( templ == nullptr ) {
    ostringstream buf;
    buf << lut_node->template_name()
	<< ": No such lu_table template";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    lut_node->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  int d = templ->dimension();

  vector<double> index1_array;
  if ( lut_node->index_1() ) {
    lut_node->index_1()->get_vector(index1_array);
  }
  vector<double> index2_array;
  if ( d >= 2 && lut_node->index_2() ) {
    lut_node->index_2()->get_vector(index2_array);
  }
  vector<double> index3_array;
  if ( d >= 3 && lut_node->index_3() ) {
    lut_node->index_3()->get_vector(index3_array);
  }

  const AstFloatVector* vector_node = lut_node->value_list();
  vector<double> value_array;
  vector_node->get_vector(value_array);

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
gen_expr(const AstExpr* expr_node,
	 const HashMap<ShString, int>& pin_map,
	 bool& has_expr)
{
  if ( expr_node ) {
    has_expr = true;
    return expr_node->to_expr(pin_map);
  }
  else {
    has_expr = false;
    return Expr::const_zero();
  }
}

// ピンを生成する．
void
gen_pin(const vector<const AstPin*>& pin_list,
	const HashMap<ShString, int>& pin_map,
	CiCellLibrary* library,
	vector<CiInputPin*>& input_list,
	vector<CiOutputPin*>& output_list,
	vector<CiInoutPin*>& inout_list,
	vector<CiInternalPin*>& internal_list)
{
  for ( auto pin_info: pin_list ) {
    switch ( pin_info->direction()->value() ) {
    case kClibCellPinInput:
      // 入力ピンの生成
      {
	ClibCapacitance cap(pin_info->capacitance()->value());
	ClibCapacitance rise_cap(pin_info->rise_capacitance()->value());
	ClibCapacitance fall_cap(pin_info->fall_capacitance()->value());
	for ( auto i: Range(pin_info->name_num()) ) {
	  ShString name = pin_info->name(i)->value();
	  CiInputPin* pin = library->new_cell_input(name, cap, rise_cap, fall_cap);
	  input_list.push_back(pin);
	}
      }
      break;

    case kClibCellPinOutput:
      // 出力の生成
      {
	bool has_logic;
	Expr logic_expr = gen_expr(pin_info->function(), pin_map, has_logic);
	bool dummy;
	Expr tristate_expr = gen_expr(pin_info->three_state(), pin_map, dummy);
	ClibCapacitance max_fanout(pin_info->max_fanout()->value());
	ClibCapacitance min_fanout (pin_info->min_fanout()->value());
	ClibCapacitance max_capacitance(pin_info->max_capacitance()->value());
	ClibCapacitance min_capacitance(pin_info->min_capacitance()->value());
	ClibTime max_transition(pin_info->max_transition()->value());
	ClibTime min_transition(pin_info->min_transition()->value());
	for ( auto i: Range(pin_info->name_num()) ) {
	  ShString name = pin_info->name(i)->value();
	  CiOutputPin* pin = library->new_cell_output(name,
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

    case kClibCellPinInout:
      // 入出力ピンの生成
      {
	bool has_logic;
	Expr logic_expr = gen_expr(pin_info->function(), pin_map, has_logic);
	bool dummy;
	Expr tristate_expr = gen_expr(pin_info->three_state(), pin_map, dummy);
	ClibCapacitance cap(pin_info->capacitance()->value());
	ClibCapacitance rise_cap(pin_info->rise_capacitance()->value());
	ClibCapacitance fall_cap(pin_info->fall_capacitance()->value());
	ClibCapacitance max_fanout(pin_info->max_fanout()->value());
	ClibCapacitance min_fanout(pin_info->min_fanout()->value());
	ClibCapacitance max_capacitance(pin_info->max_capacitance()->value());
	ClibCapacitance min_capacitance(pin_info->min_capacitance()->value());
	ClibTime max_transition(pin_info->max_transition()->value());
	ClibTime min_transition(pin_info->min_transition()->value());
	for ( auto i: Range(pin_info->name_num()) ) {
	  ShString name = pin_info->name(i)->value();
	  CiInoutPin* pin = library->new_cell_inout(name,
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

    case kClibCellPinInternal:
      // 内部ピンの生成
      for ( auto i: Range(pin_info->name_num()) ) {
	ShString name = pin_info->name(i)->value();
	CiInternalPin* pin = library->new_cell_internal(name);
	internal_list.push_back(pin);
      }
      break;

    default:
      ASSERT_NOT_REACHED;
    }
  }
}

void
gen_timing_list(const vector<const AstPin*> pin_list,
		const HashMap<ShString, int>& pin_map,
		CiCellLibrary* library,
		vector<CiTiming*>& timing_list,
		vector<vector<CiTiming*> >& timing_list_array)
{
  for ( auto pin_info: pin_list ) {
    vector<const AstTiming*> dt_timing_list;
    for ( auto i: Range(pin_info->timing_num()) ) {
      auto dl_timing = pin_info->timing_elem(i);
      ClibTimingType timing_type = dl_timing->timing_type()->value();
      bool dummy;
      Expr cond = gen_expr(dl_timing->when(), pin_map, dummy);
      CiTiming* timing = nullptr;
      switch ( library->delay_model() ) {
      case kClibDelayGenericCmos:
	{
	  ClibTime intrinsic_rise(dl_timing->intrinsic_rise()->value());
	  ClibTime intrinsic_fall(dl_timing->intrinsic_fall()->value());
	  ClibTime slope_rise(dl_timing->slope_rise()->value());
	  ClibTime slope_fall(dl_timing->slope_fall()->value());
	  ClibResistance rise_res(dl_timing->rise_resistance()->value());
	  ClibResistance fall_res(dl_timing->fall_resistance()->value());
	  timing = library->new_timing_generic(timing_type, cond,
					       intrinsic_rise, intrinsic_fall,
					       slope_rise, slope_fall,
					       rise_res, fall_res);
	}
	break;

      case kClibDelayTableLookup:
	{
	  const AstLut* cr_node = dl_timing->cell_rise();
	  const AstLut* rt_node = dl_timing->rise_transition();
	  const AstLut* rp_node = dl_timing->rise_propagation();

	  ClibLut* cr_lut = nullptr;
	  ClibLut* rt_lut = nullptr;
	  ClibLut* rp_lut = nullptr;
	  if ( cr_node != nullptr ) {
	    if ( rp_node != nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dl_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "cell_rise and rise_propagation are mutually exclusive.");
	      continue;
	    }
	    if ( rt_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dl_timing->loc(),
			      MsgType::Error,
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
			      dl_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "rise_transition is missing.");
	      continue;
	    }
	    rt_lut = gen_lut(library, rt_node);
	    rp_lut = gen_lut(library, rp_node);
	  }
	  else if ( rt_node != nullptr ) {
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    dl_timing->loc(),
			    MsgType::Error,
			    "DOTLIB_PARSER",
			    "Either cell_rise or rise_propagation should be present.");
	    continue;
	  }

	  const AstLut* cf_node = dl_timing->cell_fall();
	  const AstLut* ft_node = dl_timing->fall_transition();
	  const AstLut* fp_node = dl_timing->fall_propagation();

	  ClibLut* cf_lut = nullptr;
	  ClibLut* ft_lut = nullptr;
	  ClibLut* fp_lut = nullptr;
	  if ( cf_node != nullptr ) {
	    if ( fp_node != nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dl_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "cell_fall and fall_propagation are mutually exclusive.");
	      continue;
	    }
	    if ( ft_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dl_timing->loc(),
			      MsgType::Error,
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
			      dl_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "fall_transition is missing.");
	      continue;
	    }
	    ft_lut = gen_lut(library, ft_node);
	    fp_lut = gen_lut(library, fp_node);
	  }
	  else if ( ft_node != nullptr ) {
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    dl_timing->loc(),
			    MsgType::Error,
			    "DOTLIB_PARSER",
			    "Either cell_fall or fall_propagation should be present.");
	    continue;
	  }

	  if ( cr_lut != nullptr || cf_lut != nullptr ) {
	    if ( fp_lut != nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      dl_timing->loc(),
			      MsgType::Error,
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

      ClibTimingSense timing_sense = dl_timing->timing_sense()->value();

      // タイミング情報の設定
      if ( dl_timing->related_pin() ) {
	ShString tmp_str = dl_timing->related_pin()->value();
	vector<string> pin_name_list;
	split(tmp_str, pin_name_list);
	for ( auto pin_name: pin_name_list ) {
	  int id;
	  if ( !pin_map.find(ShString(pin_name), id) ) {
	    ostringstream buf;
	    buf << pin_name << ": no such pin";
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    dl_timing->loc(),
			    MsgType::Error,
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
			dl_timing->loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"No \"related_pin\"");
      }
    }
  }
}

// @brief AstNode から CiCellLibrary を生成する．
// @param[in] library_info ライブラリの情報を持つオブジェクト
// @param[in] library設定対象のライブラリ
void
set_library(const AstLibrary* dt_library,
	    CiCellLibrary* library)
{
  // 'name' の設定
  library->set_name(dt_library->name()->value());

  // 'technology' の設定
  library->set_technology(dt_library->technology()->value());

  // 'delay_model' の設定
  library->set_delay_model(dt_library->delay_model()->value());

  // 'bus_naming_style' の設定
  if ( dt_library->bus_naming_style() ) {
    ShString value = dt_library->bus_naming_style()->value();
    library->set_attr("bus_naming_style", value);
  }

  // 'comment' の設定
  if ( dt_library->comment() ) {
    ShString value = dt_library->comment()->value();
    library->set_attr("comment", value);
  }

  // 'date' の設定
  if ( dt_library->date() ) {
    ShString value = dt_library->date()->value();
    library->set_attr("date", value);
  }

  // 'revision' の設定
  if ( dt_library->revision() ) {
    ShString value = dt_library->revision()->value();
    library->set_attr("revision", value);
  }

  // 'time_unit' の設定
  if ( dt_library->time_unit() ) {
    ShString value = dt_library->time_unit()->value();
    library->set_attr("time_unit", value);
  }

  // 'voltage_unit' の設定
  if ( dt_library->voltage_unit() ) {
    ShString value = dt_library->voltage_unit()->value();
    library->set_attr("voltage_unit", value);
  }

  // 'current_unit' の設定
  if ( dt_library->current_unit() ) {
    ShString value = dt_library->current_unit()->value();
    library->set_attr("current_unit", value);
  }

  // 'pulling_resistance_unit' の設定
  if ( dt_library->pulling_resistance_unit() ) {
    ShString value = dt_library->pulling_resistance_unit()->value();
    library->set_attr("pulling_resistance_unit", value);
  }

  // 'capacitive_load_unit' の設定
  if ( dt_library->capacitive_load_unit() ) {
    double u = dt_library->capacitive_load_unit()->unit_val();
    string ustr = dt_library->capacitive_load_unit()->unit_str();
    library->set_capacitive_load_unit(u, ustr);
  }

  // 'leakage_power_unit' の設定
  if ( dt_library->leakage_power_unit() ) {
    ShString value = dt_library->leakage_power_unit()->value();
    library->set_attr("leakage_power_unit", value);
  }

  // 'lu_table_template' の設定
  vector<CiLutTemplate*> template_list;
  template_list.reserve(dt_library->lut_template_num());
  for ( auto i: Range(dt_library->lut_template_num()) ) {
    auto dt_template =  dt_library->lut_template_elem(i);
    CiLutTemplate* tmpl = nullptr;
    vector<double> index_1;
    vector<double> index_2;
    vector<double> index_3;
    int d = dt_template->dimension();
    switch ( d ) {
    case 1:
      dt_template->index_1()->get_vector(index_1);
      tmpl = library->new_lut_template1(dt_template->name()->value(),
					dt_template->variable_1()->value(), index_1);
      break;

    case 2:
      dt_template->index_1()->get_vector(index_1);
      dt_template->index_2()->get_vector(index_2);
      tmpl = library->new_lut_template2(dt_template->name()->value(),
					dt_template->variable_1()->value(), index_1,
					dt_template->variable_2()->value(), index_2);
      break;

    case 3:
      dt_template->index_1()->get_vector(index_1);
      dt_template->index_2()->get_vector(index_2);
      dt_template->index_3()->get_vector(index_3);
      tmpl = library->new_lut_template3(dt_template->name()->value(),
					dt_template->variable_1()->value(), index_1,
					dt_template->variable_2()->value(), index_2,
					dt_template->variable_3()->value(), index_3);
      break;

    default:
      ASSERT_NOT_REACHED;
    }
    template_list.push_back(tmpl);
  }
  library->set_lu_table_template_list(template_list);

  // セルの内容の設定
  //const vector<const AstCell*>& dt_cell_list = dt_library->cell_list();
#warning "TODO: 未完成"
  vector<const AstCell*> dt_cell_list;
  int nc = dt_cell_list.size();
  vector<CiCell*> cell_list;
  cell_list.reserve(nc);
  for ( const AstCell* dt_cell: dt_cell_list ) {
    ShString cell_name = dt_cell->name()->value();
    ClibArea area(dt_cell->area()->value());

    // 各タイプの個数のカウント
    int ni = 0;
    int no = 0;
    int nio = 0;
    int nit = 0;
    vector<const AstPin*> dt_pin_list;
    for ( auto i: Range(dt_cell->pin_num()) ) {
      auto pin_info = dt_cell->pin_elem(i);
      int nn = pin_info->name_num();
      switch ( pin_info->direction()->value() ) {
      case kClibCellPinInput:    ni += nn; break;
      case kClibCellPinOutput:   no += nn; break;
      case kClibCellPinInout:    nio += nn; break;
      case kClibCellPinInternal: nit += nn; break;
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
      for ( auto i: Range(dt_cell->pin_num()) ) {
	auto pin_info = dt_cell->pin_elem(i);
	switch ( pin_info->direction()->value() ) {
	case kClibCellPinInput:
	case kClibCellPinInout:
	  for ( auto j: Range(pin_info->name_num()) ) {
	    pin_map.add(pin_info->name(j)->value(), ipos);
	    ++ ipos;
	  }
	  break;

	case kClibCellPinInternal:
	  for ( auto j: Range(pin_info->name_num()) ) {
	    pin_map.add(pin_info->name(j)->value(), itpos + ni2);
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

    // ff情報の読み出し
    const AstFF* ff_info = dt_cell->ff();
    if ( ff_info != nullptr ) {
      ShString var1 = ff_info->var1_name()->value();
      ShString var2 = ff_info->var2_name()->value();
      // pin_map に登録しておく
      pin_map.add(var1, ni2 + 0);
      pin_map.add(var2, ni2 + 1);
    }

    // ラッチ情報の読み出し
    const AstLatch* latch_info = dt_cell->latch();
    if ( latch_info != nullptr) {
      ShString var1 = latch_info->var1_name()->value();
      ShString var2 = latch_info->var2_name()->value();
      // pin_map に登録しておく
      pin_map.add(var1, ni2 + 0);
      pin_map.add(var2, ni2 + 1);
    }

    // 遷移表情報の読み出し
    const AstStateTable* statetable_info = dt_cell->state_table();

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
    gen_pin(dt_pin_list, pin_map, library,
	    input_list,
	    output_list,
	    inout_list,
	    internal_list);

    // タイミング情報の生成
    vector<CiTiming*> timing_list;
    vector<vector<CiTiming*> > timing_list_array(ni2 * 2);
    gen_timing_list(dt_pin_list, pin_map, library,
		    timing_list,
		    timing_list_array);

    // セルの生成
    CiCell* cell = nullptr;
    if ( ff_info ) {
      bool dummy;
      Expr next_state = gen_expr(ff_info->next_state(), pin_map, dummy);
      Expr clocked_on = gen_expr(ff_info->clocked_on(), pin_map, dummy);
      Expr clocked_on_also = gen_expr(ff_info->clocked_on_also(), pin_map, dummy);
      Expr clear = gen_expr(ff_info->clear(), pin_map, dummy);
      Expr preset = gen_expr(ff_info->preset(), pin_map, dummy);
      int v1 = ff_info->clear_preset_var1();
      int v2 = ff_info->clear_preset_var2();
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
    else if ( latch_info ) {
      bool dummy;
      Expr data_in = gen_expr(latch_info->data_in(), pin_map, dummy);
      Expr enable = gen_expr(latch_info->enable(), pin_map, dummy);
      Expr enable_also = gen_expr(latch_info->enable_also(), pin_map, dummy);
      Expr clear = gen_expr(latch_info->clear(), pin_map, dummy);
      Expr preset = gen_expr(latch_info->preset(), pin_map, dummy);
      int v1 = latch_info->clear_preset_var1();
      int v2 = latch_info->clear_preset_var2();
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
    else if ( statetable_info ) {
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

  FileIDO ido;
  if ( !ido.open(filename) ) {
    ostringstream buf;
    buf << filename << ": Could not open.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(),
		    MsgType::Failure,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  AstMgr mgr;
  DotlibParser parser(ido, mgr, false);
  const AstLibrary* dt_library = parser.parse();
  if ( dt_library == nullptr ) {
    return false;
  }

  set_library(dt_library, this);

  return true;
}

END_NAMESPACE_YM_CLIB
