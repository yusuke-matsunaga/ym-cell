
/// @file TimingHandler.cc
/// @brief TimingHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "TimingHandler.h"
#include "dotlib/HandlerFactory.h"
#include "dotlib/DotlibAttr.h"
#include "SimpleHandler.h"
#include "ComplexHandler.h"
#include "PwComplexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_timing(DotlibParser& parser)
{
  return new EmptyGroupHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス TimingHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingHandler::TimingHandler(DotlibParser& parser) :
  EmptyGroupHandler(parser)
{
  // simple attributes
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* flt_simple = new FloatSimpleHandler(parser);
  DotlibHandler* func_handler = HandlerFactory::new_function(parser);
  DotlibHandler* ts_handler = HandlerFactory::new_timing_sense(parser);
  DotlibHandler* tt_handler = HandlerFactory::new_timing_type(parser);
  DotlibHandler* complex = new ComplexHandler(parser);
  DotlibHandler* pw_complex = new PwComplexHandler(parser);
  DotlibHandler* table_handler = HandlerFactory::new_table(parser);
  DotlibHandler* g_group = HandlerFactory::new_group(parser);

  reg_handler(AttrType::RELATED_BUS_EQUIVALENT,                      str_simple);
  reg_handler(AttrType::RELATED_BUS_PINS,                            str_simple);
  reg_handler(AttrType::RELATED_OUTPUT_PIN,                          str_simple);
  reg_handler(AttrType::RELATED_PIN,                                 str_simple);

  reg_handler(AttrType::TIMING_SENSE,                                ts_handler);
  reg_handler(AttrType::TIMING_TYPE,                                 tt_handler);

  reg_handler(AttrType::EDGE_RATE_SENSITIVITY_F0,                    simple);
  reg_handler(AttrType::EDGE_RATE_SENSITIVITY_F1,                    simple);
  reg_handler(AttrType::EDGE_RATE_SENSITIVITY_R0,                    simple);
  reg_handler(AttrType::EDGE_RATE_SENSITIVITY_R1,                    simple);

  reg_handler(AttrType::RISE_RESISTANCE,                             flt_simple);
  reg_handler(AttrType::FALL_RESISTANCE,                             flt_simple);
  reg_handler(AttrType::INTRINSIC_RISE,                              flt_simple);
  reg_handler(AttrType::INTRINSIC_FALL,                              flt_simple);

  reg_handler(AttrType::SDF_COND,                                    simple);
  reg_handler(AttrType::SDF_COND_END,                                simple);
  reg_handler(AttrType::SDF_COND_START,                              simple);
  reg_handler(AttrType::SDF_EDGES,                                   simple);

  reg_handler(AttrType::SLOPE_FALL,                                  flt_simple);
  reg_handler(AttrType::SLOPE_RISE,                                  flt_simple);

  reg_handler(AttrType::WHEN,                                        func_handler);
  reg_handler(AttrType::WHEN_END,                                    func_handler);
  reg_handler(AttrType::WHEN_START,                                  func_handler);

  // complex attribute
  reg_handler(AttrType::RISE_DELAY_INTERCEPT,                        pw_complex);
  reg_handler(AttrType::FALL_DELAY_INTERCEPT,                        pw_complex);
  reg_handler(AttrType::RISE_PIN_RESISTANCE,                         pw_complex);
  reg_handler(AttrType::FALL_PIN_RESISTANCE,                         pw_complex);
  reg_handler(AttrType::ORDERS,                                      complex);
  reg_handler(AttrType::COEFS,                                       complex);

  // group statements
  reg_handler(AttrType::CELL_DEGRADATION,                            g_group);

  reg_handler(AttrType::CELL_RISE,                                   table_handler);
  reg_handler(AttrType::CELL_FALL,                                   table_handler);

  reg_handler(AttrType::RISE_CONSTRAINT,                             table_handler);
  reg_handler(AttrType::FALL_CONSTRAINT,                             table_handler);

  reg_handler(AttrType::RISE_PROPAGATION,                            table_handler);
  reg_handler(AttrType::FALL_PROPAGATION,                            table_handler);

  reg_handler(AttrType::RISE_TRANSITION,                             table_handler);
  reg_handler(AttrType::FALL_TRANSITION,                             table_handler);

  reg_handler(AttrType::NOISE_IMMUNITY_ABOVE_HIGH,                   g_group);
  reg_handler(AttrType::NOISE_IMMUNITY_BELOW_LOW,                    g_group);
  reg_handler(AttrType::NOISE_IMMUNITY_HIGH,                         g_group);
  reg_handler(AttrType::NOISE_IMMUNITY_LOW,                          g_group);

  reg_handler(AttrType::PROPAGATED_NOISE_HEIGHT_ABOVE_HIGH,	        g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_HEIGHT_BELOW_LOW,	        g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_HEIGHT_HIGH,	        g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_HEIGHT_LOW,		        g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_PEAK_TIME_RATIO_ABOVE_HIGH, g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_PEAK_TIME_RATIO_BELOW_LOW,  g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_PEAK_TIME_RATIO_HIGH,       g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_PEAK_TIME_RATIO_LOW,        g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_WIDTH_ABOVE_HIGH,  	        g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_WIDTH_BELOW_LOW, 	        g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_WIDTH_HIGH,		        g_group);
  reg_handler(AttrType::PROPAGATED_NOISE_WIDTH_LOW,		        g_group);

  reg_handler(AttrType::RETAINING_RISE,		                g_group);
  reg_handler(AttrType::RETAINING_FALL,		                g_group);

  reg_handler(AttrType::RETAIN_FALL_SLEW,		                g_group);
  reg_handler(AttrType::RETAIN_RISE_SLEW,		                g_group);

  reg_handler(AttrType::STEADY_STATE_CURRENT_HIGH,		        g_group);
  reg_handler(AttrType::STEADY_STATE_CURRENT_LOW,		        g_group);
  reg_handler(AttrType::STEADY_STATE_CURRENT_TRISTATE,	        g_group);
}

// @brief デストラクタ
TimingHandler::~TimingHandler()
{
}

// @brief 値を作る．
DotlibNode*
TimingHandler::gen_value(const FileRegion& loc,
			 const vector<DotlibAttr*>& attr_list)
{
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == AttrType::RELATED_PIN ) {
      ;
    }
  }

#warning "TODO: 未完成"
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
