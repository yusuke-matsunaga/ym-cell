
/// @file Parser_complex.cc
/// @brief Parser の実装ファイル (complex attribute 関係)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"
#include "dotlib/TokenType.h"
#include "dotlib/HeaderHandler.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief Complex Attribute を読み込む．
AstAttrPtr
Parser::parse_complex_attribute(const AttrKwd& attr,
				HeaderHandler& handler)
{
  auto value{parse_header(handler)};
  if ( value == nullptr ) {
    return {};
  }

  if ( !read_tail() ) {
    return {};
  }

  return AstAttrPtr{new AstAttr(attr, std::move(value))};
}

// @brief 'define' Complex attribute のパースを行う．
AstAttrPtr
Parser::parse_define(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sStrStrStrHeader);
}

// @brief ( float, float ) の形式の complex attribute のパースを行う．
AstAttrPtr
Parser::parse_float_float(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sFloatFloatHeader);
}

// @brief ( float, string ) 型の Complex attribute のパースを行う．
AstAttrPtr
Parser::parse_float_string(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sFloatStrHeader);
}

// @brief ( "float, float, ... " ) の形式の Complex attribute のパースを行う．
// @param[in] attr_type 属性の型
//
// - 'coefs'
// - 'curve_x'
// - 'index'
// - 'piece_define'
AstAttrPtr
Parser::parse_float_vector(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sFloatVectorHeader);
}

// @brief ( integer, float ) の形式の Complex attribute のパースを行う．
// @param[in] attr_type 属性の型
//
// - 'curve_y'
AstAttrPtr
Parser::parse_int_float(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sIntFloatHeader);
}

// @brief ( integer, "float, float, ... " ) の形式の Complex attribute のパースを行う．
// @param[in] attr_type 属性の型
//
// - 'curve_y'
AstAttrPtr
Parser::parse_int_float_vector(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sIntFloatVectorHeader);
}

// @brief ( "integer, integer, ... " ) の形式の Complex attribute のパースを行う．
// @param[in] attr_type 属性の型
//
// - 'orders'
AstAttrPtr
Parser::parse_int_vector(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sIntVectorHeader);
}

// @brief ( string ) Complex attribute のパースを行う．
// @param[in] attr_type 属性の型
//
// - 'library_features'
AstAttrPtr
Parser::parse_string_complex(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sStrHeader);
}

// @brief ( string, float ) の形式の Complex attribute のパースを行う．
// @param[in] attr_type 属性の型
//
// - 'power_rail'
AstAttrPtr
Parser::parse_string_float(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sStrFloatHeader);
}

// @brief ( string, integer ) の形式の Complex attribute のパースを行う．
// @param[in] attr_type 属性の型
//
// - 'max_count'
AstAttrPtr
Parser::parse_string_int(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sStrIntHeader);
}

// @brief ( string, string, ... ) の形式の Complex attribute のパースを行う．
// @param[in] attr_type 属性の型
AstAttrPtr
Parser::parse_string_list(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sStrListHeader);
}

// @brief ( string, string ) の形式の Complex attribute のパースを行う．
// @param[in] attr_type 属性の型
//
// - 'default_part'
AstAttrPtr
Parser::parse_string_string(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sStrStrHeader);
}

// @brief 'technology' Complex Attribute のパースを行う．
// @param[in] attr_type 属性の型
AstAttrPtr
Parser::parse_technology(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sTechnologyHeader);
}

// @brief 'values' complex attribute のパースを行う．
// @param[in] attr_type 属性の型
AstAttrPtr
Parser::parse_values(const AttrKwd& attr)
{
  return parse_complex_attribute(attr, sFloatVectorListHeader);
}

END_NAMESPACE_YM_DOTLIB
