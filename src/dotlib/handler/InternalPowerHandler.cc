
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
  reg_handler(AttrType::equal_or_opposite_output, simple);
  reg_handler(AttrType::falling_together_group,   simple);
  reg_handler(AttrType::power_level,              simple);
  reg_handler(AttrType::RELATED_pin,              str_simple);
  reg_handler(AttrType::rising_together_group,    simple);
  reg_handler(AttrType::switching_interval,       simple);
  reg_handler(AttrType::switching_together_group, simple);
  reg_handler(AttrType::when,                     func_handler);

  // complex attribute

  // group statements
  reg_handler(AttrType::power,                    power_handler);
  reg_handler(AttrType::fall_power,               power_handler);
  reg_handler(AttrType::RISE_power,               power_handler);
  reg_handler(AttrType::domain,                   g_handler);
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
