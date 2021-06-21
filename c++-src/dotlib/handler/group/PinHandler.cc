
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
  reg_func(AttrType::bit_width,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_int(attr_type, attr_loc); });
  reg_func(AttrType::capacitance,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::clock,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_clock_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_enable_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_test_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_obs_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_out_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::complementary_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::connection_class,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::direction,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_direction(attr_type, attr_loc); });
  reg_func(AttrType::dont_fault,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::drive_current,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::driver_type,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::fall_capacitance,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::fall_current_slope_after_threshold,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::fall_current_slope_before_threshold,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::fall_time_after_threshold,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::fall_time_before_threshold,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::fanout_load,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::fault_model,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::function,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_function(attr_type, attr_loc); });
  reg_func(AttrType::has_builtin_pad,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::hysteresis,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::input_map,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::input_signal_level,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::input_threshold_pct_fall,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::input_threshold_pct_rise,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::input_voltage,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::internal_node,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::inverted_output,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::is_pad,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::isolation_cell_enable_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::level_shifter_enable_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::map_to_logic,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::max_capacitance,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::max_fanout,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::max_input_noise_width,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::max_transition,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::min_capacitance,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::min_fanout,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::min_input_noise_width,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::min_period,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::min_pulse_width_high,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::min_transition,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::multicell_pad_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::nextstate_type,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::output_signal_level,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::output_voltage,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::pg_function,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func(AttrType::pin_func_type,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::power_down_function,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func(AttrType::prefer_tied,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::primary_output,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::pulling_current,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::pulling_resistance,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::pulse_clock,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::related_ground_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::related_power_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::rise_capacitance,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::rise_current_slope_after_threshold,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::rise_current_slope_before_threshold,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::rise_time_after_threshold,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::rise_time_before_threshold,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::signal_type,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::slew_control,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::slew_lower_threshold_pct_fall,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::slew_lower_threshold_pct_rise,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::slew_upper_threshold_pct_fall,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::slew_upper_threshold_pct_rise,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func(AttrType::state_function,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func(AttrType::std_cell_main_rail,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::switch_function,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func(AttrType::switch_pin,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::test_output_only,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func(AttrType::three_state,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });
  reg_func(AttrType::vhdl_name,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func(AttrType::x_function,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_expr(attr_type, attr_loc); });

  reg_func(AttrType::fall_capacitance_range,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float_float(attr_type, attr_loc); });
  reg_func(AttrType::rise_capacitance_range,
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

  reg_func(AttrType::timing,
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_timing(attr_type, attr_loc); });
}

END_NAMESPACE_YM_DOTLIB
