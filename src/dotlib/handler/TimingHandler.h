#ifndef timingHANDLER_H
#define timingHANDLER_H

/// @file TimingHandler.h
/// @brief TimingHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"
#include "FloatHandler.h"
#include "FuncHandler.h"
#include "PieceWiseHandler.h"
#include "TableHandler.h"
#include "TimingSenseHandler.h"
#include "TimingTypeHandler.h"


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

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const vector<const AstTiming*>&
  value() const;


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
  parse_attr(AttrType attr_type,
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
  StrHandler mRelatedPinEquivalent;

  // related_bus_pins
  StrHandler mRelatedBusPins;

  // related_output_pin
  StrHandler mRelatedOutputPin;

  // related_pin
  StrHandler mRelatedPin;

  // timing_sense
  TimingSenseHandler mTimingSense;

  // timing_type
  TimingTypeHandler mTimingType;

  // edge_rate_sensitivity_f0

  // rise_resistance
  FloatHandler mRiseResistance;

  // fall_resistance
  FloatHandler mFallResistance;

  // intrinsic_rise
  FloatHandler mIntrinsicRise;

  // intrinsic_fall
  FloatHandler mIntrinsicFall;

  // sdf_cond

  // slope_rise
  FloatHandler mSlopeRise;

  // slope_fall
  FloatHandler mSlopeFall;

  // when
  FuncHandler mWhen;

  // when_start
  FuncHandler mWhenStart;

  // when_end
  FuncHandler mWhenEnd;

  // rise_delay_intercept
  PieceWiseHandler mRiseDelayIntercept;

  // fall_delay_intercept
  PieceWiseHandler mFallDelayIntercept;

  // rise_pin_resistance
  PieceWiseHandler mRisePinResistance;

  // fall_pin_resistance
  PieceWiseHandler mFallPinResistance;

  // orders

  // coefs

  // cell_degradation

  // cell_rise
  TableHandler mCellRise;

  // cell_fall
  TableHandler mCellFall;

  // rise_constraint
  TableHandler mRiseConstraint;

  // fall_constraint
  TableHandler mFallConstraint;

  // rise_transition
  TableHandler mRiseTransition;

  // fall_transition
  TableHandler mFallTransition;

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

  // 読み込んだ値のリスト
  vector<const AstTiming*> mValueList;

};

END_NAMESPACE_YM_DOTLIB

#endif // timingHANDLER_H
