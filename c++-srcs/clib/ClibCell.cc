
/// @file ClibCell.cc
/// @brief ClibCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCell.h"
#include "ym/ClibPin.h"
#include "ym/ClibBus.h"
#include "ym/ClibBundle.h"
#include "ym/ClibTiming.h"
#include "ci/CiCell.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibCell
//////////////////////////////////////////////////////////////////////

// @brief 名前の取得
string
ClibCell::name() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->name();
}

// @brief 面積の取得
ClibArea
ClibCell::area() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->area();
}

// @brief ピン数の取得
SizeType
ClibCell::pin_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->pin_num();
}

// @brief ピンの取得
ClibPin
ClibCell::pin(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType pin_id = cell->pin(pos);
  return ClibPin{mLibrary, pin_id};
}

// @brief 名前からピンの取得
ClibPin
ClibCell::pin(
  const string& name
) const
{
  ASSERT_COND( is_valid() );
  SizeType pin_id = mLibrary->get_pin_id(mId, ShString{name});
  return ClibPin{mLibrary, pin_id};
}

// @brief ピンのリストを返す．
ClibPinList
ClibCell::pin_list() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return ClibPinList{mLibrary, cell->pin_list()};
}

// @brief 入力ピン数の取得
SizeType
ClibCell::input_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->input_num();
}

// @brief 入力ピンの取得
ClibPin
ClibCell::input(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType id = cell->input(pos);
  return ClibPin{mLibrary, id};
}

// @brief 入力ピンのリストの取得
ClibPinList
ClibCell::input_list() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return ClibPinList{mLibrary, cell->input_list()};
}

// @brief 出力ピン数の取得
SizeType
ClibCell::output_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->output_num();
}

// @brief 出力ピンの取得
ClibPin
ClibCell::output(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType id = cell->output(pos);
  return ClibPin{mLibrary, id};
}

// @brief 出力ピンのリストの取得
ClibPinList
ClibCell::output_list() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return ClibPinList{mLibrary, cell->output_list()};
}

// @brief 入出力ピン数の取得
SizeType
ClibCell::inout_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->inout_num();
}

// @brief 入出力ピンの取得
ClibPin
ClibCell::inout(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType id = cell->inout(pos);
  return ClibPin{mLibrary, id};
}

// @brief 入出力ピンのリストの取得
ClibPinList
ClibCell::inout_list() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return ClibPinList{mLibrary, cell->inout_begin(), cell->input_list().end()};
}

// @brief 入力ピン+入出力ピン数の取得
SizeType
ClibCell::input2_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->input2_num();
}

// @brief 入力ピンの取得
ClibPin
ClibCell::input2(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType id = cell->input(pos);
  return ClibPin{mLibrary, id};
}

// @brief 出力ピン+入出力ピン数の取得
SizeType
ClibCell::output2_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->output2_num();
}

// @brief 出力ピンの取得
ClibPin
ClibCell::output2(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType id = cell->output(pos);
  return ClibPin{mLibrary, id};
}

// @brief 内部ピン数の取得
SizeType
ClibCell::internal_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->internal_num();
}

// @brief 内部ピンの取得
ClibPin
ClibCell::internal(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType id = cell->internal(pos);
  return ClibPin{mLibrary, id};
}

// @brief 内部ピンのリストの取得
ClibPinList
ClibCell::internal_list() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return ClibPinList{mLibrary, cell->internal_list()};
}

// @brief バス数の取得
SizeType
ClibCell::bus_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->bus_num();
}

// @brief バスの取得
ClibBus
ClibCell::bus(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType id = cell->bus(pos);
  return ClibBus{mLibrary, id};
}

// @brief 名前からバスの取得
ClibBus
ClibCell::bus(
  const string& name
) const
{
  ASSERT_COND( is_valid() );
  auto id = mLibrary->get_bus_id(mId, ShString{name});
  return ClibBus{mLibrary, id};
}

// @brief バスのリストの取得
ClibBusList
ClibCell::bus_list() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return ClibBusList{mLibrary, cell->bus_list()};
}

// @brief バンドル数の取得
SizeType
ClibCell::bundle_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->bundle_num();
}

// @brief バンドルの取得
ClibBundle
ClibCell::bundle(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType id = cell->bundle(pos);
  return ClibBundle{mLibrary, id};
}

// @brief 名前からバンドルの取得
ClibBundle
ClibCell::bundle(
  const string& name
) const
{
  ASSERT_COND( is_valid() );
  SizeType id = mLibrary->get_bundle_id(mId, ShString{name});
  return ClibBundle{mLibrary, id};
}

// @brief バンドルのリストの取得
ClibBundleList
ClibCell::bundle_list() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return ClibBundleList{mLibrary, cell->bundle_list()};
}

// @brief タイミング情報の数を返す．
SizeType
ClibCell::timing_num() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->timing_num();
}

// @brief タイミング情報を返す．
ClibTiming
ClibCell::timing(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  SizeType id = cell->timing(pos);
  return ClibTiming{mLibrary, id};
}

// @brief タイミング情報のリストを返す．
ClibTimingList
ClibCell::timing_list() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return ClibTimingList{mLibrary, cell->timing_list()};
}

// @brief 条件に合致するタイミング情報のリストを返す．
ClibTimingList
ClibCell::timing_list(
  SizeType ipos,
  SizeType opos,
  ClibTimingSense sense
) const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return ClibTimingList{mLibrary, cell->timing_list(ipos, opos, sense)};
}

// @brief セルの種類を返す．
ClibCellType
ClibCell::type() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->type();
}

// @brief 組み合わせ論理タイプの時 true を返す．
bool
ClibCell::is_logic() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->is_logic();
}

// @brief FFタイプの時 true を返す．
bool
ClibCell::is_ff() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->is_ff();
}

// @brief ラッチタイプの時 true を返す．
bool
ClibCell::is_latch() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->is_latch();
}

// @brief 出力の論理式を持っている時に true を返す．
bool
ClibCell::has_logic(
  SizeType pin_id
) const
{
  return logic_expr(pin_id).is_valid();
}

// @brief 全ての出力が論理式を持っているときに true を返す．
bool
ClibCell::has_logic() const
{
  ASSERT_COND( is_valid() );
  for ( auto pin: output_list() ) {
    if ( !pin.function().is_valid() ) {
      return false;
    }
  }
  return true;
}

// @brief 論理セルの場合に出力の論理式を返す．
Expr
ClibCell::logic_expr(
  SizeType pin_id
) const
{
  ASSERT_COND( is_valid() );
  auto pin = output(pin_id);
  return pin.function();
}

// @brief 出力がトライステート条件を持っている時に true を返す．
bool
ClibCell::has_tristate(
  SizeType pin_id
) const
{
  return tristate_expr(pin_id).is_valid();
}

// @brief トライステートセルの場合にトライステート条件式を返す．
Expr
ClibCell::tristate_expr(
  SizeType pin_id
) const
{
  ASSERT_COND( is_valid() );
  auto pin = output(pin_id);
  return pin.tristate();
}

// @brief 内部変数1の名前を返す．
string
ClibCell::qvar1() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->qvar1();
}

// @brief 内部変数1の名前を返す．
string
ClibCell::qvar2() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->qvar2();
}

// @brief 非同期 clear を持つ時 true を返す．
bool
ClibCell::has_clear() const
{
  return clear_expr().is_valid();
}

// @brief FFセル/ラッチセルの場合にクリア条件を表す論理式を返す．
Expr
ClibCell::clear_expr() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->clear_expr();
}

// @brief 非同期 preset を持つ時 true を返す．
bool
ClibCell::has_preset() const
{
  return preset_expr().is_valid();
}

// @brief FFセル/ラッチセルの場合にプリセット条件を表す論理式を返す．
Expr
ClibCell::preset_expr() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->preset_expr();
}

// @brief clear と preset が同時にアクティブになった時の値1
ClibCPV
ClibCell::clear_preset_var1() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->clear_preset_var1();
}

// @brief clear と preset が同時にアクティブになった時の値1
ClibCPV
ClibCell::clear_preset_var2() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->clear_preset_var2();
}

// @brief FFセルの場合にクロックのアクティブエッジを表す論理式を返す．
Expr
ClibCell::clock_expr() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->clock_expr();
}

// @brief FFセルの場合にスレーブクロックのアクティブエッジを表す論理式を返す．
Expr
ClibCell::clock2_expr() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->clock2_expr();
}

// @brief FFセルの場合に次状態関数を表す論理式を返す．
Expr
ClibCell::next_state_expr() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->next_state_expr();
}

// @brief ラッチセルの場合にイネーブル条件を表す論理式を返す．
Expr
ClibCell::enable_expr() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->enable_expr();
}

// @brief ラッチセルの場合に2つめのイネーブル条件を表す論理式を返す．
Expr
ClibCell::enable2_expr() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->enable2_expr();
}

// @brief ラッチセルの場合にデータ入力関数を表す論理式を返す．
Expr
ClibCell::data_in_expr() const
{
  ASSERT_COND( is_valid() );
  auto cell = mLibrary->_cell(mId);
  return cell->data_in_expr();
}

END_NAMESPACE_YM_CLIB
