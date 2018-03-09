#ifndef DOTLIBTIMING_H
#define DOTLIBTIMING_H

/// @file DotlibTiming.h
/// @brief DolibTiming のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibBase.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibTiming DotlibTiming.h "DotlibTiming.h"
/// @brief DotlibNode の木から取り出したタイミング情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTiming :
  public DotlibBase
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  DotlibTiming(const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibTiming();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をセットする．
  bool
  set_data(const DotlibNode* timing_node);

  /// @brief "related_pin" を返す．
  const DotlibNode*
  related_pin() const;

  /// @brief "related_bus_pins" を返す．
  const DotlibNode*
  related_bus_pins() const;

  /// @brief "related_bus_equivalent" を返す．
  const DotlibNode*
  related_bus_equivalent() const;

  /// @brief "timing_sense" を返す．
  ClibTimingSense
  timing_sense() const;

  /// @brief "timing_type" を返す．
  ClibTimingType
  timing_type() const;

  /// @brief "when" を返す．
  const DotlibNode*
  when() const;

  /// @brief "when_start" を返す．
  const DotlibNode*
  when_start() const;

  /// @brief "when_end" を返す．
  const DotlibNode*
  when_end() const;

  /// @brief "rise_resistance" を返す．
  const DotlibNode*
  rise_resistance() const;

  /// @brief "fall_resistance" を返す．
  const DotlibNode*
  fall_resistance() const;

  /// @brief "intrinsic_rise" を返す．
  const DotlibNode*
  intrinsic_rise() const;

  /// @brief "intrinsic_fall" を返す．
  const DotlibNode*
  intrinsic_fall() const;

  /// @brief "slope_rise" を返す．
  const DotlibNode*
  slope_rise() const;

  /// @brief "slope_fall" を返す．
  const DotlibNode*
  slope_fall() const;

  /// @brief "rise_delay_intercept" を返す．
  const DotlibNode*
  rise_delay_intercept() const;

  /// @brief "fall_delay_intercept" を返す．
  const DotlibNode*
  fall_delay_intercept() const;

  /// @brief "rise_pin_resistance" を返す．
  const DotlibNode*
  rise_pin_resistance() const;

  /// @brief "fall_pin_resistance" を返す．
  const DotlibNode*
  fall_pin_resistance() const;

  /// @brief "cell_degradation" を返す．
  const DotlibNode*
  cell_degradation() const;

  /// @brief "cell_rise" を返す．
  const DotlibNode*
  cell_rise() const;

  /// @brief "cell_fall" を返す．
  const DotlibNode*
  cell_fall() const;

  /// @brief "rise_constraint" を返す．
  const DotlibNode*
  rise_constraint() const;

  /// @brief "fall_constraint" を返す．
  const DotlibNode*
  fall_constraint() const;

  /// @brief "rise_propagation" を返す．
  const DotlibNode*
  rise_propagation() const;

  /// @brief "fall_propagation" を返す．
  const DotlibNode*
  fall_propagation() const;

  /// @brief "rise_transition" を返す．
  const DotlibNode*
  rise_transition() const;

  /// @brief "fall_transition" を返す．
  const DotlibNode*
  fall_transition() const;

  /// @brief "retaining_rise" を返す．
  const DotlibNode*
  retaining_rise() const;

  /// @brief "retaining_fall" を返す．
  const DotlibNode*
  retaining_fall() const;

  /// @brief "retain_rise_slew" を返す．
  const DotlibNode*
  retain_rise_slew() const;

  /// @brief "retain_fall_slew" を返す．
  const DotlibNode*
  retain_fall_slew() const;

  /// @brief 次の要素を返す．
  const DotlibTiming*
  next() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // related_pin
  const DotlibNode* mRelatedPin;

  // related_bus_pins
  const DotlibNode* mRelatedBusPins;

  // related_bus_equivalent
  const DotlibNode* mRelatedBusEquivalent;

  // rise_resistance
  const DotlibNode* mRiseResistance;

  // timing_sense
  ClibTimingSense mTimingSense;

  // timing_type
  ClibTimingType mTimingType;

  // when
  const DotlibNode* mWhen;

  // when_start
  const DotlibNode* mWhenStart;

  // when_end
  const DotlibNode* mWhenEnd;

  // fall_resistance
  const DotlibNode* mFallResistance;

  // intrinsic_rise
  const DotlibNode* mIntrinsicRise;

  // intrinsic_fall
  const DotlibNode* mIntrinsicFall;

  // slope_rise
  const DotlibNode* mSlopeRise;

  // slope_fall
  const DotlibNode* mSlopeFall;

  // rise_delay_intercept
  const DotlibNode* mRiseDelayIntercept;

  // fall_delay_intercept
  const DotlibNode* mFallDelayIntercept;

  // rise_pin_resistance
  const DotlibNode* mRisePinResistance;

  // fall_pin_resistance
  const DotlibNode* mFallPinResistance;

  // cell_degradation
  const DotlibNode* mClibDegradation;

  // cell_rise
  const DotlibNode* mClibRise;

  // cell_fall
  const DotlibNode* mClibFall;

  // rise_constraint
  const DotlibNode* mRiseConstraint;

  // fall_constraint
  const DotlibNode* mFallConstraint;

  // rise_propagation
  const DotlibNode* mRisePropagation;

  // fall_propagation
  const DotlibNode* mFallPropagation;

  // rise_transition
  const DotlibNode* mRiseTransition;

  // fall_transition
  const DotlibNode* mFallTransition;

  // retaining_rise
  const DotlibNode* mRetainingRise;

  // retaining_fall
  const DotlibNode* mRetainingFall;

  // retain_rise_slew
  const DotlibNode* mRetainRiseSlew;

  // retain_fall_slew
  const DotlibNode* mRetainFallSlew;

  // 次の要素
  DotlibTiming* mNext;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief "fall_resistance" を返す．
inline
const DotlibNode*
DotlibTiming::fall_resistance() const
{
  return mFallResistance;
}

// @brief "rise_resistance" を返す．
inline
const DotlibNode*
DotlibTiming::rise_resistance() const
{
  return mRiseResistance;
}

// @brief "intrinsic_fall" を返す．
inline
const DotlibNode*
DotlibTiming::intrinsic_fall() const
{
  return mIntrinsicFall;
}

// @brief "intrinsic_rise" を返す．
inline
const DotlibNode*
DotlibTiming::intrinsic_rise() const
{
  return mIntrinsicRise;
}

// @brief "related_bus_equivalent" を返す．
inline
const DotlibNode*
DotlibTiming::related_bus_equivalent() const
{
  return mRelatedBusEquivalent;
}

// @brief "related_bus_pins" を返す．
inline
const DotlibNode*
DotlibTiming::related_bus_pins() const
{
  return mRelatedBusPins;
}

// @brief "related_pin" を返す．
inline
const DotlibNode*
DotlibTiming::related_pin() const
{
  return mRelatedPin;
}

// @brief "slope_fall" を返す．
inline
const DotlibNode*
DotlibTiming::slope_fall() const
{
  return mSlopeFall;
}

// @brief "slope_rise" を返す．
inline
const DotlibNode*
DotlibTiming::slope_rise() const
{
  return mSlopeRise;
}

// @brief "timing_sense" を返す．
inline
ClibTimingSense
DotlibTiming::timing_sense() const
{
  return mTimingSense;
}

// @brief "timing_type" を返す．
inline
ClibTimingType
DotlibTiming::timing_type() const
{
  return mTimingType;
}

// @brief "when" を返す．
inline
const DotlibNode*
DotlibTiming::when() const
{
  return mWhen;
}

// @brief "when_start" を返す．
inline
const DotlibNode*
DotlibTiming::when_start() const
{
  return mWhenStart;
}

// @brief "when_end" を返す．
inline
const DotlibNode*
DotlibTiming::when_end() const
{
  return mWhenEnd;
}

// @brief "fall_delay_intercept" を返す．
inline
const DotlibNode*
DotlibTiming::fall_delay_intercept() const
{
  return mFallDelayIntercept;
}

// @brief "rise_delay_intercept" を返す．
inline
const DotlibNode*
DotlibTiming::rise_delay_intercept() const
{
  return mRiseDelayIntercept;
}

// @brief "fall_pin_resistance" を返す．
inline
const DotlibNode*
DotlibTiming::fall_pin_resistance() const
{
  return mFallPinResistance;
}

// @brief "rise_pin_resistance" を返す．
inline
const DotlibNode*
DotlibTiming::rise_pin_resistance() const
{
  return mRisePinResistance;
}

// @brief "cell_degradation" を返す．
inline
const DotlibNode*
DotlibTiming::cell_degradation() const
{
  return mClibDegradation;
}

// @brief "cell_fall" を返す．
inline
const DotlibNode*
DotlibTiming::cell_fall() const
{
  return mClibFall;
}

// @brief "cell_rise" を返す．
inline
const DotlibNode*
DotlibTiming::cell_rise() const
{
  return mClibRise;
}

// @brief "fall_constraint" を返す．
inline
const DotlibNode*
DotlibTiming::fall_constraint() const
{
  return mFallConstraint;
}

// @brief "rise_constraint" を返す．
inline
const DotlibNode*
DotlibTiming::rise_constraint() const
{
  return mRiseConstraint;
}

// @brief "fall_propagation" を返す．
inline
const DotlibNode*
DotlibTiming::fall_propagation() const
{
  return mFallPropagation;
}

// @brief "rise_propagation" を返す．
inline
const DotlibNode*
DotlibTiming::rise_propagation() const
{
  return mRisePropagation;
}

// @brief "fall_transition" を返す．
inline
const DotlibNode*
DotlibTiming::fall_transition() const
{
  return mFallTransition;
}

// @brief "rise_transition" を返す．
inline
const DotlibNode*
DotlibTiming::rise_transition() const
{
  return mRiseTransition;
}

// @brief "retaining_fall" を返す．
inline
const DotlibNode*
DotlibTiming::retaining_fall() const
{
  return mRetainingFall;
}

// @brief "retaining_rise" を返す．
inline
const DotlibNode*
DotlibTiming::retaining_rise() const
{
  return mRetainingRise;
}

// @brief "retain_fall_slew" を返す．
inline
const DotlibNode*
DotlibTiming::retain_fall_slew() const
{
  return mRetainFallSlew;
}

// @brief "retain_rise_slew" を返す．
inline
const DotlibNode*
DotlibTiming::retain_rise_slew() const
{
  return mRetainRiseSlew;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBTIMING_H
