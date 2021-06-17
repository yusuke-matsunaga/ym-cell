
/// @file DotlibParser_simple.cc
/// @brief DotlibParser の実装ファイル ( simple attribute 関連 )
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstValue.h"
#include "dotlib/TokenType.h"

#include "ym/MsgMgr.h"

#include "FuncParser.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 整数値型の simple attribute のパースを行う．
const AstAttr*
DotlibParser::parse_int(AttrType attr_type,
			const FileRegion& attr_loc)
{
  unique_ptr<const AstValue> value;
  bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
  {
    value = parser.read_int();
    return value != nullptr;
  });

  if ( stat ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief float 値型の simple attribute のパースを行う．
const AstAttr*
DotlibParser::parse_float(AttrType attr_type,
			  const FileRegion& attr_loc)
{
  unique_ptr<const AstValue> value;
  bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
  {
    value = parser.read_float();
    return value != nullptr;
  });

  if ( stat ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief 文字列値型の simple attribute のパースを行う．
const AstAttr*
DotlibParser::parse_string(AttrType attr_type,
			   const FileRegion& attr_loc)
{
  unique_ptr<const AstValue> value;
  bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
  {
    value = parser.read_string();
    return value != nullptr;
  });

  if ( stat ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief ブール値 のパースを行う．
const AstAttr*
DotlibParser::parse_bool(AttrType attr_type,
			 const FileRegion& attr_loc)
{
  unique_ptr<const AstValue> value;
  bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
  {
    value = parser.read_bool();
    return value != nullptr;
  });

  if ( stat ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief 'delay_model' Simple Attribute のパースを行う．
const AstAttr*
DotlibParser::parse_delay_model(AttrType attr_type,
				const FileRegion& attr_loc)
{
  unique_ptr<const AstValue> value;
  bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
  {
    value = parser.read_delay_model();
    return value != nullptr;
  });

  if ( stat ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief 'direction' Simple Attribute のパースを行う．
const AstAttr*
DotlibParser::parse_direction(AttrType attr_type,
			      const FileRegion& attr_loc)
{
  unique_ptr<const AstValue> value;
  bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
  {
    value = parser.read_direction();
    return value != nullptr;
  });

  if ( stat ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief 'timing_sense' Simple Attribute のパースを行う．
const AstAttr*
DotlibParser::parse_timing_sense(AttrType attr_type,
				 const FileRegion& attr_loc)
{
  unique_ptr<const AstValue> value;
  bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
  {
    value = parser.read_timing_sense();
    return value != nullptr;
  });

  if ( stat ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief 'timing_type' Simple Attribute のパースを行う．
const AstAttr*
DotlibParser::parse_timing_type(AttrType attr_type,
				const FileRegion& attr_loc)
{
  unique_ptr<const AstValue> value;
  bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
  {
    value = parser.read_timing_type();
    return value != nullptr;
  });

  if ( stat ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief 'var_type' Simple Attribute のパースを行う．
const AstAttr*
DotlibParser::parse_vartype(AttrType attr_type,
			    const FileRegion& attr_loc)
{
  unique_ptr<const AstValue> value;
  bool stat = parse_simple_attribute([&](DotlibParser& parser) -> bool
  {
    value = parser.read_vartype();
    return value != nullptr;
  });

  if ( stat ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief 式型の simple attribute のパースを行う．
const AstAttr*
DotlibParser::parse_expr(AttrType attr_type,
			 const FileRegion& attr_loc)
{
  // ちょっと例外的に DotlibParse 自ら処理する．
  if ( !expect(TokenType::COLON) ) {
    return nullptr;
  }

  unique_ptr<const AstValue> value{read_expr()};
  if ( value == nullptr ) {
    return nullptr;
  }

  if ( expect_nl() ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

// @brief "式"型の simple attribute のパースを行う．
const AstAttr*
DotlibParser::parse_function(AttrType attr_type,
			     const FileRegion& attr_loc)
{
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

  if ( !stat ) {
    return nullptr;
  }

  FuncParser read(tmp_str, value_loc, mgr());
  unique_ptr<const AstValue> value{read()};
  if ( value ) {
    auto node = new AstAttr(attr_type, attr_loc, std::move(value));
    return node;
  }
  else {
    return nullptr;
  }
}

END_NAMESPACE_YM_DOTLIB
