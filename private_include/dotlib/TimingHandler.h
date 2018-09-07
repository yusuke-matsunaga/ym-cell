#ifndef timingHANDLER_H
#define timingHANDLER_H

/// @file TimingHandler.h
/// @brief TimingHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/EmptyGroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TimingHandler TimingHandler.h "TimingHandler.h"
/// @brief 'timing' Group Statement を読み込むためのハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 3
///           "pin Group Description and Syntax"
///
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
///   - when : "Boolean expression" ;
///   - when_end : "Boolean expression" ;
///   - when_start : "Boolean expression" ;
/// * Complex Attributes
///   - fall_delay_intercept ( integer, float ) ;
///   - fall_pin_resistance ( integer, float ) ;
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
///   - noise_immunity_before_low () { ... }
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
  public EmptyGroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  TimingHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~TimingHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif 'timing' Group Statement の記述をパースする．
  /// @param[in] dst_list 読み込んだ値を格納する変数
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(vector<const AstTiming*>& dst_list);


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
  // ???

  // sdf_cond_end
  // ???

  // sdf_cond_start
  // ???

  // sdf_edges
  // ???

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

  // when
  const AstExpr* mWhen;

  // when_end
  const AstExpr* mWhenEnd;

  // when_start
  const AstExpr* mWhenStart;

  // fall_delay_intercept
  const AstPieceWise* mFallDelayIntercept;

  // fall_pin_resistance
  const AstPieceWise* mFallPinResistance;

  // mode
  // ??? たぶん，(string, string)

  // rise_delay_intercept
  const AstPieceWise* mRiseDelayIntercept;

  // rise_pin_resistance
  const AstPieceWise* mRisePinResistance;

  // cell_degradation
  // ??

  // cell_fall
  const AstLut* mCellFall;

  // cell_rise
  const AstLut* mCellRise;

  // fall_constraint
  const AstLut* mFallConstraint;

  // fall_transition
  const AstLut* mFallTransition;

  // rise_constraint
  const AstLut* mRiseConstraint;

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

  // retaining_rise

  // retaining_fall

  // retain_rise_slew

  // retain_fall_slew

  // steady_state_current_high

  // steady_state_current_low

  // steady_state_current_tristate

  // 読み込んだ値
  const AstTiming* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // timingHANDLER_H
