#ifndef LCSIGLOGIC_H
#define LCSIGLOGIC_H

/// @file LcSigLogic.h
/// @brief LcSigLogic のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/LcSignature.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcSigLogic LcSigLogic.h "LcSigLogic.h"
/// @brief 多出力論理セルグループ用のシグネチャ
//////////////////////////////////////////////////////////////////////
class LcSigLogic :
  public LcSignature
{
public:

  /// @brief コンストラクタ
  LcSigLogic(
    SizeType input_num,            ///< [in] 入力数
    SizeType output_num,           ///< [in] 出力数
    const vector<Expr>& expr_array ///< [in] 出力の論理式の配列
  );

  /// @brief デストラクタ
  ~LcSigLogic() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン数+入出力ピン数を返す．
  SizeType
  input_num() const override;

  /// @brief 出力ピン数+入出力ピン数を返す．
  SizeType
  output_num() const override;

  /// @brief 入出力ピン数を返す．
  SizeType
  inout_num() const override;

  /// @brief 内部ノード数を返す．
  SizeType
  internal_node_num() const override;

  /// @brief セルの種類を返す．
  ClibCellType
  type() const override;

  /// @brief 出力の論理式を持っている時に true を返す．
  bool
  has_logic(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const override;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  bool
  has_logic() const override;

  /// @brief 論理セルの場合に出力の論理式を返す．
  ///
  /// 論理式中の変数番号は入力ピン番号に対応する．
  Expr
  logic_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
  ) const override;

  /// @brief 内容を表す文字列を作る．
  string
  str() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力数
  SizeType mInputNum;

  // 出力数
  SizeType mOutputNum;

  // 出力の論理式の配列
  vector<Expr> mExprArray;

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCSIGLOGIC_H
