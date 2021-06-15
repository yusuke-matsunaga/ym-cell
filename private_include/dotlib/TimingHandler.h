#ifndef timingHANDLER_H
#define timingHANDLER_H

/// @file TimingHandler.h
/// @brief TimingHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TimingHandler TimingHandler.h "TimingHandler.h"
/// @brief 'timing' Group Statement を読み込むためのハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 3
///           "pin Group Description and Syntax"
///
/// * timing '(' name_(string) ')' '{'
///   ...
///   '}'
///   name_(string) はオプショナル
//
/// * Simple Attributes
///   - clock_gating_flag : true | false ;
///   - default_timing : true | false ;
///   - fall_resistance : float ;
///   - fpga_arc_condition : "Boolean expression" ;
///   - fpga_domain_style : string ;
///   - interdependence_id : integer ;
///   - intrinsic_fall : float ;
///   - intrinsic_rise : float ;
///   - related_bus_equivalent : "name1 [name2 name3 ...]" ;
///   - related_bus_pins : "name1 [name2 name3 ...]" ;
///   - related_output_pin : string ;
///   - related_pin : "name1 [name2 name3 ..]" ;
///   - rise_resistance : float ;
///   - sdf_conf : "SDF expression" ;
///   - sdf_cond_end : "SDF expression" ;
///   - sdf_cond_start : "SDF expression" ;
///   - sdf_edges : SDF edge type ;
///   - slope_fall : float ;
///   - slope_rise : float ;
///   - steady_state_resistance_above_high : float ;
///   - steady_state_resistance_below_low : float ;
///   - steady_state_resistance_high : float ;
///   - steady_state_resistance_low : float ;
///   - tied_off : true | false ;
///   - timing_sense : positive_unate | negative_unate | non_unate ;
///   - timing_type : <timing type> ;
///   - wave_fall_sampling_index : integer ;
///   - wave_rise_sampling_index : integer ;
///   - when : "Boolean expression" ;
///   - when_end : "Boolean expression" ;
///   - when_start : "Boolean expression" ;
///
/// * Complex Attributes
///   - fall_delay_intercept ( integer, float ) ;
///   - fall_pin_resistance ( integer, float ) ;
///   - mode ( string, string ) ;
///   - rise_delay_intercept ( integer, float ) ;
///   - rise_pin_resistance ( integer, float ) ;
///
/// * Group Statements
///   - cell_degradation () { ... }
///   - cell_fall () { ... }
///   - cell_rise () { ... }
///   - fall_constraint () { ... }
///   - fall_propagation () { ... }
///   - fall_transition () { ... }
///   - noise_immunity_above_high () { ... }
///   - noise_immunity_below_low () { ... }
///   - noise_immunity_high () { ... }
///   - noise_immunity_low () { ... }
///   - output_current_fall () { ... }
///   - output_current_rise () { ... }
///   - propagated_noise_height_above_high () { ... }
///   - propagated_noise_height_below_low() { ... }
///   - propagated_noise_height_high() { ... }
///   - propagated_noise_height_low() { ... }
///   - propagated_noise_peak_time_ratio_above_high() { ... }
///   - propagated_noise_peak_time_ratio_below_low() { ... }
///   - propagated_noise_peak_time_ratio_high() { ... }
///   - propagated_noise_peak_time_ratio_low() { ... }
///   - propagated_noise_width_above_high() { ... }
///   - propagated_noise_width_below_low() { ... }
///   - propagated_noise_width_high() { ... }
///   - propagated_noise_width_low() { ... }
///   - receiver_capacitance1_fall() { ... }
///   - receiver_capacitance1_rise() { ... }
///   - receiver_capacitance2_fall() { ... }
///   - receiver_capacitance2_rise() { ... }
///   - retaining_fall () { ... }
///   - retaining_rise () { ... }
///   - retain_fall_slew () { ... }
///   - retain_rise_slew () { ... }
///   - rise_constraint () { ... }
///   - rise_propagation () { ... }
///   - rise_transition () { ... }
///   - steady_state_current_high () { ... }
///   - steady_state_current_low () { ... }
///   - steady_state_current_tristate () { ... }
//////////////////////////////////////////////////////////////////////
class TimingHandler :
  public GroupHandler
{
  friend class AstTiming;

public:

  /// @brief コンストラクタ
  TimingHandler(DotlibParser& parser); ///< [in] パーサー

  /// @brief デストラクタ
  ~TimingHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief グループ記述の終わり
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group() override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // clock_gating_flag
  const AstBool* mClockGatingFlag;

  // default_timing
  const AstBool* mDefaultTiming;

  // fall_resistance
  const AstFloat* mFallResistance;

  // fpga_arc_condition
  const AstExpr* mFpgaArcCondition;

  // fpga_domain_style
  const AstString* mFpgaDomainStyle;

  // interdependence_id
  const AstInt* mInterdependenceId;

  // intrinsic_fall
  const AstFloat* mIntrinsicFall;

  // intrinsic_rise
  const AstFloat* mIntrinsicRise;

  // related_bus_equivalent
  const AstString* mRelatedBusEquivalent;

  // related_bus_pins
  const AstString* mRelatedBusPins;

  // related_output_pin
  const AstString* mRelatedOutputPin;

  // related_pin
  const AstString* mRelatedPin;

  // rise_resistance
  const AstFloat* mRiseResistance;

  // sdf_cond
  const AstString* mSdfCond;

  // sdf_cond_end
  const AstString* mSdfCondEnd;

  // sdf_cond_start
  const AstString* mSdfCondStart;

  // sdf_edges (noedge, start_edge, end_edge, both_edges)
  const AstString* mSdfEdges;

  // sensitization_master
  const AstString* mSensitizationMaster;

  // slope_fall
  const AstFloat* mSlopeFall;

  // slope_rise
  const AstFloat* mSlopeRise;

  // steady_state_resistance_above_high
  const AstFloat* mSteadyStateResistanceAboveHigh;

  // steady_state_resistance_below_low
  const AstFloat* mSteadyStateResistanceBelowLow;

  // steady_state_resistance_high
  const AstFloat* mSteadyStateResistanceHigh;

  // steady_state_resistance_low
  const AstFloat* mSteadyStateResistanceLow;

  // tied_off
  const AstBool* mTiedOff;

  // timing_sense
  const AstTimingSense* mTimingSense;

  // timing_type
  const AstTimingType* mTimingType;

  // wave_fall_sampling_index
  const AstInt* mWaveFallSamplingIndex;

  // wave_rise_sampling_index
  const AstInt* mWaveRiseSamplingIndex;

  // when
  const AstExpr* mWhen;

  // when_end
  const AstExpr* mWhenEnd;

  // when_start
  const AstExpr* mWhenStart;

  // fall_delay_intercept
  vector<const AstIntFloat*> mFallDelayIntercept;

  // fall_pin_resistance
  vector<const AstIntFloat*> mFallPinResistance;

  // mode
  const AstString* mModeName;
  const AstString* mModeValue;

  // pin_name_map
  const AstStrList* mPinNameMap;

  // rise_delay_intercept
  vector<const AstIntFloat*> mRiseDelayIntercept;

  // rise_pin_resistance
  vector<const AstIntFloat*> mRisePinResistance;

  // wave_fall
  const AstIntVector* mWaveFall;

  // wave_fall_time_interval
  const AstFloatVector* mWaveFallTimeInterval;

  // wave_rise
  const AstIntVector* mWaveRise;

  // wave_rise_time_interval
  const AstFloatVector* mWaveRiseTimeInterval;

  // cell_degradation
  const AstCellDegradation* mCellDegradation;

  // cell_fall
  const AstLut* mCellFall;

  // cell_rise
  const AstLut* mCellRise;

  // compact_ccs_fall
  const AstCCS* mCompactCCSFall;

  // compact_ccs_rise
  const AstCCS* mCompactCCSRise;

  // fall_constraint
  const AstLut* mFallConstraint;

  // fall_propagation
  const AstLut* mFallPropagation;

  // fall_transition
  const AstLut* mFallTransition;

  // output_current_fall
  const AstLut* mOutputCurrentFall;

  // output_current_rise
  const AstLut* mOutputCurrentRise;

  // rise_constraint
  const AstLut* mRiseConstraint;

  // rise_propagation
  const AstLut* mRisePropagation;

  // rise_transition
  const AstLut* mRiseTransition;

  // noise_immunity_above_high

  // noise_immunity_below_low

  // noise_immunity_high

  // noise_immunity_low

  // propagated_noise_height_above_high

  // propagated_noise_height_below_low

  // propagated_noise_height_high

  // propagated_noise_height_low

  // propagated_noise_peak_time_ratio_above_high

  // propagated_noise_peak_time_ratio_below_low

  // propagated_noise_peak_time_ratio_high

  // propagated_noise_peak_time_ratio_low

  // propagated_noise_width_high

  // propagated_noise_width_low

  // retaining_fall
  const AstLut* mRetainingFall;

  // retaining_rise
  const AstLut* mRetainingRise;

  // retain_fall_slew
  const AstLut* mRetainFallSlew;

  // retain_rise_slew
  const AstLut* mRetainRiseSlew;

  // steady_state_current_high

  // steady_state_current_low

  // steady_state_current_tristate

};

END_NAMESPACE_YM_DOTLIB

#endif // timingHANDLER_H
