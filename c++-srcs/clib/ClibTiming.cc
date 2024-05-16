
/// @file ClibTiming.cc
/// @brief ClibTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibTiming.h"
#include "ym/ClibLut.h"
#include "ci/CiTiming.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibTiming
//////////////////////////////////////////////////////////////////////

// @brief 内容を指定したコンストラクタ
ClibTiming::ClibTiming(
  const CiTiming* impl
) : mImpl{impl}
{
  if ( mImpl != nullptr ) {
    mImpl->inc_ref();
  }
}

// @brief デストラクタ
ClibTiming::~ClibTiming()
{
  if ( mImpl != nullptr ) {
    mImpl->dec_ref();
  }
}

// @brief 型の取得
ClibTimingType
ClibTiming::type() const
{
  _check_valid();
  return mImpl->type();
}

// @brief タイミング条件式の取得
Expr
ClibTiming::timing_cond() const
{
  _check_valid();
  return mImpl->timing_cond();
}

// @brief 立ち上がり固有遅延の取得
ClibTime
ClibTiming::intrinsic_rise() const
{
  _check_valid();
  return mImpl->intrinsic_rise();
}

// @brief 立ち下がり固有遅延の取得
ClibTime
ClibTiming::intrinsic_fall() const
{
  _check_valid();
  return mImpl->intrinsic_fall();
}

// @brief 立ち上がりスロープ遅延の取得
ClibTime
ClibTiming::slope_rise() const
{
  _check_valid();
  return mImpl->slope_rise();
}

// @brief 立ち下がりスロープ遅延の取得
ClibTime
ClibTiming::slope_fall() const
{
  _check_valid();
  return mImpl->slope_fall();
}

// @brief 立ち上がり遷移遅延の取得
ClibResistance
ClibTiming::rise_resistance() const
{
  _check_valid();
  return mImpl->rise_resistance();
}

// @brief 立ち下がり遷移遅延の取得
ClibResistance
ClibTiming::fall_resistance() const
{
  _check_valid();
  return mImpl->fall_resistance();
}

// @brief 立ち上がり遷移遅延の取得
ClibResistance
ClibTiming::rise_pin_resistance() const
{
  _check_valid();
  return mImpl->rise_pin_resistance();
}

// @brief 立ち下がり遷移遅延の取得
ClibResistance
ClibTiming::fall_pin_resistance() const
{
  _check_valid();
  return mImpl->fall_pin_resistance();
}

// @brief 立ち上がり？？？
ClibTime
ClibTiming::rise_delay_intercept() const
{
  _check_valid();
  return mImpl->rise_delay_intercept();
}

// @brief 立ち下がり？？？
ClibTime
ClibTiming::fall_delay_intercept() const
{
  _check_valid();
  return mImpl->fall_delay_intercept();
}

// @brief 立ち上がり遷移遅延テーブルの取得
ClibLut
ClibTiming::rise_transition() const
{
  _check_valid();
  auto lut = mImpl->rise_transition();
  return ClibLut{lut};
}

// @brief 立ち下がり遷移遅延テーブルの取得
ClibLut
ClibTiming::fall_transition() const
{
  _check_valid();
  auto lut = mImpl->fall_transition();
  return ClibLut{lut};
}

// @brief 立ち上がり伝搬遅延テーブルの取得
ClibLut
ClibTiming::rise_propagation() const
{
  _check_valid();
  auto lut = mImpl->rise_propagation();
  return ClibLut{lut};
}

// @brief 立ち下がり伝搬遅延テーブルの取得
ClibLut
ClibTiming::fall_propagation() const
{
  _check_valid();
  auto lut = mImpl->fall_propagation();
  return ClibLut{lut};
}

// @brief 立ち上がりセル遅延テーブルの取得
ClibLut
ClibTiming::cell_rise() const
{
  _check_valid();
  auto lut = mImpl->cell_rise();
  return ClibLut{lut};
}

// @brief 立ち下がりセル遅延テーブルの取得
ClibLut
ClibTiming::cell_fall() const
{
  _check_valid();
  auto lut = mImpl->cell_fall();
  return ClibLut{lut};
}

END_NAMESPACE_YM_CLIB
