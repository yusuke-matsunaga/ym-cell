
/// @file CiTriLogicCell.cc
/// @brief CiTriLogicCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiTriLogicCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiTriLogicCell
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiTriLogicCell::CiTriLogicCell(
  CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
  const ShString& name,                    ///< [in] 名前
  ClibArea area,                           ///< [in] 面積
#if 0
  const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
  CiOutputPin* output,                     ///< [in] 出力ピン
  const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
  const Expr& expr,                        ///< [in] 出力の論理式
  const Expr& tristate_expr                ///< [in] トライステート条件式
) : CiLogicCell(library, name, area,
#if 0
		input_list, output,
		timing_list,
#endif
		expr),
    mTriExpr{tristate_expr}
{
}

// @brief 出力がトライステート条件を持っている時に true を返す．
bool
CiTriLogicCell::has_tristate(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( pin_id == 0 );
  return true;
}

// @brief トライステートセルの場合にトライステート条件式を返す．
//
// - 論理式中の変数番号は入力ピン番号に対応する．
// - 通常の論理セルの場合には定数0を返す．
Expr
CiTriLogicCell::tristate_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( pin_id == 0 );
  return mTriExpr;
}

END_NAMESPACE_YM_CLIB
