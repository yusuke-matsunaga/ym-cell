
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
    { AttrType::area,                         parse_float },
    { AttrType::auxiliary_pad_cell,           parse_bool },
    { AttrType::base_name,                    parse_string },
    { AttrType::bus_naming_style,             parse_string },
    { AttrType::cell_footprint,               parse_string },
    { AttrType::cell_leakage_power,           parse_float },
    { AttrType::clock_gating_integrated_cell, parse_string },
    { AttrType::contention_condition,         parse_function },
    { AttrType::dont_fault,                   parse_string },
    { AttrType::dont_touch,                   parse_bool },
    { AttrType::dont_use,                     parse_bool },
    { AttrType::driver_type,                  parse_string },
    { AttrType::edif_name,                    parse_string },
    { AttrType::em_temp_degradation_factor,   parse_float },
    { AttrType::fpga_cell_type,               parse_string },
    { AttrType::fpga_domain_style,            parse_string },
    { AttrType::geometry_print,               parse_string },
    { AttrType::handle_negative_constraint,   parse_bool },
    { AttrType::interface_timing,             parse_bool },
    { AttrType::io_type,                      parse_string },
    { AttrType::is_clock_gating_cell,         parse_bool },
    { AttrType::is_isolation_cell,            parse_bool },
    { AttrType::is_level_shifter,             parse_bool },
    { AttrType::level_shifter_type,           parse_string },
    { AttrType::map_only,                     parse_bool },
    { AttrType::pad_cell,                     parse_bool },
    { AttrType::pad_type,                     parse_string },
    { AttrType::power_cell_type,              parse_string },
    { AttrType::power_gating_cell,            parse_string },
    { AttrType::preferred,                    parse_bool },
    { AttrType::scaling_factors,              parse_string },
    { AttrType::sensitization_master,         parse_string },
    { AttrType::single_bit_degenerate,        parse_string },
    { AttrType::slew_type,                    parse_string },
    { AttrType::switch_cell_type,             parse_string },
    { AttrType::threshold_voltage_group,      parse_string },
    { AttrType::timing_model_type,            parse_string },
    { AttrType::use_for_size_only,            parse_bool },
    { AttrType::vhdl_name,                    parse_string },

    // complex attributes
    { AttrType::input_voltage_range,          parse_float_float },
    { AttrType::output_voltage_range,         parse_float_float },
    { AttrType::pin_equal,                    parse_string_complex },
    { AttrType::pin_name_map,                 parse_string_list },
    { AttrType::pin_opposite,                 parse_string_list },
    { AttrType::rail_connection,              parse_string_string },
    { AttrType::resource_usage,               parse_string_string },

    // group statements
    { AttrType::bundle,                       parse_bundle },
    { AttrType::bus,                          parse_bus },
    //{ AttrType::dynamic_current               parse_dynamic_current },
    { AttrType::ff,                           parse_ff },
    { AttrType::ff_bank,                      parse_ff_bank },
    //{ AttrType::functional_yield_metric,      parse_functional_yield_metric },
    //{ AttrType::generated_clock,              parse_generated_clock },
    //{ AttrType::intrinsic_parasitic,          parse_intrinsic_parasitic },
    { AttrType::latch,                        parse_latch },
    { AttrType::latch_bank,                   parse_latch_bank },
    { AttrType::leakage_current,              parse_leakage_current },
    { AttrType::leakage_power,                parse_leakage_power },
    { AttrType::lut,                          parse_lut },
    //{ AttrType::mode_definition,              parse_mode_definition },
    //{ AttrType::pg_pin,                       parse_pg_pin },
    { AttrType::pin,                          parse_pin },
    { AttrType::pin_group,                    parse_pin_group },
    //{ AttrType::routing_track,                parse_routing_track },
    { AttrType::statetable,                   parse_statetable },
    { AttrType::test_cell,                    parse_cell },
    { AttrType::type,                         parse_type },
  };
  return parser.parse_group_statement(attr, Parser::sStrHeader, handler_dict);
}

END_NAMESPACE_YM_DOTLIB
