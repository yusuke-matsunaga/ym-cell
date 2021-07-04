
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

TEST_F(ParserTest, library_default_cell_leakage_power1)
{
  istringstream buf("( test ) {\n"
		    "  default_cell_leakage_power: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_cell_leakage_power", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_connection_class1)
{
  istringstream buf("( test ) {\n"
		    "  default_connection_class: \"a b c\";\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_connection_class", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( "a b c", value1.string_value() );
}

TEST_F(ParserTest, library_default_fall_delay_intercept1)
{
  istringstream buf("( test ) {\n"
		    "  default_fall_delay_intercept: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_fall_delay_intercept", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_fall_pin_resistance1)
{
  istringstream buf("( test ) {\n"
		    "  default_fall_pin_resistance: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_fall_pin_resistance", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_fanout_load1)
{
  istringstream buf("( test ) {\n"
		    "  default_fanout_load: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_fanout_load", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_inout_pin_cap1)
{
  istringstream buf("( test ) {\n"
		    "  default_inout_pin_cap: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_inout_pin_cap", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_inout_pin_fall_res1)
{
  istringstream buf("( test ) {\n"
		    "  default_inout_pin_fall_res: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_inout_pin_fall_res", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_inout_pin_rise_res1)
{
  istringstream buf("( test ) {\n"
		    "  default_inout_pin_rise_res: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_inout_pin_rise_res", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_input_pin_cap1)
{
  istringstream buf("( test ) {\n"
		    "  default_input_pin_cap: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_input_pin_cap", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_input_pin_fall_res1)
{
  istringstream buf("( test ) {\n"
		    "  default_input_pin_fall_res: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_input_pin_fall_res", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_input_pin_rise_res1)
{
  istringstream buf("( test ) {\n"
		    "  default_input_pin_rise_res: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_input_pin_rise_res", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_intrinsic_fall1)
{
  istringstream buf("( test ) {\n"
		    "  default_intrinsic_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_intrinsic_fall", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_intrinsic_rise1)
{
  istringstream buf("( test ) {\n"
		    "  default_intrinsic_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_intrinsic_rise", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_leakage_power_density1)
{
  istringstream buf("( test ) {\n"
		    "  default_leakage_power_density: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_leakage_power_density", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_max_capacitance1)
{
  istringstream buf("( test ) {\n"
		    "  default_max_capacitance: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_max_capacitance", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_max_fanout1)
{
  istringstream buf("( test ) {\n"
		    "  default_max_fanout: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_max_fanout", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_max_transition1)
{
  istringstream buf("( test ) {\n"
		    "  default_max_transition: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_max_transition", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_max_utilization1)
{
  istringstream buf("( test ) {\n"
		    "  default_max_utilization: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_max_utilization", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_min_porosity1)
{
  istringstream buf("( test ) {\n"
		    "  default_min_porosity: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_min_porosity", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_operating_conditions1)
{
  istringstream buf("( test ) {\n"
		    "  default_operating_conditions: typ;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_operating_conditions", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( "typ", value1.string_value() );
}

TEST_F(ParserTest, library_default_output_pin_cap1)
{
  istringstream buf("( test ) {\n"
		    "  default_output_pin_cap: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_output_pin_cap", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_output_pin_fall_res1)
{
  istringstream buf("( test ) {\n"
		    "  default_output_pin_fall_res: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_output_pin_fall_res", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_output_pin_rise_res1)
{
  istringstream buf("( test ) {\n"
		    "  default_output_pin_rise_res: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_output_pin_rise_res", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_rise_delay_intercept1)
{
  istringstream buf("( test ) {\n"
		    "  default_rise_delay_intercept: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_rise_delay_intercept", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_rise_pin_resistance1)
{
  istringstream buf("( test ) {\n"
		    "  default_rise_pin_resistance: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_rise_pin_resistance", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_slope_fall1)
{
  istringstream buf("( test ) {\n"
		    "  default_slope_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_slope_fall", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_slope_rise1)
{
  istringstream buf("( test ) {\n"
		    "  default_slope_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_slope_rise", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_wire_load1)
{
  istringstream buf("( test ) {\n"
		    "  default_wire_load: abc;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_wire_load", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( "abc", value1.string_value() );
}

TEST_F(ParserTest, library_default_wire_load_area1)
{
  istringstream buf("( test ) {\n"
		    "  default_wire_load_area: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_wire_load_area", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_wire_load_capacitance1)
{
  istringstream buf("( test ) {\n"
		    "  default_wire_load_capacitance: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_wire_load_capacitance", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_wire_load_mode1)
{
  istringstream buf("( test ) {\n"
		    "  default_wire_load_mode: top;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_wire_load_mode", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( "top", value1.string_value() );
}

TEST_F(ParserTest, library_default_wire_load_resistance1)
{
  istringstream buf("( test ) {\n"
		    "  default_wire_load_resistance: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_wire_load_resistance", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTest, library_default_wire_load_selection1)
{
  istringstream buf("( test ) {\n"
		    "  default_wire_load_selection: xyz;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

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

  EXPECT_EQ( "default_wire_load_selection", attr1.attr().name() );
  auto& value1{attr1.value()};
  EXPECT_EQ( "xyz", value1.string_value() );
}

END_NAMESPACE_YM_DOTLIB
