
/// @file ClibPin.cc
/// @brief ClibPin の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibPin.h"
#include "ci/CiPin.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibPin
//////////////////////////////////////////////////////////////////////

// @brief ピン名を返す．
string
ClibPin::name() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->name();
}

// @brief 方向を返す．
ClibDirection
ClibPin::direction() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->direction();
}

// @brief 入力ピンの時に true を返す．
bool
ClibPin::is_input() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->is_input();
}

// @brief 出力ピンの時に true を返す．
bool
ClibPin::is_output() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->is_output();
}

// @brief 入出力ピンの時に true を返す．
bool
ClibPin::is_inout() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->is_inout();
}

// @brief 内部ピンの時に true を返す．
bool
ClibPin::is_internal() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->is_internal();
}

// @brief ピン番号を返す．
SizeType
ClibPin::pin_id() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->pin_id();
}

// @brief 入力ピン番号を返す．
SizeType
ClibPin::input_id() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->input_id();
}

// @brief 負荷容量を返す．
ClibCapacitance
ClibPin::capacitance() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->capacitance();
}

// @brief 立ち上がり時の負荷容量を返す．
ClibCapacitance
ClibPin::rise_capacitance() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->rise_capacitance();
}

// @brief 立ち下がり時の負荷容量を返す．
ClibCapacitance
ClibPin::fall_capacitance() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->fall_capacitance();
}

// @brief 出力ピン番号を返す．
SizeType
ClibPin::output_id() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->output_id();
}

// @brief 最大ファンアウト容量を返す．
ClibCapacitance
ClibPin::max_fanout() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->max_fanout();
}

// @brief 最小ファンアウト容量を返す．
ClibCapacitance
ClibPin::min_fanout() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->min_fanout();
}

// @brief 最大負荷容量を返す．
ClibCapacitance
ClibPin::max_capacitance() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->max_capacitance();
}

// @brief 最小負荷容量を返す．
ClibCapacitance
ClibPin::min_capacitance() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->min_capacitance();
}

// @brief 最大遷移時間を返す．
ClibTime
ClibPin::max_transition() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->max_transition();
}

// @brief 最小遷移時間を返す．
ClibTime
ClibPin::min_transition() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->min_transition();
}

// @brief 論理式を返す．
Expr
ClibPin::function() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->function();
}

// @brief tristate 条件式を返す．
Expr
ClibPin::tristate() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->tristate();
}

// @brief 内部ピン番号を返す．
SizeType
ClibPin::internal_id() const
{
  ASSERT_COND( is_valid() );
  auto pin = mLibrary->_pin(mId);
  return pin->internal_id();
}

END_NAMESPACE_YM_CLIB
