﻿
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
  handler->reg_handler(AttrType::CALC_MODE,   simple);
  handler->reg_handler(AttrType::PARAMETER1,  simple);
  handler->reg_handler(AttrType::PARAMETER2,  simple);
  handler->reg_handler(AttrType::PARAMETER3,  simple);
  handler->reg_handler(AttrType::PARAMETER4,  simple);
  handler->reg_handler(AttrType::PARAMETER5,  simple);
  handler->reg_handler(AttrType::PROCESS,     flt_simple);
  handler->reg_handler(AttrType::TEMPERATURE, flt_simple);
  handler->reg_handler(AttrType::TREE_TYPE,   str_simple);
  handler->reg_handler(AttrType::VOLTAGE,     flt_simple);

  // complex attributes
  handler->reg_handler(AttrType::POWER_RAIL, complex);

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
  handler->reg_handler(AttrType::AREA,        flt_simple);
  handler->reg_handler(AttrType::CAPACITANCE, flt_simple);
  handler->reg_handler(AttrType::RESISTANCE,  flt_simple);
  handler->reg_handler(AttrType::SLOPE,       flt_simple);

  // complex attributes
  handler->reg_handler(AttrType::FANOUT_LENGTH, complex);

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
  handler->reg_handler(AttrType::WIRE_LOAD_FROM_AREA, complex);

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
  handler->reg_handler(AttrType::FANOUT_AREA,        complex);
  handler->reg_handler(AttrType::FANOUT_CAPACITANCE, complex);
  handler->reg_handler(AttrType::FANOUT_LENGTH,      complex);
  handler->reg_handler(AttrType::FANOUT_RESISTANCE,  complex);

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
  handler->reg_handler(AttrType::AREA,                         flt_simple);
  handler->reg_handler(AttrType::AUXILIARY_PAD_CELL,           simple);
  handler->reg_handler(AttrType::BASE_NAME,                    str_simple);
  handler->reg_handler(AttrType::BUS_NAMING_STYLE,             str_simple);
  handler->reg_handler(AttrType::CELL_FOOTPRINT,               str_simple);
  handler->reg_handler(AttrType::CELL_LEAKAGE_POWER,           simple);
  handler->reg_handler(AttrType::CLOCK_GATING_INTEGRATED_CELL, simple);
  handler->reg_handler(AttrType::CONTENTION_CONDITION,         simple);
  handler->reg_handler(AttrType::DONT_FAULT,                   simple);
  handler->reg_handler(AttrType::DONT_TOUCH,                   simple);
  handler->reg_handler(AttrType::DONT_USE,                     simple);
  handler->reg_handler(AttrType::DRIVER_TYPE,                  simple);
  handler->reg_handler(AttrType::EDIF_NAME,                    simple);
  handler->reg_handler(AttrType::EM_TEMP_DEGRADATION_FACTOR,   simple);
  handler->reg_handler(AttrType::FPGA_DOMAIN_STYLE,            simple);
  handler->reg_handler(AttrType::GEOMETRY_PRINT,               simple);
  handler->reg_handler(AttrType::HANDLE_NEGATIVE_CONSTRAINT,   simple);
  handler->reg_handler(AttrType::INTERFACE_TIMING,             simple);
  handler->reg_handler(AttrType::IO_TYPE,                      simple);
  handler->reg_handler(AttrType::IS_CLOCK_GATING_CELL,         simple);
  handler->reg_handler(AttrType::MAP_ONLY,                     simple);
  handler->reg_handler(AttrType::PAD_CELL,                     simple);
  handler->reg_handler(AttrType::PAD_TYPE,                     simple);
  handler->reg_handler(AttrType::POWER_CELL_TYPE,              simple);
  handler->reg_handler(AttrType::PREFERRED,                    simple);
  handler->reg_handler(AttrType::SCALING_FACTORS,              simple);
  handler->reg_handler(AttrType::SINGLE_BIT_DEGENERATE,        simple);
  handler->reg_handler(AttrType::SLEW_TYPE,                    simple);
  handler->reg_handler(AttrType::TIMING_MODEL_TYPE,            simple);
  handler->reg_handler(AttrType::USE_FOR_SIZE_ONLY,            simple);
  handler->reg_handler(AttrType::VHDL_NAME,                    simple);

  handler->reg_handler(AttrType::IS_FILLER_CELL,               simple);

  // complex attributes
  handler->reg_handler(AttrType::PIN_OPPOSITE,                 complex);
  handler->reg_handler(AttrType::RAIL_CONNECTION,              complex);
  handler->reg_handler(AttrType::POWER_SUPPLY_NAMESTRING,      complex);
  handler->reg_handler(AttrType::RESOURCE_USAGE,               complex);

  // group statements
  handler->reg_handler(AttrType::BUS,                          new_bus(parser));
  handler->reg_handler(AttrType::BUNDLE,                       new_bundle(parser));
  handler->reg_handler(AttrType::DYNAMIC_CURRENT,              new_group(parser));
  handler->reg_handler(AttrType::FF,                           new_ff(parser));
  handler->reg_handler(AttrType::FF_BANK,                      new_ff_bank(parser));
  handler->reg_handler(AttrType::FUNCTIONAL_YIELD_METRIC,      new_group(parser));
  handler->reg_handler(AttrType::GENERATED_CLOCK,              new_group(parser));
  handler->reg_handler(AttrType::INTRINSIC_PARASITIC,          new_group(parser));
  handler->reg_handler(AttrType::LATCH,                        new_latch(parser));
  handler->reg_handler(AttrType::LATCH_BANK,                   new_latch_bank(parser));
  handler->reg_handler(AttrType::LEAKAGE_CURRENT,              new_group(parser));
  handler->reg_handler(AttrType::LEAKAGE_POWER,                new_leakage_power(parser));
  handler->reg_handler(AttrType::LUT,                          new_group(parser));
  handler->reg_handler(AttrType::MODE_DEFINITION,              new_group(parser));
  handler->reg_handler(AttrType::PIN,                          new_pin(parser));
  handler->reg_handler(AttrType::ROUTING_TRACK,                new_group(parser));
  handler->reg_handler(AttrType::STATETABLE,                   new_statetable(parser));

  handler->reg_handler(AttrType::INTERNAL_POWER,               new_cell_internal_power(parser));

  handler->reg_handler(AttrType::TEST_CELL,                    new_test_cell(parser));

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
  handler->reg_handler(AttrType::POWER_LEVEL,    simple);
  handler->reg_handler(AttrType::RELATED_PG_PIN, str_simple);
  handler->reg_handler(AttrType::WHEN,           func_handler);
  handler->reg_handler(AttrType::VALUE,          flt_simple);

  return handler;
}

// @brief test_cell group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_test_cell(DotlibParser& parser)
{
  GroupHandler* handler = new_group(parser);

  // group statements
  handler->reg_handler(AttrType::BUS, new_bus(parser));
  handler->reg_handler(AttrType::DYNAMIC_CURRENT, new_group(parser));
  handler->reg_handler(AttrType::FF, new_ff(parser));
  handler->reg_handler(AttrType::FF_BANK, new_ff_bank(parser));
  handler->reg_handler(AttrType::FUNCTIONAL_YIELD_METRIC, new_group(parser));
  handler->reg_handler(AttrType::GENERATED_CLOCK, new_group(parser));
  handler->reg_handler(AttrType::INTRINSIC_PARASITIC, new_group(parser));
  handler->reg_handler(AttrType::LATCH, new_latch(parser));
  handler->reg_handler(AttrType::LATCH_BANK, new_latch_bank(parser));
  handler->reg_handler(AttrType::LEAKAGE_CURRENT, new_group(parser));
  handler->reg_handler(AttrType::LEAKAGE_POWER, new_leakage_power(parser));
  handler->reg_handler(AttrType::LUT, new_group(parser));
  handler->reg_handler(AttrType::MODE_DEFINITION, new_group(parser));
  handler->reg_handler(AttrType::PIN, new_pin(parser));
  handler->reg_handler(AttrType::STATETABLE, new_statetable(parser));

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
  handler->reg_handler(AttrType::CLEAR,             fhandler);
  handler->reg_handler(AttrType::CLEAR_PRESET_VAR1, str_simple);
  handler->reg_handler(AttrType::CLEAR_PRESET_VAR2, str_simple);
  handler->reg_handler(AttrType::CLOCKED_ON,        fhandler);
  handler->reg_handler(AttrType::CLOCKED_ON_ALSO,   fhandler);
  handler->reg_handler(AttrType::NEXT_STATE,        fhandler);
  handler->reg_handler(AttrType::PRESET,            fhandler);

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
  handler->reg_handler(AttrType::CLEAR,             fhandler);
  handler->reg_handler(AttrType::CLEAR_PRESET_VAR1, str_simple);
  handler->reg_handler(AttrType::CLEAR_PRESET_VAR2, str_simple);
  handler->reg_handler(AttrType::CLOCKED_ON,        fhandler);
  handler->reg_handler(AttrType::CLOCKED_ON_ALSO,   fhandler);
  handler->reg_handler(AttrType::NEXT_STATE,        fhandler);
  handler->reg_handler(AttrType::PRESET,            fhandler);

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
  handler->reg_handler(AttrType::CLEAR,             fhandler);
  handler->reg_handler(AttrType::CLEAR_PRESET_VAR1, str_simple);
  handler->reg_handler(AttrType::CLEAR_PRESET_VAR2, str_simple);
  handler->reg_handler(AttrType::DATA_IN,           fhandler);
  handler->reg_handler(AttrType::ENABLE,            fhandler);
  handler->reg_handler(AttrType::ENABLE_ALSO,       fhandler);
  handler->reg_handler(AttrType::PRESET,            fhandler);

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
  handler->reg_handler(AttrType::CLEAR,             fhandler);
  handler->reg_handler(AttrType::CLEAR_PRESET_VAR1, str_simple);
  handler->reg_handler(AttrType::CLEAR_PRESET_VAR2, str_simple);
  handler->reg_handler(AttrType::DATA_IN,           fhandler);
  handler->reg_handler(AttrType::ENABLE,            fhandler);
  handler->reg_handler(AttrType::ENABLE_ALSO,       fhandler);
  handler->reg_handler(AttrType::PRESET,            fhandler);

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
  handler->reg_handler(AttrType::TABLE, str_simple);

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
  handler->reg_handler(AttrType::BUS_TYPE, str_simple);

  // group statements
  handler->reg_handler(AttrType::PIN, new_pin(parser));

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
  handler->reg_handler(AttrType::CAPACITANCE, flt_simple);
  handler->reg_handler(AttrType::DIRECTION,   pin_direction);
  handler->reg_handler(AttrType::FUNCTION,    func_handler);

  // complex attributes
  handler->reg_handler(AttrType::MEMBERS,     complex);

  // group statements
  handler->reg_handler(AttrType::PIN, new_pin(parser));
  handler->reg_handler(AttrType::ELECTROMIGRATION, new_group(parser));
  handler->reg_handler(AttrType::HYPERBOLIC_NOISE_ABOVE_HIGH, new_group(parser));
  handler->reg_handler(AttrType::HYPERBOLIC_NOISE_BELOW_LOW, new_group(parser));
  handler->reg_handler(AttrType::HYPERBOLIC_NOISE_HIGH, new_group(parser));
  handler->reg_handler(AttrType::HYPERBOLIC_NOISE_LOW, new_group(parser));
  handler->reg_handler(AttrType::INTERNAL_POWER, new_internal_power(parser));
  handler->reg_handler(AttrType::MAX_TRANS, new_group(parser));
  handler->reg_handler(AttrType::MIN_PULSE_WIDTH, new_group(parser));
  handler->reg_handler(AttrType::MINIMUM_PERIOD, new_group(parser));
  handler->reg_handler(AttrType::TIMING, new_timing(parser));
  handler->reg_handler(AttrType::TLATCH, new_group(parser));

  return handler;
}

// @brief 汎用の group 用のハンドラを作る．
GroupHandler*
HandlerFactory::new_group(DotlibParser& parser)
{
  return new GroupHandler(parser);
}

END_NAMESPACE_YM_DOTLIB
