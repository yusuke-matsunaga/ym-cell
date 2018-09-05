
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
InternalPowerHandler::InternalPowerHandler(DotlibParser& parser) :
  EmptyGroupHandler(parser)
{
#if 0
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* str_simple = new StrSimpleHandler(parser, false);
  DotlibHandler* func_handler = HandlerFactory::new_function(parser);
  DotlibHandler* power_handler = HandlerFactory::new_power(parser);
  DotlibHandler* g_handler = HandlerFactory::new_group(parser);

  // simple attributes
  reg_handler(AttrType::equal_or_opposite_output, simple);
  reg_handler(AttrType::falling_together_group,   simple);
  reg_handler(AttrType::power_level,              simple);
  reg_handler(AttrType::related_pin,              str_simple);
  reg_handler(AttrType::rising_together_group,    simple);
  reg_handler(AttrType::switching_interval,       simple);
  reg_handler(AttrType::switching_together_group, simple);
  reg_handler(AttrType::when,                     func_handler);

  // complex attribute

  // group statements
  reg_handler(AttrType::power,                    power_handler);
  reg_handler(AttrType::fall_power,               power_handler);
  reg_handler(AttrType::rise_power,               power_handler);
  reg_handler(AttrType::domain,                   g_handler);
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

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
InternalPowerHandler::read_group_attr(AttrType attr_type,
				      const FileRegion& attr_loc)
{
  return false;
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
