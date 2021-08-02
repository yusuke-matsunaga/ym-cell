
/// @file CiFFCell.cc
/// @brief CiFFCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiFFCell.h"
#include "ym/ClibFFInfo.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiFFCell
//////////////////////////////////////////////////////////////////////

// @brief FFセルの時に true を返す．
bool
CiFFCell::is_ff() const
{
  return true;
}

// @brief FFセルの場合にFFのピン情報を得る．
ClibFFInfo
CiFFCell::ff_info() const
{
  //return cell_group().ff_info();
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFCell::next_state_expr() const
{
  return mNextState;
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFCell::clock_expr() const
{
  return mClock;
}

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFFCell::clock2_expr() const
{
  return mClock2;
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
SizeType
CiFFSRCell::clear_preset_var1() const
{
  return mClearPresetVal[0];
}

// @brief clear_preset_var2 の取得
SizeType
CiFFSRCell::clear_preset_var2() const
{
  return mClearPresetVal[1];
}

END_NAMESPACE_YM_CLIB
