#! /usr/bin/env python3

### @file timing.py
### @brief TimingHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2019 Yusuke Matsunaga
### All rights reserved.

from strgroup import StrGroupClassDef


class TimingClassDef(StrGroupClassDef) :

    def __init__(self) :
        super().__init__()
        self.data_type = 'timing'
        self.desc = 'タイミング'
        self.group_class = 'TimingHandler'
        self.attr_list = [
            # ( 属性名, 属性の型, メンバ変数名, 必須フラグ, 複数フラグ ) のリスト
            # simple attribute
            ( 'clock_gating_flag', 'bool', 'mClockGatingFlag', False, False ),
            ( 'default_timing', 'bool', 'mDefaultTiming', False, False ),
            ( 'fall_resistance', 'float', 'mFallResistance', False, False ),
            ( 'fpga_arc_condition', 'expr', 'mFpgaArcCondition', False, False ),
            ( 'fpga_domain_style', 'string', 'mFpgaDomainStyle', False, False ),
            ( 'interdependence_id', 'int', 'mInterdependenceId', False, False ),
            ( 'intrinsic_fall', 'float', 'mIntrinsicFall', False, False ),
            ( 'intrinsic_rise', 'float', 'mIntrinsicRise', False, False ),
            ( 'related_bus_equivalent', 'string', 'mRelatedBusEquivalent', False, False ),
            ( 'related_bus_pins', 'string', 'mRelatedBusPins', False, False ),
            ( 'related_output_pin', 'string', 'mRelatedOutputPin', False, False ),
            ( 'related_pin', 'string', 'mRelatedPin', False, False ),
            ( 'rise_resistance', 'float', 'mRiseResistance', False, False ),
            ( 'sdf_cond', 'function', 'mSdfCond', False, False ),
            ( 'sdf_cond_end', 'function', 'mSdfCondEnd', False, False ),
            ( 'sdf_cond_start', 'function', mSdfCondStart, False, False ),
            ( 'sdf_edges', 'string', 'mSdfEdges', False, False ),
            ( 'slope_fall', 'float' 'mSlopeFall', False, False ),
            ( 'slope_rise', 'float', 'mSlopeRise', False, False ),
            ( 'steady_state_resistance_above_high', 'float', 'mSteadyStateResistanceAboveHigh', False, False ),
            ( 'steady_state_resistance_below_low', 'float', 'mSteadyStateResistanceBelowLow', False, False ),
            ( 'steady_state_resistance_high', 'float', 'mSteadyStateResistanceHigh', False, False ),
            ( 'steady_state_resistance_low', 'float', 'mSteadyStateResistanceLow', False, False ),
            ( 'tied_off', 'bool', 'mTiedOff', False, False ),
            ( 'timing_sense', 'timing_sense', 'mTimingSense', False, False ),
            ( 'timing_type', 'timing_type', 'mTimingType', False, False ),
            ( 'wave_fall_sampling_index', 'int', 'mWaveFallSamplingINdex', False, False ),
            ( 'wave_rise_sampling_index', 'int', 'mWaveRiseSamplingINdex', False, False ),
            ( 'when', 'expr', 'mWhen', False, False ),
            ( 'when_end', 'expr', 'mWhenEnd', False, False ),
            ( 'when_start', 'expr', 'mWhenStart', False, False ),
            # complex attribute
            ( 'fall_delay_intercept', 'int_float', 'mFallDelayIntercept', False, True ),
            ( 'fall_pin_resistance', 'int_float', 'mFallPinIntercept', False, True ),
            ( 'mode', 'str_str', 'mMode', False, False ),
            ( 'pin_name_map', 'str_list', 'mPinNameMap', False, False ),
            ( 'rise_delay_intercept', 'int_float', 'mRiseDelayIntercept', False, True ),
            ( 'rise_pin_resistance', 'int_float', 'mRisePinIntercept', False, True ),
            ( 'wave_fall', 'int_list', 'mWaveFall', False, False ),
            ( 'wave_rise', 'int_list', 'mWaveRise', False, False ),
            ( 'wave_fall_time_interval', 'float_list', 'mWaveFallInterval', False, False ),
            ( 'wave_rise_time_interval', 'float_list', 'mWaveRiseInterval', False, False ),
            # group attribute
            ( 'cell_degradation', 'cell_degradation', 'mCellDegradation', False, False ),
            ( 'cell_fall', '???', 'mCellFall', False, False ),
            ( 'cell_rise', '???', 'mCellFall', False, False ),
            ( 'fall_constraint', '???', 'mFallConstraint', False, False ),
            ( 'fall_propagation', '???', 'mFallPropagation', False, False ),
            ( 'fall_transition', '???', 'mFallTransition', False, False ),
            ( 'noise_immunity_above_high', '???', 'mNoiseImmunityAboveHigh', False, False ),
            ( 'noise_immunity_below_low', '???', 'mNoiseImmunityBelowLow', False, False ),
            ( 'noise_immunity_high', '???', 'mNoiseImmunityHigh', False, False ),
            ( 'noise_immunity_low', '???', 'mNoiseImmunityLow', False, False ),
            ( 'output_current_fall', '???', 'mOutputCurrentFall', False, False ),
            ( 'output_current_rise', '???', 'mOutputCurrentRise', False, False ),
            ( 'propagated_noise_height_above_high', '???', 'mPropagatedNoiseHeightAboveHigh', False, False ),
            ( 'propagated_noise_height_below_low', '???', 'mPropagatedNoiseHeightBelowLow', False, False ),
            ( 'propagated_noise_height_high', '???', 'mPropagatedNoiseHeightHigh', False, False ),
            ( 'propagated_noise_height_low', '???', 'mPropagatedNoiseHeightLow', False, False ),
            ( 'propagated_noise_peak_time_ratio_above_high', '???', 'mPropagatedNoisePeakTimeRatioAboveHigh', False, False ),
            ( 'propagated_noise_peak_time_ratio_below_low', '???', 'mPropagatedNoisePeakTimeRatioBelowLow', False, False ),
            ( 'propagated_noise_peak_time_ratio_high', '???', 'mPropagatedNoisePeakTimeRatioHigh', False, False ),
            ( 'propagated_noise_peak_time_ratio_low', '???', 'mPropagatedNoisePeakTimeRatioLow', False, False ),
            ( 'propagated_noise_width_above_high', '???', 'mPropagatedNoiseWidthAboveHigh', False, False ),
            ( 'propagated_noise_width_below_low', '???', 'mPropagatedNoiseWidthBelowLow', False, False ),
            ( 'propagated_noise_width_high', '???', 'mPropagatedNoiseWidthHigh', False, False ),
            ( 'propagated_noise_width_low', '???', 'mPropagatedNoiseWidthLow', False, False ),
            ( 'receiver_capacitance1_fall', '???', 'mReceiverCapacitance1Fall', False, False ),
            ( 'receiver_capacitance1_rise', '???', 'mReceiverCapacitance1Rise', False, False ),
            ( 'receiver_capacitance2_fall', '???', 'mReceiverCapacitance2Fall', False, False ),
            ( 'receiver_capacitance2_rise', '???', 'mReceiverCapacitance2Rise', False, False ),
            ( 'retaining_fall', '???', 'mRetainingFall', False, False ),
            ( 'retaining_rise', '???', 'mRetainingFall', False, False ),
            ( 'retain_fall_slew', '???', 'mRetainFallSlew', False, False ),
            ( 'retain_rise_slew', '???', 'mRetainRiseSlew', False, False ),
            ( 'rise_constraint', '???', 'mRiseConstraint', False, False ),
            ( 'rise_propagation', '???', 'mRisePropagation', False, False ),
            ( 'rise_transition', '???', 'mRiseTransition', False, False ),
            ( 'steady_state_current_high', '???', 'mSteadyStateCurrentHigh', False, False ),
            ( 'steady_state_current_low', '???', 'mSteadyStateCurrentLow', False, False ),
            ( 'steady_state_current_tristate', '????', 'mSteadyStateCurrentTristate', False, False )
            ]
