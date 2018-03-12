
/// @file LibraryHandler.cc
/// @brief LibraryHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"

#include "LibraryHandler.h"
#include "SimpleHandler.h"
#include "ComplexHandler.h"
#include "Str1ComplexHandler.h"
#include "UnitComplexHandler.h"
#include "DefineHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief library group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_library(DotlibParser& parser)
{
  return new LibraryHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス LibraryHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LibraryHandler::LibraryHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* symstr_simple = new StrSimpleHandler(parser, true);
  DotlibHandler* flt_simple = new FloatSimpleHandler(parser);
  DotlibHandler* delay_model = HandlerFactory::new_delay_model(parser);
  DotlibHandler* complex = new ComplexHandler(parser);
  DotlibHandler* str1_complex = new Str1ComplexHandler(parser);
  DotlibHandler* unit_complex = new UnitComplexHandler(parser);
  DotlibHandler* define = new DefineHandler(parser, this);
  DotlibHandler* tmpl_handler = HandlerFactory::new_template(parser);
  DotlibHandler* group_handler = HandlerFactory::new_group(parser);
  DotlibHandler* cell_handler = HandlerFactory::new_cell(parser);
  DotlibHandler* iv_handler = HandlerFactory::new_input_voltage(parser);
  DotlibHandler* ov_handler = HandlerFactory::new_output_voltage(parser);
  DotlibHandler* oc_handler = HandlerFactory::new_operating_conditions(parser);
  DotlibHandler* wl_handler = HandlerFactory::new_wire_load(parser);
  DotlibHandler* wls_handler = HandlerFactory::new_wire_load_selection(parser);
  DotlibHandler* wlt_handler = HandlerFactory::new_wire_load_table(parser);

  // simple attributes
  reg_handler(ATTR_BUS_NAMING_STYLE,                       str_simple);
  reg_handler(ATTR_COMMENT,                                str_simple);
  reg_handler(ATTR_CURRENT_UNIT,                           symstr_simple);
  reg_handler(ATTR_DATE,                                   str_simple);
  reg_handler(ATTR_DELAY_MODEL,                            delay_model);
  reg_handler(ATTR_EM_TEMP_DEGRADATION_FACTOR,             flt_simple);
  reg_handler(ATTR_FPGA_TECHNOLOGY,                        str_simple);
  reg_handler(ATTR_IN_PLACE_SWAP_MODE,                     str_simple);
  reg_handler(ATTR_INPUT_THRESHOLD_PCT_FALL,               simple);
  reg_handler(ATTR_INPUT_THRESHOLD_PCT_RISE,               simple);
  reg_handler(ATTR_LEAKAGE_POWER_UNIT,                     symstr_simple);
  reg_handler(ATTR_NOM_CALC_MODE,                          str_simple);
  reg_handler(ATTR_NOM_PROCESS,                            flt_simple);
  reg_handler(ATTR_NOM_TEMPERATURE,                        flt_simple);
  reg_handler(ATTR_NOM_VOLTAGE,                            flt_simple);
  reg_handler(ATTR_OUTPUT_THRESHOLD_PCT_FALL,              simple);
  reg_handler(ATTR_OUTPUT_THRESHOLD_PCT_RISE,              simple);
  reg_handler(ATTR_PIECE_TYPE,                             str_simple);
  reg_handler(ATTR_POWER_MODEL,                            str_simple);
  reg_handler(ATTR_PREFERRED_INPUT_PAD_VOLTAGE,            str_simple);
  reg_handler(ATTR_PREFERRED_OUTPUT_PAD_VOLTAGE,           str_simple);
  reg_handler(ATTR_PREFERRED_OUTPUT_PAD_SLEW_RATE_CONTROL, str_simple);
  reg_handler(ATTR_PULLING_RESISTANCE_UNIT,                symstr_simple);
  reg_handler(ATTR_REVISION,                               symstr_simple);
  reg_handler(ATTR_SIMULATION,                             str_simple);
  reg_handler(ATTR_SLEW_DERATE_FROM_LIBRARY,               simple);
  reg_handler(ATTR_SLEW_LOWER_THRESHOLD_PCT_FALL,          simple);
  reg_handler(ATTR_SLEW_LOWER_THRESHOLD_PCT_RISE,          simple);
  reg_handler(ATTR_SLEW_UPPER_THRESHOLD_PCT_FALL,          simple);
  reg_handler(ATTR_SLEW_UPPER_THRESHOLD_PCT_RISE,          simple);
  reg_handler(ATTR_TIME_UNIT,                              symstr_simple);
  reg_handler(ATTR_VOLTAGE_UNIT,                           symstr_simple);

  // default attributes
  reg_handler(ATTR_DEFAULT_CELL_LEAKAGE_POWER,             flt_simple);
  reg_handler(ATTR_DEFAULT_CONNECTION_CLASS,               str_simple);
  reg_handler(ATTR_DEFAULT_FALL_DELAY_INTERCEPT,           flt_simple);
  reg_handler(ATTR_DEFAULT_FALL_PIN_RESISTANCE,            flt_simple);
  reg_handler(ATTR_DEFAULT_FANOUT_LOAD,                    flt_simple);
  reg_handler(ATTR_DEFAULT_INOUT_PIN_CAP,                  flt_simple);
  reg_handler(ATTR_DEFAULT_INOUT_PIN_FALL_RES,             flt_simple);
  reg_handler(ATTR_DEFAULT_INOUT_PIN_RISE_RES,             flt_simple);
  reg_handler(ATTR_DEFAULT_INPUT_PIN_CAP,                  flt_simple);
  reg_handler(ATTR_DEFAULT_INTRINSIC_FALL,                 flt_simple);
  reg_handler(ATTR_DEFAULT_INTRINSIC_RISE,                 flt_simple);
  reg_handler(ATTR_DEFAULT_LEAKAGE_POWER_DENSITY,          flt_simple);
  reg_handler(ATTR_DEFAULT_MAX_CAPACITANCE,                flt_simple);
  reg_handler(ATTR_DEFAULT_MAX_FANOUT,                     flt_simple);
  reg_handler(ATTR_DEFAULT_MAX_TRANSITION,                 flt_simple);
  reg_handler(ATTR_DEFAULT_MAX_UTILIZATION,                flt_simple);
  reg_handler(ATTR_DEFAULT_MIN_POROSITY,                   flt_simple);
  reg_handler(ATTR_DEFAULT_OPERATING_CONDITIONS,           str_simple);
  reg_handler(ATTR_DEFAULT_OUTPUT_PIN_CAP,                 flt_simple);
  reg_handler(ATTR_DEFAULT_OUTPUT_PIN_FALL_RES,            flt_simple);
  reg_handler(ATTR_DEFAULT_OUTPUT_PIN_RISE_RES,            flt_simple);
  reg_handler(ATTR_DEFAULT_RISE_DELAY_INTERCEPT,           flt_simple);
  reg_handler(ATTR_DEFAULT_RISE_PIN_RESISTANCE,            flt_simple);
  reg_handler(ATTR_DEFAULT_SLOPE_FALL,                     flt_simple);
  reg_handler(ATTR_DEFAULT_SLOPE_RISE,                     flt_simple);
  reg_handler(ATTR_DEFAULT_WIRE_LOAD,                      str_simple);
  reg_handler(ATTR_DEFAULT_WIRE_LOAD_AREA,                 flt_simple);
  reg_handler(ATTR_DEFAULT_WIRE_LOAD_CAPACITANCE,          flt_simple);
  reg_handler(ATTR_DEFAULT_WIRE_LOAD_MODE,                 str_simple);
  reg_handler(ATTR_DEFAULT_WIRE_LOAD_RESISTANCE,           flt_simple);
  reg_handler(ATTR_DEFAULT_WIRE_LOAD_SELECTION,            str_simple);

  // scaling attributes
  reg_handler(ATTR_K_PROCESS_CELL_FALL,                    flt_simple);
  reg_handler(ATTR_K_PROCESS_CELL_LEAKAGE_POWER,           flt_simple);
  reg_handler(ATTR_K_PROCESS_CELL_RISE,                    flt_simple);
  reg_handler(ATTR_K_PROCESS_DRIVE_CURRENT,                flt_simple);
  reg_handler(ATTR_K_PROCESS_DRIVE_FALL,                   flt_simple);
  reg_handler(ATTR_K_PROCESS_DRIVE_RISE,                   flt_simple);
  reg_handler(ATTR_K_PROCESS_FALL_DELAY_INTERCEPT,         flt_simple);
  reg_handler(ATTR_K_PROCESS_FALL_PIN_RESISTANCE,          flt_simple);
  reg_handler(ATTR_K_PROCESS_FALL_PROPAGATION,             flt_simple);
  reg_handler(ATTR_K_PROCESS_FALL_TRANSITION,              flt_simple);
  reg_handler(ATTR_K_PROCESS_HOLD_FALL,                    flt_simple);
  reg_handler(ATTR_K_PROCESS_HOLD_RISE,                    flt_simple);
  reg_handler(ATTR_K_PROCESS_INTERNAL_POWER,               flt_simple);
  reg_handler(ATTR_K_PROCESS_INTRINSIC_FALL,               flt_simple);
  reg_handler(ATTR_K_PROCESS_INTRINSIC_RISE,               flt_simple);
  reg_handler(ATTR_K_PROCESS_MIN_PERIOD,                   flt_simple);
  reg_handler(ATTR_K_PROCESS_MIN_PULSE_WIDTH_HIGH,         flt_simple);
  reg_handler(ATTR_K_PROCESS_MIN_PULSE_WIDTH_LOW,          flt_simple);
  reg_handler(ATTR_K_PROCESS_NOCHANGE_FALL,                flt_simple);
  reg_handler(ATTR_K_PROCESS_NOCHANGE_RISE,                flt_simple);
  reg_handler(ATTR_K_PROCESS_PIN_CAP,                      flt_simple);
  reg_handler(ATTR_K_PROCESS_RECOVERY_FALL,                flt_simple);
  reg_handler(ATTR_K_PROCESS_RECOVERY_RISE,                flt_simple);
  reg_handler(ATTR_K_PROCESS_REMOVAL_FALL,                 flt_simple);
  reg_handler(ATTR_K_PROCESS_REMOVAL_RISE,                 flt_simple);
  reg_handler(ATTR_K_PROCESS_RISE_DELAY_INTERCEPT,         flt_simple);
  reg_handler(ATTR_K_PROCESS_RISE_PIN_RESISTANCE,          flt_simple);
  reg_handler(ATTR_K_PROCESS_RISE_PROPAGATION,             flt_simple);
  reg_handler(ATTR_K_PROCESS_RISE_TRANSITION,              flt_simple);
  reg_handler(ATTR_K_PROCESS_SETUP_FALL,                   flt_simple);
  reg_handler(ATTR_K_PROCESS_SETUP_RISE,                   flt_simple);
  reg_handler(ATTR_K_PROCESS_SKEW_FALL,                    flt_simple);
  reg_handler(ATTR_K_PROCESS_SKEW_RISE,                    flt_simple);
  reg_handler(ATTR_K_PROCESS_SLOPE_FALL,                   flt_simple);
  reg_handler(ATTR_K_PROCESS_SLOPE_RISE,                   flt_simple);
  reg_handler(ATTR_K_PROCESS_WIRE_CAP,                     flt_simple);
  reg_handler(ATTR_K_PROCESS_WIRE_RES,                     flt_simple);
  reg_handler(ATTR_K_TEMP_CELL_FALL,                       flt_simple);
  reg_handler(ATTR_K_TEMP_CELL_LEAKAGE_POWER,              flt_simple);
  reg_handler(ATTR_K_TEMP_CELL_RISE,                       flt_simple);
  reg_handler(ATTR_K_TEMP_DRIVE_CURRENT,                   flt_simple);
  reg_handler(ATTR_K_TEMP_DRIVE_FALL,                      flt_simple);
  reg_handler(ATTR_K_TEMP_DRIVE_RISE,                      flt_simple);
  reg_handler(ATTR_K_TEMP_FALL_DELAY_INTERCEPT,            flt_simple);
  reg_handler(ATTR_K_TEMP_FALL_PIN_RESISTANCE,             flt_simple);
  reg_handler(ATTR_K_TEMP_FALL_PROPAGATION,                flt_simple);
  reg_handler(ATTR_K_TEMP_FALL_TRANSITION,                 flt_simple);
  reg_handler(ATTR_K_TEMP_HOLD_FALL,                       flt_simple);
  reg_handler(ATTR_K_TEMP_HOLD_RISE,                       flt_simple);
  reg_handler(ATTR_K_TEMP_INTERNAL_POWER,                  flt_simple);
  reg_handler(ATTR_K_TEMP_INTRINSIC_FALL,                  flt_simple);
  reg_handler(ATTR_K_TEMP_INTRINSIC_RISE,                  flt_simple);
  reg_handler(ATTR_K_TEMP_MIN_PERIOD,                      flt_simple);
  reg_handler(ATTR_K_TEMP_MIN_PULSE_WIDTH_HIGH,            flt_simple);
  reg_handler(ATTR_K_TEMP_MIN_PULSE_WIDTH_LOW,             flt_simple);
  reg_handler(ATTR_K_TEMP_NOCHANGE_FALL,                   flt_simple);
  reg_handler(ATTR_K_TEMP_NOCHANGE_RISE,                   flt_simple);
  reg_handler(ATTR_K_TEMP_PIN_CAP,                         flt_simple);
  reg_handler(ATTR_K_TEMP_RECOVERY_FALL,                   flt_simple);
  reg_handler(ATTR_K_TEMP_RECOVERY_RISE,                   flt_simple);
  reg_handler(ATTR_K_TEMP_REMOVAL_FALL,                    flt_simple);
  reg_handler(ATTR_K_TEMP_REMOVAL_RISE,                    flt_simple);
  reg_handler(ATTR_K_TEMP_RISE_DELAY_INTERCEPT,            flt_simple);
  reg_handler(ATTR_K_TEMP_RISE_PIN_RESISTANCE,             flt_simple);
  reg_handler(ATTR_K_TEMP_RISE_PROPAGATION,                flt_simple);
  reg_handler(ATTR_K_TEMP_RISE_TRANSITION,                 flt_simple);
  reg_handler(ATTR_K_TEMP_SETUP_FALL,                      flt_simple);
  reg_handler(ATTR_K_TEMP_SETUP_RISE,                      flt_simple);
  reg_handler(ATTR_K_TEMP_SKEW_FALL,                       flt_simple);
  reg_handler(ATTR_K_TEMP_SKEW_RISE,                       flt_simple);
  reg_handler(ATTR_K_TEMP_SLOPE_FALL,                      flt_simple);
  reg_handler(ATTR_K_TEMP_SLOPE_RISE,                      flt_simple);
  reg_handler(ATTR_K_TEMP_WIRE_CAP,                        flt_simple);
  reg_handler(ATTR_K_TEMP_WIRE_RES,                        flt_simple);
  reg_handler(ATTR_K_VOLT_CELL_FALL,                       flt_simple);
  reg_handler(ATTR_K_VOLT_CELL_LEAKAGE_POWER,              flt_simple);
  reg_handler(ATTR_K_VOLT_CELL_RISE,                       flt_simple);
  reg_handler(ATTR_K_VOLT_DRIVE_CURRENT,                   flt_simple);
  reg_handler(ATTR_K_VOLT_DRIVE_FALL,                      flt_simple);
  reg_handler(ATTR_K_VOLT_DRIVE_RISE,                      flt_simple);
  reg_handler(ATTR_K_VOLT_FALL_DELAY_INTERCEPT,            flt_simple);
  reg_handler(ATTR_K_VOLT_FALL_PIN_RESISTANCE,             flt_simple);
  reg_handler(ATTR_K_VOLT_FALL_PROPAGATION,                flt_simple);
  reg_handler(ATTR_K_VOLT_FALL_TRANSITION,                 flt_simple);
  reg_handler(ATTR_K_VOLT_HOLD_FALL,                       flt_simple);
  reg_handler(ATTR_K_VOLT_HOLD_RISE,                       flt_simple);
  reg_handler(ATTR_K_VOLT_INTERNAL_POWER,                  flt_simple);
  reg_handler(ATTR_K_VOLT_INTRINSIC_FALL,                  flt_simple);
  reg_handler(ATTR_K_VOLT_INTRINSIC_RISE,                  flt_simple);
  reg_handler(ATTR_K_VOLT_MIN_PERIOD,                      flt_simple);
  reg_handler(ATTR_K_VOLT_MIN_PULSE_WIDTH_HIGH,            flt_simple);
  reg_handler(ATTR_K_VOLT_MIN_PULSE_WIDTH_LOW,             flt_simple);
  reg_handler(ATTR_K_VOLT_NOCHANGE_FALL,                   flt_simple);
  reg_handler(ATTR_K_VOLT_NOCHANGE_RISE,                   flt_simple);
  reg_handler(ATTR_K_VOLT_PIN_CAP,                         flt_simple);
  reg_handler(ATTR_K_VOLT_RECOVERY_FALL,                   flt_simple);
  reg_handler(ATTR_K_VOLT_RECOVERY_RISE,                   flt_simple);
  reg_handler(ATTR_K_VOLT_REMOVAL_FALL,                    flt_simple);
  reg_handler(ATTR_K_VOLT_REMOVAL_RISE,                    flt_simple);
  reg_handler(ATTR_K_VOLT_RISE_DELAY_INTERCEPT,            flt_simple);
  reg_handler(ATTR_K_VOLT_RISE_PIN_RESISTANCE,             flt_simple);
  reg_handler(ATTR_K_VOLT_RISE_PROPAGATION,                flt_simple);
  reg_handler(ATTR_K_VOLT_RISE_TRANSITION,                 flt_simple);
  reg_handler(ATTR_K_VOLT_SETUP_FALL,                      flt_simple);
  reg_handler(ATTR_K_VOLT_SETUP_RISE,                      flt_simple);
  reg_handler(ATTR_K_VOLT_SKEW_FALL,                       flt_simple);
  reg_handler(ATTR_K_VOLT_SKEW_RISE,                       flt_simple);
  reg_handler(ATTR_K_VOLT_SLOPE_FALL,                      flt_simple);
  reg_handler(ATTR_K_VOLT_SLOPE_RISE,                      flt_simple);
  reg_handler(ATTR_K_VOLT_WIRE_CAP,                        flt_simple);
  reg_handler(ATTR_K_VOLT_WIRE_RES,                        flt_simple);

  // complex attributes
  reg_handler(ATTR_CAPACITIVE_LOAD_UNIT,                   unit_complex);
  reg_handler(ATTR_DEFAULT_PART,                           complex);
  reg_handler(ATTR_DEFINE,                                 define);
  reg_handler(ATTR_DEFINE_CELL_AREA,                       complex);
  reg_handler(ATTR_DEFINE_GROUP,                           complex);
  reg_handler(ATTR_LIBRARY_FEATURES,                       str1_complex);
  reg_handler(ATTR_PIECE_DEFINE,                           str1_complex);
  reg_handler(ATTR_ROUTING_LAYERS,                         complex);
  reg_handler(ATTR_TECHNOLOGY,                             str1_complex);

  //fall_net_delay : name ;
  //rise_net_delay : name ;

  // group statements
  reg_handler(ATTR_CELL,   		                   cell_handler);
  reg_handler(ATTR_DC_CURRENT_TEMPLATE,                    tmpl_handler);
  reg_handler(ATTR_EM_LUT_TEMPLATE,                        tmpl_handler);
  reg_handler(ATTR_FALL_TRANSITION_DEGRADATION,            group_handler);
  reg_handler(ATTR_FAULTS_LUT_TEMPLATE,                    tmpl_handler);
  reg_handler(ATTR_INPUT_VOLTAGE,		           iv_handler);
  reg_handler(ATTR_IV_LUT_TEMPLATE,                        tmpl_handler);
  reg_handler(ATTR_LU_TABLE_TEMPLATE,                      tmpl_handler);
  reg_handler(ATTR_NOISE_LUT_TEMPLATE,                     tmpl_handler);
  reg_handler(ATTR_OPERATING_CONDITIONS,	           oc_handler);
  reg_handler(ATTR_OUTPUT_CURRENT_TEMPLATE,                tmpl_handler);
  reg_handler(ATTR_OUTPUT_VOLTAGE,		           ov_handler);
  reg_handler(ATTR_PART,                                   group_handler);
  reg_handler(ATTR_POLY_TEMPLATE,                          tmpl_handler);
  reg_handler(ATTR_POWER_LUT_TEMPLATE,                     tmpl_handler);
  reg_handler(ATTR_POWER_POLY_TEMPLATE,                    tmpl_handler);
  reg_handler(ATTR_POWER_SUPPLY,                           group_handler);
  reg_handler(ATTR_PROPAGATION_LUT_TEMPLATE,               tmpl_handler);
  reg_handler(ATTR_RISE_TRANSITION_DEGRADATION,            group_handler);
  reg_handler(ATTR_SCALED_CELL,                            group_handler);
  reg_handler(ATTR_SCALING_FACTORS,                        group_handler);
  reg_handler(ATTR_TIMING,                                 group_handler);
  reg_handler(ATTR_TIMING_RANGE,                           group_handler);
  reg_handler(ATTR_TYPE,                                   group_handler);
  reg_handler(ATTR_WIRE_LOAD,                              wl_handler);
  reg_handler(ATTR_WIRE_LOAD_SELECTION,		           wls_handler);
  reg_handler(ATTR_WIRE_LOAD_TABLE,		           wlt_handler);
}

// @brief デストラクタ
LibraryHandler::~LibraryHandler()
{
}

// @brief 値を作る．
DotlibNode*
LibraryHandler::gen_value(const FileRegion& loc,
			  const DotlibString* name,
			  const vector<DotlibAttr*>& attr_list)
{
#warning "TODO: 未完成"
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
