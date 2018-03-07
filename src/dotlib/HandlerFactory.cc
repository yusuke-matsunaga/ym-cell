
/// @file HandlerFactory.cc
/// @brief HandlerFactory の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "HandlerFactory.h"

#include "SimpleHandler.h"
#include "ComplexHandler.h"
#include "DefineHandler.h"
#include "GroupHandler.h"
#include "ExprHandler.h"
#include "FuncHandler.h"


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

// @brief library group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_library(DotlibParserImpl& parser)
{
  GroupHandler* handler = new Str1GroupHandler(parser);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(handler, false);
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* symstr_simple = new StrSimpleHandler(handler, true);
  DotlibHandler* flt_simple = new FloatSimpleHandler(handler);

  handler->reg_handler(ATTR_BUS_NAMING_STYLE,                       str_simple);
  handler->reg_handler(ATTR_COMMENT,                                str_simple);
  handler->reg_handler(ATTR_CURRENT_UNIT,                           symstr_simple);
  handler->reg_handler(ATTR_DATE,                                   str_simple);
  handler->reg_handler(ATTR_DELAY_MODEL,                            new DelayModelHandler(handler));
  handler->reg_handler(ATTR_EM_TEMP_DEGRADATION_FACTOR,             flt_simple);
  handler->reg_handler(ATTR_FPGA_TECHNOLOGY,                        str_simple);
  handler->reg_handler(ATTR_IN_PLACE_SWAP_MODE,                     str_simple);
  handler->reg_handler(ATTR_INPUT_THRESHOLD_PCT_FALL,               simple);
  handler->reg_handler(ATTR_INPUT_THRESHOLD_PCT_RISE,               simple);
  handler->reg_handler(ATTR_LEAKAGE_POWER_UNIT,                     symstr_simple);
  handler->reg_handler(ATTR_NOM_CALC_MODE,                          str_simple);
  handler->reg_handler(ATTR_NOM_PROCESS,                            flt_simple);
  handler->reg_handler(ATTR_NOM_TEMPERATURE,                        flt_simple);
  handler->reg_handler(ATTR_NOM_VOLTAGE,                            flt_simple);
  handler->reg_handler(ATTR_OUTPUT_THRESHOLD_PCT_FALL,              simple);
  handler->reg_handler(ATTR_OUTPUT_THRESHOLD_PCT_RISE,              simple);
  handler->reg_handler(ATTR_PIECE_TYPE,                             str_simple);
  handler->reg_handler(ATTR_POWER_MODEL,                            str_simple);
  handler->reg_handler(ATTR_PREFERRED_INPUT_PAD_VOLTAGE,            str_simple);
  handler->reg_handler(ATTR_PREFERRED_OUTPUT_PAD_VOLTAGE,           str_simple);
  handler->reg_handler(ATTR_PREFERRED_OUTPUT_PAD_SLEW_RATE_CONTROL, str_simple);
  handler->reg_handler(ATTR_PULLING_RESISTANCE_UNIT,                symstr_simple);
  handler->reg_handler(ATTR_REVISION,                               symstr_simple);
  handler->reg_handler(ATTR_SIMULATION,                             str_simple);
  handler->reg_handler(ATTR_SLEW_DERATE_FROM_LIBRARY,               simple);
  handler->reg_handler(ATTR_SLEW_LOWER_THRESHOLD_PCT_FALL,          simple);
  handler->reg_handler(ATTR_SLEW_LOWER_THRESHOLD_PCT_RISE,          simple);
  handler->reg_handler(ATTR_SLEW_UPPER_THRESHOLD_PCT_FALL,          simple);
  handler->reg_handler(ATTR_SLEW_UPPER_THRESHOLD_PCT_RISE,          simple);
  handler->reg_handler(ATTR_TIME_UNIT,                              symstr_simple);
  handler->reg_handler(ATTR_VOLTAGE_UNIT,                           symstr_simple);

  // default attributes
  handler->reg_handler(ATTR_DEFAULT_CELL_LEAKAGE_POWER,             flt_simple);
  handler->reg_handler(ATTR_DEFAULT_CONNECTION_CLASS,               str_simple);
  handler->reg_handler(ATTR_DEFAULT_FALL_DELAY_INTERCEPT,           flt_simple);
  handler->reg_handler(ATTR_DEFAULT_FALL_PIN_RESISTANCE,            flt_simple);
  handler->reg_handler(ATTR_DEFAULT_FANOUT_LOAD,                    flt_simple);
  handler->reg_handler(ATTR_DEFAULT_INOUT_PIN_CAP,                  flt_simple);
  handler->reg_handler(ATTR_DEFAULT_INOUT_PIN_FALL_RES,             flt_simple);
  handler->reg_handler(ATTR_DEFAULT_INOUT_PIN_RISE_RES,             flt_simple);
  handler->reg_handler(ATTR_DEFAULT_INPUT_PIN_CAP,                  flt_simple);
  handler->reg_handler(ATTR_DEFAULT_INTRINSIC_FALL,                 flt_simple);
  handler->reg_handler(ATTR_DEFAULT_INTRINSIC_RISE,                 flt_simple);
  handler->reg_handler(ATTR_DEFAULT_LEAKAGE_POWER_DENSITY,          flt_simple);
  handler->reg_handler(ATTR_DEFAULT_MAX_CAPACITANCE,                flt_simple);
  handler->reg_handler(ATTR_DEFAULT_MAX_FANOUT,                     flt_simple);
  handler->reg_handler(ATTR_DEFAULT_MAX_TRANSITION,                 flt_simple);
  handler->reg_handler(ATTR_DEFAULT_MAX_UTILIZATION,                flt_simple);
  handler->reg_handler(ATTR_DEFAULT_MIN_POROSITY,                   flt_simple);
  handler->reg_handler(ATTR_DEFAULT_OPERATING_CONDITIONS,           str_simple);
  handler->reg_handler(ATTR_DEFAULT_OUTPUT_PIN_CAP,                 flt_simple);
  handler->reg_handler(ATTR_DEFAULT_OUTPUT_PIN_FALL_RES,            flt_simple);
  handler->reg_handler(ATTR_DEFAULT_OUTPUT_PIN_RISE_RES,            flt_simple);
  handler->reg_handler(ATTR_DEFAULT_RISE_DELAY_INTERCEPT,           flt_simple);
  handler->reg_handler(ATTR_DEFAULT_RISE_PIN_RESISTANCE,            flt_simple);
  handler->reg_handler(ATTR_DEFAULT_SLOPE_FALL,                     flt_simple);
  handler->reg_handler(ATTR_DEFAULT_SLOPE_RISE,                     flt_simple);
  handler->reg_handler(ATTR_DEFAULT_WIRE_LOAD,                      str_simple);
  handler->reg_handler(ATTR_DEFAULT_WIRE_LOAD_AREA,                 flt_simple);
  handler->reg_handler(ATTR_DEFAULT_WIRE_LOAD_CAPACITANCE,          flt_simple);
  handler->reg_handler(ATTR_DEFAULT_WIRE_LOAD_MODE,                 str_simple);
  handler->reg_handler(ATTR_DEFAULT_WIRE_LOAD_RESISTANCE,           flt_simple);
  handler->reg_handler(ATTR_DEFAULT_WIRE_LOAD_SELECTION,            str_simple);

  // scaling attributes
  handler->reg_handler(ATTR_K_PROCESS_CELL_FALL,                    flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_CELL_LEAKAGE_POWER,           flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_CELL_RISE,                    flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_DRIVE_CURRENT,                flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_DRIVE_FALL,                   flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_DRIVE_RISE,                   flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_FALL_DELAY_INTERCEPT,         flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_FALL_PIN_RESISTANCE,          flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_FALL_PROPAGATION,             flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_FALL_TRANSITION,              flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_HOLD_FALL,                    flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_HOLD_RISE,                    flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_INTERNAL_POWER,               flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_INTRINSIC_FALL,               flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_INTRINSIC_RISE,               flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_MIN_PERIOD,                   flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_MIN_PULSE_WIDTH_HIGH,         flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_MIN_PULSE_WIDTH_LOW,          flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_NOCHANGE_FALL,                flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_NOCHANGE_RISE,                flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_PIN_CAP,                      flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_RECOVERY_FALL,                flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_RECOVERY_RISE,                flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_REMOVAL_FALL,                 flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_REMOVAL_RISE,                 flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_RISE_DELAY_INTERCEPT,         flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_RISE_PIN_RESISTANCE,          flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_RISE_PROPAGATION,             flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_RISE_TRANSITION,              flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_SETUP_FALL,                   flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_SETUP_RISE,                   flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_SKEW_FALL,                    flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_SKEW_RISE,                    flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_SLOPE_FALL,                   flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_SLOPE_RISE,                   flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_WIRE_CAP,                     flt_simple);
  handler->reg_handler(ATTR_K_PROCESS_WIRE_RES,                     flt_simple);
  handler->reg_handler(ATTR_K_TEMP_CELL_FALL,                       flt_simple);
  handler->reg_handler(ATTR_K_TEMP_CELL_LEAKAGE_POWER,              flt_simple);
  handler->reg_handler(ATTR_K_TEMP_CELL_RISE,                       flt_simple);
  handler->reg_handler(ATTR_K_TEMP_DRIVE_CURRENT,                   flt_simple);
  handler->reg_handler(ATTR_K_TEMP_DRIVE_FALL,                      flt_simple);
  handler->reg_handler(ATTR_K_TEMP_DRIVE_RISE,                      flt_simple);
  handler->reg_handler(ATTR_K_TEMP_FALL_DELAY_INTERCEPT,            flt_simple);
  handler->reg_handler(ATTR_K_TEMP_FALL_PIN_RESISTANCE,             flt_simple);
  handler->reg_handler(ATTR_K_TEMP_FALL_PROPAGATION,                flt_simple);
  handler->reg_handler(ATTR_K_TEMP_FALL_TRANSITION,                 flt_simple);
  handler->reg_handler(ATTR_K_TEMP_HOLD_FALL,                       flt_simple);
  handler->reg_handler(ATTR_K_TEMP_HOLD_RISE,                       flt_simple);
  handler->reg_handler(ATTR_K_TEMP_INTERNAL_POWER,                  flt_simple);
  handler->reg_handler(ATTR_K_TEMP_INTRINSIC_FALL,                  flt_simple);
  handler->reg_handler(ATTR_K_TEMP_INTRINSIC_RISE,                  flt_simple);
  handler->reg_handler(ATTR_K_TEMP_MIN_PERIOD,                      flt_simple);
  handler->reg_handler(ATTR_K_TEMP_MIN_PULSE_WIDTH_HIGH,            flt_simple);
  handler->reg_handler(ATTR_K_TEMP_MIN_PULSE_WIDTH_LOW,             flt_simple);
  handler->reg_handler(ATTR_K_TEMP_NOCHANGE_FALL,                   flt_simple);
  handler->reg_handler(ATTR_K_TEMP_NOCHANGE_RISE,                   flt_simple);
  handler->reg_handler(ATTR_K_TEMP_PIN_CAP,                         flt_simple);
  handler->reg_handler(ATTR_K_TEMP_RECOVERY_FALL,                   flt_simple);
  handler->reg_handler(ATTR_K_TEMP_RECOVERY_RISE,                   flt_simple);
  handler->reg_handler(ATTR_K_TEMP_REMOVAL_FALL,                    flt_simple);
  handler->reg_handler(ATTR_K_TEMP_REMOVAL_RISE,                    flt_simple);
  handler->reg_handler(ATTR_K_TEMP_RISE_DELAY_INTERCEPT,            flt_simple);
  handler->reg_handler(ATTR_K_TEMP_RISE_PIN_RESISTANCE,             flt_simple);
  handler->reg_handler(ATTR_K_TEMP_RISE_PROPAGATION,                flt_simple);
  handler->reg_handler(ATTR_K_TEMP_RISE_TRANSITION,                 flt_simple);
  handler->reg_handler(ATTR_K_TEMP_SETUP_FALL,                      flt_simple);
  handler->reg_handler(ATTR_K_TEMP_SETUP_RISE,                      flt_simple);
  handler->reg_handler(ATTR_K_TEMP_SKEW_FALL,                       flt_simple);
  handler->reg_handler(ATTR_K_TEMP_SKEW_RISE,                       flt_simple);
  handler->reg_handler(ATTR_K_TEMP_SLOPE_FALL,                      flt_simple);
  handler->reg_handler(ATTR_K_TEMP_SLOPE_RISE,                      flt_simple);
  handler->reg_handler(ATTR_K_TEMP_WIRE_CAP,                        flt_simple);
  handler->reg_handler(ATTR_K_TEMP_WIRE_RES,                        flt_simple);
  handler->reg_handler(ATTR_K_VOLT_CELL_FALL,                       flt_simple);
  handler->reg_handler(ATTR_K_VOLT_CELL_LEAKAGE_POWER,              flt_simple);
  handler->reg_handler(ATTR_K_VOLT_CELL_RISE,                       flt_simple);
  handler->reg_handler(ATTR_K_VOLT_DRIVE_CURRENT,                   flt_simple);
  handler->reg_handler(ATTR_K_VOLT_DRIVE_FALL,                      flt_simple);
  handler->reg_handler(ATTR_K_VOLT_DRIVE_RISE,                      flt_simple);
  handler->reg_handler(ATTR_K_VOLT_FALL_DELAY_INTERCEPT,            flt_simple);
  handler->reg_handler(ATTR_K_VOLT_FALL_PIN_RESISTANCE,             flt_simple);
  handler->reg_handler(ATTR_K_VOLT_FALL_PROPAGATION,                flt_simple);
  handler->reg_handler(ATTR_K_VOLT_FALL_TRANSITION,                 flt_simple);
  handler->reg_handler(ATTR_K_VOLT_HOLD_FALL,                       flt_simple);
  handler->reg_handler(ATTR_K_VOLT_HOLD_RISE,                       flt_simple);
  handler->reg_handler(ATTR_K_VOLT_INTERNAL_POWER,                  flt_simple);
  handler->reg_handler(ATTR_K_VOLT_INTRINSIC_FALL,                  flt_simple);
  handler->reg_handler(ATTR_K_VOLT_INTRINSIC_RISE,                  flt_simple);
  handler->reg_handler(ATTR_K_VOLT_MIN_PERIOD,                      flt_simple);
  handler->reg_handler(ATTR_K_VOLT_MIN_PULSE_WIDTH_HIGH,            flt_simple);
  handler->reg_handler(ATTR_K_VOLT_MIN_PULSE_WIDTH_LOW,             flt_simple);
  handler->reg_handler(ATTR_K_VOLT_NOCHANGE_FALL,                   flt_simple);
  handler->reg_handler(ATTR_K_VOLT_NOCHANGE_RISE,                   flt_simple);
  handler->reg_handler(ATTR_K_VOLT_PIN_CAP,                         flt_simple);
  handler->reg_handler(ATTR_K_VOLT_RECOVERY_FALL,                   flt_simple);
  handler->reg_handler(ATTR_K_VOLT_RECOVERY_RISE,                   flt_simple);
  handler->reg_handler(ATTR_K_VOLT_REMOVAL_FALL,                    flt_simple);
  handler->reg_handler(ATTR_K_VOLT_REMOVAL_RISE,                    flt_simple);
  handler->reg_handler(ATTR_K_VOLT_RISE_DELAY_INTERCEPT,            flt_simple);
  handler->reg_handler(ATTR_K_VOLT_RISE_PIN_RESISTANCE,             flt_simple);
  handler->reg_handler(ATTR_K_VOLT_RISE_PROPAGATION,                flt_simple);
  handler->reg_handler(ATTR_K_VOLT_RISE_TRANSITION,                 flt_simple);
  handler->reg_handler(ATTR_K_VOLT_SETUP_FALL,                      flt_simple);
  handler->reg_handler(ATTR_K_VOLT_SETUP_RISE,                      flt_simple);
  handler->reg_handler(ATTR_K_VOLT_SKEW_FALL,                       flt_simple);
  handler->reg_handler(ATTR_K_VOLT_SKEW_RISE,                       flt_simple);
  handler->reg_handler(ATTR_K_VOLT_SLOPE_FALL,                      flt_simple);
  handler->reg_handler(ATTR_K_VOLT_SLOPE_RISE,                      flt_simple);
  handler->reg_handler(ATTR_K_VOLT_WIRE_CAP,                        flt_simple);
  handler->reg_handler(ATTR_K_VOLT_WIRE_RES,                        flt_simple);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(handler);
  DotlibHandler* str1_complex = new Str1ComplexHandler(handler);
  DotlibHandler* unit_complex = new UnitComplexHandler(handler);
  DotlibHandler* define = new DefineHandler(handler);
  handler->reg_handler(ATTR_CAPACITIVE_LOAD_UNIT,                   unit_complex);
  handler->reg_handler(ATTR_DEFAULT_PART,                           complex);
  handler->reg_handler(ATTR_DEFINE,                                 define);
  handler->reg_handler(ATTR_DEFINE_CELL_AREA,                       complex);
  handler->reg_handler(ATTR_DEFINE_GROUP,                           complex);
  handler->reg_handler(ATTR_LIBRARY_FEATURES,                       str1_complex);
  handler->reg_handler(ATTR_PIECE_DEFINE,                           str1_complex);
  handler->reg_handler(ATTR_ROUTING_LAYERS,                         complex);
  handler->reg_handler(ATTR_TECHNOLOGY,                             str1_complex);

  //fall_net_delay : name ;
  //rise_net_delay : name ;

  // group statements
  handler->reg_handler(ATTR_CELL,
		       new_cell(handler));
  handler->reg_handler(ATTR_DC_CURRENT_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_EM_LUT_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_FALL_TRANSITION_DEGRADATION,
		       new_group(handler));
  handler->reg_handler(ATTR_FAULTS_LUT_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_INPUT_VOLTAGE,
		       new_input_voltage(handler));
  handler->reg_handler(ATTR_IV_LUT_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_LU_TABLE_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_NOISE_LUT_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_OPERATING_CONDITIONS,
		       new_operating_conditions(handler));
  handler->reg_handler(ATTR_OUTPUT_CURRENT_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_OUTPUT_VOLTAGE,
		       new_output_voltage(handler));
  handler->reg_handler(ATTR_PART,
		       new_group(handler));
  handler->reg_handler(ATTR_POLY_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_POWER_LUT_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_POWER_POLY_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_POWER_SUPPLY,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATION_LUT_TEMPLATE,
		       new_template(handler));
  handler->reg_handler(ATTR_RISE_TRANSITION_DEGRADATION,
		       new_group(handler));
  handler->reg_handler(ATTR_SCALED_CELL,
		       new_group(handler));
  handler->reg_handler(ATTR_SCALING_FACTORS,
		       new_group(handler));
  handler->reg_handler(ATTR_TIMING,
		       new_group(handler));
  handler->reg_handler(ATTR_TIMING_RANGE,
		       new_group(handler));
  handler->reg_handler(ATTR_TYPE,
		       new_group(handler));
  handler->reg_handler(ATTR_WIRE_LOAD,
		       new_wire_load(handler));
  handler->reg_handler(ATTR_WIRE_LOAD_SELECTION,
		       new_wire_load_selection(handler));
  handler->reg_handler(ATTR_WIRE_LOAD_TABLE,
		       new_wire_load_table(handler));

  return handler;
}

// @brief input_voltage group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_input_voltage(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes
  DotlibHandler* expr_handler = new ExprHandler(handler);
  handler->reg_handler(ATTR_VIL,   expr_handler);
  handler->reg_handler(ATTR_VIH,   expr_handler);
  handler->reg_handler(ATTR_VIMIN, expr_handler);
  handler->reg_handler(ATTR_VIMAX, expr_handler);

  return handler;
}

// @brief output_voltage group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_output_voltage(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes
  DotlibHandler* expr_handler = new ExprHandler(handler);
  handler->reg_handler(ATTR_VOL,   expr_handler);
  handler->reg_handler(ATTR_VOH,   expr_handler);
  handler->reg_handler(ATTR_VOMIN, expr_handler);
  handler->reg_handler(ATTR_VOMAX, expr_handler);

  return handler;
}

// @brief operating_conditions group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_operating_conditions(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(handler, false);
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* flt_simple = new FloatSimpleHandler(handler);
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
  DotlibHandler* complex = new ComplexHandler(handler);
  handler->reg_handler(ATTR_POWER_RAIL, complex);

  return handler;
}

// @brief template group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_template(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes
  DotlibHandler* var_type = new VarTypeHandler(handler);
  handler->reg_handler(ATTR_VARIABLE_1, var_type);
  handler->reg_handler(ATTR_VARIABLE_2, var_type);
  handler->reg_handler(ATTR_VARIABLE_3, var_type);

  // complex attributes
  DotlibHandler* index_handler = new VectorComplexHandler(handler);
  handler->reg_handler(ATTR_INDEX_1,    index_handler);
  handler->reg_handler(ATTR_INDEX_2,    index_handler);
  handler->reg_handler(ATTR_INDEX_3,    index_handler);

  // group statements
  handler->reg_handler(ATTR_DOMAIN, new_group(handler));

  return handler;
}

// @brief wire_load group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_wire_load(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes
  DotlibHandler* flt_simple = new FloatSimpleHandler(handler);
  handler->reg_handler(ATTR_AREA,        flt_simple);
  handler->reg_handler(ATTR_CAPACITANCE, flt_simple);
  handler->reg_handler(ATTR_RESISTANCE,  flt_simple);
  handler->reg_handler(ATTR_SLOPE,       flt_simple);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(handler);
  handler->reg_handler(ATTR_FANOUT_LENGTH, complex);

  return handler;
}

// @brief wire_load_selection group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_wire_load_selection(GroupHandler* parent)
{
  GroupHandler* handler = new GroupHandler(parent);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(handler);
  handler->reg_handler(ATTR_WIRE_LOAD_FROM_AREA, complex);

  return handler;
}

// @brief wire_load_table group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_wire_load_table(GroupHandler* parent)
{
  GroupHandler* handler = new_group(parent);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(handler);
  handler->reg_handler(ATTR_FANOUT_AREA,        complex);
  handler->reg_handler(ATTR_FANOUT_CAPACITANCE, complex);
  handler->reg_handler(ATTR_FANOUT_LENGTH,      complex);
  handler->reg_handler(ATTR_FANOUT_RESISTANCE,  complex);

  return handler;
}

// @brief cell group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_cell(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(handler, false);
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* flt_simple = new FloatSimpleHandler(handler);
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
  DotlibHandler* complex = new ComplexHandler(handler);
  handler->reg_handler(ATTR_PIN_OPPOSITE,                 complex);
  handler->reg_handler(ATTR_RAIL_CONNECTION,              complex);
  handler->reg_handler(ATTR_POWER_SUPPLY_NAMESTRING,      complex);
  handler->reg_handler(ATTR_RESOURCE_USAGE,               complex);

  // group statements
  handler->reg_handler(ATTR_BUS,                          new_bus(handler));
  handler->reg_handler(ATTR_BUNDLE,                       new_bundle(handler));
  handler->reg_handler(ATTR_DYNAMIC_CURRENT,              new_group(handler));
  handler->reg_handler(ATTR_FF,                           new_ff(handler));
  handler->reg_handler(ATTR_FF_BANK,                      new_ff_bank(handler));
  handler->reg_handler(ATTR_FUNCTIONAL_YIELD_METRIC,      new_group(handler));
  handler->reg_handler(ATTR_GENERATED_CLOCK,              new_group(handler));
  handler->reg_handler(ATTR_INTRINSIC_PARASITIC,          new_group(handler));
  handler->reg_handler(ATTR_LATCH,                        new_latch(handler));
  handler->reg_handler(ATTR_LATCH_BANK,                   new_latch_bank(handler));
  handler->reg_handler(ATTR_LEAKAGE_CURRENT,              new_group(handler));
  handler->reg_handler(ATTR_LEAKAGE_POWER,                new_leakage_power(handler));
  handler->reg_handler(ATTR_LUT,                          new_group(handler));
  handler->reg_handler(ATTR_MODE_DEFINITION,              new_group(handler));
  handler->reg_handler(ATTR_PIN,                          new_pin(handler));
  handler->reg_handler(ATTR_ROUTING_TRACK,                new_group(handler));
  handler->reg_handler(ATTR_STATETABLE,                   new_statetable(handler));

  handler->reg_handler(ATTR_INTERNAL_POWER, new_cell_internal_power(handler));

  handler->reg_handler(ATTR_TEST_CELL,                    new_test_cell(handler));

  return handler;
}

// @brief leakage_power group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_leakage_power(GroupHandler* parent)
{
  GroupHandler* handler = new EmptyGroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(handler, false);
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* func_handler = new FuncHandler(handler);
  DotlibHandler* flt_simple = new FloatSimpleHandler(handler);
  handler->reg_handler(ATTR_POWER_LEVEL,    simple);
  handler->reg_handler(ATTR_RELATED_PG_PIN, str_simple);
  handler->reg_handler(ATTR_WHEN,           func_handler);
  handler->reg_handler(ATTR_VALUE,          flt_simple);

  return handler;
}

// @brief test_cell group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_test_cell(GroupHandler* parent)
{
  GroupHandler* handler = new_group(parent);

  // group statements
  handler->reg_handler(ATTR_BUS, new_bus(handler));
  handler->reg_handler(ATTR_DYNAMIC_CURRENT, new_group(handler));
  handler->reg_handler(ATTR_FF, new_ff(handler));
  handler->reg_handler(ATTR_FF_BANK, new_ff_bank(handler));
  handler->reg_handler(ATTR_FUNCTIONAL_YIELD_METRIC, new_group(handler));
  handler->reg_handler(ATTR_GENERATED_CLOCK, new_group(handler));
  handler->reg_handler(ATTR_INTRINSIC_PARASITIC, new_group(handler));
  handler->reg_handler(ATTR_LATCH, new_latch(handler));
  handler->reg_handler(ATTR_LATCH_BANK, new_latch_bank(handler));
  handler->reg_handler(ATTR_LEAKAGE_CURRENT, new_group(handler));
  handler->reg_handler(ATTR_LEAKAGE_POWER, new_leakage_power(handler));
  handler->reg_handler(ATTR_LUT, new_group(handler));
  handler->reg_handler(ATTR_MODE_DEFINITION, new_group(handler));
  handler->reg_handler(ATTR_PIN, new_pin(handler));
  handler->reg_handler(ATTR_STATETABLE, new_statetable(handler));

  return handler;
}

// @brief ff group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_ff(GroupHandler* parent)
{
  GroupHandler* handler = new Str2GroupHandler(parent);

  // simple attributes
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* fhandler = new FuncHandler(handler);
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
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_ff_bank(GroupHandler* parent)
{
  GroupHandler* handler = new Str2IntGroupHandler(parent);

  // simple attributes
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* fhandler = new FuncHandler(handler);
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
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_latch(GroupHandler* parent)
{
  GroupHandler* handler = new Str2GroupHandler(parent);

  // simple attributes
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* fhandler = new FuncHandler(handler);
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
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_latch_bank(GroupHandler* parent)
{
  GroupHandler* handler = new Str2IntGroupHandler(parent);

  // simple attributes
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* fhandler = new FuncHandler(handler);
  handler->reg_handler(ATTR_CLEAR,             fhandler);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR1, str_simple);
  handler->reg_handler(ATTR_CLEAR_PRESET_VAR2, str_simple);
  handler->reg_handler(ATTR_DATA_IN,           fhandler);
  handler->reg_handler(ATTR_ENABLE,            fhandler);
  handler->reg_handler(ATTR_ENABLE_ALSO,       fhandler);
  handler->reg_handler(ATTR_PRESET,            fhandler);

  return handler;
}

// @brief cell 内の internal_power group 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_cell_internal_power(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(handler, false);
  handler->reg_handler(ATTR_RELATED_INPUTS, simple);
  handler->reg_handler(ATTR_RELATED_OUTPUTS, simple);

  // complex attribute
  DotlibHandler* complex = new ComplexHandler(handler);
  handler->reg_handler(ATTR_VALUES, complex);

  return handler;
}

// @brief power group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_power(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes

  // complex attribute
  DotlibHandler* index_handler = new VectorComplexHandler(handler);
  DotlibHandler* value_handler = new VectorListComplexHandler(handler);
  DotlibHandler* complex = new ComplexHandler(handler);
  handler->reg_handler(ATTR_INDEX_1, index_handler);
  handler->reg_handler(ATTR_INDEX_2, index_handler);
  handler->reg_handler(ATTR_INDEX_3, index_handler);
  handler->reg_handler(ATTR_VALUES,  value_handler);

  handler->reg_handler(ATTR_ORDERS,  complex);
  handler->reg_handler(ATTR_COEFS,   complex);

  // group statements
  handler->reg_handler(ATTR_DOMAIN, new_group(handler));

  return handler;
}

// @brief statetable group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_statetable(GroupHandler* parent)
{
  GroupHandler* handler = new Str2GroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new StrSimpleHandler(handler, false);
  handler->reg_handler(ATTR_TABLE, simple);

  return handler;
}

// @brief bus group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_bus(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new StrSimpleHandler(handler, false);
  handler->reg_handler(ATTR_BUS_TYPE, simple);

  // group statements
  handler->reg_handler(ATTR_PIN, new_pin(handler));

  return handler;
}

// @brief bundle group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_bundle(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(handler, false);
  DotlibHandler* flt_simple = new FloatSimpleHandler(handler);
  DotlibHandler* func_handler = new FuncHandler(handler);
  handler->reg_handler(ATTR_CAPACITANCE, flt_simple);
  handler->reg_handler(ATTR_DIRECTION,   new CellPinDirectionHandler(handler));
  handler->reg_handler(ATTR_FUNCTION,    func_handler);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(handler);
  handler->reg_handler(ATTR_MEMBERS,     complex);

  // group statements
  handler->reg_handler(ATTR_PIN, new_pin(handler));
  handler->reg_handler(ATTR_ELECTROMIGRATION, new_group(handler));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_ABOVE_HIGH, new_group(handler));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_BELOW_LOW, new_group(handler));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_HIGH, new_group(handler));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_LOW, new_group(handler));
  handler->reg_handler(ATTR_INTERNAL_POWER, new_internal_power(handler));
  handler->reg_handler(ATTR_MAX_TRANS, new_group(handler));
  handler->reg_handler(ATTR_MIN_PULSE_WIDTH, new_group(handler));
  handler->reg_handler(ATTR_MINIMUM_PERIOD, new_group(handler));
  handler->reg_handler(ATTR_TIMING, new_timing(handler));
  handler->reg_handler(ATTR_TLATCH, new_group(handler));

  return handler;
}

// @brief pin group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_pin(GroupHandler* parent)
{
  GroupHandler* handler = new GroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(handler, false);
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* flt_simple = new FloatSimpleHandler(handler);
  DotlibHandler* func_handler = new FuncHandler(handler);
  handler->reg_handler(ATTR_BIT_WIDTH, simple);
  handler->reg_handler(ATTR_CAPACITANCE,                         flt_simple);
  handler->reg_handler(ATTR_CLOCK,                               simple);
  handler->reg_handler(ATTR_CLOCK_GATE_CLOCK_PIN,                simple);
  handler->reg_handler(ATTR_CLOCK_GATE_ENABLE_PIN,               simple);
  handler->reg_handler(ATTR_CLOCK_GATE_TEST_PIN,                 simple);
  handler->reg_handler(ATTR_CLOCK_GATE_OBS_PIN,                  simple);
  handler->reg_handler(ATTR_CLOCK_GATE_OUT_PIN,                  simple);
  handler->reg_handler(ATTR_COMPLEMENTARY_PIN,                   simple);
  handler->reg_handler(ATTR_CONNECTION_CLASS,                    simple);
  handler->reg_handler(ATTR_DIRECTION,                           new CellPinDirectionHandler(handler));
  handler->reg_handler(ATTR_DONT_FAULT,                          simple);
  handler->reg_handler(ATTR_DRIVE_CURRENT,                       simple);
  handler->reg_handler(ATTR_DRIVER_TYPE,                         simple);
  handler->reg_handler(ATTR_FALL_CAPACITANCE,                    simple);
  handler->reg_handler(ATTR_FALL_CURRENT_SLOPE_AFTER_THRESHOLD,  simple);
  handler->reg_handler(ATTR_FALL_CURRENT_SLOPE_BEFORE_THRESHOLD, simple);
  handler->reg_handler(ATTR_FALL_TIME_AFTER_THRESHOLD,           simple);
  handler->reg_handler(ATTR_FALL_TIME_BEFORE_THRESHOLD,          simple);
  handler->reg_handler(ATTR_FANOUT_LOAD,                         flt_simple);
  handler->reg_handler(ATTR_FAULT_MODEL,                         simple);
  handler->reg_handler(ATTR_FUNCTION,                            func_handler);
  handler->reg_handler(ATTR_HAS_BUILTIN_PAD,                     simple);
  handler->reg_handler(ATTR_HYSTERESIS,                          simple);
  handler->reg_handler(ATTR_INPUT_MAP,                           simple);
  handler->reg_handler(ATTR_INPUT_SIGNAL_LEVEL,                  simple);
  handler->reg_handler(ATTR_INPUT_VOLTAGE,                       simple);
  handler->reg_handler(ATTR_INTERNAL_NODE,                       simple);
  handler->reg_handler(ATTR_INVERTED_OUTPUT,                     simple);
  handler->reg_handler(ATTR_IS_PAD,                              simple);
  handler->reg_handler(ATTR_MAX_CAPACITANCE,                     flt_simple);
  handler->reg_handler(ATTR_MAX_FANOUT,                          flt_simple);
  handler->reg_handler(ATTR_MAX_INPUT_NOISE_WIDTH,               simple);
  handler->reg_handler(ATTR_MAX_TRANSITION,                      flt_simple);
  handler->reg_handler(ATTR_MIN_CAPACITANCE,                     flt_simple);
  handler->reg_handler(ATTR_MIN_FANOUT,                          flt_simple);
  handler->reg_handler(ATTR_MIN_INPUT_NOISE_WIDTH,               simple);
  handler->reg_handler(ATTR_MIN_PERIOD,                          simple);
  handler->reg_handler(ATTR_MIN_PULSE_WIDTH_HIGH,                simple);
  handler->reg_handler(ATTR_MIN_PULSE_WIDTH_LOW,                 simple);
  handler->reg_handler(ATTR_MIN_TRANSITION,                      flt_simple);
  handler->reg_handler(ATTR_MULTICELL_PAD_PIN,                   simple);
  handler->reg_handler(ATTR_NEXTSTATE_TYPE,                      simple);
  handler->reg_handler(ATTR_OUTPUT_SIGNAL_LEVEL,                 simple);
  handler->reg_handler(ATTR_OUTPUT_VOLTAGE,                      flt_simple);
  handler->reg_handler(ATTR_PIN_FUNC_TYPE,                       simple);
  handler->reg_handler(ATTR_PREFER_TIED,                         simple);
  handler->reg_handler(ATTR_PRIMARY_OUTPUT,                      simple);
  handler->reg_handler(ATTR_PULLING_CURRENT,                     flt_simple);
  handler->reg_handler(ATTR_PULLING_RESISTANCE,                  flt_simple);
  handler->reg_handler(ATTR_RISE_CAPACITANCE,                    flt_simple);
  handler->reg_handler(ATTR_RISE_CURRENT_SLOPE_AFTER_THRESHOLD,  flt_simple);
  handler->reg_handler(ATTR_RISE_CURRENT_SLOPE_BEFORE_THRESHOLD, flt_simple);
  handler->reg_handler(ATTR_RISE_TIME_AFTER_THRESHOLD,           flt_simple);
  handler->reg_handler(ATTR_RISE_TIME_BEFORE_THRESHOLD,          flt_simple);
  handler->reg_handler(ATTR_SIGNAL_TYPE,                         simple);
  handler->reg_handler(ATTR_SLEW_CONTROL,                        simple);
  handler->reg_handler(ATTR_STATE_FUNCTION,                      simple);
  handler->reg_handler(ATTR_TEST_OUTPUT_ONLY,                    simple);
  handler->reg_handler(ATTR_THREE_STATE,
		       new FuncHandler(handler));
  handler->reg_handler(ATTR_VHDL_NAME,                           str_simple);
  handler->reg_handler(ATTR_X_FUNCTION,                          simple);

  // complex attributes
  DotlibHandler* complex = new ComplexHandler(handler);
  handler->reg_handler(ATTR_FALL_CAPACITANCE_RANGE,              complex);
  handler->reg_handler(ATTR_RISE_CAPACITANCE_RANGE,              complex);

  // group statements
  handler->reg_handler(ATTR_ELECTROMIGRATION, new_group(handler));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_ABOVE_HIGH, new_group(handler));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_BELOW_LOW, new_group(handler));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_HIGH, new_group(handler));
  handler->reg_handler(ATTR_HYPERBOLIC_NOISE_LOW, new_group(handler));
  handler->reg_handler(ATTR_INTERNAL_POWER, new_internal_power(handler));
  handler->reg_handler(ATTR_MAX_TRANS, new_group(handler));
  handler->reg_handler(ATTR_MIN_PULSE_WIDTH, new_group(handler));
  handler->reg_handler(ATTR_MINIMUM_PERIOD, new_group(handler));
  handler->reg_handler(ATTR_TIMING, new_timing(handler));
  handler->reg_handler(ATTR_TLATCH, new_group(handler));

  return handler;
}

// @brief internal_power group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_internal_power(GroupHandler* parent)
{
  GroupHandler* handler = new EmptyGroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(handler, false);
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* func_handler = new FuncHandler(handler);
  handler->reg_handler(ATTR_EQUAL_OR_OPPOSITE_OUTPUT, simple);
  handler->reg_handler(ATTR_FALLING_TOGETHER_GROUP,   simple);
  handler->reg_handler(ATTR_POWER_LEVEL,              simple);
  handler->reg_handler(ATTR_RELATED_PIN,              str_simple);
  handler->reg_handler(ATTR_RISING_TOGETHER_GROUP,    simple);
  handler->reg_handler(ATTR_SWITCHING_INTERVAL,       simple);
  handler->reg_handler(ATTR_SWITCHING_TOGETHER_GROUP, simple);
  handler->reg_handler(ATTR_WHEN,                     func_handler);

  // complex attribute

  // group statements
  handler->reg_handler(ATTR_POWER,                    new_power(handler));
  handler->reg_handler(ATTR_FALL_POWER,               new_power(handler));
  handler->reg_handler(ATTR_RISE_POWER,               new_power(handler));
  handler->reg_handler(ATTR_DOMAIN,                   new_group(handler));

  return handler;
}

// @brief timing group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_timing(GroupHandler* parent)
{
  GroupHandler* handler = new EmptyGroupHandler(parent);

  // simple attributes
  DotlibHandler* simple = new SimpleHandler(handler, false);
  DotlibHandler* str_simple = new StrSimpleHandler(handler, false);
  DotlibHandler* flt_simple = new FloatSimpleHandler(handler);
  DotlibHandler* func_handler = new FuncHandler(handler);

  handler->reg_handler(ATTR_RELATED_BUS_EQUIVALENT,   str_simple);
  handler->reg_handler(ATTR_RELATED_BUS_PINS,         str_simple);
  handler->reg_handler(ATTR_RELATED_OUTPUT_PIN,       str_simple);
  handler->reg_handler(ATTR_RELATED_PIN,              str_simple);

  handler->reg_handler(ATTR_TIMING_SENSE,             new TimingSenseHandler(handler));
  handler->reg_handler(ATTR_TIMING_TYPE,              new TimingTypeHandler(handler));

  handler->reg_handler(ATTR_EDGE_RATE_SENSITIVITY_F0, simple);
  handler->reg_handler(ATTR_EDGE_RATE_SENSITIVITY_F1, simple);
  handler->reg_handler(ATTR_EDGE_RATE_SENSITIVITY_R0, simple);
  handler->reg_handler(ATTR_EDGE_RATE_SENSITIVITY_R1, simple);

  handler->reg_handler(ATTR_RISE_RESISTANCE,          flt_simple);
  handler->reg_handler(ATTR_FALL_RESISTANCE,          flt_simple);
  handler->reg_handler(ATTR_INTRINSIC_RISE,           flt_simple);
  handler->reg_handler(ATTR_INTRINSIC_FALL,           flt_simple);

  handler->reg_handler(ATTR_SDF_COND,                 simple);
  handler->reg_handler(ATTR_SDF_COND_END,             simple);
  handler->reg_handler(ATTR_SDF_COND_START,           simple);
  handler->reg_handler(ATTR_SDF_EDGES,                simple);

  handler->reg_handler(ATTR_SLOPE_FALL,               flt_simple);
  handler->reg_handler(ATTR_SLOPE_RISE,               flt_simple);

  handler->reg_handler(ATTR_WHEN,                     func_handler);
  handler->reg_handler(ATTR_WHEN_END,                 func_handler);
  handler->reg_handler(ATTR_WHEN_START,               func_handler);

  // complex attribute
  DotlibHandler* complex = new ComplexHandler(handler);
  DotlibHandler* pw_complex = new PwComplexHandler(handler);
  handler->reg_handler(ATTR_RISE_DELAY_INTERCEPT,     pw_complex);
  handler->reg_handler(ATTR_FALL_DELAY_INTERCEPT,     pw_complex);
  handler->reg_handler(ATTR_RISE_PIN_RESISTANCE,      pw_complex);
  handler->reg_handler(ATTR_FALL_PIN_RESISTANCE,      pw_complex);
  handler->reg_handler(ATTR_ORDERS,                   complex);
  handler->reg_handler(ATTR_COEFS,                    complex);

  // group statements
  handler->reg_handler(ATTR_CELL_DEGRADATION,
		       new_group(handler));

  handler->reg_handler(ATTR_CELL_RISE,
		       new_table(handler));
  handler->reg_handler(ATTR_CELL_FALL,
		       new_table(handler));

  handler->reg_handler(ATTR_RISE_CONSTRAINT,
		       new_table(handler));
  handler->reg_handler(ATTR_FALL_CONSTRAINT,
		       new_table(handler));

  handler->reg_handler(ATTR_RISE_PROPAGATION,
		       new_table(handler));
  handler->reg_handler(ATTR_FALL_PROPAGATION,
		       new_table(handler));

  handler->reg_handler(ATTR_RISE_TRANSITION,
		       new_table(handler));
  handler->reg_handler(ATTR_FALL_TRANSITION,
		       new_table(handler));

  handler->reg_handler(ATTR_NOISE_IMMUNITY_ABOVE_HIGH,
		       new_group(handler));
  handler->reg_handler(ATTR_NOISE_IMMUNITY_BELOW_LOW,
		       new_group(handler));
  handler->reg_handler(ATTR_NOISE_IMMUNITY_HIGH,
		       new_group(handler));
  handler->reg_handler(ATTR_NOISE_IMMUNITY_LOW,
		       new_group(handler));

  handler->reg_handler(ATTR_PROPAGATED_NOISE_HEIGHT_ABOVE_HIGH,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_HEIGHT_BELOW_LOW,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_HEIGHT_HIGH,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_HEIGHT_LOW,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_ABOVE_HIGH,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_BELOW_LOW,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_HIGH,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_LOW,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_WIDTH_ABOVE_HIGH,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_WIDTH_BELOW_LOW,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_WIDTH_HIGH,
		       new_group(handler));
  handler->reg_handler(ATTR_PROPAGATED_NOISE_WIDTH_LOW,
		       new_group(handler));

  handler->reg_handler(ATTR_RETAINING_RISE,
		       new_group(handler));
  handler->reg_handler(ATTR_RETAINING_FALL,
		       new_group(handler));

  handler->reg_handler(ATTR_RETAIN_FALL_SLEW,
		       new_group(handler));
  handler->reg_handler(ATTR_RETAIN_RISE_SLEW,
		       new_group(handler));

  handler->reg_handler(ATTR_STEADY_STATE_CURRENT_HIGH,
		       new_group(handler));
  handler->reg_handler(ATTR_STEADY_STATE_CURRENT_LOW,
		       new_group(handler));
  handler->reg_handler(ATTR_STEADY_STATE_CURRENT_TRISTATE,
		       new_group(handler));

  return handler;
}

// @brief table group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_table(GroupHandler* parent)
{
  GroupHandler* handler = new Str1GroupHandler(parent);

  // simple attributes

  // complex attribute
  DotlibHandler* index_handler = new VectorComplexHandler(handler);
  DotlibHandler* value_handler = new VectorListComplexHandler(handler);
  handler->reg_handler(ATTR_INDEX_1, index_handler);
  handler->reg_handler(ATTR_INDEX_2, index_handler);
  handler->reg_handler(ATTR_INDEX_3, index_handler);
  handler->reg_handler(ATTR_VALUES,  value_handler);

  // group statements
  handler->reg_handler(ATTR_DOMAIN, new_group(handler));

  return handler;
}

// @brief 汎用の group 用のハンドラを作る．
GroupHandler*
HandlerFactory::new_group(GroupHandler* parent)
{
  return new GroupHandler(parent);
}

END_NAMESPACE_YM_DOTLIB
