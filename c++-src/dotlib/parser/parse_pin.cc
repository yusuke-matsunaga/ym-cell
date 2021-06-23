
/// @file parse_pin.cc
/// @brief parse_pin() の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'pin' group statement のパースを行う．
AstAttrPtr
parse_pin(Parser& parser,
	  const AttrKwd& attr)
{
  static AttrHandlerDict handler_dict{
    { AttrType::bit_width,                           parse_int },
    { AttrType::capacitance,                         parse_float },
    { AttrType::clock,                               parse_bool },
    { AttrType::clock_gate_clock_pin,                parse_bool },
    { AttrType::clock_gate_enable_pin,               parse_bool },
    { AttrType::clock_gate_test_pin,                 parse_bool },
    { AttrType::clock_gate_obs_pin,                  parse_bool },
    { AttrType::clock_gate_out_pin,                  parse_bool },
    { AttrType::complementary_pin,                   parse_string },
    { AttrType::connection_class,                    parse_string },
    { AttrType::direction,                           parse_direction },
    { AttrType::dont_fault,                          parse_string },
    { AttrType::drive_current,                       parse_float },
    { AttrType::driver_type,                         parse_string },
    { AttrType::fall_capacitance,                    parse_float },
    { AttrType::fall_current_slope_after_threshold,  parse_float },
    { AttrType::fall_current_slope_before_threshold, parse_float },
    { AttrType::fall_time_after_threshold,           parse_float },
    { AttrType::fall_time_before_threshold,          parse_float },
    { AttrType::fanout_load,                         parse_float },
    { AttrType::fault_model,                         parse_string },
    { AttrType::function,                            parse_function },
    { AttrType::has_builtin_pad,                     parse_bool },
    { AttrType::hysteresis,                          parse_bool },
    { AttrType::input_map,                           parse_string },
    { AttrType::input_signal_level,                  parse_string },
    { AttrType::input_threshold_pct_fall,            parse_float },
    { AttrType::input_threshold_pct_rise,            parse_float },
    { AttrType::input_voltage,                       parse_string },
    { AttrType::internal_node,                       parse_string },
    { AttrType::inverted_output,                     parse_bool },
    { AttrType::is_pad,                              parse_bool },
    { AttrType::isolation_cell_enable_pin,           parse_bool },
    { AttrType::level_shifter_enable_pin,            parse_bool },
    { AttrType::map_to_logic,                        parse_expr },
    { AttrType::max_capacitance,                     parse_float },
    { AttrType::max_fanout,                          parse_float },
    { AttrType::max_input_noise_width,               parse_float },
    { AttrType::max_transition,                      parse_float },
    { AttrType::min_capacitance,                     parse_float },
    { AttrType::min_fanout,                          parse_float },
    { AttrType::min_input_noise_width,               parse_float },
    { AttrType::min_period,                          parse_float},
    { AttrType::min_pulse_width_low,                 parse_float},
    { AttrType::min_pulse_width_high,                parse_float},
    { AttrType::min_transition,                      parse_float },
    { AttrType::multicell_pad_pin,                   parse_bool },
    { AttrType::nextstate_type,                      parse_string },
    { AttrType::output_signal_level,                 parse_string },
    { AttrType::output_voltage,                      parse_string },
    { AttrType::pg_function,                         parse_function },
    { AttrType::pin_func_type,                       parse_string },
    { AttrType::power_down_function,                 parse_function },
    { AttrType::prefer_tied,                         parse_function },
    { AttrType::primary_output,                      parse_bool },
    { AttrType::pulling_current,                     parse_float },
    { AttrType::pulling_resistance,                  parse_float },
    { AttrType::pulse_clock,                         parse_string },
    { AttrType::related_ground_pin,                  parse_string },
    { AttrType::related_power_pin,                   parse_string },
    { AttrType::rise_capacitance,                    parse_float },
    { AttrType::rise_current_slope_after_threshold,  parse_float },
    { AttrType::rise_current_slope_before_threshold, parse_float },
    { AttrType::rise_time_after_threshold,           parse_float },
    { AttrType::rise_time_before_threshold,          parse_float },
    { AttrType::signal_type,                         parse_string },
    { AttrType::slew_control,                        parse_string },
    { AttrType::slew_lower_threshold_pct_fall,       parse_float },
    { AttrType::slew_lower_threshold_pct_rise,       parse_float },
    { AttrType::slew_upper_threshold_pct_fall,       parse_float },
    { AttrType::slew_upper_threshold_pct_rise,       parse_float },
    { AttrType::state_function,                      parse_function },
    { AttrType::std_cell_main_rail,                  parse_bool },
    { AttrType::switch_function,                     parse_function },
    { AttrType::switch_pin,                          parse_bool },
    { AttrType::test_output_only,                    parse_bool },
    { AttrType::three_state,                         parse_function },
    { AttrType::vhdl_name,                           parse_string },
    { AttrType::x_function,                          parse_function },

    // complex attributes
    { AttrType::fall_capacitance_range,              parse_float_float },
    { AttrType::power_gating_pin,                    parse_string_int },
    { AttrType::rise_capacitance_range,              parse_float_float },

    // group statements
    { AttrType::ccsn_first_stage,                    parse_ccsn },
    { AttrType::ccsn_last_stage,                     parse_ccsn },
    { AttrType::dc_current,                          parse_dc_current },
    { AttrType::electromigration,                    parse_electromigration },
    { AttrType::hyperbolic_noise_above_high,         parse_hyperbolic_noise },
    { AttrType::hyperbolic_noise_below_low,          parse_hyperbolic_noise },
    { AttrType::hyperbolic_noise_high,               parse_hyperbolic_noise },
    { AttrType::hyperbolic_noise_low,                parse_hyperbolic_noise },
    { AttrType::input_signal_swing,                  parse_signal_swing },
    { AttrType::internal_power,                      parse_internal_power },
    { AttrType::max_trans,                           parse_trans },
    { AttrType::min_pulse_width,                     parse_pulse_width },
    { AttrType::minimum_period,                      parse_minimum_period },
    { AttrType::output_signal_swing,                 parse_signal_swing },
    { AttrType::pin_capacitance,                     parse_pin_capacitance },
    { AttrType::timing,                              parse_timing },
    { AttrType::tlatch,                              parse_tlatch }

  };
  return parser.parse_group_statement(attr, Parser::sStrHeader, handler_dict);
}

END_NAMESPACE_YM_DOTLIB
