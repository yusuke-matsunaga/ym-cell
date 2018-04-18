
/// @file CellInternalPowerHandler.cc
/// @brief CellInternalPowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "CellInternalPower.h"
#include "SimpleHandler.h"
#include "ValuesHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス CellInternalPowerHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
CellInternalPowerHandler::CellInternalPowerHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
#if 0
  // simple attributes
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* values_handler = new ValuesHandler(parser);

  reg_handler(AttrType::related_inputs,  simple);
  reg_handler(AttrType::related_outputs, simple);

  reg_handler(AttrType::valueS,          values_handler);
#endif
}

// @brief デストラクタ
CellInternalPowerHandler::~CellInternalPowerHandler()
{
}

// @brief グループ記述の始まり
void
CellInternalPowerHandler::begin_group()
{
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
CellInternalPowerHandler::parse_attr(AttrType attr_type,
				     const FileRegion& attr_loc)
{
  return false;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
CellInternalPowerHandler::end_group(const FileRegion& group_loc)
{
  return false;
}

END_NAMESPACE_YM_DOTLIB
