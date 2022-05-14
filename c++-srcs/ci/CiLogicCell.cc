
/// @file CiLogicCell.cc
/// @brief CiLogicCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "CiLogicCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLogicCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiLogicCell::CiLogicCell(
  CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
  const ShString& name,                    ///< [in] 名前
  ClibArea area,                           ///< [in] 面積
  const Expr& expr                         ///< [in] 出力の論理式
) : CiCell{library, name, area},
    mExpr{expr}
{
}

// @brief セルの種類を返す．
ClibCellType
CiLogicCell::type() const
{
  return ClibCellType::Logic;
}

// @brief 組み合わせ論理セルの時に true を返す．
bool
CiLogicCell::is_logic() const
{
  return true;
}

// @brief 出力の論理式を持っている時に true を返す．
bool
CiLogicCell::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( pin_id == 0 );
  return true;
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiLogicCell::has_logic() const
{
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
CiLogicCell::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( pin_id == 0 );
  return mExpr;
}

END_NAMESPACE_YM_CLIB
