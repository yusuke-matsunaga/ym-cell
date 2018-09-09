﻿
/// @file AstTiming.cc
/// @brief AstTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstTiming.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
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
AstTiming*
AstMgr::new_timing(const FileRegion& loc,
		   const AstString* name,
		   const AstString* related_pin,
		   const AstString* related_bus_pins,
		   const AstString* related_bus_equivalent,
		   const AstTimingSense* timing_sense,
		   const AstTimingType* timing_type,
		   const AstExpr* when,
		   const AstExpr* when_start,
		   const AstExpr* when_end,
		   const AstFloat* rise_resistance,
		   const AstFloat* fall_resistance,
		   const AstFloat* intrinsic_rise,
		   const AstFloat* intrinsic_fall,
		   const AstFloat* slope_rise,
		   const AstFloat* slope_fall,
		   const vector<const AstPieceWise*>& rise_delay_intercept,
		   const vector<const AstPieceWise*>& fall_delay_intercept,
		   const vector<const AstPieceWise*>& rise_pin_resistance,
		   const vector<const AstPieceWise*>& fall_pin_resistance,
		   const AstCellDegradation* cell_degradation,
		   const AstLut* cell_rise,
		   const AstLut* cell_fall,
		   const AstCCS* compact_ccs_rise,
		   const AstCCS* compact_ccs_fall,
		   const AstLut* rise_constraint,
		   const AstLut* fall_constraint,
		   const AstLut* rise_propagation,
		   const AstLut* fall_propagation,
		   const AstLut* rise_transition,
		   const AstLut* fall_transition,
		   const AstLut* retaining_rise,
		   const AstLut* retaining_fall,
		   const AstLut* retain_rise_slew,
		   const AstLut* retain_fall_slew)
{
  void* p = mAlloc.get_memory(sizeof(AstTiming));
  return new (p) AstTiming(loc, name, related_pin, related_bus_pins, related_bus_equivalent,
			   timing_sense, timing_type, when, when_start, when_end,
			   rise_resistance, fall_resistance, intrinsic_rise, intrinsic_fall,
			   slope_rise, slope_fall, rise_delay_intercept, fall_delay_intercept,
			   rise_pin_resistance, fall_pin_resistance, cell_degradation,
			   cell_rise, cell_fall, compact_ccs_rise, compact_ccs_rise,
			   rise_constraint, fall_constraint,
			   rise_propagation, fall_propagation, rise_transition, fall_transition,
			   retaining_rise, retaining_fall, retain_rise_slew, retain_fall_slew);
}


//////////////////////////////////////////////////////////////////////
// クラス AstTiming
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
AstTiming::AstTiming(const FileRegion& loc,
		     const AstString* name,
		     const AstString* related_pin,
		     const AstString* related_bus_pins,
		     const AstString* related_bus_equivalent,
		     const AstTimingSense* timing_sense,
		     const AstTimingType* timing_type,
		     const AstExpr* when,
		     const AstExpr* when_start,
		     const AstExpr* when_end,
		     const AstFloat* rise_resistance,
		     const AstFloat* fall_resistance,
		     const AstFloat* intrinsic_rise,
		     const AstFloat* intrinsic_fall,
		     const AstFloat* slope_rise,
		     const AstFloat* slope_fall,
		     const vector<const AstPieceWise*>& rise_delay_intercept,
		     const vector<const AstPieceWise*>& fall_delay_intercept,
		     const vector<const AstPieceWise*>& rise_pin_resistance,
		     const vector<const AstPieceWise*>& fall_pin_resistance,
		     const AstCellDegradation* cell_degradation,
		     const AstLut* cell_rise,
		     const AstLut* cell_fall,
		     const AstCCS* compact_ccs_rise,
		     const AstCCS* compact_ccs_fall,
		     const AstLut* rise_constraint,
		     const AstLut* fall_constraint,
		     const AstLut* rise_propagation,
		     const AstLut* fall_propagation,
		     const AstLut* rise_transition,
		     const AstLut* fall_transition,
		     const AstLut* retaining_rise,
		     const AstLut* retaining_fall,
		     const AstLut* retain_rise_slew,
		     const AstLut* retain_fall_slew) :
  AstNode(loc),
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
  mCompactCCSRise(compact_ccs_rise),
  mCompactCCSFall(compact_ccs_fall),
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
AstTiming::~AstTiming()
{
}

#if 0
// @brief 内容をセットする．
bool
AstTiming::set_data(const AstNode* node)
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
  AstAttrMap attr_map(node->attr_top());

  // 'related_pin' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RELATED_pin, mRelatedPin) ) {
    return false;
  }

  // 'related_bus_pins' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RELATED_bus_pinS, mRelatedBusPins) ) {
    return false;
  }

  // 'related_bus_equivalent' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RELATED_bus_EQUIVALENT, mRelatedBusEquivalent) ) {
    return false;
  }

  // 'timing_sense' を取り出す．
  const AstNode* ts_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_timing_sense, ts_node) ) {
    return false;
  }
  if ( ts_node == nullptr ) {
    mTimingSense = kClibNonUnate;
  }
  else {
    ASSERT_COND( ts_node->type() == AstNode::kTimingSense );
    mTimingSense = ts_node->timing_sense();
  }

  // 'timing_type' を取り出す．
  const AstNode* tt_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_timing_type, tt_node) ) {
    return false;
  }
  if ( tt_node == nullptr ) {
    mTimingType = kClibTimingCombinational;
  }
  else {
    ASSERT_COND( tt_node->type() == AstNode::kTimingType );
    mTimingType = tt_node->timing_type();
  }

  // 'when' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_when, mWhen) ) {
    return false;
  }

  // 'when_start' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_when_start, mWhenStart) ) {
    return false;
  }

  // 'when_end' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_when_end, mWhenEnd) ) {
    return false;
  }

  // 'rise_resistance' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_resistance, mRiseResistance) ) {
    return false;
  }

  // 'fall_resistance' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_fall_resistance, mFallResistance) ) {
    return false;
  }

  // 'intrinsic_rise' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_intrinsic_rise, mIntrinsicRise) ) {
    return false;
  }

  // 'intrinsic_fall' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_intrinsic_fall, mIntrinsicFall) ) {
    return false;
  }

  // 'slope_rise' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_slope_rise, mSlopeRise) ) {
    return false;
  }

  // 'slope_fall' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_slope_fall, mSlopeFall) ) {
    return false;
  }

  // 'rise_delay_intercept' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_rise_delay_intercept, mRiseDelayIntercept) ) {
    return false;
  }

  // 'fall_delay_intercept' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_fall_delay_intercept, mFallDelayIntercept) ) {
    return false;
  }

  // 'rise_pin_resistance' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_pin_resistance, mRisePinResistance) ) {
    return false;
  }

  // 'fall_pin_resistance' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_fall_pin_resistance, mFallPinResistance) ) {
    return false;
  }

  // 'cell_degradation' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_cell_degradation, mClibDegradation) ) {
    return false;
  }

  // 'cell_rise' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_cell_rise, mClibRise) ) {
    return false;
  }

  // 'cell_fall' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_cell_fall, mClibFall) ) {
    return false;
  }

  // 'rise_constraint' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_rise_constraint, mRiseConstraint) ) {
    return false;
  }

  // 'fall_constraint' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_fall_constraint, mFallConstraint) ) {
    return false;
  }

  // 'rise_propagation' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_rise_propagation, mRisePropagation) ) {
    return false;
  }

  // 'fall_propagation' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_fall_propagation, mFallPropagation) ) {
    return false;
  }

  // 'rise_transition' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_rise_transition, mRiseTransition) ) {
    return false;
  }

  // 'fall_transition' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_fall_transition, mFallTransition) ) {
    return false;
  }

  // 'retaining_rise' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_retaining_rise, mRetainingRise) ) {
    return false;
  }

  // 'retaining_fall' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_retaining_fall, mRetainingFall) ) {
    return false;
  }

  // 'retain_rise_slew' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_retain_rise_slew, mRetainRiseSlew) ) {
    return false;
  }

  // 'retain_fall_slew' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_retain_fall_slew, mRetainFallSlew) ) {
    return false;
  }

  return true;
}
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTiming::dump(ostream& s,
		   int indent) const
{
#warning"TODO: 未実装"
}

END_NAMESPACE_YM_DOTLIB
