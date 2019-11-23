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
        super().__init__()
        self.data_type = 'pin'
        self.desc = 'ピン'
        self.group_class = 'PinHandler'
        self.attr_list = [
            # ( 属性名, 属性の型, メンバ変数名, 必須フラグ, 複数フラグ ) のリスト
            ( 'bit_width', 'int', 'mBitWidth', False, False ),
            ( 'capacitance', 'float', 'mCapacitance', False, False ),
            ( 'clock_gate_clock_pin', 'bool', 'mClockGateClockPin', False, False ),
            ( 'clock_gate_enable_pin', 'bool', 'mClockGateEnablePin', False, False ),
            ( 'clock_gate_test_pin', 'bool', 'mClockGateTestPin', False, False ),
            ( 'clock_gate_obs_pin', 'bool', 'mClockGateObsPin', False, False ),
            ( 'clock_gate_out_pin', 'bool', 'mClockGateOutPin', False, False ),
            ( 'complementary_pin', 'string', 'mComplementaryPin', False, False ),
            ( 'connection_class', 'string', 'mConnectionClass', False, False ),
            ( 'direction', 'direction', 'mDirection', True, False ),
            ( 'dont_fault', 'string', 'mDontFault', False, False ),
            ( 'drive_current', 'float', 'mDriveCurrent', False, False ),
            ( 'driver_type', 'string', 'mDriverType', False, False ),
            ( 'fall_capacitance', 'float', 'mFallCapacitance', False, False ),
            ( 'fall_current_slope_after_threshold', 'float', 'mFallCurrentSlopeAfterThreshold', False, False ),
            ( 'fall_current_slope_before_threshold', 'float', 'mFallCurrentSlopeBeforeThreshold', False, False ),
            ( 'fall_time_after_threshold', 'float', 'mFallTimeAfterThreshold', False, False ),
            ( 'fall_time_before_threshold', 'float', 'mFallTimeBeforeThreshold', False, False ),
            ( 'fanout_load', 'float', 'mFanoutLoad', False, False ),
            ( 'fault_model', 'string', 'mFaultModel', False, False ),
            ( 'function', 'expr', 'mFunction', False, False ),
            ( 'has_builtin_pad', 'bool', 'mHasBuiltinPad', False, False ),
            ( 'hysteresis', 'bool', 'mHysteresis', False, False ),
            ( 'input_map', 'string', 'mInputMap', False, False ),
            ( 'input_signal_level', 'string', 'mInputSignalLevel', False, False ),
            ( 'input_threshold_pct_fall', 'float', 'mInputThresholdPctFall', False, False ),
            ( 'input_threshold_pct_rise', 'float', 'mInputThresholdPctRise', False, False ),
            ( 'input_voltage', 'string', 'mInputVoltage', False, False ),
            ( 'internal_node', 'string', 'mInternalNode', False, False ),
            ( 'inverted_output', 'bool', 'mInvertedOutput', False, False ),
            ( 'isolation_cell_enable_pin', 'bool', 'mIsolationCellEnablePin', False, False ),
            ( 'level_shifter_enable_pin', 'bool', 'mLevelShifterEnablePin', False, False ),
            ( 'map_to_logic', 'bool', 'mMapToLogic', False, False ),
            ( 'max_capacitance', 'float', 'mMaxCapacitance', False, False ),
            ( 'max_fanout', 'float', 'mMaxFanout', False, False ),
            ( 'max_input_noise_width', 'float', 'mMaxInputNoiseWidth', False, False ),
            ( 'max_transition', 'float', 'mMaxTransition', False, False ),
            ( 'min_capacitance', 'float', 'mMinCapacitance', False, False ),
            ( 'min_fanout', 'float', 'mMinFanout', False, False ),
            ( 'min_input_noise_width', 'float', 'mMinInputNoiseWidth', False, False ),
            ( 'min_pulse_width_high', 'float', 'mMinPulseWidthHigh', False, False ),
            ( 'min_pulse_width_low', 'float', 'mMinPulseWidthLow', False, False ),
            ( 'min_transition', 'float', 'mMinTransition', False, False ),
            ( 'min_period', 'float', 'mMinPeriod', False, False ),
            ( 'multicell_pad_pin', 'bool', 'mMulticellPadPin', False, False ),
            ( 'nextstate_type', 'string', 'mNextstateType', False, False ),
            ( 'output_signal_level', 'string', 'mOutputSignalLevel', False, False ),
            ( 'output_voltage', 'string', 'mOutputVoltage', False, False ),
            ( 'pg_function', 'function', 'mPgFunction', False, False ),
            ( 'pin_func_type', 'string', 'mPinFuncType', False, False ),
            ( 'power_down_function', 'function', 'mPowerDownFunction', False, False ),
            ( 'prefer_tied', 'string', 'mPreferTied', False, False ),
            ( 'primary_output', 'bool', 'mPrimaryOutput', False, False ),
            ( 'pulling_current', 'float', 'mPullingCurrent', False, False ),
            ( 'pulling_resistance', 'float', 'mPullingResistance', False, False ),
            ( 'pulse_clock', 'string', 'mPulseClock', False, False ),
            ( 'related_ground_pin', 'string', 'mRelatedGroundPin', False, False ),
            ( 'related_power_pin', 'string', 'mRelatedPowerPin', False, False ),
            ( 'rise_capacitance', 'float', 'mRiseCapacitance', False, False ),
            ( 'rise_current_slope_after_threshold', 'float', 'mRiseCurrentSlopeAfterThreshold', False, False ),
            ( 'rise_current_slope_before_threshold', 'float', 'mRiseCurrentSlopeBeforeThreshold', False, False ),
            ( 'rise_time_after_threshold', 'float', 'mRiseTimeAfterThreshold', False, False ),
            ( 'rise_time_before_threshold', 'float', 'mRiseTimeBeforeThreshold', False, False ),
            ( 'signal_type', 'string', 'mSignalType', False, False ),
            ( 'slew_control', 'string', 'mSlewControl', False, False ),
            ( 'slew_lower_threshold_pct_fall', 'float', 'mSlewLowerThresholdPctFall', False, False ),
            ( 'slew_lower_threshold_pct_rise', 'float', 'mSlewLowerThresholdPctRise', False, False ),
            ( 'slew_upper_threshold_pct_fall', 'float', 'mSlewUpperThresholdPctFall', False, False ),
            ( 'slew_upper_threshold_pct_rise', 'float', 'mSlewUpperThresholdPctRise', False, False ),
            ( 'state_function', 'expr', 'mStateFunction', False, False ),
            ( 'std_cell_main_rail', 'bool', 'mStdCellMainRail', False, False ),
            ( 'switch_function', 'function', 'mSwitchFunction', False, False ),
            ( 'switch_pin', 'bool', 'mSwitchPin', False, False ),
            ( 'test_output_only', 'bool', 'mTestOutputOnly', False, False ),
            ( 'three_state', 'expr', 'mThreeState', False, False ),
            ( 'vhdl_name', 'string', 'mVhdlName', False, False ),
            ( 'x_function', 'expr', 'mXFunction', False, False ),
            ( 'fall_capacitance_range', 'float2complex', 'mFallCapacitanceRange', False, False ),
            ( 'rise_capacitance_range', 'float2complex', 'mRiseCapacitanceRange', False, False ),
            ( 'power_gating_pin', 'pg_pin', 'mPowerGatingPin', False, False ),
            ( 'dc_current', 'dc_current', 'mDcCurrent', False, False ),
            ( 'electromigration', 'electromigration', 'mElectromigration', False, False ),
            ( 'hyperbolic_noise_above_high', '???', 'mHyperbolicNoiseAboveHigh', False, False ),
            ( 'hyperbolic_noise_below_low', '???', 'mHyperbolicNoiseBeforeLow', False, False ),
            ( 'hyperbolic_noise_high', '???', 'mHyperbolicNoiseHigh', False, False ),
            ( 'hyperbolic_noise_low', '???', 'mHyperbolicNoiseLow', False, False ),
            ( 'input_signal_swing', '???', 'mInputSignalSwing', False, False ),
            ( 'max_capacitance', '???', 'mMaxCapacitance', False, False ),
            ( 'max_transition', '???', 'mMaxTransition', False, False ),
            ( 'min_pulse_width', '???', 'mMinPulseWidth', False, False ),
            ( 'minimum_period', '???', 'mMinimumPeriod', False, False ),
            ( 'output_signal_swing', '???', 'mOutputSignalSwing', False, False ),
            ( 'pin_capacitance', '???', 'mPinCapacitance', False, False ),
            ( 'timing', 'timing', 'mTiming', False, True ),
            ( 'tlatch', 'tlatch', 'mTlatch', False, False )
            ]


if __name__ == '__main__' :
    import gen_handler_code

    class_def = PinClassDef()
    gen_handler_code.main(class_def)
