
/// @file ClibSeqAttrTest.cc
/// @brief ClibSeqAttr のテスト
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include <gtest/gtest.h>
#include "ym/ClibSeqAttr.h"


BEGIN_NAMESPACE_YM_CLIB

TEST(ClibSeqAttrTest, constr0)
{
  ClibSeqAttr seq_attr{false, false, false};

  EXPECT_FALSE( seq_attr.has_slave_clock() );
  EXPECT_FALSE( seq_attr.has_clear() );
  EXPECT_FALSE( seq_attr.has_preset() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv1() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv2() );
}

TEST(ClibSeqAttrTest, constr1)
{
  ClibSeqAttr seq_attr{true, false, false};

  EXPECT_TRUE( seq_attr.has_slave_clock() );
  EXPECT_FALSE( seq_attr.has_clear() );
  EXPECT_FALSE( seq_attr.has_preset() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv1() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv2() );
}

TEST(ClibSeqAttrTest, constr2)
{
  ClibSeqAttr seq_attr{false, true, false};

  EXPECT_FALSE( seq_attr.has_slave_clock() );
  EXPECT_TRUE( seq_attr.has_clear() );
  EXPECT_FALSE( seq_attr.has_preset() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv1() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv2() );
}

TEST(ClibSeqAttrTest, constr3)
{
  ClibSeqAttr seq_attr{true, true, false};

  EXPECT_TRUE( seq_attr.has_slave_clock() );
  EXPECT_TRUE( seq_attr.has_clear() );
  EXPECT_FALSE( seq_attr.has_preset() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv1() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv2() );
}

TEST(ClibSeqAttrTest, constr4)
{
  ClibSeqAttr seq_attr{false, false, true};

  EXPECT_FALSE( seq_attr.has_slave_clock() );
  EXPECT_FALSE( seq_attr.has_clear() );
  EXPECT_TRUE( seq_attr.has_preset() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv1() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv2() );
}

TEST(ClibSeqAttrTest, constr5)
{
  ClibSeqAttr seq_attr{true, false, true};

  EXPECT_TRUE( seq_attr.has_slave_clock() );
  EXPECT_FALSE( seq_attr.has_clear() );
  EXPECT_TRUE( seq_attr.has_preset() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv1() );
  EXPECT_EQ( ClibCPV::X, seq_attr.cpv2() );
}

TEST(ClibSeqAttrTest, constr6)
{
  ASSERT_THROW(
    ClibSeqAttr seq_attr(false, true, true)
    , std::invalid_argument);
}

TEST(ClibSeqAttrTest, constr7)
{
  ASSERT_THROW(
    ClibSeqAttr seq_attr(true, true, true)
    , std::invalid_argument);
}

TEST(ClibSeqAttrTest, constr_LL)
{
  ClibSeqAttr seq_attr{false, ClibCPV::L, ClibCPV::L};

  EXPECT_FALSE( seq_attr.has_slave_clock() );
  EXPECT_TRUE( seq_attr.has_clear() );
  EXPECT_TRUE( seq_attr.has_preset() );
  EXPECT_EQ( ClibCPV::L, seq_attr.cpv1() );
  EXPECT_EQ( ClibCPV::L, seq_attr.cpv2() );
}
END_NAMESPACE_YM_CLIB
