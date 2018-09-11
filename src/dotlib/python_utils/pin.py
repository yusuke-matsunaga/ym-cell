#! /usr/bin/env python3

### @file gen_reg_func.py
### @brief GroupHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

import sys
import argparse
import os.path

from gen_handler_code import gen_reg_func, gen_clear, gen_member
from gen_handler_code import gen_ast_header, gen_ast_source
from gen_handler_code import type_to_class

class PinClass :

    def __init__(self) :
        self.data_type = 'pin'
        self.desc = 'ピン'
        self.attr_list = [
            # ( 属性名, 属性の型, メンバ変数名 ) のリスト
            ( 'bit_width', 'int', 'mBitWidth' ),
            ( 'capacitance', 'float', 'mCapacitance' ),
            ( 'clock_gate_clock_pin', 'bool', 'mClockGateClockPin' ),
            ( 'clock_gate_enable_pin', 'bool', 'mClockGateEnablePin' ),
            ( 'clock_gate_test_pin', 'bool', 'mClockGateTestPin' ),
            ( 'clock_gate_obs_pin', 'bool', 'mClockGateObsPin' ),
            ( 'clock_gate_out_pin', 'bool', 'mClockGateOutPin' ),
            ( 'complementary_pin', 'string', 'mComplementaryPin' ),
            ( 'connection_class', 'string', 'mConnectionClass' ),
            ( 'direction', 'direction', 'mDirection' ),
            ( 'dont_fault', 'string', 'mDontFault' ),
            ( 'drive_current', 'float', 'mDriveCurrent' ),
            ( 'driver_type', 'string', 'mDriverType' ),
            ( 'fall_capacitance', 'float', 'mFallCapacitance' ),
            ( 'fall_current_slope_after_threshold', 'float', 'mFallCurrentSlopeAfterThreshold' ),
            ( 'fall_current_slope_before_threshold', 'float', 'mFallCurrentSlopeBeforeThreshold' ),
            ( 'fall_time_after_threshold', 'float', 'mFallTimeAfterThreshold' ),
            ( 'fall_time_before_threshold', 'float', 'mFallTimeBeforeThreshold' ),
            ( 'fanout_load', 'float', 'mFanoutLoad' ),
            ( 'fault_model', 'string', 'mFaultModel' ),
            ( 'function', 'expr', 'mFunction' ),
            ( 'has_builtin_pad', 'bool', 'mHasBuiltinPad' ),
            ( 'hysteresis', 'bool', 'mHysteresis' ),
            ( 'input_map', 'string', 'mInputMap' ),
            ( 'input_signal_level', 'string', 'mInputSignalLevel' ),
            ( 'input_threshold_pct_fall', 'float', 'mInputThresholdPctFall' ),
            ( 'input_threshold_pct_rise', 'float', 'mInputThresholdPctRise' ),
            ( 'input_voltage', 'string', 'mInputVoltage' ),
            ( 'internal_node', 'string', 'mInternalNode' ),
            ( 'inverted_output', 'bool', 'mInvertedOutput' ),
            ( 'isolation_cell_enable_pin', 'bool', 'mIsolationCellEnablePin' ),
            ( 'level_shifter_enable_pin', 'bool', 'mLevelShifterEnablePin' ),
            ( 'map_to_logic', 'bool', 'mMapToLogic' ),
            ( 'max_capacitance', 'float', 'mMaxCapacitance' ),
            ( 'max_fanout', 'float', 'mMaxFanout' ),
            ( 'max_input_noise_width', 'float', 'mMaxInputNoiseWidth' ),
            ( 'max_transition', 'float', 'mMaxTransition' ),
            ( 'min_capacitance', 'float', 'mMinCapacitance' ),
            ( 'min_fanout', 'float', 'mMinFanout' ),
            ( 'min_input_noise_width', 'float', 'mMinInputNoiseWidth' ),
            ( 'min_pulse_width_high', 'float', 'mMinPulseWidthHigh' ),
            ( 'min_pulse_width_low', 'float', 'mMinPulseWidthLow' ),
            ( 'min_transition', 'float', 'mMinTransition' ),
            ( 'min_period', 'float', 'mMinPeriod' ),
            ( 'multicell_pad_pin', 'bool', 'mMulticellPadPin' ),
            ( 'nextstate_type', 'string', 'mNextstateType' ),
            ( 'output_signal_level', 'string', 'mOutputSignalLevel' ),
            ( 'output_voltage', 'string', 'mOutputVoltage' ),
            ( 'pg_function', 'function', 'mPgFunction' ),
            ( 'pin_func_type', 'string', 'mPinFuncType' ),
            ( 'power_down_function', 'function', 'mPowerDownFunction' ),
            ( 'prefer_tied', 'string', 'mPreferTied' ),
            ( 'primary_output', 'bool', 'mPrimaryOutput' ),
            ( 'pulling_current', 'float', 'mPullingCurrent' ),
            ( 'pulling_resistance', 'float', 'mPullingResistance' ),
            ( 'pulse_clock', 'string', 'mPulseClock' ),
            ( 'related_ground_pin', 'string', 'mRelatedGroundPin' ),
            ( 'related_power_pin', 'string', 'mRelatedPowerPin' ),
            ( 'rise_capacitance', 'float', 'mRiseCapacitance' ),
            ( 'rise_current_slope_after_threshold', 'float', 'mRiseCurrentSlopeAfterThreshold' ),
            ( 'rise_current_slope_before_threshold', 'float', 'mRiseCurrentSlopeBeforeThreshold' ),
            ( 'rise_time_after_threshold', 'float', 'mRiseTimeAfterThreshold' ),
            ( 'rise_time_before_threshold', 'float', 'mRiseTimeBeforeThreshold' ),
            ( 'signal_type', 'string', 'mSignalType' ),
            ( 'slew_control', 'string', 'mSlewControl' ),
            ( 'slew_lower_threshold_pct_fall', 'float', 'mSlewLowerThresholdPctFall' ),
            ( 'slew_lower_threshold_pct_rise', 'float', 'mSlewLowerThresholdPctRise' ),
            ( 'slew_upper_threshold_pct_fall', 'float', 'mSlewUpperThresholdPctFall' ),
            ( 'slew_upper_threshold_pct_rise', 'float', 'mSlewUpperThresholdPctRise' ),
            ( 'state_function', 'expr', 'mStateFunction' ),
            ( 'std_cell_main_rail', 'bool', 'mStdCellMainRail' ),
            ( 'switch_function', 'function', 'mSwitchFunction' ),
            ( 'switch_pin', 'bool', 'mSwitchPin' ),
            ( 'test_output_only', 'bool', 'mTestOutputOnly' ),
            ( 'three_state', 'expr', 'mThreeState' ),
            ( 'vhdl_name', 'string', 'mVhdlName' ),
            ( 'x_function', 'expr', 'mXFunction' ),
            ( 'fall_capacitance_range', 'float2complex', 'mFallCapacitanceRange' ),
            ( 'rise_capacitance_range', 'float2complex', 'mRiseCapacitanceRange' ),
            ( 'power_gating_pin', 'pg_pin', 'mPowerGatingPin' ),
            ( 'dc_current', 'dc_current', 'mDcCurrent' ),
            ( 'electromigration', 'electromigration', 'mElectromigration' ),
            ( 'hyperbolic_noise_above_high', '???', 'mHyperbolicNoiseAboveHigh' ),
            ( 'hyperbolic_noise_below_low', '???', 'mHyperbolicNoiseBeforeLow' ),
            ( 'hyperbolic_noise_high', '???', 'mHyperbolicNoiseHigh' ),
            ( 'hyperbolic_noise_low', '???', 'mHyperbolicNoiseLow' ),
            ( 'input_signal_swing', '???', 'mInputSignalSwing' ),
            ( 'max_capacitance', '???', 'mMaxCapacitance' ),
            ( 'max_transition', '???', 'mMaxTransition' ),
            ( 'min_pulse_width', '???', 'mMinPulseWidth' ),
            ( 'minimum_period', '???', 'mMinimumPeriod' ),
            ( 'output_signal_swing', '???', 'mOutputSignalSwing' ),
            ( 'pin_capacitance', '???', 'mPinCapacitance' ),
            ( 'timing', 'timing', 'mTiming' ),
            ( 'tlatch', 'tlatch', 'mTlatch' )
            ]

    ### @brief コンストラクタの引数の記述を生成する．
    def gen_constructor_arguments(self, fout, cspc) :
        fout.write('{}const vector<const AstString*>& name_list,\n'.format(cspc))

    ### @brief アクセッサー関数の宣言を生成する．
    def gen_accessor_decl(self, fout) :
        fout.write('\n')
        fout.write('  /// @brief 名前のリストの要素数を返す．\n')
        fout.write('  int\n')
        fout.write('  name_num() const;\n')
        fout.write('\n')
        fout.write('  /// @brief 名前のリストの要素を返す．\n')
        fout.write('  /// @param[in] pos 位置番号 ( 0 <= pos < name_num() )\n')
        fout.write('  const AstString*\n')
        fout.write('  name(int pos) const;\n')

    ### @brief メンバの初期化文を生成する．
    def gen_member_init(self, fout) :
        fout.write('  mNameNum(name_list.size()),\n')
        fout.write('  mNameList(alloc.get_array<const AstString*>(mNameNum)),\n')

    ### @brief メンバの初期化文を生成する．
    def gen_member_init2(self, fout) :
        fout.write('  for ( auto i: Range(mNameNum) ) {\n')
        fout.write('    mNameList[i] = name_list[i];\n')
        fout.write('  }\n')

    ### @brief メンバ定義を生成する．
    def gen_member_def(self, fout) :
        fout.write('\n')
        fout.write('  // ピン名のリストの要素数\n')
        fout.write('  int mNameNum;\n')
        fout.write('\n')
        fout.write('  // ピン名のリスト\n')
        fout.write('  const AstString** mNameList;\n')

    ### @brief アクセッサー関数のインライン定義を生成する．
    def gen_accessor_impl(self, fout) :
        class_name = type_to_class(self.data_type)
        fout.write('\n')
        fout.write('// @brief 名前のリストの要素数を返す．\n')
        fout.write('inline\n')
        fout.write('int\n')
        fout.write('{}::name_num() const\n'.format(class_name))
        fout.write('{\n')
        fout.write('  return mNameNum;\n')
        fout.write('}\n')
        fout.write('\n')
        fout.write('// @brief 名前のリストの要素を返す．\n')
        fout.write('// @param[in] pos 位置番号 ( 0 <= pos < name_num() )\n')
        fout.write('inline\n')
        fout.write('const AstString*\n')
        fout.write('{}::name(int pos) const\n'.format(class_name))
        fout.write('{\n')
        fout.write('  ASSERT_COND( pos >= 0 && pos < name_num() );\n')
        fout.write('\n')
        fout.write('  return mNameList[pos];\n')
        fout.write('}\n')


if __name__ == '__main__' :

    parser = argparse.ArgumentParser()

    mode_group = parser.add_mutually_exclusive_group()
    mode_group.add_argument('--init',
                            action = 'store_true',
                            help = 'generate initialization code')
    mode_group.add_argument('--clear',
                            action = 'store_true',
                            help = 'generate clear code')
    mode_group.add_argument('--ast_header',
                            action = 'store_true',
                            help = 'generate clear code')
    mode_group.add_argument('--ast_source',
                            action = 'store_true',
                            help = 'generate clear code')

    args = parser.parse_args()
    if not args :
        exit(1)

    fout = sys.stdout
    parent_class = 'AstPin'

    if args.init :
        for attr in attr_list :
            gen_reg_func(fout, attr)
    elif args.clear :
        for attr in attr_list :
            gen_clear(fout, attr)
    elif args.ast_header :
        gen_ast_header(fout, PinClass())
    elif args.ast_source :
        gen_ast_source(fout, PinClass())
