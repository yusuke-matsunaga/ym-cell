
/// @file TimingHandler.cc
/// @brief TimingHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "TimingHandler.h"
#include "TableHandler.h"
#include "dotlib/AstTiming.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TimingHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingHandler::TimingHandler(DotlibParser& parser) :
  EmptyGroupHandler(parser),
  mRelatedPinEquivalent(parser),
  mRelatedBusPins(parser),
  mRelatedOutputPin(parser),
  mRelatedPin(parser),
  mTimingSense(parser),
  mTimingType(parser),
  mRiseResistance(parser),
  mFallResistance(parser),
  mIntrinsicRise(parser),
  mIntrinsicFall(parser),
  mSlopeRise(parser),
  mSlopeFall(parser),
  mWhen(parser),
  mWhenStart(parser),
  mWhenEnd(parser),
  mRiseDelayIntercept(parser),
  mFallDelayIntercept(parser),
  mRisePinResistance(parser),
  mFallPinResistance(parser),
  mCellRise(parser),
  mCellFall(parser),
  mRiseConstraint(parser),
  mFallConstraint(parser),
  mRiseTransition(parser),
  mFallTransition(parser)
{
#if 0
  reg_handler(AttrType::RELATED_bus_EQUIVALENT,                      str_simple);
  reg_handler(AttrType::RELATED_bus_pinS,                            str_simple);
  reg_handler(AttrType::RELATED_OUTPUT_pin,                          str_simple);
  reg_handler(AttrType::RELATED_pin,                                 str_simple);

  reg_handler(AttrType::timing_sense,                                ts_handler);
  reg_handler(AttrType::timing_type,                                 tt_handler);

  reg_handler(AttrType::edge_rate_sensitivity_f0,                    simple);
  reg_handler(AttrType::edge_rate_sensitivity_f1,                    simple);
  reg_handler(AttrType::edge_rate_sensitivity_r0,                    simple);
  reg_handler(AttrType::edge_rate_sensitivity_r1,                    simple);

  reg_handler(AttrType::RISE_resistance,                             flt_simple);
  reg_handler(AttrType::fall_resistance,                             flt_simple);
  reg_handler(AttrType::intrinsic_rise,                              flt_simple);
  reg_handler(AttrType::intrinsic_fall,                              flt_simple);

  reg_handler(AttrType::sdf_cond,                                    simple);
  reg_handler(AttrType::sdf_cond_end,                                simple);
  reg_handler(AttrType::sdf_cond_start,                              simple);
  reg_handler(AttrType::sdf_edges,                                   simple);

  reg_handler(AttrType::slope_fall,                                  flt_simple);
  reg_handler(AttrType::slope_rise,                                  flt_simple);

  reg_handler(AttrType::when,                                        func_handler);
  reg_handler(AttrType::when_end,                                    func_handler);
  reg_handler(AttrType::when_start,                                  func_handler);

  // complex attribute
  reg_handler(AttrType::rise_delay_intercept,                        pw_complex);
  reg_handler(AttrType::fall_delay_intercept,                        pw_complex);
  reg_handler(AttrType::RISE_pin_resistance,                         pw_complex);
  reg_handler(AttrType::fall_pin_resistance,                         pw_complex);
  reg_handler(AttrType::orders,                                      complex);
  reg_handler(AttrType::coefs,                                       complex);

  // group statements
  reg_handler(AttrType::cell_degradation,                            g_group);

  reg_handler(AttrType::cell_rise,                                   table_handler);
  reg_handler(AttrType::cell_fall,                                   table_handler);

  reg_handler(AttrType::rise_constraint,                             table_handler);
  reg_handler(AttrType::fall_constraint,                             table_handler);

  reg_handler(AttrType::rise_propagation,                            table_handler);
  reg_handler(AttrType::fall_propagation,                            table_handler);

  reg_handler(AttrType::rise_transition,                             table_handler);
  reg_handler(AttrType::fall_transition,                             table_handler);

  reg_handler(AttrType::noise_immunity_above_high,                   g_group);
  reg_handler(AttrType::noise_immunity_below_low,                    g_group);
  reg_handler(AttrType::noise_immunity_high,                         g_group);
  reg_handler(AttrType::noise_immunity_low,                          g_group);

  reg_handler(AttrType::propagated_noise_height_above_high,	        g_group);
  reg_handler(AttrType::propagated_noise_height_below_low,	        g_group);
  reg_handler(AttrType::propagated_noise_height_high,	        g_group);
  reg_handler(AttrType::propagated_noise_height_low,		        g_group);
  reg_handler(AttrType::propagated_noise_peak_time_ratio_above_high, g_group);
  reg_handler(AttrType::propagated_noise_peak_time_ratio_below_low,  g_group);
  reg_handler(AttrType::propagated_noise_peak_time_ratio_high,       g_group);
  reg_handler(AttrType::propagated_noise_peak_time_ratio_low,        g_group);
  reg_handler(AttrType::propagated_noise_width_above_high,  	        g_group);
  reg_handler(AttrType::propagated_noise_width_below_low, 	        g_group);
  reg_handler(AttrType::propagated_noise_width_high,		        g_group);
  reg_handler(AttrType::propagated_noise_width_low,		        g_group);

  reg_handler(AttrType::retaining_rise,		                g_group);
  reg_handler(AttrType::retaining_fall,		                g_group);

  reg_handler(AttrType::retain_fall_slew,		                g_group);
  reg_handler(AttrType::retain_rise_slew,		                g_group);

  reg_handler(AttrType::steady_state_current_high,		        g_group);
  reg_handler(AttrType::steady_state_current_low,		        g_group);
  reg_handler(AttrType::steady_state_current_tristate,	        g_group);
#endif
}

// @brief デストラクタ
TimingHandler::~TimingHandler()
{
}

// @brief 値をクリアする．
void
TimingHandler::clear_value()
{
  mValueList.clear();
}

// @brief 読み込んだ値を返す．
const vector<const AstTiming*>&
TimingHandler::value() const
{
  return mValueList;
}

// @brief グループ記述の始まり
void
TimingHandler::begin_group()
{
  mRelatedPinEquivalent.clear_value();
  mRelatedBusPins.clear_value();
  mRelatedOutputPin.clear_value();
  mRelatedPin.clear_value();
  mTimingSense.clear_value();
  mTimingType.clear_value();
  mRiseResistance.clear_value();
  mFallResistance.clear_value();
  mIntrinsicRise.clear_value();
  mIntrinsicFall.clear_value();
  mSlopeRise.clear_value();
  mSlopeFall.clear_value();
  mWhen.clear_value();
  mWhenStart.clear_value();
  mWhenEnd.clear_value();
  mRiseDelayIntercept.clear_value();
  mFallDelayIntercept.clear_value();
  mRisePinResistance.clear_value();
  mFallPinResistance.clear_value();
  mCellRise.clear_value();
  mCellFall.clear_value();
  mRiseConstraint.clear_value();
  mFallConstraint.clear_value();
  mRiseTransition.clear_value();
  mFallTransition.clear_value();
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
TimingHandler::parse_attr(AttrType attr_type,
			  const FileRegion& attr_loc)
{
  return false;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
TimingHandler::end_group(const FileRegion& group_loc)
{
#if 0
  return mgr().new_timing(loc, value,
			  mVil, mVih, mVimin, mVimax);
#endif
  return false;
}

END_NAMESPACE_YM_DOTLIB
