
/// @file CiLatchCell.cc
/// @brief CiLatchCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiLatchCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLatchCell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiLatchCell::type() const
{
  return ClibCellType::Latch_S;
}

// @brief ラッチセルの時に true を返す．
bool
CiLatchCell::is_latch() const
{
  return true;
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
Expr
CiLatchCell::data_in_expr() const
{
  return mDataIn;
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
Expr
CiLatchCell::enable_expr() const
{
  return mEnable;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatch2Cell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiLatch2Cell::type() const
{
  return ClibCellType::Latch_M;
}

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiLatch2Cell::enable2_expr() const
{
  return mEnable2;
}

END_NAMESPACE_YM_CLIB
