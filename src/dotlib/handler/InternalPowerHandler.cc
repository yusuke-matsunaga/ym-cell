
/// @file InternalPowerHandler.cc
/// @brief InternalPowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HandlerFactory.h"
#include "InternalPowerHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief internal_power group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_internal_power(GroupHandler* parent)
{
  return new InternalPowerHandler(parent);
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
  DotlibHandler* func_handler = new FuncHandler(parser);
  DotlibHandler* power_handler = new_power(parser);

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
  reg_handler(ATTR_DOMAIN,                   new_group(handler));
}

// @brief デストラクタ
InternalPowerHandler::~InternalPowerHandler()
{
}

// @brief 値を作る．
DotlibNode*
InternalPowerHandler::gen_value(const DotlibList* value_list,
				const DotlibAttr* attr_top)
{
  for ( auto attr = attr_top; attr != nullptr; attr = attr->next() ) {
  }
}

END_NAMESPACE_YM_DOTLIB
