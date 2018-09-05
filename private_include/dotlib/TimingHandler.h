#ifndef timingHANDLER_H
#define timingHANDLER_H

/// @file TimingHandler.h
/// @brief TimingHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "EmptyGroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TimingHandler TimingHandler.h "TimingHandler.h"
/// @brief timing 属性を読み込むためのハンドラ
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

  /// @breif timing group statement の記述をパースする．
  /// @return 読み込んだ値を返す．
  const AstTiming*
  parse_value();


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  read_group_attr(AttrType attr_type,
		  const FileRegion& attr_loc) override;

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

  // related_pin_equivalent
  const AstString* mRelatedPinEquivalent;

  // related_bus_pins
  const AstString* mRelatedBusPins;

  // related_output_pin
  const AstString* mRelatedOutputPin;

  // related_pin
  const AstString* mRelatedPin;

  // timing_sense
  const AstTimingSense* mTimingSense;

  // timing_type
  const AstTimingType* mTimingType;

  // edge_rate_sensitivity_f0

  // rise_resistance
  const AstFloat* mRiseResistance;

  // fall_resistance
  const AstFloat* mFallResistance;

  // intrinsic_rise
  const AstFloat* mIntrinsicRise;

  // intrinsic_fall
  const AstFloat* mIntrinsicFall;

  // sdf_cond

  // slope_rise
  const AstFloat* mSlopeRise;

  // slope_fall
  const AstFloat* mSlopeFall;

  // when
  const AstExpr* mWhen;

  // when_start
  const AstExpr* mWhenStart;

  // when_end
  const AstExpr* mWhenEnd;

  // rise_delay_intercept
  const AstPieceWise* mRiseDelayIntercept;

  // fall_delay_intercept
  const AstPieceWise* mFallDelayIntercept;

  // rise_pin_resistance
  const AstPieceWise* mRisePinResistance;

  // fall_pin_resistance
  const AstPieceWise* mFallPinResistance;

  // orders

  // coefs

  // cell_degradation

  // cell_rise
  const AstLut* mCellRise;

  // cell_fall
  const AstLut* mCellFall;

  // rise_constraint
  const AstLut* mRiseConstraint;

  // fall_constraint
  const AstLut* mFallConstraint;

  // rise_transition
  const AstLut* mRiseTransition;

  // fall_transition
  const AstLut* mFallTransition;

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
