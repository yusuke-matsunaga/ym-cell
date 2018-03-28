#ifndef timingHANDLER_H
#define timingHANDLER_H

/// @file TimingHandler.h
/// @brief TimingHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"


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
  virtual
  ~TimingHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 属性値を読み込む．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return 読み込んだ値を表す AstNode を返す．
  ///
  /// エラーの場合には nullptr を返す．
  virtual
  const AstNode*
  parse_attr_value(AttrType attr_type,
		   const FileRegion& attr_loc) override;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief パーズする．
  /// @param[in] attr_type 属性
  /// @param[in] attr_loc ファイル上の位置
  /// @return 読み込んだ AstTiming を返す．
  ///
  /// エラーの場合には nullptr を返す．
  const AstTiming*
  parse(AttrType attr_type,
	const FileRegion& attr_loc);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常に処理した．
  /// @retval false 処理中にエラーが起こった．
  virtual
  bool
  parse_attr(AttrType attr_type,
	     const FileRegion& attr_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // string ハンドラ
  StrSimpleHandler* mStringHandler;

  // float ハンドラ
  FloatSimpleHandler* mFloatHandler;

  // function ハンドラ
  FuncHandler* mFuncHandler;

  // timing sense ハンドラ
  TimingSenseHandler* mTimingSenseHandler;

  // timing type ハンドラ
  TimingTypeHandler* mTimingTypeHandler;

  // piece wise ハンドラ
  PwComplexHandler* mPieceWiseHandler;

  // table ハンドラ
  TableHandler* mTableHandler;

  // gen_group ハンドラ
  GenGroupHandler* mGenGroupHandler;

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

};

END_NAMESPACE_YM_DOTLIB

#endif // timingHANDLER_H
