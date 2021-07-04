
/// @file ParserTest_simple.cc
/// @brief simple attribute 用のパース関数のテスト
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ParserTest.h"
#include "Parser.h"
#include "AstAttr.h"
#include "AstValue.h"

#include "parse_simple.h"


BEGIN_NAMESPACE_YM_DOTLIB

TEST_F(ParserTest, simple_bool1)
{
  istringstream buf{": true;\n"};
  Parser parser{buf, info, false, false};

  auto dst = simple_bool(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( true, value.bool_value() );
  EXPECT_EQ( "true", value.decompile() );
}

TEST_F(ParserTest, simple_bool2)
{
  istringstream buf{": false;\n"};
  Parser parser{buf, info, false, false};

  auto dst = simple_bool(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( false, value.bool_value() );
  EXPECT_EQ( "false", value.decompile() );
}

TEST_F(ParserTest, simple_bool3)
{
  // スペルミス
  istringstream buf{": fals;\n"};
  Parser parser{buf, info, false, false};

  auto dst = simple_bool(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 3 - 6: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: fals: Illegal value for boolean, only 'true' or 'false' are allowed.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, simple_bool4)
{
  // セミコロンの後に改行がない
  istringstream buf{": true; another_attr"};
  Parser parser{buf, info, false, false};

  auto dst = simple_bool(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 9 - 20: (ERROR  ) [DOTLIB_PARSER]: Syntax error. New-line is expected.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, simple_bool5)
{
  // セミコロンがない．
  istringstream buf{": true\n"};
  Parser parser{buf, info, false, false};

  auto dst = simple_bool(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 7: (ERROR  ) [DOTLIB_PARSER]: Syntax error. Semicolon is expected.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, simple_bool6)
{
  // セミコロンがないが，
  // allow_no_semi が true なので成功する．
  istringstream buf{": true\n"};
  Parser parser{buf, info, false, true};

  auto dst = simple_bool(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( true, value.bool_value() );
  EXPECT_EQ( "true", value.decompile() );
}

TEST_F(ParserTest, simple_int1)
{
  istringstream buf(": 123;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_int(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 123, value.int_value() );
  EXPECT_EQ( "123", value.decompile() );
}

TEST_F(ParserTest, simple_int2)
{
  // 非数字
  istringstream buf(": a123;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_int(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 3 - 6: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: a123: Not an integer value.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, simple_float1)
{
  istringstream buf(": 123.456;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_float(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 123.456, value.float_value() );
  EXPECT_EQ( "123.456", value.decompile() );
}

TEST_F(ParserTest, simple_float2)
{
  // 整数でもOK
  istringstream buf(": 123;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_float(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( 123, value.float_value() );
  EXPECT_EQ( "123", value.decompile() );
}

TEST_F(ParserTest, simple_float3)
{
  // 先頭が非数字
  istringstream buf(": f123.456;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_float(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 3 - 10: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: f123.456: Not a number value.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, simple_string1)
{
  istringstream buf(": abcdefg;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_string(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( "abcdefg", value.string_value() );
  EXPECT_EQ( "abcdefg", value.decompile() );
}

TEST_F(ParserTest, simple_string2)
{
  // " で囲まれていてもOK
  istringstream buf(": \"abcdefg\";\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_string(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( "abcdefg", value.string_value() );
  EXPECT_EQ( "abcdefg", value.decompile() );
}

TEST_F(ParserTest, simple_string2b)
{
  // " で囲まれていれば空白を含んでもOK
  istringstream buf(": \"abc def\";\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_string(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( "abc def", value.string_value() );
  EXPECT_EQ( "\"abc def\"", value.decompile() );
}

TEST_F(ParserTest, simple_string3)
{
  // 先頭が数字でもOK
  istringstream buf(": 1.3a;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_string(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( "1.3a", value.string_value() );
  EXPECT_EQ( "\"1.3a\"", value.decompile() );
}

TEST_F(ParserTest, simple_delay_model1)
{
  istringstream buf(": generic_cmos;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_delay_model(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibDelayModel::generic_cmos, value.delay_model_value() );
  EXPECT_EQ( "generic_cmos", value.decompile() );
}

TEST_F(ParserTest, simple_delay_model2)
{
  istringstream buf(": table_lookup;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_delay_model(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibDelayModel::table_lookup, value.delay_model_value() );
  EXPECT_EQ( "table_lookup", value.decompile() );
}

TEST_F(ParserTest, simple_delay_model3)
{
  istringstream buf(": piecewise_cmos;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_delay_model(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibDelayModel::piecewise_cmos, value.delay_model_value() );
  EXPECT_EQ( "piecewise_cmos", value.decompile() );
}

TEST_F(ParserTest, simple_delay_model4)
{
  istringstream buf(": cmos2;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_delay_model(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibDelayModel::cmos2, value.delay_model_value() );
  EXPECT_EQ( "cmos2", value.decompile() );
}

TEST_F(ParserTest, simple_delay_model5)
{
  istringstream buf(": dcm;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_delay_model(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibDelayModel::dcm, value.delay_model_value() );
  EXPECT_EQ( "dcm", value.decompile() );
}

TEST_F(ParserTest, simple_delay_model6)
{
  // 不適切な文字列．
  istringstream buf(": abcdef;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_delay_model(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 3 - 8: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: abcdef: Illegal value for 'delay_model'. 'generic_cmos', 'table_lookup', 'piecewise_cmos', 'cmos2', 'dcm' or 'polynomial' are expected.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, simple_direction1)
{
  istringstream buf(": input;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_direction(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibDirection::input, value.direction_value() );
  EXPECT_EQ( "input", value.decompile() );
}

TEST_F(ParserTest, simple_direction2)
{
  istringstream buf(": output;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_direction(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibDirection::output, value.direction_value() );
  EXPECT_EQ( "output", value.decompile() );
}

TEST_F(ParserTest, simple_direction3)
{
  istringstream buf(": inout;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_direction(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibDirection::inout, value.direction_value() );
  EXPECT_EQ( "inout", value.decompile() );
}

TEST_F(ParserTest, simple_direction4)
{
  istringstream buf(": internal;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_direction(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibDirection::internal, value.direction_value() );
  EXPECT_EQ( "internal", value.decompile() );
}

TEST_F(ParserTest, simple_direction5)
{
  // 不適切な文字列
  istringstream buf(": 0.1;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_direction(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 3 - 5: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: 0.1: Illegal value for 'direction'. 'input', 'output', 'inout' or 'internal' are expected.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, simple_timing_sense1)
{
  istringstream buf(": positive_unate;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_sense(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingSense::positive_unate, value.timing_sense_value() );
  EXPECT_EQ( "positive_unate", value.decompile() );
}

TEST_F(ParserTest, simple_timing_sense2)
{
  istringstream buf(": negative_unate;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_sense(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingSense::negative_unate, value.timing_sense_value() );
  EXPECT_EQ( "negative_unate", value.decompile() );
}

TEST_F(ParserTest, simple_timing_sense3)
{
  istringstream buf(": non_unate;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_sense(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingSense::non_unate, value.timing_sense_value() );
  EXPECT_EQ( "non_unate", value.decompile() );
}

TEST_F(ParserTest, simple_timing_sense4)
{
  // 不適切な文字列
  istringstream buf(": unate;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_sense(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 3 - 7: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: unate: Illegal value for 'timing_sense'. Only 'positive_unate', 'negative_unate', or 'non_unate' are allowed here.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, simple_timing_type1)
{
  istringstream buf(": combinational;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::combinational, value.timing_type_value() );
  EXPECT_EQ( "combinational", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type2)
{
  istringstream buf(": combinational_rise;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::combinational_rise, value.timing_type_value() );
  EXPECT_EQ( "combinational_rise", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type3)
{
  istringstream buf(": combinational_fall;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::combinational_fall, value.timing_type_value() );
  EXPECT_EQ( "combinational_fall", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type4)
{
  istringstream buf(": three_state_enable;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::three_state_enable, value.timing_type_value() );
  EXPECT_EQ( "three_state_enable", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type5)
{
  istringstream buf(": three_state_disable;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::three_state_disable, value.timing_type_value() );
  EXPECT_EQ( "three_state_disable", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type6)
{
  istringstream buf(": three_state_enable_rise;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::three_state_enable_rise, value.timing_type_value() );
  EXPECT_EQ( "three_state_enable_rise", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type7)
{
  istringstream buf(": three_state_enable_fall;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::three_state_enable_fall, value.timing_type_value() );
  EXPECT_EQ( "three_state_enable_fall", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type8)
{
  istringstream buf(": three_state_disable_rise;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::three_state_disable_rise, value.timing_type_value() );
  EXPECT_EQ( "three_state_disable_rise", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type9)
{
  istringstream buf(": three_state_disable_fall;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::three_state_disable_fall, value.timing_type_value() );
  EXPECT_EQ( "three_state_disable_fall", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type10)
{
  istringstream buf(": rising_edge;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::rising_edge, value.timing_type_value() );
  EXPECT_EQ( "rising_edge", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type11)
{
  istringstream buf(": falling_edge;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::falling_edge, value.timing_type_value() );
  EXPECT_EQ( "falling_edge", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type12)
{
  istringstream buf(": preset;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::preset, value.timing_type_value() );
  EXPECT_EQ( "preset", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type13)
{
  istringstream buf(": clear;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::clear, value.timing_type_value() );
  EXPECT_EQ( "clear", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type14)
{
  istringstream buf(": hold_rising;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::hold_rising, value.timing_type_value() );
  EXPECT_EQ( "hold_rising", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type15)
{
  istringstream buf(": hold_falling;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::hold_falling, value.timing_type_value() );
  EXPECT_EQ( "hold_falling", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type16)
{
  istringstream buf(": setup_rising;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::setup_rising, value.timing_type_value() );
  EXPECT_EQ( "setup_rising", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type17)
{
  istringstream buf(": setup_falling;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::setup_falling, value.timing_type_value() );
  EXPECT_EQ( "setup_falling", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type18)
{
  istringstream buf(": recovery_rising;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::recovery_rising, value.timing_type_value() );
  EXPECT_EQ( "recovery_rising", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type19)
{
  istringstream buf(": recovery_falling;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::recovery_falling, value.timing_type_value() );
  EXPECT_EQ( "recovery_falling", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type20)
{
  istringstream buf(": skew_rising;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::skew_rising, value.timing_type_value() );
  EXPECT_EQ( "skew_rising", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type21)
{
  istringstream buf(": skew_falling;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::skew_falling, value.timing_type_value() );
  EXPECT_EQ( "skew_falling", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type22)
{
  istringstream buf(": removal_rising;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::removal_rising, value.timing_type_value() );
  EXPECT_EQ( "removal_rising", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type23)
{
  istringstream buf(": removal_falling;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::removal_falling, value.timing_type_value() );
  EXPECT_EQ( "removal_falling", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type24)
{
  istringstream buf(": non_seq_setup_rising;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::non_seq_setup_rising, value.timing_type_value() );
  EXPECT_EQ( "non_seq_setup_rising", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type25)
{
  istringstream buf(": non_seq_setup_falling;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::non_seq_setup_falling, value.timing_type_value() );
  EXPECT_EQ( "non_seq_setup_falling", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type26)
{
  istringstream buf(": non_seq_hold_rising;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::non_seq_hold_rising, value.timing_type_value() );
  EXPECT_EQ( "non_seq_hold_rising", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type27)
{
  istringstream buf(": non_seq_hold_falling;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::non_seq_hold_falling, value.timing_type_value() );
  EXPECT_EQ( "non_seq_hold_falling", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type28)
{
  istringstream buf(": nochange_high_high;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::nochange_high_high, value.timing_type_value() );
  EXPECT_EQ( "nochange_high_high", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type29)
{
  istringstream buf(": nochange_high_low;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::nochange_high_low, value.timing_type_value() );
  EXPECT_EQ( "nochange_high_low", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type30)
{
  istringstream buf(": nochange_low_high;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::nochange_low_high, value.timing_type_value() );
  EXPECT_EQ( "nochange_low_high", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type31)
{
  istringstream buf(": nochange_low_low;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibTimingType::nochange_low_low, value.timing_type_value() );
  EXPECT_EQ( "nochange_low_low", value.decompile() );
}

TEST_F(ParserTest, simple_timing_type32)
{
  // 不適切な文字列
  istringstream buf(": abc;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_timing_type(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 3 - 5: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: abc: Illegal value for 'timing_type'.\n",
	     msg_list[0]);
}

TEST_F(ParserTest, simple_vartype1)
{
  istringstream buf(": input_net_transition;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::input_net_transition, value.vartype_value() );
  EXPECT_EQ( "input_net_transition", value.decompile() );
}

TEST_F(ParserTest, simple_vartype2)
{
  istringstream buf(": total_output_net_capacitance;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::total_output_net_capacitance, value.vartype_value() );
  EXPECT_EQ( "total_output_net_capacitance", value.decompile() );
}

TEST_F(ParserTest, simple_vartype3)
{
  istringstream buf(": output_net_length;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::output_net_length, value.vartype_value() );
  EXPECT_EQ( "output_net_length", value.decompile() );
}

TEST_F(ParserTest, simple_vartype4)
{
  istringstream buf(": output_net_wire_cap;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::output_net_wire_cap, value.vartype_value() );
  EXPECT_EQ( "output_net_wire_cap", value.decompile() );
}

TEST_F(ParserTest, simple_vartype5)
{
  istringstream buf(": output_net_pin_cap;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::output_net_pin_cap, value.vartype_value() );
  EXPECT_EQ( "output_net_pin_cap", value.decompile() );
}

TEST_F(ParserTest, simple_vartype6)
{
  istringstream buf(": equal_or_opposite_output_net_capacitance;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::equal_or_opposite_output_net_capacitance, value.vartype_value() );
  EXPECT_EQ( "equal_or_opposite_output_net_capacitance", value.decompile() );
}

TEST_F(ParserTest, simple_vartype7)
{
  istringstream buf(": input_transition_time;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::input_transition_time, value.vartype_value() );
}

TEST_F(ParserTest, simple_vartype8)
{
  istringstream buf(": related_out_total_output_net_capacitance;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::related_out_total_output_net_capacitance, value.vartype_value() );
  EXPECT_EQ( "related_out_total_output_net_capacitance", value.decompile() );
}

TEST_F(ParserTest, simple_vartype9)
{
  istringstream buf(": related_out_output_net_length;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::related_out_output_net_length, value.vartype_value() );
  EXPECT_EQ( "related_out_output_net_length", value.decompile() );
}

TEST_F(ParserTest, simple_vartype10)
{
  istringstream buf(": related_out_output_net_wire_cap;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::related_out_output_net_wire_cap, value.vartype_value() );
  EXPECT_EQ( "related_out_output_net_wire_cap", value.decompile() );
}

TEST_F(ParserTest, simple_vartype11)
{
  istringstream buf(": related_out_output_net_pin_cap;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::related_out_output_net_pin_cap, value.vartype_value() );
  EXPECT_EQ( "related_out_output_net_pin_cap", value.decompile() );
}

TEST_F(ParserTest, simple_vartype12)
{
  istringstream buf(": constrained_pin_transition;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::constrained_pin_transition, value.vartype_value() );
  EXPECT_EQ( "constrained_pin_transition", value.decompile() );
}

TEST_F(ParserTest, simple_vartype13)
{
  istringstream buf(": related_pin_transition;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();

  EXPECT_EQ( ClibVarType::related_pin_transition, value.vartype_value() );
  EXPECT_EQ( "related_pin_transition", value.decompile() );
}

TEST_F(ParserTest, simple_vartype15)
{
  // 不適切な文字列
  istringstream buf(": abc;\n");
  Parser parser{buf, info, false, false};

  auto dst = simple_vartype(parser, attr);

  EXPECT_TRUE( dst == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "parser_test.lib: line 1, column 3 - 5: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: abc: Illegal value for 'variable_type'.\n",
	     msg_list[0]);
}

END_NAMESPACE_YM_DOTLIB
