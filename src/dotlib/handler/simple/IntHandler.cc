﻿
/// @file IntHandler.cc
/// @brief IntHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/IntHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IntHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntHandler::IntHandler(DotlibParser& parser) :
  SimpleHandler(parser)
{
}

// @brief デストラクタ
IntHandler::~IntHandler()
{
}

// @brief int 値の記述をパースする．
// @param[in] dst 読み込んだ値を格納する変数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
IntHandler::parse_value(const AstInt*& dst)
{
  bool stat = parse_simple_attribute();
  if ( stat ) {
    dst = mValue;
  }
  return stat;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
bool
IntHandler::read_value(TokenType value_type,
		       const FileRegion& value_loc)
{
  if ( value_type == TokenType::INT_NUM ) {
    mValue = mgr().new_int(value_loc, cur_int());
    return true;
  }
  else {
    mValue = nullptr;
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. int value is expected.");
    return false;
  }
}

END_NAMESPACE_YM_DOTLIB