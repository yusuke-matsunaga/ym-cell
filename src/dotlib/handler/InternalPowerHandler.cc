
/// @file InternalPowerHandler.cc
/// @brief InternalPowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HandlerFactory.h"
#include "InternalPowerHandler.h"
#include "SimpleHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief internal_power group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_internal_power(DotlibParser& parser)
{
  return new InternalPowerHandler(parser);
}

//////////////////////////////////////////////////////////////////////
// クラス InternalPowerHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
InternalPowerHandler::InternalPowerHandler(DotlibParser& parser) :
  EmptyGroupHandler(parser)
{
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* func_handler = HandlerFactory::new_function(parser);
  DotlibHandler* power_handler = HandlerFactory::new_power(parser);
  DotlibHandler* g_handler = HandlerFactory::new_group(parser);

  // simple attributes
  reg_handler(ATTR_EQUAL_OR_OPPOSITE_OUTPUT, simple);
  reg_handler(ATTR_FALLING_TOGETHER_GROUP,   simple);
  reg_handler(ATTR_POWER_LEVEL,              simple);
  reg_handler(ATTR_RELATED_PIN,              str_simple);
  reg_handler(ATTR_RISING_TOGETHER_GROUP,    simple);
  reg_handler(ATTR_SWITCHING_INTERVAL,       simple);
  reg_handler(ATTR_SWITCHING_TOGETHER_GROUP, simple);
  reg_handler(ATTR_WHEN,                     func_handler);

  // complex attribute

  // group statements
  reg_handler(ATTR_POWER,                    power_handler);
  reg_handler(ATTR_FALL_POWER,               power_handler);
  reg_handler(ATTR_RISE_POWER,               power_handler);
  reg_handler(ATTR_DOMAIN,                   g_handler);
}

// @brief デストラクタ
InternalPowerHandler::~InternalPowerHandler()
{
}

// @brief 値を作る．
DotlibNode*
InternalPowerHandler::gen_value(const FileRegion& loc,
				const vector<DotlibAttr*>& attr_list)
{
  for ( auto attr: attr_list ) {
    ;
  }
#warning "TODO: 未完成"
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
