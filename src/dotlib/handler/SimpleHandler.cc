
/// @file SimpleHandler.cc
/// @brief SimpleHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "SimpleHandler.h"
#include "IntHandler.h"
#include "FloatHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloat.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス SimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
// @param[in] sym_mode シンボルモード
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
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
SimpleHandler::parse_attr_value()
{
  if ( !expect(TokenType::COLON) ) {
    return false;
  }

  FileRegion value_loc;
  TokenType value_type = parser().read_token(value_loc, mSymMode);
  if ( !read_value(value_type, value_loc) ) {
    return false;
  }

  if ( !expect_nl() ) {
    return false;
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス IntHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntHandler::IntHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
  clear_value();
}

// @brief デストラクタ
IntHandler::~IntHandler()
{
}

// @brief 値をクリアする．
void
IntHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstInt*
IntHandler::value() const
{
  return mValue;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
IntHandler::read_value(TokenType value_type,
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
// クラス FloatHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatHandler::FloatHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
  clear_value();
}

// @brief デストラクタ
FloatHandler::~FloatHandler()
{
}

// @brief 値をクリアする．
void
FloatHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstFloat*
FloatHandler::value() const
{
  return mValue;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
FloatHandler::read_value(TokenType value_type,
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
