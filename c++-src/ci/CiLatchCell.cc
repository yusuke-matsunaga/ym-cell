
/// @file CiLatchCell.cc
/// @brief CiLatchCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiLatchCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLatchCell
//////////////////////////////////////////////////////////////////////

// @brief ラッチセルの時に true を返す．
bool
CiLatchCell::is_latch() const
{
  return true;
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiLatchCell::data_in_expr() const
{
  return mDataIn;
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiLatchCell::enable_expr() const
{
  return mEnable;
}

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiLatchCell::enable2_expr() const
{
  return mEnable2;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchRCell
//////////////////////////////////////////////////////////////////////

// @brief ラッチセルの場合にクリア端子を持っていたら true を返す．
bool
CiLatchRCell::has_clear() const
{
  return true;
}

// @brief ラッチセルの場合にクリア条件を表す論理式を返す．
// @note クリア端子がない場合の返り値は不定
Expr
CiLatchRCell::clear_expr() const
{
  return mClear;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchSCell
//////////////////////////////////////////////////////////////////////

// @brief ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiLatchSCell::has_preset() const
{
  return true;
}

// @brief ラッチセルの場合にプリセット条件を表す論理式を返す．
// @note プリセット端子がない場合の返り値は不定
Expr
CiLatchSCell::preset_expr() const
{
  return mPreset;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchSRCell
//////////////////////////////////////////////////////////////////////

// @brief ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiLatchSRCell::has_preset() const
{
  return true;
}

// @brief ラッチセルの場合にプリセット条件を表す論理式を返す．
// @note プリセット端子がない場合の返り値は不定
Expr
CiLatchSRCell::preset_expr() const
{
  return mPreset;
}

// @brief clear_preset_var1 の取得
SizeType
CiLatchSRCell::clear_preset_var1() const
{
  return mClearPresetVal[0];
}

// @brief clear_preset_var2 の取得
SizeType
CiLatchSRCell::clear_preset_var2() const
{
  return mClearPresetVal[1];
}

END_NAMESPACE_YM_CLIB
