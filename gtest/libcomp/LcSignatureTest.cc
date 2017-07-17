
/// @file LcSignatureTest.cc
/// @brief LcSignatureTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017 Yusuke Matsunaga
/// All rights reserved.


#include "gtest/gtest.h"
#include "LcSignature.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CELL_LIBCOMP

// デフォルトコンストラクタ
TEST(LcSignatureTest, constr)
{
  LcSignature sig;

  EXPECT_EQ( LcSignature::kLogicType, sig.type() );
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
  Expr expr = Expr::const_zero();
  LcSignature sig(expr);

  EXPECT_EQ( LcSignature::kLogicType, sig.type() );
  EXPECT_EQ( 0, sig.input_num() );
  EXPECT_EQ( 1, sig.output_num() );

  EXPECT_EQ( TvFunc(), sig.clock() );
  EXPECT_EQ( TvFunc(), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::const_zero(0), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// バッファのシグネチャ
TEST(LcSignatureTest, buff)
{
  Expr expr = Expr::posi_literal(VarId(0));
  LcSignature sig(expr);

  EXPECT_EQ( LcSignature::kLogicType, sig.type() );
  EXPECT_EQ( 1, sig.input_num() );
  EXPECT_EQ( 1, sig.output_num() );

  EXPECT_EQ( TvFunc(), sig.clock() );
  EXPECT_EQ( TvFunc(), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(1, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// 2入力ANDのシグネチャ
TEST(LcSignatureTest, and2)
{
  Expr lit0 = Expr::posi_literal(VarId(0));
  Expr lit1 = Expr::posi_literal(VarId(1));
  Expr expr = lit0 & lit1;
  LcSignature sig(expr);

  TvFunc f0 = TvFunc::posi_literal(2, VarId(0));
  TvFunc f1 = TvFunc::posi_literal(2, VarId(1));
  TvFunc and2 = f0 & f1;
  EXPECT_EQ( LcSignature::kLogicType, sig.type() );
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
  LcSignature sig(LcSignature::kFFType,
		  true, false,
		  false, false);
  ymuint ni = 2;
  ymuint no = 1;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kFFType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

}

// FFのシグネチャ
// XQ あり，クリアなし，プリセットなし
TEST(LcSignatureTest, FF01)
{
  LcSignature sig(LcSignature::kFFType,
		  false, true,
		  false, false);
  ymuint ni = 2;
  ymuint no = 1;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kFFType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(1)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

}

// FFのシグネチャ
// Q, XQ あり，クリアなし，プリセットなし
TEST(LcSignatureTest, FF11)
{
  LcSignature sig(LcSignature::kFFType,
		  true, true,
		  false, false);
  ymuint ni = 2;
  ymuint no = 2;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kFFType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

  EXPECT_TRUE( sig.has_logic(1) );
  EXPECT_FALSE( sig.is_tristate(1) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(1)), sig.output_func(1) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(1) );

}

// FFのシグネチャ
// Q あり，クリアあり，プリセットなし
TEST(LcSignatureTest, FF10R)
{
  LcSignature sig(LcSignature::kFFType,
		  true, false,
		  true, false);
  ymuint ni = 3;
  ymuint no = 1;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kFFType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_TRUE( sig.has_clear() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(4)), sig.clear_func() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// FFのシグネチャ
// Q あり，クリアなし，プリセットあり
TEST(LcSignatureTest, FF10S)
{
  LcSignature sig(LcSignature::kFFType,
		  true, false,
		  false, true);
  ymuint ni = 3;
  ymuint no = 1;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kFFType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_TRUE( sig.has_preset() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(4)), sig.preset_func() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// FFのシグネチャ
// Q あり，クリアあり，プリセットあり
TEST(LcSignatureTest, FF10RS)
{
  LcSignature sig(LcSignature::kFFType,
		  true, false,
		  true, true);
  ymuint ni = 4;
  ymuint no = 1;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kFFType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_TRUE( sig.has_clear() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(4)), sig.clear_func() );

  EXPECT_TRUE( sig.has_preset() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(5)), sig.preset_func() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// ラッチのシグネチャ
// XQ あり，クリアなし，プリセットなし
TEST(LcSignatureTest, Latch01)
{
  LcSignature sig(LcSignature::kLatchType,
		  false, true,
		  false, false);
  ymuint ni = 2;
  ymuint no = 1;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kLatchType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(1)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

}

// ラッチのシグネチャ
// Q, XQ あり，クリアなし，プリセットなし
TEST(LcSignatureTest, Latch11)
{
  LcSignature sig(LcSignature::kLatchType,
		  true, true,
		  false, false);
  ymuint ni = 2;
  ymuint no = 2;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kLatchType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );

  EXPECT_TRUE( sig.has_logic(1) );
  EXPECT_FALSE( sig.is_tristate(1) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(1)), sig.output_func(1) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(1) );

}

// ラッチのシグネチャ
// Q あり，クリアあり，プリセットなし
TEST(LcSignatureTest, Latch10R)
{
  LcSignature sig(LcSignature::kLatchType,
		  true, false,
		  true, false);
  ymuint ni = 3;
  ymuint no = 1;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kLatchType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_TRUE( sig.has_clear() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(4)), sig.clear_func() );

  EXPECT_FALSE( sig.has_preset() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// ラッチのシグネチャ
// Q あり，クリアなし，プリセットあり
TEST(LcSignatureTest, Latch10S)
{
  LcSignature sig(LcSignature::kLatchType,
		  true, false,
		  false, true);
  ymuint ni = 3;
  ymuint no = 1;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kLatchType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_FALSE( sig.has_clear() );

  EXPECT_TRUE( sig.has_preset() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(4)), sig.preset_func() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// ラッチのシグネチャ
// Q あり，クリアあり，プリセットあり
TEST(LcSignatureTest, Latch10RS)
{
  LcSignature sig(LcSignature::kLatchType,
		  true, false,
		  true, true);
  ymuint ni = 4;
  ymuint no = 1;
  ymuint nfi = ni + 2;

  EXPECT_EQ( LcSignature::kLatchType, sig.type() );
  EXPECT_EQ( ni, sig.input_num() );
  EXPECT_EQ( no, sig.output_num() );

  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(2)), sig.clock() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(3)), sig.next_state() );

  EXPECT_TRUE( sig.has_clear() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(4)), sig.clear_func() );

  EXPECT_TRUE( sig.has_preset() );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(5)), sig.preset_func() );

  EXPECT_TRUE( sig.has_logic(0) );
  EXPECT_FALSE( sig.is_tristate(0) );
  EXPECT_EQ( TvFunc::posi_literal(nfi, VarId(0)), sig.output_func(0) );
  EXPECT_EQ( TvFunc(), sig.tristate_func(0) );
}

// Cell* からのコンストラクタを未テスト

END_NAMESPACE_YM_CELL_LIBCOMP
