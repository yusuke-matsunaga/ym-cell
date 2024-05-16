
/// @file CiTiming.cc
/// @brief CiTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiTiming.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiLut.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiTiming
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がり固有遅延の取得
ClibTime
CiTiming::intrinsic_rise() const
{
  return ClibTime(0.0);
}

// @brief 立ち下がり固有遅延の取得
ClibTime
CiTiming::intrinsic_fall() const
{
  return ClibTime(0.0);
}

// @brief 立ち上がりスロープ遅延の取得
ClibTime
CiTiming::slope_rise() const
{
  return ClibTime(0.0);
}

// @brief 立ち下がりスロープ遅延の取得
ClibTime
CiTiming::slope_fall() const
{
  return ClibTime(0.0);
}

// @brief 立ち上がり遷遅延の取得
ClibResistance
CiTiming::rise_resistance() const
{
  return ClibResistance(0.0);
}

// @brief 立ち下がり遷移遅延の取得
ClibResistance
CiTiming::fall_resistance() const
{
  return ClibResistance(0.0);
}

// @brief 立ち上がり遷移遅延の取得
ClibResistance
CiTiming::rise_pin_resistance() const
{
  return ClibResistance(0.0);
}

// @brief 立ち下がり遷移遅延の取得
ClibResistance
CiTiming::fall_pin_resistance() const
{
  return ClibResistance(0.0);
}

// @brief 立ち上がり？？？
ClibTime
CiTiming::rise_delay_intercept() const
{
  return ClibTime(0.0);
}

// @brief 立ち下がり？？？
ClibTime
CiTiming::fall_delay_intercept() const
{
  return ClibTime(0.0);
}

// @brief 立ち上がり遷移遅延テーブルの取得
const CiLut*
CiTiming::rise_transition() const
{
  return nullptr;
}

// @brief 立ち下がり遷移遅延テーブルの取得
const CiLut*
CiTiming::fall_transition() const
{
  return nullptr;
}

// @brief 立ち上がり伝搬遅延テーブルの取得
const CiLut*
CiTiming::rise_propagation() const
{
  return nullptr;
}

// @brief 立ち下がり伝搬遅延テーブルの取得
const CiLut*
CiTiming::fall_propagation() const
{
  return nullptr;
}

// @brief 立ち上がりセル遅延テーブルの取得
const CiLut*
CiTiming::cell_rise() const
{
  return nullptr;
}

// @brief 立ち下がりセル遅延テーブルの取得
const CiLut*
CiTiming::cell_fall() const
{
  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingGP
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がり固有遅延の取得
ClibTime
CiTimingGP::intrinsic_rise() const
{
  return mIntrinsicRise;
}

// @brief 立ち下がり固有遅延の取得
ClibTime
CiTimingGP::intrinsic_fall() const
{
  return mIntrinsicFall;
}

// @brief 立ち上がりスロープ遅延の取得
ClibTime
CiTimingGP::slope_rise() const
{
  return mSlopeRise;
}

// @brief 立ち下がりスロープ遅延の取得
ClibTime
CiTimingGP::slope_fall() const
{
  return mSlopeFall;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingGeneric
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がり遷移遅延の取得
ClibResistance
CiTimingGeneric::rise_resistance() const
{
  return mRiseResistance;
}

// @brief 立ち下がり遷移遅延の取得
ClibResistance
CiTimingGeneric::fall_resistance() const
{
  return mFallResistance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingPiecewise
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がり遷移遅延の取得
ClibResistance
CiTimingPiecewise::rise_pin_resistance() const
{
  return mRisePinResistance;
}

// @brief 立ち下がり遷移遅延の取得
ClibResistance
CiTimingPiecewise::fall_pin_resistance() const
{
  return mFallPinResistance;
}

// @brief 立ち上がり？？？
ClibTime
CiTimingPiecewise::rise_delay_intercept() const
{
#warning "TODO: CiTimingPiecewise::rise_delay_intercept"
  return ClibTime(0.0);
}

// @brief 立ち下がり？？？
ClibTime
CiTimingPiecewise::fall_delay_intercept() const
{
#warning "TODO: CiTimingPiecewise::fall_delay_intercept"
  return ClibTime(0.0);
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がり遷移遅延テーブルの取得
const CiLut*
CiTimingLut::rise_transition() const
{
  return mRiseTransition;
}

// @brief 立ち下がり遷移遅延テーブルの取得
const CiLut*
CiTimingLut::fall_transition() const
{
  return mFallTransition;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut1
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がりセル遅延テーブルの取得
const CiLut*
CiTimingLut1::cell_rise() const
{
  return mCellRise;
}

// @brief 立ち下がりセル遅延テーブルの取得
const CiLut*
CiTimingLut1::cell_fall() const
{
  return mCellFall;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut2
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がり伝搬遅延テーブルの取得
const CiLut*
CiTimingLut2::rise_propagation() const
{
  return mRisePropagation;
}

// @brief 立ち下がり伝搬遅延テーブルの取得
const CiLut*
CiTimingLut2::fall_propagation() const
{
  return mFallPropagation;
}

END_NAMESPACE_YM_CLIB
