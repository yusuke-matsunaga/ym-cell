
/// @file CiGenLogicCell.cc
/// @brief CiGenLogicCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiGenLogicCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiGenLogicCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiGenLogicCell::CiGenLogicCell(
  CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
  const ShString& name,                    ///< [in] 名前
  ClibArea area,                           ///< [in] 面積
#if 0
  const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
  const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
  const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
  const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
  const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
  const vector<Expr>& tristate_list        ///< [in] トライステート条件式のリスト
) : CiCell{
    library, name, area
#if 0
    input_list,
    output_list,
    inout_list,
    timing_list
#endif
  },
    mExprList{expr_list},
    mTriExprList{tristate_list}
{
}

// @brief セルの種類を返す．
ClibCellType
CiGenLogicCell::type() const
{
  return ClibCellType::Logic;
}

// @brief 組み合わせ論理セルの時に true を返す．
bool
CiGenLogicCell::is_logic() const
{
  return true;
}

// @brief 出力の論理式を持っている時に true を返す．
bool
CiGenLogicCell::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return mExprList[pin_id].is_valid();
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiGenLogicCell::has_logic() const
{
  for ( auto& expr: mExprList ) {
    if ( !expr.is_valid() ) {
      return false;
    }
  }
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
CiGenLogicCell::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return mExprList[pin_id];
}

// @brief 出力がトライステート条件を持っている時に true を返す．
bool
CiGenLogicCell::has_tristate(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return !mTriExprList[pin_id].is_zero();
}

// @brief トライステートセルの場合にトライステート条件式を返す．
//
// - 論理式中の変数番号は入力ピン番号に対応する．
// - 通常の論理セルの場合には定数0を返す．
Expr
CiGenLogicCell::tristate_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num2() );
  return mTriExprList[pin_id];
}

END_NAMESPACE_YM_CLIB
