
/// @file CgLogicSig_test.cc
/// @brief CgLogicSig_test の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "cgmgr/CgSignature.h"
#include "ym/ClibIOMap.h"


BEGIN_NAMESPACE_YM_CLIB

// 関数とそのシグネチャの期待値
struct FuncSpec
{
  TvFunc mFunc;
  TvFunc mTristate;
  vector<const char*> mSigList;
};

class Func0Test:
  public ::testing::TestWithParam<FuncSpec>
{
public:

  void
  check();

};

void
Func0Test::check()
{
  const auto& spec = GetParam();

  auto sig = CgSignature::make_logic_sig(spec.mFunc, spec.mTristate);
  EXPECT_EQ( spec.mSigList[0], sig.str() );
  SizeType base = 1;
  for ( bool oinv: {false, true} ) {
    auto xform = ClibIOMap{vector<ClibPinMap>{}, oinv};
    auto xsig = sig.xform(xform);
    EXPECT_EQ( spec.mSigList[base], xsig.str() );
    ++ base;
  }
}

TEST_P(Func0Test, xform)
{
  check();
}

INSTANTIATE_TEST_SUITE_P(CgLogicSig_test,
			 Func0Test,
			 ::testing::Values(
			   FuncSpec{TvFunc::make_invalid(),
				    TvFunc::make_invalid(),
				    {"C:0:1:0::",
				     "C:0:1:0::", "C:0:1:0::"}},
			   FuncSpec{TvFunc::make_zero(0),
				    TvFunc::make_invalid(),
				    {"C:0:1:0:0:",
				     "C:0:1:0:0:", "C:0:1:0:1:"}},
			   FuncSpec{TvFunc::make_one(0),
				    TvFunc::make_invalid(),
				    {"C:0:1:0:1:",
				     "C:0:1:0:1:", "C:0:1:0:0:"}}
			 ));

class Func1Test:
  public ::testing::TestWithParam<FuncSpec>
{
public:

  void
  check();
};

void
Func1Test::check()
{
  const auto& spec = GetParam();

  auto sig = CgSignature::make_logic_sig(spec.mFunc, spec.mTristate);
  EXPECT_EQ( spec.mSigList[0], sig.str() );
  SizeType base = 1;
  for ( bool oinv: {false, true} ) {
    for ( bool iinv: {false, true} ) {
      auto xform = ClibIOMap{{ClibPinMap{0, iinv}}, oinv};
      auto xsig = sig.xform(xform);
      EXPECT_EQ( spec.mSigList[base], xsig.str() );
      ++ base;
    }
  }
}

TEST_P(Func1Test, xform)
{
  check();
}

INSTANTIATE_TEST_SUITE_P(CgLogicSig_test,
			 Func1Test,
			 ::testing::Values(
			   FuncSpec{TvFunc::make_zero(1),
				    TvFunc::make_invalid(),
				    {"C:1:1:0:0:",
				     "C:1:1:0:0:", "C:1:1:0:0:",
				     "C:1:1:0:3:", "C:1:1:0:3:"}},
			   FuncSpec{TvFunc::make_one(1),
				    TvFunc::make_invalid(),
				    {"C:1:1:0:3:",
				     "C:1:1:0:3:", "C:1:1:0:3:",
				     "C:1:1:0:0:", "C:1:1:0:0:"}},
			   FuncSpec{TvFunc::make_posi_literal(1, VarId{0}),
				    TvFunc::make_invalid(),
				    {"C:1:1:0:1:",
				     "C:1:1:0:1:", "C:1:1:0:2:",
				     "C:1:1:0:2:", "C:1:1:0:1:"}},
			   FuncSpec{TvFunc::make_nega_literal(1, VarId{0}),
				    TvFunc::make_invalid(),
				    {"C:1:1:0:2:",
				     "C:1:1:0:2:", "C:1:1:0:1:",
				     "C:1:1:0:1:", "C:1:1:0:2:"}}
			 ));

class Func2Test:
  public ::testing::TestWithParam<FuncSpec>
{
public:

  void
  check();
};

void
Func2Test::check()
{
  const auto& spec = GetParam();

  auto sig = CgSignature::make_logic_sig(spec.mFunc, spec.mTristate);
  EXPECT_EQ( spec.mSigList[0], sig.str() );
  SizeType base = 1;
  for ( bool oinv: {false, true} ) {
    for ( bool i1inv: {false, true} ) {
      for ( bool i2inv: {false, true} ) {
	for ( SizeType mask: {0, 1} ) {
	  SizeType i0 = 0 ^ mask;
	  SizeType i1 = 1 ^ mask;
	  auto xform = ClibIOMap{{ClibPinMap{i0, i1inv}, ClibPinMap{i1, i2inv}}, oinv};
	  auto xsig = sig.xform(xform);
	  EXPECT_EQ( spec.mSigList[base], xsig.str() );
	  ++ base;
	}
      }
    }
  }
}

TEST_P(Func2Test, xform)
{
  check();
}

INSTANTIATE_TEST_SUITE_P(CgLogicSig_test,
			 Func2Test,
			 ::testing::Values(
			   FuncSpec{TvFunc::make_zero(2),
				    TvFunc::make_invalid(),
				    {"C:2:1:0:0:",
				     "C:2:1:0:0:", "C:2:1:0:0:",
				     "C:2:1:0:0:", "C:2:1:0:0:",
				     "C:2:1:0:0:", "C:2:1:0:0:",
				     "C:2:1:0:0:", "C:2:1:0:0:",
				     "C:2:1:0:F:", "C:2:1:0:F:",
				     "C:2:1:0:F:", "C:2:1:0:F:",
				     "C:2:1:0:F:", "C:2:1:0:F:",
				     "C:2:1:0:F:", "C:2:1:0:F:"}},
			   FuncSpec{TvFunc::make_one(2),
				    TvFunc::make_invalid(),
				    {"C:2:1:0:F:",
				     "C:2:1:0:F:", "C:2:1:0:F:",
				     "C:2:1:0:F:", "C:2:1:0:F:",
				     "C:2:1:0:F:", "C:2:1:0:F:",
				     "C:2:1:0:F:", "C:2:1:0:F:",
				     "C:2:1:0:0:", "C:2:1:0:0:",
				     "C:2:1:0:0:", "C:2:1:0:0:",
				     "C:2:1:0:0:", "C:2:1:0:0:",
				     "C:2:1:0:0:", "C:2:1:0:0:"}},
			   FuncSpec{TvFunc::make_posi_literal(2, VarId{0}),
				    TvFunc::make_invalid(),
				    {"C:2:1:0:5:",
				     "C:2:1:0:5:", "C:2:1:0:3:",
				     "C:2:1:0:5:", "C:2:1:0:3:",
				     "C:2:1:0:A:", "C:2:1:0:C:",
				     "C:2:1:0:A:", "C:2:1:0:C:",
				     "C:2:1:0:A:", "C:2:1:0:C:",
				     "C:2:1:0:A:", "C:2:1:0:C:",
				     "C:2:1:0:5:", "C:2:1:0:3:",
				     "C:2:1:0:5:", "C:2:1:0:3:"}},
			   FuncSpec{TvFunc::make_posi_literal(2, VarId{1}),
				    TvFunc::make_invalid(),
				    {"C:2:1:0:3:",
				     "C:2:1:0:3:", "C:2:1:0:5:",
				     "C:2:1:0:C:", "C:2:1:0:A:",
				     "C:2:1:0:3:", "C:2:1:0:5:",
				     "C:2:1:0:C:", "C:2:1:0:A:",
				     "C:2:1:0:C:", "C:2:1:0:A:",
				     "C:2:1:0:3:", "C:2:1:0:5:",
				     "C:2:1:0:C:", "C:2:1:0:A:",
				     "C:2:1:0:3:", "C:2:1:0:5:"}},
			   FuncSpec{TvFunc::make_posi_literal(2, VarId(0)) &
				    TvFunc::make_posi_literal(2, VarId{1}),
				    TvFunc::make_invalid(),
				    {"C:2:1:0:1:",
				     "C:2:1:0:1:", "C:2:1:0:1:",
				     "C:2:1:0:4:", "C:2:1:0:2:",
				     "C:2:1:0:2:", "C:2:1:0:4:",
				     "C:2:1:0:8:", "C:2:1:0:8:",
				     "C:2:1:0:E:", "C:2:1:0:E:",
				     "C:2:1:0:B:", "C:2:1:0:D:",
				     "C:2:1:0:D:", "C:2:1:0:B:",
				     "C:2:1:0:7:", "C:2:1:0:7:"}},
			   FuncSpec{TvFunc::make_posi_literal(2, VarId(0)) ^
				    TvFunc::make_posi_literal(2, VarId{1}),
				    TvFunc::make_invalid(),
				    {"C:2:1:0:6:",
				     "C:2:1:0:6:", "C:2:1:0:6:",
				     "C:2:1:0:9:", "C:2:1:0:9:",
				     "C:2:1:0:9:", "C:2:1:0:9:",
				     "C:2:1:0:6:", "C:2:1:0:6:",
				     "C:2:1:0:9:", "C:2:1:0:9:",
				     "C:2:1:0:6:", "C:2:1:0:6:",
				     "C:2:1:0:6:", "C:2:1:0:6:",
				     "C:2:1:0:9:", "C:2:1:0:9:"}},
			   FuncSpec{TvFunc::make_posi_literal(2, VarId{0}),
				    TvFunc::make_posi_literal(2, VarId{1}),
				    {"C:2:1:0:5:3",
				     "C:2:1:0:5:3", "C:2:1:0:3:5",
				     "C:2:1:0:5:C", "C:2:1:0:3:A",
				     "C:2:1:0:A:3", "C:2:1:0:C:5",
				     "C:2:1:0:A:C", "C:2:1:0:C:A",
				     "C:2:1:0:A:3", "C:2:1:0:C:5",
				     "C:2:1:0:A:C", "C:2:1:0:C:A",
				     "C:2:1:0:5:3", "C:2:1:0:3:5",
				     "C:2:1:0:5:C", "C:2:1:0:3:A"}}
			 ));

TEST(CgLogicSig_test, zero_3)
{
  auto f = TvFunc::make_zero(3);
  auto sig = CgSignature::make_logic_sig(f);
  auto sig_str = sig.str();

  EXPECT_EQ( "C:3:1:0:00:", sig_str );
}

TEST(CgLogicSig_test, one_3)
{
  auto f = TvFunc::make_one(3);
  auto sig = CgSignature::make_logic_sig(f);
  auto sig_str = sig.str();

  EXPECT_EQ( "C:3:1:0:FF:", sig_str );
}

TEST(CgLogicSig_test, zero_4)
{
  auto f = TvFunc::make_zero(4);
  auto sig = CgSignature::make_logic_sig(f);
  auto sig_str = sig.str();

  EXPECT_EQ( "C:4:1:0:0000:", sig_str );
}

TEST(CgLogicSig_test, one_4)
{
  auto f = TvFunc::make_one(4);
  auto sig = CgSignature::make_logic_sig(f);
  auto sig_str = sig.str();

  EXPECT_EQ( "C:4:1:0:FFFF:", sig_str );
}

END_NAMESPACE_YM_CLIB
