
/// @file InternalPowerHandler.cc
/// @brief InternalPowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/InternalPowerHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス InternalPowerHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
InternalPowerHandler::InternalPowerHandler(Parser& parser) :
  GroupHandler(parser)
{
#if 0
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* func_handler = HandlerFactory::new_function(parser);
  DotlibHandler* power_handler = HandlerFactory::new_power(parser);
  DotlibHandler* g_handler = HandlerFactory::new_group(parser);

  // simple attributes
  reg_handler("equal_or_opposite_output, simple);"
  reg_handler("falling_together_group,   simple);"
  reg_handler("power_level,              simple);"
  reg_handler("related_pin,              str_simple);"
  reg_handler("rising_together_group,    simple);"
  reg_handler("switching_interval,       simple);"
  reg_handler("switching_together_group, simple);"
  reg_handler("when,                     func_handler);"

  // complex attribute

  // group statements
  reg_handler("power,                    power_handler);"
  reg_handler("fall_power,               power_handler);"
  reg_handler("rise_power,               power_handler);"
  reg_handler("domain,                   g_handler);"
#endif
}

// @brief デストラクタ
InternalPowerHandler::~InternalPowerHandler()
{
}

// @brief グループ記述の始まり
void
InternalPowerHandler::begin_group()
{
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
InternalPowerHandler::end_group(const FileRegion& group_loc)
{
  return false;
}

END_NAMESPACE_YM_DOTLIB
