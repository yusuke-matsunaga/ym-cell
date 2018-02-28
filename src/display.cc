
/// @file display.cc
/// @brief ClibCellLibrary の内容をダンプする関数
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellLibrary.h"
#include "ym/ClibCell.h"
#include "ym/ClibCellList.h"
#include "ym/ClibLut.h"
#include "ym/ClibLutTemplate.h"
#include "ym/ClibCellPin.h"
#include "ym/ClibTiming.h"
#include "ym/ClibTimingList.h"
#include "ym/ClibCellClass.h"
#include "ym/ClibCellClassList.h"
#include "ym/ClibCellGroup.h"
#include "ym/ClibCellGroupList.h"
#include "ym/ClibPatGraph.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibTime.h"

#include "ym/Expr.h"
#include "ym/NpnMapM.h"


BEGIN_NAMESPACE_YM

// @brief ストリーム出力演算子
// @param[in] s 出力先のストリーム
// @param[in] delay_mode 遅延モード
// @return s を返す．
ostream&
operator<<(ostream& s,
	   ClibDelayModel delay_model)
{
  switch ( delay_model ) {
  case kClibDelayGenericCmos:   s << "generic_cmos"; break;
  case kClibDelayTableLookup:   s << "table_lookup"; break;
  case kClibDelayPiecewiseCmos: s << "piecewise_cmos"; break;
  case kClibDelayCmos2:         s << "cmos2"; break;
  case kClibDelayDcm:           s << "dcm"; break;
  default: ASSERT_NOT_REACHED;
  }
  return s;
}

// @brief ストリーム出力演算子
// @param[in] s 出力先のストリーム
// @param[in] timing_sense タイミングセンス
// @return s を返す．
ostream&
operator<<(ostream& s,
	   ClibTimingSense timing_sense)
{
  switch ( timing_sense ) {
  case kClibPosiUnate: s << "posi_unate"; break;
  case kClibNegaUnate: s << "nega_unate"; break;
  case kClibNonUnate:  s << "non_unate"; break;
  default: ASSERT_NOT_REACHED;
  }
  return s;
}

// @brief ストリーム出力演算子
// @param[in] s 出力先のストリーム
// @param[in] timing_type タイミング条件
// @return s を返す．
ostream&
operator<<(ostream& s,
	   ClibTimingType timing_type)
{
  switch ( timing_type ) {
  case kClibTimingCombinational:         s << "combinational"; break;
  case kClibTimingCombinationalRise:     s << "combinational_rise"; break;
  case kClibTimingCombinationalFall:     s << "combinational_fall"; break;

  case kClibTimingThreeStateEnable:      s << "three_state_enable"; break;
  case kClibTimingThreeStateDisable:     s << "three_state_disable"; break;
  case kClibTimingThreeStateEnableRise:  s << "three_state_enable_rise"; break;
  case kClibTimingThreeStateEnableFall:  s << "three_state_enable_fall"; break;
  case kClibTimingThreeStateDisableRise: s << "three_state_disable_rise"; break;
  case kClibTimingThreeStateDisableFall: s << "three_state_disable_fall"; break;

  case kClibTimingRisingEdge:            s << "rising_edge"; break;
  case kClibTimingFallingEdge:           s << "falling_edge"; break;

  case kClibTimingPreset:                s << "preset"; break;
  case kClibTimingClear:                 s << "clear"; break;

  case kClibTimingHoldRising:            s << "hold_rising"; break;
  case kClibTimingHoldFalling:           s << "hold_falling"; break;

  case kClibTimingSetupRising:           s << "setup_rising"; break;
  case kClibTimingSetupFalling:          s << "setup_falling"; break;

  case kClibTimingRecoveryRising:        s << "recover_rising"; break;
  case kClibTimingRecoveryFalling:       s << "recover_falling"; break;

  case kClibTimingSkewRising:            s << "skew_rising"; break;
  case kClibTimingSkewFalling:           s << "skew_falling"; break;

  case kClibTimingRemovalRising:         s << "removal_rising"; break;
  case kClibTimingRemovalFalling:        s << "removal_falling"; break;

  case kClibTimingNonSeqSetupRising:     s << "non_seq_setup_rising"; break;
  case kClibTimingNonSeqSetupFalling:    s << "non_seq_setup_falling"; break;
  case kClibTimingNonSeqHoldRising:      s << "non_seq_hold_rising"; break;
  case kClibTimingNonSeqHoldFalling:     s << "non_seq_hold_falling"; break;

  case kClibTimingNochangeHighHigh:      s << "nochange_high_high"; break;
  case kClibTimingNochangeHighLow:       s << "nochange_high_low"; break;
  case kClibTimingNochangeLowHigh:       s << "nochange_low_high"; break;
  case kClibTimingNochangeLowLow:        s << "nochange_low_low"; break;

  default: ASSERT_NOT_REACHED;
  }
  return s;
}

// @brief ストリーム出力演算子
// @param[in] s 出力先のストリーム
// @param[in] var_type 変数の型
// @return s を返す．
ostream&
operator<<(ostream& s,
	   ClibVarType var_type)
{
  switch ( var_type ) {
  case kClibVarInputNetTransition:
    s << "input_net_transition";
    break;

  case kClibVarTotalOutputNetCapacitance:
    s << "total_output_net_capacitance";
    break;

  case kClibVarOutputNetLength:
    s << "output_net_length";
    break;

  case kClibVarOutputNetWireCap:
    s << "output_net_wire_cap";
    break;

  case kClibVarOutputNetPinCap:
    s << "output_net_pin_cap";
    break;

  case kClibVarRelatedOutTotalOutputNetCapacitance:
    s << "related_out_total_output_net_capacitance";
    break;

  case kClibVarRelatedOutOutputNetLength:
    s << "related_out_output_net_length";
    break;

  case kClibVarRelatedOutOutputNetWireCap:
    s << "related_out_output_net_wire_cap";
    break;

  case kClibVarRelatedOutOutputNetPinCap:
    s << "related_out_output_net_pin_cap";
    break;

  case kClibVarConstrainedPinTransition:
    s << "constrained_pin_transition";
    break;

  case kClibVarRelatedPinTransition:
    s << "related_pin_transition";
    break;

  case kClibVarNone:
    s << "none";
    break;

  default:
    ASSERT_NOT_REACHED;
  }
  return s;
}

END_NAMESPACE_YM


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// LUT の情報を出力する．
void
display_lut(ostream& s,
	    const char* label,
	    const ClibLut* lut)
{
  s << "    " << label << endl;
  ymuint d = lut->dimension();
  for (ymuint i = 0; i < d; ++ i) {
    s << "      Variable_" << (i + 1) << " = " << lut->variable_type(i) << endl;
  }
  for (ymuint i = 0; i < d; ++ i) {
    s << "      Index_" << (i + 1) << "    = ";
    ymuint n = lut->index_num(i);
    const char* comma = "";
    s << "(";
    for (ymuint j = 0; j < n; ++ j) {
      s << comma << lut->index(i, j);
      comma = ", ";
    }
    s << ")" << endl;
  }

  if ( d == 1) {
    s << "      Values = (";
    ymuint n1 = lut->index_num(0);
    vector<ymuint32> pos_array(1);
    const char* comma = "";
    for (ymuint i1 = 0; i1 < n1; ++ i1) {
      pos_array[0] = i1;
      s << comma << lut->grid_value(pos_array);
      comma = ", ";
    }
    s << ")" << endl;
  }
  else if ( d == 2 ) {
    s << "      Values = (" << endl;
    ymuint n1 = lut->index_num(0);
    ymuint n2 = lut->index_num(1);
    vector<ymuint32> pos_array(2);
    for (ymuint i1 = 0; i1 < n1; ++ i1) {
      s << "                (";
      pos_array[0] = i1;
      const char* comma = "";
      for (ymuint i2 = 0; i2 < n2; ++ i2) {
	pos_array[1] = i2;
	s << comma << lut->grid_value(pos_array);
	comma = ", ";
      }
      s << ")" << endl;
    }
    s << "               )" << endl;
  }
  else if ( d == 3 ) {
    s << "      Values = (" << endl;
    ymuint n1 = lut->index_num(0);
    ymuint n2 = lut->index_num(1);
    ymuint n3 = lut->index_num(2);
    vector<ymuint32> pos_array(3);
    for (ymuint i1 = 0; i1 < n1; ++ i1) {
      s << "                (";
      pos_array[0] = i1;
      const char* comma2 = "";
      for (ymuint i2 = 0; i2 < n2; ++ i2) {
	pos_array[1] = i2;
	s << comma2 << "(";
	const char* comma3 = "";
	for (ymuint i3 = 0; i3 < n3; ++ i3) {
	  pos_array[2] = i3;
	  s << comma3 << lut->grid_value(pos_array);
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
display_timing(ostream& s,
	       const ClibCell* cell,
	       ymuint ipos,
	       ymuint opos,
	       ClibTimingSense sense,
	       ClibDelayModel delay_model)
{
  for ( auto timing : cell->timing_list(ipos, opos, sense) ) {
    s << "  Timing:" << endl
      << "    Type             = " << timing->type() << endl
      << "    Input Pin        = " << cell->input(ipos)->name() << endl
      << "    Output Pin       = " << cell->output(opos)->name() << endl
      << "    Sense            = ";
    if ( sense == kClibPosiUnate ) {
      s << "positive unate";
    }
    else if ( sense == kClibNegaUnate ) {
      s << "negative unate";
    }
    else {
      ASSERT_NOT_REACHED;
    }
    s << endl;
    if ( !timing->timing_cond().is_one() ) {
      s << "    When             = " << timing->timing_cond() << endl;
    }
    switch ( delay_model ) {
    case kClibDelayGenericCmos:
      s << "    Rise Intrinsic   = " << timing->intrinsic_rise() << endl
	<< "    Rise Resistance  = " << timing->rise_resistance() << endl
	<< "    Fall Intrinsic   = " << timing->intrinsic_fall() << endl
	<< "    Fall Resistance  = " << timing->fall_resistance() << endl;
      break;

    case kClibDelayTableLookup:
      if ( timing->cell_rise() ) {
	display_lut(s, "Clib Rise", timing->cell_rise());
      }
      if ( timing->rise_transition() ) {
	display_lut(s, "Rise Transition", timing->rise_transition());
      }
      if ( timing->rise_propagation() ) {
	display_lut(s, "Rise Propagation", timing->rise_propagation());
      }

      if ( timing->cell_fall() ) {
	display_lut(s, "Clib Fall", timing->cell_fall());
      }
      if ( timing->fall_transition() ) {
	display_lut(s, "Fall Transition", timing->fall_transition());
      }
      if ( timing->fall_propagation() ) {
	display_lut(s, "Fall Propagation", timing->fall_propagation());
      }
      break;

    case kClibDelayPiecewiseCmos:
      break;

    case kClibDelayCmos2:
      break;

    case kClibDelayDcm:
      break;
    }
  }
}

// セルクラスの情報を出力する．
void
display_class(ostream& s,
	      const char* title,
	      const ClibCellClass* cclass)
{
  s << title << endl;
  ymuint n = cclass->idmap_num();
  if ( n > 0 ) {
    s << "  Idmap List = " << endl;
    for (ymuint i = 0; i < n; ++ i) {
      s << cclass->idmap(i) << endl;
    }
    s << endl;
  }
  for ( auto group: cclass->group_list() ) {
    s << "  Group: Map = " << group->map() << endl
      << "         Clib = ";
    for ( auto cell: group->cell_list() ) {
      s << " " << cell->name();
    }
    s << endl;
  }
  s << endl;
}

void
display_pos(ostream& s,
	    const char* title,
	    ymuint pos,
	    ymuint sense)
{
  if ( sense > 0 ) {
    s << " " << title << " = ";
    if ( sense == 2 ) {
      s << "~";
    }
    s << pos;
  }
}

// FFセルクラスの情報を出力する．
void
display_ff_class(ostream& s,
		 const char* title,
		 const ClibCellClass* cclass)
{
  s << title << endl;
  ymuint n = cclass->idmap_num();
  if ( n > 0 ) {
    s << "  Idmap List = " << endl;
    for (ymuint i = 0; i < n; ++ i) {
      s << cclass->idmap(i) << endl;
    }
    s << endl;
  }
  for ( auto group: cclass->group_list() ) {
    s << "  Group:";
    s << " data-pin = " << group->data_pos();
    display_pos(s, "clock-pin", group->clock_pos(), group->clock_sense());
    display_pos(s, "clear-pin", group->clear_pos(), group->clear_sense());
    display_pos(s, "preset-pin", group->preset_pos(), group->preset_sense());
    s << " q-pin = " << group->q_pos()
      << " xq-pin = " << group->xq_pos()
      << endl;
    s << "         Clib = ";
    for ( auto cell: group->cell_list() ) {
      s << " " << cell->name();
    }
    s << endl;
  }
  s << endl;
}

// ラッチセルクラスの情報を出力する．
void
display_latch_class(ostream& s,
		    const char* title,
		    const ClibCellClass* cclass)
{
  s << title << endl;
  ymuint n = cclass->idmap_num();
  if ( n > 0 ) {
    s << "  Idmap List = " << endl;
    for (ymuint i = 0; i < n; ++ i) {
      s << cclass->idmap(i) << endl;
    }
    s << endl;
  }
  for ( auto group: cclass->group_list() ) {
    s << "  Group:";
    display_pos(s, "data-pin",  group->data_pos(), group->has_data() ? 1 : 0);
    display_pos(s, "enable-pin", group->enable_pos(), group->enable_sense());
    display_pos(s, "clear-pin", group->clear_pos(), group->clear_sense());
    display_pos(s, "preset-pin", group->preset_pos(), group->preset_sense());
    s << " q-pin = " << group->q_pos()
      << endl;
    s << "         Clib = ";
    for ( auto cell: group->cell_list() ) {
      s << " " << cell->name();
    }
    s << endl;
  }
  s << endl;
}

// セルグループの情報を出力する．
void
display_group(ostream& s,
	      const char* title,
	      const ClibCellGroup* group)
{
  s << title << endl
    << "  Clib =";
  for ( auto cell: group->cell_list() ) {
    s << " " << cell->name();
  }
  s << endl
    << endl;
}

void
display_index(ostream& s,
	      const ClibLutTemplate* templ,
	      ymuint var)
{
  ymuint n = templ->index_num(var);
  s << "(";
  const char* comma = "";
  for (ymuint i = 0; i < n; ++ i) {
    s << comma << templ->index(var, i);
    comma = ", ";
  }
  s << ")";
}

END_NONAMESPACE

void
display_library(ostream& s,
		const ClibCellLibrary& library)
{
  // ライブラリ名
  s << "Library(" << library.name() << ")" << endl;

  // テクノロジ
  s << "  technology: ";
  switch ( library.technology() ) {
  case kClibTechCmos: s << "cmos"; break;
  case kClibTechFpga: s << "fpga"; break;
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
  ymuint lut_template_num = library.lu_table_template_num();
  for (ymuint i = 0; i < lut_template_num; ++ i) {
    const ClibLutTemplate* templ = library.lu_table_template(i);
    s << "  lu_table_template(" << templ->name() << ")" << endl;
    ymuint d = templ->dimension();
    for (ymuint j = 0; j < d; ++ j) {
      s << "    variable_" << (j + 1) << ": " << templ->variable_type(j) << endl;
    }
    for (ymuint j = 0; j < d; ++ j) {
      s << "    index_" << (j + 1) << "   : ";
      display_index(s, templ, j);
      s << endl;
    }
    s << endl;
  }

  s << endl;

  // セル
  for ( auto cell: library.cell_list() ) {
    // セル名とセルの種類を出力
    s << "Clib#" << cell->id() << " (" << cell->name() << ") : ";
    if ( cell->is_logic() ) {
      s << "Combinational Logic";
    }
    else if ( cell->is_ff() ) {
      s << "Flip-Flop";
    }
    else if ( cell->is_latch() ) {
      s << "Latch";
    }
    else if ( cell->is_fsm() ) {
      s << "FSM";
    }
    else {
      ASSERT_NOT_REACHED;
    }
    s << endl;

    // 面積
    s << "  area = " << cell->area() << endl;

    if ( cell->is_ff() ) {
      // FF の情報
      s << "  Next State         = " << cell->next_state_expr() << endl
	<< "  Clock              = " << cell->clock_expr() << endl;
      if ( !cell->clock2_expr().is_zero() ) {
	s << "  Clock2             = " << cell->clock2_expr() << endl;
      }
      if ( cell->has_clear() ) {
	s << "  Clear              = " << cell->clear_expr() << endl;
      }
      if ( cell->has_preset() ) {
	s << "  Preset             = " << cell->preset_expr() << endl;
      }
      if ( cell->has_clear() && cell->has_preset() ) {
	s << "  Clear Preset Var1  = " << cell->clear_preset_var1() << endl
	  << "  Clear Preset Var2  = " << cell->clear_preset_var2() << endl;
      }
    }
    if ( cell->is_latch() ) {
      // ラッチの情報
      s << "  Data In            = " << cell->data_in_expr() << endl
	<< "  Enable             = " << cell->enable_expr() << endl;
      if ( !cell->enable2_expr().is_zero() ) {
	s << "  Enable2            = " << cell->enable2_expr() << endl;
      }
      if ( cell->has_clear() ) {
	s << "  Clear              = " << cell->clear_expr() << endl;
      }
      if ( cell->has_preset() ) {
	s << "  Preset             = " << cell->preset_expr() << endl;
      }
      if ( cell->has_clear() && cell->has_preset() ) {
	s << "  Clear Preset Var1  = " << cell->clear_preset_var1() << endl
	  << "  Clear Preset Var2  = " << cell->clear_preset_var2() << endl;
      }
    }

    // ピンの情報
    ymuint npin = cell->pin_num();
    for (ymuint pin_id = 0; pin_id < npin; ++ pin_id) {
      const ClibCellPin* pin = cell->pin(pin_id);
      s << "  Pin#" << pin_id << "[ " << pin->name() << " ]: ";
      if ( pin->is_input() ) {
	// 入力ピン
	s << "Input#" << pin->input_id() << endl
	  << "    Capacitance      = " << pin->capacitance() << endl
	  << "    Rise Capacitance = " << pin->rise_capacitance() << endl
	  << "    Fall Capacitance = " << pin->fall_capacitance() << endl;
      }
      else if ( pin->is_output() ) {
	// 出力ピン
	ymuint opos = pin->output_id();
	s << "Output# " << opos << endl;
	if ( cell->has_logic(opos) ) {
	  s << "    Logic            = " << cell->logic_expr(opos) << endl;
	  if ( cell->has_tristate(opos) ) {
	    s << "    Tristate         = " << cell->tristate_expr(opos) << endl;
	  }
	}
	s << "    Max Fanout       = " << pin->max_fanout() << endl
	  << "    Min Fanout       = " << pin->min_fanout() << endl
	  << "    Max Capacitance  = " << pin->max_capacitance() << endl
	  << "    Min Capacitance  = " << pin->min_capacitance() << endl
	  << "    Max Transition   = " << pin->max_transition() << endl
	  << "    Min Transition   = " << pin->min_transition() << endl;
      }
      else if ( pin->is_inout() ) {
	// 入出力ピン
	ymuint opos = pin->output_id();
	s << "Inout#(" << pin->input_id() << ", " << opos << ")" << endl;
	if ( cell->has_logic(opos) ) {
	  s << "    Logic            = " << cell->logic_expr(opos) << endl;
	  if ( cell->has_tristate(opos) ) {
	    s << "    Tristate         = " << cell->tristate_expr(opos) << endl;
	  }
	}
	s << "    Capacitance      = " << pin->capacitance() << endl
	  << "    Rise Capacitance = " << pin->rise_capacitance() << endl
	  << "    Fall Capacitance = " << pin->fall_capacitance() << endl
	  << "    Max Fanout       = " << pin->max_fanout() << endl
	  << "    Min Fanout       = " << pin->min_fanout() << endl
	  << "    Max Capacitance  = " << pin->max_capacitance() << endl
	  << "    Min Capacitance  = " << pin->min_capacitance() << endl
	  << "    Max Transition   = " << pin->max_transition() << endl
	  << "    Min Transition   = " << pin->min_transition() << endl;
      }
      else if ( pin->is_internal() ) {
	// 内部ピン
	ymuint itpos = pin->internal_id();
	s << "Internal#(" << itpos << ")" << endl;
      }
    }

    // タイミング情報
    ymuint ni2 = cell->input_num2();
    ymuint no2 = cell->output_num2();
    for (ymuint ipos = 0; ipos < ni2; ++ ipos) {
      for (ymuint opos = 0; opos < no2; ++ opos) {
	display_timing(s, cell, ipos, opos, kClibPosiUnate, delay_model);
	display_timing(s, cell, ipos, opos, kClibNegaUnate, delay_model);
      }
    }
    s << endl;
  }

  // セルグループの情報
  s << "Clib Group" << endl;
  int i = 0;
  for ( auto cclass: library.npn_class_list() ) {
    ostringstream buf;
    buf << "Class#" << i; ++ i;
    display_class(s, buf.str().c_str(), cclass);
  }

  // 既定セルグループの情報
  display_group(s, "Const0 Group", library.const0_func());
  display_group(s, "Const1 Group", library.const1_func());
  display_group(s, "Buffer Group", library.buf_func());
  display_group(s, "Inverter Group", library.inv_func());

  display_ff_class(s, "DFF Class", library.simple_ff_class(false, false));
  display_ff_class(s, "DFF_R Class", library.simple_ff_class(true, false));
  display_ff_class(s, "DFF_S Class", library.simple_ff_class(false, true));
  display_ff_class(s, "DFF_RS Class", library.simple_ff_class(true, true));

  display_latch_class(s, "Latch Class", library.simple_latch_class(false, false));
  display_latch_class(s, "Latch_R Class", library.simple_latch_class(true, false));
  display_latch_class(s, "Latch_S Class", library.simple_latch_class(false, true));
  display_latch_class(s, "Latch_RS Class", library.simple_latch_class(true, true));

  // パタングラフの情報
  s << "==== PatMgr dump start ====" << endl;

  // ノードの種類の出力
  ymuint nn = library.pg_node_num();
  for (ymuint i = 0; i < nn; ++ i) {
    s << "Node#" << i << ": ";
    switch ( library.pg_node_type(i) ) {
    case kClibPatInput: s << "INPUT#" << library.pg_input_id(i) ; break;
    case kClibPatAnd:   s << "AND"; break;
    case kClibPatXor:   s << "XOR"; break;
    default: ASSERT_NOT_REACHED;
    }
    s << endl;
  }
  s << endl;

  // 枝の情報の出力
  ymuint ne = library.pg_edge_num();
  for (ymuint i = 0; i < ne; ++ i) {
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
  ymuint np = library.pg_pat_num();
  for (ymuint i = 0; i < np; ++ i) {
    const ClibPatGraph& pat = library.pg_pat(i);
    s << "Pat#" << i << ": "
      << "Rep#" << pat.rep_id() << ": ";
    if ( pat.root_inv() ) {
      s << "[inv]";
    }
    s << "(" << pat.input_num() << "), ";
    ymuint n = pat.edge_num();
    for (ymuint i = 0; i < n; ++ i) {
      s << " " << pat.edge(i);
    }
    s << endl;
  }

  s << "==== PatMgr dump end ====" << endl;
}

END_NAMESPACE_YM_CLIB
