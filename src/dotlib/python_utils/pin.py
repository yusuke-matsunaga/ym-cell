#! /usr/bin/env python3

### @file pin.py
### @brief PinHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

import sys
import argparse
import os.path

from gen_handler_code import gen_ast_header, gen_ast_source
from gen_handler_code import gen_handler_header, gen_handler_source
from gen_handler_code import type_to_class

class PinClassDef :

    def __init__(self) :
        self.data_type = 'pin'
        self.desc = 'ピン'
        self.parent_class = 'GroupHandler'
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

    ### @brief コンストラクタの引数の記述を生成する．
    def gen_constructor_arguments(self, fout, cspc) :
        fout.write('{}const vector<const AstString*>& name_list,\n'.format(cspc))

    ### @brief コンストラクタの引数の記述を生成する．
    def gen_constructor_arguments2(self, fout, cspc) :
        fout.write('{}name_list,\n'.format(cspc))

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

    ### @brief ハンドラの関数宣言を生成する．
    def gen_handler_func_decl(self, fout) :
        fout.write('public:\n')
        fout.write('  //////////////////////////////////////////////////////////////////////\n')
        fout.write('  // CGHandler の仮想関数\n')
        fout.write('  //////////////////////////////////////////////////////////////////////\n')
        fout.write('\n')
        fout.write('  /// @brief ヘッダの開始処理\n')
        fout.write('  ///\n')
        fout.write('  /// \'(\' を読み込んだ時に呼ばれる．\n')
        fout.write('   void\n')
        fout.write('  begin_header() override;\n')
        fout.write('\n')
        fout.write('  /// @brief ヘッダの値を読み込む処理\n')
        fout.write('  /// @param[in] value_type 型\n')
        fout.write('  /// @param[in] value_loc トークンの位置\n')
        fout.write('  /// @param[in] count read_value() の呼ばれた回数\n')
        fout.write('  /// @retval true 正しく読み込んだ．\n')
        fout.write('  /// @retval false エラーが起きた．\n')
        fout.write('  bool\n')
        fout.write('  read_header_value(TokenType value_type,\n')
        fout.write('		    const FileRegion& value_loc,\n')
        fout.write('		    int count) override;\n')
        fout.write('\n')
        fout.write('  /// @brief 読み込みが終了した時の処理を行う．\n')
        fout.write('  /// @param[in] header_loc \'(\' から \')\' までのファイル上の位置\n')
        fout.write('  /// @param[in] count 読み込んだ要素数\n')
        fout.write('  /// @retval true 正しく読み込んだ．\n')
        fout.write('  /// @retval false エラーが起きた．\n')
        fout.write('  bool\n')
        fout.write('  end_header(const FileRegion& header_loc,\n')
        fout.write('	     int count) override;\n')
        fout.write('\n')
        fout.write('\n')

    ### @brief ハンドラのメンバ変数定義を生成する．
    def gen_handler_member(self, fout) :
        fout.write('  vector<const AstString*> mNameList;\n')

    ### @brief ハンドラの関数定義を生成する．
    def gen_handler_func_impl(self, fout) :
        str = """
// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
PinHandler::begin_header()
{
  mNameList.clear();
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
PinHandler::read_header_value(TokenType value_type,
			      const FileRegion& value_loc,
			      int count)
{
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, a string is expected.");
    return false;
  }
  else {
    mNameList.push_back(mgr().new_string(value_loc, ShString(cur_string())));
    return true;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
PinHandler::end_header(const FileRegion& header_loc,
		       int count)
{
  if ( mNameList.empty() ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, one or more strings area expected.");
    return false;
  }
  else {
    return true;
  }
}

"""
        fout.write(str)

    ### @brief ハンドラの end_group() 中のヘッダ引数を生成する．
    def gen_handler_end_group_code(self, fout) :
        pass

    ### @brief ハンドラの end_group() 中のヘッダ引数を生成する．
    def gen_handler_arguments(self, cspc, fout) :
        fout.write('{}mNameList,\n'.format(cspc))


if __name__ == '__main__' :

    parser = argparse.ArgumentParser()

    mode_group = parser.add_mutually_exclusive_group()
    mode_group.add_argument('--ast_header',
                            action = 'store_true',
                            help = 'generate AstPin.h')
    mode_group.add_argument('--ast_source',
                            action = 'store_true',
                            help = 'generate AstPin.cc')
    mode_group.add_argument('--handler_header',
                            action = 'store_true',
                            help = 'generate PinHandler.h')
    mode_group.add_argument('--handler_source',
                            action = 'store_true',
                            help = 'generate PinHandler.cc')

    args = parser.parse_args()
    if not args :
        exit(1)

    fout = sys.stdout
    class_def = PinClassDef()

    if args.ast_header :
        gen_ast_header(fout, class_def)
    elif args.ast_source :
        gen_ast_source(fout, class_def)
    elif args.handler_header :
        gen_handler_header(fout, class_def)
    elif args.handler_source :
        gen_handler_source(fout, class_def)
