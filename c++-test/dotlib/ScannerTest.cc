
/// @file ScannerTest.cc
/// @brief ScannerTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "Scanner.h"
#include "TokenType.h"
#include "ym/InputFileObj.h"
#include "ym/MsgMgr.h"
#include "ym/StrListMsgHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

class ScannerTest :
  public ::testing::Test
{
public:

  ScannerTest()
  {
    MsgMgr::attach_handler(&mh);
  }

  FileInfo info{"scanner_test.lib"};
  StrListMsgHandler mh;

};

TEST_F(ScannerTest, read_token1)
{
  istringstream buf{":;,+-*/(){}\n"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  TokenType exp_list[] = {
    TokenType::COLON,
    TokenType::SEMI,
    TokenType::COMMA,
    TokenType::PLUS,
    TokenType::MINUS,
    TokenType::MULT,
    TokenType::DIV,
    TokenType::LP,
    TokenType::RP,
    TokenType::LCB,
    TokenType::RCB,
    TokenType::NL,
    TokenType::END
  };

  for ( auto exp: exp_list ) {
    auto token = scanner.read_token();
    EXPECT_EQ ( exp, token.type() );
  }
}

TEST_F(ScannerTest, read_token2)
{
  istringstream buf{"abcdef xyz 123\t456.78"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto token1 = scanner.read_token();
  EXPECT_EQ( TokenType::SYMBOL, token1.type() );
  //EXPECT_TRUE( strcmp(scanner.cur_string(), "abcdef") == 0 );

  auto token2 = scanner.read_token();
  EXPECT_EQ( TokenType::SYMBOL, token2.type() );
  //EXPECT_TRUE( strcmp(scanner.cur_string(), "xyz") == 0 );

  auto token3 = scanner.read_token();
  EXPECT_EQ( TokenType::INT_NUM, token3.type() );
  //EXPECT_EQ( 123, scanner.cur_int() );

  auto token4 = scanner.read_token();
  EXPECT_EQ( TokenType::FLOAT_NUM, token4.type() );
  //EXPECT_EQ( 456.78, scanner.cur_float() );
}

TEST_F(ScannerTest, read_int1)
{
  istringstream buf{"123"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_int();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( 123, value1->int_value() );
}

TEST_F(ScannerTest, read_int2)
{
  // 浮動小数点数はNG
  istringstream buf{"123.45"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_int();

  EXPECT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 1 - 6: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: 123.45: Not an integer value(FLOAT).\n",
	     msg_list[0]);
}

TEST_F(ScannerTest, read_int3)
{
  // 非数字文字で始まっているのでNG
  istringstream buf{"a123"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_int();

  EXPECT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 1 - 4: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: a123: Not an integer value(SYMBOL).\n",
	     msg_list[0]);
}

TEST_F(ScannerTest, read_bool1)
{
  istringstream buf{"true"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_bool();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( true, value1->bool_value() );
}

TEST_F(ScannerTest, read_bool2)
{
  istringstream buf{"false"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_bool();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( false, value1->bool_value() );
}

TEST_F(ScannerTest, read_bool3)
{
  // 大文字小文字は区別される．
  istringstream buf{"True"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_bool();

  EXPECT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 1 - 4: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: True: Illegal value for boolean, only 'true' or 'false' are allowed.\n",
	     msg_list[0]);
}

TEST_F(ScannerTest, read_float1)
{
  istringstream buf{"123.456"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_float();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( 123.456, value1->float_value() );
}

TEST_F(ScannerTest, read_float2)
{
  // 整数はOK
  istringstream buf{"123"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_float();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( 123, value1->float_value() );
}

TEST_F(ScannerTest, read_float3)
{
  // 非数字から始まっているのでNG
  istringstream buf{"f123"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_float();

  EXPECT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 1 - 4: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: f123: Not a number value(SYMBOL).\n",
	     msg_list[0]);
}

TEST_F(ScannerTest, read_float4)
{
  // 非数字を含んでいるのでNG
  istringstream buf{"12.3f"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_float();

  EXPECT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 4: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: 12.3f: Illegal character for number value.\n",
	     msg_list[0]);
}

TEST_F(ScannerTest, read_string1)
{
  istringstream buf{"abcdefg"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_string();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( "abcdefg", value1->string_value() );
}

TEST_F(ScannerTest, read_string2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"abcdefg\""};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_string();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( "abcdefg", value1->string_value() );
}

TEST_F(ScannerTest, read_string3)
{
  // 先頭が数字でもOK
  istringstream buf{"1.2a"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_string();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( "1.2a", value1->string_value() );
}

TEST_F(ScannerTest, read_delay_model1)
{
  istringstream buf{"generic_cmos"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::GenericCmos, value1->delay_model_value() );
}

TEST_F(ScannerTest, read_delay_model2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"table_lookup\""};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::TableLookup, value1->delay_model_value() );
}

TEST_F(ScannerTest, read_delay_model3)
{
  istringstream buf{"piecewise_cmos"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::PiecewiseCmos, value1->delay_model_value() );
}

TEST_F(ScannerTest, read_delay_model4)
{
  istringstream buf{"cmos2"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::Cmos2, value1->delay_model_value() );
}

TEST_F(ScannerTest, read_delay_model5)
{
  istringstream buf{"dcm"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::Dcm, value1->delay_model_value() );
}

TEST_F(ScannerTest, read_delay_model6)
{
  // 不適切な文字列
  istringstream buf{"dmos2"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 1 - 5: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: dmos2: Illegal value for 'delay_model'. 'generic_cmos', 'table_lookup', 'piecewise_cmos', 'cmos2' or 'dcm' are expected.\n",
	     msg_list[0]);
}

TEST_F(ScannerTest, read_direction1)
{
  istringstream buf{"input"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDirection::Input, value1->direction_value() );
}

TEST_F(ScannerTest, read_direction2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"output\""};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDirection::Output, value1->direction_value() );
}

TEST_F(ScannerTest, read_direction3)
{
  istringstream buf{"inout"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDirection::Inout, value1->direction_value() );
}

TEST_F(ScannerTest, read_direction4)
{
  istringstream buf{"internal"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDirection::Internal, value1->direction_value() );
}

TEST_F(ScannerTest, read_direction5)
{
  // 不適切な文字列
  istringstream buf{"inbut"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 1 - 5: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: inbut: Illegal value for 'direction'. 'input', 'output', 'inout' or 'internal' are expected.\n",
	     msg_list[0]);
}

TEST_F(ScannerTest, read_timing_sense1)
{
  istringstream buf{"positive_unate"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_sense();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingSense::PosiUnate, value1->timing_sense_value() );
}

TEST_F(ScannerTest, read_timing_sense2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"negative_unate\""};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_sense();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingSense::NegaUnate, value1->timing_sense_value() );
}

TEST_F(ScannerTest, read_timing_sense3)
{
  istringstream buf{"non_unate"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_sense();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingSense::NonUnate, value1->timing_sense_value() );
}

TEST_F(ScannerTest, read_timing_sense4)
{
  // 不適切な文字列
  istringstream buf{"unate"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_sense();

  ASSERT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 1 - 5: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: unate: Illegal value for 'timing_sense'. Only 'positive_unate', 'negative_unate', or 'non_unate' are allowed here.\n",
	     msg_list[0]);
}

TEST_F(ScannerTest, read_timing_type1)
{
  istringstream buf{"combinational"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::Combinational, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"combinational_rise\""};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::CombinationalRise, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type3)
{
  istringstream buf{"combinational_fall"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::CombinationalFall, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type4)
{
  istringstream buf{"three_state_enable"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateEnable, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type5)
{
  istringstream buf{"three_state_disable"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateDisable, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type6)
{
  istringstream buf{"three_state_enable_rise"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateEnableRise, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type7)
{
  istringstream buf{"three_state_enable_fall"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateEnableFall, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type8)
{
  istringstream buf{"three_state_disable_rise"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateDisableRise, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type9)
{
  istringstream buf{"three_state_disable_fall"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateDisableFall, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type10)
{
  istringstream buf{"rising_edge"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RisingEdge, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type11)
{
  istringstream buf{"falling_edge"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::FallingEdge, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type12)
{
  istringstream buf{"preset"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::Preset, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type13)
{
  istringstream buf{"clear"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::Clear, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type14)
{
  istringstream buf{"hold_rising"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::HoldRising, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type15)
{
  istringstream buf{"hold_falling"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::HoldFalling, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type16)
{
  istringstream buf{"setup_rising"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::SetupRising, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type17)
{
  istringstream buf{"setup_falling"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::SetupFalling, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type18)
{
  istringstream buf{"recovery_rising"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RecoveryRising, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type19)
{
  istringstream buf{"recovery_falling"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RecoveryFalling, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type20)
{
  istringstream buf{"skew_rising"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::SkewRising, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type21)
{
  istringstream buf{"skew_falling"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::SkewFalling, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type22)
{
  istringstream buf{"removal_rising"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RemovalRising, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type23)
{
  istringstream buf{"removal_falling"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RemovalFalling, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type24)
{
  istringstream buf{"non_seq_setup_rising"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqSetupRising, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type25)
{
  istringstream buf{"non_seq_setup_falling"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqSetupFalling, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type26)
{
  istringstream buf{"non_seq_hold_rising"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqHoldRising, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type27)
{
  istringstream buf{"non_seq_hold_falling"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqHoldFalling, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type28)
{
  istringstream buf{"nochange_high_high"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeHighHigh, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type29)
{
  istringstream buf{"nochange_high_low"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeHighLow, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type30)
{
  istringstream buf{"nochange_low_high"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeLowHigh, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type31)
{
  istringstream buf{"nochange_low_low"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeLowLow, value1->timing_type_value() );
}

TEST_F(ScannerTest, read_timing_type32)
{
  // 不適切な文字列
  istringstream buf{"abc"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 1 - 3: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: abc: Illegal value for 'timing_type'.\n",
	     msg_list[0]);
}

TEST_F(ScannerTest, read_vartype1)
{
  istringstream buf{"input_net_transition"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::InputNetTransition, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype2)
{
  istringstream buf{"total_output_net_capacitance"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::TotalOutputNetCapacitance, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype3)
{
  istringstream buf{"output_net_length"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::OutputNetLength, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype4)
{
  istringstream buf{"output_net_wire_cap"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::OutputNetWireCap, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype5)
{
  istringstream buf{"output_net_pin_cap"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::OutputNetPinCap, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype6)
{
  istringstream buf{"equal_or_opposite_output_net_capacitance"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::EqualOrOppositeOutputNetCapacitance, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype7)
{
  istringstream buf{"input_transition_time"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::InputTransitionTime, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype8)
{
  istringstream buf{"related_out_total_output_net_capacitance"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::RelatedOutTotalOutputNetCapacitance, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype9)
{
  istringstream buf{"related_out_output_net_length"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::RelatedOutOutputNetLength, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype10)
{
  istringstream buf{"related_out_output_net_wire_cap"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::RelatedOutOutputNetWireCap, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype11)
{
  istringstream buf{"related_out_output_net_pin_cap"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::RelatedOutOutputNetPinCap, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype12)
{
  istringstream buf{"constrained_pin_transition"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::ConstrainedPinTransition, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype13)
{
  istringstream buf{"related_pin_transition"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibVarType::RelatedPinTransition, value1->vartype_value() );
}

TEST_F(ScannerTest, read_vartype14)
{
  istringstream buf{"related_pn_transition"};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_vartype();

  ASSERT_TRUE( value1 == nullptr );
  auto msg_list = mh.message_list();
  EXPECT_EQ( 1, msg_list.size() );
  EXPECT_EQ( "scanner_test.lib: line 1, column 1 - 21: (ERROR  ) [DOTLIB_SCANNER]: Syntax error: related_pn_transition: Illegal value for 'variable_type'.\n",
	     msg_list[0]);
}

END_NAMESPACE_YM_DOTLIB
