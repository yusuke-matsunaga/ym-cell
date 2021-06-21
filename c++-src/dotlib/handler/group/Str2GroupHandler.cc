
/// @file Str2GroupHandler.cc
/// @brief Str2GroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Str2GroupHandler.h"
#include "dotlib/Parser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Str2GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str2GroupHandler::Str2GroupHandler(Parser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
Str2GroupHandler::~Str2GroupHandler()
{
}

// @brief ヘッダの値1を取り出す．
const AstString*
Str2GroupHandler::header_value1() const
{
  return mHeaderValue1;
}

// @brief ヘッダの値2を取り出す．
const AstString*
Str2GroupHandler::header_value2() const
{
  return mHeaderValue2;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
Str2GroupHandler::begin_header()
{
  mHeaderValue1 = nullptr;
  mHeaderValue2 = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Str2GroupHandler::read_header_value(TokenType value_type,
				    const FileRegion& value_loc,
				    int count)
{
  switch ( count ) {
  case 0:
    if ( value_type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    else {
      mHeaderValue1 = mgr().new_string(value_loc, ShString(cur_string()));
      return true;
    }
    break;

  case 1:
    if ( value_type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    else {
      mHeaderValue2 = mgr().new_string(value_loc, ShString(cur_string()));
      return true;
    }
    break;

  default:
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "syntax error, wrong # of parameters.");
    return false;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
Str2GroupHandler::end_header(const FileRegion& header_loc,
			     int count)
{
  if ( count != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "a pair of string parameters is expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
