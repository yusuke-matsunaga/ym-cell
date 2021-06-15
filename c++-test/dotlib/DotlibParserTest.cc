
/// @file DotlibParserTest.cc
/// @brief DotlibParserTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "AstBool.h"
#include "AstDelayModel.h"
#include "AstDirection.h"
#include "AstFloat.h"
#include "AstInt.h"
#include "AstString.h"
#include "AstTimingSense.h"
#include "AstTimingType.h"
#include "AstVarType.h"
#include "ym/InputFileObj.h"
#include "ym/MsgMgr.h"
#include "ym/StreamMsgHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

class DotlibParserTest :
public ::testing::Test
{
public:

  DotlibParserTest()
    : mh{&cout}
  {
    MsgMgr::attach_handler(&mh);
  }

  FileInfo info;
  AstMgr mgr;
  AttrType attr_type;
  FileRegion loc;
  StreamMsgHandler mh;

};


TEST_F(DotlibParserTest, parse_bool1)
{
  istringstream buf{": true;\n"};
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstBool* dst = nullptr;
  bool stat = parser.parse_bool(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( true, dst->value() );
}

TEST_F(DotlibParserTest, parse_bool2)
{
  istringstream buf{": false;\n"};
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstBool* dst = nullptr;
  bool stat = parser.parse_bool(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( false, dst->value() );
}

TEST_F(DotlibParserTest, parse_bool3)
{
  istringstream buf{": fals;\n"};
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstBool* dst = nullptr;
  bool stat = parser.parse_bool(dst, attr_type, loc);

  EXPECT_FALSE( stat );
}

TEST_F(DotlibParserTest, parse_bool4)
{
  istringstream buf{": true;"};
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstBool* dst = nullptr;
  bool stat = parser.parse_bool(dst, attr_type, loc);

  EXPECT_FALSE( stat );
}

TEST_F(DotlibParserTest, parse_bool5)
{
  istringstream buf{": true\n"};
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstBool* dst = nullptr;
  bool stat = parser.parse_bool(dst, attr_type, loc);

  EXPECT_FALSE( stat );
}

TEST_F(DotlibParserTest, parse_bool6)
{
  istringstream buf{": true\n"};
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, true};

  const AstBool* dst = nullptr;
  bool stat = parser.parse_bool(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( true, dst->value() );
}

TEST_F(DotlibParserTest, parse_int1)
{
  istringstream buf(": 123;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstInt* dst = nullptr;
  bool stat = parser.parse_int(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( 123, dst->value() );
}

TEST_F(DotlibParserTest, parse_int2)
{
  istringstream buf(": a123;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstInt* dst = nullptr;
  bool stat = parser.parse_int(dst, attr_type, loc);

  EXPECT_FALSE( stat );
  EXPECT_TRUE( dst == nullptr );
}

TEST_F(DotlibParserTest, parse_float1)
{
  istringstream buf(": 123.456;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstFloat* dst = nullptr;
  bool stat = parser.parse_float(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( 123.456, dst->value() );
}

TEST_F(DotlibParserTest, parse_float2)
{
  istringstream buf(": 123;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstFloat* dst = nullptr;
  bool stat = parser.parse_float(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( 123, dst->value() );
}

TEST_F(DotlibParserTest, parse_float3)
{
  istringstream buf(": f123.456;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstFloat* dst = nullptr;
  bool stat = parser.parse_float(dst, attr_type, loc);

  EXPECT_FALSE( stat );
  EXPECT_TRUE( dst == nullptr );
}

TEST_F(DotlibParserTest, parse_string1)
{
  istringstream buf(": abcdefg;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstString* dst = nullptr;
  bool stat = parser.parse_string(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( "abcdefg", dst->value() );
}

TEST_F(DotlibParserTest, parse_string2)
{
  istringstream buf(": \"abcdefg\";\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstString* dst = nullptr;
  bool stat = parser.parse_string(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( "abcdefg", dst->value() );
}

TEST_F(DotlibParserTest, parse_string3)
{
  istringstream buf(": 1.3a;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstString* dst = nullptr;
  bool stat = parser.parse_string(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( "1.3a", dst->value() );
}

TEST_F(DotlibParserTest, parse_delay_model1)
{
  istringstream buf(": generic_cmos;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDelayModel* dst = nullptr;
  bool stat = parser.parse_delay_model(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibDelayModel::GenericCmos, dst->value() );
}

TEST_F(DotlibParserTest, parse_delay_model2)
{
  istringstream buf(": table_lookup;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDelayModel* dst = nullptr;
  bool stat = parser.parse_delay_model(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibDelayModel::TableLookup, dst->value() );
}

TEST_F(DotlibParserTest, parse_delay_model3)
{
  istringstream buf(": piecewise_cmos;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDelayModel* dst = nullptr;
  bool stat = parser.parse_delay_model(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibDelayModel::PiecewiseCmos, dst->value() );
}

TEST_F(DotlibParserTest, parse_delay_model4)
{
  istringstream buf(": cmos2;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDelayModel* dst = nullptr;
  bool stat = parser.parse_delay_model(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibDelayModel::Cmos2, dst->value() );
}

TEST_F(DotlibParserTest, parse_delay_model5)
{
  istringstream buf(": dcm;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDelayModel* dst = nullptr;
  bool stat = parser.parse_delay_model(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibDelayModel::Dcm, dst->value() );
}

TEST_F(DotlibParserTest, parse_delay_model6)
{
  istringstream buf(": abcdef;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDelayModel* dst = nullptr;
  bool stat = parser.parse_delay_model(dst, attr_type, loc);

  EXPECT_FALSE( stat );
  EXPECT_TRUE( dst == nullptr );
}

TEST_F(DotlibParserTest, parse_direction1)
{
  istringstream buf(": input;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDirection* dst = nullptr;
  bool stat = parser.parse_direction(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibDirection::Input, dst->value() );
}

TEST_F(DotlibParserTest, parse_direction2)
{
  istringstream buf(": output;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDirection* dst = nullptr;
  bool stat = parser.parse_direction(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibDirection::Output, dst->value() );
}

TEST_F(DotlibParserTest, parse_direction3)
{
  istringstream buf(": inout;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDirection* dst = nullptr;
  bool stat = parser.parse_direction(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibDirection::Inout, dst->value() );
}

TEST_F(DotlibParserTest, parse_direction4)
{
  istringstream buf(": internal;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDirection* dst = nullptr;
  bool stat = parser.parse_direction(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibDirection::Internal, dst->value() );
}

TEST_F(DotlibParserTest, parse_direction5)
{
  istringstream buf(": 0.1;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstDirection* dst = nullptr;
  bool stat = parser.parse_direction(dst, attr_type, loc);

  EXPECT_FALSE( stat );
  EXPECT_TRUE( dst == nullptr );
}

TEST_F(DotlibParserTest, parse_timing_sense1)
{
  istringstream buf(": positive_unate;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingSense* dst = nullptr;
  bool stat = parser.parse_timing_sense(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingSense::PosiUnate, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_sense2)
{
  istringstream buf(": negative_unate;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingSense* dst = nullptr;
  bool stat = parser.parse_timing_sense(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingSense::NegaUnate, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_sense3)
{
  istringstream buf(": non_unate;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingSense* dst = nullptr;
  bool stat = parser.parse_timing_sense(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingSense::NonUnate, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_sense4)
{
  istringstream buf(": unate;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingSense* dst = nullptr;
  bool stat = parser.parse_timing_sense(dst, attr_type, loc);

  EXPECT_FALSE( stat );
  EXPECT_TRUE( dst == nullptr );
}

TEST_F(DotlibParserTest, parse_timing_type1)
{
  istringstream buf(": combinational;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::Combinational, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type2)
{
  istringstream buf(": combinational_rise;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::CombinationalRise, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type3)
{
  istringstream buf(": combinational_fall;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::CombinationalFall, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type4)
{
  istringstream buf(": three_state_enable;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateEnable, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type5)
{
  istringstream buf(": three_state_disable;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateDisable, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type6)
{
  istringstream buf(": three_state_enable_rise;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateEnableRise, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type7)
{
  istringstream buf(": three_state_enable_fall;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateEnableFall, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type8)
{
  istringstream buf(": three_state_disable_rise;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateDisableRise, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type9)
{
  istringstream buf(": three_state_disable_fall;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::ThreeStateDisableFall, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type10)
{
  istringstream buf(": rising_edge;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::RisingEdge, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type11)
{
  istringstream buf(": falling_edge;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::FallingEdge, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type12)
{
  istringstream buf(": preset;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::Preset, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type13)
{
  istringstream buf(": clear;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::Clear, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type14)
{
  istringstream buf(": hold_rising;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::HoldRising, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type15)
{
  istringstream buf(": hold_falling;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::HoldFalling, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type16)
{
  istringstream buf(": setup_rising;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::SetupRising, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type17)
{
  istringstream buf(": setup_falling;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::SetupFalling, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type18)
{
  istringstream buf(": recovery_rising;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::RecoveryRising, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type19)
{
  istringstream buf(": recovery_falling;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::RecoveryFalling, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type20)
{
  istringstream buf(": skew_rising;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::SkewRising, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type21)
{
  istringstream buf(": skew_falling;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::SkewFalling, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type22)
{
  istringstream buf(": removal_rising;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::RemovalRising, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type23)
{
  istringstream buf(": removal_falling;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::RemovalFalling, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type24)
{
  istringstream buf(": non_seq_setup_rising;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqSetupRising, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type25)
{
  istringstream buf(": non_seq_setup_falling;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqSetupFalling, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type26)
{
  istringstream buf(": non_seq_hold_rising;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqHoldRising, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type27)
{
  istringstream buf(": non_seq_hold_falling;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::NonSeqHoldFalling, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type28)
{
  istringstream buf(": nochange_high_high;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeHighHigh, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type29)
{
  istringstream buf(": nochange_high_low;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeHighLow, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type30)
{
  istringstream buf(": nochange_low_high;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeLowHigh, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type31)
{
  istringstream buf(": nochange_low_low;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibTimingType::NochangeLowLow, dst->value() );
}

TEST_F(DotlibParserTest, parse_timing_type32)
{
  istringstream buf(": abc;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstTimingType* dst = nullptr;
  bool stat = parser.parse_timing_type(dst, attr_type, loc);

  EXPECT_FALSE( stat );
  EXPECT_TRUE( dst == nullptr );
}

TEST_F(DotlibParserTest, parse_vartype1)
{
  istringstream buf(": input_net_transition;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::InputNetTransition, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype2)
{
  istringstream buf(": total_output_net_capacitance;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::TotalOutputNetCapacitance, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype3)
{
  istringstream buf(": output_net_length;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::OutputNetLength, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype4)
{
  istringstream buf(": output_net_wire_cap;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::OutputNetWireCap, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype5)
{
  istringstream buf(": output_net_pin_cap;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::OutputNetPinCap, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype6)
{
  istringstream buf(": equal_or_opposite_output_net_capacitance;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::EqualOrOppositeOutputNetCapacitance, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype7)
{
  istringstream buf(": input_transition_time;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::InputTransitionTime, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype8)
{
  istringstream buf(": related_out_total_output_net_capacitance;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::RelatedOutTotalOutputNetCapacitance, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype9)
{
  istringstream buf(": related_out_output_net_length;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::RelatedOutOutputNetLength, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype10)
{
  istringstream buf(": related_out_output_net_wire_cap;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::RelatedOutOutputNetWireCap, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype11)
{
  istringstream buf(": related_out_output_net_pin_cap;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::RelatedOutOutputNetPinCap, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype12)
{
  istringstream buf(": constrained_pin_transition;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::ConstrainedPinTransition, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype13)
{
  istringstream buf(": related_pin_transition;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_TRUE( stat );
  ASSERT_TRUE( dst != nullptr );
  EXPECT_EQ( ClibVarType::RelatedPinTransition, dst->value() );
}

TEST_F(DotlibParserTest, parse_vartype15)
{
  istringstream buf(": abc;\n");
  InputFileObj in{buf, info};
  DotlibParser parser{in, mgr, false, false};

  const AstVarType* dst = nullptr;
  bool stat = parser.parse_vartype(dst, attr_type, loc);

  EXPECT_FALSE( stat );
  EXPECT_TRUE( dst == nullptr );
}

END_NAMESPACE_YM_DOTLIB
