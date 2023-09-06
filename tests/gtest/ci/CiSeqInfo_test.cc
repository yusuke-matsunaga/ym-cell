
/// @file CiSeqInfo_test.cc
/// @brief CiSeqInfo_test の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "CiSeqInfo.h"


BEGIN_NAMESPACE_YM_CLIB

TEST(cell_CiSeqInfo_test, case0)
{
  CiSeqInfo info{false, false, false};
  auto index = info.encode_val();
  EXPECT_EQ( 0, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_FALSE( info.has_clear() );
  EXPECT_FALSE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case1)
{
  CiSeqInfo info{true, false, false};
  auto index = info.encode_val();
  EXPECT_EQ( 1, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_FALSE( info.has_clear() );
  EXPECT_FALSE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case2)
{
  CiSeqInfo info{false, true, false};
  auto index = info.encode_val();
  EXPECT_EQ( 2, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_FALSE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case3)
{
  CiSeqInfo info{true, true, false};
  auto index = info.encode_val();
  EXPECT_EQ( 3, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_FALSE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case4)
{
  CiSeqInfo info{false, false, true};
  auto index = info.encode_val();
  EXPECT_EQ( 4, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_FALSE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case5)
{
  CiSeqInfo info{true, false, true};
  auto index = info.encode_val();
  EXPECT_EQ( 5, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_FALSE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_LL)
{
  CiSeqInfo info{false, true, true, ClibCPV::L, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 6, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_LL)
{
  CiSeqInfo info{true, true, true, ClibCPV::L, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 7, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_HL)
{
  CiSeqInfo info{false, true, true, ClibCPV::H, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 8, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_HL)
{
  CiSeqInfo info{true, true, true, ClibCPV::H, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 9, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_NL)
{
  CiSeqInfo info{false, true, true, ClibCPV::N, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 10, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_NL)
{
  CiSeqInfo info{true, true, true, ClibCPV::N, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 11, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_TL)
{
  CiSeqInfo info{false, true, true, ClibCPV::T, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 12, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_TL)
{
  CiSeqInfo info{true, true, true, ClibCPV::T, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 13, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_XL)
{
  CiSeqInfo info{false, true, true, ClibCPV::X, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 14, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_XL)
{
  CiSeqInfo info{true, true, true, ClibCPV::X, ClibCPV::L};
  auto index = info.encode_val();
  EXPECT_EQ( 15, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_LH)
{
  CiSeqInfo info{false, true, true, ClibCPV::L, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 16, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_LH)
{
  CiSeqInfo info{true, true, true, ClibCPV::L, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 17, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_HH)
{
  CiSeqInfo info{false, true, true, ClibCPV::H, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 18, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_HH)
{
  CiSeqInfo info{true, true, true, ClibCPV::H, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 19, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_NH)
{
  CiSeqInfo info{false, true, true, ClibCPV::N, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 20, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_NH)
{
  CiSeqInfo info{true, true, true, ClibCPV::N, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 21, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_TH)
{
  CiSeqInfo info{false, true, true, ClibCPV::T, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 22, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_TH)
{
  CiSeqInfo info{true, true, true, ClibCPV::T, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 23, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_XH)
{
  CiSeqInfo info{false, true, true, ClibCPV::X, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 24, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_XH)
{
  CiSeqInfo info{true, true, true, ClibCPV::X, ClibCPV::H};
  auto index = info.encode_val();
  EXPECT_EQ( 25, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_LN)
{
  CiSeqInfo info{false, true, true, ClibCPV::L, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 26, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_LN)
{
  CiSeqInfo info{true, true, true, ClibCPV::L, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 27, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_HN)
{
  CiSeqInfo info{false, true, true, ClibCPV::H, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 28, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_HN)
{
  CiSeqInfo info{true, true, true, ClibCPV::H, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 29, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_NN)
{
  CiSeqInfo info{false, true, true, ClibCPV::N, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 30, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_NN)
{
  CiSeqInfo info{true, true, true, ClibCPV::N, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 31, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_TN)
{
  CiSeqInfo info{false, true, true, ClibCPV::T, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 32, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_TN)
{
  CiSeqInfo info{true, true, true, ClibCPV::T, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 33, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_XN)
{
  CiSeqInfo info{false, true, true, ClibCPV::X, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 34, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_XN)
{
  CiSeqInfo info{true, true, true, ClibCPV::X, ClibCPV::N};
  auto index = info.encode_val();
  EXPECT_EQ( 35, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_LT)
{
  CiSeqInfo info{false, true, true, ClibCPV::L, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 36, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_LT)
{
  CiSeqInfo info{true, true, true, ClibCPV::L, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 37, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_HT)
{
  CiSeqInfo info{false, true, true, ClibCPV::H, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 38, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_HT)
{
  CiSeqInfo info{true, true, true, ClibCPV::H, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 39, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_NT)
{
  CiSeqInfo info{false, true, true, ClibCPV::N, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 40, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_NT)
{
  CiSeqInfo info{true, true, true, ClibCPV::N, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 41, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_TT)
{
  CiSeqInfo info{false, true, true, ClibCPV::T, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 42, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_TT)
{
  CiSeqInfo info{true, true, true, ClibCPV::T, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 43, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_XT)
{
  CiSeqInfo info{false, true, true, ClibCPV::X, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 44, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_XT)
{
  CiSeqInfo info{true, true, true, ClibCPV::X, ClibCPV::T};
  auto index = info.encode_val();
  EXPECT_EQ( 45, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_LX)
{
  CiSeqInfo info{false, true, true, ClibCPV::L, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 46, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_LX)
{
  CiSeqInfo info{true, true, true, ClibCPV::L, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 47, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_HX)
{
  CiSeqInfo info{false, true, true, ClibCPV::H, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 48, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_HX)
{
  CiSeqInfo info{true, true, true, ClibCPV::H, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 49, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_NX)
{
  CiSeqInfo info{false, true, true, ClibCPV::N, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 50, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_NX)
{
  CiSeqInfo info{true, true, true, ClibCPV::N, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 51, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_TX)
{
  CiSeqInfo info{false, true, true, ClibCPV::T, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 52, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_TX)
{
  CiSeqInfo info{true, true, true, ClibCPV::T, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 53, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case6_XX)
{
  CiSeqInfo info{false, true, true, ClibCPV::X, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 54, index );
  EXPECT_FALSE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, case7_XX)
{
  CiSeqInfo info{true, true, true, ClibCPV::X, ClibCPV::X};
  auto index = info.encode_val();
  EXPECT_EQ( 55, index );
  EXPECT_TRUE( info.has_slave_clock() );
  EXPECT_TRUE( info.has_clear() );
  EXPECT_TRUE( info.has_preset() );
}

TEST(cell_CiSeqInfo_test, enumerate_all)
{
  for ( SizeType index = 0; index < CiSeqInfo::max_index(); ++ index ) {
    auto info = CiSeqInfo::decode_index(index);
    EXPECT_EQ( index, info.encode_val() );
  }
}

END_NAMESPACE_YM_CLIB
