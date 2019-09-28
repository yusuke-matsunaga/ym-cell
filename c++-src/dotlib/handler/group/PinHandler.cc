
/// @file PinHandler.cc
/// @brief PinHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/PinHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス PinHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PinHandler::PinHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::bit_width,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_int(mBitWidth, attr_type, attr_loc); });
  reg_func(AttrType::capacitance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mCapacitance, attr_type, attr_loc); });
  reg_func(AttrType::clock,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mClock, attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_clock_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mClockGateClockPin, attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_enable_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mClockGateEnablePin, attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_test_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mClockGateTestPin, attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_obs_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mClockGateObsPin, attr_type, attr_loc); });
  reg_func(AttrType::clock_gate_out_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mClockGateOutPin, attr_type, attr_loc); });
  reg_func(AttrType::complementary_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mComplementaryPin, attr_type, attr_loc); });
  reg_func(AttrType::connection_class,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mConnectionClass, attr_type, attr_loc); });
  reg_func(AttrType::direction,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_direction(mDirection, attr_type, attr_loc); });
  reg_func(AttrType::dont_fault,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mDontFault, attr_type, attr_loc); });
  reg_func(AttrType::drive_current,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mDriveCurrent, attr_type, attr_loc); });
  reg_func(AttrType::driver_type,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mDriverType, attr_type, attr_loc); });
  reg_func(AttrType::fall_capacitance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mFallCapacitance, attr_type, attr_loc); });
  reg_func(AttrType::fall_current_slope_after_threshold,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mFallCurrentSlopeAfterThreshold, attr_type, attr_loc); });
  reg_func(AttrType::fall_current_slope_before_threshold,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mFallCurrentSlopeBeforeThreshold, attr_type, attr_loc); });
  reg_func(AttrType::fall_time_after_threshold,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mFallTimeAfterThreshold, attr_type, attr_loc); });
  reg_func(AttrType::fall_time_before_threshold,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mFallTimeBeforeThreshold, attr_type, attr_loc); });
  reg_func(AttrType::fanout_load,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mFanoutLoad, attr_type, attr_loc); });
  reg_func(AttrType::fault_model,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mFaultModel, attr_type, attr_loc); });
  reg_func(AttrType::function,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_function(mFunction, attr_type, attr_loc); });
  reg_func(AttrType::has_builtin_pad,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mHasBuiltinPad, attr_type, attr_loc); });
  reg_func(AttrType::hysteresis,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mHysteresis, attr_type, attr_loc); });
  reg_func(AttrType::input_map,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mInputMap, attr_type, attr_loc); });
  reg_func(AttrType::input_signal_level,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mInputSignalLevel, attr_type, attr_loc); });
  reg_func(AttrType::input_threshold_pct_fall,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mInputThresholdPctFall, attr_type, attr_loc); });
  reg_func(AttrType::input_threshold_pct_rise,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mInputThresholdPctRise, attr_type, attr_loc); });
  reg_func(AttrType::input_voltage,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mInputVoltage, attr_type, attr_loc); });
  reg_func(AttrType::internal_node,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mInternalNode, attr_type, attr_loc); });
  reg_func(AttrType::inverted_output,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mInvertedOutput, attr_type, attr_loc); });
  reg_func(AttrType::is_pad,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mIsPad, attr_type, attr_loc); });
  reg_func(AttrType::isolation_cell_enable_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mIsolationCellEnablePin, attr_type, attr_loc); });
  reg_func(AttrType::level_shifter_enable_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mLevelShifterEnablePin, attr_type, attr_loc); });
  reg_func(AttrType::map_to_logic,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mMapToLogic, attr_type, attr_loc); });
  reg_func(AttrType::max_capacitance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMaxCapacitance, attr_type, attr_loc); });
  reg_func(AttrType::max_fanout,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMaxFanout, attr_type, attr_loc); });
  reg_func(AttrType::max_input_noise_width,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMaxInputNoiseWidth, attr_type, attr_loc); });
  reg_func(AttrType::max_transition,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMaxTransition, attr_type, attr_loc); });
  reg_func(AttrType::min_capacitance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMinCapacitance, attr_type, attr_loc); });
  reg_func(AttrType::min_fanout,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMinFanout, attr_type, attr_loc); });
  reg_func(AttrType::min_input_noise_width,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMinInputNoiseWidth, attr_type, attr_loc); });
  reg_func(AttrType::min_period,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMinPeriod, attr_type, attr_loc); });
  reg_func(AttrType::min_pulse_width_high,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMinPulseWidthHigh, attr_type, attr_loc); });
  reg_func(AttrType::min_transition,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mMinTransition, attr_type, attr_loc); });
  reg_func(AttrType::multicell_pad_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mMulticellPadPin, attr_type, attr_loc); });
  reg_func(AttrType::nextstate_type,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mNextstateType, attr_type, attr_loc); });
  reg_func(AttrType::output_signal_level,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mOutputSignalLevel, attr_type, attr_loc); });
  reg_func(AttrType::output_voltage,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mOutputVoltage, attr_type, attr_loc); });
  reg_func(AttrType::pg_function,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mPgFunction, attr_type, attr_loc); });
  reg_func(AttrType::pin_func_type,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mPinFuncType, attr_type, attr_loc); });
  reg_func(AttrType::power_down_function,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mPowerDownFunction, attr_type, attr_loc); });
  reg_func(AttrType::prefer_tied,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mPreferTied, attr_type, attr_loc); });
  reg_func(AttrType::primary_output,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mPrimaryOutput, attr_type, attr_loc); });
  reg_func(AttrType::pulling_current,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mPullingCurrent, attr_type, attr_loc); });
  reg_func(AttrType::pulling_resistance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mPullingResistance, attr_type, attr_loc); });
  reg_func(AttrType::pulse_clock,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mPulseClock, attr_type, attr_loc); });
  reg_func(AttrType::related_ground_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mRelatedGroundPin, attr_type, attr_loc); });
  reg_func(AttrType::related_power_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mRelatedPowerPin, attr_type, attr_loc); });
  reg_func(AttrType::rise_capacitance,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mRiseCapacitance, attr_type, attr_loc); });
  reg_func(AttrType::rise_current_slope_after_threshold,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mRiseCurrentSlopeAfterThreshold, attr_type, attr_loc); });
  reg_func(AttrType::rise_current_slope_before_threshold,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mRiseCurrentSlopeBeforeThreshold, attr_type, attr_loc); });
  reg_func(AttrType::rise_time_after_threshold,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mRiseTimeAfterThreshold, attr_type, attr_loc); });
  reg_func(AttrType::rise_time_before_threshold,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mRiseTimeBeforeThreshold, attr_type, attr_loc); });
  reg_func(AttrType::signal_type,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mSignalType, attr_type, attr_loc); });
  reg_func(AttrType::slew_control,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mSlewControl, attr_type, attr_loc); });
  reg_func(AttrType::slew_lower_threshold_pct_fall,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mSlewLowerThresholdPctFall, attr_type, attr_loc); });
  reg_func(AttrType::slew_lower_threshold_pct_rise,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mSlewLowerThresholdPctRise, attr_type, attr_loc); });
  reg_func(AttrType::slew_upper_threshold_pct_fall,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mSlewUpperThresholdPctFall, attr_type, attr_loc); });
  reg_func(AttrType::slew_upper_threshold_pct_rise,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float(mSlewUpperThresholdPctRise, attr_type, attr_loc); });
  reg_func(AttrType::state_function,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mStateFunction, attr_type, attr_loc); });
  reg_func(AttrType::std_cell_main_rail,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mStdCellMainRail, attr_type, attr_loc); });
  reg_func(AttrType::switch_function,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mSwitchFunction, attr_type, attr_loc); });
  reg_func(AttrType::switch_pin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mSwitchPin, attr_type, attr_loc); });
  reg_func(AttrType::test_output_only,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_bool(mTestOutputOnly, attr_type, attr_loc); });
  reg_func(AttrType::three_state,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mThreeState, attr_type, attr_loc); });
  reg_func(AttrType::vhdl_name,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_string(mVhdlName, attr_type, attr_loc); });
  reg_func(AttrType::x_function,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mXFunction, attr_type, attr_loc); });

  reg_func(AttrType::fall_capacitance_range,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_float(mFallCapacitanceRange, attr_type, attr_loc); });
  reg_func(AttrType::rise_capacitance_range,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_float_float(mRiseCapacitanceRange, attr_type, attr_loc); });

  // power_gating_pin (string, int)

  // electromigration

  // hyperbolic_noise_above_high

  // hyperbolic_noise_below_low

  // hyperbolic_noise_high

  // hyperbolic_noise_low

  // internal_power

  // max_trans

  // min_pulse_width

  // minimum_period

  // tlatch

  reg_func(AttrType::timing,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_timing(mTimingList, attr_type, attr_loc); });
}

// @brief デストラクタ
PinHandler::~PinHandler()
{
}

// @brief グループ記述の始まり
void
PinHandler::begin_group()
{
  mBitWidth = nullptr;
  mCapacitance = nullptr;
  mClock = nullptr;
  mClockGateClockPin = nullptr;
  mClockGateEnablePin = nullptr;
  mClockGateTestPin = nullptr;
  mClockGateObsPin = nullptr;
  mClockGateOutPin = nullptr;
  mComplementaryPin = nullptr;
  mConnectionClass = nullptr;
  mDirection = nullptr;
  mDontFault = nullptr;
  mDriveCurrent = nullptr;
  mDriverType = nullptr;
  mFallCapacitance = nullptr;
  mFallCurrentSlopeAfterThreshold = nullptr;
  mFallCurrentSlopeBeforeThreshold = nullptr;
  mFallTimeAfterThreshold = nullptr;
  mFallTimeBeforeThreshold = nullptr;
  mFanoutLoad = nullptr;
  mFaultModel = nullptr;
  mFunction = nullptr;
  mHasBuiltinPad = nullptr;
  mHysteresis = nullptr;
  mInputMap = nullptr;
  mInputSignalLevel = nullptr;
  mInputThresholdPctFall = nullptr;
  mInputThresholdPctRise = nullptr;
  mInputVoltage = nullptr;
  mInternalNode = nullptr;
  mInvertedOutput = nullptr;
  mIsPad = nullptr;
  mIsolationCellEnablePin = nullptr;
  mLevelShifterEnablePin = nullptr;
  mMapToLogic = nullptr;
  mMaxCapacitance = nullptr;
  mMaxFanout = nullptr;
  mMaxInputNoiseWidth = nullptr;
  mMaxTransition = nullptr;
  mMinCapacitance = nullptr;
  mMinFanout = nullptr;
  mMinInputNoiseWidth = nullptr;
  mMinPeriod = nullptr;
  mMinPulseWidthHigh = nullptr;
  mMinPulseWidthLow = nullptr;
  mMinTransition = nullptr;
  mMulticellPadPin = nullptr;
  mNextstateType = nullptr;
  mOutputSignalLevel = nullptr;
  mOutputVoltage = nullptr;
  mPgFunction = nullptr;
  mPinFuncType = nullptr;
  mPowerDownFunction = nullptr;
  mPreferTied = nullptr;
  mPrimaryOutput = nullptr;
  mPullingCurrent = nullptr;
  mPullingResistance = nullptr;
  mPulseClock = nullptr;
  mRelatedGroundPin = nullptr;
  mRelatedPowerPin = nullptr;
  mRiseCapacitance = nullptr;
  mRiseCurrentSlopeAfterThreshold = nullptr;
  mRiseCurrentSlopeBeforeThreshold = nullptr;
  mRiseTimeAfterThreshold = nullptr;
  mRiseTimeBeforeThreshold = nullptr;
  mSignalType = nullptr;
  mSlewControl = nullptr;
  mSlewLowerThresholdPctFall = nullptr;
  mSlewLowerThresholdPctRise = nullptr;
  mSlewUpperThresholdPctFall = nullptr;
  mSlewUpperThresholdPctRise = nullptr;
  mStateFunction = nullptr;
  mStdCellMainRail = nullptr;
  mSwitchFunction = nullptr;
  mSwitchPin = nullptr;
  mTestOutputOnly = nullptr;
  mThreeState = nullptr;
  mVhdlName = nullptr;
  mXFunction = nullptr;

  mFallCapacitanceRange = nullptr;
  mRiseCapacitanceRange = nullptr;
  mPowerGatingPinString = nullptr;
  mPowerGatingPinInt = nullptr;

  mTimingList.clear();
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
PinHandler::end_group()
{
  // 必要な属性がちゃんと定義されているかチェック
#warning "TODO:必要な属性がちゃんと定義されているかチェック"
  return true;
}

END_NAMESPACE_YM_DOTLIB
