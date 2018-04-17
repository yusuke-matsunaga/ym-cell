
/// @file SimpleHandler.cc
/// @brief SimpleHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HandlerFactory.h"
#include "SimpleHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstString.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

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
SimpleHandler::SimpleHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
SimpleHandler::~SimpleHandler()
{
}

// @brief 構文要素を処理する．
// @param[in] attr_name 属性名
// @param[in] attr_loc ファイル上の位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
SimpleHandler::parse_attr_value(AttrType attr_type,
				const FileRegion& attr_loc)
{
  if ( !expect(TokenType::COLON) ) {
    return false;
  }

  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( !read_value(value_type, loc) ) {
    return false;
  }

  if ( !expect_nl() ) {
    return false;
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス StrSimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrSimpleHandler::StrSimpleHandler(DotlibParser& parser) :
  SimpleHandler(parser)
{
  clear_value();
}

// @brief デストラクタ
StrSimpleHandler::~StrSimpleHandler()
{
}

// @brief 値をクリアする．
void
StrSimpleHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstString*
StrSimpleHandler::value() const
{
  return mValue;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
StrSimpleHandler::read_value(TokenType value_type,
			     const FileRegion& value_loc)
{
  if ( value_type == TokenType::SYMBOL ) {
    mValue = mgr().new_string(value_loc, ShString(parser().cur_string()));
    return true;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. string value is expected.");
    return false;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス IntSimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntSimpleHandler::IntSimpleHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
  clear_value();
}

// @brief デストラクタ
IntSimpleHandler::~IntSimpleHandler()
{
}

// @brief 値をクリアする．
void
IntSimpleHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstInt*
IntSimpleHandler::value() const
{
  return mValue;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
IntSimpleHandler::read_value(TokenType value_type,
			     const FileRegion& value_loc)
{
  if ( value_type == TokenType::INT_NUM ) {
    mValue = mgr().new_int(value_loc, parser().cur_int());
    return true;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. int value is expected.");
    return false;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス FloatSimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatSimpleHandler::FloatSimpleHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
  clear_value();
}

// @brief デストラクタ
FloatSimpleHandler::~FloatSimpleHandler()
{
}

// @brief 値をクリアする．
void
FloatSimpleHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstFloat*
FloatSimpleHandler::value() const
{
  return mValue;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
FloatSimpleHandler::read_value(TokenType value_type,
			       const FileRegion& value_loc)
{
  if ( value_type == TokenType::FLOAT_NUM || value_type == TokenType::INT_NUM ) {
    mValue = mgr().new_float(value_loc, parser().cur_float());
    return true;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. float value is expected.");
    return false;
  }
}

END_NAMESPACE_YM_DOTLIB
