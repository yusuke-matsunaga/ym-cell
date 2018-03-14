
/// @file TimingSenseHandler.cc
/// @brief TimingSenseHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "HandlerFactory.h"
#include "TimingSenseHandler.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "AstTimingSense.h"
#include "TokenType.h"
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
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
TimingSenseHandler::~TimingSenseHandler()
{
}

// @brief 値を読み込む．
AstNode*
TimingSenseHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. timing sense value is expected.");
    return nullptr;
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
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. Only 'positive_unate', 'negative_unate', or 'non_unate' are allowed here.");
    return nullptr;
  }

  return mgr().new_timing_sense(loc, value);
}

END_NAMESPACE_YM_DOTLIB
