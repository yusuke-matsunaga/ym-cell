
/// @file LibraryHandler.cc
/// @brief LibraryHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/LibraryHandler.h"
//#include "DefineHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LibraryHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LibraryHandler::LibraryHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
}

// @brief デストラクタ
LibraryHandler::~LibraryHandler()
{
}

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

// @brief グループ記述の始まり
void
LibraryHandler::begin_group()
{
  mValue = nullptr;
}

// @brief attr_type に対応する属性を読み込む．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
LibraryHandler::read_group_attr(AttrType attr_type,
				const FileRegion& attr_loc)
{
  return false;
}

// @brief グループ記述の終わり
// @param[in] group_loc グループ全体のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
LibraryHandler::end_group(const FileRegion& group_loc)
{
  return false;
}

END_NAMESPACE_YM_DOTLIB