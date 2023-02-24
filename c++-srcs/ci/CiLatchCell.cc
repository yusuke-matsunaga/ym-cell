
/// @file CiLatchCell.cc
/// @brief CiLatchCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiLatchCell.h"
#include "ci/CiCellLibrary.h"
#include "cgmgr/CgSignature.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLatchCell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiLatchCell::type() const
{
  return ClibCellType::Latch;
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

// @brief シグネチャを返す．
CgSignature
CiLatchCell::make_signature(
  const CiCellLibrary* library
) const
{
  SizeType ni = input_num();
  SizeType no = output_num();
  SizeType nb = inout_num();
  SizeType ni2 = ni + nb + 2;
  SizeType no2 = no + nb + 2;
  vector<TvFunc> logic_list(no2);
  vector<TvFunc> tristate_list(no2);
  for ( SizeType i = 0; i < no2; ++ i ) {
    auto opin = library->_pin(output(i));
    logic_list[i] = opin->function().make_tv(ni2);
    tristate_list[i] = opin->tristate().make_tv(ni2);
  }
  TvFunc enable = enable_expr().make_tv(ni2);
  TvFunc enable2 = enable2_expr().make_tv(ni2);
  TvFunc data_in = data_in_expr().make_tv(ni2);
  TvFunc clear = clear_expr().make_tv(ni2);
  TvFunc preset = preset_expr().make_tv(ni2);
  return CgSignature::make_latch_sig(ni, no, nb, logic_list, tristate_list,
				     enable, enable2, data_in,
				     clear, preset,
				     clear_preset_var1(),
				     clear_preset_var2());
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatch2Cell
//////////////////////////////////////////////////////////////////////

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
// @note それ以外の型の場合の返り値は不定
Expr
CiLatch2Cell::enable2_expr() const
{
  return mEnable2;
}

END_NAMESPACE_YM_CLIB
