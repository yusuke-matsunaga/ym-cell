
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


BEGIN_NAMESPACE_YM_DOTLIB

TEST(ScannerTest, read_token1)
{
  istringstream buf{":;,+-*/(){}\n"};
  FileInfo info{};
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

TEST(ScannerTest, read_token2)
{
  istringstream buf{"abcdef xyz 123\t456.78"};
  FileInfo info{};
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

TEST(ScannerTest, read_int1)
{
  istringstream buf{"123"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_int();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( 123, value1->int_value() );
}

TEST(ScannerTest, read_int2)
{
  // 浮動小数点数はNG
  istringstream buf{"123.45"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_int();

  EXPECT_TRUE( value1 == nullptr );
}

TEST(ScannerTest, read_int3)
{
  // 非数字文字で始まっているのでNG
  istringstream buf{"a123"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_int();

  EXPECT_TRUE( value1 == nullptr );
}

TEST(ScannerTest, read_float1)
{
  istringstream buf{"123.456"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_float();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( 123.456, value1->float_value() );
}

TEST(ScannerTest, read_float2)
{
  // 整数はOK
  istringstream buf{"123"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_float();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( 123, value1->float_value() );
}

TEST(ScannerTest, read_float3)
{
  // 非数字から始まっているのでNG
  istringstream buf{"f123"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_float();

  EXPECT_TRUE( value1 == nullptr );
}

TEST(ScannerTest, read_string1)
{
  // 整数はOK
  istringstream buf{"abcdefg"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_string();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( "abcdefg", value1->string_value() );
}

TEST(ScannerTest, read_string2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"abcdefg\""};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_string();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( "abcdefg", value1->string_value() );
}

TEST(ScannerTest, read_string3)
{
  // 先頭が数字でもOK
  istringstream buf{"1.2a"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_string();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( "1.2a", value1->string_value() );
}

TEST(ScannerTest, read_delay_model1)
{
  istringstream buf{"generic_cmos"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::GenericCmos, value1->delay_model_value() );
}

TEST(ScannerTest, read_delay_model2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"table_lookup\""};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::TableLookup, value1->delay_model_value() );
}

TEST(ScannerTest, read_delay_model3)
{
  istringstream buf{"piecewise_cmos"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::PiecewiseCmos, value1->delay_model_value() );
}

TEST(ScannerTest, read_delay_model4)
{
  istringstream buf{"cmos2"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::Cmos2, value1->delay_model_value() );
}

TEST(ScannerTest, read_delay_model5)
{
  istringstream buf{"dcm"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDelayModel::Dcm, value1->delay_model_value() );
}

TEST(ScannerTest, read_delay_model6)
{
  // 不適切な文字列
  istringstream buf{"dmos2"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_delay_model();

  ASSERT_TRUE( value1 == nullptr );
}

TEST(ScannerTest, read_direction1)
{
  istringstream buf{"input"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDirection::Input, value1->direction_value() );
}

TEST(ScannerTest, read_direction2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"output\""};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDirection::Output, value1->direction_value() );
}

TEST(ScannerTest, read_direction3)
{
  istringstream buf{"inout"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDirection::Inout, value1->direction_value() );
}

TEST(ScannerTest, read_direction4)
{
  istringstream buf{"internal"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibDirection::Internal, value1->direction_value() );
}

TEST(ScannerTest, read_direction5)
{
  // 不適切な文字列
  istringstream buf{"inbut"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_direction();

  ASSERT_TRUE( value1 == nullptr );
}

TEST(ScannerTest, read_timing_sense1)
{
  istringstream buf{"positive_unate"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_sense();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingSense::PosiUnate, value1->timing_sense_value() );
}

TEST(ScannerTest, read_timing_sense2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"negative_unate\""};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_sense();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingSense::NegaUnate, value1->timing_sense_value() );
}

TEST(ScannerTest, read_timing_sense3)
{
  istringstream buf{"non_unate"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_sense();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingSense::NonUnate, value1->timing_sense_value() );
}

TEST(ScannerTest, read_timing_sense4)
{
  // 不適切な文字列
  istringstream buf{"unate"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_sense();

  ASSERT_TRUE( value1 == nullptr );
}

TEST(ScannerTest, read_timing_type1)
{
  istringstream buf{"combinational"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::Combinational, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type2)
{
  // " で囲まれていてもOK
  istringstream buf{"\"combinational_rise\""};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::CombinationalRise, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type3)
{
  istringstream buf{"combinational_fall"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::CombinationalFall, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type4)
{
  istringstream buf{"three_state_enable"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateEnable, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type5)
{
  istringstream buf{"three_state_disable"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateDisable, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type6)
{
  istringstream buf{"three_state_enable_rise"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateEnableRise, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type7)
{
  istringstream buf{"three_state_enable_fall"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateEnableFall, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type8)
{
  istringstream buf{"three_state_disable_rise"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateDisableRise, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type9)
{
  istringstream buf{"three_state_disable_fall"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateDisableFall, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type10)
{
  istringstream buf{"rising_edge"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RisingEdge, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type11)
{
  istringstream buf{"falling_edge"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::FallingEdge, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type12)
{
  istringstream buf{"preset"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::Preset, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type13)
{
  istringstream buf{"clear"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::Clear, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type14)
{
  istringstream buf{"hold_rising"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::HoldRising, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type15)
{
  istringstream buf{"hold_falling"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::HoldFalling, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type16)
{
  istringstream buf{"setup_rising"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::SetupRising, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type17)
{
  istringstream buf{"setup_falling"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::SetupFalling, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type18)
{
  istringstream buf{"recovery_rising"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RecoveryRising, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type19)
{
  istringstream buf{"recovery_falling"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RecoveryFalling, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type20)
{
  istringstream buf{"skew_rising"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::SkewRising, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type21)
{
  istringstream buf{"skew_falling"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::SkewFalling, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type22)
{
  istringstream buf{"removal_rising"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RemovalRising, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type23)
{
  istringstream buf{"removal_falling"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::RemovalFalling, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type24)
{
  istringstream buf{"non_seq_setup_rising"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqSetupRising, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type25)
{
  istringstream buf{"non_seq_setup_falling"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqSetupFalling, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type26)
{
  istringstream buf{"non_seq_hold_rising"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqHoldRising, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type27)
{
  istringstream buf{"non_seq_hold_falling"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqHoldFalling, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type28)
{
  istringstream buf{"nochange_high_high"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeHighHigh, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type29)
{
  istringstream buf{"nochange_high_low"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeHighLow, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type30)
{
  istringstream buf{"nochange_low_high"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeLowHigh, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type31)
{
  istringstream buf{"nochange_low_low"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeLowLow, value1->timing_type_value() );
}

TEST(ScannerTest, read_timing_type32)
{
  // 不適切な文字列
  istringstream buf{"abc"};
  FileInfo info{};
  InputFileObj in{buf, info};
  Scanner scanner{in};

  auto value1 = scanner.read_timing_type();

  ASSERT_TRUE( value1 == nullptr );
}

END_NAMESPACE_YM_DOTLIB
