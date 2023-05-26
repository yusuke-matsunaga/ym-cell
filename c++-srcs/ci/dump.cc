
/// @file CiCellLibrary_dump.cc
/// @brief CiCellLibrary の実装ファイル(dump()関係)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellLibrary.h"
#include "ci/CiCellClass.h"
#include "ci/CiCellGroup.h"
#include "ci/CiCell.h"
#include "ci/CiBusType.h"
#include "ci/CiLutTemplate.h"
#include "ci/CiLut.h"
#include "ci/CiTiming.h"
#include "ym/ClibIOMap.h"
#include "ym/Range.h"

#include "CiFFCell.h"
#include "CiLatchCell.h"
#include "CiFsmCell.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// 番号のベクタをダンプする．
inline
void
dump_vector(
  BinEnc& s,
  const vector<SizeType>& vec
)
{
  s.write_64(vec.size());
  for ( auto v: vec ) {
    s.write_64(v);
  }
}

// 数値のベクタをダンプする．
inline
void
dump_dvector(
  BinEnc& s,
  const vector<double>& vec
)
{
  s.write_64(vec.size());
  for ( auto v: vec ) {
    s << v;
  }
}

END_NONAMESPACE


//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiCellLibrary::dump(
  ostream& os
) const
{
  BinEnc bs{os};

  // 名前
  bs << name();

  // テクノロジ
  bs << technology();

  // 遅延モデル
  bs << delay_model();

  // バス命名規則
  bs << bus_naming_style();

  // 日付情報
  bs << date();

  // リビジョン情報
  bs << revision();

  // コメント
  bs << comment();

  // 時間単位
  bs << time_unit();

  // 電圧単位
  bs << voltage_unit();

  // 電流単位
  bs << current_unit();

  // 抵抗単位
  bs << pulling_resistance_unit();

  // 容量単位
  bs << capacitive_load_unit();

  // 容量単位の文字列
  bs << capacitive_load_unit_str();

  // 電力単位
  bs << leakage_power_unit();

  // バスタイプ
  bs.write_64(mBusTypeList.size());
  for ( auto& bustype: mBusTypeList ) {
    bustype->dump(bs);
  }

  // 遅延テーブルのテンプレート
  bs.write_64(mLutTemplateList.size());
  for ( auto& lut_templ: mLutTemplateList ) {
    lut_templ->dump(bs);
  }

  // セルの内容をダンプ
  bs.write_64(mCellList.size());
  for ( auto& cell: mCellList ) {
    cell->dump(bs);
  }

  // ピンの内容をダンプ
  bs.write_64(mPinList.size());
  for ( auto& pin: mPinList ) {
    pin->dump(bs);
  }

  // バスの内容をダンプ
  bs.write_64(mBusList.size());
  for ( auto& bus: mBusList ) {
    bus->dump(bs);
  }

  // バンドルの内容をダンプ
  bs.write_64(mBundleList.size());
  for ( auto& bundle: mBundleList ) {
    bundle->dump(bs);
  }

  // タイミング情報の内容をダンプ
  bs.write_64(mTimingList.size());
  for ( auto& timing: mTimingList ) {
    timing->dump(bs);
  }

  // LUTの内容をダンプ
  bs.write_64(mLutList.size());
  for ( auto& lut: mLutList ) {
    lut->dump(bs);
  }

  // セルグループ情報のダンプ
  bs.write_64(mGroupList.size());
  for ( auto& group: mGroupList ) {
    group->dump(bs);
  }

  // セルクラス情報のダンプ
  bs.write_64(mClassList.size());
  for ( auto& cell_class: mClassList ) {
    cell_class->dump(bs);
  }

  // 組み込み型の情報のダンプ
  for ( auto g: mLogicGroup ) {
    bs.write_64(g);
  }
  dump_vector(bs, mSimpleFFClass);
  dump_vector(bs, mSimpleLatchClass);

  // パタングラフの情報のダンプ
  mPatMgr.dump(bs);
}


//////////////////////////////////////////////////////////////////////
// クラス CiBusType
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiBusType::dump(
  BinEnc& s
) const
{
  s << mName;
  s.write_64(mBitFrom);
  s.write_64(mBitTo);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate
//////////////////////////////////////////////////////////////////////

// @brief 共通部分をバイナリダンプする．
void
CiLutTemplate::dump(
  BinEnc& s
) const
{
  s.write_8(dimension());
}

// @brief 1つの変数の情報をバイナリダンプする．
void
CiLutTemplate::dump_var(
  BinEnc& s,
  ClibVarType var_type,
  const vector<double>& index_array
)
{
  s << var_type;
  dump_dvector(s, index_array);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate1D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLutTemplate1D::dump(
  BinEnc& s
) const
{
  CiLutTemplate::dump(s);
  dump_var(s, mVarType, mIndexArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate2D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLutTemplate2D::dump(
  BinEnc& s
) const
{
  CiLutTemplate::dump(s);
  for ( SizeType i: Range(2) ) {
    dump_var(s, mVarType[i], mIndexArray[i]);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate3D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLutTemplate3D::dump(
  BinEnc& s
) const
{
  CiLutTemplate::dump(s);
  for ( SizeType i: Range(2) ) {
    dump_var(s, mVarType[i], mIndexArray[i]);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief 共通部分のダンプ
void
CiCell::dump_common(
  BinEnc& s
) const
{
  s << mName
    << mArea;
  s.write_64(mInputNum);
  s.write_64(mOutputNum);
  s.write_64(mInoutNum);
  dump_vector(s, mPinList);
  dump_vector(s, mInputList);
  dump_vector(s, mOutputList);
  dump_vector(s, mInternalList);
  dump_vector(s, mBusList);
  dump_vector(s, mBundleList);
  dump_vector(s, mTimingList);
  s.write_64(mTimingMap.size());
  for ( auto& timing_list: mTimingMap ) {
    dump_vector(s, timing_list);
  }
}

// @brief 内容をバイナリダンプする．
void
CiCell::dump(
  BinEnc& s
) const
{
  // シグネチャ
  s.write_8(0);
  dump_common(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiFLCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiFLCell::dump_FL(
  BinEnc& s
) const
{
  dump_common(s);
  s << mVar1
    << mVar2;
  mClear.dump(s);
  mPreset.dump(s);
  s << mCpv1
    << mCpv2;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiFFCell::dump(
  BinEnc& s
) const
{
  s.write_8(1);
  dump_FF(s);
}

// @brief 内容をバイナリダンプする．
void
CiFFCell::dump_FF(
  BinEnc& s
) const
{
  dump_FL(s);
  mClock.dump(s);
  mNextState.dump(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiFF2Cell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiFF2Cell::dump(
  BinEnc& s
) const
{
  s.write_8(2);
  dump_FF(s);
  mClock2.dump(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLatchCell::dump(
  BinEnc& s
) const
{
  s.write_8(3);
  dump_Latch(s);
}

// @brief 内容をバイナリダンプする．
void
CiLatchCell::dump_Latch(
  BinEnc& s
) const
{
  dump_FL(s);
  mEnable.dump(s);
  mDataIn.dump(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatch2Cell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLatch2Cell::dump(
  BinEnc& s
) const
{
  s.write_8(4);
  dump_Latch(s);
  mEnable2.dump(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiFsmCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiFsmCell::dump(
  BinEnc& s
) const
{
  s.write_8(5);
  dump_common(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiPin
//////////////////////////////////////////////////////////////////////

// @brief dump 用の共通情報を出力する．
void
CiPin::dump_common(
  BinEnc& s,
  int sig
) const
{
  s.write_8(sig);
  s << mName;
  s.write_64(mPinId);
}


//////////////////////////////////////////////////////////////////////
// クラス CiInputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiInputPin::dump(
  BinEnc& s
) const
{
  dump_common(s, 0);
  s.write_64(mInputId);
  s << mCapacitance
    << mRiseCapacitance
    << mFallCapacitance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPinBase
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiOutputPinBase::dump_base(
  BinEnc& s,
  int sig
) const
{
  dump_common(s, sig);
  s.write_64(mOutputId);
  s<< mFanoutLoad
    << mMaxFanout
    << mMinFanout
    << mMaxCapacitance
    << mMinCapacitance
    << mMaxTransition
    << mMinTransition;
  mFunction.dump(s);
  mTristate.dump(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiOutputPin::dump(
  BinEnc& s
) const
{
  dump_base(s, 1);
}


//////////////////////////////////////////////////////////////////////
// クラス CiInoutPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiInoutPin::dump(
  BinEnc& s
) const
{
  dump_base(s, 2);
  s.write_64(mInputId);
  s << mCapacitance
    << mRiseCapacitance
    << mFallCapacitance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiInternalPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiInternalPin::dump(
  BinEnc& s
) const
{
  dump_common(s, 3);
  s.write_64(internal_id());
}


//////////////////////////////////////////////////////////////////////
// クラス CiBus
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiBus::dump(
  BinEnc& s
) const
{
  s << mName;
  s.write_64(mBusType);
  dump_vector(s, mPinList);
}


//////////////////////////////////////////////////////////////////////
// クラス CiBundle
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiBundle::dump(
  BinEnc& s
) const
{
  s << mName;
  dump_vector(s, mPinList);
}


//////////////////////////////////////////////////////////////////////
// クラス CiTiming
//////////////////////////////////////////////////////////////////////

// @brief 共通な情報をダンプする．
void
CiTiming::dump_common(
  BinEnc& s,
  int type_id
) const
{
  s.write_8(type_id);
  s << mType;
  mCond.dump(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingGeneric
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiTimingGeneric::dump(
  BinEnc& s
) const
{
  dump_common(s, 0);
  s << intrinsic_rise()
    << intrinsic_fall()
    << slope_rise()
    << slope_fall()
    << rise_resistance()
    << fall_resistance();
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingPiecewise
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiTimingPiecewise::dump(
  BinEnc& s
) const
{
  dump_common(s, 1);
  s << intrinsic_rise()
    << intrinsic_fall()
    << slope_rise()
    << slope_fall();
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut1
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiTimingLut1::dump(
  BinEnc& s
) const
{
  dump_common(s, 2);

  s.write_64(cell_rise());
  s.write_64(cell_fall());
  s.write_64(rise_transition());
  s.write_64(fall_transition());
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut2
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiTimingLut2::dump(
  BinEnc& s
) const
{
  dump_common(s, 3);
  s.write_64(rise_transition());
  s.write_64(fall_transition());
  s.write_64(rise_propagation());
  s.write_64(fall_propagation());
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut
//////////////////////////////////////////////////////////////////////

// @brief 実際のダンプを行う関数
void
CiLut::dump_common(
  BinEnc& s,
  int d
) const
{
  s.write_8(d);
  s.write_64(mTemplate);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut1D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut1D::dump(
  BinEnc& s
) const
{
  dump_common(s, 1);
  dump_dvector(s, mIndexArray);
  dump_dvector(s, mValueArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut2D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut2D::dump(
  BinEnc& s
) const
{
  dump_common(s, 2);
  dump_dvector(s, mIndexArray[0]);
  dump_dvector(s, mIndexArray[1]);
  dump_dvector(s, mValueArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut3D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut3D::dump(
  BinEnc& s
) const
{
  dump_common(s, 3);
  dump_dvector(s, mIndexArray[0]);
  dump_dvector(s, mIndexArray[1]);
  dump_dvector(s, mIndexArray[2]);
  dump_dvector(s, mValueArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiCellGroup::dump(
  BinEnc& s
) const
{
  s.write_64(mRepClass);
  mIoMap.dump(s);
  dump_vector(s, mCellList);
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiCellClass::dump(
  BinEnc& s
) const
{
  // 同位体変換情報のダンプ
  s.write_64(idmap_num());
  for ( auto& map: idmap_list() ) {
    map.dump(s);
  }
  // グループ情報のダンプ
  dump_vector(s, mGroupList);
}

END_NAMESPACE_YM_CLIB
