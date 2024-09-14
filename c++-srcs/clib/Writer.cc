
/// @file Writer.cc
/// @brief Writer の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "Writer.h"
#include "ym/ClibCellLibrary.h"
#include "ym/ClibCell.h"
#include "ym/ClibIOMap.h"
#include "ym/ClibLut.h"
#include "ym/ClibPin.h"
#include "ym/ClibTiming.h"
#include "ym/ClibCellClass.h"
#include "ym/ClibCellGroup.h"
#include "ym/ClibPatGraph.h"
#include "ym/ClibSeqAttr.h"
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

// @brief コンストラクタ
Writer::Writer(
  ostream& s,
  const ClibCellLibrary& library
) : mS{s},
    mLibrary{library}
{
  { // セルクラスの登録
    SizeType id = 0;
    for ( auto cclass: mLibrary.npn_class_list() ) {
      auto key = cclass.key();
      mClassDict.emplace(key, id);
      ++ id;
    }
  }
  { // セルグループの登録
    SizeType id = 0;
    for ( auto cgroup: mLibrary.cell_group_list() ) {
      auto key = cgroup.key();
      mGroupDict.emplace(key, id);
      ++ id;
    }
  }
  { // セルの登録
    SizeType id = 0;
    for ( auto cell: mLibrary.cell_list() ) {
      auto key = cell.key();
      mCellDict.emplace(key, id);
      ++ id;
    }
  }

  // 既定のセルグループ名の登録
  reg_group_name("Const0",   mLibrary.const0_func());
  reg_group_name("Const1",   mLibrary.const1_func());
  reg_group_name("Buffer",   mLibrary.buf_func());
  reg_group_name("Inverter", mLibrary.inv_func());
  reg_group_name("And2",     mLibrary.and_func(2));
  reg_group_name("And3",     mLibrary.and_func(3));
  reg_group_name("And4",     mLibrary.and_func(4));
  reg_group_name("Nand2",    mLibrary.nand_func(2));
  reg_group_name("Nand3",    mLibrary.nand_func(3));
  reg_group_name("Nand4",    mLibrary.nand_func(4));
  reg_group_name("Or2",      mLibrary.or_func(2));
  reg_group_name("Or3",      mLibrary.or_func(3));
  reg_group_name("Or4",      mLibrary.or_func(4));
  reg_group_name("Nor2",     mLibrary.nor_func(2));
  reg_group_name("Nor3",     mLibrary.nor_func(3));
  reg_group_name("Nor4",     mLibrary.nor_func(4));
  reg_group_name("Xor2",     mLibrary.xor_func(2));
  reg_group_name("Xor3",     mLibrary.xor_func(3));
  reg_group_name("Xor4",     mLibrary.xor_func(4));
  reg_group_name("Xnor2",    mLibrary.xnor_func(2));
  reg_group_name("Xnor3",    mLibrary.xnor_func(3));
  reg_group_name("Xnor4",    mLibrary.xnor_func(4));
  reg_group_name("Mux2",     mLibrary.mux2_func());
  reg_group_name("Mux4",     mLibrary.mux4_func());

  // 既定のセルクラス名の登録
  reg_class_name("Const",    mLibrary.const0_func());
  reg_class_name("Buffer",   mLibrary.buf_func());
  reg_class_name("And2",     mLibrary.and_func(2));
  reg_class_name("And3",     mLibrary.and_func(3));
  reg_class_name("And4",     mLibrary.and_func(4));
  reg_class_name("Xor2",     mLibrary.xor_func(2));
  reg_class_name("Xor3",     mLibrary.xor_func(3));
  reg_class_name("Xor4",     mLibrary.xor_func(4));
  reg_class_name("Mux2",     mLibrary.mux2_func());
  reg_class_name("Mux4",     mLibrary.mux4_func());
  reg_dff_class();
  reg_latch_class();
}

// @brief セルライブラリの内容を出力する．
void
Writer::run()
{
  // ライブラリ名
  mS << "Library(" << mLibrary.name() << ")" << endl;

  // テクノロジ
  mS << "  technology: ";
  switch ( mLibrary.technology() ) {
  case ClibTechnology::cmos: mS << "cmos"; break;
  case ClibTechnology::fpga: mS << "fpga"; break;
  default: ASSERT_NOT_REACHED; break;
  }
  mS << endl;

  // 遅延モデル
  mS << "  delay_model: "
     << mLibrary.delay_model() << endl;

  // バス命名規則
  mS << "  bus_naming_style: "
     << mLibrary.bus_naming_style() << endl;

  // 日付
  mS << "  date: "
     << mLibrary.date() << endl;

  // リビジョン
  mS << "  revision: "
     << mLibrary.revision() << endl;

  // コメント
  mS << "  comment: "
     << mLibrary.comment() << endl;

  // 時間単位
  mS << "  time_unit: "
     << mLibrary.time_unit() << endl;

  // 電圧単位
  mS << "  voltage_unit: "
     << mLibrary.voltage_unit() << endl;

  // 電流単位
  mS << "  current_unit: "
     << mLibrary.current_unit() << endl;

  // 抵抗単位
  mS << "  pulling_resistance_unit: "
     << mLibrary.pulling_resistance_unit() << endl;

  // 容量単位
  mS << "  capacitive_load_unit: "
     << mLibrary.capacitive_load_unit()
     << mLibrary.capacitive_load_unit_str() << endl;

  // 電力単位
  mS << "  leakage_power_unit: "
     << mLibrary.leakage_power_unit() << endl;

  mS << endl;

  // セル
  for ( auto cell: mLibrary.cell_list() ) {
    display_cell(cell);
  }

  // セルグループ
  for ( auto cgroup: mLibrary.cell_group_list() ) {
    display_group(cgroup);
  }

  // セルクラス
  for ( auto cclass: mLibrary.npn_class_list() ) {
    display_class(cclass);
  }

  // パタングラフの情報
  mS << "==== PatMgr dump start ====" << endl;

  // ノードの種類の出力
  auto nn = mLibrary.pg_node_num();
  for ( auto i: Range(nn) ) {
    mS << "Node#" << i << ": ";
    switch ( mLibrary.pg_node_type(i) ) {
    case ClibPatType::Input:
      mS << "INPUT#"
	 << mLibrary.pg_input_id(i);
      break;
    case ClibPatType::And:
      mS << "AND";
      break;
    case ClibPatType::Xor:
      mS << "XOR";
      break;
    default:
      ASSERT_NOT_REACHED;
      break;
    }
    mS << endl;
  }
  mS << endl;

  // 枝の情報の出力
  auto ne = mLibrary.pg_edge_num();
  for ( auto i: Range(ne) ) {
    mS << "Edge#" << i << ": " << mLibrary.pg_edge_from(i)
       << " -> " << mLibrary.pg_edge_to(i)
       << "(" << mLibrary.pg_edge_pos(i) << ")";
    if ( mLibrary.pg_edge_inv(i) ) {
      mS << " ***";
    }
    mS << endl;
  }
  mS << endl;

  // パタングラフの情報の出力
  auto np = mLibrary.pg_pat_num();
  for ( auto i: Range(np) ) {
    const auto& pat = mLibrary.pg_pat(i);
    auto rep = pat.rep_class();
    auto rep_id = mClassDict.at(rep.key());
    mS << "Pat#" << i << ": "
      << "Rep#" << rep_id << ": ";
    if ( pat.root_inv() ) {
      mS << "[inv]";
    }
    mS << "(" << pat.input_num() << "), ";
    auto n = pat.edge_num();
    for ( auto i: Range(n) ) {
      mS << " " << pat.edge(i);
    }
    mS << endl;
  }

  mS << "==== PatMgr dump end ====" << endl;

}

// セルクラスの情報を出力する．
void
Writer::display_class(
  const ClibCellClass& cclass
)
{
  bool has_cell = false;
  for ( auto group: cclass.cell_group_list() ) {
    if ( group.cell_list().size() > 0 ) {
      has_cell = true;
      break;
    }
  }
  if ( !has_cell ) {
    // セルを持たないクラスはスキップする．
    return;
  }

  mS << "Class#"
     << mClassDict.at(cclass.key())
     << endl;
  if ( mClassNameDict.count(cclass.key()) > 0 ) {
    auto name = mClassNameDict.at(cclass.key());
    mS << "  Name = " << name
       << endl;
  }
  auto n = cclass.idmap_num();
  if ( n > 0 ) {
    mS << "  Idmap List:" << endl;
    for ( auto& idmap: cclass.idmap_list() ) {
      mS << "         " << idmap << endl;
    }
    mS << endl;
  }
  for ( auto group: cclass.cell_group_list() ) {
    if ( group.cell_list().size() == 0 ) {
      continue;
    }
    mS << "  Group#" << mGroupDict.at(group.key())
       << ": Map = " << group.iomap() << endl;
  }
  mS << endl;
}

// セルグループの情報を出力する．
void
Writer::display_group(
  const ClibCellGroup& group
)
{
  if ( group.cell_list().size() == 0 ) {
    // セルを持たないグループはスキップする．
    return;
  }

  mS << "Group#"
     << mGroupDict.at(group.key())
     << "(Class#"
     << mClassDict.at(group.rep_class().key())
     << ")" << endl;
  if ( mGroupNameDict.count(group.key()) > 0 ) {
    auto name = mGroupNameDict.at(group.key());
    mS << "  Name = " << name
       << endl;
  }
  mS << "  Cell =";
  for ( auto cell: group.cell_list() ) {
    mS << " " << cell.name();
  }
  mS << endl
     << endl;
}

void
Writer::display_cell(
  const ClibCell& cell
)
{
  // セル名とセルの種類を出力
  mS << cell.name() << ": Cell#"
     << mCellDict.at(cell.key())
     << "(Group#"
     << mGroupDict.at(cell.group().key())
     << ")" << endl
     << "  type = ";
  if ( cell.is_logic() ) {
    mS << "Combinational Logic";
  }
  else if ( cell.is_ff() ) {
    mS << "Flip-Flop";
  }
  else if ( cell.is_latch() ) {
    mS << "Latch";
  }
  else if ( cell.type() == ClibCellType::FSM ) {
    mS << "FSM";
  }
  else {
    ASSERT_NOT_REACHED;
  }
  mS << endl;

  // 面積
  mS << "  area = " << cell.area() << endl;

  // 論理式の出力用にピン名の辞書を作る．
  unordered_map<SizeType, string> var_names;
  for ( auto pin: cell.pin_list() ) {
    if ( pin.is_input() || pin.is_inout() ) {
      var_names.emplace(pin.input_id(), pin.name());
    }
  }
  ExprWriter ewriter;

  if ( cell.is_ff() ) {
    // FF の情報
    var_names.emplace(cell.input2_num(), cell.qvar1());
    mS << "  Next State         = "
       << ewriter.dump_to_string(cell.next_state_expr(), var_names)
       << endl
       << "  Clock              = "
       << ewriter.dump_to_string(cell.clock_expr(), var_names)
       << endl;
    if ( cell.clock2_expr().is_valid() ) {
      mS << "  Clock2             = "
	 << ewriter.dump_to_string(cell.clock2_expr(), var_names)
	 << endl;
    }
    if ( cell.has_clear() ) {
      mS << "  Clear              = "
	 << ewriter.dump_to_string(cell.clear_expr(), var_names)
	 << endl;
    }
    if ( cell.has_preset() ) {
      mS << "  Preset             = "
	 << ewriter.dump_to_string(cell.preset_expr(), var_names)
	 << endl;
    }
    if ( cell.has_clear() && cell.has_preset() ) {
      mS << "  Clear Preset Var1  = " << cell.clear_preset_var1() << endl
	 << "  Clear Preset Var2  = " << cell.clear_preset_var2() << endl;
    }
  }
  if ( cell.is_latch() ) {
    // ラッチの情報
    var_names.emplace(cell.input2_num(), cell.qvar1());
    mS << "  Data In            = "
       << ewriter.dump_to_string(cell.data_in_expr(), var_names)
       << endl
       << "  Enable             = "
       << ewriter.dump_to_string(cell.enable_expr(), var_names)
       << endl;
    if ( cell.enable2_expr().is_valid() ) {
      mS << "  Enable2            = "
	 << ewriter.dump_to_string(cell.enable2_expr(), var_names)
	 << endl;
    }
    if ( cell.has_clear() ) {
      mS << "  Clear              = "
	 << ewriter.dump_to_string(cell.clear_expr(), var_names)
	 << endl;
    }
    if ( cell.has_preset() ) {
      mS << "  Preset             = "
	 << ewriter.dump_to_string(cell.preset_expr(), var_names)
	 << endl;
    }
    if ( cell.has_clear() && cell.has_preset() ) {
      mS << "  Clear Preset Var1  = " << cell.clear_preset_var1() << endl
	 << "  Clear Preset Var2  = " << cell.clear_preset_var2() << endl;
    }
  }

  // ピンの情報
  for ( auto pin: cell.pin_list() ) {
    mS << "  Pin#" << pin.pin_id() << "[ " << pin.name() << " ]: ";
    if ( pin.is_input() ) {
      // 入力ピン
      mS << "Input#" << pin.input_id() << endl
	 << "    Capacitance      = " << pin.capacitance() << endl
	 << "    Rise Capacitance = " << pin.rise_capacitance() << endl
	 << "    Fall Capacitance = " << pin.fall_capacitance() << endl;
    }
    else if ( pin.is_output() ) {
      // 出力ピン
      auto opos = pin.output_id();
      mS << "Output# " << opos << endl;
      if ( cell.has_logic(opos) ) {
	mS << "    Logic            = "
	   << ewriter.dump_to_string(cell.logic_expr(opos), var_names)
	   << endl;
	if ( cell.has_tristate(opos) ) {
	  mS << "    Tristate         = "
	     << ewriter.dump_to_string(cell.tristate_expr(opos), var_names)
	     << endl;
	}
      }
      mS << "    Max Fanout       = " << pin.max_fanout() << endl
	 << "    Min Fanout       = " << pin.min_fanout() << endl
	 << "    Max Capacitance  = " << pin.max_capacitance() << endl
	 << "    Min Capacitance  = " << pin.min_capacitance() << endl
	 << "    Max Transition   = " << pin.max_transition() << endl
	 << "    Min Transition   = " << pin.min_transition() << endl;
    }
    else if ( pin.is_inout() ) {
      // 入出力ピン
      auto opos = pin.output_id();
      mS << "Inout#(" << pin.input_id()
	 << ", " << opos << ")" << endl;
      if ( cell.has_logic(opos) ) {
	mS << "    Logic            = "
	   << ewriter.dump_to_string(cell.logic_expr(opos), var_names)
	   << endl;
	if ( cell.has_tristate(opos) ) {
	  mS << "    Tristate         = "
	     << ewriter.dump_to_string(cell.tristate_expr(opos), var_names)
	     << endl;
	}
      }
      mS << "    Capacitance      = " << pin.capacitance() << endl
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
      auto ipos = pin.internal_id();
      mS << "Internal#(" << ipos << ")" << endl;
    }
  }

  // タイミング情報
  auto ni2 = cell.input2_num();
  auto no2 = cell.output2_num();
  for ( auto ipos: Range(ni2) ) {
    for ( auto opos: Range(no2) ) {
      display_timing(cell, ipos, opos, ClibTimingSense::positive_unate);
      display_timing(cell, ipos, opos, ClibTimingSense::negative_unate);
    }
  }
  mS << endl;
}

// タイミング情報を出力する．
void
Writer::display_timing(
  const ClibCell& cell,
  SizeType ipos,
  SizeType opos,
  ClibTimingSense sense
)
{
  for ( auto timing: cell.timing_list(ipos, opos, sense) ) {
    mS << "  Timing:" << endl
       << "    Type             = " << timing.type() << endl
       << "    Input Pin        = " << cell.input(ipos).name() << endl
       << "    Output Pin       = " << cell.output(opos).name() << endl
       << "    Sense            = ";
    if ( sense == ClibTimingSense::positive_unate ) {
      mS << "positive unate";
    }
    else if ( sense == ClibTimingSense::negative_unate ) {
      mS << "negative unate";
    }
    else {
      ASSERT_NOT_REACHED;
    }
    mS << endl;
    if ( !timing.timing_cond().is_one() ) {
      mS << "    When             = " << timing.timing_cond() << endl;
    }

    switch ( mLibrary.delay_model() ) {
    case ClibDelayModel::generic_cmos:
      mS << "    Rise Intrinsic   = " << timing.intrinsic_rise() << endl
	 << "    Rise Resistance  = " << timing.rise_resistance() << endl
	 << "    Fall Intrinsic   = " << timing.intrinsic_fall() << endl
	 << "    Fall Resistance  = " << timing.fall_resistance() << endl;
      break;

    case ClibDelayModel::table_lookup:
      display_lut("Cell Rise", timing.cell_rise());
      display_lut("Rise Transition", timing.rise_transition());
      display_lut("Rise Propagation", timing.rise_propagation());

      display_lut("Cell Fall", timing.cell_fall());
      display_lut("Fall Transition", timing.fall_transition());
      display_lut("Fall Propagation", timing.fall_propagation());
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

// LUT の情報を出力する．
void
Writer::display_lut(
  const string& label,
  const ClibLut& lut
)
{
  if ( lut.is_invalid() ) {
    return;
  }

  SizeType d = lut.dimension();
  mS << "    " << label << endl;
  for ( auto i: Range(d) ) {
    mS << "      Variable_" << (i + 1) << " = " << lut.variable_type(i) << endl;
  }
  for ( auto i: Range(d) ) {
    mS << "      Index_" << (i + 1) << "    = ";
    auto n = lut.index_num(i);
    const char* comma = "";
    mS << "(";
    for ( auto j: Range(n) ) {
      mS << comma << lut.index(i, j);
      comma = ", ";
    }
    mS << ")" << endl;
  }

  if ( d == 1) {
    mS << "      Values = (";
    auto n1 = lut.index_num(0);
    vector<SizeType> pos_array(1);
    const char* comma = "";
    for ( auto i1: Range(n1) ) {
      pos_array[0] = i1;
      mS << comma << lut.grid_value(pos_array);
      comma = ", ";
    }
    mS << ")" << endl;
  }
  else if ( d == 2 ) {
    mS << "      Values = (" << endl;
    auto n1 = lut.index_num(0);
    auto n2 = lut.index_num(1);
    vector<SizeType> pos_array(2);
    for ( auto i1: Range(n1) ) {
      mS << "                (";
      pos_array[0] = i1;
      const char* comma = "";
      for ( auto i2: Range(n2) ) {
	pos_array[1] = i2;
	mS << comma << lut.grid_value(pos_array);
	comma = ", ";
      }
      mS << ")" << endl;
    }
    mS << "               )" << endl;
  }
  else if ( d == 3 ) {
    mS << "      Values = (" << endl;
    auto n1 = lut.index_num(0);
    auto n2 = lut.index_num(1);
    auto n3 = lut.index_num(2);
    vector<SizeType> pos_array(3);
    for ( auto i1: Range(n1) ) {
      mS << "                (";
      pos_array[0] = i1;
      const char* comma2 = "";
      for ( auto i2: Range(n2) ) {
	pos_array[1] = i2;
	mS << comma2 << "(";
	const char* comma3 = "";
	for ( auto i3: Range(n3) ) {
	  pos_array[2] = i3;
	  mS << comma3 << lut.grid_value(pos_array);
	  comma3 = ", ";
	}
	mS << ")";
	comma2 = ", ";
      }
      mS << ")" << endl;
    }
    mS << "                )" << endl;
  }
}

// @brief DFF のセルクラスに名前をつける．
void
Writer::reg_dff_class()
{
  for ( SizeType index = 0; index < ClibSeqAttr::max_index(); ++ index ) {
    ClibSeqAttr seq_attr{index};
    auto class_list = mLibrary.find_ff_class(seq_attr);
    ostringstream buf;
    buf << "DFF";
    if ( seq_attr.has_slave_clock() ) {
      buf << "2";
    }
    if ( seq_attr.has_clear() ) {
      if ( seq_attr.has_preset() ) {
	auto cpv1 = seq_attr.cpv1();
	auto cpv2 = seq_attr.cpv2();
	buf << "_RS" << cpv1 << cpv2;
      }
      else {
	buf << "_R";
      }
    }
    else if ( seq_attr.has_preset() ) {
      buf << "_S";
    }
    auto name = buf.str();
    for ( auto cclass: class_list ) {
      mClassNameDict.emplace(cclass.key(), name);
    }
  }
}

// @brief ラッチのセルクラスに名前をつける．
void
Writer::reg_latch_class()
{
  for ( SizeType index = 0; index < ClibSeqAttr::max_index(); ++ index ) {
    ClibSeqAttr seq_attr{index};
    auto class_list = mLibrary.find_latch_class(seq_attr);
    ostringstream buf;
    buf << "Latch";
    if ( seq_attr.has_slave_clock() ) {
      buf << "2";
    }
    if ( seq_attr.has_clear() ) {
      if ( seq_attr.has_preset() ) {
	auto cpv1 = seq_attr.cpv1();
	auto cpv2 = seq_attr.cpv2();
	buf << "_RS" << cpv1 << cpv2;
      }
      else {
	buf << "_R";
      }
    }
    else if ( seq_attr.has_preset() ) {
      buf << "_S";
    }
    auto name = buf.str();
    for ( auto cclass: class_list ) {
      mClassNameDict.emplace(cclass.key(), name);
    }
  }
}

// @brief セルグループ名を登録する．
void
Writer::reg_group_name(
  const string& name,
  const ClibCellGroup& cgroup
)
{
  mGroupNameDict.emplace(cgroup.key(), name);
}

// @brief セルクラス名を登録する．
void
Writer::reg_class_name(
  const string& name,
  const ClibCellGroup& cgroup
)
{
  auto cclass = cgroup.rep_class();
  mClassNameDict.emplace(cclass.key(), name);
}

END_NAMESPACE_YM_CLIB
