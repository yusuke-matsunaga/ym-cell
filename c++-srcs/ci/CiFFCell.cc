
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

// @brief 組み合わせ論理タイプの時 true を返す．
bool
CiFFCell::is_logic() const
{
  return false;
}

// @brief FFセルの時に true を返す．
bool
CiFFCell::is_ff() const
{
  return true;
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
// クラス ClibFF2Cell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiFF2Cell::type() const
{
  return ClibCellType::FF_M;
}

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFF2Cell::clock2_expr() const
{
  return mClock2;
}

END_NAMESPACE_YM_CLIB
