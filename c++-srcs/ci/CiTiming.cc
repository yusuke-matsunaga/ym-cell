﻿
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

// @brief ID番号の取得
SizeType
CiTiming::id() const
{
  return mId;
}

// @brief 型の取得
ClibTimingType
CiTiming::type() const
{
  return mType;
}

// @brief タイミング条件式の取得
Expr
CiTiming::timing_cond() const
{
  return mCond;
}

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
const ClibLut&
CiTiming::rise_transition() const
{
  return CiCellLibrary::error_lut();
}

// @brief 立ち下がり遷移遅延テーブルの取得
const ClibLut&
CiTiming::fall_transition() const
{
  return CiCellLibrary::error_lut();
}

// @brief 立ち上がり伝搬遅延テーブルの取得
const ClibLut&
CiTiming::rise_propagation() const
{
  return CiCellLibrary::error_lut();
}

// @brief 立ち下がり伝搬遅延テーブルの取得
const ClibLut&
CiTiming::fall_propagation() const
{
  return CiCellLibrary::error_lut();
}

// @brief 立ち上がりセル遅延テーブルの取得
const ClibLut&
CiTiming::cell_rise() const
{
  return CiCellLibrary::error_lut();
}

// @brief 立ち下がりセル遅延テーブルの取得
const ClibLut&
CiTiming::cell_fall() const
{
  return CiCellLibrary::error_lut();
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

// @brief コンストラクタ
CiTimingLut::CiTimingLut(
  SizeType tid,               ///< [in] タイミング番号
  ClibTimingType timing_type, ///< [in] タイミングの型
  const Expr& cond,           ///< [in] タイミング条件を表す式
  CiLut* rise_transition,     ///< [in] 立ち上がり遷移遅延テーブル
  CiLut* fall_transition      ///< [in] 立ち下がり遷移遅延テーブル
) : CiTiming{tid, timing_type, cond},
    mRiseTransition{unique_ptr<CiLut>{rise_transition}},
    mFallTransition{unique_ptr<CiLut>{fall_transition}}
{
}

// @brief 立ち上がり遷移遅延テーブルの取得
const ClibLut&
CiTimingLut::rise_transition() const
{
  if ( mRiseTransition == nullptr ) {
    return CiCellLibrary::error_lut();
  }
  else {
    return *mRiseTransition;
  }
}

// @brief 立ち下がり遷移遅延テーブルの取得
const ClibLut&
CiTimingLut::fall_transition() const
{
  if ( mFallTransition == nullptr ) {
    return CiCellLibrary::error_lut();
  }
  else {
    return *mFallTransition;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut1
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiTimingLut1::CiTimingLut1(
  SizeType tid,               ///< [in] タイミング番号
  ClibTimingType timing_type, ///< [in] タイミングの型
  const Expr& cond,           ///< [in] タイミング条件を表す式
  CiLut* cell_rise,           ///< [in] 立ち上がりセル遅延テーブル
  CiLut* cell_fall,           ///< [in] 立ち下がりセル遅延テーブル
  CiLut* rise_transition,     ///< [in] 立ち上がり遷移遅延テーブル
  CiLut* fall_transition      ///< [in] 立ち下がり遷移遅延テーブル
) : CiTimingLut{tid, timing_type, cond, rise_transition, fall_transition},
    mCellRise{unique_ptr<CiLut>{cell_rise}},
    mCellFall{unique_ptr<CiLut>{cell_fall}}
{
}

// @brief 立ち上がりセル遅延テーブルの取得
const ClibLut&
CiTimingLut1::cell_rise() const
{
  if ( mCellRise == nullptr ) {
    return CiCellLibrary::error_lut();
  }
  else {
    return *mCellRise;
  }
}

// @brief 立ち下がりセル遅延テーブルの取得
const ClibLut&
CiTimingLut1::cell_fall() const
{
  if ( mCellFall == nullptr ) {
    return CiCellLibrary::error_lut();
  }
  else {
    return *mCellFall;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut2
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiTimingLut2::CiTimingLut2(
  SizeType tid,               ///< [in] タイミング番号
  ClibTimingType timing_type, ///< [in] タイミングの型
  const Expr& cond,           ///< [in] タイミング条件を表す式
  CiLut* rise_transition,     ///< [in] 立ち上がり遷移遅延テーブル
  CiLut* fall_transition,     ///< [in] 立ち下がり遷移遅延テーブル
  CiLut* rise_propagation,    ///< [in] 立ち上がり伝搬遅延テーブル
  CiLut* fall_propagation     ///< [in] 立ち下がり伝搬遅延テーブル
) : CiTimingLut{tid, timing_type, cond, rise_transition, fall_transition},
    mRisePropagation{unique_ptr<CiLut>{rise_propagation}},
    mFallPropagation{unique_ptr<CiLut>{fall_propagation}}
{
}

// @brief 立ち上がり伝搬遅延テーブルの取得
const ClibLut&
CiTimingLut2::rise_propagation() const
{
  if ( mRisePropagation == nullptr ) {
    return CiCellLibrary::error_lut();
  }
  else {
    return *mRisePropagation;
  }
}

// @brief 立ち下がり伝搬遅延テーブルの取得
const ClibLut&
CiTimingLut2::fall_propagation() const
{
  if ( mFallPropagation == nullptr ) {
    return CiCellLibrary::error_lut();
  }
  else {
    return *mFallPropagation;
  }
}

END_NAMESPACE_YM_CLIB