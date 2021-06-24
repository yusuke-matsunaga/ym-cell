
/// @file parse_cell.cc
/// @brief cell group の読み込みを行なう
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'cell' group statement のパースを行う．
AstAttrPtr
parse_cell(Parser& parser,
	   const AttrKwd& attr)
{
  static AttrHandlerDict handler_dict{
    // simple attributes
    { "area",                         parse_float },
    { "auxiliary_pad_cell",           parse_bool },
    { "base_name",                    parse_string },
    { "bus_naming_style",             parse_string },
    { "cell_footprint",               parse_string },
    { "cell_leakage_power",           parse_float },
    { "clock_gating_integrated_cell", parse_string },
    { "contention_condition",         parse_function },
    { "dont_fault",                   parse_string },
    { "dont_touch",                   parse_bool },
    { "dont_use",                     parse_bool },
    { "driver_type",                  parse_string },
    { "edif_name",                    parse_string },
    { "em_temp_degradation_factor",   parse_float },
    { "fpga_cell_type",               parse_string },
    { "fpga_domain_style",            parse_string },
    { "geometry_print",               parse_string },
    { "handle_negative_constraint",   parse_bool },
    { "interface_timing",             parse_bool },
    { "io_type",                      parse_string },
    { "is_clock_gating_cell",         parse_bool },
    { "is_isolation_cell",            parse_bool },
    { "is_level_shifter",             parse_bool },
    { "level_shifter_type",           parse_string },
    { "map_only",                     parse_bool },
    { "pad_cell",                     parse_bool },
    { "pad_type",                     parse_string },
    { "power_cell_type",              parse_string },
    { "power_gating_cell",            parse_string },
    { "preferred",                    parse_bool },
    { "scaling_factors",              parse_string },
    { "sensitization_master",         parse_string },
    { "single_bit_degenerate",        parse_string },
    { "slew_type",                    parse_string },
    { "switch_cell_type",             parse_string },
    { "threshold_voltage_group",      parse_string },
    { "timing_model_type",            parse_string },
    { "use_for_size_only",            parse_bool },
    { "vhdl_name",                    parse_string },

    // complex attributes
    { "input_voltage_range",          parse_float_float },
    { "output_voltage_range",         parse_float_float },
    { "pin_equal",                    parse_string_complex },
    { "pin_name_map",                 parse_string_list },
    { "pin_opposite",                 parse_string_list },
    { "rail_connection",              parse_string_string },
    { "resource_usage",               parse_string_string },

    // group statements
    { "bundle",                       parse_bundle },
    { "bus",                          parse_bus },
    //{ "dynamic_current"               parse_dynamic_current },
    { "ff",                           parse_ff },
    { "ff_bank",                      parse_ff_bank },
    //{ "functional_yield_metric",      parse_functional_yield_metric },
    //{ "generated_clock",              parse_generated_clock },
    //{ "intrinsic_parasitic",          parse_intrinsic_parasitic },
    { "latch",                        parse_latch },
    { "latch_bank",                   parse_latch_bank },
    { "leakage_current",              parse_leakage_current },
    { "leakage_power",                parse_leakage_power },
    { "lut",                          parse_lut },
    //{ "mode_definition",              parse_mode_definition },
    //{ "pg_pin",                       parse_pg_pin },
    { "pin",                          parse_pin },
    { "pin_group",                    parse_pin_group },
    //{ "routing_track",                parse_routing_track },
    { "statetable",                   parse_statetable },
    { "test_cell",                    parse_cell },
    { "type",                         parse_type },
  };
  return parser.parse_group_statement(attr, Parser::sStrHeader, handler_dict);
}

END_NAMESPACE_YM_DOTLIB
