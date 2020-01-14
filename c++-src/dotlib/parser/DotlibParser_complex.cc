
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
#include "dotlib/IntFloatVectorHandler.h"
#include "dotlib/IntVectorHandler.h"
#include "dotlib/StrHandler.h"
#include "dotlib/StrIntHandler.h"
#include "dotlib/StrStrHandler.h"
#include "dotlib/StrStrIntHandler.h"
#include "dotlib/StrStrStrHandler.h"
#include "dotlib/StrFloatHandler.h"
#include "dotlib/StrListHandler.h"

#include "dotlib/AstMgr.h"
#include "dotlib/AstFloat2.h"
#include "dotlib/AstFloatStr.h"
#include "dotlib/AstFloatVector.h"
#include "dotlib/AstIntFloat.h"
#include "dotlib/AstIntFloatVector.h"
#include "dotlib/AstIntVector.h"
#include "dotlib/AstStrInt.h"
#include "dotlib/AstStr2.h"
#include "dotlib/AstStr3.h"
#include "dotlib/AstStrFloat.h"
#include "dotlib/AstString.h"
#include "dotlib/AstStrList.h"
#include "dotlib/AstTechnology.h"

#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

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

// @brief ( float, float ) の形式の complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
// - 'variable_n_range'
bool
DotlibParser::parse_float_float(const AstFloat2*& dst,
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

// @brief ( float, string ) 型の Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_float_string(const AstFloatStr*& dst,
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

// @brief ( "float, float, ... " ) の形式の Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
// - 'coefs'
// - 'curve_x'
// - 'index'
// - 'piece_define'
bool
DotlibParser::parse_float_vector(const AstFloatVector*& dst,
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

// @brief ( integer, float ) の形式の Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
// - 'curve_y'
bool
DotlibParser::parse_int_float(const AstIntFloat*& dst,
			      AttrType attr_type,
			      const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    IntFloatHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_int_float(handler);
    }
    return stat;
  }
}

// @brief ( integer, "float, float, ... " ) の形式の Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
// - 'curve_y'
bool
DotlibParser::parse_int_float_vector(const AstIntFloatVector*& dst,
				     AttrType attr_type,
				     const FileRegion& attr_loc)
{
  if ( dst != nullptr ) {
    // 重複していた．
    duplicate_error(attr_type, attr_loc, dst);
    return false;
  }
  else {
    IntFloatVectorHandler handler(*this);
    bool stat = parse_complex_attribute(handler);
    if ( stat ) {
      dst = mgr().new_int_float_vector(handler);
    }
    return stat;
  }
}

// @brief ( "integer, integer, ... " ) の形式の Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
// - 'orders'
bool
DotlibParser::parse_int_vector(const AstIntVector*& dst,
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

// @brief ( integer, float ) 型の Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
bool
DotlibParser::parse_int_float(vector<const AstIntFloat*>& dst_list,
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

// @brief ( string ) Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
// - 'library_features'
bool
DotlibParser::parse_string_complex(const AstString*& dst,
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

// @brief ( string, float ) の形式の Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
// - 'power_rail'
bool
DotlibParser::parse_string_float(vector<const AstStrFloat*>& dst_list,
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

// @brief ( string, integer ) の形式の Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// この属性は重複チェックは行わない．
// - 'max_count'
bool
DotlibParser::parse_string_int(vector<const AstStrInt*>& dst_list,
			       AttrType attr_type,
			       const FileRegion& attr_loc)
{
  StrIntHandler handler(*this);
  bool stat = parse_complex_attribute(handler);
  if ( stat ) {
    dst_list.push_back(mgr().new_str_int(handler));
  }
  return stat;
}

// @brief ( string, string, ... ) の形式の Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
bool
DotlibParser::parse_string_list(const AstStrList*& dst,
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

// @brief ( string, string ) の形式の Complex attribute のパースを行う．
// @param[in] dst 結果を格納する変数
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
//
// すでに設定済みの属性に重複して設定しようとするとエラーになる．
// - 'default_part'
bool
DotlibParser::parse_string_string(const AstStr2*& dst,
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

// @brief ( string, string ) の形式の Complex attribute のパースを行う．
// @param[in] dst_list 結果を格納するリスト
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @retval true 正常にパーズした．
// @retval false パーズ中にエラーが起こった．
bool
DotlibParser::parse_string_string(vector<const AstStr2*>& dst_list,
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

END_NAMESPACE_YM_DOTLIB
