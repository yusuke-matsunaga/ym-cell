
/// @file DotlibParser_simple.cc
/// @brief DotlibParser の実装ファイル ( simple attribute 関連 )
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstBool.h"
#include "dotlib/AstDelayModel.h"
#include "dotlib/AstDirection.h"
#include "dotlib/AstExpr.h"
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

#include "FuncParser.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ブール値 のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_bool(const AstBool*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    const char* tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
				       { return parser.read_raw_string(tmp_str, value_loc); });
    if ( stat ) {
      bool bval;
      if ( strcmp(tmp_str, "true") == 0 ) {
	bval = true;
      }
      else if ( strcmp(tmp_str, "false") == 0 ) {
	bval = false;
      }
      else {
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. only 'true' or 'false' are allowed.");
	return false;
      }

      dst = mgr().new_bool(value_loc, bval);
    }
    return stat;
  }
}

// @brief 整数値 のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_int(const AstInt*& dst,
			AttrType attr_type,
			const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    return parse_simple_attribute([&](DotlibParser& parser) -> bool
				  { return parser.read_int(dst); });
  }
}

// @brief float 値のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_float(const AstFloat*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    return parse_simple_attribute([&](DotlibParser& parser) -> bool
				  { return parser.read_float(dst); });
  }
}

// @brief 文字列値のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_string(const AstString*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    return parse_simple_attribute([&](DotlibParser& parser) -> bool
				  { return parser.read_string(dst); });
  }
}

// @brief 'delay_model' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_delay_model(const AstDelayModel*& dst,
				AttrType attr_type,
				const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    const char* tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
				       { return parser.read_raw_string(tmp_str, value_loc); });
    if ( stat ) {
      ClibDelayModel value;
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
      else {
	ostringstream buf;
	buf << tmp_str << ": Illegal value for 'delay_model'."
	    << " 'generic_cmos', 'table_lookup', "
	    << "'piecewise_cmos', 'cmos2' or 'dcm' are expected.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			buf.str());
	return false;
      }

      dst = mgr().new_delay_model(value_loc, value);

      return true;
    }
    else {
      return false;
    }
  }
}

// @brief 'direction' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_direction(const AstDirection*& dst,
			      AttrType attr_type,
			      const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    const char* tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
				       { return parser.read_raw_string(tmp_str, value_loc); });
    if ( stat ) {
      ClibDirection value;
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
      else {
	ostringstream buf;
	buf << tmp_str << ": Illegal value for 'direction'."
	    << " 'input', 'output', 'inout' or 'internal' are expected.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			buf.str());
	return false;
      }

      dst = mgr().new_direction(value_loc, value);
    }
    return stat;
  }
}

// @brief 論理関数のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_function(const AstExpr*& dst,
			     AttrType attr_type,
			     const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    const char* tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
				       { return parser.read_raw_string(tmp_str, value_loc); });
    if ( stat ) {
      FuncParser read(tmp_str, value_loc, mgr());
      stat = read(dst);
    }

    return stat;
  }
}

// @brief 'timing_sense' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_timing_sense(const AstTimingSense*& dst,
				 AttrType attr_type,
				 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    const char* tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
				       { return parser.read_raw_string(tmp_str, value_loc); });
    if ( stat ) {
      ClibTimingSense value;
      if ( strcmp(tmp_str, "positive_unate") == 0 ) {
	value = ClibTimingSense::PosiUnate;
      }
      else if ( strcmp(tmp_str, "negative_unate") == 0 ) {
	value = ClibTimingSense::NegaUnate;
      }
      else if ( strcmp(tmp_str, "non_unate") == 0 ) {
	value = ClibTimingSense::NonUnate;
      }
      else {
	ostringstream buf;
	buf << tmp_str << ": Illegal value for 'timing_sense'."
	    << " Only 'positive_unate', 'negative_unate', or 'non_unate' are allowed here.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			buf.str());
	return false;
      }

      dst = mgr().new_timing_sense(value_loc, value);
    }

    return stat;
  }
}

// @brief 'timing_type' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_timing_type(const AstTimingType*& dst,
				AttrType attr_type,
				const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    const char* tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
				       { return parser.read_raw_string(tmp_str, value_loc); });
    if ( stat ) {
      ClibTimingType value;
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
      else {
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. Illegal string for timing type.");
	return false;
      }

      dst = mgr().new_timing_type(value_loc, value);
    }

    return stat;
  }
}

// @brief 'var_type' Simple Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_vartype(const AstVarType*& dst,
			    AttrType attr_type,
			    const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    const char* tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
				       { return parser.read_raw_string(tmp_str, value_loc); });
    if ( stat ) {
      ClibVarType value;
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
      else {
	ostringstream buf;
	buf << "Syntax error. "
	    << tmp_str << " is not a valid string for variable type.";
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			buf.str());
	return false;
      }

      dst = mgr().new_var_type(value_loc, value);
    }

    return stat;
  }
}

// @brief 式のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_expr(const AstExpr*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    // ちょっと例外的に DotlibParse 自ら処理する．
    if ( !expect(TokenType::COLON) ) {
      return false;
    }

    const AstExpr* value = read_expr(TokenType::SEMI);
    if ( value != nullptr ) {
      if ( expect_nl() ) {
	dst = value;
	return true;
      }
    }

    return false;
  }
}

END_NAMESPACE_YM_DOTLIB
