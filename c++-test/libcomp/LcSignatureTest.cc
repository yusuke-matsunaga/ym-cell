
/// @file LcSignatureTest.cc
/// @brief LcSignatureTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017 Yusuke Matsunaga
/// All rights reserved.


#include "gtest/gtest.h"
#include "lc/LcSignature.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

// デフォルトコンストラクタ
TEST(LcSignatureTest, constr)
{
  LcSignature sig;

  EXPECT_EQ( LcSignature::Type::Logic, sig.type() );
  EXPECT_EQ( 0, sig.input_num() );
  EXPECT_EQ( 0, sig.output_num() );

  EXPECT_EQ( TvFunc(), sig.clock() );
  EXPECT_EQ( TvFunc(), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );
}

// 定数０のシグネチャ
TEST(LcSignatureTest, const0)
{
  Expr expr = Expr::make_zero();
  LcSignature sig(expr);

  EXPECT_EQ( LcSignature::Type::Logic, sig.type() );
  EXPECT_EQ( 0, sig.input_num() );
  EXPECT_EQ( 1, sig.output_num() );

  EXPECT_EQ( TvFunc(), sig.clock() );
  EXPECT_EQ( TvFunc(), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_zero(0), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// バッファのシグネチャ
TEST(LcSignatureTest, buff)
{
  Expr expr = Expr::make_posi_literal(VarId(0));
  LcSignature sig(expr);

  EXPECT_EQ( LcSignature::Type::Logic, sig.type() );
  EXPECT_EQ( 1, sig.input_num() );
  EXPECT_EQ( 1, sig.output_num() );

  EXPECT_EQ( TvFunc(), sig.clock() );
  EXPECT_EQ( TvFunc(), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(1, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// 2入力ANDのシグネチャ
TEST(LcSignatureTest, and2)
{
  Expr lit0 = Expr::make_posi_literal(VarId(0));
  Expr lit1 = Expr::make_posi_literal(VarId(1));
  Expr expr = lit0 & lit1;
  LcSignature sig(expr);

  TvFunc f0 = TvFunc::make_posi_literal(2, VarId(0));
  TvFunc f1 = TvFunc::make_posi_literal(2, VarId(1));
  TvFunc and2 = f0 & f1;
  EXPECT_EQ( LcSignature::Type::Logic, sig.type() );
  EXPECT_EQ( 2, sig.input_num() );
  EXPECT_EQ( 1, sig.output_num() );

  EXPECT_EQ( TvFunc(), sig.clock() );
  EXPECT_EQ( TvFunc(), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( and2, sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// FFのシグネチャ
// Q あり，クリアなし，プリセットなし
TEST(LcSignatureTest, FF10)
{
  LcSignature sig(LcSignature::Type::FF,
		  true, false,
		  false, false);
  int ni = 2;
  int no = 1;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::FF, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

}

// FFのシグネチャ
// XQ あり，クリアなし，プリセットなし
TEST(LcSignatureTest, FF01)
{
  LcSignature sig(LcSignature::Type::FF,
		  false, true,
		  false, false);
  int ni = 2;
  int no = 1;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::FF, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(1)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

}

// FFのシグネチャ
// Q, XQ あり，クリアなし，プリセットなし
TEST(LcSignatureTest, FF11)
{
  LcSignature sig(LcSignature::Type::FF,
		  true, true,
		  false, false);
  int ni = 2;
  int no = 2;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::FF, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

  EXPECT_TRUE( sig.has_logic(1) );
  EXPECT_FALSE( sig.is_tristate(1) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(1)), sig.output_func(1) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(1) );

}

// FFのシグネチャ
// Q あり，クリアあり，プリセットなし
TEST(LcSignatureTest, FF10R)
{
  LcSignature sig(LcSignature::Type::FF,
		  true, false,
		  true, false);
  int ni = 3;
  int no = 1;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::FF, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_TRUE( sig.has_clear() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(4)), sig.clear_func() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// FFのシグネチャ
// Q あり，クリアなし，プリセットあり
TEST(LcSignatureTest, FF10S)
{
  LcSignature sig(LcSignature::Type::FF,
		  true, false,
		  false, true);
  int ni = 3;
  int no = 1;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::FF, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_TRUE( sig.has_preset() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(4)), sig.preset_func() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// FFのシグネチャ
// Q あり，クリアあり，プリセットあり
TEST(LcSignatureTest, FF10RS)
{
  LcSignature sig(LcSignature::Type::FF,
		  true, false,
		  true, true);
  int ni = 4;
  int no = 1;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::FF, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_TRUE( sig.has_clear() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(4)), sig.clear_func() );

  EXPECT_TRUE( sig.has_preset() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(5)), sig.preset_func() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// ラッチのシグネチャ
// XQ あり，クリアなし，プリセットなし
TEST(LcSignatureTest, Latch01)
{
  LcSignature sig(LcSignature::Type::Latch,
		  false, true,
		  false, false);
  int ni = 2;
  int no = 1;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::Latch, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(1)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

}

// ラッチのシグネチャ
// Q, XQ あり，クリアなし，プリセットなし
TEST(LcSignatureTest, Latch11)
{
  LcSignature sig(LcSignature::Type::Latch,
		  true, true,
		  false, false);
  int ni = 2;
  int no = 2;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::Latch, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

  EXPECT_TRUE( sig.has_logic(1) );
  EXPECT_FALSE( sig.is_tristate(1) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(1)), sig.output_func(1) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(1) );

}

// ラッチのシグネチャ
// Q あり，クリアあり，プリセットなし
TEST(LcSignatureTest, Latch10R)
{
  LcSignature sig(LcSignature::Type::Latch,
		  true, false,
		  true, false);
  int ni = 3;
  int no = 1;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::Latch, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_TRUE( sig.has_clear() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(4)), sig.clear_func() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// ラッチのシグネチャ
// Q あり，クリアなし，プリセットあり
TEST(LcSignatureTest, Latch10S)
{
  LcSignature sig(LcSignature::Type::Latch,
		  true, false,
		  false, true);
  int ni = 3;
  int no = 1;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::Latch, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_TRUE( sig.has_preset() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(4)), sig.preset_func() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// ラッチのシグネチャ
// Q あり，クリアあり，プリセットあり
TEST(LcSignatureTest, Latch10RS)
{
  LcSignature sig(LcSignature::Type::Latch,
		  true, false,
		  true, true);
  int ni = 4;
  int no = 1;
  int nfi = ni + 2;

  EXPECT_EQ( LcSignature::Type::Latch, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_TRUE( sig.has_clear() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(4)), sig.clear_func() );

  EXPECT_TRUE( sig.has_preset() );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(5)), sig.preset_func() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::make_posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// Cell* からのコンストラクタを未テスト

END_NAMESPACE_YM_CLIB_LIBCOMP
