
/// @file CiCellGroup.cc
/// @brief CiCellGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellGroup.h"
#include "ci/CiCellLibrary.h"
#include "CiCellGroup_int.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellGroup::CiCellGroup(
  SizeType id,
  const ClibCellClass* rep_class,
  const NpnMapM& map
) : mId{id},
    mRepClass{rep_class},
    mMap{map}
{
}

// @brief ID番号を返す．
SizeType
CiCellGroup::id() const
{
  return mId;
}

// @brief 親のセルクラスを返す．
const ClibCellClass&
CiCellGroup::rep_class() const
{
  return *mRepClass;
}

// @brief 入力ピン数+入出力ピン数を返す．
SizeType
CiCellGroup::input_num() const
{
  return 0;
}

// @brief 出力ピン数+入出力ピン数を返す．
SizeType
CiCellGroup::output_num() const
{
  return 0;
}

// @brief 入出力ピン数を返す．
SizeType
CiCellGroup::inout_num() const
{
  return 0;
}

// @brief 内部ノード数を返す．
SizeType
CiCellGroup::internal_node_num() const
{
  return 0;
}

// @brief 代表クラスに対する変換マップを返す．
const NpnMapM&
CiCellGroup::map() const
{
  return mMap;
}

// @brief セルの種類を返す．
ClibCellType
CiCellGroup::type() const
{
  return ClibCellType::None;
}

// s@brief FFセルの時に true を返す．
bool
CiCellGroup::is_ff() const
{
  return type() == ClibCellType::FF_S || type() == ClibCellType::FF_M;
}

// @brief ラッチセルの時に true を返す．
bool
CiCellGroup::is_latch() const
{
  return type() == ClibCellType::Latch_S || type() == ClibCellType::Latch_M;
}

/// @brief 出力の論理式を持っている時に true を返す．
bool
CiCellGroup::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return false;
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiCellGroup::has_logic() const
{
  return false;
}

// @brief 論理セルの場合に出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
CiCellGroup::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return Expr::make_invalid();
}

// @brief 出力がトライステート条件を持っている時に true を返す．
bool
CiCellGroup::has_tristate(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return false;
}

// @brief トライステートセルの場合にトライステート条件式を返す．
//
// - 論理式中の変数番号は入力ピン番号に対応する．
// - 通常の論理セルの場合には定数0を返す．
Expr
CiCellGroup::tristate_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return Expr::make_invalid();
}

// @brief FFセル/ラッチセルの場合にクリア端子を持っていたら true を返す．
bool
CiCellGroup::has_clear() const
{
  return false;
}

// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
//
// クリア端子がない場合の返り値は不定
Expr
CiCellGroup::clear_expr() const
{
  return Expr::make_invalid();
}

// @brief FFセル/ラッチセルの場合にプリセット端子を持っていたら true を返す．
bool
CiCellGroup::has_preset() const
{
  return false;
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
//
// プリセット端子がない場合の返り値は不定
Expr
CiCellGroup::preset_expr() const
{
  return Expr::make_invalid();
}

// @brief clear_preset_var1 の取得
//
// FFセルとラッチセルの時に意味を持つ．
ClibCPV
CiCellGroup::clear_preset_var1() const
{
  return ClibCPV::X;
}

// @brief clear_preset_var2 の取得
//
// FFセルとラッチセルの時に意味を持つ．
ClibCPV
CiCellGroup::clear_preset_var2() const
{
  return ClibCPV::X;
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCellGroup::clock_expr() const
{
  return Expr::make_invalid();
}

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCellGroup::clock2_expr() const
{
  return Expr::make_invalid();
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCellGroup::next_state_expr() const
{
  return Expr::make_invalid();
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCellGroup::enable_expr() const
{
  return Expr::make_invalid();
}

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCellGroup::enable2_expr() const
{
  return Expr::make_invalid();
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
//
// それ以外の型の場合の返り値は不定
Expr
CiCellGroup::data_in_expr() const
{
  return Expr::make_invalid();
}

// @brief セル数を返す．
SizeType
CiCellGroup::cell_num() const
{
  return mCellList.size();
}

// @brief セルを返す．
const ClibCell&
CiCellGroup::cell(
  SizeType pos ///< [in] インデックス ( 0 <= pos < cell_num() )
) const
{
  ASSERT_COND( 0 <= pos && pos < cell_num() );
  return *mCellList[pos];
}

// @brief セルを追加する．
void
CiCellGroup::add_cell(
  CiCell* cell
)
{
  mCellList.push_back(cell);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLogic1CellGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiLogic1CellGroup::CiLogic1CellGroup(
  SizeType id,                    ///< [in] 番号
  const ClibCellClass* rep_class, ///< [in] 親のセルクラス
  const NpnMapM& map,             ///< [in] 変換マップ
  SizeType input_num,             ///< [in] 入力数
  const Expr& expr                ///< [in] 出力の論理式
) : CiCellGroup{id, rep_class, map},
    mInputNum{input_num},
    mExpr{expr}
{
}

// @brief 入力ピン数+入出力ピン数を返す．
SizeType
CiLogic1CellGroup::input_num() const
{
  return mInputNum;
}

// @brief 出力ピン数+入出力ピン数を返す．
SizeType
CiLogic1CellGroup::output_num() const
{
  return 1;
}

// @brief 入出力ピン数を返す．
SizeType
CiLogic1CellGroup::inout_num() const
{
  return 0;
}

// @brief 内部ノード数を返す．
SizeType
CiLogic1CellGroup::internal_node_num() const
{
  return 0;
}

// @brief セルの種類を返す．
ClibCellType
CiLogic1CellGroup::type() const
{
  return ClibCellType::Logic;
}

// @brief 出力の論理式を持っている時に true を返す．
bool
CiLogic1CellGroup::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( pin_id == 0 );
  return true;
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiLogic1CellGroup::has_logic() const
{
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
CiLogic1CellGroup::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( pin_id == 0 );
  return mExpr;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLogicCellGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiLogicCellGroup::CiLogicCellGroup(
  SizeType id,                       ///< [in] 番号
  const ClibCellClass* rep_class,    ///< [in] 親のセルクラス
  const NpnMapM& map,                ///< [in] 変換マップ
  SizeType input_num,                ///< [in] 入力数
  SizeType output_num,               ///< [in] 出力数
  SizeType inout_num,                ///< [in] 入出力数
  const vector<Expr>& expr_array,    ///< [in] 出力の論理式
  const vector<Expr>& tristate_array ///< [in] 出力の論理式
) : CiCellGroup{id, rep_class, map},
    mInputNum{input_num},
    mOutputNum{output_num},
    mInoutNum{inout_num},
    mExprArray{expr_array},
    mTristateArray{tristate_array}
{
}

// @brief 入力ピン数+入出力ピン数を返す．
SizeType
CiLogicCellGroup::input_num() const
{
  return mInputNum;
}

// @brief 出力ピン数+入出力ピン数を返す．
SizeType
CiLogicCellGroup::output_num() const
{
  return mOutputNum;
}

// @brief 入出力ピン数を返す．
SizeType
CiLogicCellGroup::inout_num() const
{
  return mInoutNum;
}

// @brief 内部ノード数を返す．
SizeType
CiLogicCellGroup::internal_node_num() const
{
  return 0;
}

// @brief セルの種類を返す．
ClibCellType
CiLogicCellGroup::type() const
{
  return ClibCellType::Logic;
}

// @brief 出力の論理式を持っている時に true を返す．
bool
CiLogicCellGroup::has_logic(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  return logic_expr(pin_id).is_valid();
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
CiLogicCellGroup::has_logic() const
{
  for ( int i = 0; i < output_num(); ++ i ) {
    if ( !has_logic(i) ) {
      return false;
    }
  }
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
//
// 論理式中の変数番号は入力ピン番号に対応する．
Expr
CiLogicCellGroup::logic_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return mExprArray[pin_id];
}

// @brief 出力がトライステート条件を持っている時に true を返す．
bool
CiLogicCellGroup::has_tristate(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num() )
) const
{
  return !tristate_expr(pin_id).is_zero();
}

// @brief トライステートセルの場合にトライステート条件式を返す．
//
// - 論理式中の変数番号は入力ピン番号に対応する．
// - 通常の論理セルの場合には定数0を返す．
Expr
CiLogicCellGroup::tristate_expr(
  SizeType pin_id ///< [in] 出力ピン番号 ( 0 <= pin_id < output_num2() )
) const
{
  ASSERT_COND( 0 <= pin_id && pin_id < output_num() );
  return mTristateArray[pin_id];
}


END_NAMESPACE_YM_CLIB
