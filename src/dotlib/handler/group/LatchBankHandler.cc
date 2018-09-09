
/// @file LatchBankHandler.cc
/// @brief LatchBankHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/LatchBankHandler.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LatchBankHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LatchBankHandler::LatchBankHandler(DotlibParser& parser) :
  Str2IntGroupHandler(parser)
{
}

// @brief デストラクタ
LatchBankHandler::~LatchBankHandler()
{
}

// @breif ff Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
LatchBankHandler::parse_value(const AstLatchBank*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief グループ記述の始まり
void
LatchBankHandler::begin_group()
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
LatchBankHandler::end_group(const FileRegion& group_loc)
{
  // エラーチェック
  mValue = mgr().new_latch_bank(group_loc, header_value1(), header_value2(), header_value3(),
				mClear, mPreset, mClearPresetVar1, mClearPresetVar2,
				mEnableOn, mEnableOnAlso, mDataIn);
  return true;
}

END_NAMESPACE_YM_DOTLIB
