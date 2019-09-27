
/// @file FFHandler.cc
/// @brief FFHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/FFHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FFHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FFHandler::FFHandler(DotlibParser& parser) :
  FLHandler(parser)
{
}

// @brief デストラクタ
FFHandler::~FFHandler()
{
}

// @brief グループ記述の始まり
void
FFHandler::begin_group()
{
  mClockedOn = nullptr;
  mClockedOnAlso = nullptr;
  mNextState = nullptr;
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
FFHandler::end_group()
{
  // エラーチェック

  return true;
}

END_NAMESPACE_YM_DOTLIB
