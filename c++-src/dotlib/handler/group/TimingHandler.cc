
/// @file TimingHandler.cc
/// @brief TimingHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/TimingHandler.h"
#if 0
#include "dotlib/FloatHandler.h"
#include "dotlib/FuncHandler.h"
#include "dotlib/PieceWiseHandler.h"
#include "dotlib/TableHandler.h"
#include "dotlib/StringHandler.h"
#include "dotlib/TimingSenseHandler.h"
#include "dotlib/TimingTypeHandler.h"
#endif
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TimingHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingHandler::TimingHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::clock_gating_flag,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mClockGatingFlag, attr_type, attr_loc); });
  reg_func(AttrType::default_timing,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mDefaultTiming, attr_type, attr_loc); });
  reg_func(AttrType::fall_resistance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mFallResistance, attr_type, attr_loc); });
  reg_func(AttrType::fpga_arc_condition,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_function(mFpgaArcCondition, attr_type, attr_loc); });
  reg_func(AttrType::fpga_domain_style,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mFpgaDomainStyle, attr_type, attr_loc); });
  reg_func(AttrType::interdependence_id,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_int(mInterdependenceId, attr_type, attr_loc); });
  reg_func(AttrType::intrinsic_fall,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mIntrinsicFall, attr_type, attr_loc); });
  reg_func(AttrType::intrinsic_rise,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mIntrinsicRise, attr_type, attr_loc); });
  reg_func(AttrType::related_bus_equivalent,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mRelatedBusEquivalent, attr_type, attr_loc); });
  reg_func(AttrType::related_bus_pins,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mRelatedBusPins, attr_type, attr_loc); });
  reg_func(AttrType::related_output_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mRelatedOutputPin, attr_type, attr_loc); });
  reg_func(AttrType::related_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mRelatedPin, attr_type, attr_loc); });
  reg_func(AttrType::rise_resistance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mRiseResistance, attr_type, attr_loc); });
  // sdf_cond
  // sdf_cond_end
  // sdf_cond_start
  // sdf_edges
  reg_func(AttrType::slope_fall,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mSlopeFall, attr_type, attr_loc); });
  reg_func(AttrType::slope_rise,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mSlopeRise, attr_type, attr_loc); });
  reg_func(AttrType::steady_state_resistance_above_high,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mSteadyStateResistanceAboveHigh, attr_type, attr_loc); });
  reg_func(AttrType::steady_state_resistance_below_low,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mSteadyStateResistanceBelowLow, attr_type, attr_loc); });
  reg_func(AttrType::tied_off,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mTiedOff, attr_type, attr_loc); });
  reg_func(AttrType::timing_sense,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_timing_sense(mTimingSense, attr_type, attr_loc); });
  reg_func(AttrType::timing_type,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_timing_type(mTimingType, attr_type, attr_loc); });
  reg_func(AttrType::when,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_function(mWhen, attr_type, attr_loc); });
  reg_func(AttrType::when_end,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_function(mWhenEnd, attr_type, attr_loc); });
  reg_func(AttrType::when_start,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_function(mWhenStart, attr_type, attr_loc); });

  reg_func(AttrType::fall_delay_intercept,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_int_float(mFallDelayIntercept, attr_type, attr_loc); });
  reg_func(AttrType::fall_pin_resistance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_int_float(mFallPinResistance, attr_type, attr_loc); });
  reg_func(AttrType::rise_delay_intercept,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_int_float(mRiseDelayIntercept, attr_type, attr_loc); });
  reg_func(AttrType::rise_pin_resistance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_int_float(mRisePinResistance, attr_type, attr_loc); });

  // cell_degradation

  reg_func(AttrType::cell_fall,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mCellFall, attr_type, attr_loc); });
  reg_func(AttrType::cell_rise,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mCellRise, attr_type, attr_loc); });
  reg_func(AttrType::fall_constraint,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mFallConstraint, attr_type, attr_loc); });
  reg_func(AttrType::fall_propagation,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mFallPropagation, attr_type, attr_loc); });
  reg_func(AttrType::fall_transition,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mFallTransition, attr_type, attr_loc); });

  // noise_immunity_above_high
  // noise_immunity_below_low
  // noise_immunity_high
  // noise_immunity_low

  reg_func(AttrType::output_current_fall,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mOutputCurrentFall, attr_type, attr_loc); });
  reg_func(AttrType::output_current_rise,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mOutputCurrentRise, attr_type, attr_loc); });

  // propagated_noise_height_above_high
  // propagated_noise_height_below_low
  // propagated_noise_height_high
  // propagated_noise_height_low
  // propagated_noise_peak_time_ratio_above_high
  // propagated_noise_peak_time_ratio_below_low
  // propagated_noise_peak_time_ratio_high
  // propagated_noise_peak_time_ratio_low
  // propagated_noise_width_above_high
  // propagated_noise_width_below_low
  // propagated_noise_width_high
  // propagated_noise_width_low
  // receiver_capacitance1_fall
  // receiver_capacitance1_rise
  // receiver_capacitance2_fall
  // receiver_capacitance2_rise
  // retaining_fall
  // retaining_rise
  // retain_fall_slew
  // retain_rise_slew

  reg_func(AttrType::rise_constraint,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mRiseConstraint, attr_type, attr_loc); });
  reg_func(AttrType::rise_propagation,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mRisePropagation, attr_type, attr_loc); });
  reg_func(AttrType::rise_transition,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_table(mRiseTransition, attr_type, attr_loc); });

  // steady_state_current_high
  // steady_state_current_low
  // steady_state_current_tristate
}

// @brief デストラクタ
TimingHandler::~TimingHandler()
{
}

// @brief グループ記述の始まり
void
TimingHandler::begin_group()
{
  mClockGatingFlag = nullptr;
  mDefaultTiming = nullptr;
  mFallResistance = nullptr;
  mFpgaArcCondition = nullptr;
  mFpgaDomainStyle = nullptr;
  mInterdependenceId = nullptr;
  mIntrinsicFall = nullptr;
  mIntrinsicRise = nullptr;
  mRelatedBusEquivalent = nullptr;
  mRelatedBusPins = nullptr;
  mRelatedOutputPin = nullptr;
  mRelatedPin = nullptr;
  mRiseResistance = nullptr;
  mSdfCond = nullptr;
  mSdfCondEnd = nullptr;
  mSdfCondStart = nullptr;
  mSdfEdges = nullptr;
  mSlopeFall = nullptr;
  mSlopeRise = nullptr;
  mSteadyStateResistanceAboveHigh = nullptr;
  mSteadyStateResistanceBelowLow = nullptr;
  mSteadyStateResistanceHigh = nullptr;
  mSteadyStateResistanceLow = nullptr;
  mTiedOff = nullptr;
  mTimingSense = nullptr;
  mTimingType = nullptr;
  mWhen = nullptr;
  mWhenEnd = nullptr;
  mWhenStart = nullptr;

  mFallDelayIntercept.clear();
  mFallPinResistance.clear();

  mModeName = nullptr;
  mModeValue = nullptr;

  mRiseDelayIntercept.clear();
  mRisePinResistance.clear();

  mCellDegradation = nullptr;
  mCellFall = nullptr;
  mCellRise = nullptr;
  mCompactCCSFall = nullptr;
  mCompactCCSRise = nullptr;
  mFallConstraint = nullptr;
  mFallTransition = nullptr;
  mRiseConstraint = nullptr;
  mRiseTransition = nullptr;

  // mNoiseImmunityAbove
  // mNoiseImmunityBelowLow
  // mNoiseImmunityHigh
  // mNoiseImmunityLow
  // mPropagatedNoiseHeightAboveHigh
  // mPropagatedNoiseHeightBelowLow
  // mPropagatedNoiseHeightHigh
  // mPropagatedNoiseHeightLow
  // mPropagatedNoisePeakTimeRatioAboveHigh
  // mPropagatedNoisePeakTimeRatioBelowLow
  // mPropagatedNoisePeakTimeRatioHigh
  // mPropagatedNoisePeakTimeRatioLow
  // mPropagatedNoiseWidthHigh
  // mPropagatedNoiseWidthLow

  mRetainingRise = nullptr;
  mRetainingFall = nullptr;
  mRetainRiseSlew = nullptr;
  mRetainFallSlew = nullptr;

  // mSteadyStateCurrentHigh
  // mSteadyStateCurrentLow
  // mSteadyStateCurrentTristate
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
TimingHandler::end_group()
{
#if 0
  mValue = mgr().new_timing(group_loc,
			    mName,
			    mRelatedPin,
			    mRelatedBusPins,
			    mRelatedBusEquivalent,
			    mTimingSense,
			    mTimingType,
			    mWhen,
			    mWhenStart,
			    mWhenEnd,
			    mRiseResistance,
			    mFallResistance,
			    mIntrinsicRise,
			    mIntrinsicFall,
			    mSlopeRise,
			    mSlopeFall,
			    mRiseDelayIntercept,
			    mFallDelayIntercept,
			    mRisePinResistance,
			    mFallPinResistance,
			    mCellDegradation,
			    mCellRise,
			    mCellFall,
			    mCompactCCSRise,
			    mCompactCCSFall,
			    mRiseConstraint,
			    mFallConstraint,
			    mRisePropagation,
			    mFallPropagation,
			    mRiseTransition,
			    mFallTransition,
			    mRetainingRise,
			    mRetainingFall,
			    mRetainRiseSlew,
			    mRetainFallSlew);
#endif
  return true;
}

END_NAMESPACE_YM_DOTLIB
