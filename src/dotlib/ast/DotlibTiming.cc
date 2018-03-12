
/// @file DotlibTiming.cc
/// @brief DotlibTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibTiming.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibTiming
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] related_pin
// @param[in] related_bus_pins
// @param[in] related_bus_equivalent
// @param[in] timing_sense
// @param[in] timing_type
// @param[in] when
// @param[in] when_start
// @param[in] when_end
// @param[in] rise_resistance
// @param[in] fall_resistance
// @param[in] intrinsic_rise
// @param[in] intrinsic_fall
// @param[in] slope_rise
// @param[in] slope_fall
// @param[in] rise_delay_intercept
// @param[in] fall_delay_intercept
// @param[in] rise_pin_resistance
// @param[in] fall_pin_resistance
// @param[in] cell_degradation
// @param[in] cell_rise
// @param[in] cell_fall
// @param[in] rise_constraint
// @param[in] fall_constraint
// @param[in] rise_propagation
// @param[in] fall_propagation
// @param[in] rise_transition
// @param[in] fall_transition
// @param[in] retaing_rise
// @param[in] retaing_fall
// @param[in] retain_rise_slew
// @param[in] retainfall_slew
DotlibTiming::DotlibTiming(const FileRegion& loc,
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
			   const DotlibList* rise_delay_intercept,
			   const DotlibList* fall_delay_intercept,
			   const DotlibList* rise_pin_resistance,
			   const DotlibList* fall_pin_resistance,
			   const DotlibFloat* cell_degradation,
			   const DotlibLut* cell_rise,
			   const DotlibLut* cell_fall,
			   const DotlibLut* rise_constraint,
			   const DotlibLut* fall_constraint,
			   const DotlibLut* rise_propagation,
			   const DotlibLut* fall_propagation,
			   const DotlibLut* rise_transition,
			   const DotlibLut* fall_transition,
			   const DotlibFloat* retaining_rise,
			   const DotlibFloat* retaining_fall,
			   const DotlibFloat* retain_rise_slew,
			   const DotlibFloat* retain_fall_slew) :
  DotlibNode(loc),
  mRelatedPin(related_pin),
  mRelatedBusPins(related_bus_pins),
  mRelatedBusEquivalent(related_bus_equivalent),
  mTimingSense(timing_sense),
  mTimingType(timing_type),
  mWhen(when),
  mWhenStart(when_start),
  mWhenEnd(when_end),
  mRiseResistance(rise_resistance),
  mFallResistance(fall_resistance),
  mIntrinsicRise(intrinsic_rise),
  mIntrinsicFall(intrinsic_fall),
  mSlopeRise(slope_rise),
  mSlopeFall(slope_fall),
  mRiseDelayIntercept(rise_delay_intercept),
  mFallDelayIntercept(fall_delay_intercept),
  mCellDegradation(cell_degradation),
  mCellRise(cell_rise),
  mCellFall(cell_fall),
  mRiseConstraint(rise_constraint),
  mFallConstraint(fall_constraint),
  mRisePropagation(rise_propagation),
  mFallPropagation(fall_propagation),
  mRiseTransition(rise_transition),
  mFallTransition(fall_transition),
  mRetainingRise(retaining_rise),
  mRetainingFall(retaining_fall),
  mRetainRiseSlew(retain_rise_slew),
  mRetainFallSlew(retain_fall_slew)
{
}

// @brief デストラクタ
DotlibTiming::~DotlibTiming()
{
}

#if 0
// @brief 内容をセットする．
bool
DotlibTiming::set_data(const DotlibNode* node)
{
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

  // 属性を attr_map に登録する．
  DotlibAttrMap attr_map(node->attr_top());

  // 'related_pin' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RELATED_PIN, mRelatedPin) ) {
    return false;
  }

  // 'related_bus_pins' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RELATED_BUS_PINS, mRelatedBusPins) ) {
    return false;
  }

  // 'related_bus_equivalent' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RELATED_BUS_EQUIVALENT, mRelatedBusEquivalent) ) {
    return false;
  }

  // 'timing_sense' を取り出す．
  const DotlibNode* ts_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_TIMING_SENSE, ts_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_TIMING_TYPE, tt_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_WHEN, mWhen) ) {
    return false;
  }

  // 'when_start' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_WHEN_START, mWhenStart) ) {
    return false;
  }

  // 'when_end' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_WHEN_END, mWhenEnd) ) {
    return false;
  }

  // 'rise_resistance' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_RESISTANCE, mRiseResistance) ) {
    return false;
  }

  // 'fall_resistance' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_FALL_RESISTANCE, mFallResistance) ) {
    return false;
  }

  // 'intrinsic_rise' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_INTRINSIC_RISE, mIntrinsicRise) ) {
    return false;
  }

  // 'intrinsic_fall' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_INTRINSIC_FALL, mIntrinsicFall) ) {
    return false;
  }

  // 'slope_rise' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_SLOPE_RISE, mSlopeRise) ) {
    return false;
  }

  // 'slope_fall' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_SLOPE_FALL, mSlopeFall) ) {
    return false;
  }

  // 'rise_delay_intercept' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_DELAY_INTERCEPT, mRiseDelayIntercept) ) {
    return false;
  }

  // 'fall_delay_intercept' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_FALL_DELAY_INTERCEPT, mFallDelayIntercept) ) {
    return false;
  }

  // 'rise_pin_resistance' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_PIN_RESISTANCE, mRisePinResistance) ) {
    return false;
  }

  // 'fall_pin_resistance' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_FALL_PIN_RESISTANCE, mFallPinResistance) ) {
    return false;
  }

  // 'cell_degradation' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_CELL_DEGRADATION, mClibDegradation) ) {
    return false;
  }

  // 'cell_rise' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_CELL_RISE, mClibRise) ) {
    return false;
  }

  // 'cell_fall' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_CELL_FALL, mClibFall) ) {
    return false;
  }

  // 'rise_constraint' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_CONSTRAINT, mRiseConstraint) ) {
    return false;
  }

  // 'fall_constraint' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_FALL_CONSTRAINT, mFallConstraint) ) {
    return false;
  }

  // 'rise_propagation' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_PROPAGATION, mRisePropagation) ) {
    return false;
  }

  // 'fall_propagation' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_FALL_PROPAGATION, mFallPropagation) ) {
    return false;
  }

  // 'rise_transition' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_TRANSITION, mRiseTransition) ) {
    return false;
  }

  // 'fall_transition' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_FALL_TRANSITION, mFallTransition) ) {
    return false;
  }

  // 'retaining_rise' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RETAINING_RISE, mRetainingRise) ) {
    return false;
  }

  // 'retaining_fall' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RETAINING_FALL, mRetainingFall) ) {
    return false;
  }

  // 'retain_rise_slew' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RETAIN_RISE_SLEW, mRetainRiseSlew) ) {
    return false;
  }

  // 'retain_fall_slew' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RETAIN_FALL_SLEW, mRetainFallSlew) ) {
    return false;
  }

  return true;
}
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibTiming::dump(ostream& s,
		   int indent) const
{
#warning"TODO: 未実装"
}

END_NAMESPACE_YM_DOTLIB
