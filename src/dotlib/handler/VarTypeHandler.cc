
/// @file VarTypeHandler.cc
/// @brief VarTypeHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "VarTypeHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス VarTypeHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
VarTypeHandler::VarTypeHandler(DotlibParser& parser) :
  StrBaseHandler(parser)
{
}

// @brief デストラクタ
VarTypeHandler::~VarTypeHandler()
{
}

// @brief var_type の記述をパースする．
//
// エラーが起きた場合には nullptr が返される．
const AstVarType*
VarTypeHandler::parse_value()
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
VarTypeHandler::read_str_value(const char* str,
			       const FileRegion& value_loc)
{
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
    mValue = nullptr;
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

  mValue = mgr().new_var_type(value_loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
