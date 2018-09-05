
/// @file BoolHandler.cc
/// @brief BoolHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/BoolHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス BoolHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
BoolHandler::BoolHandler(DotlibParser& parser) :
  StrBaseHandler(parser)
{
}

// @brief デストラクタ
BoolHandler::~BoolHandler()
{
}

// @brief ブール値の記述をパースする．
//
// エラーが起きた場合には nullptr が返される．
const AstBool*
BoolHandler::parse_value()
{
  bool stat = parse_simple_attribute();
  if ( stat ) {
    return mValue;
  }
  else {
    return nullptr;
  }
}

// @brief 文字列を読み込んだ時の処理
// @param[in] str 文字列
// @param[in] value_loc 文字列トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
BoolHandler::read_str_value(const char* str,
			    const FileRegion& value_loc)
{
  bool value;
  if ( strcmp(str, "true") == 0 ) {
    value = true;
  }
  else if ( strcmp(str, "false") == 0 ) {
    value = false;
  }
  else {
    mValue = nullptr;
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. only 'true' or 'false' are allowed.");
    return false;
  }

  mValue = mgr().new_bool(value_loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
