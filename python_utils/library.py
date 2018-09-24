#! /usr/bin/env python3

### @file library.py
### @brief LibraryHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from str1group.py import Str1GroupClassDef


class LibraryClassDef(Str1GroupClassDef) :

    def __init__(self) :
        self.data_type = 'library'
        self.desc = 'ライブラリ'
        self.ast_class = 'AstLibrary'
        self.group_class = 'LibraryHandler'
        self.attr_list = [
            # ( 属性名, 属性の型, メンバ変数名, 必須フラグ, 複数フラグ ) のリスト

            # simple attributes
            ( 'bus_naming_style', 'string', 'mBusNamingStyle', False, False ),
            ( 'comment', 'string', 'mComment', False, False ),
            ( 'current_unit', 'string', 'mCurrentUnit', False, False ),
            ( 'date', 'string', 'mDate', False, False ),
            ( 'default_fpga_isd', 'string', 'mDefaultFpgaIsd', False, False ),
            ( 'default_threshold_voltage_group', 'string', 'mDefaultThresholdVoltageGroup', False ),
            ( 'delay_model', 'delay_model', 'mDelayModel', False, False ),
            ( 'em_temp_degradation_factor', 'float', 'mEmTempDegradationFactor', False, False ),
            ( 'fpga_domain_style', 'string', 'mFpgaDomainStyle', False, False ),
            ( 'fpga_technology', 'string', 'mFpgaTechnology', False, False ),
            ( 'in_place_swap_mode', 'string', 'mInPlaceSwapMode', False, False ),
            ( 'input_threshold_pct_fall', 'float', 'mInputThresholdPctFall', False, False ),
            ( 'input_threshold_pct_rise', 'float', 'mInputThresholdPctRise', False, False ),
            ( 'leakage_power_unit', 'string', 'mLeakagePowerUnit', False, False ),
            ( 'nom_calc_mode', 'string', 'mNomCalcMode', False, False ),
            ( 'nom_process', 'float', 'mNomProcess', False, False ),
            ( 'nom_temperature', 'float', 'mNomTemperature', False, False ),
            ( 'nom_voltage', 'float', 'mNomVoltage', False, False ),
            ( 'output_threshold_pct_fall', 'float', 'mOutputThresholdPctFall', False, False ),
            ( 'output_threshold_pct_rise', 'float', 'mOutputThresholdPctRise', False, False ),
            ( 'piece_type', 'string', 'mPieceType', False, False ),
            ( 'power_model', 'string', 'mPowerModel', False, False ),
            ( 'preferred_output_pad_slew_rate_control', 'string', 'mPreferredOutputPadSlewRateControl', False, False ),
            ( 'preferred_input_pad_voltage', 'string', 'mPreferredInputPadVoltage', False, False ),
            ( 'preffered_output_pad_voltage', 'string', 'mPreferredOutputPadVoltage', False, False ),
            ( 'pulling_resistance_unit', 'string', 'mPullingResistanceUnit', False, False ),
            ( 'revision', 'string', 'mRevision', False, False ),
            ( 'simulation', 'bool', 'mSimulation', False, False ),
            ( 'slew_derate_from_library', 'float', 'mSlewDerateFromLibrary', False, False ),
            ( 'slew_lower_threshold_pct_fall', 'float', 'mSlewLowerThresholdPctFall', False, False ),
            ( 'slew_lower_threshold_pct_rise', 'float', 'mSlewLowerThresholdPctRise', False, False ),
            ( 'slew_upper_threshold_pct_fall', 'float', 'mSlewUpperThresholdPctFall', False, False ),
            ( 'slew_upper_threshold_pct_rise', 'float', 'mSlewUpperThresholdPctRise', False, False ),
            ( 'time_unit', 'string', 'mTimeUnit', False, False ),
            ( 'voltage_unit', 'string', 'mVoltageUnit', False, False ),

            ( 'default_cell_leakage_power', 'float', 'mDefaultCellLeakagePower', False, False ),
            ( 'default_connection_class', 'string', 'mDefaultConnectionClass', False, False ),
            ( 'default_fanout_load', 'float', 'mDefaultFanoutLoad', False, False ),
            ( 'default_inout_pin_cap', 'float', 'mDefaultInoutPinCap', False, False ),
            ( 'default_input_pin_cap', 'float', 'mDefaultInputPinCap', False, False ),
            ( 'default_intrinsic_fall', 'float', 'mDefaultIntrinsicFall', False, False ),
            ( 'default_intrinsic_rise', 'float', 'mDefaultIntrinsicRise', False, False ),
            ( 'default_leakage_power_density', 'float', 'mDefaultLeakagePowerDensity', False, False ),
            ( 'default_max_capacitance', 'float', 'mDefaultMaxCapacitance', False, False ),
            ( 'default_max_fanout', 'float', 'mDefaultMaxFanout', False, False ),
            ( 'default_max_transition', 'float', 'mDefaultMaxTransition', False, False ),
            ( 'default_max_utilization', 'float', 'mDefaultMaxUtilization', False, False ),
            ( 'default_min_porosity', 'float', 'mDefaultMinPorosity', False, False ),
            ( 'default_operationg_conditions', 'string', 'mDefaultOperatingConditions', False, False ),
            ( 'default_output_pin_cap', 'float', 'mDefaultOutputPinCap', False, False ),
            ( 'default_slope_fall', 'float', 'mDefaultSlopeFall', False, False ),
            ( 'default_slope_rise', 'float', 'mDefaultSlopeRise', False, False ),
            ( 'default_wire_load', 'float', 'mDefaultWireLoad', False, False ),
            ( 'default_wire_load_area', 'float', 'mDefaultWireLoadArea', False, False ),
            ( 'default_wire_load_capacitance', 'float', 'mDefaultWireLoadCapacitance', False, False ),
            ( 'default_wire_load_mode', 'string', 'mDefaultWireLoadMode', False, False ),
            ( 'default_wire_load_resisitance', 'float', 'mDefaultWireLoadResistance', False, False ),
            ( 'default_wire_load_selection', 'string', 'mDefaultWireLoadSelection', False, False ),

            ( 'default_fall_delay_intercept', 'float', 'mDefaultFallDelayIntercept', False, False ),
            ( 'default_fall_pin_resistance', 'float', 'mDefaultFallPinResistance', False, False ),
            ( 'default_rise_delay_intercept', 'float', 'mDefaultRiseDelayIntercept', False, False ),
            ( 'default_rise_pin_resistance', 'float', 'mDefaultRisePinResistance', False, False ),

            ( 'default_inout_pin_fall_res', 'float', 'mDefaultInoutPinFallRes', False, False ),
            ( 'default_inout_pin_rise_res', 'float', 'mDefaultInoutPinRiseRes', False, False ),
            ( 'default_output_pin_fall_res', 'float', 'mDefaultOutputPinFallRes', False, False ),
            ( 'default_output_pin_rise_res', 'float', 'mDefaultOutputPinRiseRes', False, False ),

            ( 'k_process_cell_fall', 'float', 'mK_ProcessCellFall', False, False ),
            ( 'k_process_cell_rise', 'float', 'mK_ProcessCellRise', False, False ),
            ( 'k_process_cell_leakage_power', 'float', 'mK_ProcessCellLeakagePower', False, False ),
            ( 'k_process_drive_current', 'float', 'mK_ProcessDriveCurrent', False, False ),
            ( 'k_process_drive_fall', 'float', 'mK_ProcessDriveFall', False, False ),
            ( 'k_process_drive_rise', 'float', 'mK_ProcessDriveRise', False, False ),
            ( 'k_process_fall_delay_intercept', 'float', 'mK_ProcessFallDelayIntercept', False, False ),
            ( 'k_process_fall_pin_resistance', 'float', 'mK_ProcessFallPinResistance', False, False ),
            ( 'k_process_fall_propagation', 'float', 'mK_ProcessFallPropagation', False, False ),
            ( 'k_process_fall_transition', 'float', 'mK_ProcessFallPropagation', False, False ),
            ( 'k_process_hold_fall', 'float', 'mK_ProcessHoldFall', False, False ),
            ( 'k_process_hold_rise', 'float', 'mK_ProcessHoldRise', False, False ),
            ( 'k_process_inernal_power', 'float', 'mK_ProcessInternalPower', False, False ),
            ( 'k_process_intrinsic_fall', 'float', 'mK_ProcessIntrinsicFall', False, False ),
            ( 'k_process_intrinsic_rise', 'float', 'mK_ProcessIntrinsicRise', False, False ),
            ( 'k_process_min_period', 'float', 'mK_ProcessMinPeriod', False, False ),
            ( 'k_process_min_pulse_width_high', 'float', 'mK_ProcessMinPulseWidthHigh', False, False ),
            ( 'k_process_min_pulse_width_low', 'float', 'mK_ProcessMinPulseWidthLow', False, False ),
            ( 'k_process_nochange_fall', 'float', 'mK_ProcessNochangeFall', False, False ),
            ( 'k_process_nochange_rise', 'float', 'mK_ProcessNochangeRise', False, False ),
            ( 'k_process_pin_cap', 'float', 'mK_ProcessPinCap', False, False ),
            ( 'k_process_recovery_fall', 'float', 'mK_ProcessRecoveryFall', False, False ),
            ( 'k_process_recovery_rise', 'float', 'mK_ProcessRecoveryRise', False, False ),
            ( 'k_process_removal_fall', 'float', 'mK_ProcessRemovalFall', False, False ),
            ( 'k_process_removal_rise', 'float', 'mK_ProcessRemovalRise', False, False ),
            ( 'k_process_rise_delay_intercept', 'float', 'mK_ProcessRiseDelayIntercept', False, False ),
            ( 'k_process_rise_pin_resistance', 'float', 'mK_ProcessRisePinResistance', False, False ),
            ( 'k_process_rise_propagation', 'float', 'mK_ProcessRisePropagation', False, False ),
            ( 'k_process_rise_transition', 'float', 'mK_ProcessRisePropagation', False, False ),
            ( 'k_process_setup_fall', 'float', 'mK_ProcessSetupFall', False, False ),
            ( 'k_process_setup_rise', 'float', 'mK_ProcessSetupRise', False, False ),
            ( 'k_process_skew_fall', 'float', 'mK_ProcessSkewFall', False, False ),
            ( 'k_process_skew_rise', 'float', 'mK_ProcessSkewRise', False, False ),
            ( 'k_process_slope_fall', 'float', 'mK_ProcessSlopeFall', False, False ),
            ( 'k_process_slope_rise', 'float', 'mK_ProcessSlopeRise', False, False ),
            ( 'k_process_wire_cap', 'float', 'mK_ProcessWireCap', False, False ),
            ( 'k_process_wire_res', 'float', 'mK_ProcessWireRes', False, False ),

            ( 'k_temp_cell_fall', 'float', 'mK_TempCellFall', False, False ),
            ( 'k_temp_cell_rise', 'float', 'mK_TempCellRise', False, False ),
            ( 'k_temp_cell_leakage_power', 'float', 'mK_TempCellLeakagePower', False, False ),
            ( 'k_temp_drive_current', 'float', 'mK_TempDriveCurrent', False, False ),
            ( 'k_temp_drive_fall', 'float', 'mK_TempDriveFall', False, False ),
            ( 'k_temp_drive_rise', 'float', 'mK_TempDriveRise', False, False ),
            ( 'k_temp_fall_delay_intercept', 'float', 'mK_TempFallDelayIntercept', False, False ),
            ( 'k_temp_fall_pin_resistance', 'float', 'mK_TempFallPinResistance', False, False ),
            ( 'k_temp_fall_propagation', 'float', 'mK_TempFallPropagation', False, False ),
            ( 'k_temp_fall_transition', 'float', 'mK_TempFallPropagation', False, False ),
            ( 'k_temp_hold_fall', 'float', 'mK_TempHoldFall', False, False ),
            ( 'k_temp_hold_rise', 'float', 'mK_TempHoldRise', False, False ),
            ( 'k_temp_inernal_power', 'float', 'mK_TempInternalPower', False, False ),
            ( 'k_temp_intrinsic_fall', 'float', 'mK_TempIntrinsicFall', False, False ),
            ( 'k_temp_intrinsic_rise', 'float', 'mK_TempIntrinsicRise', False, False ),
            ( 'k_temp_min_period', 'float', 'mK_TempMinPeriod', False, False ),
            ( 'k_temp_min_pulse_width_high', 'float', 'mK_TempMinPulseWidthHigh', False, False ),
            ( 'k_temp_min_pulse_width_low', 'float', 'mK_TempMinPulseWidthLow', False, False ),
            ( 'k_temp_nochange_fall', 'float', 'mK_TempNochangeFall', False, False ),
            ( 'k_temp_nochange_rise', 'float', 'mK_TempNochangeRise', False, False ),
            ( 'k_temp_pin_cap', 'float', 'mK_TempPinCap', False, False ),
            ( 'k_temp_recovery_fall', 'float', 'mK_TempRecoveryFall', False, False ),
            ( 'k_temp_recovery_rise', 'float', 'mK_TempRecoveryRise', False, False ),
            ( 'k_temp_removal_fall', 'float', 'mK_TempRemovalFall', False, False ),
            ( 'k_temp_removal_rise', 'float', 'mK_TempRemovalRise', False, False ),
            ( 'k_temp_rise_delay_intercept', 'float', 'mK_TempRiseDelayIntercept', False, False ),
            ( 'k_temp_rise_pin_resistance', 'float', 'mK_TempRisePinResistance', False, False ),
            ( 'k_temp_rise_propagation', 'float', 'mK_TempRisePropagation', False, False ),
            ( 'k_temp_rise_transition', 'float', 'mK_TempRisePropagation', False, False ),
            ( 'k_temp_setup_fall', 'float', 'mK_TempSetupFall', False, False ),
            ( 'k_temp_setup_rise', 'float', 'mK_TempSetupRise', False, False ),
            ( 'k_temp_skew_fall', 'float', 'mK_TempSkewFall', False, False ),
            ( 'k_temp_skew_rise', 'float', 'mK_TempSkewRise', False, False ),
            ( 'k_temp_slope_fall', 'float', 'mK_TempSlopeFall', False, False ),
            ( 'k_temp_slope_rise', 'float', 'mK_TempSlopeRise', False, False ),
            ( 'k_temp_wire_cap', 'float', 'mK_TempWireCap', False, False ),
            ( 'k_temp_wire_res', 'float', 'mK_TempWireRes', False, False ),

            ( 'k_volt_cell_fall', 'float', 'mK_VoltCellFall', False, False ),
            ( 'k_volt_cell_rise', 'float', 'mK_VoltCellRise', False, False ),
            ( 'k_volt_cell_leakage_power', 'float', 'mK_VoltCellLeakagePower', False, False ),
            ( 'k_volt_drive_current', 'float', 'mK_VoltDriveCurrent', False, False ),
            ( 'k_volt_drive_fall', 'float', 'mK_VoltDriveFall', False, False ),
            ( 'k_volt_drive_rise', 'float', 'mK_VoltDriveRise', False, False ),
            ( 'k_volt_fall_delay_intercept', 'float', 'mK_VoltFallDelayIntercept', False, False ),
            ( 'k_volt_fall_pin_resistance', 'float', 'mK_VoltFallPinResistance', False, False ),
            ( 'k_volt_fall_propagation', 'float', 'mK_VoltFallPropagation', False, False ),
            ( 'k_volt_fall_transition', 'float', 'mK_VoltFallPropagation', False, False ),
            ( 'k_volt_hold_fall', 'float', 'mK_VoltHoldFall', False, False ),
            ( 'k_volt_hold_rise', 'float', 'mK_VoltHoldRise', False, False ),
            ( 'k_volt_inernal_power', 'float', 'mK_VoltInternalPower', False, False ),
            ( 'k_volt_intrinsic_fall', 'float', 'mK_VoltIntrinsicFall', False, False ),
            ( 'k_volt_intrinsic_rise', 'float', 'mK_VoltIntrinsicRise', False, False ),
            ( 'k_volt_min_period', 'float', 'mK_VoltMinPeriod', False, False ),
            ( 'k_volt_min_pulse_width_high', 'float', 'mK_VoltMinPulseWidthHigh', False, False ),
            ( 'k_volt_min_pulse_width_low', 'float', 'mK_VoltMinPulseWidthLow', False, False ),
            ( 'k_volt_nochange_fall', 'float', 'mK_VoltNochangeFall', False, False ),
            ( 'k_volt_nochange_rise', 'float', 'mK_VoltNochangeRise', False, False ),
            ( 'k_volt_pin_cap', 'float', 'mK_VoltPinCap', False, False ),
            ( 'k_volt_recovery_fall', 'float', 'mK_VoltRecoveryFall', False, False ),
            ( 'k_volt_recovery_rise', 'float', 'mK_VoltRecoveryRise', False, False ),
            ( 'k_volt_removal_fall', 'float', 'mK_VoltRemovalFall', False, False ),
            ( 'k_volt_removal_rise', 'float', 'mK_VoltRemovalRise', False, False ),
            ( 'k_volt_rise_delay_intercept', 'float', 'mK_VoltRiseDelayIntercept', False, False ),
            ( 'k_volt_rise_pin_resistance', 'float', 'mK_VoltRisePinResistance', False, False ),
            ( 'k_volt_rise_propagation', 'float', 'mK_VoltRisePropagation', False, False ),
            ( 'k_volt_rise_transition', 'float', 'mK_VoltRisePropagation', False, False ),
            ( 'k_volt_setup_fall', 'float', 'mK_VoltSetupFall', False, False ),
            ( 'k_volt_setup_rise', 'float', 'mK_VoltSetupRise', False, False ),
            ( 'k_volt_skew_fall', 'float', 'mK_VoltSkewFall', False, False ),
            ( 'k_volt_skew_rise', 'float', 'mK_VoltSkewRise', False, False ),
            ( 'k_volt_slope_fall', 'float', 'mK_VoltSlopeFall', False, False ),
            ( 'k_volt_slope_rise', 'float', 'mK_VoltSlopeRise', False, False ),
            ( 'k_volt_wire_cap', 'float', 'mK_VoltWireCap', False, False ),
            ( 'k_volt_wire_res', 'float', 'mK_VoltWireRes', False, False ),

            # complex attributes
            ( 'capacitve_load_unit', 'unit', 'mCapacitiveLoadUnit', False, False ),
            ( 'default_part', 'default_part', 'mDefaultPart', False, False ),
            ( 'define', 'define', 'mDefine', False, True ),
            ( 'define_cell_area', 'define_cell_area', 'mDefineCellArea',  False, True ),
            ( 'defin_group', 'define_group', 'mDefineGroup', False, True ),
            ( 'library_features', 'library_features', 'mLibraryFeatures', False, False ),
            ( 'piece_define', 'piece_define', 'mPieceDefine', False, False ),
            ( 'routing_layers', 'routing_layers', 'mRoutingLayers', False, False ),
            ( 'technology', 'technology', 'mTechnology', False, False ),
            ( 'voltage_map', 'voltage_map', 'mVoltageMap', False, True ),

            # group statements
            ( 'base_curves', 'base_curves', 'mBaseCurves', False, True ),
            ( 'compact_lut_template', 'clut_template', 'mCompactLutTemplate', False, True ),
            ( 'dc_current_template', 'template', 'mDcCurrentTemplate', False, True ),
            ( 'em_lut_template', 'template', 'mEmLutTemplate', False, True ),
            ( 'fall_net_delay', 'table', 'mFallNetDelay', False, True ),
            ( 'rise_net_delay', 'table', 'mRiseNetDelay', False, True ),l
            ( 'fall_transition_degradation', 'table', 'mFallTransitionDegradation', False, True ),
            ( 'rise_transition_degradation', 'table', 'mRiseTransitionDegradation', False, True ),
            ( 'fault_lut_template', 'flut_template', 'mFaultLutTemplate', False, True ),
            ( 'input_voltage', 'input_voltage', 'mInputVoltage', False, True ),
            ( 'fpga_isd', 'fpga_isd', 'mFpgaIsd', False, True ),
            ( 'iv_lut_template', 'template', 'mIvLutTempate', False, True ),
            ( 'lu_table_template', 'template', 'mLuTableTemplate', False, True ),
            ( 'maxcap_lut_template', 'template', 'mMaxcapLutTemplate', False, True ),
            ( 'maxtrans_lut_template', 'template', 'mMaxtransLutTemplate', False, True ),
            ( 'noise_lut_template', 'template', 'mNoiseLutTemplate', False, True ),
            ( 'operating_conditions', 'operating_conditions', 'mOperatingConditions', False, True ),
            ( 'output_current_template', 'template', 'mOutputCurrentTemplate', False, True ),
            ( 'output_voltage', 'output_voltage', 'mOutputVoltage', False, True ),
            ( 'part', 'part', 'mPart', False, True ),
            ( 'pg_current_template', 'template', 'mPgCurrentTemplate', False, True ),
            ( 'poly_template', 'poly_template', 'mPolyTemplate', False, True ),
            ( 'power_lut_template', 'template', 'mPowerLutTemplate', False, True ),
            ( 'power_poly_template', 'poly_template', 'mPowerPolyTemplate', False, True ),
            ( 'power_supply', 'power_supply', 'mPowerSupply', False, True ),
            ( 'propagation_lut_template', 'template', False, True ),
            ( 'scaled_cell', 'scaled_cell', 'mScaledCell', False, True ),
            ( 'scaling_factors', 'scaling_factors', 'mScalingFactors', False, True ),
            ( 'sensitization', 'sensitization', 'mSensitization', False, True ),
            ( 'timing', 'timing', 'mTiming', False, True ),
            ( 'timing_range', 'timing_range', 'mTimingRange', False, True ),
            ( 'type', 'type', 'mType', False, True ),
            ( 'user_parameters', 'user_parameters', 'mUserParameters', False, False ),
            ( 'wire_load', 'wire_load', 'mWireLoad', False, True ),
            ( 'wire_load_selection', 'wire_load_selection', 'mWireLoadSelection', False, True ),
            ( 'wire_loat_table', 'wire_load_table', 'mWireLoadTable', False, True ),
            ]
