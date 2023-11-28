
/// @file ClibTiming.cc
/// @brief ClibTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibTiming.h"
#include "ym/ClibLut.h"
#include "ci/CiTiming.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibTiming
//////////////////////////////////////////////////////////////////////

// @brief 型の取得
ClibTimingType
ClibTiming::type() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->type();
}

// @brief タイミング条件式の取得
Expr
ClibTiming::timing_cond() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->timing_cond();
}

// @brief 立ち上がり固有遅延の取得
ClibTime
ClibTiming::intrinsic_rise() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->intrinsic_rise();
}

// @brief 立ち下がり固有遅延の取得
ClibTime
ClibTiming::intrinsic_fall() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->intrinsic_fall();
}

// @brief 立ち上がりスロープ遅延の取得
ClibTime
ClibTiming::slope_rise() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->slope_rise();
}

// @brief 立ち下がりスロープ遅延の取得
ClibTime
ClibTiming::slope_fall() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->slope_fall();
}

// @brief 立ち上がり遷移遅延の取得
ClibResistance
ClibTiming::rise_resistance() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->rise_resistance();
}

// @brief 立ち下がり遷移遅延の取得
ClibResistance
ClibTiming::fall_resistance() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->fall_resistance();
}

// @brief 立ち上がり遷移遅延の取得
ClibResistance
ClibTiming::rise_pin_resistance() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->rise_pin_resistance();
}

// @brief 立ち下がり遷移遅延の取得
ClibResistance
ClibTiming::fall_pin_resistance() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->fall_pin_resistance();
}

// @brief 立ち上がり？？？
ClibTime
ClibTiming::rise_delay_intercept() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->rise_delay_intercept();
}

// @brief 立ち下がり？？？
ClibTime
ClibTiming::fall_delay_intercept() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  return timing->fall_delay_intercept();
}

// @brief 立ち上がり遷移遅延テーブルの取得
ClibLut
ClibTiming::rise_transition() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  auto id = timing->rise_transition();
  return ClibLut{mLibrary, id};
}

// @brief 立ち下がり遷移遅延テーブルの取得
ClibLut
ClibTiming::fall_transition() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  auto id = timing->fall_transition();
  return ClibLut{mLibrary, id};
}

// @brief 立ち上がり伝搬遅延テーブルの取得
ClibLut
ClibTiming::rise_propagation() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  auto id = timing->rise_propagation();
  return ClibLut{mLibrary, id};
}

// @brief 立ち下がり伝搬遅延テーブルの取得
ClibLut
ClibTiming::fall_propagation() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  auto id = timing->fall_propagation();
  return ClibLut{mLibrary, id};
}

// @brief 立ち上がりセル遅延テーブルの取得
ClibLut
ClibTiming::cell_rise() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  auto id = timing->cell_rise();
  return ClibLut{mLibrary, id};
}

// @brief 立ち下がりセル遅延テーブルの取得
ClibLut
ClibTiming::cell_fall() const
{
  _check_valid();
  auto timing = mLibrary->_timing(mId);
  auto id = timing->cell_fall();
  return ClibLut{mLibrary, id};
}

END_NAMESPACE_YM_CLIB
