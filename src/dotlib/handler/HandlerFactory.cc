
/// @file HandlerFactory.cc
/// @brief HandlerFactory の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"

#include "SimpleHandler.h"
#include "ComplexHandler.h"
#include "DefineHandler.h"
#include "GroupHandler.h"
//#include "ExprHandler.h"
//#include "FuncHandler.h"
//#include "IndexHandler.h"
//#include "UnitComplexHandler.h"
//#include "ValuesHandler.h"


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

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* flt_simple = new FloatSimpleHandler(parser);
  handler->reg_handler(ATTR_CALC_MODE,   simple);
  handler->reg_handler(ATTR_PARAMETER1,  simple);
  handler->reg_handler(ATTR_PARAMETER2,  simple);
  handler->reg_handler(ATTR_PARAMETER3,  simple);
  handler->reg_handler(ATTR_PARAMETER4,  simple);
  handler->reg_handler(ATTR_PARAMETER5,  simple);
  handler->reg_handler(ATTR_PROCESS,     flt_simple);
  handler->reg_handler(ATTR_TEMPERATURE, flt_simple);
  handler->reg_handler(ATTR_TREE_TYPE,   str_simple);
  handler->reg_handler(ATTR_VOLTAGE,     flt_simple);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(parser);
  handler->reg_handler(ATTR_POWER_RAIL, complex);

  return handler;
}

// @brief wire_load group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_wire_load(DotlibParser& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  // simple attributes
  DotlibHandler* flt_simple = new FloatSimpleHandler(parser);
  handler->reg_handler(ATTR_AREA,        flt_simple);
  handler->reg_handler(ATTR_CAPACITANCE, flt_simple);
  handler->reg_handler(ATTR_RESISTANCE,  flt_simple);
  handler->reg_handler(ATTR_SLOPE,       flt_simple);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(parser);
  handler->reg_handler(ATTR_FANOUT_LENGTH, complex);

  return handler;
}

// @brief wire_load_selection group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_wire_load_selection(DotlibParser& parser)
{
  GroupHandler* handler = new_group(parser);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(parser);
  handler->reg_handler(ATTR_WIRE_LOAD_FROM_AREA, complex);

  return handler;
}

// @brief wire_load_table group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_wire_load_table(DotlibParser& parser)
{
  GroupHandler* handler = new_group(parser);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(parser);
  handler->reg_handler(ATTR_FANOUT_AREA,        complex);
  handler->reg_handler(ATTR_FANOUT_CAPACITANCE, complex);
  handler->reg_handler(ATTR_FANOUT_LENGTH,      complex);
  handler->reg_handler(ATTR_FANOUT_RESISTANCE,  complex);

  return handler;
}

// @brief cell group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_cell(DotlibParser& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* flt_simple = new FloatSimpleHandler(parser);
  handler->reg_handler(ATTR_AREA,                         flt_simple);
  handler->reg_handler(ATTR_AUXILIARY_PAD_CELL,           simple);
  handler->reg_handler(ATTR_BASE_NAME,                    str_simple);
  handler->reg_handler(ATTR_BUS_NAMING_STYLE,             str_simple);
  handler->reg_handler(ATTR_CELL_FOOTPRINT,               str_simple);
  handler->reg_handler(ATTR_CELL_LEAKAGE_POWER,           simple);
  handler->reg_handler(ATTR_CLOCK_GATING_INTEGRATED_CELL, simple);
  handler->reg_handler(ATTR_CONTENTION_CONDITION,         simple);
  handler->reg_handler(ATTR_DONT_FAULT,                   simple);
  handler->reg_handler(ATTR_DONT_TOUCH,                   simple);
  handler->reg_handler(ATTR_DONT_USE,                     simple);
  handler->reg_handler(ATTR_DRIVER_TYPE,                  simple);
  handler->reg_handler(ATTR_EDIF_NAME,                    simple);
  handler->reg_handler(ATTR_EM_TEMP_DEGRADATION_FACTOR,   simple);
  handler->reg_handler(ATTR_FPGA_DOMAIN_STYLE,            simple);
  handler->reg_handler(ATTR_GEOMETRY_PRINT,               simple);
  handler->reg_handler(ATTR_HANDLE_NEGATIVE_CONSTRAINT,   simple);
  handler->reg_handler(ATTR_INTERFACE_TIMING,             simple);
  handler->reg_handler(ATTR_IO_TYPE,                      simple);
  handler->reg_handler(ATTR_IS_CLOCK_GATING_CELL,         simple);
  handler->reg_handler(ATTR_MAP_ONLY,                     simple);
  handler->reg_handler(ATTR_PAD_CELL,                     simple);
  handler->reg_handler(ATTR_PAD_TYPE,                     simple);
  handler->reg_handler(ATTR_POWER_CELL_TYPE,              simple);
  handler->reg_handler(ATTR_PREFERRED,                    simple);
  handler->reg_handler(ATTR_SCALING_FACTORS,              simple);
  handler->reg_handler(ATTR_SINGLE_BIT_DEGENERATE,        simple);
  handler->reg_handler(ATTR_SLEW_TYPE,                    simple);
  handler->reg_handler(ATTR_TIMING_MODEL_TYPE,            simple);
  handler->reg_handler(ATTR_USE_FOR_SIZE_ONLY,            simple);
  handler->reg_handler(ATTR_VHDL_NAME,                    simple);

  handler->reg_handler(ATTR_IS_FILLER_CELL,               simple);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(parser);
  handler->reg_handler(ATTR_PIN_OPPOSITE,                 complex);
  handler->reg_handler(ATTR_RAIL_CONNECTION,              complex);
  handler->reg_handler(ATTR_POWER_SUPPLY_NAMESTRING,      complex);
  handler->reg_handler(ATTR_RESOURCE_USAGE,               complex);

  // group statements
  handler->reg_handler(ATTR_BUS,                          new_bus(parser));
  handler->reg_handler(ATTR_BUNDLE,                       new_bundle(parser));
  handler->reg_handler(ATTR_DYNAMIC_CURRENT,              new_group(parser));
  handler->reg_handler(ATTR_FF,                           new_ff(parser));
  handler->reg_handler(ATTR_FF_BANK,                      new_ff_bank(parser));
  handler->reg_handler(ATTR_FUNCTIONAL_YIELD_METRIC,      new_group(parser));
  handler->reg_handler(ATTR_GENERATED_CLOCK,              new_group(parser));
  handler->reg_handler(ATTR_INTRINSIC_PARASITIC,          new_group(parser));
  handler->reg_handler(ATTR_LATCH,                        new_latch(parser));
  handler->reg_handler(ATTR_LATCH_BANK,                   new_latch_bank(parser));
  handler->reg_handler(ATTR_LEAKAGE_CURRENT,              new_group(parser));
  handler->reg_handler(ATTR_LEAKAGE_POWER,                new_leakage_power(parser));
  handler->reg_handler(ATTR_LUT,                          new_group(parser));
  handler->reg_handler(ATTR_MODE_DEFINITION,              new_group(parser));
  handler->reg_handler(ATTR_PIN,                          new_pin(parser));
  handler->reg_handler(ATTR_ROUTING_TRACK,                new_group(parser));
  handler->reg_handler(ATTR_STATETABLE,                   new_statetable(parser));

  handler->reg_handler(ATTR_INTERNAL_POWER,               new_cell_internal_power(parser));

  handler->reg_handler(ATTR_TEST_CELL,                    new_test_cell(parser));

  return handler;
}

// @brief leakage_power group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_leakage_power(DotlibParser& parser)
{
  GroupHandler* handler = new EmptyGroupHandler(parser);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* func_handler = new_function(parser);
  DotlibHandler* flt_simple = new FloatSimpleHandler(parser);
  handler->reg_handler(ATTR_POWER_LEVEL,    simple);
  handler->reg_handler(ATTR_RELATED_PG_PIN, str_simple);
  handler->reg_handler(ATTR_WHEN,           func_handler);
  handler->reg_handler(ATTR_VALUE,          flt_simple);

  return handler;
}

// @brief test_cell group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_test_cell(DotlibParser& parser)
{
  GroupHandler* handler = new_group(parser);

  // group statements
  handler->reg_handler(ATTR_BUS, new_bus(parser));
  handler->reg_handler(ATTR_DYNAMIC_CURRENT, new_group(parser));
  handler->reg_handler(ATTR_FF, new_ff(parser));
  handler->reg_handler(ATTR_FF_BANK, new_ff_bank(parser));
  handler->reg_handler(ATTR_FUNCTIONAL_YIELD_METRIC, new_group(parser));
  handler->reg_handler(ATTR_GENERATED_CLOCK, new_group(parser));
  handler->reg_handler(ATTR_INTRINSIC_PARASITIC, new_group(parser));
  handler->reg_handler(ATTR_LATCH, new_latch(parser));
  handler->reg_handler(ATTR_LATCH_BANK, new_latch_bank(parser));
  handler->reg_handler(ATTR_LEAKAGE_CURRENT, new_group(parser));
  handler->reg_handler(ATTR_LEAKAGE_POWER, new_leakage_power(parser));
  handler->reg_handler(ATTR_LUT, new_group(parser));
  handler->reg_handler(ATTR_MODE_DEFINITION, new_group(parser));
  handler->reg_handler(ATTR_PIN, new_pin(parser));
  handler->reg_handler(ATTR_STATETABLE, new_statetable(parser));

  return handler;
}

// @brief ff group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_ff(DotlibParser& parser)
{
  GroupHandler* handler = new Str2GroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* fhandler = new_function(parser);
  handler->reg_handler(ATTR_CLEAR,             fhandler);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR1, str_simple);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR2, str_simple);
  handler->reg_handler(ATTR_CLOCKED_ON,        fhandler);
  handler->reg_handler(ATTR_CLOCKED_ON_ALSO,   fhandler);
  handler->reg_handler(ATTR_NEXT_STATE,        fhandler);
  handler->reg_handler(ATTR_PRESET,            fhandler);

  return handler;
}

// @brief ff_bank group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_ff_bank(DotlibParser& parser)
{
  GroupHandler* handler = new Str2IntGroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* fhandler = new_function(parser);
  handler->reg_handler(ATTR_CLEAR,             fhandler);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR1, str_simple);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR2, str_simple);
  handler->reg_handler(ATTR_CLOCKED_ON,        fhandler);
  handler->reg_handler(ATTR_CLOCKED_ON_ALSO,   fhandler);
  handler->reg_handler(ATTR_NEXT_STATE,        fhandler);
  handler->reg_handler(ATTR_PRESET,            fhandler);

  return handler;
}

// @brief latch group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_latch(DotlibParser& parser)
{
  GroupHandler* handler = new Str2GroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* fhandler = new_function(parser);
  handler->reg_handler(ATTR_CLEAR,             fhandler);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR1, str_simple);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR2, str_simple);
  handler->reg_handler(ATTR_DATA_IN,           fhandler);
  handler->reg_handler(ATTR_ENABLE,            fhandler);
  handler->reg_handler(ATTR_ENABLE_ALSO,       fhandler);
  handler->reg_handler(ATTR_PRESET,            fhandler);

  return handler;
}

// @brief latch_bank group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_latch_bank(DotlibParser& parser)
{
  GroupHandler* handler = new Str2IntGroupHandler(parser);

  // simple attributes
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* fhandler = new_function(parser);
  handler->reg_handler(ATTR_CLEAR,             fhandler);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR1, str_simple);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR2, str_simple);
  handler->reg_handler(ATTR_DATA_IN,           fhandler);
  handler->reg_handler(ATTR_ENABLE,            fhandler);
  handler->reg_handler(ATTR_ENABLE_ALSO,       fhandler);
  handler->reg_handler(ATTR_PRESET,            fhandler);

  return handler;
}

// @brief statetable group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_statetable(DotlibParser& parser)
{
  GroupHandler* handler = new Str2GroupHandler(parser);

  // simple attributes
  DotlibHandler* simple = new StrSimpleHandler(parser, false);
  handler->reg_handler(ATTR_TABLE, simple);

  return handler;
}

// @brief bus group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_bus(DotlibParser& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  // simple attributes
  DotlibHandler* simple = new StrSimpleHandler(parser, false);
  handler->reg_handler(ATTR_BUS_TYPE, simple);

  // group statements
  handler->reg_handler(ATTR_PIN, new_pin(parser));

  return handler;
}

// @brief bundle group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_bundle(DotlibParser& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* flt_simple = new FloatSimpleHandler(parser);
  DotlibHandler* func_handler = new_function(parser);
  DotlibHandler* pin_direction = new_pin_direction(parser);
  handler->reg_handler(ATTR_CAPACITANCE, flt_simple);
  handler->reg_handler(ATTR_DIRECTION,   pin_direction);
  handler->reg_handler(ATTR_FUNCTION,    func_handler);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(parser);
  handler->reg_handler(ATTR_MEMBERS,     complex);

  // group statements
  handler->reg_handler(ATTR_PIN, new_pin(parser));
  handler->reg_handler(ATTR_ELECTROMIGRATION, new_group(parser));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_ABOVE_HIGH, new_group(parser));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_BELOW_LOW, new_group(parser));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_HIGH, new_group(parser));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_LOW, new_group(parser));
  handler->reg_handler(ATTR_INTERNAL_POWER, new_internal_power(parser));
  handler->reg_handler(ATTR_MAX_TRANS, new_group(parser));
  handler->reg_handler(ATTR_MIN_PULSE_WIDTH, new_group(parser));
  handler->reg_handler(ATTR_MINIMUM_PERIOD, new_group(parser));
  handler->reg_handler(ATTR_TIMING, new_timing(parser));
  handler->reg_handler(ATTR_TLATCH, new_group(parser));

  return handler;
}

// @brief 汎用の group 用のハンドラを作る．
GroupHandler*
HandlerFactory::new_group(DotlibParser& parser)
{
  return new GroupHandler(parser);
}

END_NAMESPACE_YM_DOTLIB
