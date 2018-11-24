
/// @file CiTiming.cc
/// @brief CiTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiTiming.h"
#include "ci/CiCellLibrary.h"
#include "ym/ClibLut.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiTiming
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] type タイミング条件の型
// @param[in] cond タイミング条件を表す式
CiTiming::CiTiming(ClibTimingType type,
		   const Expr& cond) :
  mType(type),
  mCond(cond)
{
}

// @brief デストラクタ
CiTiming::~CiTiming()
{
}

// @brief ID番号の取得
// @note timing = cell->timing(id); の時，timing->id() = id となる．
int
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
// @note ない場合には定数1の式が返される．
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

// @brief コンストラクタ
// @param[in] timing_type タイミングの型
// @param[in] cond タイミング条件を表す式
// @param[in] intrinsic_rise 立ち上がり固有遅延
// @param[in] intrinsic_fall 立ち下がり固有遅延
// @param[in] slope_rise 立ち上がりスロープ遅延
// @param[in] slope_fall 立ち下がりスロープ遅延
CiTimingGP::CiTimingGP(ClibTimingType timing_type,
		       const Expr& cond,
		       ClibTime intrinsic_rise,
		       ClibTime intrinsic_fall,
		       ClibTime slope_rise,
		       ClibTime slope_fall) :
  CiTiming(timing_type, cond),
  mIntrinsicRise(intrinsic_rise),
  mIntrinsicFall(intrinsic_fall),
  mSlopeRise(slope_rise),
  mSlopeFall(slope_fall)
{
}

// @brief デストラクタ
CiTimingGP::~CiTimingGP()
{
}

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

// @brief コンストラクタ
// @param[in] timing_type タイミングの型
// @param[in] cond タイミング条件を表す式
// @param[in] intrinsic_rise 立ち上がり固有遅延
// @param[in] intrinsic_fall 立ち下がり固有遅延
// @param[in] slope_rise 立ち上がりスロープ遅延
// @param[in] slope_fall 立ち下がりスロープ遅延
// @param[in] rise_resistance 立ち上がり遷移遅延パラメータ
// @param[in] fall_resistance 立ち下がり遷移遅延パラメータ
CiTimingGeneric::CiTimingGeneric(ClibTimingType timing_type,
				 const Expr& cond,
				 ClibTime intrinsic_rise,
				 ClibTime intrinsic_fall,
				 ClibTime slope_rise,
				 ClibTime slope_fall,
				 ClibResistance rise_resistance,
				 ClibResistance fall_resistance) :
  CiTimingGP(timing_type, cond,
	     intrinsic_rise, intrinsic_fall,
	     slope_rise, slope_fall),
  mRiseResistance(rise_resistance),
  mFallResistance(fall_resistance)
{
}

// @brief デストラクタ
CiTimingGeneric::~CiTimingGeneric()
{
}


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

// @brief コンストラクタ
// @param[in] timing_type タイミングの型
// @param[in] cond タイミング条件を表す式
// @param[in] intrinsic_rise 立ち上がり固有遅延
// @param[in] intrinsic_fall 立ち下がり固有遅延
// @param[in] slope_rise 立ち上がりスロープ遅延
// @param[in] slope_fall 立ち下がりスロープ遅延
CiTimingPiecewise::CiTimingPiecewise(ClibTimingType timing_type,
				     const Expr& cond,
				     ClibTime intrinsic_rise,
				     ClibTime intrinsic_fall,
				     ClibTime slope_rise,
				     ClibTime slope_fall,
				     ClibResistance rise_pin_resistance,
				     ClibResistance fall_pin_resistance) :
  CiTimingGP(timing_type, cond,
	     intrinsic_rise, intrinsic_fall,
	     slope_rise, slope_fall),
  mRisePinResistance(rise_pin_resistance),
  mFallPinResistance(fall_pin_resistance)
{
}

// @brief デストラクタ
CiTimingPiecewise::~CiTimingPiecewise()
{
}

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
// クラス CiTimingLut1
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] timing_type タイミングの型
// @param[in] cond タイミング条件を表す式
// @param[in] cell_rise 立ち上がりセル遅延テーブル
// @param[in] cell_fall 立ち下がりセル遅延テーブル
// @param[in] rise_transition 立ち上がり遷移遅延テーブル
// @param[in] fall_transition 立ち下がり遷移遅延テーブル
CiTimingLut1::CiTimingLut1(ClibTimingType timing_type,
			   const Expr& cond,
			   ClibLut* cell_rise,
			   ClibLut* cell_fall,
			   ClibLut* rise_transition,
			   ClibLut* fall_transition) :
  CiTiming(timing_type, cond),
  mClibRise(cell_rise),
  mClibFall(cell_fall),
  mRiseTransition(rise_transition),
  mFallTransition(fall_transition)
{
}

// @brief デストラクタ
CiTimingLut1::~CiTimingLut1()
{
}

// @brief 立ち上がりセル遅延テーブルの取得
const ClibLut&
CiTimingLut1::cell_rise() const
{
  return *mClibRise;
}

// @brief 立ち下がりセル遅延テーブルの取得
const ClibLut&
CiTimingLut1::cell_fall() const
{
  return *mClibFall;
}

// @brief 立ち上がり遷移遅延テーブルの取得
const ClibLut&
CiTimingLut1::rise_transition() const
{
  return *mRiseTransition;
}

// @brief 立ち下がり遷移遅延テーブルの取得
const ClibLut&
CiTimingLut1::fall_transition() const
{
  return *mFallTransition;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut2
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] timing_type タイミングの型
// @param[in] cond タイミング条件を表す式
// @param[in] rise_transition 立ち上がり遷移遅延テーブル
// @param[in] fall_transition 立ち下がり遷移遅延テーブル
// @param[in] rise_propagation 立ち上がり伝搬遅延テーブル
// @param[in] fall_propagation 立ち下がり伝搬遅延テーブル
CiTimingLut2::CiTimingLut2(ClibTimingType timing_type,
			   const Expr& cond,
			   ClibLut* rise_transition,
			   ClibLut* fall_transition,
			   ClibLut* rise_propagation,
			   ClibLut* fall_propagation) :
  CiTiming(timing_type, cond),
  mRiseTransition(rise_transition),
  mFallTransition(fall_transition),
  mRisePropagation(rise_propagation),
  mFallPropagation(fall_propagation)
{
}

// @brief デストラクタ
CiTimingLut2::~CiTimingLut2()
{
}

// @brief 立ち上がり遷移遅延テーブルの取得
const ClibLut&
CiTimingLut2::rise_transition() const
{
  return *mRiseTransition;
}

// @brief 立ち下がり遷移遅延テーブルの取得
const ClibLut&
CiTimingLut2::fall_transition() const
{
  return *mFallTransition;
}

// @brief 立ち上がり伝搬遅延テーブルの取得
const ClibLut&
CiTimingLut2::rise_propagation() const
{
  return *mRisePropagation;
}

// @brief 立ち下がり伝搬遅延テーブルの取得
const ClibLut&
CiTimingLut2::fall_propagation() const
{
  return *mFallPropagation;
}

END_NAMESPACE_YM_CLIB
