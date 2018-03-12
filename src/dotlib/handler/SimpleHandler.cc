
/// @file SimpleHandler.cc
/// @brief SimpleHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HandlerFactory.h"
#include "SimpleHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス SimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
// @param[in] sym_mode シンボルモード
//
// シンボルモードの時は数字で始まっていても文字列とみなす．
SimpleHandler::SimpleHandler(DotlibParser& parser,
			     bool sym_mode) :
  DotlibHandler(parser),
  mSymMode(sym_mode)
{
}

// @brief デストラクタ
SimpleHandler::~SimpleHandler()
{
}

// @brief 構文要素を処理する．
// @param[in] attr_name 属性名
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ属性値を返す．
//
// エラーが起きたら false を返す．
DotlibNode*
SimpleHandler::read_attr(AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( !expect(TokenType::COLON) ) {
    return nullptr;
  }

  DotlibNode* value = read_value();
  if ( value == nullptr ) {
    return nullptr;
  }
  if ( !expect_nl() ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << attr_type << " : " << value << endl;
  }

  return value;
}

// @brief 値を読み込む処理
// @return 値を表す DotlibNode を返す．
// @note エラーが起きたら nullptr を返す．
// @note デフォルトの実装では普通に DotlibParser::read_token() を呼ぶ．
DotlibNode*
SimpleHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, mSymMode);
  DotlibNode* value = new_value(loc, value_type, false);
  return value;
}


//////////////////////////////////////////////////////////////////////
// クラス StrSimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
// @param[in] sym_mode シンボルモード
// @note シンボルモードの時は数字で始まっていても文字列とみなす．
StrSimpleHandler::StrSimpleHandler(DotlibParser& parser,
				   bool sym_mode) :
  SimpleHandler(parser, sym_mode)
{
}

// @brief デストラクタ
StrSimpleHandler::~StrSimpleHandler()
{
}

// @brief 値を読み込む．
DotlibNode*
StrSimpleHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type == TokenType::SYMBOL ) {
    return mgr()->new_string(loc, ShString(parser().cur_string()));
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  kMsgError,
		  "DOTLIB_PARSER",
		  "Syntax error. string value is expected.");
  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス IntSimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntSimpleHandler::IntSimpleHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
IntSimpleHandler::~IntSimpleHandler()
{
}

// @brief 値を読み込む．
DotlibNode*
IntSimpleHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type == TokenType::INT_NUM ) {
    return mgr()->new_int(loc, parser().cur_int());
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  kMsgError,
		  "DOTLIB_PARSER",
		  "Syntax error. int value is expected.");
  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス FloatSimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatSimpleHandler::FloatSimpleHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
FloatSimpleHandler::~FloatSimpleHandler()
{
}

// @brief 値を読み込む．
DotlibNode*
FloatSimpleHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type == TokenType::FLOAT_NUM ) {
    return mgr()->new_float(loc, parser().cur_float());
  }
  if ( value_type == TokenType::INT_NUM ) {
    return mgr()->new_int(loc, parser().cur_int());
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  kMsgError,
		  "DOTLIB_PARSER",
		  "Syntax error. float value is expected.");
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
