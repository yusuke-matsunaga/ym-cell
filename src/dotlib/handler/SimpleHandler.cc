﻿
/// @file SimpleHandler.cc
/// @brief SimpleHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/HandlerFactory.h"
#include "SimpleHandler.h"
#include "DotlibParserImpl.h"
#include "DotlibMgrImpl.h"
#include "GroupHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス SimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
// @param[in] sym_mode シンボルモード
//
// シンボルモードの時は数字で始まっていても文字列とみなす．
SimpleHandler::SimpleHandler(DotlibParser& parser,
			     bool sym_mode) :
  DotlibHandler(parser),
  mSymMode(sym_mode)
{
}

// @brief デストラクタ
SimpleHandler::~SimpleHandler()
{
}

// @brief 構文要素を処理する．
// @param[in] attr_name 属性名
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ属性値を返す．
//
// エラーが起きたら false を返す．
DotlibNode*
SimpleHandler::read_attr(AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( !expect(COLON) ) {
    return nullptr;
  }

  DotlibNode* value = read_value();
  if ( value == nullptr ) {
    return nullptr;
  }
  if ( !expect_nl() ) {
    return nullptr;
  }

  if ( debug() ) {
    cout << attr_type << " : " << value << endl;
  }

  return value;
}

// @brief 値を読み込む処理
// @return 値を表す DotlibNode を返す．
// @note エラーが起きたら nullptr を返す．
// @note デフォルトの実装では普通に DotlibParser::read_token() を呼ぶ．
DotlibNode*
SimpleHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, mSymMode);
  DotlibNode* value = new_value(value_type, false, loc);
  return value;
}


//////////////////////////////////////////////////////////////////////
// クラス StrSimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
// @param[in] sym_mode シンボルモード
// @note シンボルモードの時は数字で始まっていても文字列とみなす．
StrSimpleHandler::StrSimpleHandler(DotlibParser& parser,
				   bool sym_mode) :
  SimpleHandler(parser, sym_mode)
{
}

// @brief デストラクタ
StrSimpleHandler::~StrSimpleHandler()
{
}

// @brief 値を読み込む．
DotlibNode*
StrSimpleHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. string value is expected.");
    return nullptr;
  }
  return mgr()->new_string(loc, ShString(parse().cur_string()));
}


//////////////////////////////////////////////////////////////////////
// クラス IntSimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntSimpleHandler::IntSimpleHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
IntSimpleHandler::~IntSimpleHandler()
{
}

// @brief 値を読み込む．
DotlibNode*
IntSimpleHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != INT ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. int value is expected.");
    return nullptr;
  }
  return mgr()->new_int(loc, parse().cur_int());
}


//////////////////////////////////////////////////////////////////////
// クラス FloatSimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatSimpleHandler::FloatSimpleHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
FloatSimpleHandler::~FloatSimpleHandler()
{
}

// @brief 値を読み込む．
DotlibNode*
FloatSimpleHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != FLOAT ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. float value is expected.");
    return nullptr;
  }
  return mgr()->new_float(loc, parser().cur_float());
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
DotlibNode*
TechnologyHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
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
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. only 'asic' or 'fpga' are allowed.");
    return nullptr;
  }

  return mgr()->new_technology(loc, value);
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
DotlibNode*
DelayModelHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
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
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  return mgr()->new_delay_model(loc, value);
}


//////////////////////////////////////////////////////////////////////
// クラス CellPinDirectionHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
CellPinDirectionHandler::CellPinDirectionHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
CellPinDirectionHandler::~CellPinDirectionHandler()
{
}

// @brief 値を読み込む．
DotlibNode*
CellPinDirectionHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. direction value is expected.");
    return nullptr;
  }
  const char* str = parser().cur_string();
  ClibCellPinDirection value;
  if ( strcmp(str, "input") == 0 ) {
    value = kClibCellPinInput;
  }
  else if ( strcmp(str, "output") == 0 ) {
    value = kClibCellPinOutput;
  }
  else if ( strcmp(str, "inout") == 0 ) {
    value = kClibCellPinInout;
  }
  else if ( strcmp(str, "internal") == 0 ) {
    value = kClibCellPinInternal;
  }
  else {
    ostringstream buf;
    buf << value << ": Illegal value for 'direction'."
	<< " 'input', 'output', 'inout' or 'internal' are expected.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  return mgr()->new_cell_pin_direction(loc, value);
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
DotlibNode*
TimingSenseHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != SYMBOL ) {
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

  return mgr()->new_timing_sense(loc, value);
}


//////////////////////////////////////////////////////////////////////
// クラス TimingTypeHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingTypeHandler::TimingTypeHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
TimingTypeHandler::~TimingTypeHandler()
{
}

// @brief 値を読み込む．
DotlibNode*
TimingTypeHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. timing type value is expected.");
    return nullptr;
  }
  const char* str = parser().cur_string();
  ClibTimingType value;
  if ( strcmp(str, "combinational") == 0 ) {
    value = kClibTimingCombinational;
  }
  else if ( strcmp(str, "combinational_rise") == 0 ) {
    value = kClibTimingCombinationalRise;
  }
  else if ( strcmp(str, "combinational_fall") == 0 ) {
    value = kClibTimingCombinationalFall;
  }
  else if ( strcmp(str, "three_state_enable") == 0 ) {
    value = kClibTimingThreeStateEnable;
  }
  else if ( strcmp(str, "three_state_enable_rise") == 0 ) {
    value = kClibTimingThreeStateEnableRise;
  }
  else if ( strcmp(str, "three_state_enable_fall") == 0 ) {
    value = kClibTimingThreeStateEnableFall;
  }
  else if ( strcmp(str, "three_state_disable") == 0 ) {
    value = kClibTimingThreeStateDisable;
  }
  else if ( strcmp(str, "three_state_disable_rise") == 0 ) {
    value = kClibTimingThreeStateDisableRise;
  }
  else if ( strcmp(str, "three_state_disable_fall") == 0 ) {
    value = kClibTimingThreeStateDisableFall;
  }
  else if ( strcmp(str, "rising_edge") == 0 ) {
    value = kClibTimingRisingEdge;
  }
  else if ( strcmp(str, "falling_edge") == 0 ) {
    value = kClibTimingFallingEdge;
  }
  else if ( strcmp(str, "preset") == 0 ) {
    value = kClibTimingPreset;
  }
  else if ( strcmp(str, "clear") == 0 ) {
    value = kClibTimingClear;
  }
  else if ( strcmp(str, "hold_rising") == 0 ) {
    value = kClibTimingHoldRising;
  }
  else if ( strcmp(str, "hold_falling") == 0 ) {
    value = kClibTimingHoldFalling;
  }
  else if ( strcmp(str, "setup_rising") == 0 ) {
    value = kClibTimingSetupRising;
  }
  else if ( strcmp(str, "setup_falling") == 0 ) {
    value = kClibTimingSetupFalling;
  }
  else if ( strcmp(str, "recovery_rising") == 0 ) {
    value = kClibTimingRecoveryRising;
  }
  else if ( strcmp(str, "recovery_falling") == 0 ) {
    value = kClibTimingRecoveryFalling;
  }
  else if ( strcmp(str, "skew_rising") == 0 ) {
    value = kClibTimingSkewRising;
  }
  else if ( strcmp(str, "skew_falling") == 0 ) {
    value = kClibTimingSkewFalling;
  }
  else if ( strcmp(str, "removal_rising") == 0 ) {
    value = kClibTimingRemovalRising;
  }
  else if ( strcmp(str, "removal_falling") == 0 ) {
    value = kClibTimingRemovalFalling;
  }
  else if ( strcmp(str, "non_seq_setup_rising") == 0 ) {
    value = kClibTimingNonSeqSetupRising;
  }
  else if ( strcmp(str, "non_seq_setup_falling") == 0 ) {
    value = kClibTimingNonSeqSetupFalling;
  }
  else if ( strcmp(str, "non_seq_hold_rising") == 0 ) {
    value = kClibTimingNonSeqHoldRising;
  }
  else if ( strcmp(str, "non_seq_hold_falling") == 0 ) {
    value = kClibTimingNonSeqHoldFalling;
  }
  else if ( strcmp(str, "nochange_high_high") == 0 ) {
    value = kClibTimingNochangeHighHigh;
  }
  else if ( strcmp(str, "nochange_high_low") == 0 ) {
    value = kClibTimingNochangeHighLow;
  }
  else if ( strcmp(str, "nochange_low_high") == 0 ) {
    value = kClibTimingNochangeLowHigh;
  }
  else if ( strcmp(str, "nochange_low_low") == 0 ) {
    value = kClibTimingNochangeLowLow;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. Illegal string for timing type.");
    return nullptr;
  }

  return mgr()->new_timing_type(loc, value);
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
DotlibNode*
VarTypeHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != SYMBOL ) {
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

  return mgr()->new_var_type(loc, value);
}

END_NAMESPACE_YM_DOTLIB