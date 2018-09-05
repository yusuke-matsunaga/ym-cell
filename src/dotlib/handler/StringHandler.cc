
/// @file StringHandler.cc
/// @brief StringHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "StringHandler.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StringHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StringHandler::StringHandler(DotlibParser& parser) :
  StrBaseHandler(parser)
{
}

// @brief デストラクタ
StringHandler::~StringHandler()
{
}

// @brief int 値の記述をパースする．
//
// エラーが起きた場合には nullptr が返される．
const AstString*
StringHandler::parse_value()
{
  bool stat = parse_simple_attribute();
  if ( stat ) {
    return mValue;
  }
  else {
    return nullptr;
  }
}

// @brief シンボルモードの値を返す．
bool
StringHandler::symbol_mode()
{
  return true;
}

// @brief 文字列を読み込んだ時の処理
// @param[in] str 文字列
// @param[in] value_loc 文字列トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
StringHandler::read_str_value(const char* str,
			      const FileRegion& value_loc)
{
  mValue = mgr().new_string(value_loc, ShString(str));
  return true;
}

END_NAMESPACE_YM_DOTLIB
