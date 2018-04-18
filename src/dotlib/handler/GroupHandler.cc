
/// @file GroupHandler.cc
/// @brief GroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "GroupHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstString.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief 親がない場合のコンストラクタ
// @param[in] parser パーサー
GroupHandler::GroupHandler(DotlibParser& parser) :
  CGHandler(parser)
{
}

// @brief デストラクタ
GroupHandler::~GroupHandler()
{
}

// @brief 構文要素を処理する．
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
GroupHandler::parse_attr_value()
{
  if ( !parse_header() ) {
    return false;
  }

  if ( !expect(TokenType::LCB) ) {
    return false;
  }

  begin_group();

  FileRegion first_loc = parser().cur_loc();
  FileRegion last_loc;
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = parser().read_token(loc);
    if ( type == TokenType::NL ) {
      continue;
    }
    if ( type == TokenType::RCB ) {
      last_loc = loc;
      break;
    }
    if ( type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    const char* name = parser().cur_string();
    AttrType name_type = parser().conv_to_attr(name);
    if ( name_type == AttrType::none ) {
      ostringstream buf;
      buf << name << ": syntax error.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      buf.str());
      return false;
    }
    bool r = parse_attr(name_type, loc);
    if ( !r ) {
      return false;
    }
  }

  if ( !end_group(FileRegion(first_loc, last_loc)) ) {
    return false;
  }

  if ( !expect(TokenType::NL) ) {
    return false;
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス EmptyGroupHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
EmptyGroupHandler::EmptyGroupHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
EmptyGroupHandler::~EmptyGroupHandler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
EmptyGroupHandler::begin_header()
{
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
EmptyGroupHandler::read_value(TokenType value_type,
			      const FileRegion& value_loc,
			      int count)
{
  MsgMgr::put_msg(__FILE__, __LINE__,
		  value_loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Empty header block is expected");
  return false;
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
EmptyGroupHandler::end_header(const FileRegion& header_loc,
			      int count)
{
  if ( count > 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Empty header block is expected");
    return false;
  }
  else {
    return true;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス Str1GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief 親を持たないハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str1GroupHandler::Str1GroupHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
Str1GroupHandler::~Str1GroupHandler()
{
}

// @brief ヘッダの値をクリアする．
void
Str1GroupHandler::clear_header()
{
  mHeaderValue = nullptr;
}

// @brief ヘッダの値を取り出す．
const AstString*
Str1GroupHandler::header_value() const
{
  return mHeaderValue;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
Str1GroupHandler::begin_header()
{
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Str1GroupHandler::read_value(TokenType value_type,
			     const FileRegion& value_loc,
			     int count)
{
  if ( count != 0 || value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  else {
    mHeaderValue = mgr().new_string(value_loc, ShString(parser().cur_string()));
    return true;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
Str1GroupHandler::end_header(const FileRegion& header_loc,
			     int count)
{
  if ( count != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  else {
    return true;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス Str2GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str2GroupHandler::Str2GroupHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
Str2GroupHandler::~Str2GroupHandler()
{
}

// @brief ヘッダの値をクリアする．
void
Str2GroupHandler::clear_header()
{
  mHeaderValue1 = nullptr;
  mHeaderValue2 = nullptr;
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
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Str2GroupHandler::read_value(TokenType value_type,
			     const FileRegion& value_loc,
			     int count)
{
  if ( count == 0 ) {
    if ( value_type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    else {
      mHeaderValue1 = mgr().new_string(value_loc, ShString(parser().cur_string()));
      return true;
    }
  }
  else if ( count == 1 ) {
    if ( value_type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    else {
      mHeaderValue2 = mgr().new_string(value_loc, ShString(parser().cur_string()));
      return true;
    }
  }
  else {
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


//////////////////////////////////////////////////////////////////////
// クラス Str2IntGroupHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str2IntGroupHandler::Str2IntGroupHandler(DotlibParser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
Str2IntGroupHandler::~Str2IntGroupHandler()
{
}

// @brief ヘッダの値をクリアする．
void
Str2IntGroupHandler::clear_header()
{
  mHeaderValue1 = nullptr;
  mHeaderValue2 = nullptr;
  mHeaderValue3 = nullptr;
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
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Str2IntGroupHandler::read_value(TokenType value_type,
				const FileRegion& value_loc,
				int count)
{
  if ( count == 0 ) {
    if ( value_type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    else {
      mHeaderValue1 = mgr().new_string(value_loc, ShString(parser().cur_string()));
      return true;
    }
  }
  else if ( count == 1 ) {
    if ( value_type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    else {
      mHeaderValue2 = mgr().new_string(value_loc, ShString(parser().cur_string()));
      return true;
    }
  }
  else if ( count == 2 ) {
    if ( value_type != TokenType::INT_NUM ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "integer value is expected.");
      return false;
    }
    else {
      mHeaderValue3 = mgr().new_int(value_loc, parser().cur_int());
      return true;
    }
  }
  else {
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
