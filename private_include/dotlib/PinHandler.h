#ifndef PINHANDLER_H
#define PINHANDLER_H

/// @file PinHandler.h
/// @brief PinHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"
#include "dotlib/StrListHeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class PinHandler PinHandler.h "PinHandler.h"
/// @brief 'pin' Group Statement 用のハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 3
///           "pin Group Description and Syntax"
///
/// * 注意事項：マニュアル中で論理式を表す文字列を
///   function string, "Boolean expression", <function string>
///   と表記が揺れている．さらに true | false を Boolean expression と
///   書いてあるところもある．
///
/// * Simple Attributes
///   - bit_wdith : integer ;
///   - capacitance : float ;
///   - clock : true | false ;
///   - clock_gate_clock_pin : true | false ;
///   - clock_gate_enable_pin : true | false ;
///   - clock_gate_test_pin : true | false ;
///   - clock_gate_obs_pin : true | false ;
///   - clock_gate_out_pin : true | false ;
///   - complementary_pin : "value_(string)" ;
///   - connection_class : "name1 [name2 name3 ... ]" ;
///   - direction : input | output | inout | internal ;
///   - dont_fault : sa0 | sa1 | sa01 ;
///   - drive_current : float ;
///   - driver_type : pull_up | pull_down | opendrain | open_source |
///                   bus_hold | resistive | resistive_0 | resistive_1 ;
///   - fall_capacitance : float ;
///   - fall_current_slope_after_threshold : float ;
///   - fall_current_slope_before_threshold : float ;
///   - fall_time_after_threshold : float ;
///   - fall_time_before_threshold : float ;
///   - fanout_load : float ;
///   - fault_model "two-value string" ; [01x][01x]
///   - function : "Boolean expression" ;
///   - has_builtin_pad : true | false ;
///   - hysteresis : true | false ;
///   - input_map : name_(id) ; 空白で区切られた入力ピン名のリスト
///   - input_signal_level : name_(id) ;
///   - input_threshold_pct_fall : float ;
///   - input_threshold_pct_rise : float ;
///   - input_voltage : name_(id) ;
///   - internal_node : pin_name_(id) ;
///   - inverted_output : true | false ;
///   - is_pad : true | false ;
///   - isolation_cell_enable_pin : true | false ;
///   - level_shifter_enable_pin : true | false ;
///   - map_to_logic : 1 | 0 ; // なんでこれが Boolean expression なの？
///   - max_capacitance : float ;
///   - max_fanout : float ;
///   - max_input_noise_width : float ;
///   - max_transition : float ;
///   - min_capacitance : float ;
///   - min_fanout : float ;
///   - min_input_noise_width : float ;
///   - min_period : float ;
///   - min_pulse_width_high : float ;
///   - min_pulse_width_low : float ;
///   - min_transition : float ;
///   - multicell_pad_pin : true | false ;
///   - nextstate_type : data | preset | clear | load | scan_in | scan_enable ;
///   - output_signal_level : name_(id) ;
///   - output_voltage : name_(id) ;
///   - pg_function : "<function_string>" ; ??
///   - pin_func_type : clock_enable | active_high | active_low |
///                     active_rising | active_falling ;
///   - power_down_function : "<function string>" ;
///   - prefer_tied : "0" | "1" ;
///   - primary_output : true | false ;
///   - pulling_current : float ; // マニュアルには正確な記述なし．
///   - pulling_resistance : float ;
///   - pulse_clock : rise_triggered_high_pulse |
///                   rise_triggered_low_pulse |
///                   fall_triggered_high_pulse |
///                   fall_triggered_low_pulse ;
///   - related_ground_pin : pg_pin_name_(id) ;
///   - related_power_pin : pg_pin_name_(id) ;
///   - rise_capacitance : float ;
///   - rise_currrent_slope_after_threshold : float ;
///   - rise_current_slope_before_threshold : falot ;
///   - rise_time_after_threshold : float ;
///   - rise_time_before_threshold : float ;
///   - signal_type : test_scan_in | test_scan_in_inverted |
///                   test_scan_out | test_scan_out_inverted |
///                   test_scan_enable | test_scan_enable_inverted |
///                   test_scan_clock | test_scan_clock_a |
///                   test_scan_clock_b | test_clock ;
///   - slew_control : low | medium | high | none ;
///   - slew_lower_threshold_pct_fall : float ;
///   - slew_lower_threshold_pct_rise : float ;
///   - slew_upper_threshold_pct_fall : float ;
///   - slew_upper_threshold_pct_rise : falot ;
///   - state_function : "Boolean expression" ;
///   - std_cell_main_rail : true | false ;
///   - switch_function : function_string ; // "Boolean expression" のこと？
///   - switch_pin : true | false ;
///   - test_output_only : true | false ;
///   - three_state : "Boolean expression" ;
///   - vhdl_name : "name_(string)" ;
///   - x_function : "Boolean expression" ;
///
/// * Complex Attributes
///   - fall_capacitance_range : (value_1_(float), value_2_(float)) ;
///   - power_gating_pin : (value_1_(enum), value2_(Boolean)) ;
///                         たぶん value_1 は string, value2 は integer
///   - rise_capacitance_range : (value_1_(float), value_2(float)) ;
///
/// * Group Statements
///   - ccsn_first_stage () { ... }
///   - ccsn_last_stage () { ... }
///   - dc_current () { ... }
///   - electromigration () { ... }
///   - hyperbolic_noise_above_high () { ... }
///   - hyperbolic_noise_below_low () { ... }
///   - hyperbolic_noise_high () { ... }
///   - hyperbolic_noise_low () { ... }
///   - input_signal_swing () { ... }
///   - max_capacitance () { ... }
///   - max_transition () { ... }
///   - min_pulse_width () { ... }
///   - minimum_period () { ... }
///   - output_signal_swing () { ... }
///   - pin_capacitance () { ... }
///   - timing () { ... }
///   - tlatch () { ... }
//////////////////////////////////////////////////////////////////////
class PinHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  PinHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~PinHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif 'pin' Group Statement の記述をパースする．
  /// @param[in] dst_list 読み込んだ値を格納する変数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(vector<const AstPin*>& dst_list);


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ヘッダ用のハンドラ
  StrListHeaderHandler mHeaderHandler;

  // bit_width
  const AstInt* mBitWidth;

  // capacitance
  const AstFloat* mCapacitance;

  // clock
  const AstBool* mClock;

  // clock_gate_clock_pin
  const AstBool* mClockGateClockPin;

  // clock_gate_enable_pin
  const AstBool* mClockGateEnablePin;

  // clock_gate_test_pin
  const AstBool* mClockGateTestPin;

  // clock_gate_obs_pin
  const AstBool* mClockGateObsPin;

  // clock_gate_out_pin
  const AstBool* mClockGateOutPin;

  // complementary_pin
  const AstString* mComplementaryPin;

  // connection_class
  const AstString* mConnectionClass;

  // direction
  const AstPinDirection* mDirection;

  // dont_faut
  const AstString* mDontFault;

  // drive_current
  const AstFloat* mDriveCurrent;

  // driver_type
  const AstString* mDriverType;

  // fall_capacitance
  const AstFloat* mFallCapacitance;

  // fall_current_slope_after_threshold
  const AstFloat* mFallCurrentSlopeAfterThreshold;

  // fall_current_slope_before_threshold
  const AstFloat* mFallCurrentSlopeBeforeThreshold;

  // fall_time_after_threshold
  const AstFloat* mFallTimeAfterThreshold;

  // fall_time_before_threshold
  const AstFloat* mFallTimeBeforeThreshold;

  // fanout_load
  const AstFloat* mFanoutLoad;

  // fault_model
  const AstString* mFaultModel;

  // function
  const AstExpr* mFunction;

  // has_builtin_pad
  const AstBool* mHasBuiltinPad;

  // hysteresis
  const AstBool* mHysteresis;

  // input_map
  const AstString* mInputMap;

  // input_signal_level
  const AstString* mInputSignalLevel;

  // input_threshold_pct_fall
  const AstFloat* mInputThresholdPctFall;

  // input_threshold_pct_rise
  const AstFloat* mInputThresholdPctRise;

  // input_voltage
  const AstString* mInputVoltage;

  // internal_node
  const AstString* mInternalNode;

  // inverted_output
  const AstBool* mInvertedOutput;

  // is_pad
  const AstBool* mIsPad;

  // isolation_cell_enable_pin
  const AstBool* mIsolationCellEnablePin;

  // level_shifter_enable_pin
  const AstBool* mLevelShifterEnablePin;

  // map_to_logic
  const AstBool* mMapToLogic;

  // max_capacitance
  const AstFloat* mMaxCapacitance;

  // max_fanout
  const AstFloat* mMaxFanout;

  // max_input_noise_width
  const AstFloat* mMaxInputNoiseWidth;

  // max_transition
  const AstFloat* mMaxTransition;

  // min_capacitance
  const AstFloat* mMinCapacitance;

  // min_fanout
  const AstFloat* mMinFanout;

  // min_input_noise_width
  const AstFloat* mMinInputNoiseWidth;

  // min_period
  const AstFloat* mMinPeriod;

  // min_pulse_width_high
  const AstFloat* mMinPulseWidthHigh;

  // min_pulse_width_low
  const AstFloat* mMinPulseWidthLow;

  // min_transition
  const AstFloat* mMinTransition;

  // multicell_pad_pin
  const AstBool* mMulticellPadPin;

  // nextstate_type
  const AstString* mNextstateType;

  // output_signal_level
  const AstString* mOutputSignalLevel;

  // output_voltage
  const AstString* mOutputVoltage;

  // pg_function
  const AstExpr* mPgFunction;

  // pin_func_type
  const AstString* mPinFuncType;

  // power_down_function
  const AstExpr* mPowerDownFunction;

  // prefer_tied
  const AstString* mPreferTied;

  // primary_output
  const AstBool* mPrimaryOutput;

  // pulling_current
  const AstFloat* mPullingCurrent;

  // pulling_resistance
  const AstFloat* mPullingResistance;

  // pulse_clock
  const AstString* mPulseClock;

  // related_ground_pin
  const AstString* mRelatedGroundPin;

  // related_power_pin
  const AstString* mRelatedPowerPin;

  // rise_capacitance
  const AstFloat* mRiseCapacitance;

  // rise_current_slope_after_threshold
  const AstFloat* mRiseCurrentSlopeAfterThreshold;

  // rise_current_slope_before_threshold
  const AstFloat* mRiseCurrentSlopeBeforeThreshold;

  // rise_time_after_threshold
  const AstFloat* mRiseTimeAfterThreshold;

  // rise_time_before_threshold
  const AstFloat* mRiseTimeBeforeThreshold;

  // signal_type
  const AstString* mSignalType;

  // slew_control
  const AstString* mSlewControl;

  // slew_lower_threshold_pct_fall
  const AstFloat* mSlewLowerThresholdPctFall;

  // slew_lower_threshold_pct_rise
  const AstFloat* mSlewLowerThresholdPctRise;

  // slew_upper_threshold_pct_fall
  const AstFloat* mSlewUpperThresholdPctFall;

  // slew_upper_threshold_pct_rise
  const AstFloat* mSlewUpperThresholdPctRise;

  // state_function
  const AstExpr* mStateFunction;

  // std_cell_main_rail
  const AstBool* mStdCellMainRail;

  // switch_function
  const AstExpr* mSwitchFunction;

  // switch_pin
  const AstBool* mSwitchPin;

  // test_output_only
  const AstBool* mTestOutputOnly;

  // three_state
  const AstExpr* mThreeState;

  // vdhl_name
  const AstString* mVhdlName;

  // x_function
  const AstExpr* mXFunction;

  // fall_capacitance_range
  const AstFloat* mFallCapacitanceRange[2];

  // power_gating_pin
  const AstString* mPowerGatingPinString;
  const AstInt* mPowerGatingPinInt;

  // rise_capacitance_range
  const AstFloat* mRiseCapacitanceRange[2];

  // electromigration
  // ???

  // hyperbolic_noise_above_high
  // ???

  // hyperbolic_nose_below_low
  // ???

  // hyperbolic_noise_high
  // ???

  // hyperbolic_noise_low
  // ???

  // input_signal_swing
  // ???

  // internal_power
  // ???

  // max_transition
  // ???

  // min_pulse_width
  // ???

  // minimum_period
  // ???

  // output_signal_swing
  // ???

  // pin_capacitance
  // ???

  // timing
  vector<const AstTiming*> mTimingList;

  // tlatch
  // ???

  // 読み込んだ値
  const AstPin* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // PINHANDLER_H
