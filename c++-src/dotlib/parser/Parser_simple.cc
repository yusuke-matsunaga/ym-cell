
/// @file Parser_simple.cc
/// @brief Parser の実装ファイル ( simple attribute 関連 )
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/TokenType.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstValue.h"

#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief Simple Attribute を読み込む．
// @retrun 結果の AstAttr を返す．
//
// エラーが起こったら nullptr を返す．
AstAttrPtr
Parser::parse_simple_attribute(const AttrKwd& attr,
				     SimpleHandler handler)
{
  Token token = mScanner.read_and_verify(TokenType::COLON);
  if ( token.type() != TokenType::COLON ) {
    return {};
  }

  auto value{handler(mScanner)};
  if ( value == nullptr ) {
    return {};
  }

  if ( !read_tail() ) {
    return {};
  }

  return AstAttrPtr{new AstAttr(attr, std::move(value))};
}

// @brief 整数値型の simple attribute のパースを行う．
AstAttrPtr
Parser::parse_int(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_int(); });
}

// @brief float 値型の simple attribute のパースを行う．
AstAttrPtr
Parser::parse_float(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_float(); });
}

// @brief 文字列値型の simple attribute のパースを行う．
AstAttrPtr
Parser::parse_string(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_string(); });
}

// @brief ブール値 のパースを行う．
AstAttrPtr
Parser::parse_bool(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_bool(); });
}

// @brief 'delay_model' Simple Attribute のパースを行う．
AstAttrPtr
Parser::parse_delay_model(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_delay_model(); });
}

// @brief 'direction' Simple Attribute のパースを行う．
AstAttrPtr
Parser::parse_direction(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_direction(); });
}

// @brief 'timing_sense' Simple Attribute のパースを行う．
AstAttrPtr
Parser::parse_timing_sense(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_timing_sense(); });
}

// @brief 'timing_type' Simple Attribute のパースを行う．
AstAttrPtr
Parser::parse_timing_type(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_timing_type(); });
}

// @brief 'var_type' Simple Attribute のパースを行う．
AstAttrPtr
Parser::parse_vartype(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_vartype(); });
}

// @brief 式型の simple attribute のパースを行う．
AstAttrPtr
Parser::parse_expr(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_expr(); });
}

// @brief "式"型の simple attribute のパースを行う．
AstAttrPtr
Parser::parse_function(const AttrKwd& attr)
{
  return parse_simple_attribute(attr,
				[](Scanner& scanner) -> AstValuePtr
				{ return scanner.read_function(); });
}

END_NAMESPACE_YM_DOTLIB
