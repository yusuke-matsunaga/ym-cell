
/// @file Scanner_value.cc
/// @brief Scanner の実装ファイル(値の読み込み)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2019, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Scanner.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief int 型を値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーの時は nullptr を返す．
AstValuePtr
Scanner::read_int()
{
  Token value_token{read_token()};
  if ( value_token.type() == TokenType::INT_NUM ) {
    return AstValue::new_int(cur_int(), value_token.loc());
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_token.loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'integer' value is expected.");
    return {};
  }
}

// @brief float 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_float()
{
  Token value_token{read_token()};
  // int 型も float 型とみなす．
  if ( value_token.type() == TokenType::FLOAT_NUM || value_token.type() == TokenType::INT_NUM ) {
    return AstValue::new_float(cur_float(), value_token.loc());
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_token.loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'float' value is expected.");
    return {};
  }
}

// @brief string 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_string()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  if ( tmp_str ) {
    return AstValue::new_string(ShString(tmp_str), value_loc);
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return {};
  }
}

// @brief bool 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_bool()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  if ( tmp_str != nullptr ) {
    if ( strcmp(tmp_str, "true") == 0 ) {
      return AstValue::new_bool(true, value_loc);
    }
    if ( strcmp(tmp_str, "false") == 0 ) {
      return AstValue::new_bool(false, value_loc);
    }
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  value_loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. only 'true' or 'false' are allowed.");
  return {};
}

// @brief delay_model 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_delay_model()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  ClibDelayModel value{ClibDelayModel::None};
  if ( tmp_str != nullptr ) {
    if ( strcmp(tmp_str, "generic_cmos") == 0 ) {
      value = ClibDelayModel::GenericCmos;
    }
    else if ( strcmp(tmp_str, "table_lookup") == 0 ) {
      value = ClibDelayModel::TableLookup;
    }
    else if ( strcmp(tmp_str, "piecewise_cmos") == 0 ) {
      value = ClibDelayModel::PiecewiseCmos;
    }
    else if ( strcmp(tmp_str, "cmos2") == 0 ) {
      value = ClibDelayModel::Cmos2;
    }
    else if ( strcmp(tmp_str, "dcm") == 0 ) {
      value = ClibDelayModel::Dcm;
    }
  }
  if ( value == ClibDelayModel::None ) {
    ostringstream buf;
    buf << tmp_str << ": Illegal value for 'delay_model'."
	<< " 'generic_cmos', 'table_lookup', "
	<< "'piecewise_cmos', 'cmos2' or 'dcm' are expected.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return {};
  }

  return AstValue::new_delay_model(value, value_loc);
}

// @brief direction 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_direction()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  ClibDirection value{ClibDirection::None};
  if ( tmp_str != nullptr ) {
    if ( strcmp(tmp_str, "input") == 0 ) {
      value = ClibDirection::Input;
    }
    else if ( strcmp(tmp_str, "output") == 0 ) {
      value = ClibDirection::Output;
    }
    else if ( strcmp(tmp_str, "inout") == 0 ) {
      value = ClibDirection::Inout;
    }
    else if ( strcmp(tmp_str, "internal") == 0 ) {
      value = ClibDirection::Internal;
    }
  }
  if ( value == ClibDirection::None ) {
    ostringstream buf;
    buf << tmp_str << ": Illegal value for 'direction'."
	<< " 'input', 'output', 'inout' or 'internal' are expected.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return {};
  }

  return AstValue::new_direction(value, value_loc);
}

// @brief technology 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_technology()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  ClibTechnology value{ClibTechnology::none};
  if ( tmp_str != nullptr ) {
    if ( strcmp(tmp_str, "cmos") == 0 ) {
      value = ClibTechnology::cmos;
    }
    else if ( strcmp(tmp_str, "fpga") == 0 ) {
      value = ClibTechnology::fpga;
    }
  }
  if ( value == ClibTechnology::none ) {
    ostringstream buf;
    buf << tmp_str << ": Illegal value for 'technology'. "
	<< " Only 'cmos' or 'fpga' are allowed here.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return {};
  }

  return AstValue::new_technology(value, value_loc);
}

// @brief timing_sense 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_timing_sense()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  ClibTimingSense value{ClibTimingSense::None};
  if ( tmp_str != nullptr ) {
    if ( strcmp(tmp_str, "positive_unate") == 0 ) {
      value = ClibTimingSense::PosiUnate;
    }
    else if ( strcmp(tmp_str, "negative_unate") == 0 ) {
      value = ClibTimingSense::NegaUnate;
    }
    else if ( strcmp(tmp_str, "non_unate") == 0 ) {
      value = ClibTimingSense::NonUnate;
    }
  }
  if ( value == ClibTimingSense::None ) {
    ostringstream buf;
    buf << tmp_str << ": Illegal value for 'timing_sense'."
	<< " Only 'positive_unate', 'negative_unate', or 'non_unate' are allowed here.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return {};
  }

  return AstValue::new_timing_sense(value, value_loc);
}

// @brief timing_type 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_timing_type()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  ClibTimingType value{ClibTimingType::None};
  if ( tmp_str != nullptr ) {
    if ( strcmp(tmp_str, "combinational") == 0 ) {
      value = ClibTimingType::Combinational;
    }
    else if ( strcmp(tmp_str, "combinational_rise") == 0 ) {
      value = ClibTimingType::CombinationalRise;
    }
    else if ( strcmp(tmp_str, "combinational_fall") == 0 ) {
      value = ClibTimingType::CombinationalFall;
    }
    else if ( strcmp(tmp_str, "three_state_enable") == 0 ) {
      value = ClibTimingType::ThreeStateEnable;
    }
    else if ( strcmp(tmp_str, "three_state_enable_rise") == 0 ) {
      value = ClibTimingType::ThreeStateEnableRise;
    }
    else if ( strcmp(tmp_str, "three_state_enable_fall") == 0 ) {
      value = ClibTimingType::ThreeStateEnableFall;
    }
    else if ( strcmp(tmp_str, "three_state_disable") == 0 ) {
      value = ClibTimingType::ThreeStateDisable;
    }
    else if ( strcmp(tmp_str, "three_state_disable_rise") == 0 ) {
      value = ClibTimingType::ThreeStateDisableRise;
    }
    else if ( strcmp(tmp_str, "three_state_disable_fall") == 0 ) {
      value = ClibTimingType::ThreeStateDisableFall;
    }
    else if ( strcmp(tmp_str, "rising_edge") == 0 ) {
      value = ClibTimingType::RisingEdge;
    }
    else if ( strcmp(tmp_str, "falling_edge") == 0 ) {
      value = ClibTimingType::FallingEdge;
    }
    else if ( strcmp(tmp_str, "preset") == 0 ) {
      value = ClibTimingType::Preset;
    }
    else if ( strcmp(tmp_str, "clear") == 0 ) {
      value = ClibTimingType::Clear;
    }
    else if ( strcmp(tmp_str, "hold_rising") == 0 ) {
      value = ClibTimingType::HoldRising;
    }
    else if ( strcmp(tmp_str, "hold_falling") == 0 ) {
      value = ClibTimingType::HoldFalling;
    }
    else if ( strcmp(tmp_str, "setup_rising") == 0 ) {
      value = ClibTimingType::SetupRising;
    }
    else if ( strcmp(tmp_str, "setup_falling") == 0 ) {
      value = ClibTimingType::SetupFalling;
    }
    else if ( strcmp(tmp_str, "recovery_rising") == 0 ) {
      value = ClibTimingType::RecoveryRising;
    }
    else if ( strcmp(tmp_str, "recovery_falling") == 0 ) {
      value = ClibTimingType::RecoveryFalling;
    }
    else if ( strcmp(tmp_str, "skew_rising") == 0 ) {
      value = ClibTimingType::SkewRising;
    }
    else if ( strcmp(tmp_str, "skew_falling") == 0 ) {
      value = ClibTimingType::SkewFalling;
    }
    else if ( strcmp(tmp_str, "removal_rising") == 0 ) {
      value = ClibTimingType::RemovalRising;
    }
    else if ( strcmp(tmp_str, "removal_falling") == 0 ) {
      value = ClibTimingType::RemovalFalling;
    }
    else if ( strcmp(tmp_str, "non_seq_setup_rising") == 0 ) {
      value = ClibTimingType::NonSeqSetupRising;
    }
    else if ( strcmp(tmp_str, "non_seq_setup_falling") == 0 ) {
      value = ClibTimingType::NonSeqSetupFalling;
    }
    else if ( strcmp(tmp_str, "non_seq_hold_rising") == 0 ) {
      value = ClibTimingType::NonSeqHoldRising;
    }
    else if ( strcmp(tmp_str, "non_seq_hold_falling") == 0 ) {
      value = ClibTimingType::NonSeqHoldFalling;
    }
    else if ( strcmp(tmp_str, "nochange_high_high") == 0 ) {
      value = ClibTimingType::NochangeHighHigh;
    }
    else if ( strcmp(tmp_str, "nochange_high_low") == 0 ) {
      value = ClibTimingType::NochangeHighLow;
    }
    else if ( strcmp(tmp_str, "nochange_low_high") == 0 ) {
      value = ClibTimingType::NochangeLowHigh;
    }
    else if ( strcmp(tmp_str, "nochange_low_low") == 0 ) {
      value = ClibTimingType::NochangeLowLow;
    }
  }
  if ( value == ClibTimingType::None ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. Illegal string for timing type.");
    return {};
  }

  return AstValue::new_timing_type(value, value_loc);
}

// @brief vartype 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_vartype()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  ClibVarType value{ClibVarType::None};
  if ( tmp_str != nullptr ) {
    if ( strcmp(tmp_str, "input_net_transition") == 0 ) {
      value = ClibVarType::InputNetTransition;
    }
    else if ( strcmp(tmp_str, "total_output_net_capacitance") == 0 ) {
      value = ClibVarType::TotalOutputNetCapacitance;
    }
    else if ( strcmp(tmp_str, "equal_or_opposite_output_net_capacitance") == 0 ) {
      value = ClibVarType::EqualOrOppositeOutputNetCapacitance;
    }
    else if ( strcmp(tmp_str, "input_transition_time") == 0 ) {
      value = ClibVarType::InputTransitionTime;
    }
    else if ( strcmp(tmp_str, "output_net_length") == 0 ) {
      value = ClibVarType::OutputNetLength;
    }
    else if ( strcmp(tmp_str, "output_net_wire_cap") == 0 ) {
      value = ClibVarType::OutputNetWireCap;
    }
    else if ( strcmp(tmp_str, "output_net_pin_cap") == 0 ) {
      value = ClibVarType::OutputNetPinCap;
    }
    else if ( strcmp(tmp_str, "related_out_total_output_net_capacitance") == 0 ) {
      value = ClibVarType::RelatedOutTotalOutputNetCapacitance;
    }
    else if ( strcmp(tmp_str, "related_out_output_net_length") == 0 ) {
      value = ClibVarType::RelatedOutOutputNetLength;
    }
    else if ( strcmp(tmp_str, "related_out_output_net_wire_cap") == 0 ) {
      value = ClibVarType::RelatedOutOutputNetWireCap;
    }
    else if ( strcmp(tmp_str, "related_out_output_net_pin_cap") == 0 ) {
      value = ClibVarType::RelatedOutOutputNetPinCap;
    }
    else if ( strcmp(tmp_str, "constrained_pin_transition") == 0 ) {
      value = ClibVarType::ConstrainedPinTransition;
    }
    else if ( strcmp(tmp_str, "related_pin_transition") == 0 ) {
      value = ClibVarType::RelatedPinTransition;
    }
  }
  if ( value == ClibVarType::None ) {
    ostringstream buf;
    buf << "Syntax error. "
	<< tmp_str << " is not a valid string for variable type.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    buf.str());
    return {};
  }

  return AstValue::new_vartype(value, value_loc);
}

// @brief int vector 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_int_vector()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  if ( tmp_str == nullptr ) {
    return {};
  }

  vector<int> dst_list;
  string buf;
  char c = '\0';
  for ( const char* s = tmp_str; (c = *s) ; ++ s ) {
    if ( isspace(c) ) {
      continue;
    }
    else if ( c == ',' ) {
      if ( buf.size() == 0 ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. Null element.");
	return nullptr;
      }
      dst_list.push_back(atoi(buf.c_str()));
      buf.clear();
    }
    else {
      buf += c;
    }
  }
  if ( buf.size() > 0 ) {
    dst_list.push_back(atoi(buf.c_str()));
  }

  return AstValue::new_int_vector(dst_list, value_loc);
}

// @brief float vector 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_float_vector()
{
  FileRegion value_loc;
  vector<double> dst_list;
  bool stat = read_raw_float_vector(dst_list, value_loc);
  if ( stat ) {
    return AstValue::new_float_vector(dst_list, value_loc);
  }
  else {
    return {};
  }
}

END_NAMESPACE_YM_DOTLIB
