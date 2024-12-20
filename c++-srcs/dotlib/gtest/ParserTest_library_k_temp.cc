
/// @file ParserTest_library_k_temp.cc
/// @brief library の k_temp_xxx simple attribute 用パース関数のテスト
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ParserTest.h"
#include "dotlib/Parser.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstValue.h"

#include "parse_group.h"


BEGIN_NAMESPACE_YM_DOTLIB

TEST_F(ParserTestLibrary, library_k_temp_cell_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_cell_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_cell_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_cell_leakage_power1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_cell_leakage_power: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_cell_leakage_power", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_cell_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_cell_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_cell_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_drive_current1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_drive_current: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_drive_current", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_drive_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_drive_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_drive_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_drive_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_drive_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_drive_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_fall_delay_intercept1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_fall_delay_intercept: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_fall_delay_intercept", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_fall_pin_resistance1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_fall_pin_resistance: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_fall_pin_resistance", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_fall_propagation1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_fall_propagation: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_fall_propagation", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_fall_transition1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_fall_transition: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_fall_transition", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_hold_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_hold_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_hold_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_hold_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_hold_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_hold_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_internal_power1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_internal_power: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_internal_power", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_intrinsic_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_intrinsic_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_intrinsic_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_intrinsic_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_intrinsic_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_intrinsic_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_min_period1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_min_period: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_min_period", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_min_pulse_width_high1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_min_pulse_width_high: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_min_pulse_width_high", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_min_pulse_width_low1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_min_pulse_width_low: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_min_pulse_width_low", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_nochange_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_nochange_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_nochange_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_nochange_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_nochange_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_nochange_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_pin_cap1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_pin_cap: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_pin_cap", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_recoverry_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_recovery_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_recovery_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_recovery_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_recovery_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_recovery_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_removal_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_removal_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_removal_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_removal_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_removal_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_removal_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_rise_delay_intercept1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_rise_delay_intercept: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_rise_delay_intercept", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_rise_pin_resistance1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_rise_pin_resistance: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_rise_pin_resistance", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_rise_propagation1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_rise_propagation: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_rise_propagation", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_rise_transition1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_rise_transition: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_rise_transition", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_setup_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_setup_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_setup_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_setup_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_setup_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_setup_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_skew_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_skew_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_skew_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_skew_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_skew_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_skew_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_slope_fall1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_slope_fall: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_slope_fall", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_slope_rise1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_slope_rise: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_slope_rise", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_wire_cap1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_wire_cap: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_wire_cap", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

TEST_F(ParserTestLibrary, library_k_temp_wire_res1)
{
  istringstream buf("( test ) {\n"
		    "  k_temp_wire_res: 1.0;\n"
		    "}\n");
  Parser parser{buf, info, false, false};

  auto dst = group_library(parser, kwd, kwd_loc);

  ASSERT_TRUE( dst != nullptr );
  auto& value{dst->value()};

  auto& header = value.group_header_value();
  ASSERT_TRUE( header.is_valid() );

  EXPECT_EQ( 1, header.complex_elem_size() );
  EXPECT_EQ( "test", header.complex_elem_value(0).string_value() );

  EXPECT_EQ( 1, value.group_elem_size() );
  auto& attr1{value.group_elem_attr(0)};

  EXPECT_EQ( "k_temp_wire_res", attr1.kwd() );
  auto& value1{attr1.value()};
  EXPECT_EQ( 1.0, value1.float_value() );
}

END_NAMESPACE_YM_DOTLIB
