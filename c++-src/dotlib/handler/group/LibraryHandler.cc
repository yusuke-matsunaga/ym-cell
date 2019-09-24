
/// @file LibraryHandler.cc
/// @brief LibraryHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/LibraryHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LibraryHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LibraryHandler::LibraryHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
LibraryHandler::~LibraryHandler()
{
}

#if 0
// @breif 'library' Group Statement の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
LibraryHandler::parse_value(const AstLibrary*& dst)
{
  bool stat = parse_group_statement();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}
#endif

// @brief グループ記述の始まり
void
LibraryHandler::begin_group()
{
}

// @brief グループ記述の終わり
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
LibraryHandler::end_group()
{
  return false;
}

END_NAMESPACE_YM_DOTLIB
