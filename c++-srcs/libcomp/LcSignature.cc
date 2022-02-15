
/// @file LcSignature.cc
/// @brief LcSignature の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/LcSignature.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcSignature
//////////////////////////////////////////////////////////////////////

// @brief 出力の論理式を持っている時に true を返す．
bool
LcSignature::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return false;
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
LcSignature::has_logic() const
{
  for ( int i = 0; i < output_num(); ++ i ) {
    if ( !has_logic(i) ) {
      return false;
    }
  }
  return true;
}

// @brief 出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
LcSignature::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return Expr::make_zero();
}

// @brief 出力がトライステート条件を持っている時に true を返す．
bool
LcSignature::has_tristate(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return false;
}

// @brief トライステートセルの場合にトライステート条件式を返す．
//
// - 論理式中の変数番号は入力ピン番号に対応する．
// - 通常の論理セルの場合には定数0を返す．
Expr
LcSignature::tristate_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return Expr::make_zero();
}

// @brief 非同期 clear を持つ時 true を返す．
//
// FF/ラッチセル以外の場合には返り値は不定
bool
LcSignature::has_clear() const
{
  return false;
}

// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
//
// クリア端子がない場合の返り値は不定
Expr
LcSignature::clear_expr() const
{
  return Expr::make_zero();
}

// @brief 非同期 preset を持つ時 true を返す．
//
// FF/ラッチセル以外の場合には返り値は不定
bool
LcSignature::has_preset() const
{
  return false;
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
//
// プリセット端子がない場合の返り値は不定
Expr
LcSignature::preset_expr() const
{
  return Expr::make_zero();
}

// @brief clear と preset が同時にアクティブになった時の値1
//
// has_clear() == true && has_preset() == true の時のみ意味を持つ．
// FF/ラッチセル以外の場合には返り値は不定
ClibCPV
LcSignature::clear_preset_var1() const
{
  return ClibCPV::X;
}

// @brief clear と preset が同時にアクティブになった時の値1
//
// has_clear() == true && has_preset() == true の時のみ意味を持つ．
// FF/ラッチセル以外の場合には返り値は不定
ClibCPV
LcSignature::clear_preset_var2() const
{
  return ClibCPV::X;
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
LcSignature::clock_expr() const
{
  return Expr::make_zero();
}

// @brief master-slave FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
LcSignature::clock2_expr() const
{
  return Expr::make_zero();
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
LcSignature::next_state_expr() const
{
  return Expr::make_zero();
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
LcSignature::enable_expr() const
{
  return Expr::make_zero();
}

// @brief master-slave ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
LcSignature::enable2_expr() const
{
  return Expr::make_zero();
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
LcSignature::data_in_expr() const
{
  return Expr::make_zero();
}

END_NAMESPACE_YM_CLIB_LIBCOMP
