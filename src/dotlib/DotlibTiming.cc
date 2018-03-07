
/// @file DotlibTiming.cc
/// @brief DotlibTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibTiming.h"
#include "DotlibAttr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibTiming
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibTiming::DotlibTiming()
{
}

// @brief デストラクタ
DotlibTiming::~DotlibTiming()
{
}

// @brief 内容をセットする．
bool
DotlibTiming::set_data(const DotlibNode* timing_node)
{
  init();

  mFallResistance = nullptr;
  mRiseResistance = nullptr;
  mIntrinsicFall = nullptr;
  mIntrinsicRise = nullptr;
  mRelatedBusEquivalent = nullptr;
  mRelatedBusPins = nullptr;
  mRelatedPin = nullptr;
  mSlopeFall = nullptr;
  mSlopeRise = nullptr;
  mTimingSense = kClibNonUnate;
  mTimingType = kClibTimingCombinational;
  mWhen = nullptr;
  mWhenStart = nullptr;
  mWhenEnd = nullptr;
  mFallDelayIntercept = nullptr;
  mRiseDelayIntercept = nullptr;
  mFallPinResistance = nullptr;
  mRisePinResistance = nullptr;
  mClibDegradation = nullptr;
  mClibFall = nullptr;
  mClibRise = nullptr;
  mFallConstraint = nullptr;
  mRiseConstraint = nullptr;
  mFallPropagation = nullptr;
  mRisePropagation = nullptr;
  mFallTransition = nullptr;
  mRiseTransition = nullptr;
  mRetainingFall = nullptr;
  mRetainingRise = nullptr;
  mRetainFallSlew = nullptr;
  mRetainRiseSlew = nullptr;

  // 属性を内部のハッシュに登録する．
  for ( const DotlibAttr* attr = timing_node->attr_top();
	attr; attr = attr->next() ) {
    AttrType attr_type = attr->attr_type();
    const DotlibNode* attr_value = attr->attr_value();
    add(attr_type, attr_value);
  }

  // 'related_pin' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RELATED_PIN, mRelatedPin) ) {
    return false;
  }

  // 'related_bus_pins' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RELATED_BUS_PINS, mRelatedBusPins) ) {
    return false;
  }

  // 'related_bus_equivalent' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RELATED_BUS_EQUIVALENT, mRelatedBusEquivalent) ) {
    return false;
  }

  // 'timing_sense' を取り出す．
  const DotlibNode* ts_node = nullptr;
  if ( !expect_singleton_or_null(ATTR_TIMING_SENSE, ts_node) ) {
    return false;
  }
  if ( ts_node == nullptr ) {
    mTimingSense = kClibNonUnate;
  }
  else {
    ASSERT_COND( ts_node->type() == DotlibNode::kTimingSense );
    mTimingSense = ts_node->timing_sense();
  }

  // 'timing_type' を取り出す．
  const DotlibNode* tt_node = nullptr;
  if ( !expect_singleton_or_null(ATTR_TIMING_TYPE, tt_node) ) {
    return false;
  }
  if ( tt_node == nullptr ) {
    mTimingType = kClibTimingCombinational;
  }
  else {
    ASSERT_COND( tt_node->type() == DotlibNode::kTimingType );
    mTimingType = tt_node->timing_type();
  }

  // 'when' を取り出す．
  if ( !expect_singleton_or_null(ATTR_WHEN, mWhen) ) {
    return false;
  }

  // 'when_start' を取り出す．
  if ( !expect_singleton_or_null(ATTR_WHEN_START, mWhenStart) ) {
    return false;
  }

  // 'when_end' を取り出す．
  if ( !expect_singleton_or_null(ATTR_WHEN_END, mWhenEnd) ) {
    return false;
  }

  // 'rise_resistance' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RISE_RESISTANCE, mRiseResistance) ) {
    return false;
  }

  // 'fall_resistance' を取り出す．
  if ( !expect_singleton_or_null(ATTR_FALL_RESISTANCE, mFallResistance) ) {
    return false;
  }

  // 'intrinsic_rise' を取り出す．
  if ( !expect_singleton_or_null(ATTR_INTRINSIC_RISE, mIntrinsicRise) ) {
    return false;
  }

  // 'intrinsic_fall' を取り出す．
  if ( !expect_singleton_or_null(ATTR_INTRINSIC_FALL, mIntrinsicFall) ) {
    return false;
  }

  // 'slope_rise' を取り出す．
  if ( !expect_singleton_or_null(ATTR_SLOPE_RISE, mSlopeRise) ) {
    return false;
  }

  // 'slope_fall' を取り出す．
  if ( !expect_singleton_or_null(ATTR_SLOPE_FALL, mSlopeFall) ) {
    return false;
  }

  // 'rise_delay_intercept' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RISE_DELAY_INTERCEPT, mRiseDelayIntercept) ) {
    return false;
  }

  // 'fall_delay_intercept' を取り出す．
  if ( !expect_singleton_or_null(ATTR_FALL_DELAY_INTERCEPT, mFallDelayIntercept) ) {
    return false;
  }

  // 'rise_pin_resistance' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RISE_PIN_RESISTANCE, mRisePinResistance) ) {
    return false;
  }

  // 'fall_pin_resistance' を取り出す．
  if ( !expect_singleton_or_null(ATTR_FALL_PIN_RESISTANCE, mFallPinResistance) ) {
    return false;
  }

  // 'cell_degradation' を取り出す．
  if ( !expect_singleton_or_null(ATTR_CELL_DEGRADATION, mClibDegradation) ) {
    return false;
  }

  // 'cell_rise' を取り出す．
  if ( !expect_singleton_or_null(ATTR_CELL_RISE, mClibRise) ) {
    return false;
  }

  // 'cell_fall' を取り出す．
  if ( !expect_singleton_or_null(ATTR_CELL_FALL, mClibFall) ) {
    return false;
  }

  // 'rise_constraint' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RISE_CONSTRAINT, mRiseConstraint) ) {
    return false;
  }

  // 'fall_constraint' を取り出す．
  if ( !expect_singleton_or_null(ATTR_FALL_CONSTRAINT, mFallConstraint) ) {
    return false;
  }

  // 'rise_propagation' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RISE_PROPAGATION, mRisePropagation) ) {
    return false;
  }

  // 'fall_propagation' を取り出す．
  if ( !expect_singleton_or_null(ATTR_FALL_PROPAGATION, mFallPropagation) ) {
    return false;
  }

  // 'rise_transition' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RISE_TRANSITION, mRiseTransition) ) {
    return false;
  }

  // 'fall_transition' を取り出す．
  if ( !expect_singleton_or_null(ATTR_FALL_TRANSITION, mFallTransition) ) {
    return false;
  }

  // 'retaining_rise' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RETAINING_RISE, mRetainingRise) ) {
    return false;
  }

  // 'retaining_fall' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RETAINING_FALL, mRetainingFall) ) {
    return false;
  }

  // 'retain_rise_slew' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RETAIN_RISE_SLEW, mRetainRiseSlew) ) {
    return false;
  }

  // 'retain_fall_slew' を取り出す．
  if ( !expect_singleton_or_null(ATTR_RETAIN_FALL_SLEW, mRetainFallSlew) ) {
    return false;
  }

  return true;
}

// @brief "fall_resistance" を返す．
const DotlibNode*
DotlibTiming::fall_resistance() const
{
  return mFallResistance;
}

// @brief "rise_resistance" を返す．
const DotlibNode*
DotlibTiming::rise_resistance() const
{
  return mRiseResistance;
}

// @brief "intrinsic_fall" を返す．
const DotlibNode*
DotlibTiming::intrinsic_fall() const
{
  return mIntrinsicFall;
}

// @brief "intrinsic_rise" を返す．
const DotlibNode*
DotlibTiming::intrinsic_rise() const
{
  return mIntrinsicRise;
}

// @brief "related_bus_equivalent" を返す．
const DotlibNode*
DotlibTiming::related_bus_equivalent() const
{
  return mRelatedBusEquivalent;
}

// @brief "related_bus_pins" を返す．
const DotlibNode*
DotlibTiming::related_bus_pins() const
{
  return mRelatedBusPins;
}

// @brief "related_pin" を返す．
const DotlibNode*
DotlibTiming::related_pin() const
{
  return mRelatedPin;
}

// @brief "slope_fall" を返す．
const DotlibNode*
DotlibTiming::slope_fall() const
{
  return mSlopeFall;
}

// @brief "slope_rise" を返す．
const DotlibNode*
DotlibTiming::slope_rise() const
{
  return mSlopeRise;
}

// @brief "timing_sense" を返す．
ClibTimingSense
DotlibTiming::timing_sense() const
{
  return mTimingSense;
}

// @brief "timing_type" を返す．
ClibTimingType
DotlibTiming::timing_type() const
{
  return mTimingType;
}

// @brief "when" を返す．
const DotlibNode*
DotlibTiming::when() const
{
  return mWhen;
}

// @brief "when_start" を返す．
const DotlibNode*
DotlibTiming::when_start() const
{
  return mWhenStart;
}

// @brief "when_end" を返す．
const DotlibNode*
DotlibTiming::when_end() const
{
  return mWhenEnd;
}

// @brief "fall_delay_intercept" を返す．
const DotlibNode*
DotlibTiming::fall_delay_intercept() const
{
  return mFallDelayIntercept;
}

// @brief "rise_delay_intercept" を返す．
const DotlibNode*
DotlibTiming::rise_delay_intercept() const
{
  return mRiseDelayIntercept;
}

// @brief "fall_pin_resistance" を返す．
const DotlibNode*
DotlibTiming::fall_pin_resistance() const
{
  return mFallPinResistance;
}

// @brief "rise_pin_resistance" を返す．
const DotlibNode*
DotlibTiming::rise_pin_resistance() const
{
  return mRisePinResistance;
}

// @brief "cell_degradation" を返す．
const DotlibNode*
DotlibTiming::cell_degradation() const
{
  return mClibDegradation;
}

// @brief "cell_fall" を返す．
const DotlibNode*
DotlibTiming::cell_fall() const
{
  return mClibFall;
}

// @brief "cell_rise" を返す．
const DotlibNode*
DotlibTiming::cell_rise() const
{
  return mClibRise;
}

// @brief "fall_constraint" を返す．
const DotlibNode*
DotlibTiming::fall_constraint() const
{
  return mFallConstraint;
}

// @brief "rise_constraint" を返す．
const DotlibNode*
DotlibTiming::rise_constraint() const
{
  return mRiseConstraint;
}

// @brief "fall_propagation" を返す．
const DotlibNode*
DotlibTiming::fall_propagation() const
{
  return mFallPropagation;
}

// @brief "rise_propagation" を返す．
const DotlibNode*
DotlibTiming::rise_propagation() const
{
  return mRisePropagation;
}

// @brief "fall_transition" を返す．
const DotlibNode*
DotlibTiming::fall_transition() const
{
  return mFallTransition;
}

// @brief "rise_transition" を返す．
const DotlibNode*
DotlibTiming::rise_transition() const
{
  return mRiseTransition;
}

// @brief "retaining_fall" を返す．
const DotlibNode*
DotlibTiming::retaining_fall() const
{
  return mRetainingFall;
}

// @brief "retaining_rise" を返す．
const DotlibNode*
DotlibTiming::retaining_rise() const
{
  return mRetainingRise;
}

// @brief "retain_fall_slew" を返す．
const DotlibNode*
DotlibTiming::retain_fall_slew() const
{
  return mRetainFallSlew;
}

// @brief "retain_rise_slew" を返す．
const DotlibNode*
DotlibTiming::retain_rise_slew() const
{
  return mRetainRiseSlew;
}

END_NAMESPACE_YM_DOTLIB
