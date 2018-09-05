
/// @file TimingSenseHandler.cc
/// @brief TimingSenseHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "TimingSenseHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TimingSenseHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingSenseHandler::TimingSenseHandler(DotlibParser& parser) :
  StrBaseHandler(parser)
{
}

// @brief デストラクタ
TimingSenseHandler::~TimingSenseHandler()
{
}

// @brief timing_sense の記述をパースする．
//
/// エラーが起きた場合には nullptr が返される．
const AstTimingSense*
TimingSenseHandler::parse_value()
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
TimingSenseHandler::read_str_value(const char* str,
				   const FileRegion& value_loc)
{
  ClibTimingSense value;
  if ( strcmp(str, "positive_unate") == 0 ) {
    value = kClibPosiUnate;
  }
  else if ( strcmp(str, "negative_unate") == 0 ) {
    value = kClibNegaUnate;
  }
  else if ( strcmp(str, "non_unate") == 0 ) {
    value = kClibNonUnate;
  }
  else {
    mValue = nullptr;
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. Only 'positive_unate', 'negative_unate', or 'non_unate' are allowed here.");
    return false;
  }

  mValue = mgr().new_timing_sense(value_loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
