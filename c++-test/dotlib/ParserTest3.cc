
/// @file ParserTest3.cc
/// @brief ParserTest の実装ファイル(3)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ParserTest.h"
#include "Parser.h"
#include "AstAttr.h"
#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

#if 0
TEST_F(ParserTest, parse_input_voltage1)
{
  istringstream buf("( 1.0, 2 );\n"
		    ""
  );
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_float(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();
  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( 1.0, value.complex_elem_value(0).float_value() );
  EXPECT_EQ( 2.0, value.complex_elem_value(1).float_value() );
}
#endif

TEST_F(ParserTest, group_cell0)
{
  // ヘッダの検査
  istringstream buf("( test ) {\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"cell", FileRegion{}};
  auto dst = group_string(parser, attr, "cell");

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );
}

TEST_F(ParserTest, parse_cell_area)
{
  istringstream buf("( test ) {\n"
		    "  area: 1.2; \n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"cell", FileRegion{}};
  auto dst = group_string(parser, attr, "cell");

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1 = value.group_elem_attr(0);

  EXPECT_EQ( "area", attr1.attr().name() );
  EXPECT_EQ( 1.2, attr1.value().float_value() );
}

END_NAMESPACE_YM_DOTLIB
