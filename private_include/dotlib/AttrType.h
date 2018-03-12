﻿#ifndef ATTRTYPE_H
#define ATTRTYPE_H

/// @file AttrType.h
/// @brief 属性を表す列挙型
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "ym/HashFunc.h"

BEGIN_NAMESPACE_YM_DOTLIB

/// @brief 属性を表す列挙型
enum class AttrType {
  NONE,

  AREA,
  AUXILIARY_PAD_CELL,
  BASE_NAME,
  BIT_WIDTH,
  BUNDLE,
  BUS_NAMING_STYLE,
  BUS_TYPE,
  BUS,
  CALC_MODE,
  CAPACITANCE,
  CAPACITIVE_LOAD_UNIT,
  CELL_DEGRADATION,
  CELL_FALL,
  CELL_FOOTPRINT,
  CELL_LEAKAGE_POWER,
  CELL_RISE,
  CELL,
  CLEAR_PRESET_VAR1,
  CLEAR_PRESET_VAR2,
  CLEAR,
  CLOCK_GATE_CLOCK_PIN,
  CLOCK_GATE_ENABLE_PIN,
  CLOCK_GATE_TEST_PIN,
  CLOCK_GATE_OBS_PIN,
  CLOCK_GATE_OUT_PIN,
  CLOCK_GATING_INTEGRATED_CELL,
  CLOCK,
  CLOCKED_ON_ALSO,
  CLOCKED_ON,
  COEFS,
  COMMENT,
  COMPLEMENTARY_PIN,
  CONNECTION_CLASS,
  CONTENTION_CONDITION,
  CURRENT_UNIT,
  DATA_IN,
  DATE,
  DC_CURRENT_TEMPLATE,
  DEFAULT_CELL_LEAKAGE_POWER,
  DEFAULT_CONNECTION_CLASS,
  DEFAULT_FALL_DELAY_INTERCEPT,
  DEFAULT_FALL_PIN_RESISTANCE,
  DEFAULT_FANOUT_LOAD,
  DEFAULT_INOUT_PIN_CAP,
  DEFAULT_INOUT_PIN_FALL_RES,
  DEFAULT_INOUT_PIN_RISE_RES,
  DEFAULT_INPUT_PIN_CAP,
  DEFAULT_INTRINSIC_FALL,
  DEFAULT_INTRINSIC_RISE,
  DEFAULT_LEAKAGE_POWER_DENSITY,
  DEFAULT_MAX_CAPACITANCE,
  DEFAULT_MAX_FANOUT,
  DEFAULT_MAX_TRANSITION,
  DEFAULT_MAX_UTILIZATION,
  DEFAULT_MIN_POROSITY,
  DEFAULT_OPERATING_CONDITIONS,
  DEFAULT_OUTPUT_PIN_CAP,
  DEFAULT_OUTPUT_PIN_FALL_RES,
  DEFAULT_OUTPUT_PIN_RISE_RES,
  DEFAULT_PART,
  DEFAULT_RISE_DELAY_INTERCEPT,
  DEFAULT_RISE_PIN_RESISTANCE,
  DEFAULT_SLOPE_FALL,
  DEFAULT_SLOPE_RISE,
  DEFAULT_WIRE_LOAD_AREA,
  DEFAULT_WIRE_LOAD_CAPACITANCE,
  DEFAULT_WIRE_LOAD_MODE,
  DEFAULT_WIRE_LOAD_RESISTANCE,
  DEFAULT_WIRE_LOAD_SELECTION,
  DEFAULT_WIRE_LOAD,
  DEFINE_CELL_AREA,
  DEFINE_GROUP,
  DEFINE,
  DELAY_MODEL,
  DIRECTION,
  DOMAIN,
  DONT_FAULT,
  DONT_TOUCH,
  DONT_USE,
  DRIVE_CURRENT,
  DRIVER_TYPE,
  DYNAMIC_CURRENT,
  EDGE_RATE_SENSITIVITY_F0,
  EDGE_RATE_SENSITIVITY_F1,
  EDGE_RATE_SENSITIVITY_R0,
  EDGE_RATE_SENSITIVITY_R1,
  EDIF_NAME,
  ELECTROMIGRATION,
  EM_LUT_TEMPLATE,
  EM_TEMP_DEGRADATION_FACTOR,
  ENABLE_ALSO,
  ENABLE,
  EQUAL_OR_OPPOSITE_OUTPUT,
  FALL_CAPACITANCE_RANGE,
  FALL_CAPACITANCE,
  FALL_CONSTRAINT,
  FALL_CURRENT_SLOPE_AFTER_THRESHOLD,
  FALL_CURRENT_SLOPE_BEFORE_THRESHOLD,
  FALL_DELAY_INTERCEPT,
  FALL_PIN_RESISTANCE,
  FALL_POWER,
  FALL_PROPAGATION,
  FALL_RESISTANCE,
  FALL_TIME_AFTER_THRESHOLD,
  FALL_TIME_BEFORE_THRESHOLD,
  FALL_TRANSITION_DEGRADATION,
  FALL_TRANSITION,
  FALLING_TOGETHER_GROUP,
  FANOUT_AREA,
  FANOUT_CAPACITANCE,
  FANOUT_LENGTH,
  FANOUT_LOAD,
  FANOUT_RESISTANCE,
  FAULT_MODEL,
  FAULTS_LUT_TEMPLATE,
  FF_BANK,
  FF,
  FPGA_DOMAIN_STYLE,
  FPGA_TECHNOLOGY,
  FUNCTION,
  FUNCTIONAL_YIELD_METRIC,
  GENERATED_CLOCK,
  GEOMETRY_PRINT,
  HANDLE_NEGATIVE_CONSTRAINT,
  HAS_BUILTIN_PAD,
  HYPERBOLIC_NOISE_ABOVE_HIGH,
  HYPERBOLIC_NOISE_BELOW_LOW,
  HYPERBOLIC_NOISE_HIGH,
  HYPERBOLIC_NOISE_LOW,
  HYSTERESIS,
  IN_PLACE_SWAP_MODE,
  INDEX_1,
  INDEX_2,
  INDEX_3,
  INPUT_MAP,
  INPUT_SIGNAL_LEVEL,
  INPUT_THRESHOLD_PCT_FALL,
  INPUT_THRESHOLD_PCT_RISE,
  INPUT_VOLTAGE,
  INTERFACE_TIMING,
  INTERNAL_NODE,
  INTERNAL_POWER,
  INTRINSIC_FALL,
  INTRINSIC_PARASITIC,
  INTRINSIC_RISE,
  INVERTED_OUTPUT,
  IO_TYPE,
  IS_CLOCK_GATING_CELL,
  IS_FILLER_CELL,
  IS_PAD,
  IV_LUT_TEMPLATE,
  K_PROCESS_CELL_FALL,
  K_PROCESS_CELL_LEAKAGE_POWER,
  K_PROCESS_CELL_RISE,
  K_PROCESS_DRIVE_CURRENT,
  K_PROCESS_DRIVE_FALL,
  K_PROCESS_DRIVE_RISE,
  K_PROCESS_FALL_DELAY_INTERCEPT,
  K_PROCESS_FALL_PIN_RESISTANCE,
  K_PROCESS_FALL_PROPAGATION,
  K_PROCESS_FALL_TRANSITION,
  K_PROCESS_HOLD_FALL,
  K_PROCESS_HOLD_RISE,
  K_PROCESS_INTERNAL_POWER,
  K_PROCESS_INTRINSIC_FALL,
  K_PROCESS_INTRINSIC_RISE,
  K_PROCESS_MIN_PERIOD,
  K_PROCESS_MIN_PULSE_WIDTH_HIGH,
  K_PROCESS_MIN_PULSE_WIDTH_LOW,
  K_PROCESS_NOCHANGE_FALL,
  K_PROCESS_NOCHANGE_RISE,
  K_PROCESS_PIN_CAP,
  K_PROCESS_RECOVERY_FALL,
  K_PROCESS_RECOVERY_RISE,
  K_PROCESS_REMOVAL_FALL,
  K_PROCESS_REMOVAL_RISE,
  K_PROCESS_RISE_TRANSITION,
  K_PROCESS_RISE_DELAY_INTERCEPT,
  K_PROCESS_RISE_PIN_RESISTANCE,
  K_PROCESS_RISE_PROPAGATION,
  K_PROCESS_SETUP_FALL,
  K_PROCESS_SETUP_RISE,
  K_PROCESS_SKEW_FALL,
  K_PROCESS_SKEW_RISE,
  K_PROCESS_SLOPE_FALL,
  K_PROCESS_SLOPE_RISE,
  K_PROCESS_WIRE_CAP,
  K_PROCESS_WIRE_RES,
  K_TEMP_CELL_FALL,
  K_TEMP_CELL_LEAKAGE_POWER,
  K_TEMP_CELL_RISE,
  K_TEMP_DRIVE_CURRENT,
  K_TEMP_DRIVE_FALL,
  K_TEMP_DRIVE_RISE,
  K_TEMP_FALL_DELAY_INTERCEPT,
  K_TEMP_FALL_PIN_RESISTANCE,
  K_TEMP_FALL_PROPAGATION,
  K_TEMP_FALL_TRANSITION,
  K_TEMP_HOLD_FALL,
  K_TEMP_HOLD_RISE,
  K_TEMP_INTERNAL_POWER,
  K_TEMP_INTRINSIC_FALL,
  K_TEMP_INTRINSIC_RISE,
  K_TEMP_MIN_PERIOD,
  K_TEMP_MIN_PULSE_WIDTH_HIGH,
  K_TEMP_MIN_PULSE_WIDTH_LOW,
  K_TEMP_NOCHANGE_FALL,
  K_TEMP_NOCHANGE_RISE,
  K_TEMP_PIN_CAP,
  K_TEMP_RECOVERY_FALL,
  K_TEMP_RECOVERY_RISE,
  K_TEMP_REMOVAL_FALL,
  K_TEMP_REMOVAL_RISE,
  K_TEMP_RISE_TRANSITION,
  K_TEMP_RISE_DELAY_INTERCEPT,
  K_TEMP_RISE_PIN_RESISTANCE,
  K_TEMP_RISE_PROPAGATION,
  K_TEMP_SETUP_FALL,
  K_TEMP_SETUP_RISE,
  K_TEMP_SKEW_FALL,
  K_TEMP_SKEW_RISE,
  K_TEMP_SLOPE_FALL,
  K_TEMP_SLOPE_RISE,
  K_TEMP_WIRE_CAP,
  K_TEMP_WIRE_RES,
  K_VOLT_CELL_FALL,
  K_VOLT_CELL_LEAKAGE_POWER,
  K_VOLT_CELL_RISE,
  K_VOLT_DRIVE_CURRENT,
  K_VOLT_DRIVE_FALL,
  K_VOLT_DRIVE_RISE,
  K_VOLT_FALL_DELAY_INTERCEPT,
  K_VOLT_FALL_PIN_RESISTANCE,
  K_VOLT_FALL_PROPAGATION,
  K_VOLT_FALL_TRANSITION,
  K_VOLT_HOLD_FALL,
  K_VOLT_HOLD_RISE,
  K_VOLT_INTERNAL_POWER,
  K_VOLT_INTRINSIC_FALL,
  K_VOLT_INTRINSIC_RISE,
  K_VOLT_MIN_PERIOD,
  K_VOLT_MIN_PULSE_WIDTH_HIGH,
  K_VOLT_MIN_PULSE_WIDTH_LOW,
  K_VOLT_NOCHANGE_FALL,
  K_VOLT_NOCHANGE_RISE,
  K_VOLT_PIN_CAP,
  K_VOLT_RECOVERY_FALL,
  K_VOLT_RECOVERY_RISE,
  K_VOLT_REMOVAL_FALL,
  K_VOLT_REMOVAL_RISE,
  K_VOLT_RISE_TRANSITION,
  K_VOLT_RISE_DELAY_INTERCEPT,
  K_VOLT_RISE_PIN_RESISTANCE,
  K_VOLT_RISE_PROPAGATION,
  K_VOLT_SETUP_FALL,
  K_VOLT_SETUP_RISE,
  K_VOLT_SKEW_FALL,
  K_VOLT_SKEW_RISE,
  K_VOLT_SLOPE_FALL,
  K_VOLT_SLOPE_RISE,
  K_VOLT_WIRE_CAP,
  K_VOLT_WIRE_RES,
  LATCH_BANK,
  LATCH,
  LEAKAGE_CURRENT,
  LEAKAGE_POWER_UNIT,
  LEAKAGE_POWER,
  LIBRARY_FEATURES,
  LIBRARY,
  LU_TABLE_TEMPLATE,
  LUT,
  MAP_ONLY,
  MAX_CAPACITANCE,
  MAX_FANOUT,
  MAX_INPUT_NOISE_WIDTH,
  MAX_TRANS,
  MAX_TRANSITION,
  MEMBERS,
  MIN_CAPACITANCE,
  MIN_FANOUT,
  MIN_INPUT_NOISE_WIDTH,
  MIN_PERIOD,
  MIN_PULSE_WIDTH_HIGH,
  MIN_PULSE_WIDTH_LOW,
  MIN_PULSE_WIDTH,
  MIN_TRANSITION,
  MINIMUM_PERIOD,
  MODE_DEFINITION,
  MULTICELL_PAD_PIN,
  NEXT_STATE,
  NEXTSTATE_TYPE,
  NOISE_IMMUNITY_ABOVE_HIGH,
  NOISE_IMMUNITY_BELOW_LOW,
  NOISE_IMMUNITY_HIGH,
  NOISE_IMMUNITY_LOW,
  NOISE_LUT_TEMPLATE,
  NOM_CALC_MODE,
  NOM_PROCESS,
  NOM_TEMPERATURE,
  NOM_VOLTAGE,
  OPERATING_CONDITIONS,
  ORDERS,
  OUTPUT_CURRENT_TEMPLATE,
  OUTPUT_SIGNAL_LEVEL,
  OUTPUT_THRESHOLD_PCT_FALL,
  OUTPUT_THRESHOLD_PCT_RISE,
  OUTPUT_VOLTAGE,
  PAD_CELL,
  PAD_TYPE,
  PARAMETER1,
  PARAMETER2,
  PARAMETER3,
  PARAMETER4,
  PARAMETER5,
  PART,
  PIECE_DEFINE,
  PIECE_TYPE,
  PIN_FUNC_TYPE,
  PIN_OPPOSITE,
  PIN,
  POLY_TEMPLATE,
  POWER_CELL_TYPE,
  POWER_LEVEL,
  POWER_LUT_TEMPLATE,
  POWER_POLY_TEMPLATE,
  POWER_MODEL,
  POWER_RAIL,
  POWER_SUPPLY_NAMESTRING,
  POWER_SUPPLY,
  POWER,
  PREFER_TIED,
  PREFERRED,
  PREFERRED_INPUT_PAD_VOLTAGE,
  PREFERRED_OUTPUT_PAD_SLEW_RATE_CONTROL,
  PREFERRED_OUTPUT_PAD_VOLTAGE,
  PRESET,
  PRIMARY_OUTPUT,
  PROCESS,
  PROPAGATED_NOISE_HEIGHT_ABOVE_HIGH,
  PROPAGATED_NOISE_HEIGHT_BELOW_LOW,
  PROPAGATED_NOISE_HEIGHT_HIGH,
  PROPAGATED_NOISE_HEIGHT_LOW,
  PROPAGATED_NOISE_PEAK_TIME_RATIO_ABOVE_HIGH,
  PROPAGATED_NOISE_PEAK_TIME_RATIO_BELOW_LOW,
  PROPAGATED_NOISE_PEAK_TIME_RATIO_HIGH,
  PROPAGATED_NOISE_PEAK_TIME_RATIO_LOW,
  PROPAGATED_NOISE_WIDTH_ABOVE_HIGH,
  PROPAGATED_NOISE_WIDTH_BELOW_LOW,
  PROPAGATED_NOISE_WIDTH_HIGH,
  PROPAGATED_NOISE_WIDTH_LOW,
  PROPAGATION_LUT_TEMPLATE,
  PULLING_CURRENT,
  PULLING_RESISTANCE_UNIT,
  PULLING_RESISTANCE,
  RAIL_CONNECTION,
  RELATED_BUS_EQUIVALENT,
  RELATED_BUS_PINS,
  RELATED_INPUTS,
  RELATED_OUTPUT_PIN,
  RELATED_OUTPUTS,
  RELATED_PG_PIN,
  RELATED_PIN,
  RESISTANCE,
  RESOURCE_USAGE,
  RETAIN_FALL_SLEW,
  RETAIN_RISE_SLEW,
  RETAINING_FALL,
  RETAINING_RISE,
  REVISION,
  RISE_CAPACITANCE_RANGE,
  RISE_CAPACITANCE,
  RISE_CONSTRAINT,
  RISE_CURRENT_SLOPE_AFTER_THRESHOLD,
  RISE_CURRENT_SLOPE_BEFORE_THRESHOLD,
  RISE_DELAY_INTERCEPT,
  RISE_PIN_RESISTANCE,
  RISE_POWER,
  RISE_PROPAGATION,
  RISE_RESISTANCE,
  RISE_TIME_AFTER_THRESHOLD,
  RISE_TIME_BEFORE_THRESHOLD,
  RISE_TRANSITION_DEGRADATION,
  RISE_TRANSITION,
  RISING_TOGETHER_GROUP,
  ROUTING_LAYERS,
  ROUTING_TRACK,
  SCALED_CELL,
  SCALING_FACTORS,
  SDF_COND_END,
  SDF_COND_START,
  SDF_COND,
  SDF_EDGES,
  SIGNAL_TYPE,
  SIMULATION,
  SINGLE_BIT_DEGENERATE,
  SLEW_CONTROL,
  SLEW_DERATE_FROM_LIBRARY,
  SLEW_LOWER_THRESHOLD_PCT_FALL,
  SLEW_LOWER_THRESHOLD_PCT_RISE,
  SLEW_TYPE,
  SLEW_UPPER_THRESHOLD_PCT_FALL,
  SLEW_UPPER_THRESHOLD_PCT_RISE,
  SLOPE_FALL,
  SLOPE_RISE,
  SLOPE,
  STATE_FUNCTION,
  STATETABLE,
  STEADY_STATE_CURRENT_HIGH,
  STEADY_STATE_CURRENT_LOW,
  STEADY_STATE_CURRENT_TRISTATE,
  SWITCHING_INTERVAL,
  SWITCHING_TOGETHER_GROUP,
  TABLE,
  TECHNOLOGY,
  TEMPERATURE,
  TEST_CELL,
  TEST_OUTPUT_ONLY,
  THREE_STATE,
  TIME_UNIT,
  TIMING_MODEL_TYPE,
  TIMING_RANGE,
  TIMING_SENSE,
  TIMING_TYPE,
  TIMING,
  TLATCH,
  TREE_TYPE,
  TYPE,
  USE_FOR_SIZE_ONLY,
  VALUE,
  VALUES,
  VARIABLE_1,
  VARIABLE_2,
  VARIABLE_3,
  VHDL_NAME,
  VIH,
  VIL,
  VIMAX,
  VIMIN,
  VOH,
  VOL,
  VOLTAGE_UNIT,
  VOLTAGE,
  VOMAX,
  VOMIN,
  WHEN_END,
  WHEN_START,
  WHEN,
  WIRE_LOAD_FROM_AREA,
  WIRE_LOAD_SELECTION,
  WIRE_LOAD_TABLE,
  WIRE_LOAD,
  X_FUNCTION,

  END
};

/// @brief AttrType の内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   AttrType attr);

END_NAMESPACE_YM_DOTLIB

BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
// HashFunc<> の特殊化
//////////////////////////////////////////////////////////////////////
template<>
struct
HashFunc<nsClib::nsDotlib::AttrType>
{
  SizeType
  operator()(nsClib::nsDotlib::AttrType key) const {
    return static_cast<SizeType>(key);
  }
};

END_NAMESPACE_YM

#endif // ATTRTYPE_H
