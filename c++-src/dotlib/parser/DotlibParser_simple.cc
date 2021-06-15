
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
    string tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
    {
      auto s = parser.read_raw_string(value_loc);
      if ( s != nullptr ) {
	tmp_str = s;
	return true;
      }
      else {
	return false;
      }
    });
    if ( stat ) {
      bool bval;
      if ( tmp_str == "true" ) {
	bval = true;
      }
      else if ( tmp_str == "false" ) {
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
    {
      auto tmp = parser.read_int();
      if ( tmp ) {
	dst = tmp;
	return true;
      }
      else {
	return false;
      }
    });
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
    {
      auto tmp = parser.read_float();
      if ( tmp ) {
	dst = tmp;
	return true;
      }
      else {
	return false;
      }
    });
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
    {
      dst = parser.read_string();
      return dst != nullptr;
    });
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
    string tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
    {
      auto s = parser.read_raw_string(value_loc);
      if ( s != nullptr ) {
	tmp_str = s;
	return true;
      }
      else {
	return false;
      }
    });
    if ( stat ) {
      ClibDelayModel value;
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
    string tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
    {
      auto s = parser.read_raw_string(value_loc);
      if ( s != nullptr ) {
	tmp_str = s;
	return true;
      }
      else {
	return false;
      }
    });
    if ( stat ) {
      ClibDirection value;
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
    string tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
    {
      auto s = parser.read_raw_string(value_loc);
      if ( s != nullptr ) {
	tmp_str = s;
	return true;
      }
      else {
	return false;
      }
    });
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
    string tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
    {
      auto s = parser.read_raw_string(value_loc);
      if ( s != nullptr ) {
	tmp_str = s;
	return true;
      }
      else {
	return false;
      }
    });
    if ( stat ) {
      ClibTimingSense value;
      if ( tmp_str == "positive_unate" ) {
	value = ClibTimingSense::PosiUnate;
      }
      else if ( tmp_str == "negative_unate" ) {
	value = ClibTimingSense::NegaUnate;
      }
      else if ( tmp_str == "non_unate" ) {
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
    string tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
    {
      auto s = parser.read_raw_string(value_loc);
      if ( s != nullptr ) {
	tmp_str = s;
	return true;
      }
      else {
	return false;
      }
    });
    if ( stat ) {
      ClibTimingType value;
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
    string tmp_str;
    FileRegion value_loc;
    bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
    {
      auto s = parser.read_raw_string(value_loc);
      if ( s != nullptr ) {
	tmp_str = s;
	return true;
      }
      else {
	return false;
      }
    });
    if ( stat ) {
      ClibVarType value;
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

    auto value = read_expr(TokenType::SEMI);
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
