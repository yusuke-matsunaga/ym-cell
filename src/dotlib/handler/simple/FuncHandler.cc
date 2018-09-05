
/// @file FuncHandler.cc
/// @brief FuncHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/FuncHandler.h"
#include "FuncParser.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FuncHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FuncHandler::FuncHandler(DotlibParser& parser) :
  SimpleHandler(parser)
{
}

// @brief デストラクタ
FuncHandler::~FuncHandler()
{
}

// @brief int 値の記述をパースする．
//
// エラーが起きた場合には nullptr が返される．
const AstExpr*
FuncHandler::parse_value()
{
  bool stat = parse_simple_attribute();
  if ( stat ) {
    return mValue;
  }
  else {
    return nullptr;
  }
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
FuncHandler::read_value(TokenType value_type,
			const FileRegion& value_loc)
{
  if ( value_type != TokenType::SYMBOL ) {
    mValue = nullptr;
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "String value is expected.");
    return false;
  }

  FuncParser read(cur_string(), value_loc, mgr());

  mValue = read();

  if ( mValue == nullptr ) {
    return false;
  }
  return true;
}

END_NAMESPACE_YM_DOTLIB
