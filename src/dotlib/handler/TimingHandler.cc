
/// @file TimingHandler.cc
/// @brief TimingHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "TimingHandler.h"
#include "HanderFactory.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_timing(GroupHandler* parent)
{
  GroupHandler* handler = new EmptyGroupHandler(parent);

  return handler;
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
  DotlibHandler* func_handler = new_function(parser);
  DotlibHandler* ts_handler = new TimingSenseHandler(parser);
  DotlibHandler* tt_handler = new TimingTypeHandler(parser);
  DotlibHandler* complex = new ComplexHandler(handler);
  DotlibHandler* pw_complex = new PwComplexHandler(handler);
  DotlibHandler* table_handler = new_table(handler);

  reg_handler(ATTR_RELATED_BUS_EQUIVALENT,                      str_simple);
  reg_handler(ATTR_RELATED_BUS_PINS,                            str_simple);
  reg_handler(ATTR_RELATED_OUTPUT_PIN,                          str_simple);
  reg_handler(ATTR_RELATED_PIN,                                 str_simple);

  reg_handler(ATTR_TIMING_SENSE,                                ts_handler);
  reg_handler(ATTR_TIMING_TYPE,                                 tt_handler);

  reg_handler(ATTR_EDGE_RATE_SENSITIVITY_F0,                    simple);
  reg_handler(ATTR_EDGE_RATE_SENSITIVITY_F1,                    simple);
  reg_handler(ATTR_EDGE_RATE_SENSITIVITY_R0,                    simple);
  reg_handler(ATTR_EDGE_RATE_SENSITIVITY_R1,                    simple);

  reg_handler(ATTR_RISE_RESISTANCE,                             flt_simple);
  reg_handler(ATTR_FALL_RESISTANCE,                             flt_simple);
  reg_handler(ATTR_INTRINSIC_RISE,                              flt_simple);
  reg_handler(ATTR_INTRINSIC_FALL,                              flt_simple);

  reg_handler(ATTR_SDF_COND,                                    simple);
  reg_handler(ATTR_SDF_COND_END,                                simple);
  reg_handler(ATTR_SDF_COND_START,                              simple);
  reg_handler(ATTR_SDF_EDGES,                                   simple);

  reg_handler(ATTR_SLOPE_FALL,                                  flt_simple);
  reg_handler(ATTR_SLOPE_RISE,                                  flt_simple);

  reg_handler(ATTR_WHEN,                                        func_handler);
  reg_handler(ATTR_WHEN_END,                                    func_handler);
  reg_handler(ATTR_WHEN_START,                                  func_handler);

  // complex attribute
  reg_handler(ATTR_RISE_DELAY_INTERCEPT,                        pw_complex);
  reg_handler(ATTR_FALL_DELAY_INTERCEPT,                        pw_complex);
  reg_handler(ATTR_RISE_PIN_RESISTANCE,                         pw_complex);
  reg_handler(ATTR_FALL_PIN_RESISTANCE,                         pw_complex);
  reg_handler(ATTR_ORDERS,                                      complex);
  reg_handler(ATTR_COEFS,                                       complex);

  // group statements
  reg_handler(ATTR_CELL_DEGRADATION,                            new_group(handler));

  reg_handler(ATTR_CELL_RISE,                                   table_handler);
  reg_handler(ATTR_CELL_FALL,                                   table_handler);

  reg_handler(ATTR_RISE_CONSTRAINT,                             table_handler);
  reg_handler(ATTR_FALL_CONSTRAINT,                             table_handler);

  reg_handler(ATTR_RISE_PROPAGATION,                            table_handler);
  reg_handler(ATTR_FALL_PROPAGATION,                            table_handler);

  reg_handler(ATTR_RISE_TRANSITION,                             table_handler);
  reg_handler(ATTR_FALL_TRANSITION,                             table_handler);

  reg_handler(ATTR_NOISE_IMMUNITY_ABOVE_HIGH,                   new_group(handler));
  reg_handler(ATTR_NOISE_IMMUNITY_BELOW_LOW,                    new_group(handler));
  reg_handler(ATTR_NOISE_IMMUNITY_HIGH,                         new_group(handler));
  reg_handler(ATTR_NOISE_IMMUNITY_LOW,                          new_group(handler));

  reg_handler(ATTR_PROPAGATED_NOISE_HEIGHT_ABOVE_HIGH,	        new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_HEIGHT_BELOW_LOW,	        new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_HEIGHT_HIGH,	        new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_HEIGHT_LOW,		        new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_ABOVE_HIGH, new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_BELOW_LOW,  new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_HIGH,       new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_PEAK_TIME_RATIO_LOW,        new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_WIDTH_ABOVE_HIGH,  	        new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_WIDTH_BELOW_LOW, 	        new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_WIDTH_HIGH,		        new_group(handler));
  reg_handler(ATTR_PROPAGATED_NOISE_WIDTH_LOW,		        new_group(handler));

  reg_handler(ATTR_RETAINING_RISE,		                new_group(handler));
  reg_handler(ATTR_RETAINING_FALL,		                new_group(handler));

  reg_handler(ATTR_RETAIN_FALL_SLEW,		                new_group(handler));
  reg_handler(ATTR_RETAIN_RISE_SLEW,		                new_group(handler));

  reg_handler(ATTR_STEADY_STATE_CURRENT_HIGH,		        new_group(handler));
  reg_handler(ATTR_STEADY_STATE_CURRENT_LOW,		        new_group(handler));
  reg_handler(ATTR_STEADY_STATE_CURRENT_TRISTATE,	        new_group(handler));
}

// @brief デストラクタ
TimingHandler::~TimingHandler()
{
}

// @brief 値を作る．
DotlibNode*
TimingHandler::gen_value(const DotlibList* value_list,
			 const DotlibAttr* attr_top)
{
  for ( auto attr = attr_top; attr != nullptr; attr = attr->next() ) {
    if ( attr->attr_type() == ATTR_RELATED_PIN ) {
    }
  }
}

END_NAMESPACE_YM_DOTLIB
