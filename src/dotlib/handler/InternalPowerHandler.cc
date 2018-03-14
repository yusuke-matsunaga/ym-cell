
/// @file InternalPowerHandler.cc
/// @brief InternalPowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "HandlerFactory.h"
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
  reg_handler(AttrType::EQUAL_OR_OPPOSITE_OUTPUT, simple);
  reg_handler(AttrType::FALLING_TOGETHER_GROUP,   simple);
  reg_handler(AttrType::POWER_LEVEL,              simple);
  reg_handler(AttrType::RELATED_PIN,              str_simple);
  reg_handler(AttrType::RISING_TOGETHER_GROUP,    simple);
  reg_handler(AttrType::SWITCHING_INTERVAL,       simple);
  reg_handler(AttrType::SWITCHING_TOGETHER_GROUP, simple);
  reg_handler(AttrType::WHEN,                     func_handler);

  // complex attribute

  // group statements
  reg_handler(AttrType::POWER,                    power_handler);
  reg_handler(AttrType::FALL_POWER,               power_handler);
  reg_handler(AttrType::RISE_POWER,               power_handler);
  reg_handler(AttrType::DOMAIN,                   g_handler);
}

// @brief デストラクタ
InternalPowerHandler::~InternalPowerHandler()
{
}

// @brief 値を作る．
const AstNode*
InternalPowerHandler::gen_node(const FileRegion& loc,
			       const vector<const AstAttr*>& attr_list)
{
  for ( auto attr: attr_list ) {
    ;
  }
#warning "TODO: 未完成"
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
