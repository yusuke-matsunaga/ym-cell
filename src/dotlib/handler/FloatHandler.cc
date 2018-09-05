
/// @file FloatHandler.cc
/// @brief FloatHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "FloatHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FloatHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatHandler::FloatHandler(DotlibParser& parser) :
  SimpleHandler(parser)
{
}

// @brief デストラクタ
FloatHandler::~FloatHandler()
{
}

// @brief float 値の記述をパースする．
// @return 読み込んだ値を返す．
//
// エラーの場合には nullptr を返す．
const AstFloat*
FloatHandler::parse_value()
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
bool
FloatHandler::read_value(TokenType value_type,
			 const FileRegion& value_loc)
{
  if ( value_type == TokenType::FLOAT_NUM || value_type == TokenType::INT_NUM ) {
    mValue = mgr().new_float(value_loc, cur_float());
    return true;
  }
  else {
    mValue = nullptr;
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. float value is expected.");
    return false;
  }
}

END_NAMESPACE_YM_DOTLIB
