﻿#ifndef ATTRTYPE_H
#define ATTRTYPE_H

/// @file AttrType.h
/// @brief 属性を表す列挙型
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"


BEGIN_NAMESPACE_YM_DOTLIB

/// @brief 属性を表す列挙型
enum AttrType {
  ATTR_NONE = 0,

  ATTR_AREA,
  ATTR_AUXILIARY_PAD_CELL,
  ATTR_BASE_NAME,
  ATTR_BIT_WIDTH,
  ATTR_BUNDLE,
  ATTR_BUS_NAMING_STYLE,
  ATTR_BUS_TYPE,
  ATTR_BUS,
  ATTR_CALC_MODE,
  ATTR_CAPACITANCE,
  ATTR_CAPACITIVE_LOAD_UNIT,
  ATTR_CELL_DEGRADATION,
  ATTR_CELL_FALL,
  ATTR_CELL_FOOTPRINT,
  ATTR_CELL_LEAKAGE_POWER,
  ATTR_CELL_RISE,
  ATTR_CELL,
  ATTR_CLEAR_PRESET_VAR1,
  ATTR_CLEAR_PRESET_VAR2,
  ATTR_CLEAR,
  ATTR_CLOCK_GATE_CLOCK_PIN,
  ATTR_CLOCK_GATE_ENABLE_PIN,
  ATTR_CLOCK_GATE_TEST_PIN,
  ATTR_CLOCK_GATE_OBS_PIN,
  ATTR_CLOCK_GATE_OUT_PIN,
  ATTR_CLOCK_GATING_INTEGRATED_CELL,
  ATTR_CLOCK,
  ATTR_CLOCKED_ON_ALSO,
  ATTR_CLOCKED_ON,
  ATTR_COEFS,
  ATTR_COMMENT,
  ATTR_COMPLEMENTARY_PIN,
  ATTR_CONNECTION_CLASS,
  ATTR_CONTENTION_CONDITION,
  ATTR_CURRENT_UNIT,
  ATTR_DATA_IN,
  ATTR_DATE,
  ATTR_DC_CURRENT_TEMPLATE,
  ATTR_DEFAULT_CELL_LEAKAGE_POWER,
  ATTR_DEFAULT_CONNECTION_CLASS,
  ATTR_DEFAULT_FALL_DELAY_INTERCEPT,
  ATTR_DEFAULT_FALL_PIN_RESISTANCE,
  ATTR_DEFAULT_FANOUT_LOAD,
  ATTR_DEFAULT_INOUT_PIN_CAP,
  ATTR_DEFAULT_INOUT_PIN_FALL_RES,
  ATTR_DEFAULT_INOUT_PIN_RISE_RES,
  ATTR_DEFAULT_INPUT_PIN_CAP,
  ATTR_DEFAULT_INTRINSIC_FALL,
  ATTR_DEFAULT_INTRINSIC_RISE,
  ATTR_DEFAULT_LEAKAGE_POWER_DENSITY,
  ATTR_DEFAULT_MAX_CAPACITANCE,
  ATTR_DEFAULT_MAX_FANOUT,
  ATTR_DEFAULT_MAX_TRANSITION,
  ATTR_DEFAULT_MAX_UTILIZATION,
  ATTR_DEFAULT_MIN_POROSITY,
  ATTR_DEFAULT_OPERATING_CONDITIONS,
  ATTR_DEFAULT_OUTPUT_PIN_CAP,
  ATTR_DEFAULT_OUTPUT_PIN_FALL_RES,
  ATTR_DEFAULT_OUTPUT_PIN_RISE_RES,
  ATTR_DEFAULT_PART,
  ATTR_DEFAULT_RISE_DELAY_INTERCEPT,
  ATTR_DEFAULT_RISE_PIN_RESISTANCE,
  ATTR_DEFAULT_SLOPE_FALL,
  ATTR_DEFAULT_SLOPE_RISE,
  ATTR_DEFAULT_WIRE_LOAD_AREA,
  ATTR_DEFAULT_WIRE_LOAD_CAPACITANCE,
  ATTR_DEFAULT_WIRE_LOAD_MODE,
  ATTR_DEFAULT_WIRE_LOAD_RESISTANCE,
  ATTR_DEFAULT_WIRE_LOAD_SELECTION,
  ATTR_DEFAULT_WIRE_LOAD,
  ATTR_DEFINE_CELL_AREA,
  ATTR_DEFINE_GROUP,
  ATTR_DEFINE,
  ATTR_DELAY_MODEL,
  ATTR_DIRECTION,
  ATTR_DOMAIN,
  ATTR_DONT_FAULT,
  ATTR_DONT_TOUCH,
  ATTR_DONT_USE,
  ATTR_DRIVE_CURRENT,
  ATTR_DRIVER_TYPE,
  ATTR_DYNAMIC_CURRENT,
  ATTR_EDGE_RATE_SENSITIVITY_F0,
  ATTR_EDGE_RATE_SENSITIVITY_F1,
  ATTR_EDGE_RATE_SENSITIVITY_R0,
  ATTR_EDGE_RATE_SENSITIVITY_R1,
  ATTR_EDIF_NAME,
  ATTR_ELECTROMIGRATION,
  ATTR_EM_LUT_TEMPLATE,
  ATTR_EM_TEMP_DEGRADATION_FACTOR,
  ATTR_ENABLE_ALSO,
  ATTR_ENABLE,
  ATTR_EQUAL_OR_OPPOSITE_OUTPUT,
  ATTR_FALL_CAPACITANCE_RANGE,
  ATTR_FALL_CAPACITANCE,
  ATTR_FALL_CONSTRAINT,
  ATTR_FALL_CURRENT_SLOPE_AFTER_THRESHOLD,
  ATTR_FALL_CURRENT_SLOPE_BEFORE_THRESHOLD,
  ATTR_FALL_DELAY_INTERCEPT,
  ATTR_FALL_PIN_RESISTANCE,
  ATTR_FALL_POWER,
  ATTR_FALL_PROPAGATION,
  ATTR_FALL_RESISTANCE,
  ATTR_FALL_TIME_AFTER_THRESHOLD,
  ATTR_FALL_TIME_BEFORE_THRESHOLD,
  ATTR_FALL_TRANSITION_DEGRADATION,
  ATTR_FALL_TRANSITION,
  ATTR_FALLING_TOGETHER_GROUP,
  ATTR_FANOUT_AREA,
  ATTR_FANOUT_CAPACITANCE,
  ATTR_FANOUT_LENGTH,
  ATTR_FANOUT_LOAD,
  ATTR_FANOUT_RESISTANCE,
  ATTR_FAULT_MODEL,
  ATTR_FAULTS_LUT_TEMPLATE,
  ATTR_FF_BANK,
  ATTR_FF,
  ATTR_FPGA_DOMAIN_STYLE,
  ATTR_FPGA_TECHNOLOGY,
  ATTR_FUNCTION,
  ATTR_FUNCTIONAL_YIELD_METRIC,
  ATTR_GENERATED_CLOCK,
  ATTR_GEOMETRY_PRINT,
  ATTR_HANDLE_NEGATIVE_CONSTRAINT,
  ATTR_HAS_BUILTIN_PAD,
  ATTR_HYPERBOLIC_NOISE_ABOVE_HIGH,
  ATTR_HYPERBOLIC_NOISE_BELOW_LOW,
  ATTR_HYPERBOLIC_NOISE_HIGH,
  ATTR_HYPERBOLIC_NOISE_LOW,
  ATTR_HYSTERESIS,
  ATTR_IN_PLACE_SWAP_MODE,
  ATTR_INDEX_1,
  ATTR_INDEX_2,
  ATTR_INDEX_3,
  ATTR_INPUT_MAP,
  ATTR_INPUT_SIGNAL_LEVEL,
  ATTR_INPUT_THRESHOLD_PCT_FALL,
  ATTR_INPUT_THRESHOLD_PCT_RISE,
  ATTR_INPUT_VOLTAGE,
  ATTR_INTERFACE_TIMING,
  ATTR_INTERNAL_NODE,
  ATTR_INTERNAL_POWER,
  ATTR_INTRINSIC_FALL,
  ATTR_INTRINSIC_PARASITIC,
  ATTR_INTRINSIC_RISE,
  ATTR_INVERTED_OUTPUT,
  ATTR_IO_TYPE,
  ATTR_IS_CLOCK_GATING_CELL,
  ATTR_IS_FILLER_CELL,
  ATTR_IS_PAD,
  ATTR_IV_LUT_TEMPLATE,
  ATTR_K_PROCESS_CELL_FALL,
  ATTR_K_PROCESS_CELL_LEAKAGE_POWER,
  ATTR_K_PROCESS_CELL_RISE,
  ATTR_K_PROCESS_DRIVE_CURRENT,
  ATTR_K_PROCESS_DRIVE_FALL,
  ATTR_K_PROCESS_DRIVE_RISE,
  ATTR_K_PROCESS_FALL_DELAY_INTERCEPT,
  ATTR_K_PROCESS_FALL_PIN_RESISTANCE,
  ATTR_K_PROCESS_FALL_PROPAGATION,
  ATTR_K_PROCESS_FALL_TRANSITION,
  ATTR_K_PROCESS_HOLD_FALL,
  ATTR_K_PROCESS_HOLD_RISE,
  ATTR_K_PROCESS_INTERNAL_POWER,
  ATTR_K_PROCESS_INTRINSIC_FALL,
  ATTR_K_PROCESS_INTRINSIC_RISE,
  ATTR_K_PROCESS_MIN_PERIOD,
  ATTR_K_PROCESS_MIN_PULSE_WIDTH_HIGH,
  ATTR_K_PROCESS_MIN_PULSE_WIDTH_LOW,
  ATTR_K_PROCESS_NOCHANGE_FALL,
  ATTR_K_PROCESS_NOCHANGE_RISE,
  ATTR_K_PROCESS_PIN_CAP,
  ATTR_K_PROCESS_RECOVERY_FALL,
  ATTR_K_PROCESS_RECOVERY_RISE,
  ATTR_K_PROCESS_REMOVAL_FALL,
  ATTR_K_PROCESS_REMOVAL_RISE,
  ATTR_K_PROCESS_RISE_TRANSITION,
  ATTR_K_PROCESS_RISE_DELAY_INTERCEPT,
  ATTR_K_PROCESS_RISE_PIN_RESISTANCE,
  ATTR_K_PROCESS_RISE_PROPAGATION,
  ATTR_K_PROCESS_SETUP_FALL,
  ATTR_K_PROCESS_SETUP_RISE,
  ATTR_K_PROCESS_SKEW_FALL,
  ATTR_K_PROCESS_SKEW_RISE,
  ATTR_K_PROCESS_SLOPE_FALL,
  ATTR_K_PROCESS_SLOPE_RISE,
  ATTR_K_PROCESS_WIRE_CAP,
  ATTR_K_PROCESS_WIRE_RES,
  ATTR_K_TEMP_CELL_FALL,
  ATTR_K_TEMP_CELL_LEAKAGE_POWER,
  ATTR_K_TEMP_CELL_RISE,
  ATTR_K_TEMP_DRIVE_CURRENT,
  ATTR_K_TEMP_DRIVE_FALL,
  ATTR_K_TEMP_DRIVE_RISE,
  ATTR_K_TEMP_FALL_DELAY_INTERCEPT,
  ATTR_K_TEMP_FALL_PIN_RESISTANCE,
  ATTR_K_TEMP_FALL_PROPAGATION,
  ATTR_K_TEMP_FALL_TRANSITION,
  ATTR_K_TEMP_HOLD_FALL,
  ATTR_K_TEMP_HOLD_RISE,
  ATTR_K_TEMP_INTERNAL_POWER,
  ATTR_K_TEMP_INTRINSIC_FALL,
  ATTR_K_TEMP_INTRINSIC_RISE,
  ATTR_K_TEMP_MIN_PERIOD,
  ATTR_K_TEMP_MIN_PULSE_WIDTH_HIGH,
  ATTR_K_TEMP_MIN_PULSE_WIDTH_LOW,
  ATTR_K_TEMP_NOCHANGE_FALL,
  ATTR_K_TEMP_NOCHANGE_RISE,
  ATTR_K_TEMP_PIN_CAP,
  ATTR_K_TEMP_RECOVERY_FALL,
  ATTR_K_TEMP_RECOVERY_RISE,
  ATTR_K_TEMP_REMOVAL_FALL,
  ATTR_K_TEMP_REMOVAL_RISE,
  ATTR_K_TEMP_RISE_TRANSITION,
  ATTR_K_TEMP_RISE_DELAY_INTERCEPT,
  ATTR_K_TEMP_RISE_PIN_RESISTANCE,
  ATTR_K_TEMP_RISE_PROPAGATION,
  ATTR_K_TEMP_SETUP_FALL,
  ATTR_K_TEMP_SETUP_RISE,
  ATTR_K_TEMP_SKEW_FALL,
  ATTR_K_TEMP_SKEW_RISE,
  ATTR_K_TEMP_SLOPE_FALL,
  ATTR_K_TEMP_SLOPE_RISE,
  ATTR_K_TEMP_WIRE_CAP,
  ATTR_K_TEMP_WIRE_RES,
  ATTR_K_VOLT_CELL_FALL,
  ATTR_K_VOLT_CELL_LEAKAGE_POWER,
  ATTR_K_VOLT_CELL_RISE,
  ATTR_K_VOLT_DRIVE_CURRENT,
  ATTR_K_VOLT_DRIVE_FALL,
  ATTR_K_VOLT_DRIVE_RISE,
  ATTR_K_VOLT_FALL_DELAY_INTERCEPT,
  ATTR_K_VOLT_FALL_PIN_RESISTANCE,
  ATTR_K_VOLT_FALL_PROPAGATION,
  ATTR_K_VOLT_FALL_TRANSITION,
  ATTR_K_VOLT_HOLD_FALL,
  ATTR_K_VOLT_HOLD_RISE,
  ATTR_K_VOLT_INTERNAL_POWER,
  ATTR_K_VOLT_INTRINSIC_FALL,
  ATTR_K_VOLT_INTRINSIC_RISE,
  ATTR_K_VOLT_MIN_PERIOD,
  ATTR_K_VOLT_MIN_PULSE_WIDTH_HIGH,
  ATTR_K_VOLT_MIN_PULSE_WIDTH_LOW,
  ATTR_K_VOLT_NOCHANGE_FALL,
  ATTR_K_VOLT_NOCHANGE_RISE,
  ATTR_K_VOLT_PIN_CAP,
  ATTR_K_VOLT_RECOVERY_FALL,
  ATTR_K_VOLT_RECOVERY_RISE,
  ATTR_K_VOLT_REMOVAL_FALL,
  ATTR_K_VOLT_REMOVAL_RISE,
  ATTR_K_VOLT_RISE_TRANSITION,
  ATTR_K_VOLT_RISE_DELAY_INTERCEPT,
  ATTR_K_VOLT_RISE_PIN_RESISTANCE,
  ATTR_K_VOLT_RISE_PROPAGATION,
  ATTR_K_VOLT_SETUP_FALL,
  ATTR_K_VOLT_SETUP_RISE,
  ATTR_K_VOLT_SKEW_FALL,
  ATTR_K_VOLT_SKEW_RISE,
  ATTR_K_VOLT_SLOPE_FALL,
  ATTR_K_VOLT_SLOPE_RISE,
  ATTR_K_VOLT_WIRE_CAP,
  ATTR_K_VOLT_WIRE_RES,
  ATTR_LATCH_BANK,
  ATTR_LATCH,
  ATTR_LEAKAGE_CURRENT,
  ATTR_LEAKAGE_POWER_UNIT,
  ATTR_LEAKAGE_POWER,
  ATTR_LIBRARY_FEATURES,
  ATTR_LIBRARY,
  ATTR_LU_TABLE_TEMPLATE,
  ATTR_LUT,
  ATTR_MAP_ONLY,
  ATTR_MAX_CAPACITANCE,
  ATTR_MAX_FANOUT,
  ATTR_MAX_INPUT_NOISE_WIDTH,
  ATTR_MAX_TRANS,
  ATTR_MAX_TRANSITION,
  ATTR_MEMBERS,
  ATTR_MIN_CAPACITANCE,
  ATTR_MIN_FANOUT,
  ATTR_MIN_INPUT_NOISE_WIDTH,
  ATTR_MIN_PERIOD,
  ATTR_MIN_PULSE_WIDTH_HIGH,
  ATTR_MIN_PULSE_WIDTH_LOW,
  ATTR_MIN_PULSE_WIDTH,
  ATTR_MIN_TRANSITION,
  ATTR_MINIMUM_PERIOD,
  ATTR_MODE_DEFINITION,
  ATTR_MULTICELL_PAD_PIN,
  ATTR_NEXT_STATE,
  ATTR_NEXTSTATE_TYPE,
  ATTR_NOISE_IMMUNITY_ABOVE_HIGH,
  ATTR_NOISE_IMMUNITY_BELOW_LOW,
  ATTR_NOISE_IMMUNITY_HIGH,
  ATTR_NOISE_IMMUNITY_LOW,
  ATTR_NOISE_LUT_TEMPLATE,
  ATTR_NOM_CALC_MODE,
  ATTR_NOM_PROCESS,
  ATTR_NOM_TEMPERATURE,
  ATTR_NOM_VOLTAGE,
  ATTR_OPERATING_CONDITIONS,
  ATTR_ORDERS,
  ATTR_OUTPUT_CURRENT_TEMPLATE,
  ATTR_OUTPUT_SIGNAL_LEVEL,
  ATTR_OUTPUT_THRESHOLD_PCT_FALL,
  ATTR_OUTPUT_THRESHOLD_PCT_RISE,
  ATTR_OUTPUT_VOLTAGE,
  ATTR_PAD_CELL,
  ATTR_PAD_TYPE,
  ATTR_PARAMETER1,
  ATTR_PARAMETER2,
  ATTR_PARAMETER3,
  ATTR_PARAMETER4,
  ATTR_PARAMETER5,
  ATTR_PART,
  ATTR_PIECE_DEFINE,
  ATTR_PIECE_TYPE,
  ATTR_PIN_FUNC_TYPE,
  ATTR_PIN_OPPOSITE,
  ATTR_PIN,
  ATTR_POLY_TEMPLATE,
  ATTR_POWER_CELL_TYPE,
  ATTR_POWER_LEVEL,
  ATTR_POWER_LUT_TEMPLATE,
  ATTR_POWER_POLY_TEMPLATE,
  ATTR_POWER_MODEL,
  ATTR_POWER_RAIL,
  ATTR_POWER_SUPPLY_NAMESTRING,
  ATTR_POWER_SUPPLY,
  ATTR_POWER,
  ATTR_PREFER_TIED,
  ATTR_PREFERRED,
  ATTR_PREFERRED_INPUT_PAD_VOLTAGE,
  ATTR_PREFERRED_OUTPUT_PAD_SLEW_RATE_CONTROL,
  ATTR_PREFERRED_OUTPUT_PAD_VOLTAGE,
  ATTR_PRESET,
  ATTR_PRIMARY_OUTPUT,
  ATTR_PROCESS,
  ATTR_PROPAGATED_NOISE_HEIGHT_ABOVE_HIGH,
  ATTR_PROPAGATED_NOISE_HEIGHT_BELOW_LOW,
  ATTR_PROPAGATED_NOISE_HEIGHT_HIGH,
  ATTR_PROPAGATED_NOISE_HEIGHT_LOW,
  ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_ABOVE_HIGH,
  ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_BELOW_LOW,
  ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_HIGH,
  ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_LOW,
  ATTR_PROPAGATED_NOISE_WIDTH_ABOVE_HIGH,
  ATTR_PROPAGATED_NOISE_WIDTH_BELOW_LOW,
  ATTR_PROPAGATED_NOISE_WIDTH_HIGH,
  ATTR_PROPAGATED_NOISE_WIDTH_LOW,
  ATTR_PROPAGATION_LUT_TEMPLATE,
  ATTR_PULLING_CURRENT,
  ATTR_PULLING_RESISTANCE_UNIT,
  ATTR_PULLING_RESISTANCE,
  ATTR_RAIL_CONNECTION,
  ATTR_RELATED_BUS_EQUIVALENT,
  ATTR_RELATED_BUS_PINS,
  ATTR_RELATED_INPUTS,
  ATTR_RELATED_OUTPUT_PIN,
  ATTR_RELATED_OUTPUTS,
  ATTR_RELATED_PG_PIN,
  ATTR_RELATED_PIN,
  ATTR_RESISTANCE,
  ATTR_RESOURCE_USAGE,
  ATTR_RETAIN_FALL_SLEW,
  ATTR_RETAIN_RISE_SLEW,
  ATTR_RETAINING_FALL,
  ATTR_RETAINING_RISE,
  ATTR_REVISION,
  ATTR_RISE_CAPACITANCE_RANGE,
  ATTR_RISE_CAPACITANCE,
  ATTR_RISE_CONSTRAINT,
  ATTR_RISE_CURRENT_SLOPE_AFTER_THRESHOLD,
  ATTR_RISE_CURRENT_SLOPE_BEFORE_THRESHOLD,
  ATTR_RISE_DELAY_INTERCEPT,
  ATTR_RISE_PIN_RESISTANCE,
  ATTR_RISE_POWER,
  ATTR_RISE_PROPAGATION,
  ATTR_RISE_RESISTANCE,
  ATTR_RISE_TIME_AFTER_THRESHOLD,
  ATTR_RISE_TIME_BEFORE_THRESHOLD,
  ATTR_RISE_TRANSITION_DEGRADATION,
  ATTR_RISE_TRANSITION,
  ATTR_RISING_TOGETHER_GROUP,
  ATTR_ROUTING_LAYERS,
  ATTR_ROUTING_TRACK,
  ATTR_SCALED_CELL,
  ATTR_SCALING_FACTORS,
  ATTR_SDF_COND_END,
  ATTR_SDF_COND_START,
  ATTR_SDF_COND,
  ATTR_SDF_EDGES,
  ATTR_SIGNAL_TYPE,
  ATTR_SIMULATION,
  ATTR_SINGLE_BIT_DEGENERATE,
  ATTR_SLEW_CONTROL,
  ATTR_SLEW_DERATE_FROM_LIBRARY,
  ATTR_SLEW_LOWER_THRESHOLD_PCT_FALL,
  ATTR_SLEW_LOWER_THRESHOLD_PCT_RISE,
  ATTR_SLEW_TYPE,
  ATTR_SLEW_UPPER_THRESHOLD_PCT_FALL,
  ATTR_SLEW_UPPER_THRESHOLD_PCT_RISE,
  ATTR_SLOPE_FALL,
  ATTR_SLOPE_RISE,
  ATTR_SLOPE,
  ATTR_STATE_FUNCTION,
  ATTR_STATETABLE,
  ATTR_STEADY_STATE_CURRENT_HIGH,
  ATTR_STEADY_STATE_CURRENT_LOW,
  ATTR_STEADY_STATE_CURRENT_TRISTATE,
  ATTR_SWITCHING_INTERVAL,
  ATTR_SWITCHING_TOGETHER_GROUP,
  ATTR_TABLE,
  ATTR_TECHNOLOGY,
  ATTR_TEMPERATURE,
  ATTR_TEST_CELL,
  ATTR_TEST_OUTPUT_ONLY,
  ATTR_THREE_STATE,
  ATTR_TIME_UNIT,
  ATTR_TIMING_MODEL_TYPE,
  ATTR_TIMING_RANGE,
  ATTR_TIMING_SENSE,
  ATTR_TIMING_TYPE,
  ATTR_TIMING,
  ATTR_TLATCH,
  ATTR_TREE_TYPE,
  ATTR_TYPE,
  ATTR_USE_FOR_SIZE_ONLY,
  ATTR_VALUE,
  ATTR_VALUES,
  ATTR_VARIABLE_1,
  ATTR_VARIABLE_2,
  ATTR_VARIABLE_3,
  ATTR_VHDL_NAME,
  ATTR_VIH,
  ATTR_VIL,
  ATTR_VIMAX,
  ATTR_VIMIN,
  ATTR_VOH,
  ATTR_VOL,
  ATTR_VOLTAGE_UNIT,
  ATTR_VOLTAGE,
  ATTR_VOMAX,
  ATTR_VOMIN,
  ATTR_WHEN_END,
  ATTR_WHEN_START,
  ATTR_WHEN,
  ATTR_WIRE_LOAD_FROM_AREA,
  ATTR_WIRE_LOAD_SELECTION,
  ATTR_WIRE_LOAD_TABLE,
  ATTR_WIRE_LOAD,
  ATTR_X_FUNCTION,

  ATTR_END
};

/// @brief AttrType の内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   AttrType attr);

END_NAMESPACE_YM_DOTLIB

#endif // ATTRTYPE_H
