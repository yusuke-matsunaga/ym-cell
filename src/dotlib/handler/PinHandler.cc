
/// @file PinHandler.cc
/// @brief PinHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "HandlerFactory.h"
#include "PinHandler.h"
#include "TimingHandler.h"
#include "AstMgr.h"
#include "AstString.h"
#include "AstAttr.h"
#include "AstPin.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief pin group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_pin(DotlibParser& parser)
{
  return new PinHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス PinHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PinHandler::PinHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
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
  reg_handler(AttrType::BIT_WIDTH,                           simple);
  reg_handler(AttrType::CAPACITANCE,                         flt_simple);
  reg_handler(AttrType::CLOCK,                               simple);
  reg_handler(AttrType::CLOCK_GATE_CLOCK_PIN,                simple);
  reg_handler(AttrType::CLOCK_GATE_ENABLE_PIN,               simple);
  reg_handler(AttrType::CLOCK_GATE_TEST_PIN,                 simple);
  reg_handler(AttrType::CLOCK_GATE_OBS_PIN,                  simple);
  reg_handler(AttrType::CLOCK_GATE_OUT_PIN,                  simple);
  reg_handler(AttrType::COMPLEMENTARY_PIN,                   simple);
  reg_handler(AttrType::CONNECTION_CLASS,                    simple);
  reg_handler(AttrType::DIRECTION,                           dir_handler);
  reg_handler(AttrType::DONT_FAULT,                          simple);
  reg_handler(AttrType::DRIVE_CURRENT,                       simple);
  reg_handler(AttrType::DRIVER_TYPE,                         simple);
  reg_handler(AttrType::FALL_CAPACITANCE,                    simple);
  reg_handler(AttrType::FALL_CURRENT_SLOPE_AFTER_THRESHOLD,  simple);
  reg_handler(AttrType::FALL_CURRENT_SLOPE_BEFORE_THRESHOLD, simple);
  reg_handler(AttrType::FALL_TIME_AFTER_THRESHOLD,           simple);
  reg_handler(AttrType::FALL_TIME_BEFORE_THRESHOLD,          simple);
  reg_handler(AttrType::FANOUT_LOAD,                         flt_simple);
  reg_handler(AttrType::FAULT_MODEL,                         simple);
  reg_handler(AttrType::FUNCTION,                            func_handler);
  reg_handler(AttrType::HAS_BUILTIN_PAD,                     simple);
  reg_handler(AttrType::HYSTERESIS,                          simple);
  reg_handler(AttrType::INPUT_MAP,                           simple);
  reg_handler(AttrType::INPUT_SIGNAL_LEVEL,                  simple);
  reg_handler(AttrType::INPUT_VOLTAGE,                       simple);
  reg_handler(AttrType::INTERNAL_NODE,                       simple);
  reg_handler(AttrType::INVERTED_OUTPUT,                     simple);
  reg_handler(AttrType::IS_PAD,                              simple);
  reg_handler(AttrType::MAX_CAPACITANCE,                     flt_simple);
  reg_handler(AttrType::MAX_FANOUT,                          flt_simple);
  reg_handler(AttrType::MAX_INPUT_NOISE_WIDTH,               simple);
  reg_handler(AttrType::MAX_TRANSITION,                      flt_simple);
  reg_handler(AttrType::MIN_CAPACITANCE,                     flt_simple);
  reg_handler(AttrType::MIN_FANOUT,                          flt_simple);
  reg_handler(AttrType::MIN_INPUT_NOISE_WIDTH,               simple);
  reg_handler(AttrType::MIN_PERIOD,                          simple);
  reg_handler(AttrType::MIN_PULSE_WIDTH_HIGH,                simple);
  reg_handler(AttrType::MIN_PULSE_WIDTH_LOW,                 simple);
  reg_handler(AttrType::MIN_TRANSITION,                      flt_simple);
  reg_handler(AttrType::MULTICELL_PAD_PIN,                   simple);
  reg_handler(AttrType::NEXTSTATE_TYPE,                      simple);
  reg_handler(AttrType::OUTPUT_SIGNAL_LEVEL,                 simple);
  reg_handler(AttrType::OUTPUT_VOLTAGE,                      flt_simple);
  reg_handler(AttrType::PIN_FUNC_TYPE,                       simple);
  reg_handler(AttrType::PREFER_TIED,                         simple);
  reg_handler(AttrType::PRIMARY_OUTPUT,                      simple);
  reg_handler(AttrType::PULLING_CURRENT,                     flt_simple);
  reg_handler(AttrType::PULLING_RESISTANCE,                  flt_simple);
  reg_handler(AttrType::RISE_CAPACITANCE,                    flt_simple);
  reg_handler(AttrType::RISE_CURRENT_SLOPE_AFTER_THRESHOLD,  flt_simple);
  reg_handler(AttrType::RISE_CURRENT_SLOPE_BEFORE_THRESHOLD, flt_simple);
  reg_handler(AttrType::RISE_TIME_AFTER_THRESHOLD,           flt_simple);
  reg_handler(AttrType::RISE_TIME_BEFORE_THRESHOLD,          flt_simple);
  reg_handler(AttrType::SIGNAL_TYPE,                         simple);
  reg_handler(AttrType::SLEW_CONTROL,                        simple);
  reg_handler(AttrType::STATE_FUNCTION,                      simple);
  reg_handler(AttrType::TEST_OUTPUT_ONLY,                    simple);
  reg_handler(AttrType::THREE_STATE,                         func_handler);
  reg_handler(AttrType::VHDL_NAME,                           str_simple);
  reg_handler(AttrType::X_FUNCTION,                          simple);

  // complex attributes
  reg_handler(AttrType::FALL_CAPACITANCE_RANGE,              complex);
  reg_handler(AttrType::RISE_CAPACITANCE_RANGE,              complex);

  // group statements
  reg_handler(AttrType::ELECTROMIGRATION,                    g_handler);
  reg_handler(AttrType::HYPERBOLIC_NOISE_ABOVE_HIGH,         g_handler);
  reg_handler(AttrType::HYPERBOLIC_NOISE_BELOW_LOW,          g_handler);
  reg_handler(AttrType::HYPERBOLIC_NOISE_HIGH,               g_handler);
  reg_handler(AttrType::HYPERBOLIC_NOISE_LOW,                g_handler);
  reg_handler(AttrType::INTERNAL_POWER,                      ip_handler);
  reg_handler(AttrType::MAX_TRANS,                           g_handler);
  reg_handler(AttrType::MIN_PULSE_WIDTH,                     g_handler);
  reg_handler(AttrType::MINIMUM_PERIOD,                      g_handler);
  reg_handler(AttrType::TLATCH,                              g_handler);

  mTimingHandler = HandlerFactory::new_timing(parser);
}

// @brief デストラクタ
PinHandler::~PinHandler()
{
}

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
  if ( attr_type == AttrType::TIMING ) {
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
		      kMsgError,
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
    if ( attr->attr_type() == AttrType::DIRECTION ) {
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

END_NAMESPACE_YM_DOTLIB
