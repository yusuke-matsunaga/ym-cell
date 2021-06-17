
/// @file InputVoltageHandler.cc
/// @brief InputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/InputVoltageHandler.h"
#include "dotlib/AstExpr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス InputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
InputVoltageHandler::InputVoltageHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::vil,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_expr(mExprList, attr_type, attr_loc); });
  reg_func(AttrType::vih,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_expr(mExprList, attr_type, attr_loc); });
  reg_func(AttrType::vimin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_expr(mExprList, attr_type, attr_loc); });
  reg_func(AttrType::vimax,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.add_expr(mExprList, attr_type, attr_loc); });
}

// @brief デストラクタ
InputVoltageHandler::~InputVoltageHandler()
{
}

// @brief グループ記述の始まり
void
InputVoltageHandler::begin_group()
{
  mExprList.clear();
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
InputVoltageHandler::end_group()
{
#if 0
  if ( !check_attr(mVil,   AttrType::vil,   group_loc()) ||
       !check_attr(mVih,   AttrType::vih,   group_loc()) ||
       !check_attr(mVimin, AttrType::vimin, group_loc()) ||
       !check_attr(mVimax, AttrType::vimax, group_loc()) ) {
    return false;
  }
  else {
    return true;
  }
#else
  return false;
#endif
}

END_NAMESPACE_YM_DOTLIB
