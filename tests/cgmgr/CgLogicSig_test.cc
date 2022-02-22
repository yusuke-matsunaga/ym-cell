
/// @file CgLogicSinature_test.cc
/// @brief CgLogicSinature_test の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "cgmgr/CgSignature.h"
#include "ym/ClibIOMap.h"


BEGIN_NAMESPACE_YM_CLIB

TEST(CgLogicSig_test, zero_0)
{
  TvFunc f{TvFunc::make_zero(0)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:0:1:0:0", sig_str );
}

TEST(CgLogicSig_test, one_0)
{
  TvFunc f{TvFunc::make_one(0)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:0:1:0:1", sig_str );
}

TEST(CgLogicSig_test, zero_1)
{
  TvFunc f{TvFunc::make_zero(1)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:1:1:0:0", sig_str );
}

TEST(CgLogicSig_test, one_1)
{
  TvFunc f{TvFunc::make_one(1)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:1:1:0:3", sig_str );
}

TEST(CgLogicSig_test, buf_1)
{
  TvFunc f{TvFunc::make_literal(1, VarId{0}, false)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:1:1:0:1", sig_str );
}

TEST(CgLogicSig_test, not_1)
{
  TvFunc f{TvFunc::make_literal(1, VarId{0}, true)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:1:1:0:2", sig_str );
}

TEST(CgLogicSig_test, zero_2)
{
  TvFunc f{TvFunc::make_zero(2)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:2:1:0:0", sig_str );
}

TEST(CgLogicSig_test, one_2)
{
  TvFunc f{TvFunc::make_one(2)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:2:1:0:F", sig_str );
}

TEST(CgLogicSig_test, and_2)
{
  TvFunc v0{TvFunc::make_literal(2, VarId{0}, false)};
  TvFunc v1{TvFunc::make_literal(2, VarId{1}, false)};
  auto f = v0 & v1;

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:2:1:0:1", sig_str );

  auto m = sig.rep_map();
  auto rep_sig = sig.xform(m);
  auto rep_str = rep_sig.str();

  EXPECT_EQ( "C:2:1:0:1", rep_str );
}

TEST(CgLogicSig_test, or_2)
{
  TvFunc v0{TvFunc::make_literal(2, VarId{0}, false)};
  TvFunc v1{TvFunc::make_literal(2, VarId{1}, false)};
  auto f = v0 | v1;

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:2:1:0:7", sig_str );

  auto m = sig.rep_map();
  auto rep_sig = sig.xform(m);
  auto rep_str = rep_sig.str();

  EXPECT_EQ( "C:2:1:0:1", rep_str );
}

TEST(CgLogicSig_test, xor_2)
{
  TvFunc v0{TvFunc::make_literal(2, VarId{0}, false)};
  TvFunc v1{TvFunc::make_literal(2, VarId{1}, false)};
  auto f = v0 ^ v1;

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:2:1:0:6", sig_str );

  auto m = sig.rep_map();
  auto rep_sig = sig.xform(m);
  auto rep_str = rep_sig.str();

  EXPECT_EQ( "C:2:1:0:6", rep_str );
}

TEST(CgLogicSig_test, xnor_2)
{
  TvFunc v0{TvFunc::make_literal(2, VarId{0}, false)};
  TvFunc v1{TvFunc::make_literal(2, VarId{1}, false)};
  auto f = ~(v0 ^ v1);

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:2:1:0:9", sig_str );

  auto m = sig.rep_map();
  auto rep_sig = sig.xform(m);
  auto rep_str = rep_sig.str();

  EXPECT_EQ( "C:2:1:0:6", rep_str );
}

TEST(CgLogicSig_test, zero_3)
{
  TvFunc f{TvFunc::make_zero(3)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:3:1:0:00", sig_str );
}

TEST(CgLogicSig_test, one_3)
{
  TvFunc f{TvFunc::make_one(3)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:3:1:0:FF", sig_str );
}

TEST(CgLogicSig_test, zero_4)
{
  TvFunc f{TvFunc::make_zero(4)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:4:1:0:0000", sig_str );
}

TEST(CgLogicSig_test, one_4)
{
  TvFunc f{TvFunc::make_one(4)};

  auto sig = CgSignature::make_logic_sig(f);

  auto sig_str = sig.str();

  EXPECT_EQ( "C:4:1:0:FFFF", sig_str );
}

END_NAMESPACE_YM_CLIB
