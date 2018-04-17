
/// @file TimingSenseHandler.cc
/// @brief TimingSenseHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HandlerFactory.h"
#include "TimingSenseHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstTimingSense.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'timing sense' 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_timing_sense(DotlibParser& parser)
{
  return new TimingSenseHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス TimingSenseHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingSenseHandler::TimingSenseHandler(DotlibParser& parser) :
  SimpleHandler(parser)
{
  clear_value();
}

// @brief デストラクタ
TimingSenseHandler::~TimingSenseHandler()
{
}

// @brief 値をクリアする．
void
TimingSenseHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstTimingSense*
TimingSenseHandler::value() const
{
  return mValue;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
TimingSenseHandler::read_value(TokenType value_type,
			       const FileRegion& value_loc)
{
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. timing sense value is expected.");
    return false;
  }
  const char* str = parser().cur_string();
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
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. Only 'positive_unate', 'negative_unate', or 'non_unate' are allowed here.");
    return false;
  }

  mValue = mgr().new_timing_sense(loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
