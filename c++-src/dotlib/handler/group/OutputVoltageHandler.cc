
/// @file OutputVoltageHandler.cc
/// @brief OutputVoltageHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/OutputVoltageHandler.h"
#include "dotlib/AstExpr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス OutputVoltageHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
OutputVoltageHandler::OutputVoltageHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func(AttrType::vol,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mVol, attr_type, attr_loc); });
  reg_func(AttrType::voh,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mVoh, attr_type, attr_loc); });
  reg_func(AttrType::vomin,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mVomin, attr_type, attr_loc); });
  reg_func(AttrType::vomax,
	   [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
	   { return parser.parse_expr(mVomax, attr_type, attr_loc); });
}

// @brief デストラクタ
OutputVoltageHandler::~OutputVoltageHandler()
{
}

// @brief グループ記述の始まり
void
OutputVoltageHandler::begin_group()
{
  mVol = nullptr;
  mVoh = nullptr;
  mVomin = nullptr;
  mVomax = nullptr;
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
OutputVoltageHandler::end_group()
{
  if ( !check_attr(mVol,   AttrType::vol,   group_loc()) ||
       !check_attr(mVoh,   AttrType::voh,   group_loc()) ||
       !check_attr(mVomin, AttrType::vomin, group_loc()) ||
       !check_attr(mVomax, AttrType::vomax, group_loc()) ) {
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
