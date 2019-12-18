#ifndef ASTTIMING_H
#define ASTTIMING_H

/// @file AstTiming.h
/// @brief DolibTiming のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "AstNode.h"
#include "AstArray.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstTiming AstTiming.h "AstTiming.h"
/// @brief タイミング情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstTiming :
  public AstNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] attr_loc 属性のファイル上の位置
  /// @param[in] header ヘッダのハンドラ
  /// @param[in] group グループ本体のハンドラ
  AstTiming(const FileRegion& attr_loc,
	    const StrListHandler& header,
	    const TimingHandler& group);

  /// @brief デストラクタ
  ~AstTiming();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const AstString*
  name() const;

  /// @brief "related_pin" を返す．
  const AstString*
  related_pin() const;

  /// @brief "related_bus_pins" を返す．
  const AstString*
  related_bus_pins() const;

  /// @brief "related_bus_equivalent" を返す．
  const AstString*
  related_bus_equivalent() const;

  /// @brief "timing_sense" を返す．
  const AstTimingSense*
  timing_sense() const;

  /// @brief "timing_type" を返す．
  const AstTimingType*
  timing_type() const;

  /// @brief "when" を返す．
  const AstExpr*
  when() const;

  /// @brief "when_start" を返す．
  const AstExpr*
  when_start() const;

  /// @brief "when_end" を返す．
  const AstExpr*
  when_end() const;

  /// @brief "rise_resistance" を返す．
  const AstFloat*
  rise_resistance() const;

  /// @brief "fall_resistance" を返す．
  const AstFloat*
  fall_resistance() const;

  /// @brief "intrinsic_rise" を返す．
  const AstFloat*
  intrinsic_rise() const;

  /// @brief "intrinsic_fall" を返す．
  const AstFloat*
  intrinsic_fall() const;

  /// @brief "slope_rise" を返す．
  const AstFloat*
  slope_rise() const;

  /// @brief "slope_fall" を返す．
  const AstFloat*
  slope_fall() const;

  /// @brief "rise_delay_intercept" を返す．
  AstArray<const AstIntFloat*>
  rise_delay_intercept() const;

  /// @brief "fall_delay_intercept" を返す．
  AstArray<const AstIntFloat*>
  fall_delay_intercept() const;

  /// @brief "rise_pin_resistance" を返す．
  AstArray<const AstIntFloat*>
  rise_pin_resistance() const;

  /// @brief "fall_pin_resistance" を返す．
  AstArray<const AstIntFloat*>
  fall_pin_resistance() const;

  /// @brief "cell_degradation" を返す．
  const AstCellDegradation*
  cell_degradation() const;

  /// @brief "cell_rise" を返す．
  const AstLut*
  cell_rise() const;

  /// @brief "cell_fall" を返す．
  const AstLut*
  cell_fall() const;

  /// @brief "compact_ccs_rise" を返す．
  const AstCCS*
  compact_ccs_rise() const;

  /// @brief "compact_ccs_rise" を返す．
  const AstCCS*
  compact_ccs_fall() const;

  /// @brief "rise_constraint" を返す．
  const AstLut*
  rise_constraint() const;

  /// @brief "fall_constraint" を返す．
  const AstLut*
  fall_constraint() const;

  /// @brief "rise_propagation" を返す．
  const AstLut*
  rise_propagation() const;

  /// @brief "fall_propagation" を返す．
  const AstLut*
  fall_propagation() const;

  /// @brief "rise_transition" を返す．
  const AstLut*
  rise_transition() const;

  /// @brief "fall_transition" を返す．
  const AstLut*
  fall_transition() const;

  /// @brief "retaining_rise" を返す．
  const AstLut*
  retaining_rise() const;

  /// @brief "retaining_fall" を返す．
  const AstLut*
  retaining_fall() const;

  /// @brief "retain_rise_slew" を返す．
  const AstLut*
  retain_rise_slew() const;

  /// @brief "retain_fall_slew" を返す．
  const AstLut*
  retain_fall_slew() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  void
  dump(ostream& s,
       int indent = 0) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  const AstString* mName;

  // related_pin
  const AstString* mRelatedPin;

  // related_bus_pins
  const AstString* mRelatedBusPins;

  // related_bus_equivalent
  const AstString* mRelatedBusEquivalent;

  // timing_sense
  const AstTimingSense* mTimingSense;

  // timing_type
  const AstTimingType* mTimingType;

  // when
  const AstExpr* mWhen;

  // when_start
  const AstExpr* mWhenStart;

  // when_end
  const AstExpr* mWhenEnd;

  // rise_resistance
  const AstFloat* mRiseResistance;

  // fall_resistance
  const AstFloat* mFallResistance;

  // intrinsic_rise
  const AstFloat* mIntrinsicRise;

  // intrinsic_fall
  const AstFloat* mIntrinsicFall;

  // slope_rise
  const AstFloat* mSlopeRise;

  // slope_fall
  const AstFloat* mSlopeFall;

  // rise_delay_intercept
  AstArray<const AstIntFloat*> mRiseDelayIntercept;

  // fall_delay_intercept
  AstArray<const AstIntFloat*> mFallDelayIntercept;

  // rise_pin_resistance
  AstArray<const AstIntFloat*> mRisePinResistance;

  // fall_pin_resistance
  AstArray<const AstIntFloat*> mFallPinResistance;

  // cell_degradation
  const AstCellDegradation* mCellDegradation;

  // cell_rise
  const AstLut* mCellRise;

  // cell_fall
  const AstLut* mCellFall;

  // compact_ccs_rise
  const AstCCS* mCompactCCSRise;

  // compact_ccs_fall
  const AstCCS* mCompactCCSFall;

  // rise_constraint
  const AstLut* mRiseConstraint;

  // fall_constraint
  const AstLut* mFallConstraint;

  // rise_propagation
  const AstLut* mRisePropagation;

  // fall_propagation
  const AstLut* mFallPropagation;

  // rise_transition
  const AstLut* mRiseTransition;

  // fall_transition
  const AstLut* mFallTransition;

  // retaining_rise
  const AstLut* mRetainingRise;

  // retaining_fall
  const AstLut* mRetainingFall;

  // retain_rise_slew
  const AstLut* mRetainRiseSlew;

  // retain_fall_slew
  const AstLut* mRetainFallSlew;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief "related_pin" を返す．
inline
const AstString*
AstTiming::related_pin() const
{
  return mRelatedPin;
}

// @brief "related_bus_pins" を返す．
inline
const AstString*
AstTiming::related_bus_pins() const
{
  return mRelatedBusPins;
}

// @brief "related_bus_equivalent" を返す．
inline
const AstString*
AstTiming::related_bus_equivalent() const
{
  return mRelatedBusEquivalent;
}

// @brief "timing_sense" を返す．
inline
const AstTimingSense*
AstTiming::timing_sense() const
{
  return mTimingSense;
}

// @brief "timing_type" を返す．
inline
const AstTimingType*
AstTiming::timing_type() const
{
  return mTimingType;
}

// @brief "when" を返す．
inline
const AstExpr*
AstTiming::when() const
{
  return mWhen;
}

// @brief "when_start" を返す．
inline
const AstExpr*
AstTiming::when_start() const
{
  return mWhenStart;
}

// @brief "when_end" を返す．
inline
const AstExpr*
AstTiming::when_end() const
{
  return mWhenEnd;
}

// @brief "fall_resistance" を返す．
inline
const AstFloat*
AstTiming::fall_resistance() const
{
  return mFallResistance;
}

// @brief "rise_resistance" を返す．
inline
const AstFloat*
AstTiming::rise_resistance() const
{
  return mRiseResistance;
}

// @brief "intrinsic_fall" を返す．
inline
const AstFloat*
AstTiming::intrinsic_fall() const
{
  return mIntrinsicFall;
}

// @brief "intrinsic_rise" を返す．
inline
const AstFloat*
AstTiming::intrinsic_rise() const
{
  return mIntrinsicRise;
}

// @brief "slope_fall" を返す．
inline
const AstFloat*
AstTiming::slope_fall() const
{
  return mSlopeFall;
}

// @brief "slope_rise" を返す．
inline
const AstFloat*
AstTiming::slope_rise() const
{
  return mSlopeRise;
}

// @brief "fall_delay_intercept" を返す．
inline
AstArray<const AstIntFloat*>
AstTiming::fall_delay_intercept() const
{
  return mFallDelayIntercept;
}

// @brief "rise_delay_intercept" を返す．
inline
AstArray<const AstIntFloat*>
AstTiming::rise_delay_intercept() const
{
  return mRiseDelayIntercept;
}

// @brief "fall_pin_resistance" を返す．
inline
AstArray<const AstIntFloat*>
AstTiming::fall_pin_resistance() const
{
  return mFallPinResistance;
}

// @brief "rise_pin_resistance" を返す．
inline
AstArray<const AstIntFloat*>
AstTiming::rise_pin_resistance() const
{
  return mRisePinResistance;
}

// @brief "cell_degradation" を返す．
inline
const AstCellDegradation*
AstTiming::cell_degradation() const
{
  return mCellDegradation;
}

// @brief "cell_fall" を返す．
inline
const AstLut*
AstTiming::cell_fall() const
{
  return mCellFall;
}

// @brief "cell_rise" を返す．
inline
const AstLut*
AstTiming::cell_rise() const
{
  return mCellRise;
}

// @brief "fall_constraint" を返す．
inline
const AstLut*
AstTiming::fall_constraint() const
{
  return mFallConstraint;
}

// @brief "rise_constraint" を返す．
inline
const AstLut*
AstTiming::rise_constraint() const
{
  return mRiseConstraint;
}

// @brief "fall_propagation" を返す．
inline
const AstLut*
AstTiming::fall_propagation() const
{
  return mFallPropagation;
}

// @brief "rise_propagation" を返す．
inline
const AstLut*
AstTiming::rise_propagation() const
{
  return mRisePropagation;
}

// @brief "fall_transition" を返す．
inline
const AstLut*
AstTiming::fall_transition() const
{
  return mFallTransition;
}

// @brief "rise_transition" を返す．
inline
const AstLut*
AstTiming::rise_transition() const
{
  return mRiseTransition;
}

// @brief "retaining_fall" を返す．
inline
const AstLut*
AstTiming::retaining_fall() const
{
  return mRetainingFall;
}

// @brief "retaining_rise" を返す．
inline
const AstLut*
AstTiming::retaining_rise() const
{
  return mRetainingRise;
}

// @brief "retain_fall_slew" を返す．
inline
const AstLut*
AstTiming::retain_fall_slew() const
{
  return mRetainFallSlew;
}

// @brief "retain_rise_slew" を返す．
inline
const AstLut*
AstTiming::retain_rise_slew() const
{
  return mRetainRiseSlew;
}

END_NAMESPACE_YM_DOTLIB

#endif // ASTTIMING_H
