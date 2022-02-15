#ifndef CITRILOGICCELL_H
#define CITRILOGICCELL_H

/// @file CiTriLogicCell.h
/// @brief CiTriLogicCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiLogicCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiTriLogicCell CiTriLogicCell.h "CiTriLogicCell.h"
/// @brief １出力のトライステート条件付き論理セルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiTriLogicCell :
  public CiLogicCell
{
public:

  /// @brief コンストラクタ
  CiTriLogicCell(
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
  );

  /// @brief デストラクタ
  ~CiTriLogicCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力がトライステート条件を持っている時に true を返す．
  bool
  has_tristate(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;

  /// @brief トライステートセルの場合にトライステート条件式を返す．
  ///
  /// - 論理式中の変数番号は入力ピン番号に対応する．
  /// - 通常の論理セルの場合には定数0を返す．
  Expr
  tristate_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // トライステート条件の論理式
  Expr mTriExpr;

};

END_NAMESPACE_YM_CLIB

#endif // CITRILOGICCELL_H
