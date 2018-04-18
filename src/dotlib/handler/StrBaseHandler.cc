
/// @file StrBaseHandler.cc
/// @brief StrBaseHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "StrBaseHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrBaseHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrBaseHandler::StrBaseHandler(DotlibParser& parser,
			       bool sym_mode) :
  SimpleHandler(parser, sym_mode)
{
}

// @brief デストラクタ
StrBaseHandler::~StrBaseHandler()
{
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
StrBaseHandler::read_value(TokenType value_type,
			   const FileRegion& value_loc)
{
  if ( value_type == TokenType::SYMBOL ) {
    return read_str_value(parser().cur_string(), value_loc);
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
// クラス StrHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrHandler::StrHandler(DotlibParser& parser) :
  StrBaseHandler(parser, true)
{
  clear_value();
}

// @brief デストラクタ
StrHandler::~StrHandler()
{
}

// @brief 値をクリアする．
void
StrHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstString*
StrHandler::value() const
{
  return mValue;
}

// @brief 文字列を読み込んだ時の処理
// @param[in] str 文字列
// @param[in] value_loc 文字列トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
StrHandler::read_str_value(const char* str,
			   const FileRegion& value_loc)
{
  mValue = mgr().new_string(value_loc, ShString(str));
  return true;
}

END_NAMESPACE_YM_DOTLIB
