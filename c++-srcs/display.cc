﻿
/// @file display.cc
/// @brief ClibCellLibrary の内容をダンプする関数
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellLibrary.h"
#include "ym/ClibCell.h"
#include "ym/ClibIOMap.h"
#include "ym/ClibLut.h"
#include "ym/ClibLutTemplate.h"
#include "ym/ClibPin.h"
#include "ym/ClibTiming.h"
#include "ym/ClibCellClass.h"
#include "ym/ClibCellGroup.h"
#include "ym/ClibPatGraph.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibTime.h"

#include "ym/Expr.h"
#include "ym/ExprWriter.h"
#include "ym/NpnMapM.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM

// @brief ストリーム出力演算子
ostream&
operator<<(
  ostream& s,
  ClibDelayModel delay_model
)
{
  switch ( delay_model ) {
  case ClibDelayModel::generic_cmos:   s << "generic_cmos"; break;
  case ClibDelayModel::table_lookup:   s << "table_lookup"; break;
  case ClibDelayModel::piecewise_cmos: s << "piecewise_cmos"; break;
  case ClibDelayModel::cmos2:          s << "cmos2"; break;
  case ClibDelayModel::dcm:            s << "dcm"; break;
  case ClibDelayModel::polynomial:     s << "polynomial"; break;
  default: ASSERT_NOT_REACHED;
  }
  return s;
}

// @brief ストリーム出力演算子
ostream&
operator<<(
  ostream& s,
  ClibTimingSense timing_sense
)
{
  switch ( timing_sense ) {
  case ClibTimingSense::positive_unate: s << "posi_unate"; break;
  case ClibTimingSense::negative_unate: s << "nega_unate"; break;
  case ClibTimingSense::non_unate:      s << "non_unate"; break;
  case ClibTimingSense::none:           s << "none"; break;
  default: ASSERT_NOT_REACHED;
  }
  return s;
}

// @brief ストリーム出力演算子
ostream&
operator<<(
  ostream& s,
  ClibTimingType timing_type
)
{
  switch ( timing_type ) {
  case ClibTimingType::combinational:            s << "combinational"; break;
  case ClibTimingType::combinational_rise:       s << "combinational_rise"; break;
  case ClibTimingType::combinational_fall:       s << "combinational_fall"; break;

  case ClibTimingType::three_state_enable:       s << "three_state_enable"; break;
  case ClibTimingType::three_state_disable:      s << "three_state_disable"; break;
  case ClibTimingType::three_state_enable_rise:  s << "three_state_enable_rise"; break;
  case ClibTimingType::three_state_enable_fall:  s << "three_state_enable_fall"; break;
  case ClibTimingType::three_state_disable_rise: s << "three_state_disable_rise"; break;
  case ClibTimingType::three_state_disable_fall: s << "three_state_disable_fall"; break;

  case ClibTimingType::rising_edge:              s << "rising_edge"; break;
  case ClibTimingType::falling_edge:             s << "falling_edge"; break;

  case ClibTimingType::preset:                   s << "preset"; break;
  case ClibTimingType::clear:                    s << "clear"; break;

  case ClibTimingType::hold_rising:              s << "hold_rising"; break;
  case ClibTimingType::hold_falling:             s << "hold_falling"; break;

  case ClibTimingType::setup_rising:             s << "setup_rising"; break;
  case ClibTimingType::setup_falling:            s << "setup_falling"; break;

  case ClibTimingType::recovery_rising:          s << "recover_rising"; break;
  case ClibTimingType::recovery_falling:         s << "recover_falling"; break;

  case ClibTimingType::skew_rising:              s << "skew_rising"; break;
  case ClibTimingType::skew_falling:             s << "skew_falling"; break;

  case ClibTimingType::removal_rising:           s << "removal_rising"; break;
  case ClibTimingType::removal_falling:          s << "removal_falling"; break;

  case ClibTimingType::non_seq_setup_rising:     s << "non_seq_setup_rising"; break;
  case ClibTimingType::non_seq_setup_falling:    s << "non_seq_setup_falling"; break;
  case ClibTimingType::non_seq_hold_rising:      s << "non_seq_hold_rising"; break;
  case ClibTimingType::non_seq_hold_falling:     s << "non_seq_hold_falling"; break;

  case ClibTimingType::nochange_high_high:       s << "nochange_high_high"; break;
  case ClibTimingType::nochange_high_low:        s << "nochange_high_low"; break;
  case ClibTimingType::nochange_low_high:        s << "nochange_low_high"; break;
  case ClibTimingType::nochange_low_low:         s << "nochange_low_low"; break;

  default: ASSERT_NOT_REACHED;
  }
  return s;
}

// @brief ストリーム出力演算子
ostream&
operator<<(
  ostream& s,
  ClibVarType var_type
)
{
  switch ( var_type ) {
  case ClibVarType::input_net_transition:
    s << "input_net_transition";
    break;

  case ClibVarType::total_output_net_capacitance:
    s << "total_output_net_capacitance";
    break;

  case ClibVarType::output_net_length:
    s << "output_net_length";
    break;

  case ClibVarType::output_net_wire_cap:
    s << "output_net_wire_cap";
    break;

  case ClibVarType::output_net_pin_cap:
    s << "output_net_pin_cap";
    break;

  case ClibVarType::related_out_total_output_net_capacitance:
    s << "related_out_total_output_net_capacitance";
    break;

  case ClibVarType::related_out_output_net_length:
    s << "related_out_output_net_length";
    break;

  case ClibVarType::related_out_output_net_wire_cap:
    s << "related_out_output_net_wire_cap";
    break;

  case ClibVarType::related_out_output_net_pin_cap:
    s << "related_out_output_net_pin_cap";
    break;

  case ClibVarType::constrained_pin_transition:
    s << "constrained_pin_transition";
    break;

  case ClibVarType::related_pin_transition:
    s << "related_pin_transition";
    break;

  case ClibVarType::none:
    s << "none";
    break;

  default:
    ASSERT_NOT_REACHED;
  }
  return s;
}

// @brief ClibCPV のストリーム出力演算子
// @return s を返す．
ostream&
operator<<(
  ostream& s,  ///< [in] 出力先のストリーム
  ClibCPV cpv  ///< [in] clear_preset_var の値
)
{
  switch ( cpv ) {
  case ClibCPV::L: s << "L"; break;
  case ClibCPV::H: s << "H"; break;
  case ClibCPV::N: s << "N"; break;
  case ClibCPV::T: s << "T"; break;
  case ClibCPV::X: s << "X"; break;
  default:         s << "-"; break;
  }
  return s;
}

END_NAMESPACE_YM


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// LUT の情報を出力する．
void
display_lut(
  ostream& s,
  const char* label,
  const ClibLut& lut
)
{
  int d = lut.dimension();
  if ( d == 0 ) {
    return;
  }

  s << "    " << label << endl;
  for ( auto i: Range(d) ) {
    s << "      Variable_" << (i + 1) << " = " << lut.variable_type(i) << endl;
  }
  for ( auto i: Range(d) ) {
    s << "      Index_" << (i + 1) << "    = ";
    auto n = lut.index_num(i);
    const char* comma = "";
    s << "(";
    for ( auto j: Range(n) ) {
      s << comma << lut.index(i, j);
      comma = ", ";
    }
    s << ")" << endl;
  }

  if ( d == 1) {
    s << "      Values = (";
    auto n1 = lut.index_num(0);
    vector<SizeType> pos_array(1);
    const char* comma = "";
    for ( auto i1: Range(n1) ) {
      pos_array[0] = i1;
      s << comma << lut.grid_value(pos_array);
      comma = ", ";
    }
    s << ")" << endl;
  }
  else if ( d == 2 ) {
    s << "      Values = (" << endl;
    auto n1 = lut.index_num(0);
    auto n2 = lut.index_num(1);
    vector<SizeType> pos_array(2);
    for ( auto i1: Range(n1) ) {
      s << "                (";
      pos_array[0] = i1;
      const char* comma = "";
      for ( auto i2: Range(n2) ) {
	pos_array[1] = i2;
	s << comma << lut.grid_value(pos_array);
	comma = ", ";
      }
      s << ")" << endl;
    }
    s << "               )" << endl;
  }
  else if ( d == 3 ) {
    s << "      Values = (" << endl;
    auto n1 = lut.index_num(0);
    auto n2 = lut.index_num(1);
    auto n3 = lut.index_num(2);
    vector<SizeType> pos_array(3);
    for ( auto i1: Range(n1) ) {
      s << "                (";
      pos_array[0] = i1;
      const char* comma2 = "";
      for ( auto i2: Range(n2) ) {
	pos_array[1] = i2;
	s << comma2 << "(";
	const char* comma3 = "";
	for ( auto i3: Range(n3) ) {
	  pos_array[2] = i3;
	  s << comma3 << lut.grid_value(pos_array);
	  comma3 = ", ";
	}
	s << ")";
	comma2 = ", ";
      }
      s << ")" << endl;
    }
    s << "                )" << endl;
  }
}

// タイミング情報を出力する．
void
display_timing(
  ostream& s,
  const ClibCell& cell,
  SizeType ipos,
  SizeType opos,
  ClibTimingSense sense,
  ClibDelayModel delay_model
)
{
  for ( auto id: cell.timing_id_list(ipos, opos, sense) ) {
    auto& timing = cell.timing(id);
    s << "  Timing:" << endl
      << "    Type             = " << timing.type() << endl
      << "    Input Pin        = " << cell.input(ipos).name() << endl
      << "    Output Pin       = " << cell.output(opos).name() << endl
      << "    Sense            = ";
    if ( sense == ClibTimingSense::positive_unate ) {
      s << "positive unate";
    }
    else if ( sense == ClibTimingSense::negative_unate ) {
      s << "negative unate";
    }
    else {
      ASSERT_NOT_REACHED;
    }
    s << endl;
    if ( !timing.timing_cond().is_one() ) {
      s << "    When             = " << timing.timing_cond() << endl;
    }

    switch ( delay_model ) {
    case ClibDelayModel::generic_cmos:
      s << "    Rise Intrinsic   = " << timing.intrinsic_rise() << endl
	<< "    Rise Resistance  = " << timing.rise_resistance() << endl
	<< "    Fall Intrinsic   = " << timing.intrinsic_fall() << endl
	<< "    Fall Resistance  = " << timing.fall_resistance() << endl;
      break;

    case ClibDelayModel::table_lookup:
      display_lut(s, "Cell Rise", timing.cell_rise());
      display_lut(s, "Rise Transition", timing.rise_transition());
      display_lut(s, "Rise Propagation", timing.rise_propagation());

      display_lut(s, "Cell Fall", timing.cell_fall());
      display_lut(s, "Fall Transition", timing.fall_transition());
      display_lut(s, "Fall Propagation", timing.fall_propagation());
      break;

    case ClibDelayModel::piecewise_cmos:
      break;

    case ClibDelayModel::cmos2:
      break;

    case ClibDelayModel::dcm:
      break;

    case ClibDelayModel::polynomial:
      break;

    case ClibDelayModel::none:
      break;
    }
  }
}

// セルクラスの情報を出力する．
void
display_class(
  ostream& s,
  const char* title,
  const ClibCellClass& cclass
)
{
  s << title << endl;
  auto n = cclass.idmap_num();
  if ( n > 0 ) {
    s << "  Idmap List = " << endl;
    for ( auto& idmap: cclass.idmap_list() ) {
      s << idmap << endl;
    }
    s << endl;
  }
  for ( auto& group: cclass.cell_group_list() ) {
    s << "  Group: Map = " << group.iomap() << endl
      << "         Cell = ";
    for ( auto& cell: group.cell_list() ) {
      s << " " << cell.name();
    }
    s << endl;
  }
  s << endl;
}

void
display_CPV(
  ostream& s,
  const char* title,
  ClibCPV cpv)
{
  s << title << " = " << cpv;
}

// FFセルクラスの情報を出力する．
void
display_ff_class(
  ostream& s,
  const char* title,
  const ClibCellClass& cclass
)
{
  s << title << endl;
  auto n = cclass.idmap_num();
  if ( n > 0 ) {
    s << "  Idmap List = " << endl;
    for ( auto& idmap: cclass.idmap_list() ) {
      s << idmap << endl;
    }
    s << endl;
  }
  for ( auto& group: cclass.cell_group_list() ) {
    s << "  Group:";
#if 0
    s << " clock = " << group.clock_expr();
    if ( group.type() == ClibCellType::FF_M ) {
      s << " clock2 = " << group.clock2_expr();
    }
    s << " next_state = " << group.next_state_expr();
    if ( group.has_clear() ) {
      s << " clear = " << group.clear_expr();
    }
    if ( group.has_preset() ) {
      s << " preset = " << group.preset_expr();
    }
    if ( group.has_clear() && group.has_preset() ) {
      s << "clear_preset_var1 = " << group.clear_preset_var1();
      s << "clear_preset_var2 = " << group.clear_preset_var2();
    }
    s << endl;
#endif
    s << "         Cell = ";
    for ( auto& cell: group.cell_list() ) {
      s << " " << cell.name();
    }
    s << endl;
  }
  s << endl;
}

// ラッチセルクラスの情報を出力する．
void
display_latch_class(
  ostream& s,
  const char* title,
  const ClibCellClass& cclass
)
{
  s << title << endl;
  int n = cclass.idmap_num();
  if ( n > 0 ) {
    s << "  Idmap List = " << endl;
    for ( auto& idmap: cclass.idmap_list() ) {
      s << idmap << endl;
    }
    s << endl;
  }
  for ( auto& group: cclass.cell_group_list() ) {
    s << "  Group:";
#if 0
    s << " enable = " << group.enable_expr();
    if ( group.type() == ClibCellType::Latch_M ) {
      s << " enable2 = " << group.enable2_expr();
    }
    s << " data_in = " << group.data_in_expr();
    if ( group.has_clear() ) {
      s << " clear = " << group.clear_expr();
    }
    if ( group.has_preset() ) {
      s << " preset = " << group.preset_expr();
    }
    if ( group.has_clear() && group.has_preset() ) {
      display_CPV(s, "clear_preset_var1", group.clear_preset_var1());
      display_CPV(s, "clear_preset_var2", group.clear_preset_var2());
    }
    s << endl;
#endif
    s << "         Cell = ";
    for ( auto& cell: group.cell_list() ) {
      s << " " << cell.name();
    }
    s << endl;
  }
  s << endl;
}

// セルグループの情報を出力する．
void
display_group(
  ostream& s,
  const char* title,
  const ClibCellGroup& group
)
{
  s << title << endl
    << "  Cell =";
  for ( auto& cell: group.cell_list() ) {
    s << " " << cell.name();
  }
  s << endl
    << endl;
}

void
display_index(
  ostream& s,
  const ClibLutTemplate& templ,
  SizeType var
)
{
  auto n = templ.index_num(var);
  s << "(";
  const char* comma = "";
  for ( auto i: Range(n) ) {
    s << comma << templ.index(var, i);
    comma = ", ";
  }
  s << ")";
}

void
display_cell(
  ostream& s,
  const ClibCell& cell,
  ClibDelayModel delay_model
)
{
  // セル名とセルの種類を出力
  s << "Clib#" << cell.id() << " (" << cell.name() << ") : ";
  if ( cell.is_logic() ) {
    s << "Combinational Logic";
  }
  else if ( cell.is_ff() ) {
    s << "Flip-Flop";
  }
  else if ( cell.is_latch() ) {
    s << "Latch";
  }
  else if ( cell.type() == ClibCellType::FSM ) {
    s << "FSM";
  }
  else {
    ASSERT_NOT_REACHED;
  }
  s << endl;

  // 面積
  s << "  area = " << cell.area() << endl;

  // 論理式の出力用にピン名の辞書を作る．
  unordered_map<VarId, string> var_names;
  for ( auto i: Range(cell.pin_num()) ) {
    auto& pin = cell.pin(i);
    if ( pin.is_input() || pin.is_inout() ) {
      var_names.emplace(VarId{pin.input_id()}, pin.name());
    }
  }
  ExprWriter ewriter;

  if ( cell.is_ff() ) {
    // FF の情報
    var_names.emplace(VarId{cell.input_num2()}, cell.qvar1());
    s << "  Next State         = "
      << ewriter.dump_to_string(cell.next_state_expr(), var_names)
      << endl
      << "  Clock              = "
      << ewriter.dump_to_string(cell.clock_expr(), var_names)
      << endl;
    if ( cell.clock2_expr().is_valid() ) {
      s << "  Clock2             = "
	<< ewriter.dump_to_string(cell.clock2_expr(), var_names)
	<< endl;
    }
    if ( cell.has_clear() ) {
      s << "  Clear              = "
	<< ewriter.dump_to_string(cell.clear_expr(), var_names)
	<< endl;
    }
    if ( cell.has_preset() ) {
      s << "  Preset             = "
	<< ewriter.dump_to_string(cell.preset_expr(), var_names)
	<< endl;
    }
    if ( cell.has_clear() && cell.has_preset() ) {
      s << "  Clear Preset Var1  = " << cell.clear_preset_var1() << endl
	<< "  Clear Preset Var2  = " << cell.clear_preset_var2() << endl;
    }
  }
  if ( cell.is_latch() ) {
    // ラッチの情報
    var_names.emplace(VarId{cell.input_num2()}, cell.qvar1());
    s << "  Data In            = "
      << ewriter.dump_to_string(cell.data_in_expr(), var_names)
      << endl
      << "  Enable             = "
      << ewriter.dump_to_string(cell.enable_expr(), var_names)
      << endl;
    if ( !cell.enable2_expr().is_zero() ) {
      s << "  Enable2            = "
	<< ewriter.dump_to_string(cell.enable2_expr(), var_names)
	<< endl;
    }
    if ( cell.has_clear() ) {
      s << "  Clear              = "
	<< ewriter.dump_to_string(cell.clear_expr(), var_names)
	<< endl;
    }
    if ( cell.has_preset() ) {
      s << "  Preset             = "
	<< ewriter.dump_to_string(cell.preset_expr(), var_names)
	<< endl;
    }
    if ( cell.has_clear() && cell.has_preset() ) {
      s << "  Clear Preset Var1  = " << cell.clear_preset_var1() << endl
	<< "  Clear Preset Var2  = " << cell.clear_preset_var2() << endl;
    }
  }

  // ピンの情報
  for ( auto i: Range(cell.pin_num()) ) {
    auto& pin = cell.pin(i);
    s << "  Pin#" << i << "[ " << pin.name() << " ]: ";
    if ( pin.is_input() ) {
      // 入力ピン
      s << "Input#" << pin.input_id() << endl
	<< "    Capacitance      = " << pin.capacitance() << endl
	<< "    Rise Capacitance = " << pin.rise_capacitance() << endl
	<< "    Fall Capacitance = " << pin.fall_capacitance() << endl;
    }
    else if ( pin.is_output() ) {
      // 出力ピン
      auto opos = pin.output_id();
      s << "Output# " << opos << endl;
      if ( cell.has_logic(opos) ) {
	s << "    Logic            = "
	  << ewriter.dump_to_string(cell.logic_expr(opos), var_names)
	  << endl;
	if ( cell.has_tristate(opos) ) {
	  s << "    Tristate         = "
	    << ewriter.dump_to_string(cell.tristate_expr(opos), var_names)
	    << endl;
	}
      }
      s << "    Max Fanout       = " << pin.max_fanout() << endl
	<< "    Min Fanout       = " << pin.min_fanout() << endl
	<< "    Max Capacitance  = " << pin.max_capacitance() << endl
	<< "    Min Capacitance  = " << pin.min_capacitance() << endl
	<< "    Max Transition   = " << pin.max_transition() << endl
	<< "    Min Transition   = " << pin.min_transition() << endl;
    }
    else if ( pin.is_inout() ) {
      // 入出力ピン
      auto opos = pin.output_id();
      s << "Inout#(" << pin.input_id() << ", " << opos << ")" << endl;
      if ( cell.has_logic(opos) ) {
	s << "    Logic            = "
	  << ewriter.dump_to_string(cell.logic_expr(opos), var_names)
	  << endl;
	if ( cell.has_tristate(opos) ) {
	  s << "    Tristate         = "
	    << ewriter.dump_to_string(cell.tristate_expr(opos), var_names)
	    << endl;
	}
      }
      s << "    Capacitance      = " << pin.capacitance() << endl
	<< "    Rise Capacitance = " << pin.rise_capacitance() << endl
	<< "    Fall Capacitance = " << pin.fall_capacitance() << endl
	<< "    Max Fanout       = " << pin.max_fanout() << endl
	<< "    Min Fanout       = " << pin.min_fanout() << endl
	<< "    Max Capacitance  = " << pin.max_capacitance() << endl
	<< "    Min Capacitance  = " << pin.min_capacitance() << endl
	<< "    Max Transition   = " << pin.max_transition() << endl
	<< "    Min Transition   = " << pin.min_transition() << endl;
    }
    else if ( pin.is_internal() ) {
      // 内部ピン
      auto itpos = pin.internal_id();
      s << "Internal#(" << itpos << ")" << endl;
    }
  }

  // タイミング情報
  auto ni2 = cell.input_num2();
  auto no2 = cell.output_num2();
  for ( auto ipos: Range(ni2) ) {
    for ( auto opos: Range(no2) ) {
      display_timing(s, cell, ipos, opos, ClibTimingSense::positive_unate, delay_model);
      display_timing(s, cell, ipos, opos, ClibTimingSense::negative_unate, delay_model);
    }
  }
  s << endl;
}

END_NONAMESPACE

void
display_library(
  ostream& s,
  const ClibCellLibrary& library
)
{
  // ライブラリ名
  s << "Library(" << library.name() << ")" << endl;

  // テクノロジ
  s << "  technology: ";
  switch ( library.technology() ) {
  case ClibTechnology::cmos: s << "cmos"; break;
  case ClibTechnology::fpga: s << "fpga"; break;
  default: ASSERT_NOT_REACHED; break;
  }
  s << endl;

  // 遅延モデル
  ClibDelayModel delay_model = library.delay_model();
  s << "  delay_model: " << delay_model << endl;

  // バス命名規則
  s << "  bus_naming_style: " << library.bus_naming_style() << endl;

  // 日付
  s << "  date: " << library.date() << endl;

  // リビジョン
  s << "  revision: " << library.revision() << endl;

  // コメント
  s << "  comment: " << library.comment() << endl;

  // 時間単位
  s << "  time_unit: " << library.time_unit() << endl;

  // 電圧単位
  s << "  voltage_unit: " << library.voltage_unit() << endl;

  // 電流単位
  s << "  current_unit: " << library.current_unit() << endl;

  // 抵抗単位
  s << "  pulling_resistance_unit: " << library.pulling_resistance_unit() << endl;

  // 容量単位
  s << "  capacitive_load_unit: " << library.capacitive_load_unit()
    << library.capacitive_load_unit_str() << endl;

  // 電力単位
  s << "  leakage_power_unit: " << library.leakage_power_unit() << endl;

  s << endl;

  // lu_table_template
  for ( auto id: Range(library.lu_table_template_num()) ) {
    auto& templ = library.lu_table_template(id);
    s << "  lu_table_template(" << templ.name() << ")" << endl;
    auto d = templ.dimension();
    for ( auto j: Range(d) ) {
      s << "    variable_" << (j + 1) << ": " << templ.variable_type(j) << endl;
    }
    for ( auto j: Range(d) ) {
      s << "    index_" << (j + 1) << "   : ";
      display_index(s, templ, j);
      s << endl;
    }
    s << endl;
  }

  s << endl;

  // セル
  for ( auto& cell: library.cell_list() ) {
    display_cell(s, cell, delay_model);
  }

  // セルクラスの情報
  s << "Cell Class" << endl;
  for ( auto class_id: Range(library.npn_class_num()) ) {
    ostringstream buf;
    buf << "Class#" << class_id;
    auto& cclass = library.npn_class(class_id);
    display_class(s, buf.str().c_str(), cclass);
  }

  // 既定セルグループの情報
  display_group(s, "Const0 Group", library.const0_func());
  display_group(s, "Const1 Group", library.const1_func());
  display_group(s, "Buffer Group", library.buf_func());
  display_group(s, "Inverter Group", library.inv_func());

  display_ff_class(s, "DFF Class", library.simple_ff_class(false, false, false));
  display_ff_class(s, "DFF_R Class", library.simple_ff_class(false, true, false));
  display_ff_class(s, "DFF_S Class", library.simple_ff_class(false, false, true));
  display_ff_class(s, "DFF_RS Class", library.simple_ff_class(false, true, true));

  display_latch_class(s, "Latch Class", library.simple_latch_class(false, false, false));
  display_latch_class(s, "Latch_R Class", library.simple_latch_class(false, true, false));
  display_latch_class(s, "Latch_S Class", library.simple_latch_class(false, false, true));
  display_latch_class(s, "Latch_RS Class", library.simple_latch_class(false, true, true));

#if 1
  // パタングラフの情報
  s << "==== PatMgr dump start ====" << endl;

  // ノードの種類の出力
  auto nn = library.pg_node_num();
  for ( auto i: Range(nn) ) {
    s << "Node#" << i << ": ";
    switch ( library.pg_node_type(i) ) {
    case ClibPatType::Input: s << "INPUT#" << library.pg_input_id(i) ; break;
    case ClibPatType::And:   s << "AND"; break;
    case ClibPatType::Xor:   s << "XOR"; break;
    default: ASSERT_NOT_REACHED;
    }
    s << endl;
  }
  s << endl;

  // 枝の情報の出力
  auto ne = library.pg_edge_num();
  for ( auto i: Range(ne) ) {
    s << "Edge#" << i << ": " << library.pg_edge_from(i)
      << " -> " << library.pg_edge_to(i)
      << "(" << library.pg_edge_pos(i) << ")";
    if ( library.pg_edge_inv(i) ) {
      s << " ***";
    }
    s << endl;
  }
  s << endl;

  // パタングラフの情報の出力
  auto np = library.pg_pat_num();
  for ( auto i: Range(np) ) {
    const ClibPatGraph& pat = library.pg_pat(i);
    s << "Pat#" << i << ": "
      << "Rep#" << pat.rep_id() << ": ";
    if ( pat.root_inv() ) {
      s << "[inv]";
    }
    s << "(" << pat.input_num() << "), ";
    auto n = pat.edge_num();
    for ( auto i: Range(n) ) {
      s << " " << pat.edge(i);
    }
    s << endl;
  }

  s << "==== PatMgr dump end ====" << endl;
#endif

}

END_NAMESPACE_YM_CLIB