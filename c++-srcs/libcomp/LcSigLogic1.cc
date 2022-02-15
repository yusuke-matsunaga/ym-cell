
/// @file LcSigLogic1.cc
/// @brief LcSigLogic1 の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "LcSigLogic1.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcSigLogic1
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
LcSigLogic1::LcSigLogic1(
  SizeType input_num, ///< [in] 入力数
  const Expr& expr    ///< [in] 出力の論理式
) : mInputNum{input_num},
    mExpr{expr}
{
}

// @brief 入力ピン数+入出力ピン数を返す．
SizeType
LcSigLogic1::input_num() const
{
  return mInputNum;
}

// @brief 出力ピン数+入出力ピン数を返す．
SizeType
LcSigLogic1::output_num() const
{
  return 1;
}

// @brief 入出力ピン数を返す．
SizeType
LcSigLogic1::inout_num() const
{
  return 0;
}

// @brief 内部ノード数を返す．
SizeType
LcSigLogic1::internal_node_num() const
{
  return 0;
}

// @brief セルの種類を返す．
ClibCellType
LcSigLogic1::type() const
{
  return ClibCellType::Logic;
}

// @brief 出力の論理式を持っている時に true を返す．
bool
LcSigLoci1::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( pid_in == 0 );
  return true;
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
LcSigLogic1::has_logic() const
{
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
LcSigLogic1::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( pin_id == 0 );
  return mExpr;
}

// @brief 内容を表す文字列を作る．
string
LcSigLogic1::str() const
{
}

END_NAMESPACE_YM_CLIB_LIBCOMP
