
/// @file CiFFCell.cc
/// @brief CiFFCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiFFCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiFFCell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiFFCell::type() const
{
  return ClibCellType::FF_S;
}

// @brief FFセルの時に true を返す．
bool
CiFFCell::is_ff() const
{
  return true;
}

// @brief 出力の論理式を持っている時に true を返す．
bool
CiFFCell::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return mExprList[pin_id].is_valid();
}

// @brief 論理セルの場合に出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
CiFFCell::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return mExprList[pin_id];
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFCell::clock_expr() const
{
  return mClock;
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFCell::next_state_expr() const
{
  return mNextState;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFRCell
//////////////////////////////////////////////////////////////////////

// @brief FFセル/ラッチセルの場合にクリア端子を持っていたら true を返す．
bool
CiFFRCell::has_clear() const
{
  return true;
}

// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
// @note クリア端子がない場合の返り値は不定
Expr
CiFFRCell::clear_expr() const
{
  return mClear;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFSCell
//////////////////////////////////////////////////////////////////////

// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiFFSCell::has_preset() const
{
  return true;
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
// @note プリセット端子がない場合の返り値は不定
Expr
CiFFSCell::preset_expr() const
{
  return mPreset;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFSRCell
//////////////////////////////////////////////////////////////////////

// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiFFSRCell::has_preset() const
{
  return true;
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
Expr
CiFFSRCell::preset_expr() const
{
  return mPreset;
}

// @brief clear_preset_var1 の取得
ClibCPV
CiFFSRCell::clear_preset_var1() const
{
  return static_cast<ClibCPV>(mCPV[0]);
}

// @brief clear_preset_var2 の取得
ClibCPV
CiFFSRCell::clear_preset_var2() const
{
  return static_cast<ClibCPV>(mCPV[1]);
}


//////////////////////////////////////////////////////////////////////
// クラス ClibFFMCell
//////////////////////////////////////////////////////////////////////

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFMCell::clock2_expr() const
{
  return mClock2;
}


//////////////////////////////////////////////////////////////////////
// クラス ClibFFMRCell
//////////////////////////////////////////////////////////////////////

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFMRCell::clock2_expr() const
{
  return mClock2;
}


//////////////////////////////////////////////////////////////////////
// クラス ClibFFMSCell
//////////////////////////////////////////////////////////////////////

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFMSCell::clock2_expr() const
{
  return mClock2;
}


//////////////////////////////////////////////////////////////////////
// クラス ClibFFMSRCell
//////////////////////////////////////////////////////////////////////

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFMSRCell::clock2_expr() const
{
  return mClock2;
}

END_NAMESPACE_YM_CLIB
