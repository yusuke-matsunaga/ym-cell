
/// @file Str2IntGroupHandler.cc
/// @brief Str2IntGroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Str2IntGroupHandler.h"
#include "dotlib/Parser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Str2IntGroupHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str2IntGroupHandler::Str2IntGroupHandler(Parser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
Str2IntGroupHandler::~Str2IntGroupHandler()
{
}

// @brief ヘッダの値1を取り出す．
const AstString*
Str2IntGroupHandler::header_value1() const
{
  return mHeaderValue1;
}

// @brief ヘッダの値2を取り出す．
const AstString*
Str2IntGroupHandler::header_value2() const
{
  return mHeaderValue2;
}

// @brief ヘッダの値3を取り出す．
const AstInt*
Str2IntGroupHandler::header_value3() const
{
  return mHeaderValue3;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
Str2IntGroupHandler::begin_header()
{
  mHeaderValue1 = nullptr;
  mHeaderValue2 = nullptr;
  mHeaderValue3 = nullptr;
}

// @brief 値を読み込む処理
// @param[in] parser パーサー
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Str2IntGroupHandler::read_header_value(TokenType value_type,
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

  case 2:
    if ( value_type != TokenType::INT_NUM ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "integer value is expected.");
      return false;
    }
    else {
      mHeaderValue3 = mgr().new_int(value_loc, cur_int());
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
Str2IntGroupHandler::end_header(const FileRegion& header_loc,
				int count)
{
  if ( count != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "(str, str, int)-type parameters are expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
