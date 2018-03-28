
/// @file DelayModelHandler.cc
/// @brief DelayModelHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "HandlerFactory.h"
#include "DelayModelHandler.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "AstDelayModel.h"
#include "TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'delay model' 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_delay_model(DotlibParser& parser)
{
  return new DelayModelHandler(parser);
}

//////////////////////////////////////////////////////////////////////
// クラス DelayModelHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
DelayModelHandler::DelayModelHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
DelayModelHandler::~DelayModelHandler()
{
}

// @brief 値を読み込む．
AstNode*
DelayModelHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. delay_model value is expected.");
    return nullptr;
  }
  const char* str = parser().cur_string();
  ClibDelayModel value;
  if ( strcmp(str, "generic_cmos") == 0 ) {
    value = kClibDelayGenericCmos;
  }
  else if ( strcmp(str, "table_lookup") == 0 ) {
    value = kClibDelayTableLookup;
  }
  else if ( strcmp(str, "piecewise_cmos") == 0 ) {
    value = kClibDelayPiecewiseCmos;
  }
  else if ( strcmp(str, "cmos2") == 0 ) {
    value = kClibDelayCmos2;
  }
  else if ( strcmp(str, "dcm") == 0 ) {
    value = kClibDelayDcm;
  }
  else {
    ostringstream buf;
    buf << str << ": Illegal value for 'delay_model'."
	<< " 'generic_cmos', 'table_lookup', "
	<< "'piecewise_cmos', 'cmos2' or 'dcm' are expected.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  return mgr().new_delay_model(loc, value);
}

END_NAMESPACE_YM_DOTLIB
