
/// @file LatchHandler.cc
/// @brief LatchHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/LatchHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LatchHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LatchHandler::LatchHandler(DotlibParser& parser) :
  Str2GroupHandler(parser)
{
}

// @brief デストラクタ
LatchHandler::~LatchHandler()
{
}

// @breif ff Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
LatchHandler::parse_value(const AstLatch*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief グループ記述の始まり
void
LatchHandler::begin_group()
{
  mClear = nullptr;
  mPreset = nullptr;
  mClearPresetVar1 = nullptr;
  mClearPresetVar2 = nullptr;
  mEnableOn = nullptr;
  mEnableOnAlso = nullptr;
  mDataIn = nullptr;

  mValue = nullptr;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
LatchHandler::end_group(const FileRegion& group_loc)
{
  // エラーチェック
  mValue = mgr().new_latch(group_loc, header_value1(), header_value2(),
			   mClear, mPreset, mClearPresetVar1, mClearPresetVar2,
			   mEnableOn, mEnableOnAlso, mDataIn);
  return true;
}

END_NAMESPACE_YM_DOTLIB