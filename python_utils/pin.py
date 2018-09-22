#! /usr/bin/env python3

### @file pin.py
### @brief PinHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from strlistgroup import StrListGroupClassDef


class PinClassDef(StrListGroupClassDef) :

    def __init__(self) :
        self.data_type = 'pin'
        self.desc = 'ピン'
        self.ast_class = 'AstPin'
        self.group_class = 'PinHandler'
        self.attr_list = [
            # ( 属性名, 属性の型, メンバ変数名 ) のリスト
            ( 'bit_width', 'int', 'mBitWidth', False ),
            ( 'capacitance', 'float', 'mCapacitance', False ),
            ( 'clock_gate_clock_pin', 'bool', 'mClockGateClockPin', False ),
            ( 'clock_gate_enable_pin', 'bool', 'mClockGateEnablePin', False ),
            ( 'clock_gate_test_pin', 'bool', 'mClockGateTestPin', False ),
            ( 'clock_gate_obs_pin', 'bool', 'mClockGateObsPin', False ),
            ( 'clock_gate_out_pin', 'bool', 'mClockGateOutPin', False ),
            ( 'complementary_pin', 'string', 'mComplementaryPin', False ),
            ( 'connection_class', 'string', 'mConnectionClass', False ),
            ( 'direction', 'direction', 'mDirection', True ),
            ( 'dont_fault', 'string', 'mDontFault', False ),
            ( 'drive_current', 'float', 'mDriveCurrent', False ),
            ( 'driver_type', 'string', 'mDriverType', False ),
            ( 'fall_capacitance', 'float', 'mFallCapacitance', False ),
            ( 'fall_current_slope_after_threshold', 'float', 'mFallCurrentSlopeAfterThreshold', False ),
            ( 'fall_current_slope_before_threshold', 'float', 'mFallCurrentSlopeBeforeThreshold', False ),
            ( 'fall_time_after_threshold', 'float', 'mFallTimeAfterThreshold', False ),
            ( 'fall_time_before_threshold', 'float', 'mFallTimeBeforeThreshold', False ),
            ( 'fanout_load', 'float', 'mFanoutLoad', False ),
            ( 'fault_model', 'string', 'mFaultModel', False ),
            ( 'function', 'expr', 'mFunction', False ),
            ( 'has_builtin_pad', 'bool', 'mHasBuiltinPad', False ),
            ( 'hysteresis', 'bool', 'mHysteresis', False ),
            ( 'input_map', 'string', 'mInputMap', False ),
            ( 'input_signal_level', 'string', 'mInputSignalLevel', False ),
            ( 'input_threshold_pct_fall', 'float', 'mInputThresholdPctFall', False ),
            ( 'input_threshold_pct_rise', 'float', 'mInputThresholdPctRise', False ),
            ( 'input_voltage', 'string', 'mInputVoltage', False ),
            ( 'internal_node', 'string', 'mInternalNode', False ),
            ( 'inverted_output', 'bool', 'mInvertedOutput', False ),
            ( 'isolation_cell_enable_pin', 'bool', 'mIsolationCellEnablePin', False ),
            ( 'level_shifter_enable_pin', 'bool', 'mLevelShifterEnablePin', False ),
            ( 'map_to_logic', 'bool', 'mMapToLogic', False ),
            ( 'max_capacitance', 'float', 'mMaxCapacitance', False ),
            ( 'max_fanout', 'float', 'mMaxFanout', False ),
            ( 'max_input_noise_width', 'float', 'mMaxInputNoiseWidth', False ),
            ( 'max_transition', 'float', 'mMaxTransition', False ),
            ( 'min_capacitance', 'float', 'mMinCapacitance', False ),
            ( 'min_fanout', 'float', 'mMinFanout', False ),
            ( 'min_input_noise_width', 'float', 'mMinInputNoiseWidth', False ),
            ( 'min_pulse_width_high', 'float', 'mMinPulseWidthHigh', False ),
            ( 'min_pulse_width_low', 'float', 'mMinPulseWidthLow', False ),
            ( 'min_transition', 'float', 'mMinTransition', False ),
            ( 'min_period', 'float', 'mMinPeriod', False ),
            ( 'multicell_pad_pin', 'bool', 'mMulticellPadPin', False ),
            ( 'nextstate_type', 'string', 'mNextstateType', False ),
            ( 'output_signal_level', 'string', 'mOutputSignalLevel', False),
            ( 'output_voltage', 'string', 'mOutputVoltage', False ),
            ( 'pg_function', 'function', 'mPgFunction', False ),
            ( 'pin_func_type', 'string', 'mPinFuncType', False ),
            ( 'power_down_function', 'function', 'mPowerDownFunction', False ),
            ( 'prefer_tied', 'string', 'mPreferTied', False ),
            ( 'primary_output', 'bool', 'mPrimaryOutput', False ),
            ( 'pulling_current', 'float', 'mPullingCurrent', False ),
            ( 'pulling_resistance', 'float', 'mPullingResistance', False ),
            ( 'pulse_clock', 'string', 'mPulseClock', False ),
            ( 'related_ground_pin', 'string', 'mRelatedGroundPin', False ),
            ( 'related_power_pin', 'string', 'mRelatedPowerPin', False ),
            ( 'rise_capacitance', 'float', 'mRiseCapacitance', False ),
            ( 'rise_current_slope_after_threshold', 'float', 'mRiseCurrentSlopeAfterThreshold', False ),
            ( 'rise_current_slope_before_threshold', 'float', 'mRiseCurrentSlopeBeforeThreshold', False ),
            ( 'rise_time_after_threshold', 'float', 'mRiseTimeAfterThreshold', False ),
            ( 'rise_time_before_threshold', 'float', 'mRiseTimeBeforeThreshold', False ),
            ( 'signal_type', 'string', 'mSignalType', False ),
            ( 'slew_control', 'string', 'mSlewControl', False ),
            ( 'slew_lower_threshold_pct_fall', 'float', 'mSlewLowerThresholdPctFall', False ),
            ( 'slew_lower_threshold_pct_rise', 'float', 'mSlewLowerThresholdPctRise', False ),
            ( 'slew_upper_threshold_pct_fall', 'float', 'mSlewUpperThresholdPctFall', False ),
            ( 'slew_upper_threshold_pct_rise', 'float', 'mSlewUpperThresholdPctRise', False ),
            ( 'state_function', 'expr', 'mStateFunction', False ),
            ( 'std_cell_main_rail', 'bool', 'mStdCellMainRail', False ),
            ( 'switch_function', 'function', 'mSwitchFunction', False ),
            ( 'switch_pin', 'bool', 'mSwitchPin', False ),
            ( 'test_output_only', 'bool', 'mTestOutputOnly', False ),
            ( 'three_state', 'expr', 'mThreeState', False ),
            ( 'vhdl_name', 'string', 'mVhdlName', False ),
            ( 'x_function', 'expr', 'mXFunction', False ),
            ( 'fall_capacitance_range', 'float2complex', 'mFallCapacitanceRange', False ),
            ( 'rise_capacitance_range', 'float2complex', 'mRiseCapacitanceRange', False ),
            ( 'power_gating_pin', 'pg_pin', 'mPowerGatingPin', False ),
            ( 'dc_current', 'dc_current', 'mDcCurrent', False ),
            ( 'electromigration', 'electromigration', 'mElectromigration', False ),
            ( 'hyperbolic_noise_above_high', '???', 'mHyperbolicNoiseAboveHigh', False ),
            ( 'hyperbolic_noise_below_low', '???', 'mHyperbolicNoiseBeforeLow', False ),
            ( 'hyperbolic_noise_high', '???', 'mHyperbolicNoiseHigh', False ),
            ( 'hyperbolic_noise_low', '???', 'mHyperbolicNoiseLow', False ),
            ( 'input_signal_swing', '???', 'mInputSignalSwing', False ),
            ( 'max_capacitance', '???', 'mMaxCapacitance', False ),
            ( 'max_transition', '???', 'mMaxTransition', False ),
            ( 'min_pulse_width', '???', 'mMinPulseWidth', False ),
            ( 'minimum_period', '???', 'mMinimumPeriod', False ),
            ( 'output_signal_swing', '???', 'mOutputSignalSwing', False ),
            ( 'pin_capacitance', '???', 'mPinCapacitance', False ),
            ( 'timing', 'timing', 'mTiming', False ),
            ( 'tlatch', 'tlatch', 'mTlatch', False )
            ]
