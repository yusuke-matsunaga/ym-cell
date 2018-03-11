#ifndef DOTLIBTIMING_H
#define DOTLIBTIMING_H

/// @file DotlibTiming.h
/// @brief DolibTiming のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibTiming DotlibTiming.h "DotlibTiming.h"
/// @brief DotlibNode の木から取り出したタイミング情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTiming :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] related_pin
  /// @param[in] related_bus_pins
  /// @param[in] related_bus_equivalent
  /// @param[in] timing_sense
  /// @param[in] timing_type
  /// @param[in] when
  /// @param[in] when_start
  /// @param[in] when_end
  /// @param[in] rise_resistance
  /// @param[in] fall_resistance
  /// @param[in] intrinsic_rise
  /// @param[in] intrinsic_fall
  /// @param[in] slope_rise
  /// @param[in] slope_fall
  /// @param[in] rise_delay_intercept
  /// @param[in] fall_delay_intercept
  /// @param[in] rise_pin_resistance
  /// @param[in] fall_pin_resistance
  /// @param[in] cell_degradation
  /// @param[in] cell_rise
  /// @param[in] cell_fall
  /// @param[in] rise_constraint
  /// @param[in] fall_constraint
  /// @param[in] rise_propagation
  /// @param[in] fall_propagation
  /// @param[in] rise_transition
  /// @param[in] fall_transition
  /// @param[in] retaing_rise
  /// @param[in] retaing_fall
  /// @param[in] retain_rise_slew
  /// @param[in] retainfall_slew
  DotlibTiming(const FileRegion& loc,
	       const DotlibString* related_pin,
	       const DotlibString* related_bus_pins,
	       const DotlibString* related_bus_equivalent,
	       const DotlibTimingSense* timing_sense,
	       const DotlibTimingType* timing_type,
	       const DotlibExpr* when,
	       const DotlibExpr* when_start,
	       const DotlibExpr* when_end,
	       const DotlibFloat* rise_resistance,
	       const DotlibFloat* fall_resistance,
	       const DotlibFloat* intrinsic_rise,
	       const DotlibFloat* intrinsic_fall,
	       const DotlibFloat* slope_rise,
	       const DotlibFloat* slope_fall,
	       const DotlibFloat* rise_delay_intercept,
	       const DotlibFloat* fall_delay_intercept,
	       const DotlibFloat* rise_pin_resistance,
	       const DotlibFloat* fall_pin_resistance,
	       const DotlibFloat* cell_degradation,
	       const DotlibLut* cell_rise,
	       const DotlibLut* cell_fall,
	       const DotlibFloat* rise_constraint,
	       const DotlibFloat* fall_constraint,
	       const DotlibLut* rise_propagation,
	       const DotlibLut* fall_propagation,
	       const DotlibLut* rise_transition,
	       const DotlibLut* fall_transition,
	       const DotlibFloat* retaining_rise,
	       const DotlibFloat* retaining_fall,
	       const DotlibFloat* retain_rise_slew,
	       const DotlibFloat* retain_fall_slew);

  /// @brief デストラクタ
  virtual
  ~DotlibTiming();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

#if 0
  /// @brief 内容をセットする．
  bool
  set_data(const DotlibNode* timing_node);
#endif

  /// @brief "related_pin" を返す．
  const DotlibString*
  related_pin() const;

  /// @brief "related_bus_pins" を返す．
  const DotlibString*
  related_bus_pins() const;

  /// @brief "related_bus_equivalent" を返す．
  const DotlibString*
  related_bus_equivalent() const;

  /// @brief "timing_sense" を返す．
  const DotlibTimingSense*
  timing_sense() const;

  /// @brief "timing_type" を返す．
  const DotlibTimingType*
  timing_type() const;

  /// @brief "when" を返す．
  const DotlibExpr*
  when() const;

  /// @brief "when_start" を返す．
  const DotlibExpr*
  when_start() const;

  /// @brief "when_end" を返す．
  const DotlibExpr*
  when_end() const;

  /// @brief "rise_resistance" を返す．
  const DotlibFloat*
  rise_resistance() const;

  /// @brief "fall_resistance" を返す．
  const DotlibFloat*
  fall_resistance() const;

  /// @brief "intrinsic_rise" を返す．
  const DotlibFloat*
  intrinsic_rise() const;

  /// @brief "intrinsic_fall" を返す．
  const DotlibFloat*
  intrinsic_fall() const;

  /// @brief "slope_rise" を返す．
  const DotlibFloat*
  slope_rise() const;

  /// @brief "slope_fall" を返す．
  const DotlibFloat*
  slope_fall() const;

  /// @brief "rise_delay_intercept" を返す．
  const DotlibFloat*
  rise_delay_intercept() const;

  /// @brief "fall_delay_intercept" を返す．
  const DotlibFloat*
  fall_delay_intercept() const;

  /// @brief "rise_pin_resistance" を返す．
  const DotlibFloat*
  rise_pin_resistance() const;

  /// @brief "fall_pin_resistance" を返す．
  const DotlibFloat*
  fall_pin_resistance() const;

  /// @brief "cell_degradation" を返す．
  const DotlibFloat*
  cell_degradation() const;

  /// @brief "cell_rise" を返す．
  const DotlibLut*
  cell_rise() const;

  /// @brief "cell_fall" を返す．
  const DotlibLut*
  cell_fall() const;

  /// @brief "rise_constraint" を返す．
  const DotlibFloat*
  rise_constraint() const;

  /// @brief "fall_constraint" を返す．
  const DotlibFloat*
  fall_constraint() const;

  /// @brief "rise_propagation" を返す．
  const DotlibLut*
  rise_propagation() const;

  /// @brief "fall_propagation" を返す．
  const DotlibLut*
  fall_propagation() const;

  /// @brief "rise_transition" を返す．
  const DotlibLut*
  rise_transition() const;

  /// @brief "fall_transition" を返す．
  const DotlibLut*
  fall_transition() const;

  /// @brief "retaining_rise" を返す．
  const DotlibFloat*
  retaining_rise() const;

  /// @brief "retaining_fall" を返す．
  const DotlibFloat*
  retaining_fall() const;

  /// @brief "retain_rise_slew" を返す．
  const DotlibFloat*
  retain_rise_slew() const;

  /// @brief "retain_fall_slew" を返す．
  const DotlibFloat*
  retain_fall_slew() const;

  /// @brief 次の要素を返す．
  const DotlibTiming*
  next() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // related_pin
  const DotlibString* mRelatedPin;

  // related_bus_pins
  const DotlibString* mRelatedBusPins;

  // related_bus_equivalent
  const DotlibString* mRelatedBusEquivalent;

  // timing_sense
  const DotlibTimingSense* mTimingSense;

  // timing_type
  const DotlibTimingType* mTimingType;

  // when
  const DotlibExpr* mWhen;

  // when_start
  const DotlibExpr* mWhenStart;

  // when_end
  const DotlibExpr* mWhenEnd;

  // rise_resistance
  const DotlibFloat* mRiseResistance;

  // fall_resistance
  const DotlibFloat* mFallResistance;

  // intrinsic_rise
  const DotlibFloat* mIntrinsicRise;

  // intrinsic_fall
  const DotlibFloat* mIntrinsicFall;

  // slope_rise
  const DotlibFloat* mSlopeRise;

  // slope_fall
  const DotlibFloat* mSlopeFall;

  // rise_delay_intercept
  const DotlibFloat* mRiseDelayIntercept;

  // fall_delay_intercept
  const DotlibFloat* mFallDelayIntercept;

  // rise_pin_resistance
  const DotlibFloat* mRisePinResistance;

  // fall_pin_resistance
  const DotlibFloat* mFallPinResistance;

  // cell_degradation
  const DotlibFloat* mCellDegradation;

  // cell_rise
  const DotlibLut* mCellRise;

  // cell_fall
  const DotlibLut* mCellFall;

  // rise_constraint
  const DotlibFloat* mRiseConstraint;

  // fall_constraint
  const DotlibFloat* mFallConstraint;

  // rise_propagation
  const DotlibLut* mRisePropagation;

  // fall_propagation
  const DotlibLut* mFallPropagation;

  // rise_transition
  const DotlibLut* mRiseTransition;

  // fall_transition
  const DotlibLut* mFallTransition;

  // retaining_rise
  const DotlibFloat* mRetainingRise;

  // retaining_fall
  const DotlibFloat* mRetainingFall;

  // retain_rise_slew
  const DotlibFloat* mRetainRiseSlew;

  // retain_fall_slew
  const DotlibFloat* mRetainFallSlew;

  // 次の要素
  DotlibTiming* mNext;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief "related_pin" を返す．
inline
const DotlibString*
DotlibTiming::related_pin() const
{
  return mRelatedPin;
}

// @brief "related_bus_pins" を返す．
inline
const DotlibString*
DotlibTiming::related_bus_pins() const
{
  return mRelatedBusPins;
}

// @brief "related_bus_equivalent" を返す．
inline
const DotlibString*
DotlibTiming::related_bus_equivalent() const
{
  return mRelatedBusEquivalent;
}

// @brief "timing_sense" を返す．
inline
const DotlibTimingSense*
DotlibTiming::timing_sense() const
{
  return mTimingSense;
}

// @brief "timing_type" を返す．
inline
const DotlibTimingType*
DotlibTiming::timing_type() const
{
  return mTimingType;
}

// @brief "when" を返す．
inline
const DotlibExpr*
DotlibTiming::when() const
{
  return mWhen;
}

// @brief "when_start" を返す．
inline
const DotlibExpr*
DotlibTiming::when_start() const
{
  return mWhenStart;
}

// @brief "when_end" を返す．
inline
const DotlibExpr*
DotlibTiming::when_end() const
{
  return mWhenEnd;
}

// @brief "fall_resistance" を返す．
inline
const DotlibFloat*
DotlibTiming::fall_resistance() const
{
  return mFallResistance;
}

// @brief "rise_resistance" を返す．
inline
const DotlibFloat*
DotlibTiming::rise_resistance() const
{
  return mRiseResistance;
}

// @brief "intrinsic_fall" を返す．
inline
const DotlibFloat*
DotlibTiming::intrinsic_fall() const
{
  return mIntrinsicFall;
}

// @brief "intrinsic_rise" を返す．
inline
const DotlibFloat*
DotlibTiming::intrinsic_rise() const
{
  return mIntrinsicRise;
}

// @brief "slope_fall" を返す．
inline
const DotlibFloat*
DotlibTiming::slope_fall() const
{
  return mSlopeFall;
}

// @brief "slope_rise" を返す．
inline
const DotlibFloat*
DotlibTiming::slope_rise() const
{
  return mSlopeRise;
}

// @brief "fall_delay_intercept" を返す．
inline
const DotlibFloat*
DotlibTiming::fall_delay_intercept() const
{
  return mFallDelayIntercept;
}

// @brief "rise_delay_intercept" を返す．
inline
const DotlibFloat*
DotlibTiming::rise_delay_intercept() const
{
  return mRiseDelayIntercept;
}

// @brief "fall_pin_resistance" を返す．
inline
const DotlibFloat*
DotlibTiming::fall_pin_resistance() const
{
  return mFallPinResistance;
}

// @brief "rise_pin_resistance" を返す．
inline
const DotlibFloat*
DotlibTiming::rise_pin_resistance() const
{
  return mRisePinResistance;
}

// @brief "cell_degradation" を返す．
inline
const DotlibFloat*
DotlibTiming::cell_degradation() const
{
  return mCellDegradation;
}

// @brief "cell_fall" を返す．
inline
const DotlibLut*
DotlibTiming::cell_fall() const
{
  return mCellFall;
}

// @brief "cell_rise" を返す．
inline
const DotlibLut*
DotlibTiming::cell_rise() const
{
  return mCellRise;
}

// @brief "fall_constraint" を返す．
inline
const DotlibFloat*
DotlibTiming::fall_constraint() const
{
  return mFallConstraint;
}

// @brief "rise_constraint" を返す．
inline
const DotlibFloat*
DotlibTiming::rise_constraint() const
{
  return mRiseConstraint;
}

// @brief "fall_propagation" を返す．
inline
const DotlibLut*
DotlibTiming::fall_propagation() const
{
  return mFallPropagation;
}

// @brief "rise_propagation" を返す．
inline
const DotlibLut*
DotlibTiming::rise_propagation() const
{
  return mRisePropagation;
}

// @brief "fall_transition" を返す．
inline
const DotlibLut*
DotlibTiming::fall_transition() const
{
  return mFallTransition;
}

// @brief "rise_transition" を返す．
inline
const DotlibLut*
DotlibTiming::rise_transition() const
{
  return mRiseTransition;
}

// @brief "retaining_fall" を返す．
inline
const DotlibFloat*
DotlibTiming::retaining_fall() const
{
  return mRetainingFall;
}

// @brief "retaining_rise" を返す．
inline
const DotlibFloat*
DotlibTiming::retaining_rise() const
{
  return mRetainingRise;
}

// @brief "retain_fall_slew" を返す．
inline
const DotlibFloat*
DotlibTiming::retain_fall_slew() const
{
  return mRetainFallSlew;
}

// @brief "retain_rise_slew" を返す．
inline
const DotlibFloat*
DotlibTiming::retain_rise_slew() const
{
  return mRetainRiseSlew;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBTIMING_H
