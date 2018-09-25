
/// @file StrBaseHandler.cc
/// @brief StrBaseHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/StrBaseHandler.h"
//#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrBaseHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrBaseHandler::StrBaseHandler(DotlibParser& parser) :
  SimpleHandler(parser)
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
    return read_str_value(cur_string(), value_loc);
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

END_NAMESPACE_YM_DOTLIB
