#ifndef CIGENLOGICCELL_H
#define CIGENLOGICCELL_H

/// @file CiGenLogicCell.h
/// @brief CiGenLogicCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CiLogicCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiGenLogicCell CiGenLogicCell.h "CiGenLogicCell.h"
/// @brief １出力のトライステート条件付き論理セルを表す CiCell の派生クラス
//////////////////////////////////////////////////////////////////////
class CiGenLogicCell :
  public CiCell
{
public:

  /// @brief コンストラクタ
  CiGenLogicCell(
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
  );

  /// @brief デストラクタ
  ~CiGenLogicCell() = default;


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

  // 出力の論理式のリスト
  vector<Expr> mExprList;

  // トライステート条件の論理式のリスト
  vector<Expr> mTriExprList;

};

END_NAMESPACE_YM_CLIB

#endif // CIGENLOGICCELL_H
