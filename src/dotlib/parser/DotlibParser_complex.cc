
/// @file DotlibParser_complex.cc
/// @brief DotlibParser の実装ファイル (complex attribute 関係)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"

#include "dotlib/FloatFloatHandler.h"
#include "dotlib/FloatStrHandler.h"
#include "dotlib/FloatVectorHandler.h"
#include "dotlib/FloatVectorListHandler.h"
#include "dotlib/IntFloatHandler.h"
#include "dotlib/IntVectorHandler.h"
#include "dotlib/StrHandler.h"
#include "dotlib/StrStrHandler.h"
#include "dotlib/StrStrIntHandler.h"
#include "dotlib/StrStrStrHandler.h"
#include "dotlib/StrFloatHandler.h"
#include "dotlib/StrListHandler.h"

#include "dotlib/AstMgr.h"
#include "dotlib/AstBool.h"
#include "dotlib/AstDelayModel.h"
#include "dotlib/AstDirection.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstFloat2.h"
#include "dotlib/AstFloatStr.h"
#include "dotlib/AstFloatVector.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstIntFloat.h"
#include "dotlib/AstIntVector.h"
#include "dotlib/AstStr2.h"
#include "dotlib/AstStr3.h"
#include "dotlib/AstStrFloat.h"
#include "dotlib/AstString.h"
#include "dotlib/AstStrList.h"
#include "dotlib/AstTechnology.h"

#include "dotlib/TokenType.h"
#include "ym/FileIDO.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief coefs attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_coefs(const AstFloatVector*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatVectorHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      FileRegion loc(handler.first_loc(), handler.last_loc());
      dst = mgr().new_float_vector(loc, handler.value_list());
    }
    return stat;
  }
}

// @brief 'default_part' Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_default_part(const AstStr2*& dst,
				 AttrType attr_type,
				 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    StrStrHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_str2(handler);
    }
    return stat;
  }
}

// @brief 'define' Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
DotlibParser::parse_define(vector<const AstStr3*>& dst_list,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  StrStrStrHandler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_str3(handler));
  }
  return stat;
}

// @brief 'define_cell_area' Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
DotlibParser::parse_define_cell_area(vector<const AstStr2*>& dst_list,
				     AttrType attr_type,
				     const FileRegion& attr_loc)
{
  StrStrHandler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_str2(handler));
  }
  return stat;
}

// @brief 'define_group' Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
DotlibParser::parse_define_group(vector<const AstStr2*>& dst_list,
				 AttrType attr_type,
				 const FileRegion& attr_loc)
{
  StrStrHandler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_str2(handler));
  }
  return stat;
}

// @brief 'index' complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_index(const AstFloatVector*& dst,
			  AttrType attr_type,
			  const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatVectorHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      FileRegion loc(handler.first_loc(), handler.last_loc());
      dst = mgr().new_float_vector(loc, handler.value_list());
    }
    return stat;
  }
}

// @brief 'library_features' Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_library_features(const AstString*& dst,
				     AttrType attr_type,
				     const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    StrHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief orders attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_orders(const AstIntVector*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    IntVectorHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = handler.value();
    }
    return stat;
  }
}

// @brief 'piece_define' Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_piece_define(const AstFloatVector*& dst,
				 AttrType attr_type,
				 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatVectorHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      FileRegion loc(handler.first_loc(), handler.last_loc());
      dst = mgr().new_float_vector(loc, handler.value_list());
    }
    return stat;
  }
}

// @brief piecewise attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_piecewise(vector<const AstIntFloat*>& dst_list,
			      AttrType attr_type,
			      const FileRegion& attr_loc)
{
  IntFloatHandler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_int_float(handler));
  }
  return stat;
}

// @brief 'routing_layers' Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_routing_layers(const AstStrList*& dst,
				   AttrType attr_type,
				   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    StrListHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_str_list(handler);
    }
    return stat;
  }
}

// @brief 'technology' Complex Attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_technology(const AstTechnology*& dst,
			       AttrType attr_type,
			       const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    StrHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      // handler.value() から dst に値を設定する．
      ShString str = handler.value()->value();
      ClibTechnology tech = ClibTechnology::cmos;
      if ( strcmp(str, "cmos") == 0 ) {
	tech = ClibTechnology::cmos;
      }
      else if ( strcmp(str, "fpga") == 0 ) {
	tech = ClibTechnology::fpga;
      }
      else {
	ostringstream buf;
	buf << "Syntax error. Unexpected value: " << str << ".";
	MsgMgr::put_msg(__FILE__, __LINE__,
			attr_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			buf.str());
	return false;
      }
      FileRegion loc(handler.first_loc(), handler.last_loc());
      dst = mgr().new_technology(loc, tech);
    }
    return stat;
  }
}

// @brief 単位型 attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_unit(const AstFloatStr*& dst,
			 AttrType attr_type,
			 const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatStrHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_float_str(handler);
    }
    return stat;
  }
}

// @brief 'values' complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_values(const AstFloatVector*& dst,
			   AttrType attr_type,
			   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatVectorListHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      FileRegion loc(handler.first_loc(), handler.last_loc());
      dst = mgr().new_float_vector(loc, handler.value_list());
    }
    return stat;
  }
}

// @brief variable_n_range attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_variable_range(const AstFloat2*& dst,
				   AttrType attr_type,
				   const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    FloatFloatHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_float2(handler);
    }
    return stat;
  }
}

// @brief 'voltage_map' Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_voltage_map(vector<const AstStrFloat*>& dst_list,
				AttrType attr_type,
				const FileRegion& attr_loc)
{
  StrFloatHandler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_str_float(handler));
  }
  return stat;
}

END_NAMESPACE_YM_DOTLIB
