
/// @file PinHandler.cc
/// @brief PinHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "PinHandler.h"
#include "SimpleHandler.h"
#include "ComplexHandler.h"
#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/DotlibString.h"
#include "dotlib/DotlibAttr.h"
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
  DotlibHandler* simple       = new SimpleHandler(parser, false);
  DotlibHandler* str_simple   = new StrSimpleHandler(parser, false);
  DotlibHandler* flt_simple   = new FloatSimpleHandler(parser);
  DotlibHandler* func_handler = HandlerFactory::new_function(parser);
  DotlibHandler* dir_handler  = HandlerFactory::new_pin_direction(parser);
  DotlibHandler* complex      = new ComplexHandler(parser);
  DotlibHandler* g_handler    = HandlerFactory::new_group(parser);
  DotlibHandler* ip_handler   = HandlerFactory::new_internal_power(parser);
  DotlibHandler* timing_handler = HandlerFactory::new_timing(parser);

  // simple attributes
  reg_handler(ATTR_BIT_WIDTH,                           simple);
  reg_handler(ATTR_CAPACITANCE,                         flt_simple);
  reg_handler(ATTR_CLOCK,                               simple);
  reg_handler(ATTR_CLOCK_GATE_CLOCK_PIN,                simple);
  reg_handler(ATTR_CLOCK_GATE_ENABLE_PIN,               simple);
  reg_handler(ATTR_CLOCK_GATE_TEST_PIN,                 simple);
  reg_handler(ATTR_CLOCK_GATE_OBS_PIN,                  simple);
  reg_handler(ATTR_CLOCK_GATE_OUT_PIN,                  simple);
  reg_handler(ATTR_COMPLEMENTARY_PIN,                   simple);
  reg_handler(ATTR_CONNECTION_CLASS,                    simple);
  reg_handler(ATTR_DIRECTION,                           dir_handler);
  reg_handler(ATTR_DONT_FAULT,                          simple);
  reg_handler(ATTR_DRIVE_CURRENT,                       simple);
  reg_handler(ATTR_DRIVER_TYPE,                         simple);
  reg_handler(ATTR_FALL_CAPACITANCE,                    simple);
  reg_handler(ATTR_FALL_CURRENT_SLOPE_AFTER_THRESHOLD,  simple);
  reg_handler(ATTR_FALL_CURRENT_SLOPE_BEFORE_THRESHOLD, simple);
  reg_handler(ATTR_FALL_TIME_AFTER_THRESHOLD,           simple);
  reg_handler(ATTR_FALL_TIME_BEFORE_THRESHOLD,          simple);
  reg_handler(ATTR_FANOUT_LOAD,                         flt_simple);
  reg_handler(ATTR_FAULT_MODEL,                         simple);
  reg_handler(ATTR_FUNCTION,                            func_handler);
  reg_handler(ATTR_HAS_BUILTIN_PAD,                     simple);
  reg_handler(ATTR_HYSTERESIS,                          simple);
  reg_handler(ATTR_INPUT_MAP,                           simple);
  reg_handler(ATTR_INPUT_SIGNAL_LEVEL,                  simple);
  reg_handler(ATTR_INPUT_VOLTAGE,                       simple);
  reg_handler(ATTR_INTERNAL_NODE,                       simple);
  reg_handler(ATTR_INVERTED_OUTPUT,                     simple);
  reg_handler(ATTR_IS_PAD,                              simple);
  reg_handler(ATTR_MAX_CAPACITANCE,                     flt_simple);
  reg_handler(ATTR_MAX_FANOUT,                          flt_simple);
  reg_handler(ATTR_MAX_INPUT_NOISE_WIDTH,               simple);
  reg_handler(ATTR_MAX_TRANSITION,                      flt_simple);
  reg_handler(ATTR_MIN_CAPACITANCE,                     flt_simple);
  reg_handler(ATTR_MIN_FANOUT,                          flt_simple);
  reg_handler(ATTR_MIN_INPUT_NOISE_WIDTH,               simple);
  reg_handler(ATTR_MIN_PERIOD,                          simple);
  reg_handler(ATTR_MIN_PULSE_WIDTH_HIGH,                simple);
  reg_handler(ATTR_MIN_PULSE_WIDTH_LOW,                 simple);
  reg_handler(ATTR_MIN_TRANSITION,                      flt_simple);
  reg_handler(ATTR_MULTICELL_PAD_PIN,                   simple);
  reg_handler(ATTR_NEXTSTATE_TYPE,                      simple);
  reg_handler(ATTR_OUTPUT_SIGNAL_LEVEL,                 simple);
  reg_handler(ATTR_OUTPUT_VOLTAGE,                      flt_simple);
  reg_handler(ATTR_PIN_FUNC_TYPE,                       simple);
  reg_handler(ATTR_PREFER_TIED,                         simple);
  reg_handler(ATTR_PRIMARY_OUTPUT,                      simple);
  reg_handler(ATTR_PULLING_CURRENT,                     flt_simple);
  reg_handler(ATTR_PULLING_RESISTANCE,                  flt_simple);
  reg_handler(ATTR_RISE_CAPACITANCE,                    flt_simple);
  reg_handler(ATTR_RISE_CURRENT_SLOPE_AFTER_THRESHOLD,  flt_simple);
  reg_handler(ATTR_RISE_CURRENT_SLOPE_BEFORE_THRESHOLD, flt_simple);
  reg_handler(ATTR_RISE_TIME_AFTER_THRESHOLD,           flt_simple);
  reg_handler(ATTR_RISE_TIME_BEFORE_THRESHOLD,          flt_simple);
  reg_handler(ATTR_SIGNAL_TYPE,                         simple);
  reg_handler(ATTR_SLEW_CONTROL,                        simple);
  reg_handler(ATTR_STATE_FUNCTION,                      simple);
  reg_handler(ATTR_TEST_OUTPUT_ONLY,                    simple);
  reg_handler(ATTR_THREE_STATE,                         func_handler);
  reg_handler(ATTR_VHDL_NAME,                           str_simple);
  reg_handler(ATTR_X_FUNCTION,                          simple);

  // complex attributes
  reg_handler(ATTR_FALL_CAPACITANCE_RANGE,              complex);
  reg_handler(ATTR_RISE_CAPACITANCE_RANGE,              complex);

  // group statements
  reg_handler(ATTR_ELECTROMIGRATION,                    g_handler);
  reg_handler(ATTR_HYPERBOLIC_NOISE_ABOVE_HIGH,         g_handler);
  reg_handler(ATTR_HYPERBOLIC_NOISE_BELOW_LOW,          g_handler);
  reg_handler(ATTR_HYPERBOLIC_NOISE_HIGH,               g_handler);
  reg_handler(ATTR_HYPERBOLIC_NOISE_LOW,                g_handler);
  reg_handler(ATTR_INTERNAL_POWER,                      ip_handler);
  reg_handler(ATTR_MAX_TRANS,                           g_handler);
  reg_handler(ATTR_MIN_PULSE_WIDTH,                     g_handler);
  reg_handler(ATTR_MINIMUM_PERIOD,                      g_handler);
  reg_handler(ATTR_TIMING,                              timing_handler);
  reg_handler(ATTR_TLATCH,                              g_handler);
}

// @brief デストラクタ
PinHandler::~PinHandler()
{
}

// @brief 値を作る．
DotlibNode*
PinHandler::gen_value(const FileRegion& loc,
		      const vector<DotlibNode*>& value_list,
		      const vector<DotlibAttr*>& attr_list)
{
  // ピン名のリストを作る．
  int n = value_list.size();
  vector<const DotlibString*> name_list(n);
  for ( int i = 0; i < n; ++ i ) {
    const DotlibNode* elem = value_list[i];
    const DotlibString* str_node = dynamic_cast<const DotlibString*>(elem);
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
  const DotlibPinDirection* direction = nullptr;
  const DotlibFloat* capacitance = nullptr;
  const DotlibFloat* rise_capacitance = nullptr;
  const DotlibFloat* fall_capacitance = nullptr;
  const DotlibFloat* max_fanout = nullptr;
  const DotlibFloat* min_fanout = nullptr;
  const DotlibFloat* max_capacitance = nullptr;
  const DotlibFloat* min_capacitance = nullptr;
  const DotlibFloat* max_transition = nullptr;
  const DotlibFloat* min_transition = nullptr;
  const DotlibExpr* function = nullptr;
  const DotlibExpr* three_state = nullptr;
  const DotlibNode* internal_node = nullptr;
  const DotlibNode* pin_func_type = nullptr;
  const DotlibTiming* timing_top = nullptr;
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == ATTR_DIRECTION ) {
    }
  }

  return mgr()->new_pin(loc, direction, capacitance, rise_capacitance, fall_capacitance,
			max_fanout, min_fanout, max_capacitance, min_capacitance,
			max_transition, min_transition,
			function, three_state,
			internal_node, pin_func_type,
			timing_top);
}

END_NAMESPACE_YM_DOTLIB
