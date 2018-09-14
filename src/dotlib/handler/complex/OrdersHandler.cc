
/// @file OrdersHandler.cc
/// @brief OrdersHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/OrdersHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス OrdersHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
/// @param[in] parser パーサー
OrdersHandler::OrdersHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
OrdersHandler::~OrdersHandler()
{
}

// @brief 'orders' Complex Attribute の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
OrdersHandler::parse_value(const AstIntVector*& dst)
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
OrdersHandler::begin_header()
{
  mValueList.clear();
  mValue = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
OrdersHandler::read_header_value(TokenType value_type,
				 const FileRegion& value_loc,
				 int count)
{
  if ( count != 0 || value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error.");
    return false;
  }

  const char* tmp_str = cur_string();
  string buf;
  char c = '\0';
  for ( const char* s = tmp_str; (c = *s) ; ++ s ) {
    if ( isspace(c) ) {
      continue;
    }
    else if ( c == ',' ) {
      if ( buf.size() == 0 ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. Null element.");
	return false;
      }
      mValueList.push_back(atoi(buf.c_str()));
      buf.clear();
    }
    else {
      buf += c;
    }
  }
  if ( buf.size() > 0 ) {
    mValueList.push_back(atoi(buf.c_str()));
  }

  return true;
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
OrdersHandler::end_header(const FileRegion& header_loc,
			  int count)
{
  if ( count == 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, a float vector expected.");
    return false;
  }
  else {
    mValue = mgr().new_int_vector(header_loc, mValueList);
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
