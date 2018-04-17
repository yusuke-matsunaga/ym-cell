﻿
/// @file VarTypeHandler.cc
/// @brief VarTypeHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HandlerFactory.h"
#include "VarTypeHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstVarType.h"
#include "dotlib/TokenType.h"
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
  SimpleHandler(parser)
{
  clear_value();
}

// @brief デストラクタ
VarTypeHandler::~VarTypeHandler()
{
}

// @brief 値をクリアする．
void
VarTypeHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstVarType*
VarTypeHander::value() const
{
  return mValue;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
VarTypeHandler::read_value(TokenType value_type,
			   const FileRegion& value_loc)
{
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
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
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  mValue = mgr().new_var_type(loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
