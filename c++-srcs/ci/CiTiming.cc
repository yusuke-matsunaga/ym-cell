
/// @file CiTiming.cc
/// @brief CiTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiTiming.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiLut.h"
#include "CiTiming_sub.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiTiming
//////////////////////////////////////////////////////////////////////

// @brief CMOSジェネリックタイプのインスタンスを生成する．
unique_ptr<CiTiming>
CiTiming::new_Generic(
  ClibTimingType timing_type,
  const Expr& cond,
  ClibTime intrinsic_rise,
  ClibTime intrinsic_fall,
  ClibTime slope_rise,
  ClibTime slope_fall,
  ClibResistance rise_resistance,
  ClibResistance fall_resistance
)
{
  auto ptr = new CiTimingGeneric{
    timing_type, cond,
    intrinsic_rise, intrinsic_fall,
    slope_rise, slope_fall,
    rise_resistance, fall_resistance
  };
  return unique_ptr<CiTiming>{ptr};
}

// @brief CMOS折れ線近似タイプのインスタンスを生成する．
unique_ptr<CiTiming>
CiTiming::new_Piecewise(
  ClibTimingType timing_type,
  const Expr& cond,
  ClibTime intrinsic_rise,
  ClibTime intrinsic_fall,
  ClibTime slope_rise,
  ClibTime slope_fall,
  ClibResistance rise_pin_resistance,
  ClibResistance fall_pin_resistance
)
{
  auto ptr = new CiTimingPiecewise{
    timing_type, cond,
    intrinsic_rise, intrinsic_fall,
    slope_rise, slope_fall,
    rise_pin_resistance, fall_pin_resistance
  };
  return unique_ptr<CiTiming>{ptr};
}

// @brief CMOS非線形タイプ1のインスタンスを生成する．
unique_ptr<CiTiming>
CiTiming::new_Lut1(
  ClibTimingType timing_type,
  const Expr& cond,
  unique_ptr<CiLut>&& cell_rise,
  unique_ptr<CiLut>&& cell_fall,
  unique_ptr<CiLut>&& rise_transition,
  unique_ptr<CiLut>&& fall_transition
)
{
  auto ptr = new CiTimingLut1{
    timing_type, cond,
    std::move(cell_rise),
    std::move(cell_fall),
    std::move(rise_transition),
    std::move(fall_transition)
  };
  return unique_ptr<CiTiming>{ptr};
}

// @brief CMOS非線形タイプ2のインスタンスを生成する．
unique_ptr<CiTiming>
CiTiming::new_Lut2(
  ClibTimingType timing_type,
  const Expr& cond,
  unique_ptr<CiLut>&& rise_transition,
  unique_ptr<CiLut>&& fall_transition,
  unique_ptr<CiLut>&& rise_propagation,
  unique_ptr<CiLut>&& fall_propagation
)
{
  auto ptr = new CiTimingLut2{
    timing_type, cond,
    std::move(rise_transition),
    std::move(fall_transition),
    std::move(rise_propagation),
    std::move(fall_propagation)
  };
  return unique_ptr<CiTiming>{ptr};
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

// @brief 内容をシリアライズする．
void
CiTiming::serialize(
  Serializer& s ///< [in] シリアライザ
) const
{
  s.reg_obj(this);
  rise_transition()->serialize(s);
  fall_transition()->serialize(s);
  rise_propagation()->serialize(s);
  fall_propagation()->serialize(s);
  cell_rise()->serialize(s);
  cell_fall()->serialize(s);
}

// @brief 共通な情報をダンプする．
void
CiTiming::dump_common(
  Serializer& s,
  int type_id
) const
{
  s.out().write_8(type_id);
  s.dump(mType);
  mCond.dump(s.out());
}

// @brief 内容を読み込む．
unique_ptr<CiTiming>
CiTiming::restore(
  Deserializer& s
)
{
  auto ttype = s.in().read_8();
  unique_ptr<CiTiming> timing;
  switch ( ttype ) {
  case 0: timing = unique_ptr<CiTiming>{new CiTimingGeneric{}}; break;
  case 1: timing = unique_ptr<CiTiming>{new CiTimingPiecewise{}}; break;
  case 2: timing = unique_ptr<CiTiming>{new CiTimingLut1{}}; break;
  case 3: timing = unique_ptr<CiTiming>{new CiTimingLut2{}}; break;
  default: ASSERT_NOT_REACHED; break;
  }
  timing->_restore(s);
  return timing;
}

void
CiTiming::_restore(
  Deserializer& s
)
{
  s.restore(mType);
  mCond.restore(s.in());
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

// @brief 内容をバイナリダンプする．
void
CiTimingGP::dump_GP(
  Serializer& s
) const
{
  s.out() << intrinsic_rise()
	  << intrinsic_fall()
	  << slope_rise()
	  << slope_fall();
}

// @brief 内容を読み込む．
void
CiTimingGP::restore_GP(
  Deserializer& s
)
{
  CiTiming::_restore(s);
  s.in() >> mIntrinsicRise
	 >> mIntrinsicFall
	 >> mSlopeRise
	 >> mSlopeFall;
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

// @brief 内容をバイナリダンプする．
void
CiTimingGeneric::dump(
  Serializer& s
) const
{
  dump_common(s, 0);
  dump_GP(s);
  s.out() << rise_resistance()
	  << fall_resistance();
}

// @brief 内容を読み込む．
void
CiTimingGeneric::_restore(
  Deserializer& s
)
{
  restore_GP(s);
  s.in() >> mRiseResistance
	 >> mFallResistance;
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

// @brief 内容をバイナリダンプする．
void
CiTimingPiecewise::dump(
  Serializer& s
) const
{
  dump_common(s, 1);
  dump_GP(s);
  s.out() << rise_pin_resistance()
	  << fall_pin_resistance();
}

// @brief 内容を読み込む．
void
CiTimingPiecewise::_restore(
  Deserializer& s
)
{
  restore_GP(s);
  s.in() >> mRisePinResistance
	 >> mFallPinResistance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がり遷移遅延テーブルの取得
const CiLut*
CiTimingLut::rise_transition() const
{
  return mRiseTransition.get();
}

// @brief 立ち下がり遷移遅延テーブルの取得
const CiLut*
CiTimingLut::fall_transition() const
{
  return mFallTransition.get();
}

// @brief 内容をバイナリダンプする．
void
CiTimingLut::dump_LUT(
  Serializer& s
) const
{
  s.dump(rise_transition());
  s.dump(fall_transition());
}

// @brief 内容を読み込む．
void
CiTimingLut::restore_LUT(
  Deserializer& s
)
{
  CiTiming::_restore(s);
  s.restore(mRiseTransition);
  s.restore(mFallTransition);
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut1
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がりセル遅延テーブルの取得
const CiLut*
CiTimingLut1::cell_rise() const
{
  return mCellRise.get();
}

// @brief 立ち下がりセル遅延テーブルの取得
const CiLut*
CiTimingLut1::cell_fall() const
{
  return mCellFall.get();
}

// @brief 内容をバイナリダンプする．
void
CiTimingLut1::dump(
  Serializer& s
) const
{
  dump_common(s, 2);
  dump_LUT(s);
  s.dump(cell_rise());
  s.dump(cell_fall());
}

// @brief 内容を読み込む．
void
CiTimingLut1::_restore(
  Deserializer& s
)
{
  restore_LUT(s);
  s.restore(mCellRise);
  s.restore(mCellFall);
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut2
//////////////////////////////////////////////////////////////////////

// @brief 立ち上がり伝搬遅延テーブルの取得
const CiLut*
CiTimingLut2::rise_propagation() const
{
  return mRisePropagation.get();
}

// @brief 立ち下がり伝搬遅延テーブルの取得
const CiLut*
CiTimingLut2::fall_propagation() const
{
  return mFallPropagation.get();
}

// @brief 内容をバイナリダンプする．
void
CiTimingLut2::dump(
  Serializer& s
) const
{
  dump_common(s, 3);
  dump_LUT(s);
  s.dump(rise_propagation());
  s.dump(fall_propagation());
}

// @brief 内容を読み込む．
void
CiTimingLut2::_restore(
  Deserializer& s
)
{
  restore_LUT(s);
  s.restore(mRisePropagation);
  s.restore(mFallPropagation);
}

END_NAMESPACE_YM_CLIB
