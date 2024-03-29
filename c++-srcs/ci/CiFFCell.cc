﻿
/// @file CiFFCell.cc
/// @brief CiFFCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiFFCell.h"
#include "ci/CiCellLibrary.h"
#include "cgmgr/CgSignature.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiFFCell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiFFCell::type() const
{
  return ClibCellType::FF;
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
Expr
CiFFCell::clock_expr() const
{
  return mClock;
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
Expr
CiFFCell::next_state_expr() const
{
  return mNextState;
}

// @brief シグネチャを返す．
CgSignature
CiFFCell::make_signature(
  const CiCellLibrary* library
) const
{
  SizeType ni = input_num();
  SizeType no = output_num();
  SizeType nb = inout_num();
  SizeType ni2 = ni + nb + 2;
  SizeType no2 = no + nb;
  vector<TvFunc> logic_list(no2);
  vector<TvFunc> tristate_list(no2);
  for ( SizeType i = 0; i < no2; ++ i ) {
    auto opin = library->_pin(output(i));
    logic_list[i] = opin->function().make_tv(ni2);
    tristate_list[i] = opin->tristate().make_tv(ni2);
  }
  TvFunc clock = clock_expr().make_tv(ni2);
  TvFunc clock2 = clock2_expr().make_tv(ni2);
  TvFunc next = next_state_expr().make_tv(ni2);
  TvFunc clear = clear_expr().make_tv(ni2);
  TvFunc preset = preset_expr().make_tv(ni2);
  return CgSignature::make_ff_sig(ni, no, nb,
				  logic_list, tristate_list,
				  clock, clock2, next,
				  clear, preset,
				  clear_preset_var1(),
				  clear_preset_var2());
}


//////////////////////////////////////////////////////////////////////
// クラス ClibFF2Cell
//////////////////////////////////////////////////////////////////////

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiFF2Cell::clock2_expr() const
{
  return mClock2;
}

END_NAMESPACE_YM_CLIB
