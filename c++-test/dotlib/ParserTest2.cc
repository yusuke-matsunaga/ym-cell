
/// @file ParserTest2.cc
/// @brief ParserTest の実装ファイル(2)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ParserTest.h"
#include "Parser.h"
#include "AstAttr.h"
#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

TEST_F(ParserTest, parse_float_float1)
{
  istringstream buf("( 1.0, 2 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_float(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( 1.0, value.complex_elem_value(0).float_value() );
  EXPECT_EQ( 2.0, value.complex_elem_value(1).float_value() );

  EXPECT_EQ( "( 1, 2)", value.decompile() );
}

TEST_F(ParserTest, parse_float_float2)
{
  // 要素数が少ない
  istringstream buf("( 1.0 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_float(parser, attr);

  ASSERT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_float_float3)
{
  // 要素数が多い
  istringstream buf("( 1.0, 2.0, 3.0 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_float(parser, attr);

  ASSERT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_float_float4)
{
  // 1番目の要素の型が合わない．
  istringstream buf("( \"1.0\", 2.0 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_float(parser, attr);

  ASSERT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_float_float5)
{
  // 2番目の要素の型が合わない．
  istringstream buf("( 1.0, false );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_float(parser, attr);

  ASSERT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_float_string1)
{
  istringstream buf("( 1.0, ff );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_string(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( 1.0, value.complex_elem_value(0).float_value() );
  EXPECT_EQ( "ff", value.complex_elem_value(1).string_value() );
  EXPECT_EQ( "( 1, ff)", value.decompile() );
}

TEST_F(ParserTest, parse_float_string2)
{
  // " で囲まれた文字列
  istringstream buf("( 1.0, \"ff\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_string(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();
  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( 1.0, value.complex_elem_value(0).float_value() );
  EXPECT_EQ( "ff", value.complex_elem_value(1).string_value() );
  EXPECT_EQ( "( 1, ff)", value.decompile() );
}

TEST_F(ParserTest, parse_float_string3)
{
  // 要素数が少ない．
  istringstream buf("( 1.0 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_string(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_float_string4)
{
  // 要素数が多い．
  istringstream buf("( 1.0, ff, 2.0 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_string(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_float_string5)
{
  // 1番目の要素の型が不適
  istringstream buf("( \"1.0\", \"ff\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_string(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_float_vector1)
{
  istringstream buf("( \"1.0, 2.0, 3.0\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_vector(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();
  EXPECT_EQ( "( \"1, 2, 3\")", value.decompile() );

  EXPECT_EQ( 1, value.complex_elem_size() );
  auto fv = value.complex_elem_value(0).float_vector_value();
  EXPECT_EQ( 3, fv.size() );
  EXPECT_EQ( 1.0, fv[0] );
  EXPECT_EQ( 2.0, fv[1] );
  EXPECT_EQ( 3.0, fv[2] );
}

TEST_F(ParserTest, parse_float_vector2)
{
  // 文字列の内容が不適切
  istringstream buf("( \"1.0, 2.0a, 3.0\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_vector(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_float_vector3)
{
  // 要素数が少ない．
  istringstream buf("(  );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_vector(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_float_vector4)
{
  // 要素数が多い．
  istringstream buf("( \"1.0, 2.0, 3.0\", \"4.0, 5.0\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_float_vector(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_int_float1)
{
  istringstream buf("( 1, 2.3 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_float(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( 1, value.complex_elem_value(0).int_value() );
  EXPECT_EQ( 2.3, value.complex_elem_value(1).float_value() );
  EXPECT_EQ( "( 1, 2.3)", value.decompile() );
}

TEST_F(ParserTest, parse_int_float2)
{
  // 要素数が少ない．
  istringstream buf("( 1 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_float(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_int_float3)
{
  // 要素数が多い．
  istringstream buf("( 1, 2.3, 3.0 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_float(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_int_float4)
{
  // 1番目の要素の型が不適切
  istringstream buf("( \"1\", 2.3 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_float(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_int_float5)
{
  // 2番目の要素の型が不適切
  istringstream buf("( 1, \"2.3\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_float(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_int_float_vector1)
{
  istringstream buf("( 1, \"2.3, 4.5\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_float_vector(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( 1, value.complex_elem_value(0).int_value() );
  auto fv = value.complex_elem_value(1).float_vector_value();
  EXPECT_EQ( 2, fv.size() );
  EXPECT_EQ( 2.3, fv[0] );
  EXPECT_EQ( 4.5, fv[1] );
  EXPECT_EQ( "( 1, \"2.3, 4.5\")", value.decompile() );
}

TEST_F(ParserTest, parse_int_float_vector2)
{
  // 要素の数が少ない．
  istringstream buf("( 1 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_float_vector(parser, attr);

  ASSERT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_int_float_vector3)
{
  // 要素の数が多い．
  istringstream buf("( 1, \"2.3, 4.5\", abc );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_float_vector(parser, attr);

  ASSERT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_int_float_vector4)
{
  // 1番目の要素の型が不適切
  istringstream buf("( \"1\", \"2.3, 4.5\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_float_vector(parser, attr);

  ASSERT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_int_vector1)
{
  istringstream buf("( \"1, 2, 3\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_vector(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();
  EXPECT_EQ( "( \"1, 2, 3\")", value.decompile() );

  EXPECT_EQ( 1, value.complex_elem_size() );
  auto iv = value.complex_elem_value(0).int_vector_value();
  EXPECT_EQ( 3, iv.size() );
  EXPECT_EQ( 1, iv[0] );
  EXPECT_EQ( 2, iv[1] );
  EXPECT_EQ( 3, iv[2] );
}

TEST_F(ParserTest, parse_int_vector2)
{
  // 要素の数が少ない．
  istringstream buf("(  );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_vector(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_int_vector3)
{
  // 要素の数が多い．
  istringstream buf("( \"1, 2, 3\", \"4, 5\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_int_vector(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_complex1)
{
  istringstream buf("( abc );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_complex(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( "( abc)", value.decompile() );

  EXPECT_EQ( 1, value.complex_elem_size() );
  EXPECT_EQ( "abc", value.complex_elem_value(0).string_value() );

}

TEST_F(ParserTest, parse_string_complex2)
{
  istringstream buf("( \"abc\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_complex(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();
  EXPECT_EQ( "( abc)", value.decompile() );

  EXPECT_EQ( 1, value.complex_elem_size() );
  EXPECT_EQ( "abc", value.complex_elem_value(0).string_value() );
}

TEST_F(ParserTest, parse_string_complex3)
{
  // 要素数が少ない．
  istringstream buf("( );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_complex(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_complex4)
{
  // 要素数が多い．
  istringstream buf("( abc, def );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_complex(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_float1)
{
  istringstream buf("( abc, 1.2 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_float(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( "abc", value.complex_elem_value(0).string_value() );
  EXPECT_EQ( 1.2, value.complex_elem_value(1).float_value() );
  EXPECT_EQ( "( abc, 1.2)", value.decompile() );
}

TEST_F(ParserTest, parse_string_float2)
{
  // 要素数が少ない．
  istringstream buf("( abc );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_float(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_float3)
{
  // 要素数が多い．
  istringstream buf("( abc, 1.2, xyz );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_float(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_float4)
{
  // 2番目の要素の型が不適
  istringstream buf("( abc, \"1.2\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_float(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_int1)
{
  istringstream buf("( abc, 1 );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_int(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( "abc", value.complex_elem_value(0).string_value() );
  EXPECT_EQ( 1, value.complex_elem_value(1).int_value() );
  EXPECT_EQ( "( abc, 1)", value.decompile() );
}

TEST_F(ParserTest, parse_string_int2)
{
  // 要素数が少ない．
  istringstream buf("( abc );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_int(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_int3)
{
  // 要素数が多い．
  istringstream buf("( abc, 1, xyz );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_int(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_int4)
{
  // 2番目の要素の型が不適
  istringstream buf("( abc, \"1\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_int(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_list1)
{
  istringstream buf("( abc, def, ghi );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_list(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 3, value.complex_elem_size() );
  EXPECT_EQ( "abc", value.complex_elem_value(0).string_value() );
  EXPECT_EQ( "def", value.complex_elem_value(1).string_value() );
  EXPECT_EQ( "ghi", value.complex_elem_value(2).string_value() );
  EXPECT_EQ( "( abc, def, ghi)", value.decompile() );
}

TEST_F(ParserTest, parse_string_list2)
{
  istringstream buf("( \"abc\", def, ghi );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_list(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 3, value.complex_elem_size() );
  EXPECT_EQ( "abc", value.complex_elem_value(0).string_value() );
  EXPECT_EQ( "def", value.complex_elem_value(1).string_value() );
  EXPECT_EQ( "ghi", value.complex_elem_value(2).string_value() );
  EXPECT_EQ( "( abc, def, ghi)", value.decompile() );
}

TEST_F(ParserTest, parse_string_list3)
{
  // 定義上は空もあり．
  istringstream buf("( );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_list(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 0, value.complex_elem_size() );
  EXPECT_EQ( "( )", value.decompile() );
}

TEST_F(ParserTest, parse_string_string1)
{
  istringstream buf("( abc, def );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_string(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( "abc", value.complex_elem_value(0).string_value() );
  EXPECT_EQ( "def", value.complex_elem_value(1).string_value() );
  EXPECT_EQ( "( abc, def)", value.decompile() );
}

TEST_F(ParserTest, parse_string_string2)
{
  istringstream buf("( abc, \"def\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_string(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( "abc", value.complex_elem_value(0).string_value() );
  EXPECT_EQ( "def", value.complex_elem_value(1).string_value() );
  EXPECT_EQ( "( abc, def)", value.decompile() );
}

TEST_F(ParserTest, parse_string_string3)
{
  // 要素数が少ない．
  istringstream buf("( abc );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_string(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_string_string4)
{
  // 要素数が多い．
  istringstream buf("( abc, def, xyz );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_string_string(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_define1)
{
  istringstream buf("( abc, \"def\", xyz );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_define(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 3, value.complex_elem_size() );
  EXPECT_EQ( "abc", value.complex_elem_value(0).string_value() );
  EXPECT_EQ( "def", value.complex_elem_value(1).string_value() );
  EXPECT_EQ( "xyz", value.complex_elem_value(2).string_value() );
  EXPECT_EQ( "( abc, def, xyz)", value.decompile() );
}

TEST_F(ParserTest, parse_define2)
{
  // 要素数が少ない．
  istringstream buf("( abc, \"def\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_define(parser, attr);
  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_define3)
{
  // 要素数が多い．
  istringstream buf("( abc, \"def\", xyz, \"012\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_define(parser, attr);
  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_technology1)
{
  istringstream buf("( cmos );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_technology(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();
  EXPECT_EQ( "( cmos)", value.decompile() );

  EXPECT_EQ( 1, value.complex_elem_size() );
  EXPECT_EQ( ClibTechnology::cmos, value.complex_elem_value(0).technology_value() );
}

TEST_F(ParserTest, parse_technology2)
{
  istringstream buf("( fpga );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_technology(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();
  EXPECT_EQ( "( fpga)", value.decompile() );

  EXPECT_EQ( 1, value.complex_elem_size() );
  EXPECT_EQ( ClibTechnology::fpga, value.complex_elem_value(0).technology_value() );
}

TEST_F(ParserTest, parse_technology3)
{
  // 要素数が少ない．
  istringstream buf("( );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_technology(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_technology4)
{
  // 要素数が多い．
  istringstream buf("( cmos, fpga );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_technology(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_technology5)
{
  // 内容が不適切
  istringstream buf("( abc );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_technology(parser, attr);

  EXPECT_TRUE( dst == nullptr );
}

TEST_F(ParserTest, parse_values1)
{
  istringstream buf("( \"1.1, 2.2, 3.3\", \"4.4, 5.5, 6.6\" );\n");
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parse_values(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();
  EXPECT_EQ( "( \"1.1, 2.2, 3.3\", \"4.4, 5.5, 6.6\")", value.decompile() );

  EXPECT_EQ( 2, value.complex_elem_size() );

  auto fv1 = value.complex_elem_value(0).float_vector_value();
  EXPECT_EQ( 3, fv1.size() );
  EXPECT_EQ( 1.1, fv1[0] );
  EXPECT_EQ( 2.2, fv1[1] );
  EXPECT_EQ( 3.3, fv1[2] );

  auto fv2 = value.complex_elem_value(1).float_vector_value();
  EXPECT_EQ( 3, fv2.size() );
  EXPECT_EQ( 4.4, fv2[0] );
  EXPECT_EQ( 5.5, fv2[1] );
  EXPECT_EQ( 6.6, fv2[2] );
}

END_NAMESPACE_YM_DOTLIB
