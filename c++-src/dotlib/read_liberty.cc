
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
#include "ci/CiLutTemplate.h"

#include "ym/ClibCellPin.h"
#include "ym/ClibTiming.h"
#include "ym/ClibArea.h"
#include "ym/ClibResistance.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibTime.h"
#include "ym/ClibLut.h"
#include "ym/ClibLutTemplate.h"

#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"

#include "ym/Expr.h"
#include "ym/TvFunc.h"
#include "ym/MsgMgr.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_DOTLIB

BEGIN_NONAMESPACE

// 文字列を空白で区切る
// string の定番コード
// ただし結果は ShString のリストとなる．
vector<ShString>
split(const string& src_str,
      const string& delim = " \t\n")
{
  vector<ShString> ans;
  string::size_type start = 0;
  for ( ; ; ) {
    // start 以降で初めて delim とマッチする位置を探す．
    string::size_type p = src_str.find_first_of(delim, start);
    if ( p == string::npos ) {
      // 終端に達した．
      break;
    }
    string::size_type n = p - start;
    if ( n > 0 ) {
      string tmp = src_str.substr(start, n);
      ans.push_back(ShString(tmp));
    }
    start = p + 1;
  }
  return ans;
}

#if 0
// lut を読み込む．
ClibLut*
gen_lut(CiCellLibrary* library,
	const AstLut* lut_node,
	const unordered_map<ShString, const ClibLutTemplate*>& template_dict)
{
  // lut 名を template_dict から探す．
  ShString name{lut_node->name()->string_value()};
  if ( template_dict.count(name) == 0 ) {
    // 見つからなかった．
    ostringstream buf;
    buf << lut_node->name()
	<< ": No such lu_table template";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    lut_node->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  // テンプレートを取り出す．
  auto templ{template_dict.at(name)};
  int d = templ->dimension();

  // 各軸のインデックス値を取り出す．
  vector<double> index1_array;
  if ( lut_node->index_1() ) {
    index1_array = lut_node->index_1()->float_vector_value();
  }
  vector<double> index2_array;
  if ( d >= 2 && lut_node->index_2() ) {
    index2_array = lut_node->index_2()->float_vector_value();
  }
  vector<double> index3_array;
  if ( d >= 3 && lut_node->index_3() ) {
    index3_array = lut_node->index_3()->float_vector_value();
  }

  // 値を取り出す．
  auto vector_node{lut_node->value_list()};
  vector<double> value_array{vector_node->float_vector_value()};

  ClibLut* lut = nullptr;
  switch ( d ) {
  case 1:
    lut = library->new_lut1(templ, value_array,
			    index1_array);
    break;
  case 2:
    lut = library->new_lut2(templ, value_array,
			    index1_array,
			    index2_array);
    break;
  case 3:
    lut = library->new_lut3(templ, value_array,
			    index1_array,
			    index2_array,
			    index3_array);
    break;
  default:
    ASSERT_NOT_REACHED;
    break;
  }
  return lut;
}

// 論理式を生成する．
Expr
gen_expr(const AstExpr* expr_node,
	 const unordered_map<ShString, int>& pin_map,
	 bool& has_expr)
{
  if ( expr_node ) {
    has_expr = true;
    return expr_node->to_expr(pin_map);
  }
  else {
    has_expr = false;
    return Expr::make_zero();
  }
}

// ピンを生成する．
void
gen_pin(const vector<const AstPin*>& pin_list,
	const unordered_map<ShString, int>& pin_map,
	CiCellLibrary* library,
	vector<CiInputPin*>& input_list,
	vector<CiOutputPin*>& output_list,
	vector<CiInoutPin*>& inout_list,
	vector<CiInternalPin*>& internal_list)
{
  for ( auto pin_info: pin_list ) {
    switch ( pin_info->direction()->direction_value() ) {
    case ClibDirection::Input:
      // 入力ピンの生成
      {
	ClibCapacitance cap{pin_info->capacitance()->float_value()};
	ClibCapacitance rise_cap{pin_info->rise_capacitance()->float_value()};
	ClibCapacitance fall_cap{pin_info->fall_capacitance()->float_value()};
	for ( auto name: pin_info->name_list() ) {
	  CiInputPin* pin = library->new_cell_input(name->string_value(), cap, rise_cap, fall_cap);
	  input_list.push_back(pin);
	}
      }
      break;

    case ClibDirection::Output:
      // 出力の生成
      {
	bool has_logic;
	Expr logic_expr = gen_expr(pin_info->function(), pin_map, has_logic);
	bool dummy;
	Expr tristate_expr = gen_expr(pin_info->three_state(), pin_map, dummy);
	ClibCapacitance max_fanout{pin_info->max_fanout()->float_value()};
	ClibCapacitance min_fanout{pin_info->min_fanout()->float_value()};
	ClibCapacitance max_capacitance{pin_info->max_capacitance()->float_value()};
	ClibCapacitance min_capacitance{pin_info->min_capacitance()->float_value()};
	ClibTime max_transition{pin_info->max_transition()->float_value()};
	ClibTime min_transition{pin_info->min_transition()->float_value()};
	for ( auto name: pin_info->name_list() ) {
	  CiOutputPin* pin = library->new_cell_output(name->string_value(),
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

    case ClibDirection::Inout:
      // 入出力ピンの生成
      {
	bool has_logic;
	Expr logic_expr = gen_expr(pin_info->function(), pin_map, has_logic);
	bool dummy;
	Expr tristate_expr = gen_expr(pin_info->three_state(), pin_map, dummy);
	ClibCapacitance cap{pin_info->capacitance()->float_value()};
	ClibCapacitance rise_cap{pin_info->rise_capacitance()->float_value()};
	ClibCapacitance fall_cap{pin_info->fall_capacitance()->float_value()};
	ClibCapacitance max_fanout{pin_info->max_fanout()->float_value()};
	ClibCapacitance min_fanout{pin_info->min_fanout()->float_value()};
	ClibCapacitance max_capacitance{pin_info->max_capacitance()->float_value()};
	ClibCapacitance min_capacitance{pin_info->min_capacitance()->float_value()};
	ClibTime max_transition{pin_info->max_transition()->float_value()};
	ClibTime min_transition{pin_info->min_transition()->float_value()};
	for ( auto name: pin_info->name_list() ) {
	  CiInoutPin* pin = library->new_cell_inout(name->string_value(),
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

    case ClibDirection::Internal:
      // 内部ピンの生成
      for ( auto name: pin_info->name_list() ) {
	CiInternalPin* pin = library->new_cell_internal(name->string_value());
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
		const unordered_map<ShString, int>& pin_map,
		const unordered_map<ShString, const ClibLutTemplate*>& template_dict,
		CiCellLibrary* library,
		vector<CiTiming*>& timing_list,
		vector<vector<CiTiming*> >& timing_list_array)
{
  for ( auto pin_info: pin_list ) {
    for ( auto ast_timing: pin_info->timing_list() ) {
      ClibTimingType timing_type = ast_timing->timing_type()->timing_type_value();
      bool dummy;
      Expr cond = gen_expr(ast_timing->when(), pin_map, dummy);
      CiTiming* timing = nullptr;
      switch ( library->delay_model() ) {
      case ClibDelayModel::GenericCmos:
	{
	  ClibTime intrinsic_rise{ast_timing->intrinsic_rise()->float_value()};
	  ClibTime intrinsic_fall{ast_timing->intrinsic_fall()->float_value()};
	  ClibTime slope_rise{ast_timing->slope_rise()->float_value()};
	  ClibTime slope_fall{ast_timing->slope_fall()->float_value()};
	  ClibResistance rise_res{ast_timing->rise_resistance()->float_value()};
	  ClibResistance fall_res{ast_timing->fall_resistance()->float_value()};
	  timing = library->new_timing_generic(timing_type, cond,
					       intrinsic_rise, intrinsic_fall,
					       slope_rise, slope_fall,
					       rise_res, fall_res);
	}
	break;

      case ClibDelayModel::TableLookup:
	{
	  const AstLut* cr_node = ast_timing->cell_rise();
	  const AstLut* rt_node = ast_timing->rise_transition();
	  const AstLut* rp_node = ast_timing->rise_propagation();

	  ClibLut* cr_lut = nullptr;
	  ClibLut* rt_lut = nullptr;
	  ClibLut* rp_lut = nullptr;
	  if ( cr_node != nullptr ) {
	    if ( rp_node != nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      ast_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "cell_rise and rise_propagation are mutually exclusive.");
	      continue;
	    }
	    if ( rt_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      ast_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "rise_transition is missing.");
	      continue;
	    }
	    cr_lut = gen_lut(library, cr_node, template_dict);
	    rt_lut = gen_lut(library, rt_node, template_dict);
	  }
	  else if ( rp_node != nullptr ) {
	    if ( rt_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      ast_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "rise_transition is missing.");
	      continue;
	    }
	    rt_lut = gen_lut(library, rt_node, template_dict);
	    rp_lut = gen_lut(library, rp_node, template_dict);
	  }
	  else if ( rt_node != nullptr ) {
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    ast_timing->loc(),
			    MsgType::Error,
			    "DOTLIB_PARSER",
			    "Either cell_rise or rise_propagation should be present.");
	    continue;
	  }

	  const AstLut* cf_node = ast_timing->cell_fall();
	  const AstLut* ft_node = ast_timing->fall_transition();
	  const AstLut* fp_node = ast_timing->fall_propagation();

	  ClibLut* cf_lut = nullptr;
	  ClibLut* ft_lut = nullptr;
	  ClibLut* fp_lut = nullptr;
	  if ( cf_node != nullptr ) {
	    if ( fp_node != nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      ast_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "cell_fall and fall_propagation are mutually exclusive.");
	      continue;
	    }
	    if ( ft_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      ast_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "fall_transition is missing.");
	      continue;
	    }
	    cf_lut = gen_lut(library, cf_node, template_dict);
	    ft_lut = gen_lut(library, ft_node, template_dict);
	  }
	  else if ( fp_node != nullptr ) {
	    if ( ft_node == nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      ast_timing->loc(),
			      MsgType::Error,
			      "DOTLIB_PARSER",
			      "fall_transition is missing.");
	      continue;
	    }
	    ft_lut = gen_lut(library, ft_node, template_dict);
	    fp_lut = gen_lut(library, fp_node, template_dict);
	  }
	  else if ( ft_node != nullptr ) {
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    ast_timing->loc(),
			    MsgType::Error,
			    "DOTLIB_PARSER",
			    "Either cell_fall or fall_propagation should be present.");
	    continue;
	  }

	  if ( cr_lut != nullptr || cf_lut != nullptr ) {
	    if ( fp_lut != nullptr ) {
	      MsgMgr::put_msg(__FILE__, __LINE__,
			      ast_timing->loc(),
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

      case ClibDelayModel::PiecewiseCmos:
	// 未実装
	break;

      case ClibDelayModel::Cmos2:
	// 未実装
	break;

      case ClibDelayModel::Dcm:
	// 未実装
	break;

      case ClibDelayModel::None:
	ASSERT_NOT_REACHED;
	break;
      }
      timing_list.push_back(timing);

      ClibTimingSense timing_sense = ast_timing->timing_sense()->timing_sense_value();

      // タイミング情報の設定
      if ( ast_timing->related_pin() ) {
	string tmp_str{ast_timing->related_pin()->string_value()};
	auto pin_name_list = split(tmp_str);
	for ( auto pin_name: pin_name_list ) {
	  if ( pin_map.count(pin_name) == 0 ) {
	    ostringstream buf;
	    buf << pin_name << ": no such pin";
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    ast_timing->loc(),
			    MsgType::Error,
			    "DOTLIB_PARSER",
			    buf.str());
	    continue;
	  }
	  int id = pin_map.at(pin_name);
	  switch ( timing_sense ) {
	  case ClibTimingSense::PosiUnate:
	    timing_list_array[id * 2 + 0].push_back(timing);
	    break;

	  case ClibTimingSense::NegaUnate:
	    timing_list_array[id * 2 + 1].push_back(timing);
	    break;

	  case ClibTimingSense::NonUnate:
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
			ast_timing->loc(),
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
set_library(const AstLibrary* ast_library,
	    CiCellLibrary* library)
{
  // 'name' の設定
  library->set_name(ast_library->name()->string_value());

  // 'technology' の設定
  library->set_technology(ast_library->technology()->technology_value());

  // 'delay_model' の設定
  library->set_delay_model(ast_library->delay_model()->delay_model_value());

  // 'bus_naming_style' の設定
  if ( ast_library->bus_naming_style() ) {
    ShString value = ast_library->bus_naming_style()->string_value();
    library->set_attr("bus_naming_style", value);
  }

  // 'comment' の設定
  if ( ast_library->comment() ) {
    ShString value = ast_library->comment()->string_value();
    library->set_attr("comment", value);
  }

  // 'date' の設定
  if ( ast_library->date() ) {
    ShString value = ast_library->date()->string_value();
    library->set_attr("date", value);
  }

  // 'revision' の設定
  if ( ast_library->revision() ) {
    ShString value = ast_library->revision()->string_value();
    library->set_attr("revision", value);
  }

  // 'time_unit' の設定
  if ( ast_library->time_unit() ) {
    ShString value = ast_library->time_unit()->string_value();
    library->set_attr("time_unit", value);
  }

  // 'voltage_unit' の設定
  if ( ast_library->voltage_unit() ) {
    ShString value = ast_library->voltage_unit()->string_value();
    library->set_attr("voltage_unit", value);
  }

  // 'current_unit' の設定
  if ( ast_library->current_unit() ) {
    ShString value = ast_library->current_unit()->string_value();
    library->set_attr("current_unit", value);
  }

  // 'pulling_resistance_unit' の設定
  if ( ast_library->pulling_resistance_unit() ) {
    ShString value = ast_library->pulling_resistance_unit()->string_value();
    library->set_attr("pulling_resistance_unit", value);
  }

  // 'capacitive_load_unit' の設定
  if ( ast_library->capacitive_load_unit() ) {
    double u = ast_library->capacitive_load_unit()->value1()->float_value();
    ShString ustr = ast_library->capacitive_load_unit()->value2()->string_value();
    library->set_capacitive_load_unit(u, ustr);
  }

  // 'leakage_power_unit' の設定
  if ( ast_library->leakage_power_unit() ) {
    ShString value = ast_library->leakage_power_unit()->string_value();
    library->set_attr("leakage_power_unit", value);
  }

  // 'lu_table_template' の設定
  vector<CiLutTemplate*> template_list;
  unordered_map<ShString, const ClibLutTemplate*> template_dict;
  for ( auto ast_template: ast_library->lut_template_list() ) {
    CiLutTemplate* tmpl = nullptr;
    ShString name = ast_template->name()->string_value();
    int d = ast_template->dimension();
    switch ( d ) {
    case 1:
      tmpl = library->new_lut_template1(name,
					ast_template->variable_1()->vartype_value(),
					ast_template->index_1()->float_vector_value());
      break;

    case 2:
      tmpl = library->new_lut_template2(name,
					ast_template->variable_1()->vartype_value(),
					ast_template->index_1()->float_vector_value(),
					ast_template->variable_2()->vartype_value(),
					ast_template->index_2()->float_vector_value());
      break;

    case 3:
      tmpl = library->new_lut_template3(name,
					ast_template->variable_1()->vartype_value(),
					ast_template->index_1()->float_vector_value(),
					ast_template->variable_2()->vartype_value(),
					ast_template->index_2()->float_vector_value(),
					ast_template->variable_3()->vartype_value(),
					ast_template->index_3()->float_vector_value());
      break;

    default:
      ASSERT_NOT_REACHED;
    }
    template_list.push_back(tmpl);
    template_dict[name] = tmpl;
  }
  library->set_lu_table_template_list(template_list);

  // セルの内容の設定
  vector<CiCell*> cell_list;
  cell_list.reserve(ast_library->cell_list().size());
  for ( const AstCell* ast_cell: ast_library->cell_list() ) {
    ShString cell_name = ast_cell->name()->string_value();
    ClibArea area(ast_cell->area()->float_value());

    // 各タイプの個数のカウント
    int ni = 0;
    int no = 0;
    int nio = 0;
    int nit = 0;
    vector<const AstPin*> dt_pin_list;
    for ( auto pin_info: ast_cell->pin_list() ) {
      int nn = pin_info->name_list().size();
      switch ( pin_info->direction()->direction_value() ) {
      case ClibDirection::Input:    ni += nn; break;
      case ClibDirection::Output:   no += nn; break;
      case ClibDirection::Inout:    nio += nn; break;
      case ClibDirection::Internal: nit += nn; break;
      default: ASSERT_NOT_REACHED; break;
      }
    }

    int ni2 = ni + nio;
    int no2 = no + nio;

    // ピン名とピン番号の対応づけを行う．
    unordered_map<ShString, int> pin_map;
    {
      int ipos = 0;
      int itpos = 0;
      for ( auto pin_info: ast_cell->pin_list() ) {
	switch ( pin_info->direction()->direction_value() ) {
	case ClibDirection::Input:
	case ClibDirection::Inout:
	  for ( auto name: pin_info->name_list() ) {
	    pin_map[name->string_value()] = ipos;
	    ++ ipos;
	  }
	  break;

	case ClibDirection::Internal:
	  for ( auto name: pin_info->name_list() ) {
	    pin_map[name->string_value()] = itpos + ni2;
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
    const AstFF* ff_info = ast_cell->ff();
    if ( ff_info != nullptr ) {
      ShString var1 = ff_info->var1_name()->string_value();
      ShString var2 = ff_info->var2_name()->string_value();
      // pin_map に登録しておく
      pin_map[var1] = ni2 + 0;
      pin_map[var2] = ni2 + 1;
    }

    // ラッチ情報の読み出し
    const AstLatch* latch_info = ast_cell->latch();
    if ( latch_info != nullptr) {
      ShString var1 = latch_info->var1_name()->string_value();
      ShString var2 = latch_info->var2_name()->string_value();
      // pin_map に登録しておく
      pin_map[var1] = ni2 + 0;
      pin_map[var2] = ni2 + 1;
    }

    // 遷移表情報の読み出し
    const AstStateTable* statetable_info = ast_cell->state_table();

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
    vector<vector<CiTiming*>> timing_list_array(ni2 * 2);
    gen_timing_list(dt_pin_list, pin_map, template_dict,
		    library, timing_list, timing_list_array);

    // セルの生成
    CiCell* cell = nullptr;
    if ( ff_info ) {
      bool dummy;
      Expr next_state = gen_expr(ff_info->next_state(), pin_map, dummy);
      Expr clocked_on = gen_expr(ff_info->clocked_on(), pin_map, dummy);
      Expr clocked_on_also = gen_expr(ff_info->clocked_on_also(), pin_map, dummy);
      Expr clear = gen_expr(ff_info->clear(), pin_map, dummy);
      Expr preset = gen_expr(ff_info->preset(), pin_map, dummy);
      AstCPType::Type v1 = ff_info->clear_preset_var1()->value();
      AstCPType::Type v2 = ff_info->clear_preset_var2()->value();
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
      AstCPType::Type v1 = latch_info->clear_preset_var1()->value();
      AstCPType::Type v2 = latch_info->clear_preset_var2()->value();
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
      auto& opin = cell->output(oid);
      TvFunc tv_function;
      if ( opin.has_function() ) {
	Expr expr = opin.function();
	tv_function = expr.make_tv(ni2);
      }
      for ( int iid = 0; iid < ni2; ++ iid ) {
	TvFunc p_func = tv_function.cofactor(VarId(iid), false);
	TvFunc n_func = tv_function.cofactor(VarId(iid), true);

	const vector<CiTiming*>& timing_list_p = timing_list_array[iid * 2 + 0];
	if ( !timing_list_p.empty() ) {
	  CiTiming* timing = timing_list_p[0];
	  bool depend = true;
	  if ( timing->type() == ClibTimingType::Combinational ) {
	    if ( opin.has_function() && !(~n_func && p_func) ) {
	      depend = false;
	    }
	  }
	  if ( depend ) {
	    library->set_timing(cell, iid, oid, ClibTimingSense::PosiUnate, timing_list_p);
	  }
	}

	const vector<CiTiming*>& timing_list_n = timing_list_array[iid * 2 + 1];
	if ( !timing_list_n.empty() ) {
	  CiTiming* timing = timing_list_n[0];
	  bool depend = true;
	  if ( timing->type() == ClibTimingType::Combinational ) {
	    if ( opin.has_function() && !(~p_func && n_func) ) {
	      depend = false;
	    }
	  }
	  if ( depend ) {
	    library->set_timing(cell, iid, oid, ClibTimingSense::NegaUnate, timing_list_n);
	  }
	}
      }
    }
  }

  library->set_cell_list(cell_list);
}
#endif

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

  // ファイルを開く
  ifstream fin(filename);
  if ( !fin ) {
    ostringstream buf;
    buf << filename << ": Could not open.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(),
		    MsgType::Failure,
		    "DOTLIB_PARSER",
		    buf.str());
    // ファイルが開けなかった．
    return false;
  }

  // 読み込んでASTを作る．
  InputFileObj in{fin, {filename}};
  Parser parser(in, false);
  auto ast_library{parser.parse()};
  if ( ast_library == nullptr ) {
    // 読み込みに失敗した．
    return false;
  }

  // AST の内容をライブラリに設定する．
  // ここではエラーは起こらないはず．
  //set_library(ast_library, this);

  return true;
}

END_NAMESPACE_YM_CLIB
