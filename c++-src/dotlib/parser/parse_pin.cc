
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
    { "bit_width",                           parse_int },
    { "capacitance",                         parse_float },
    { "clock",                               parse_bool },
    { "clock_gate_clock_pin",                parse_bool },
    { "clock_gate_enable_pin",               parse_bool },
    { "clock_gate_test_pin",                 parse_bool },
    { "clock_gate_obs_pin",                  parse_bool },
    { "clock_gate_out_pin",                  parse_bool },
    { "complementary_pin",                   parse_string },
    { "connection_class",                    parse_string },
    { "direction",                           parse_direction },
    { "dont_fault",                          parse_string },
    { "drive_current",                       parse_float },
    { "driver_type",                         parse_string },
    { "fall_capacitance",                    parse_float },
    { "fall_current_slope_after_threshold",  parse_float },
    { "fall_current_slope_before_threshold", parse_float },
    { "fall_time_after_threshold",           parse_float },
    { "fall_time_before_threshold",          parse_float },
    { "fanout_load",                         parse_float },
    { "fault_model",                         parse_string },
    { "function",                            parse_function },
    { "has_builtin_pad",                     parse_bool },
    { "hysteresis",                          parse_bool },
    { "input_map",                           parse_string },
    { "input_signal_level",                  parse_string },
    { "input_threshold_pct_fall",            parse_float },
    { "input_threshold_pct_rise",            parse_float },
    { "input_voltage",                       parse_string },
    { "internal_node",                       parse_string },
    { "inverted_output",                     parse_bool },
    { "is_pad",                              parse_bool },
    { "isolation_cell_enable_pin",           parse_bool },
    { "level_shifter_enable_pin",            parse_bool },
    { "map_to_logic",                        parse_expr },
    { "max_capacitance",                     parse_float },
    { "max_fanout",                          parse_float },
    { "max_input_noise_width",               parse_float },
    { "max_transition",                      parse_float },
    { "min_capacitance",                     parse_float },
    { "min_fanout",                          parse_float },
    { "min_input_noise_width",               parse_float },
    { "min_period",                          parse_float},
    { "min_pulse_width_low",                 parse_float},
    { "min_pulse_width_high",                parse_float},
    { "min_transition",                      parse_float },
    { "multicell_pad_pin",                   parse_bool },
    { "nextstate_type",                      parse_string },
    { "output_signal_level",                 parse_string },
    { "output_voltage",                      parse_string },
    { "pg_function",                         parse_function },
    { "pin_func_type",                       parse_string },
    { "power_down_function",                 parse_function },
    { "prefer_tied",                         parse_function },
    { "primary_output",                      parse_bool },
    { "pulling_current",                     parse_float },
    { "pulling_resistance",                  parse_float },
    { "pulse_clock",                         parse_string },
    { "related_ground_pin",                  parse_string },
    { "related_power_pin",                   parse_string },
    { "rise_capacitance",                    parse_float },
    { "rise_current_slope_after_threshold",  parse_float },
    { "rise_current_slope_before_threshold", parse_float },
    { "rise_time_after_threshold",           parse_float },
    { "rise_time_before_threshold",          parse_float },
    { "signal_type",                         parse_string },
    { "slew_control",                        parse_string },
    { "slew_lower_threshold_pct_fall",       parse_float },
    { "slew_lower_threshold_pct_rise",       parse_float },
    { "slew_upper_threshold_pct_fall",       parse_float },
    { "slew_upper_threshold_pct_rise",       parse_float },
    { "state_function",                      parse_function },
    { "std_cell_main_rail",                  parse_bool },
    { "switch_function",                     parse_function },
    { "switch_pin",                          parse_bool },
    { "test_output_only",                    parse_bool },
    { "three_state",                         parse_function },
    { "vhdl_name",                           parse_string },
    { "x_function",                          parse_function },

    // complex attributes
    { "fall_capacitance_range",              parse_float_float },
    { "power_gating_pin",                    parse_string_int },
    { "rise_capacitance_range",              parse_float_float },

    // group statements
    { "ccsn_first_stage",                    parse_ccsn },
    { "ccsn_last_stage",                     parse_ccsn },
    { "dc_current",                          parse_dc_current },
    { "electromigration",                    parse_electromigration },
    { "hyperbolic_noise_above_high",         parse_hyperbolic_noise },
    { "hyperbolic_noise_below_low",          parse_hyperbolic_noise },
    { "hyperbolic_noise_high",               parse_hyperbolic_noise },
    { "hyperbolic_noise_low",                parse_hyperbolic_noise },
    { "input_signal_swing",                  parse_signal_swing },
    { "internal_power",                      parse_internal_power },
    { "max_trans",                           parse_trans },
    { "min_pulse_width",                     parse_pulse_width },
    { "minimum_period",                      parse_minimum_period },
    { "output_signal_swing",                 parse_signal_swing },
    { "pin_capacitance",                     parse_pin_capacitance },
    { "timing",                              parse_timing },
    { "tlatch",                              parse_tlatch }

  };
  return parser.parse_group_statement(attr, Parser::sStrHeader, handler_dict);
}

END_NAMESPACE_YM_DOTLIB
