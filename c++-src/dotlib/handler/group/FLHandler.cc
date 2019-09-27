
/// @file FLHandler.cc
/// @brief FLHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/FLHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FLHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FLHandler::FLHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
FLHandler::~FLHandler()
{
}

// @brief グループ記述の始まり
void
FLHandler::begin_group()
{
  mClear = nullptr;
  mPreset = nullptr;
  mClearPresetVar1 = nullptr;
  mClearPresetVar2 = nullptr;
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
FLHandler::end_group()
{
  // エラーチェック

  return true;
}

END_NAMESPACE_YM_DOTLIB
