
/// @file PinHandler.cc
/// @brief PinHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/PinHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス PinHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PinHandler::PinHandler(Parser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func("bit_width,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_int(attr_type, attr_loc); });
  reg_func("capacitance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("clock,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("clock_gate_clock_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("clock_gate_enable_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("clock_gate_test_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("clock_gate_obs_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("clock_gate_out_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("complementary_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("connection_class,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("direction,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_direction(attr_type, attr_loc); });
  reg_func("dont_fault,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("drive_current,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("driver_type,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("fall_capacitance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("fall_current_slope_after_threshold,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("fall_current_slope_before_threshold,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("fall_time_after_threshold,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("fall_time_before_threshold,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("fanout_load,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("fault_model,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("function,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_function(attr_type, attr_loc); });
  reg_func("has_builtin_pad,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("hysteresis,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("input_map,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("input_signal_level,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("input_threshold_pct_fall,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("input_threshold_pct_rise,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("input_voltage,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("internal_node,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("inverted_output,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("is_pad,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("isolation_cell_enable_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("level_shifter_enable_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("map_to_logic,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("max_capacitance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("max_fanout,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("max_input_noise_width,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("max_transition,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("min_capacitance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("min_fanout,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("min_input_noise_width,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("min_period,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("min_pulse_width_high,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("min_transition,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("multicell_pad_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("nextstate_type,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("output_signal_level,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("output_voltage,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("pg_function,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func("pin_func_type,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("power_down_function,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func("prefer_tied,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("primary_output,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("pulling_current,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("pulling_resistance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("pulse_clock,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("related_ground_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("related_power_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("rise_capacitance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("rise_current_slope_after_threshold,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("rise_current_slope_before_threshold,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("rise_time_after_threshold,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("rise_time_before_threshold,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("signal_type,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("slew_control,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("slew_lower_threshold_pct_fall,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("slew_lower_threshold_pct_rise,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("slew_upper_threshold_pct_fall,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("slew_upper_threshold_pct_rise,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("state_function,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func("std_cell_main_rail,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("switch_function,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func("switch_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("test_output_only,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("three_state,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func("vhdl_name,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("x_function,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });

  reg_func("fall_capacitance_range,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_float(attr_type, attr_loc); });
  reg_func("rise_capacitance_range,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_float(attr_type, attr_loc); });

  // power_gating_pin (string, int)

  // electromigration

  // hyperbolic_noise_above_high

  // hyperbolic_noise_below_low

  // hyperbolic_noise_high

  // hyperbolic_noise_low

  // internal_power

  // max_trans

  // min_pulse_width

  // minimum_period

  // tlatch

  reg_func("timing,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_timing(attr_type, attr_loc); });
}

END_NAMESPACE_YM_DOTLIB
