
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
  auto token = read_token();
  auto tmp_str = token.str_value();
  SizeType n = tmp_str.size();
  bool ok = true;
  for ( int i = 0; i < n; ++ i ) {
    if ( !isdigit(tmp_str[i]) ) {
      ok = false;
      break;
    }
  }
  if ( ok ) {
    int val = atoi(tmp_str.c_str());
    return AstValue::new_int(val, token.loc());
  }

  ostringstream emsg;
  emsg << "Syntax error: " << tmp_str
       << ": Not an integer value.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_SCANNER",
		  emsg.str());
  return {};
}

// @brief float 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_float()
{
  auto token = read_token();
  auto tmp_str = token.str_value();
  char* end;
  double value = strtod(tmp_str.c_str(), &end);
  if ( end[0] == '\0' ) {
    // 全体が float 文字列だった．
    return AstValue::new_float(value, token.loc());
  }

  ostringstream emsg;
  emsg << "Syntax error: " << tmp_str
       << ": Not a number value.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_SCANNER",
		  emsg.str());
  return {};
}

// @brief string 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_string()
{
  auto token = read_token();
  if ( token.type() == TokenType::SYMBOL ) {
    return AstValue::new_string(token.value(), token.loc());
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_SCANNER",
		  "Syntax error. 'string' value is expected.");
  return {};
}

// @brief bool 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_bool()
{
  auto token = read_token();
  auto tmp_str = token.str_value();
  if ( tmp_str == "true" ) {
    return AstValue::new_bool(true, token.loc());
  }
  if ( tmp_str == "false" ) {
    return AstValue::new_bool(false, token.loc());
  }

  ostringstream buf;
  buf << "Syntax error: "
      << tmp_str << ": Illegal value for boolean, only 'true' or 'false' are allowed.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_SCANNER",
		  buf.str());
  return {};
}

// @brief delay_model 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_delay_model()
{
  auto token = read_token();
  auto tmp_str = token.str_value();
  ClibDelayModel value{ClibDelayModel::None};
  if ( tmp_str == "generic_cmos" ) {
    value = ClibDelayModel::GenericCmos;
  }
  else if ( tmp_str == "table_lookup" ) {
    value = ClibDelayModel::TableLookup;
  }
  else if ( tmp_str == "piecewise_cmos" ) {
    value = ClibDelayModel::PiecewiseCmos;
  }
  else if ( tmp_str == "cmos2" ) {
    value = ClibDelayModel::Cmos2;
  }
  else if ( tmp_str == "dcm" ) {
    value = ClibDelayModel::Dcm;
  }
  if ( value != ClibDelayModel::None ) {
    return AstValue::new_delay_model(value, token.loc());
  }

  ostringstream buf;
  buf << "Syntax error: " << tmp_str << ": Illegal value for 'delay_model'."
      << " 'generic_cmos', 'table_lookup', "
      << "'piecewise_cmos', 'cmos2' or 'dcm' are expected.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_SCANNER",
		  buf.str());
  return {};
}

// @brief direction 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_direction()
{
  auto token = read_token();
  auto tmp_str = token.str_value();
  ClibDirection value{ClibDirection::None};
  if ( tmp_str == "input" ) {
    value = ClibDirection::Input;
  }
  else if ( tmp_str == "output" ) {
    value = ClibDirection::Output;
  }
  else if ( tmp_str == "inout" ) {
    value = ClibDirection::Inout;
  }
  else if ( tmp_str == "internal" ) {
    value = ClibDirection::Internal;
  }
  if ( value != ClibDirection::None ) {
    return AstValue::new_direction(value, token.loc());
  }

  ostringstream buf;
  buf << "Syntax error: " << tmp_str << ": Illegal value for 'direction'."
      << " 'input', 'output', 'inout' or 'internal' are expected.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_SCANNER",
		  buf.str());
  return {};
}

// @brief technology 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_technology()
{
  auto token = read_token();
  auto tmp_str = token.str_value();
  ClibTechnology value{ClibTechnology::none};
  if ( tmp_str == "cmos" ) {
    value = ClibTechnology::cmos;
  }
  else if ( tmp_str == "fpga" ) {
    value = ClibTechnology::fpga;
  }
  if ( value != ClibTechnology::none ) {
    return AstValue::new_technology(value, token.loc());
  }

  ostringstream buf;
  buf << "Syntax error: " << tmp_str << ": Illegal value for 'technology'. "
      << "Only 'cmos' or 'fpga' are allowed here.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_SCANNER",
		  buf.str());
  return {};
}

// @brief timing_sense 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_timing_sense()
{
  auto token = read_token();
  ClibTimingSense value{ClibTimingSense::None};
  auto tmp_str = token.str_value();
  if ( tmp_str == "positive_unate" ) {
    value = ClibTimingSense::PosiUnate;
  }
  else if ( tmp_str == "negative_unate" ) {
    value = ClibTimingSense::NegaUnate;
  }
  else if ( tmp_str == "non_unate" ) {
    value = ClibTimingSense::NonUnate;
  }
  if ( value != ClibTimingSense::None ) {
    return AstValue::new_timing_sense(value, token.loc());
  }

  ostringstream buf;
  buf << "Syntax error: " << tmp_str << ": Illegal value for 'timing_sense'."
      << " Only 'positive_unate', 'negative_unate', or 'non_unate' are allowed here.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_SCANNER",
		  buf.str());
  return {};
}

// @brief timing_type 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_timing_type()
{
  auto token = read_token();
  auto tmp_str = token.str_value();
  ClibTimingType value{ClibTimingType::None};
  if ( tmp_str == "combinational" ) {
    value = ClibTimingType::Combinational;
  }
  else if ( tmp_str == "combinational_rise" ) {
    value = ClibTimingType::CombinationalRise;
  }
  else if ( tmp_str == "combinational_fall" ) {
    value = ClibTimingType::CombinationalFall;
  }
  else if ( tmp_str == "three_state_enable" ) {
    value = ClibTimingType::ThreeStateEnable;
  }
  else if ( tmp_str == "three_state_enable_rise" ) {
    value = ClibTimingType::ThreeStateEnableRise;
  }
  else if ( tmp_str == "three_state_enable_fall" ) {
    value = ClibTimingType::ThreeStateEnableFall;
  }
  else if ( tmp_str == "three_state_disable" ) {
    value = ClibTimingType::ThreeStateDisable;
  }
  else if ( tmp_str == "three_state_disable_rise" ) {
    value = ClibTimingType::ThreeStateDisableRise;
  }
  else if ( tmp_str == "three_state_disable_fall" ) {
    value = ClibTimingType::ThreeStateDisableFall;
  }
  else if ( tmp_str == "rising_edge" ) {
    value = ClibTimingType::RisingEdge;
  }
  else if ( tmp_str == "falling_edge" ) {
    value = ClibTimingType::FallingEdge;
  }
  else if ( tmp_str == "preset" ) {
    value = ClibTimingType::Preset;
  }
  else if ( tmp_str == "clear" ) {
    value = ClibTimingType::Clear;
  }
  else if ( tmp_str == "hold_rising" ) {
    value = ClibTimingType::HoldRising;
  }
  else if ( tmp_str == "hold_falling" ) {
    value = ClibTimingType::HoldFalling;
  }
  else if ( tmp_str == "setup_rising" ) {
    value = ClibTimingType::SetupRising;
  }
  else if ( tmp_str == "setup_falling" ) {
    value = ClibTimingType::SetupFalling;
  }
  else if ( tmp_str == "recovery_rising" ) {
    value = ClibTimingType::RecoveryRising;
  }
  else if ( tmp_str == "recovery_falling" ) {
    value = ClibTimingType::RecoveryFalling;
  }
  else if ( tmp_str == "skew_rising" ) {
    value = ClibTimingType::SkewRising;
  }
  else if ( tmp_str == "skew_falling" ) {
    value = ClibTimingType::SkewFalling;
  }
  else if ( tmp_str == "removal_rising" ) {
    value = ClibTimingType::RemovalRising;
  }
  else if ( tmp_str == "removal_falling" ) {
    value = ClibTimingType::RemovalFalling;
  }
  else if ( tmp_str == "non_seq_setup_rising" ) {
    value = ClibTimingType::NonSeqSetupRising;
  }
  else if ( tmp_str == "non_seq_setup_falling" ) {
    value = ClibTimingType::NonSeqSetupFalling;
  }
  else if ( tmp_str == "non_seq_hold_rising" ) {
    value = ClibTimingType::NonSeqHoldRising;
  }
  else if ( tmp_str == "non_seq_hold_falling" ) {
    value = ClibTimingType::NonSeqHoldFalling;
  }
  else if ( tmp_str == "nochange_high_high" ) {
    value = ClibTimingType::NochangeHighHigh;
  }
  else if ( tmp_str == "nochange_high_low" ) {
    value = ClibTimingType::NochangeHighLow;
  }
  else if ( tmp_str == "nochange_low_high" ) {
    value = ClibTimingType::NochangeLowHigh;
  }
  else if ( tmp_str == "nochange_low_low" ) {
    value = ClibTimingType::NochangeLowLow;
  }
  if ( value == ClibTimingType::None ) {
    ostringstream buf;
    buf << "Syntax error: "
	<< tmp_str << ": Illegal value for 'timing_type'.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    token.loc(),
		    MsgType::Error,
		    "DOTLIB_SCANNER",
		    buf.str());
    return {};
  }

  return AstValue::new_timing_type(value, token.loc());
}

// @brief vartype 型の値を読み込む．
// @param[in] 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_vartype()
{
  auto token = read_token();
  auto tmp_str = token.str_value();
  ClibVarType value{ClibVarType::None};
  if ( tmp_str == "input_net_transition" ) {
    value = ClibVarType::InputNetTransition;
  }
  else if ( tmp_str == "total_output_net_capacitance" ) {
    value = ClibVarType::TotalOutputNetCapacitance;
  }
  else if ( tmp_str == "equal_or_opposite_output_net_capacitance" ) {
    value = ClibVarType::EqualOrOppositeOutputNetCapacitance;
  }
  else if ( tmp_str == "input_transition_time" ) {
    value = ClibVarType::InputTransitionTime;
  }
  else if ( tmp_str == "output_net_length" ) {
    value = ClibVarType::OutputNetLength;
  }
  else if ( tmp_str == "output_net_wire_cap" ) {
    value = ClibVarType::OutputNetWireCap;
  }
  else if ( tmp_str == "output_net_pin_cap" ) {
    value = ClibVarType::OutputNetPinCap;
  }
  else if ( tmp_str == "related_out_total_output_net_capacitance" ) {
    value = ClibVarType::RelatedOutTotalOutputNetCapacitance;
  }
  else if ( tmp_str == "related_out_output_net_length" ) {
    value = ClibVarType::RelatedOutOutputNetLength;
  }
  else if ( tmp_str == "related_out_output_net_wire_cap" ) {
    value = ClibVarType::RelatedOutOutputNetWireCap;
  }
  else if ( tmp_str == "related_out_output_net_pin_cap" ) {
    value = ClibVarType::RelatedOutOutputNetPinCap;
  }
  else if ( tmp_str == "constrained_pin_transition" ) {
    value = ClibVarType::ConstrainedPinTransition;
  }
  else if ( tmp_str == "related_pin_transition" ) {
    value = ClibVarType::RelatedPinTransition;
  }
  if ( value != ClibVarType::None ) {
    return AstValue::new_vartype(value, token.loc());
  }

  ostringstream buf;
  buf << "Syntax error: "
      << tmp_str << ": Illegal value for 'variable_type'.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_SCANNER",
		  buf.str());
  return {};
}

// @brief int vector 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_int_vector()
{
  auto token = read_token();
  auto tmp_str = token.str_value();
  if ( tmp_str == string() ) {
    return {};
  }

  vector<int> dst_list;
  string buf;
  for ( auto c: tmp_str ) {
    if ( isspace(c) ) {
      continue;
    }
    else if ( c == ',' ) {
      if ( buf.size() == 0 ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			token.loc(),
			MsgType::Error,
			"DOTLIB_SCANNER",
			"Syntax error: Null element.");
	return {};
      }
      dst_list.push_back(atoi(buf.c_str()));
      buf.clear();
    }
    else if ( isdigit(c) ) {
      buf += c;
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      token.loc(),
		      MsgType::Error,
		      "DOTLIB_SCANNER",
		      "Syntax error: Integer value expected.");
      return {};
    }
  }
  if ( buf.size() > 0 ) {
    dst_list.push_back(atoi(buf.c_str()));
  }

  return AstValue::new_int_vector(dst_list, token.loc());
}

// @brief float vector 型の値を読み込む．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_float_vector()
{
  auto token = read_token();
  auto value_loc = token.loc();
  auto tmp_str = token.str_value();
  if ( tmp_str == string() ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    token.loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return {};
  }

  vector<double> dst_list;
  string buf;
  for ( auto c: tmp_str ) {
    if ( isspace(c) ) {
      continue;
    }
    else if ( c == ',' ) {
      if ( buf.size() == 0 ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			token.loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. Null element.");
	return {};
      }
      char* end;
      double val = strtod(buf.c_str(), &end);
      if ( end[0] != '\0' ) {
	ostringstream emsg;
	emsg << "Syntax error: "
	     << buf << ": Could not convert to a number.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			emsg.str());
	return {};
      }
      dst_list.push_back(val);
      buf.clear();
    }
    else {
      buf += c;
    }
  }
  if ( buf.size() > 0 ) {
    dst_list.push_back(strtod(buf.c_str(), nullptr));
  }

  return AstValue::new_float_vector(dst_list, token.loc());
}

END_NAMESPACE_YM_DOTLIB
