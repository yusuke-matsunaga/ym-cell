
/// @file CiCellLibrary_dump.cc
/// @brief CiCellLibrary の実装ファイル(dump()関係)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellLibrary.h"
#include "ci/CiCellClass.h"
#include "ci/CiCellGroup.h"
#include "ci/CiCell.h"
#include "ci/CiBusType.h"
#include "ci/CiLutTemplate.h"
#include "ci/CiLut.h"
#include "ci/CiTiming.h"
#include "ci/CiPatGraph.h"
#include "ci/Serializer.h"
#include "ym/ClibIOMap.h"
#include "ym/Range.h"

#include "CiFFCell.h"
#include "CiLatchCell.h"
#include "CiFsmCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiCellLibrary::dump(
  ostream& os
) const
{
  Serializer s{os};

  // 要素のシリアライズを行う．
  serialize(s);

  // シリアライズで登録された要素の内容をダンプする．
  s.dump_obj();

  // 名前
  s.dump(name());

  // テクノロジ
  s.out() << technology();

  // 遅延モデル
  s.out() << delay_model();

  // バス命名規則
  s.out() << bus_naming_style();

  // 日付情報
  s.out() << date();

  // リビジョン情報
  s.out() << revision();

  // コメント
  s.out() << comment();

  // 時間単位
  s.out() << time_unit();

  // 電圧単位
  s.out() << voltage_unit();

  // 電流単位
  s.out() << current_unit();

  // 抵抗単位
  s.out() << pulling_resistance_unit();

  // 容量単位
  s.out() << capacitive_load_unit();

  // 容量単位の文字列
  s.out() << capacitive_load_unit_str();

  // 電力単位
  s.out() << leakage_power_unit();

  // バスタイプのリスト
  s.dump(mBusTypeList.size());
  for ( auto& bustype: mBusTypeList ) {
    s.dump(bustype.get());
  }

  // 遅延テーブルのテンプレートのリスト
  s.dump(mLutTemplateList.size());
  for ( auto& lut_templ: mLutTemplateList ) {
    s.dump(lut_templ.get());
  }

  // セルのリスト
  s.dump(mCellList.size());
  for ( auto& cell: mCellList ) {
    s.dump(cell.get());
  }

  // セルグループ情報のリスト
  s.dump(mGroupList.size());
  for ( auto& group: mGroupList ) {
    s.dump(group.get());
  }

  // セルクラス情報のリスト
  s.dump(mClassList.size());
  for ( auto& cell_class: mClassList ) {
    s.dump(cell_class.get());
  }

  // 組み込み型の情報のダンプ
  for ( auto g: mLogicGroup ) {
    s.dump(g);
  }
  s.dump(mSimpleFFClass);
  s.dump(mSimpleLatchClass);

  // パタングラフの情報のダンプ
  mPatMgr.dump(s);
}

// @brief 要素をシリアライズする．
void
CiCellLibrary::serialize(
  Serializer& s
) const
{
  for ( auto& bustype: mBusTypeList ) {
    bustype->serialize(s);
  }
  for ( auto& templ: mLutTemplateList ) {
    templ->serialize(s);
  }
  for ( auto& cell: mCellList ) {
    cell->serialize(s);
  }
  for ( auto& cgroup: mGroupList ) {
    cgroup->serialize(s);
  }
  for ( auto& cclass: mClassList ) {
    cclass->serialize(s);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiBusType
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiBusType::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiBusType::dump(
  Serializer& s
) const
{
  s.dump(name());
  s.dump(bit_from());
  s.dump(bit_to());
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiLutTemplate::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 1つの変数の情報をバイナリダンプする．
void
CiLutTemplate::dump_var(
  Serializer& s,
  ClibVarType var_type,
  const vector<double>& index_array
)
{
  s.out() << var_type;
  s.dump(index_array);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate1D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLutTemplate1D::dump(
  Serializer& s
) const
{
  s.out().write_8(1);
  dump_var(s, mVarType, mIndexArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate2D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLutTemplate2D::dump(
  Serializer& s
) const
{
  s.out().write_8(2);
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
  Serializer& s
) const
{
  s.out().write_8(3);
  for ( SizeType i: Range(2) ) {
    dump_var(s, mVarType[i], mIndexArray[i]);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiLut::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 実際のダンプを行う関数
void
CiLut::dump_common(
  Serializer& s,
  int d
) const
{
  s.out().write_8(d);
  s.dump(mTemplate);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut1D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut1D::dump(
  Serializer& s
) const
{
  dump_common(s, 1);
  s.dump(mIndexArray);
  s.dump(mValueArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut2D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut2D::dump(
  Serializer& s
) const
{
  dump_common(s, 2);
  s.dump(mIndexArray[0]);
  s.dump(mIndexArray[1]);
  s.dump(mValueArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut3D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut3D::dump(
  Serializer& s
) const
{
  dump_common(s, 3);
  s.dump(mIndexArray[0]);
  s.dump(mIndexArray[1]);
  s.dump(mIndexArray[2]);
  s.dump(mValueArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiTiming
//////////////////////////////////////////////////////////////////////

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
  s.out() << mType;
  mCond.dump(s.out());
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingGeneric
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiTimingGeneric::dump(
  Serializer& s
) const
{
  dump_common(s, 0);
  s.out() << intrinsic_rise()
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
  Serializer& s
) const
{
  dump_common(s, 1);
  s.out() << intrinsic_rise()
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
  Serializer& s
) const
{
  dump_common(s, 2);

  s.dump(cell_rise());
  s.dump(cell_fall());
  s.dump(rise_transition());
  s.dump(fall_transition());
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut2
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiTimingLut2::dump(
  Serializer& s
) const
{
  dump_common(s, 3);
  s.dump(rise_transition());
  s.dump(fall_transition());
  s.dump(rise_propagation());
  s.dump(fall_propagation());
}


//////////////////////////////////////////////////////////////////////
// クラス CiPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiPin::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief dump 用の共通情報を出力する．
void
CiPin::dump_common(
  Serializer& s,
  int sig
) const
{
  s.out().write_8(sig);
  s.out() << mName;
  s.out().write_64(mPinId);
}


//////////////////////////////////////////////////////////////////////
// クラス CiInputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiInputPin::dump(
  Serializer& s
) const
{
  dump_common(s, 0);
  s.out().write_64(mInputId);
  s.out() << mCapacitance
	  << mRiseCapacitance
	  << mFallCapacitance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPinBase
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiOutputPinBase::dump_base(
  Serializer& s,
  int sig
) const
{
  dump_common(s, sig);
  s.out().write_64(mOutputId);
  s.out() << mFanoutLoad
	  << mMaxFanout
	  << mMinFanout
	  << mMaxCapacitance
	  << mMinCapacitance
	  << mMaxTransition
	  << mMinTransition;
  mFunction.dump(s.out());
  mTristate.dump(s.out());
}


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiOutputPin::dump(
  Serializer& s
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
  Serializer& s
) const
{
  dump_base(s, 2);
  s.out().write_64(mInputId);
  s.out() << mCapacitance
	  << mRiseCapacitance
	  << mFallCapacitance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiInternalPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiInternalPin::dump(
  Serializer& s
) const
{
  dump_common(s, 3);
  s.out().write_64(internal_id());
}


//////////////////////////////////////////////////////////////////////
// クラス CiBus
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiBus::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiBus::dump(
  Serializer& s
) const
{
  s.out() << name();
  s.dump(bus_type());
  s.dump(pin_list());
}


//////////////////////////////////////////////////////////////////////
// クラス CiBundle
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiBundle::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiBundle::dump(
  Serializer& s
) const
{
  s.out() << _name();
  s.dump(pin_list());
}


//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiCell::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
  for ( auto pin: mPinList ) {
    pin->serialize(s);
  }
  for ( auto bus: mBusList ) {
    bus->serialize(s);
  }
  for ( auto bundle: mBundleList ) {
    bundle->serialize(s);
  }
  for ( auto timing: mTimingList ) {
    timing->serialize(s);
  }
  for ( auto& timing_list: mTimingMap ) {
    for ( auto timing: timing_list ) {
      timing->serialize(s);
    }
  }
}

// @brief 共通部分のダンプ
void
CiCell::dump_common(
  Serializer& s
) const
{
  s.dump(mName);
  s.out() << mArea;
  s.dump(mInputNum);
  s.dump(mOutputNum);
  s.dump(mInoutNum);
  s.dump(mPinList);
  s.dump(mInputList);
  s.dump(mOutputList);
  s.dump(mInternalList);
  s.dump(mBusList);
  s.dump(mBundleList);
  s.dump(mTimingList);
  s.dump(mTimingMap.size());
  for ( auto& timing_list: mTimingMap ) {
    s.dump(timing_list);
  }
}

// @brief 内容をバイナリダンプする．
void
CiCell::dump(
  Serializer& s
) const
{
  // シグネチャ
  s.out().write_8(0);
  dump_common(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiFLCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiFLCell::dump_FL(
  Serializer& s
) const
{
  dump_common(s);
  s.out() << mVar1
	  << mVar2;
  mClear.dump(s.out());
  mPreset.dump(s.out());
  s.out() << mCpv1
	  << mCpv2;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiFFCell::dump(
  Serializer& s
) const
{
  s.out().write_8(1);
  dump_FF(s);
}

// @brief 内容をバイナリダンプする．
void
CiFFCell::dump_FF(
  Serializer& s
) const
{
  dump_FL(s);
  mClock.dump(s.out());
  mNextState.dump(s.out());
}


//////////////////////////////////////////////////////////////////////
// クラス CiFF2Cell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiFF2Cell::dump(
  Serializer& s
) const
{
  s.out().write_8(2);
  dump_FF(s);
  mClock2.dump(s.out());
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLatchCell::dump(
  Serializer& s
) const
{
  s.out().write_8(3);
  dump_Latch(s);
}

// @brief 内容をバイナリダンプする．
void
CiLatchCell::dump_Latch(
  Serializer& s
) const
{
  dump_FL(s);
  mEnable.dump(s.out());
  mDataIn.dump(s.out());
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatch2Cell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLatch2Cell::dump(
  Serializer& s
) const
{
  s.out().write_8(4);
  dump_Latch(s);
  mEnable2.dump(s.out());
}


//////////////////////////////////////////////////////////////////////
// クラス CiFsmCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiFsmCell::dump(
  Serializer& s
) const
{
  s.out().write_8(5);
  dump_common(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiCellClass::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiCellClass::dump(
  Serializer& s
) const
{
  // 同位体変換情報のダンプ
  s.dump(idmap_num());
  for ( auto& map: idmap_list() ) {
    map.dump(s.out());
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiCellGroup::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiCellGroup::dump(
  Serializer& s
) const
{
  mIoMap.dump(s.out());
  s.dump(mCellList);
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatMgr
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
CiPatMgr::dump(
  Serializer& s
) const
{
  // パタングラフのノード情報のダンプ
  s.dump(node_num());
  for ( auto i: Range(node_num()) ) {
    s.dump(mNodeTypeArray[i]);
    s.dump(mEdgeArray[i * 2 + 0]);
    s.dump(mEdgeArray[i * 2 + 1]);
  }

  // パタングラフの情報のダンプ
  s.dump(pat_num());
  for ( auto& pat: mPatArray ) {
    pat.dump(s);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
CiPatGraph::dump(
  Serializer& s
) const
{
  s.dump(mRepClass);
  s.dump(mInputNum);
  s.dump(mEdgeList);
}

END_NAMESPACE_YM_CLIB
