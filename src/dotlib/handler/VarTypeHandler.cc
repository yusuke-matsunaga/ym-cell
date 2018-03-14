
/// @file VarTypeHandler.cc
/// @brief VarTypeHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "HandlerFactory.h"
#include "VarTypeHandler.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "AstVarType.h"
#include "TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'var type' 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_var_type(DotlibParser& parser)
{
  return new VarTypeHandler(parser);
}

//////////////////////////////////////////////////////////////////////
// クラス VarTypeHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
VarTypeHandler::VarTypeHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
VarTypeHandler::~VarTypeHandler()
{
}

// @brief 値を読み込む．
AstNode*
VarTypeHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. technology value is expected.");
    return nullptr;
  }
  const char* str = parser().cur_string();
  ClibVarType value;
  if ( strcmp(str, "input_net_transition") == 0 ) {
    value = kClibVarInputNetTransition;
  }
  else if ( strcmp(str, "total_output_net_capacitance") == 0 ) {
    value = kClibVarTotalOutputNetCapacitance;
  }
  else if ( strcmp(str, "equal_or_opposite_output_net_capacitance") == 0 ) {
    value = kClibVarEqualOrOppositeOutputNetCapacitance;
  }
  else if ( strcmp(str, "input_transition_time") == 0 ) {
    value = kClibVarInputTransitionTime;
  }
  else if ( strcmp(str, "output_net_length") == 0 ) {
    value = kClibVarOutputNetLength;
  }
  else if ( strcmp(str, "output_net_wire_cap") == 0 ) {
    value = kClibVarOutputNetWireCap;
  }
  else if ( strcmp(str, "output_net_pin_cap") == 0 ) {
    value = kClibVarOutputNetPinCap;
  }
  else if ( strcmp(str, "related_out_total_output_net_capacitance") == 0 ) {
    value = kClibVarRelatedOutTotalOutputNetCapacitance;
  }
  else if ( strcmp(str, "related_out_output_net_length") == 0 ) {
    value = kClibVarRelatedOutOutputNetLength;
  }
  else if ( strcmp(str, "related_out_output_net_wire_cap") == 0 ) {
    value = kClibVarRelatedOutOutputNetWireCap;
  }
  else if ( strcmp(str, "related_out_output_net_pin_cap") == 0 ) {
    value = kClibVarRelatedOutOutputNetPinCap;
  }
  else if ( strcmp(str, "constrained_pin_transition") == 0 ) {
    value = kClibVarConstrainedPinTransition;
  }
  else if ( strcmp(str, "related_pin_transition") == 0 ) {
    value = kClibVarRelatedPinTransition;
  }
  else {
    ostringstream buf;
    buf << "Syntax error. "
	<< str << " is not a valid string for variable type.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  return mgr().new_var_type(loc, value);
}

END_NAMESPACE_YM_DOTLIB
