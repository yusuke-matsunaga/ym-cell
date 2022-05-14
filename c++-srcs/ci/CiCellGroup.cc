
/// @file CiCellGroup.cc
/// @brief CiCellGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellGroup.h"
#include "ci/CiCellLibrary.h"
#include "ym/ClibCellList.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellGroup::CiCellGroup(
  SizeType id,
  const ClibCellClass* rep_class,
  const ClibIOMap& iomap
) : mId{id},
    mRepClass{rep_class},
    mIomap{iomap}
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
const ClibIOMap&
CiCellGroup::iomap() const
{
  return mIomap;
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
  return type() == ClibCellType::FF;
}

// @brief ラッチセルの時に true を返す．
bool
CiCellGroup::is_latch() const
{
  return type() == ClibCellType::Latch;
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

// @brief セルのリストを返す．
ClibCellList
CiCellGroup::cell_list() const
{
  return mCellList;
}

END_NAMESPACE_YM_CLIB
