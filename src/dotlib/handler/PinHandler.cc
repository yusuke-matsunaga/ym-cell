
/// @file PinHandler.cc
/// @brief PinHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "PinHandler.h"
#include "TimingHandler.h"
#include "dotlib/AstMgr.h"
//#include "dotlib/AstString.h"
//#include "dotlib/AstAttr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス PinHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PinHandler::PinHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
#if 0
  DotlibHandler* simple       = HandlerFactory::new_simple(parser);
  DotlibHandler* str_simple   = HandlerFactory::new_string(parser, false);
  DotlibHandler* flt_simple   = HandlerFactory::new_float(parser);
  DotlibHandler* func_handler = HandlerFactory::new_function(parser);
  DotlibHandler* dir_handler  = HandlerFactory::new_pin_direction(parser);
  DotlibHandler* complex      = HandlerFactory::new_complex(parser);
  DotlibHandler* g_handler    = HandlerFactory::new_group(parser);
  DotlibHandler* ip_handler   = HandlerFactory::new_internal_power(parser);
  DotlibHandler* timing_handler = HandlerFactory::new_timing(parser);

  // simple attributes
  reg_handler(AttrType::bit_width,                           simple);
  reg_handler(AttrType::capacitance,                         flt_simple);
  reg_handler(AttrType::clock,                               simple);
  reg_handler(AttrType::clock_gate_clock_pin,                simple);
  reg_handler(AttrType::clock_gate_enable_pin,               simple);
  reg_handler(AttrType::clock_gate_test_pin,                 simple);
  reg_handler(AttrType::clock_gate_obs_pin,                  simple);
  reg_handler(AttrType::clock_gate_out_pin,                  simple);
  reg_handler(AttrType::complementary_pin,                   simple);
  reg_handler(AttrType::connection_class,                    simple);
  reg_handler(AttrType::direction,                           dir_handler);
  reg_handler(AttrType::dont_fault,                          simple);
  reg_handler(AttrType::drive_current,                       simple);
  reg_handler(AttrType::driver_type,                         simple);
  reg_handler(AttrType::FALL_capacitance,                    simple);
  reg_handler(AttrType::fall_current_slope_after_threshold,  simple);
  reg_handler(AttrType::fall_current_slope_before_threshold, simple);
  reg_handler(AttrType::fall_time_after_threshold,           simple);
  reg_handler(AttrType::fall_time_before_threshold,          simple);
  reg_handler(AttrType::fanout_load,                         flt_simple);
  reg_handler(AttrType::fault_model,                         simple);
  reg_handler(AttrType::function,                            func_handler);
  reg_handler(AttrType::has_builtin_pad,                     simple);
  reg_handler(AttrType::hysteresis,                          simple);
  reg_handler(AttrType::input_map,                           simple);
  reg_handler(AttrType::input_signal_level,                  simple);
  reg_handler(AttrType::input_voltage,                       simple);
  reg_handler(AttrType::internal_node,                       simple);
  reg_handler(AttrType::inverted_output,                     simple);
  reg_handler(AttrType::is_pad,                              simple);
  reg_handler(AttrType::MAX_capacitance,                     flt_simple);
  reg_handler(AttrType::max_fanout,                          flt_simple);
  reg_handler(AttrType::max_input_noise_width,               simple);
  reg_handler(AttrType::max_transITION,                      flt_simple);
  reg_handler(AttrType::MIN_capacitance,                     flt_simple);
  reg_handler(AttrType::min_fanout,                          flt_simple);
  reg_handler(AttrType::min_input_noise_width,               simple);
  reg_handler(AttrType::min_period,                          simple);
  reg_handler(AttrType::min_pulse_width_high,                simple);
  reg_handler(AttrType::min_pulse_width_low,                 simple);
  reg_handler(AttrType::min_transition,                      flt_simple);
  reg_handler(AttrType::MULTIcell_PAD_pin,                   simple);
  reg_handler(AttrType::nextstate_type,                      simple);
  reg_handler(AttrType::output_signal_level,                 simple);
  reg_handler(AttrType::output_voltage,                      flt_simple);
  reg_handler(AttrType::pin_func_type,                       simple);
  reg_handler(AttrType::prefer_tied,                         simple);
  reg_handler(AttrType::primary_output,                      simple);
  reg_handler(AttrType::pulling_current,                     flt_simple);
  reg_handler(AttrType::pulling_resistance,                  flt_simple);
  reg_handler(AttrType::RISE_capacitance,                    flt_simple);
  reg_handler(AttrType::rise_current_slope_after_threshold,  flt_simple);
  reg_handler(AttrType::rise_current_slope_before_threshold, flt_simple);
  reg_handler(AttrType::rise_time_after_threshold,           flt_simple);
  reg_handler(AttrType::rise_time_before_threshold,          flt_simple);
  reg_handler(AttrType::signal_type,                         simple);
  reg_handler(AttrType::slew_control,                        simple);
  reg_handler(AttrType::STATE_function,                      simple);
  reg_handler(AttrType::test_output_only,                    simple);
  reg_handler(AttrType::three_state,                         func_handler);
  reg_handler(AttrType::vhdl_name,                           str_simple);
  reg_handler(AttrType::X_function,                          simple);

  // complex attributes
  reg_handler(AttrType::FALL_capacitance_RANGE,              complex);
  reg_handler(AttrType::RISE_capacitance_RANGE,              complex);

  // group statements
  reg_handler(AttrType::electromigration,                    g_handler);
  reg_handler(AttrType::hyperbolic_noise_above_high,         g_handler);
  reg_handler(AttrType::hyperbolic_noise_below_low,          g_handler);
  reg_handler(AttrType::hyperbolic_noise_high,               g_handler);
  reg_handler(AttrType::hyperbolic_noise_low,                g_handler);
  reg_handler(AttrType::internal_power,                      ip_handler);
  reg_handler(AttrType::max_trans,                           g_handler);
  reg_handler(AttrType::min_pulse_width,                     g_handler);
  reg_handler(AttrType::minimum_period,                      g_handler);
  reg_handler(AttrType::Tlatch,                              g_handler);

  mTimingHandler = HandlerFactory::new_timing(parser);
#endif
}

// @brief デストラクタ
PinHandler::~PinHandler()
{
}

// @brief 値をクリアする．
void
PinHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstPin*
PinHandler::value() const
{
  return mValue;
}

// @brief グループ記述の始まり
void
PinHandler::begin_group()
{
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
PinHandler::parse_attr(AttrType attr_type,
		       const FileRegion& attr_loc)
{
  return false;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
PinHandler::end_group(const FileRegion& group_loc)
{
  return false;
}

#if 0
// @brief グループ開始の処理を行う．
void
PinHandler::begin_group()
{
  mTimingList.clear();
  GroupHandler::begin_group();
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval 0 処理しなかった．
// @retval 1 正常に処理した．
// @retval 2 処理中にエラーが起こった．
int
PinHandler::parse_attr(AttrType attr_type,
		       const FileRegion& attr_loc)
{
  if ( attr_type == AttrType::timing ) {
    auto timing = mTimingHandler->parse_timing_value(attr_type, attr_loc);
    mTimingList.push_back(timing);
    return 1;
  }
  return GroupHandler::parse_attr(attr_type, attr_loc);
}

// @brief 値を作る．
const AstNode*
PinHandler::gen_node(const FileRegion& loc,
		     const vector<const AstNode*>& value_list,
		     const vector<const AstAttr*>& attr_list)
{
  // ピン名のリストを作る．
  int n = value_list.size();
  vector<const AstString*> name_list(n);
  for ( int i = 0; i < n; ++ i ) {
    const AstNode* elem = value_list[i];
    const AstString* str_node = dynamic_cast<const AstString*>(elem);
    if ( str_node == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      elem->loc(),
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. string value expected");
      return nullptr;
    }
    name_list[i] = str_node;
  }

  // 属性を取り出す．
  const AstPinDirection* direction = nullptr;
  const AstFloat* capacitance = nullptr;
  const AstFloat* rise_capacitance = nullptr;
  const AstFloat* fall_capacitance = nullptr;
  const AstFloat* max_fanout = nullptr;
  const AstFloat* min_fanout = nullptr;
  const AstFloat* max_capacitance = nullptr;
  const AstFloat* min_capacitance = nullptr;
  const AstFloat* max_transition = nullptr;
  const AstFloat* min_transition = nullptr;
  const AstExpr* function = nullptr;
  const AstExpr* three_state = nullptr;
  const AstNode* internal_node = nullptr;
  const AstNode* pin_func_type = nullptr;
  const AstTiming* timing_top = nullptr;
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == AttrType::direction ) {
    }
  }

  return mgr().new_pin(loc, name_list, direction,
		       capacitance, rise_capacitance, fall_capacitance,
		       max_fanout, min_fanout,
		       max_capacitance, min_capacitance,
		       max_transition, min_transition,
		       function, three_state,
		       internal_node, pin_func_type,
		       mTimingList);
}
#endif

END_NAMESPACE_YM_DOTLIB
