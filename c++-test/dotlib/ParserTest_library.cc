
/// @file ParserTest_library.cc
/// @brief ParserTest_library の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ParserTest.h"
#include "Parser.h"
#include "AstAttr.h"
#include "AstValue.h"

#include "parse_group.h"


BEGIN_NAMESPACE_YM_DOTLIB

TEST_F(ParserTest, group_library_header)
{
  // ヘッダの検査
  istringstream buf("( test ) {\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );
}

TEST_F(ParserTest, group_library_bus_naming_style)
{
  istringstream buf("( test ) {\n"
		    "  bus_naming_style: %s[%d];\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "bus_naming_style", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( "%s[%d]", value1.string_value() );
}

TEST_F(ParserTest, group_library_comment)
{
  istringstream buf("( test ) {\n"
		    "  comment: \"this is a comment\";\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "comment", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( "this is a comment", value1.string_value() );
}

TEST_F(ParserTest, group_library_current_unit)
{
  istringstream buf("( test ) {\n"
		    "  current_unit: uA;\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "current_unit", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( "uA", value1.string_value() );
}

TEST_F(ParserTest, group_library_date)
{
  istringstream buf("( test ) {\n"
		    "  date: \"2021/06/28\";\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "date", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( "2021/06/28", value1.string_value() );
}

TEST_F(ParserTest, group_library_delay_model1)
{
  istringstream buf("( test ) {\n"
		    "  delay_model: generic_cmos;\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "delay_model", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( ClibDelayModel::generic_cmos, value1.delay_model_value() );
}

TEST_F(ParserTest, group_library_delay_model2)
{
  istringstream buf("( test ) {\n"
		    "  delay_model: table_lookup;\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "delay_model", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( ClibDelayModel::table_lookup, value1.delay_model_value() );
}

TEST_F(ParserTest, group_library_delay_model3)
{
  istringstream buf("( test ) {\n"
		    "  delay_model: piecewise_cmos;\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "delay_model", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( ClibDelayModel::piecewise_cmos, value1.delay_model_value() );
}

TEST_F(ParserTest, group_library_delay_model4)
{
  istringstream buf("( test ) {\n"
		    "  delay_model: dcm;\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "delay_model", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( ClibDelayModel::dcm, value1.delay_model_value() );
}

TEST_F(ParserTest, group_library_delay_model5)
{
  istringstream buf("( test ) {\n"
		    "  delay_model: polynomial;\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "delay_model", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( ClibDelayModel::polynomial, value1.delay_model_value() );
}

TEST_F(ParserTest, group_library_delay_model6)
{
  istringstream buf("( test ) {\n"
		    "  delay_model: xyz;\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  ASSERT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 2, column 16 - 18: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: xyz: Illegal value for 'delay_model'. 'generic_cmos', 'table_lookup', 'piecewise_cmos', 'cmos2', 'dcm' or 'polynomial' are expected.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, group_library_em_temp_degradation_factor1)
{
  istringstream buf("( test ) {\n"
		    "  em_temp_degradation_factor: 1.0;\n"
		    "}\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  AttrKwd attr{"library", FileRegion{}};
  auto dst = group_library(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "em_temp_degradation_factor", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

END_NAMESPACE_YM_DOTLIB
