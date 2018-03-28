
/// @file SimpleHandler.cc
/// @brief SimpleHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "HandlerFactory.h"
#include "SimpleHandler.h"
#include "DotlibParser.h"
#include "TokenType.h"
#include "AstMgr.h"
#include "AstInt.h"
#include "AstFloat.h"
#include "AstString.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ダミーの simple ハンドラを作る．
DotlibHandler*
HandlerFactory::new_simple(DotlibParser& parser)
{
  return new SimpleHandler(parser, false);
}

// @brief string 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_string(DotlibParser& parser,
			   bool sym_mode)
{
  return new StrSimpleHandler(parser, sym_mode);
}

// @brief int 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_int(DotlibParser& parser)
{
  return new IntSimpleHandler(parser);
}

// @brief float 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_float(DotlibParser& parser)
{
  return new FloatSimpleHandler(parser);
}


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
AstNode*
SimpleHandler::parse_attr_value(AttrType attr_type,
				const FileRegion& attr_loc)
{
  if ( !expect(TokenType::COLON) ) {
    return nullptr;
  }

  AstNode* value = gen_node();
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
// @return 値を表す AstNode を返す．
//
// エラーが起きたら nullptr を返す．
AstNode*
SimpleHandler::gen_node()
{
  return nullptr;
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

// @brief AstString を作る．
AstNode*
StrSimpleHandler::gen_node()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type == TokenType::SYMBOL ) {
    return mgr().new_string(loc, ShString(parser().cur_string()));
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
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

// @brief AstInt を作る．
AstNode*
IntSimpleHandler::gen_node()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type == TokenType::INT_NUM ) {
    return mgr().new_int(loc, parser().cur_int());
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
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

// @brief AstFloat を作る．
AstNode*
FloatSimpleHandler::gen_node()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type == TokenType::FLOAT_NUM || value_type == TokenType::INT_NUM ) {
    return mgr().new_float(loc, parser().cur_float());
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. float value is expected.");
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
