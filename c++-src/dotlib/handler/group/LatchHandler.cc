
/// @file LatchHandler.cc
/// @brief LatchHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/LatchHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LatchHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LatchHandler::LatchHandler(DotlibParser& parser) :
  FLHandler(parser)
{
}

// @brief デストラクタ
LatchHandler::~LatchHandler()
{
}

// @brief グループ記述の始まり
void
LatchHandler::begin_group()
{
  mEnableOn = nullptr;
  mEnableOnAlso = nullptr;
  mDataIn = nullptr;
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
LatchHandler::end_group()
{
  // エラーチェック

  return true;
}

END_NAMESPACE_YM_DOTLIB
