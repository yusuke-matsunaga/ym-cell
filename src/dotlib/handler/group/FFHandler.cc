
/// @file FFHandler.cc
/// @brief FFHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/FFHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FFHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FFHandler::FFHandler(DotlibParser& parser) :
  Str2GroupHandler(parser)
{
}

// @brief デストラクタ
FFHandler::~FFHandler()
{
}

// @breif ff Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
FFHandler::parse_value(const AstFF*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief グループ記述の始まり
void
FFHandler::begin_group()
{
  mClear = nullptr;
  mPreset = nullptr;
  mClearPresetVar1 = nullptr;
  mClearPresetVar2 = nullptr;
  mClockedOn = nullptr;
  mClockedOnAlso = nullptr;
  mNextState = nullptr;

  mValue = nullptr;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
FFHandler::end_group(const FileRegion& group_loc)
{
  // エラーチェック
  mValue = mgr().new_ff(group_loc, header_value1(), header_value2(),
			mClear, mPreset, mClearPresetVar1, mClearPresetVar2,
			mClockedOn, mClockedOnAlso, mNextState);
  return true;
}

END_NAMESPACE_YM_DOTLIB
