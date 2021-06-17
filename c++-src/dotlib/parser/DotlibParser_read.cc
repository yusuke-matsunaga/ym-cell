
/// @file DotlibParser_simple.cc
/// @brief DotlibParser の実装ファイル ( simple attribute 関連 )
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstBool.h"
#include "dotlib/AstDelayModel.h"
#include "dotlib/AstDirection.h"
#include "dotlib/AstExprValue.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstFloatVector.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstIntVector.h"
#include "dotlib/AstString.h"
#include "dotlib/AstTechnology.h"
#include "dotlib/AstTimingSense.h"
#include "dotlib/AstTimingType.h"
#include "dotlib/AstVarType.h"
#include "dotlib/TokenType.h"

#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 直前に読んだトークンから AstInt を生成する．
unique_ptr<const AstValue>
DotlibParser::read_int()
{
  FileRegion value_loc;
  TokenType value_type = read_token(value_loc, false);
  if ( value_type == TokenType::INT_NUM ) {
    auto p = new AstInt(cur_int(), value_loc);
    return unique_ptr<const AstValue>{p};
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'integer' value is expected.");
    return unique_ptr<const AstValue>{};
  }
}

// @brief 直前に読んだトークンから AstFloat を生成する．
unique_ptr<const AstValue>
DotlibParser::read_float()
{
  FileRegion value_loc;
  TokenType value_type = read_token(value_loc, false);
  // int 型も float 型とみなす．
  if ( value_type == TokenType::FLOAT_NUM || value_type == TokenType::INT_NUM ) {
    auto p = new AstFloat(cur_float(), value_loc);
    return unique_ptr<const AstValue>{p};
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'float' value is expected.");
    return unique_ptr<const AstValue>{};
  }
}

// @brief 直前に読んだトークンから文字列を取り出す．
const char*
DotlibParser::read_raw_string(FileRegion& value_loc)
{
  TokenType value_type = read_token(value_loc, true);
  if ( value_type == TokenType::SYMBOL ) {
    return cur_string();
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return nullptr;
  }
}

// @brief 直前に読んだトークンから AstString を生成する．
unique_ptr<const AstValue>
DotlibParser::read_string()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  if ( tmp_str ) {
    auto p = new AstString(ShString(tmp_str), value_loc);
    return unique_ptr<const AstValue>{p};
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return unique_ptr<const AstValue>{};
  }
}

// @brief 直前に読んだトークンから AstBool を生成する．
// @return 生成した AstBool を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
unique_ptr<const AstValue>
DotlibParser::read_bool()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  if ( tmp_str != nullptr ) {
    if ( strcmp(tmp_str, "true") == 0 ) {
      auto p = new AstBool(true, value_loc);
      return unique_ptr<const AstValue>{p};
    }
    if ( strcmp(tmp_str, "false") == 0 ) {
      auto p = new AstBool(false, value_loc);
      return unique_ptr<const AstValue>{p};
    }
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  value_loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. only 'true' or 'false' are allowed.");
  return unique_ptr<const AstValue>{};
}

// @brief 直前に読んだトークンから AstDelayModel を生成する．
// @param[in] 生成した AstDelayModel を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
unique_ptr<const AstValue>
DotlibParser::read_delay_model()
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
    return unique_ptr<const AstValue>{};
  }

  auto p = new AstDelayModel(value, value_loc);
  return unique_ptr<const AstValue>{p};
}

// @brief 直前に読んだトークンから AstDirection を生成する．
// @param[in] 生成した AstDirection を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
unique_ptr<const AstValue>
DotlibParser::read_direction()
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
    return unique_ptr<const AstValue>{};
  }

  auto p = new AstDirection(value, value_loc);
  return unique_ptr<const AstValue>{p};
}

// @brief 直前に読んだトークンから AstTechnology を生成する．
// @param[in] 生成した AstTechnology を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
unique_ptr<const AstValue>
DotlibParser::read_technology()
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
    return unique_ptr<const AstValue>{};
  }

  auto p = new AstTechnology(value, value_loc);
  return unique_ptr<const AstValue>{p};
}

// @brief 直前に読んだトークンから AstTimingSense を生成する．
// @param[in] 生成した AstTimingSense を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
unique_ptr<const AstValue>
DotlibParser::read_timing_sense()
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
    return unique_ptr<const AstValue>{};
  }

  auto p = new AstTimingSense(value, value_loc);
  return unique_ptr<const AstValue>{p};
}

// @brief 直前に読んだトークンから AstTimingType を生成する．
// @param[in] 生成した AstTimingType を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
unique_ptr<const AstValue>
DotlibParser::read_timing_type()
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
    return unique_ptr<const AstValue>{};
  }

  auto p = new AstTimingType(value, value_loc);
  return unique_ptr<const AstValue>{p};
}

// @brief 直前に読んだトークンから AstVarType を生成する．
// @param[in] 生成した AstVarType を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
unique_ptr<const AstValue>
DotlibParser::read_vartype()
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
    return unique_ptr<const AstValue>{};
  }

  auto p = new AstVarType(value, value_loc);
  return unique_ptr<const AstValue>{p};
}

// @brief 直前に読んだトークンから AstIntVector を生成する．
unique_ptr<const AstValue>
DotlibParser::read_int_vector()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  if ( tmp_str == nullptr ) {
    return unique_ptr<const AstValue>{};
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

  auto p = new AstIntVector(dst_list, value_loc);
  return unique_ptr<const AstValue>{p};
}

// @brief 直前に読んだトークンから AstFloatVector を生成する．
unique_ptr<const AstValue>
DotlibParser::read_float_vector()
{
  FileRegion value_loc;
  vector<double> dst_list;
  bool stat = read_raw_float_vector(dst_list, value_loc);
  if ( stat ) {
    auto p = new AstFloatVector(dst_list, value_loc);
    return unique_ptr<const AstValue>{p};
  }
  else {
    return unique_ptr<const AstValue>{};
  }
}

// @brief 直前に読んだトークンから float のリストを生成する．
// @retval true 正しく読み込んだ．
// @retval false エラーが起こった．
//
// dst_list は初期化せず，末尾に追加する．
bool
DotlibParser::read_raw_float_vector(vector<double>& dst_list,
				    FileRegion& value_loc)
{
  TokenType value_type = read_token(value_loc, false);
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return false;
  }

  const char* tmp_str = cur_string();
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
	return false;
      }
      dst_list.push_back(strtod(buf.c_str(), nullptr));
      buf.clear();
    }
    else {
      buf += c;
    }
  }
  if ( buf.size() > 0 ) {
    dst_list.push_back(strtod(buf.c_str(), nullptr));
  }

  return true;
}

// @brief primary を読み込む．
const AstExpr*
DotlibParser::_read_primary()
{
  FileRegion loc;
  TokenType type = read_token(loc);
  if ( type == TokenType::LP ) {
    return _read_expr(TokenType::RP);
  }
  if ( type == TokenType::SYMBOL ) {
    const char* name =  cur_string();
    if ( strcmp(name, "VDD") == 0 ) {
      return mgr().new_vdd_expr(loc);
    }
    else if ( strcmp(name, "VSS") == 0 ) {
      return mgr().new_vss_expr(loc);
    }
    else if ( strcmp(name, "VCC") == 0 ) {
      return mgr().new_vcc_expr(loc);
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. "
		      "Only 'VDD', 'VSS', and 'VCC' are allowed.");
      return nullptr;
    }
  }
  if ( type == TokenType::FLOAT_NUM || type == TokenType::INT_NUM ) {
    double val = cur_float();
    return mgr().new_float_expr(loc, val);
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. number is expected.");
  return nullptr;
}

// @brief prudct を読み込む．
const AstExpr*
DotlibParser::_read_product()
{
  const AstExpr* opr1 = _read_primary();
  if ( opr1 == nullptr ) {
    return nullptr;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == TokenType::MULT || type == TokenType::DIV ) {
      const AstExpr* opr2 = _read_primary();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      if ( type == TokenType::MULT ) {
	opr1 = mgr().new_mult(opr1, opr2);
      }
      else {
	opr1 = mgr().new_div(opr1, opr2);
      }
    }
    else {
      // token を戻す．
      unget_token(type, loc);
      return opr1;
    }
  }
}

// @brief expression を読み込む．
const AstExpr*
DotlibParser::_read_expr(TokenType end_marker)
{
  const AstExpr* opr1 = _read_product();
  if ( opr1 == nullptr ) {
    return nullptr;
  }
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == end_marker ) {
      return opr1;
    }
    if ( type == TokenType::PLUS || type == TokenType::MINUS ) {
      const AstExpr* opr2 = _read_product();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      if ( type == TokenType::PLUS ) {
	opr1 = mgr().new_plus(opr1, opr2);
      }
      else {
	opr1 = mgr().new_minus(opr1, opr2);
      }
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error.");
      return nullptr;
    }
  }
}

// @brief 式を表す AstExprValue を生成する．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
unique_ptr<const AstValue>
DotlibParser::read_expr()
{
  auto expr = _read_expr(TokenType::SEMI);
  if ( expr ) {
    return unique_ptr<const AstValue>{new AstExprValue(expr)};
  }
  else {
    return unique_ptr<const AstValue>{};
  }
}

END_NAMESPACE_YM_DOTLIB
