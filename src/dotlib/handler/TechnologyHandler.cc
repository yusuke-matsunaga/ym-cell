
/// @file TechnologyHandler.cc
/// @brief TechnologyHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "HandlerFactory.h"
#include "TechnologyHandler.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "AstTechnology.h"
#include "TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'technology' 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_technology(DotlibParser& parser)
{
  return new TechnologyHandler(parser);
}

//////////////////////////////////////////////////////////////////////
// クラス TechnologyHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TechnologyHandler::TechnologyHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
TechnologyHandler::~TechnologyHandler()
{
}

// @brief 値を読み込む．
AstNode*
TechnologyHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. technology value is expected.");
    return nullptr;
  }
  const char* str = parser().cur_string();
  ClibTechnology value;
  if ( strcmp(str, "cmos") == 0 ) {
    value = kClibTechCmos;
  }
  else if ( strcmp(str, "fpga") == 0 ) {
    value = kClibTechFpga;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. only 'asic' or 'fpga' are allowed.");
    return nullptr;
  }

  return mgr().new_technology(loc, value);
}

END_NAMESPACE_YM_DOTLIB
