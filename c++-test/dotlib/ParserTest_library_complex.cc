
/// @file ParserTest_library_complex.cc
/// @brief library グループの complex attribute のパーステスト
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

TEST_F(ParserTest, library_capacitive_load_unit1)
{
  istringstream buf("( test ) {\n"
		    "  capacitive_load_unit ( 1, pf);\n"
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

  EXPECT_EQ( "capacitive_load_unit", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 2, value1.complex_elem_size() );
  EXPECT_EQ( 1, value1.complex_elem_value(0).float_value() );
  EXPECT_EQ( "pf", value1.complex_elem_value(1).string_value() );
}

TEST_F(ParserTest, library_default_part1)
{
  istringstream buf("( test ) {\n"
		    "  default_part ( AUTO, \"-5\");\n"
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

  EXPECT_EQ( "default_part", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 2, value1.complex_elem_size() );
  EXPECT_EQ( "AUTO", value1.complex_elem_value(0).string_value() );
  EXPECT_EQ( "-5", value1.complex_elem_value(1).string_value() );
}

TEST_F(ParserTest, library_define1)
{
  istringstream buf("( test ) {\n"
		    "  define ( bork, pin, string);\n"
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

  EXPECT_EQ( "define", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 3, value1.complex_elem_size() );
  EXPECT_EQ( "bork", value1.complex_elem_value(0).string_value() );
  EXPECT_EQ( "pin", value1.complex_elem_value(1).string_value() );
  EXPECT_EQ( "string", value1.complex_elem_value(2).string_value() );
}

TEST_F(ParserTest, library_define_cell_area1)
{
  istringstream buf("( test ) {\n"
		    "  define_cell_area ( bond_pads, pad_slots);\n"
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

  EXPECT_EQ( "define_cell_area", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 2, value1.complex_elem_size() );
  EXPECT_EQ( "bond_pads", value1.complex_elem_value(0).string_value() );
  EXPECT_EQ( "pad_slots", value1.complex_elem_value(1).string_value() );
}

TEST_F(ParserTest, library_define_group1)
{
  istringstream buf("( test ) {\n"
		    "  define_group ( myGroup, timing);\n"
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

  EXPECT_EQ( "define_group", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 2, value1.complex_elem_size() );
  EXPECT_EQ( "myGroup", value1.complex_elem_value(0).string_value() );
  EXPECT_EQ( "timing", value1.complex_elem_value(1).string_value() );
}

TEST_F(ParserTest, library_library_features1)
{
  istringstream buf("( test ) {\n"
		    "  library_features ( report_delay_calculation );\n"
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

  EXPECT_EQ( "library_features", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 1, value1.complex_elem_size() );
  EXPECT_EQ( "report_delay_calculation", value1.complex_elem_value(0).string_value() );
}

TEST_F(ParserTest, library_piece_define1)
{
  istringstream buf("( test ) {\n"
		    "  piece_define ( \"0 10 20\");\n"
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

  EXPECT_EQ( "piece_define", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 1, value1.complex_elem_size() );
  EXPECT_EQ( "0 10 20", value1.complex_elem_value(0).string_value() );
}

TEST_F(ParserTest, library_routing_layers1)
{
  istringstream buf("( test ) {\n"
		    "  routing_layers ( metal1, metal2, metal3, metal4 );\n"
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

  EXPECT_EQ( "routing_layers", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 4, value1.complex_elem_size() );
  EXPECT_EQ( "metal1", value1.complex_elem_value(0).string_value() );
  EXPECT_EQ( "metal2", value1.complex_elem_value(1).string_value() );
  EXPECT_EQ( "metal3", value1.complex_elem_value(2).string_value() );
  EXPECT_EQ( "metal4", value1.complex_elem_value(3).string_value() );
}

TEST_F(ParserTest, library_technology1)
{
  istringstream buf("( test ) {\n"
		    "  technology ( cmos );\n"
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

  EXPECT_EQ( "technology", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 1, value1.complex_elem_size() );
  EXPECT_EQ( ClibTechnology::cmos, value1.complex_elem_value(0).technology_value() );
}

TEST_F(ParserTest, library_voltage_map1)
{
  istringstream buf("( test ) {\n"
		    "  voltage_map ( VDD1, 3.0);\n"
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

  EXPECT_EQ( "voltage_map", attr1.attr().name() );
  auto& value1{attr1.value()};
  ASSERT_EQ( 2, value1.complex_elem_size() );
  EXPECT_EQ( "VDD1", value1.complex_elem_value(0).string_value() );
  EXPECT_EQ( 3.0, value1.complex_elem_value(1).float_value() );
}

#if 0
TEST_F(ParserTest, library_delay_model6)
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
#endif

END_NAMESPACE_YM_DOTLIB
