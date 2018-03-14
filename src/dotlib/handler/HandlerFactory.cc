
/// @file HandlerFactory.cc
/// @brief HandlerFactory の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "HandlerFactory.h"

#include "DefineHandler.h"
#include "GroupHandler.h"

#include "TimingHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス HandlerFactory
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
HandlerFactory::HandlerFactory()
{
}

// @brief デストラクタ
HandlerFactory::~HandlerFactory()
{
}

// @brief operating_conditions group 用のハンドラを作る．
// @param[in] parent パーサー
DotlibHandler*
HandlerFactory::new_operating_conditions(DotlibParser& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  DotlibHandler* simple = HandlerFactory::new_simple(parser);
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  DotlibHandler* flt_simple = HandlerFactory::new_float(parser);
  DotlibHandler* complex = HandlerFactory::new_complex(parser);

  // simple attributes
  handler->reg_handler(AttrType::calc_mode,   simple);
  handler->reg_handler(AttrType::parameter1,  simple);
  handler->reg_handler(AttrType::parameter2,  simple);
  handler->reg_handler(AttrType::parameter3,  simple);
  handler->reg_handler(AttrType::parameter4,  simple);
  handler->reg_handler(AttrType::parameter5,  simple);
  handler->reg_handler(AttrType::process,     flt_simple);
  handler->reg_handler(AttrType::temperature, flt_simple);
  handler->reg_handler(AttrType::tree_type,   str_simple);
  handler->reg_handler(AttrType::volTAGE,     flt_simple);

  // complex attributes
  handler->reg_handler(AttrType::power_rail, complex);

  return handler;
}

// @brief wire_load group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_wire_load(DotlibParser& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  DotlibHandler* flt_simple = HandlerFactory::new_float(parser);
  DotlibHandler* complex = HandlerFactory::new_complex(parser);

  // simple attributes
  handler->reg_handler(AttrType::area,        flt_simple);
  handler->reg_handler(AttrType::capacitance, flt_simple);
  handler->reg_handler(AttrType::resistance,  flt_simple);
  handler->reg_handler(AttrType::slope,       flt_simple);

  // complex attributes
  handler->reg_handler(AttrType::fanout_length, complex);

  return handler;
}

// @brief wire_load_selection group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_wire_load_selection(DotlibParser& parser)
{
  GroupHandler* handler = new_group(parser);

  DotlibHandler* complex = HandlerFactory::new_complex(parser);

  // complex attributes
  handler->reg_handler(AttrType::wire_load_FROM_area, complex);

  return handler;
}

// @brief wire_load_table group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_wire_load_table(DotlibParser& parser)
{
  GroupHandler* handler = new_group(parser);

  DotlibHandler* complex = HandlerFactory::new_complex(parser);

  // complex attributes
  handler->reg_handler(AttrType::FANOUT_area,        complex);
  handler->reg_handler(AttrType::FANOUT_capacitance, complex);
  handler->reg_handler(AttrType::fanout_length,      complex);
  handler->reg_handler(AttrType::fanout_resistance,  complex);

  return handler;
}

// @brief cell group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_cell(DotlibParser& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  DotlibHandler* simple = HandlerFactory::new_simple(parser);
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  DotlibHandler* flt_simple = HandlerFactory::new_float(parser);
  DotlibHandler* complex = HandlerFactory::new_complex(parser);

  // simple attributes
  handler->reg_handler(AttrType::area,                         flt_simple);
  handler->reg_handler(AttrType::auxiliary_pad_cell,           simple);
  handler->reg_handler(AttrType::base_name,                    str_simple);
  handler->reg_handler(AttrType::bus_naming_style,             str_simple);
  handler->reg_handler(AttrType::cell_footprint,               str_simple);
  handler->reg_handler(AttrType::cell_leakage_power,           simple);
  handler->reg_handler(AttrType::clock_GATING_INTEGRATED_cell, simple);
  handler->reg_handler(AttrType::contention_condition,         simple);
  handler->reg_handler(AttrType::dont_fault,                   simple);
  handler->reg_handler(AttrType::dont_touch,                   simple);
  handler->reg_handler(AttrType::dont_use,                     simple);
  handler->reg_handler(AttrType::driver_type,                  simple);
  handler->reg_handler(AttrType::edif_name,                    simple);
  handler->reg_handler(AttrType::em_temp_degradation_factor,   simple);
  handler->reg_handler(AttrType::FPGA_domain_STYLE,            simple);
  handler->reg_handler(AttrType::geometry_print,               simple);
  handler->reg_handler(AttrType::handle_negative_constraint,   simple);
  handler->reg_handler(AttrType::interface_timing,             simple);
  handler->reg_handler(AttrType::io_type,                      simple);
  handler->reg_handler(AttrType::IS_clock_GATING_cell,         simple);
  handler->reg_handler(AttrType::map_only,                     simple);
  handler->reg_handler(AttrType::PAD_cell,                     simple);
  handler->reg_handler(AttrType::pad_type,                     simple);
  handler->reg_handler(AttrType::power_cell_type,              simple);
  handler->reg_handler(AttrType::preferred,                    simple);
  handler->reg_handler(AttrType::scaling_factors,              simple);
  handler->reg_handler(AttrType::single_bit_degenerate,        simple);
  handler->reg_handler(AttrType::slew_type,                    simple);
  handler->reg_handler(AttrType::timing_model_type,            simple);
  handler->reg_handler(AttrType::use_for_size_only,            simple);
  handler->reg_handler(AttrType::vhdl_name,                    simple);

  handler->reg_handler(AttrType::IS_FILLER_cell,               simple);

  // complex attributes
  handler->reg_handler(AttrType::pin_opposite,                 complex);
  handler->reg_handler(AttrType::rail_connection,              complex);
  handler->reg_handler(AttrType::power_supply_namestring,      complex);
  handler->reg_handler(AttrType::resource_usage,               complex);

  // group statements
  handler->reg_handler(AttrType::bus,                          new_bus(parser));
  handler->reg_handler(AttrType::bundle,                       new_bundle(parser));
  handler->reg_handler(AttrType::dynamic_current,              new_group(parser));
  handler->reg_handler(AttrType::ff,                           new_ff(parser));
  handler->reg_handler(AttrType::ff_bank,                      new_ff_bank(parser));
  handler->reg_handler(AttrType::functionAL_YIELD_METRIC,      new_group(parser));
  handler->reg_handler(AttrType::GENERATED_clock,              new_group(parser));
  handler->reg_handler(AttrType::intrinsic_parasitic,          new_group(parser));
  handler->reg_handler(AttrType::latch,                        new_latch(parser));
  handler->reg_handler(AttrType::latch_bank,                   new_latch_bank(parser));
  handler->reg_handler(AttrType::leakage_current,              new_group(parser));
  handler->reg_handler(AttrType::leakage_power,                new_leakage_power(parser));
  handler->reg_handler(AttrType::lut,                          new_group(parser));
  handler->reg_handler(AttrType::mode_definition,              new_group(parser));
  handler->reg_handler(AttrType::pin,                          new_pin(parser));
  handler->reg_handler(AttrType::routing_track,                new_group(parser));
  handler->reg_handler(AttrType::statetable,                   new_statetable(parser));

  handler->reg_handler(AttrType::internal_power,               new_cell_internal_power(parser));

  handler->reg_handler(AttrType::TEST_cell,                    new_test_cell(parser));

  return handler;
}

// @brief leakage_power group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_leakage_power(DotlibParser& parser)
{
  GroupHandler* handler = new EmptyGroupHandler(parser);

  // simple attributes
  DotlibHandler* simple = HandlerFactory::new_simple(parser);
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  DotlibHandler* func_handler = HandlerFactory::new_function(parser);
  DotlibHandler* flt_simple = HandlerFactory::new_float(parser);
  handler->reg_handler(AttrType::power_level,    simple);
  handler->reg_handler(AttrType::RELATED_PG_pin, str_simple);
  handler->reg_handler(AttrType::when,           func_handler);
  handler->reg_handler(AttrType::value,          flt_simple);

  return handler;
}

// @brief test_cell group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_test_cell(DotlibParser& parser)
{
  GroupHandler* handler = new_group(parser);

  // group statements
  handler->reg_handler(AttrType::bus, new_bus(parser));
  handler->reg_handler(AttrType::dynamic_current, new_group(parser));
  handler->reg_handler(AttrType::ff, new_ff(parser));
  handler->reg_handler(AttrType::ff_bank, new_ff_bank(parser));
  handler->reg_handler(AttrType::functionAL_YIELD_METRIC, new_group(parser));
  handler->reg_handler(AttrType::GENERATED_clock, new_group(parser));
  handler->reg_handler(AttrType::intrinsic_parasitic, new_group(parser));
  handler->reg_handler(AttrType::latch, new_latch(parser));
  handler->reg_handler(AttrType::latch_bank, new_latch_bank(parser));
  handler->reg_handler(AttrType::leakage_current, new_group(parser));
  handler->reg_handler(AttrType::leakage_power, new_leakage_power(parser));
  handler->reg_handler(AttrType::lut, new_group(parser));
  handler->reg_handler(AttrType::mode_definition, new_group(parser));
  handler->reg_handler(AttrType::pin, new_pin(parser));
  handler->reg_handler(AttrType::statetable, new_statetable(parser));

  return handler;
}

// @brief ff group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_ff(DotlibParser& parser)
{
  GroupHandler* handler = new Str2GroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  DotlibHandler* fhandler = HandlerFactory::new_function(parser);
  handler->reg_handler(AttrType::clear,             fhandler);
  handler->reg_handler(AttrType::clear_preset_var1, str_simple);
  handler->reg_handler(AttrType::clear_preset_var2, str_simple);
  handler->reg_handler(AttrType::clockED_ON,        fhandler);
  handler->reg_handler(AttrType::clockED_ON_ALSO,   fhandler);
  handler->reg_handler(AttrType::next_state,        fhandler);
  handler->reg_handler(AttrType::preset,            fhandler);

  return handler;
}

// @brief ff_bank group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_ff_bank(DotlibParser& parser)
{
  GroupHandler* handler = new Str2IntGroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  DotlibHandler* fhandler = HandlerFactory::new_function(parser);
  handler->reg_handler(AttrType::clear,             fhandler);
  handler->reg_handler(AttrType::clear_preset_var1, str_simple);
  handler->reg_handler(AttrType::clear_preset_var2, str_simple);
  handler->reg_handler(AttrType::clockED_ON,        fhandler);
  handler->reg_handler(AttrType::clockED_ON_ALSO,   fhandler);
  handler->reg_handler(AttrType::next_state,        fhandler);
  handler->reg_handler(AttrType::preset,            fhandler);

  return handler;
}

// @brief latch group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_latch(DotlibParser& parser)
{
  GroupHandler* handler = new Str2GroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  DotlibHandler* fhandler = HandlerFactory::new_function(parser);
  handler->reg_handler(AttrType::clear,             fhandler);
  handler->reg_handler(AttrType::clear_preset_var1, str_simple);
  handler->reg_handler(AttrType::clear_preset_var2, str_simple);
  handler->reg_handler(AttrType::data_in,           fhandler);
  handler->reg_handler(AttrType::enable,            fhandler);
  handler->reg_handler(AttrType::enable_also,       fhandler);
  handler->reg_handler(AttrType::preset,            fhandler);

  return handler;
}

// @brief latch_bank group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_latch_bank(DotlibParser& parser)
{
  GroupHandler* handler = new Str2IntGroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  DotlibHandler* fhandler = HandlerFactory::new_function(parser);
  handler->reg_handler(AttrType::clear,             fhandler);
  handler->reg_handler(AttrType::clear_preset_var1, str_simple);
  handler->reg_handler(AttrType::clear_preset_var2, str_simple);
  handler->reg_handler(AttrType::data_in,           fhandler);
  handler->reg_handler(AttrType::enable,            fhandler);
  handler->reg_handler(AttrType::enable_also,       fhandler);
  handler->reg_handler(AttrType::preset,            fhandler);

  return handler;
}

// @brief statetable group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_statetable(DotlibParser& parser)
{
  GroupHandler* handler = new Str2GroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  handler->reg_handler(AttrType::table, str_simple);

  return handler;
}

// @brief bus group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_bus(DotlibParser& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  handler->reg_handler(AttrType::bus_type, str_simple);

  // group statements
  handler->reg_handler(AttrType::pin, new_pin(parser));

  return handler;
}

// @brief bundle group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_bundle(DotlibParser& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  DotlibHandler* flt_simple = HandlerFactory::new_float(parser);
  DotlibHandler* func_handler = HandlerFactory::new_function(parser);
  DotlibHandler* pin_direction = HandlerFactory::new_pin_direction(parser);
  DotlibHandler* complex = HandlerFactory::new_complex(parser);

  // simple attributes
  handler->reg_handler(AttrType::capacitance, flt_simple);
  handler->reg_handler(AttrType::direction,   pin_direction);
  handler->reg_handler(AttrType::function,    func_handler);

  // complex attributes
  handler->reg_handler(AttrType::members,     complex);

  // group statements
  handler->reg_handler(AttrType::pin, new_pin(parser));
  handler->reg_handler(AttrType::electromigration, new_group(parser));
  handler->reg_handler(AttrType::hyperbolic_noise_above_high, new_group(parser));
  handler->reg_handler(AttrType::hyperbolic_noise_below_low, new_group(parser));
  handler->reg_handler(AttrType::hyperbolic_noise_high, new_group(parser));
  handler->reg_handler(AttrType::hyperbolic_noise_low, new_group(parser));
  handler->reg_handler(AttrType::internal_power, new_internal_power(parser));
  handler->reg_handler(AttrType::max_trans, new_group(parser));
  handler->reg_handler(AttrType::min_pulse_width, new_group(parser));
  handler->reg_handler(AttrType::minimum_period, new_group(parser));
  handler->reg_handler(AttrType::timing, new_timing(parser));
  handler->reg_handler(AttrType::Tlatch, new_group(parser));

  return handler;
}

// @brief 汎用の group 用のハンドラを作る．
GroupHandler*
HandlerFactory::new_group(DotlibParser& parser)
{
  return new GroupHandler(parser);
}

END_NAMESPACE_YM_DOTLIB
