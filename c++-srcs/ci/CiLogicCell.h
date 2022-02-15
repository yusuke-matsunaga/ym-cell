#ifndef CILOGICCELL_H
#define CILOGICCELL_H

/// @file CiLogicCell.h
/// @brief CiLogicCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiLogicCell CiLogicCell.h "CiLogicCell.h"
/// @brief １出力の単純な論理セルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiLogicCell :
  public CiCell
{
public:

  /// @brief コンストラクタ
  CiLogicCell(
    CiCellLibrary* library,                  ///< [in] 親のセルライブラリ
    const ShString& name,                    ///< [in] 名前
    ClibArea area,                           ///< [in] 面積
#if 0
    const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
    CiOutputPin* output,                     ///< [in] 出力ピン
    const vector<CiTiming*>& timing_list,    ///< [in] タイミング情報のリスト
#endif
    const Expr& expr                         ///< [in] 出力の論理式
  );

  /// @brief デストラクタ
  ~CiLogicCell() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 機能情報の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief セルの種類を返す．
  ClibCellType
  type() const override;

  /// @brief 組み合わせ論理セルの時に true を返す．
  bool
  is_logic() const override;

  /// @brief 出力の論理式を持っている時に true を返す．
  bool
  has_logic(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;

  /// @brief 全ての出力が論理式を持っているときに true を返す．
  bool
  has_logic() const override;

  /// @brief 論理セルの場合に出力の論理式を返す．
  ///
  /// 論理式中の変数番号は入力ピン番号に対応する．
  Expr
  logic_expr(
    SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 出力の論理式
  Expr mExpr;

};

END_NAMESPACE_YM_CLIB

#endif // CILOGICCELL_H
