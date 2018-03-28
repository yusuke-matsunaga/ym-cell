
/// @file TimingHandler.cc
/// @brief TimingHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "TimingHandler.h"
#include "HandlerFactory.h"
#include "TableHandler.h"
#include "AstTiming.h"
#include "AstAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
TimingHandler*
HandlerFactory::new_timing(DotlibParser& parser)
{
  return new TimingHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス TimingHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingHandler::TimingHandler(DotlibParser& parser) :
  EmptyGroupHandler(parser)
{
  mStringHandler = HandlerFactory::new_string(parser, false);
  mFloatHandler = HandlerFactory::new_float(parser);
  mFuncHandler = HandlerFactory::new_function(parser);
  mTimingSenseHandler = HandlerFactory::new_timing_sense(parser);
  mTimingTypeHandler = HandlerFactory::new_timing_type(parser);
  mPieceWiseHandler = HandlerFactory::new_piece_wise(parser);
  mTableHandler = HandlerFactory::new_table(parser);
  mGenGroupHandler = HandlerFactory::new_gen_group(parse);

  // simple attributes
  DotlibHandler* simple = HandlerFactory::new_simple(parser);
  DotlibHandler* str_simple
  DotlibHandler* flt_simple
  DotlibHandler* func_handler =
  DotlibHandler* ts_handler
  DotlibHandler* tt_handler
  DotlibHandler* complex = HandlerFactory::new_complex(parser);
  DotlibHandler* pw_complex
  DotlibHandler* table_handler
  DotlibHandler* g_group = HandlerFactory::new_group(parser);

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
}

// @brief デストラクタ
TimingHandler::~TimingHandler()
{
}

// @brief 属性値を読み込む．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ値を表す AstNode を返す．
//
// エラーの場合には nullptr を返す．
const AstNode*
TimingHandler::parse_attr_value(AttrType attr_type,
				const FileRegion& attr_loc)
{
  return parse(attr_type, attr_loc);
}

// @brief パーズする．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ AstTiming を返す．
//
// エラーの場合には nullptr を返す．
const AstTiming*
TimingHandler::parse(AttrType attr_type,
		     const FileRegion& attr_loc)
{

  const AstString* value;
  FileRegion value_loc;
  FileRegion end_loc;
  bool r = parse_common(attr_type, attr_loc, value, value_loc, end_loc);
  if ( !r ) {
    return nullptr;
  }

  FileRegion loc(attr_loc, end_loc);
  return mgr().new_timing(loc, value,
			  mVil, mVih, mVimin, mVimax);
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常に処理した．
// @retval false 処理中にエラーが起こった．
bool
TimingHandler::parse_attr(AttrType attr_type,
			  const FileRegion& attr_loc)
{
  switch ( attr_type ) {
  }
}

END_NAMESPACE_YM_DOTLIB
