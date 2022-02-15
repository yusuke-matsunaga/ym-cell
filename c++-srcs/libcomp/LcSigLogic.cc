
/// @file LcSigLogic.cc
/// @brief LcSigLogic の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "LcSigLogic.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcSigLogic
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
LcSigLogic::LcSigLogic(
  SizeType input_num,            ///< [in] 入力数
  SizeType output_num,           ///< [in] 出力数
  const vector<Expr>& expr_array ///< [in] 出力の論理式の配列
) : mInputNum{input_num},
    mOutputNum{output_num},
    mExprArray{expr_array}
{
}

// @brief 入力ピン数+入出力ピン数を返す．
SizeType
LcSigLogic::input_num() const
{
  return mInputNum;
}

// @brief 出力ピン数+入出力ピン数を返す．
SizeType
LcSigLogic::output_num() const
{
  return mOutputNum;
}

// @brief 入出力ピン数を返す．
SizeType
LcSigLogic::inout_num() const
{
  return 0;
}

// @brief 内部ノード数を返す．
SizeType
LcSigLogic::internal_node_num() const
{
  return 0;
}

// @brief セルの種類を返す．
ClibCellType
LcSigLogic::type() const
{
  return ClibCellType::Logic;
}

// @brief 出力の論理式を持っている時に true を返す．
bool
LcSigLogic::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return true;
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
LcSigLogic::has_logic() const
{
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
LcSigLogic::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return mExprArray[pin_id];
}

// @brief 内容を表す文字列を作る．
string
LcSigLogic::str() const
{
}

END_NAMESPACE_YM_CLIB_LIBCOMP
