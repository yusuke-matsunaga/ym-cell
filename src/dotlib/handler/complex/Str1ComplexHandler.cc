
/// @file Str1HeaderHandler.cc
/// @brief Str1HeaderHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Str1HeaderHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Str1HeaderHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
Str1HeaderHandler::Str1HeaderHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
Str1HeaderHandler::~Str1HeaderHandler()
{
}

// @brief 1つの文字列型を取る complex attribute の記述をパースする．
// @param[in] dst 結果を格納する変数
// @retval true 正しくパースした．
// @retval false エラーが怒った．
bool
Str1HeaderHandler::parse_value(const AstString*& dst)
{
  bool stat = parse_complex_attribute();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
Str1HeaderHandler::begin_header()
{
  mValue = nullptr;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Str1HeaderHandler::read_header_value(TokenType value_type,
				     const FileRegion& value_loc,
				     int count)
{
  switch ( count ) {
  case 0:
    if ( value_type == TokenType::SYMBOL ) {
      mValue = mgr().new_string(value_loc, ShString(cur_string()));
      return true;
    }
    break;

  default:
    break;
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  value_loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error, a string expected.");
  return false;
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
Str1HeaderHandler::end_header(const FileRegion& header_loc,
			      int count)
{
  if ( count != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
