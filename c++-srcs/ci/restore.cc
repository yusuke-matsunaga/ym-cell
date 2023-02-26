
/// @file CiCellLibrary_restore.cc
/// @brief CiCellLibrary の実装ファイル(restore()関係)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellLibrary.h"
#include "ci/CiCellClass.h"
#include "ci/CiCellGroup.h"
#include "ci/CiCell.h"
#include "ci/CiPin.h"
#include "ci/CiBus.h"
#include "ci/CiBusType.h"
#include "ci/CiBundle.h"
#include "ci/CiTiming.h"
#include "ci/CiLutTemplate.h"
#include "ci/CiLut.h"
#include "ci/CiPatMgr.h"
#include "ci/CiPatGraph.h"
#include "ym/ClibIOMap.h"
#include "ym/Range.h"

#include "CiFFCell.h"
#include "CiLatchCell.h"
#include "CiFsmCell.h"

BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// 番号のベクタの読み込み
inline
void
restore_vector(
  BinDec& s,
  vector<SizeType>& vec
)
{
  SizeType n;
  s >> n;
  vec.resize(n);
  for ( SizeType i: Range(n) ) {
    s >> vec[i];
  }
}

// 数値のベクタの読み込み
inline
void
restore_dvector(
  BinDec& s,
  vector<double>& vec
)
{
  SizeType n;
  s >> n;
  vec.resize(n);
  for ( SizeType i: Range(n) ) {
    s >> vec[i];
  }
}

END_NONAMESPACE


//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

void
CiCellLibrary::restore(
  istream& is
)
{
  clear();

  BinDec bs{is};

  // 名前
  restore_name(bs);

  // テクノロジ
  restore_technology(bs);

  // 遅延モデル
  restore_delay_model(bs);

  // バス命名規則
  restore_str_attr(bs, "bus_naming_style");

  // 日付情報
  restore_str_attr(bs, "date");

  // リビジョン情報
  restore_str_attr(bs, "revision");

  // コメント
  restore_str_attr(bs, "comment");

  // 時間単位
  restore_str_attr(bs, "time_unit");

  // 電圧単位
  restore_str_attr(bs, "voltage_unit");

  // 電流単位
  restore_str_attr(bs, "current_unit");

  // 抵抗単位
  restore_str_attr(bs, "pulling_resistance_unit");

  // 容量単位
  restore_capacitive_load_unit(bs);

  // 電力単位
  restore_str_attr(bs, "leakage_power_unit");

  // バスタイプ情報の読み込み
  restore_bustype(bs);

  // LUTテンプレート情報の読み込み
  restore_lut_template(bs);

  // セル情報の読み込み
  restore_cell(bs);

  // ピン情報の読み込み
  restore_pin(bs);

  // バス情報の読み込み
  restore_bus(bs);

  // バンドル情報の読み込み
  restore_bundle(bs);

  // セルごとのピン，バス，バンドルの辞書を作る．
  construct_cellpin_dict();

  // タイミング情報の読み込み
  restore_timing(bs);

  // LUT の読み込み
  restore_lut(bs);

  // セルグループ情報の読み込み
  restore_cell_group(bs);

  // セルクラス情報の読み込み
  restore_cell_class(bs);

  // 組み込み型の読み込み
  for ( auto id: Range(4) ) {
    bs >> mLogicGroup[id];
  }
  restore_vector(bs, mSimpleFFClass);
  restore_vector(bs, mSimpleLatchClass);

  // パタングラフの情報の設定
  mPatMgr.restore(bs);
}

// @brief バスタイプを読み込む．
void
CiCellLibrary::restore_bustype(
  BinDec& s
)
{
  SizeType n;
  s >> n;
  mBusTypeList.reserve(n);
  for ( SizeType id: Range(n) ) {
    auto bustype = unique_ptr<CiBusType>{new CiBusType};
    bustype->restore(s);
    mBusTypeDict.emplace(bustype->_name(), id);
    mBusTypeList.push_back(std::move(bustype));
  }
}

// @brief LUT テンプレートを読み込む．
void
CiCellLibrary::restore_lut_template(
  BinDec& s
)
{
  // 要素数
  SizeType n;
  s >> n;
  mLutTemplateList.reserve(n);
  for ( auto id: Range(n) ) {
    ymuint8 d;
    s >> d;
    unique_ptr<CiLutTemplate> ptr;
    switch ( d ) {
    case 1:
      ptr = unique_ptr<CiLutTemplate>{new CiLutTemplate1D};
      break;
    case 2:
      ptr = unique_ptr<CiLutTemplate>{new CiLutTemplate2D};
      break;
    case 3:
      ptr = unique_ptr<CiLutTemplate>{new CiLutTemplate3D};
      break;
    }
    ptr->restore(s);
    mLutDict.emplace(ptr->_name(), id);
    mLutTemplateList.push_back(std::move(ptr));
  }
  mRefLutTemplateList.resize(n);
  for ( SizeType id: Range(n) ) {
    mRefLutTemplateList[id] = id;
  }
}

// @brief セルを読み込む．
void
CiCellLibrary::restore_cell(
  BinDec& s
)
{
  // 要素数
  SizeType nc;
  s >> nc;
  mCellList.reserve(nc);
  for ( auto id: Range(nc) ) {
    ymuint8 type;
    s >> type;
    unique_ptr<CiCell> ptr;
    switch ( type ) {
    case 0:
      ptr = unique_ptr<CiCell>{new CiCell};
      break;

    case 1:
      ptr = unique_ptr<CiCell>{new CiFFCell};
      break;

    case 2:
      ptr = unique_ptr<CiCell>{new CiFF2Cell};
      break;

    case 3:
      ptr = unique_ptr<CiCell>{new CiLatchCell};
      break;

    case 4:
      ptr = unique_ptr<CiCell>{new CiLatch2Cell};
      break;

    case 5:
      ptr = unique_ptr<CiCell>{new CiFsmCell};
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    ptr->restore(s);
    mCellDict.emplace(ptr->_name(), id);
    mCellList.push_back(std::move(ptr));
  }
  mRefCellList.resize(nc);
  for ( SizeType id: Range(nc) ) {
    mRefCellList[id] = id;
  }
}

// @brief ピン情報を読み込む．
void
CiCellLibrary::restore_pin(
  BinDec& s
)
{
  SizeType n;
  s >> n;
  mPinList.reserve(n);
  for ( SizeType _: Range(n) ) {
    ymuint8 sig;
    s >> sig;
    unique_ptr<CiPin> pin;
    switch ( sig ) {
    case 0: // 入力ピン
      pin = unique_ptr<CiPin>{new CiInputPin};
      break;

    case 1: // 出力ピン
      pin = unique_ptr<CiPin>{new CiOutputPin};
      break;

    case 2: // 入出力ピン
      pin = unique_ptr<CiPin>{new CiInoutPin};
      break;

    case 3: // 内部ピン
      pin = unique_ptr<CiPin>{new CiInternalPin};
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    pin->restore(s);
    mPinList.push_back(std::move(pin));
  }
}

// @brief バス情報を読み込む．
void
CiCellLibrary::restore_bus(
  BinDec& s
)
{
  SizeType n;
  s >> n;
  mBusList.reserve(n);
  for ( SizeType _: Range(n) ) {
    unique_ptr<CiBus> bus{new CiBus};
    bus->restore(s);
    mBusList.push_back(std::move(bus));
  }
}

// @brief バンドル情報を読み込む．
void
CiCellLibrary::restore_bundle(
  BinDec& s
)
{
  SizeType n;
  s >> n;
  mBundleList.reserve(n);
  for ( SizeType _: Range(n) ) {
    unique_ptr<CiBundle> bundle{new CiBundle};
    bundle->restore(s);
    mBundleList.push_back(std::move(bundle));
  }
}

// @brief セルごとのピン，バス，バンドルの辞書を作る．
void
CiCellLibrary::construct_cellpin_dict()
{
  for ( SizeType cell_id: mRefCellList ) {
    auto& cell = mCellList[cell_id];
    for ( auto pin_id: cell->pin_list() ) {
      auto& pin = mPinList[pin_id];
      mPinDict.add(cell_id, pin->_name(), pin_id);
    }
    for ( auto bus_id: cell->bus_list() ) {
      auto& bus = mBusList[bus_id];
      mBusDict.add(cell_id, bus->_name(), bus_id);
    }
    for ( auto bundle_id: cell->bundle_list() ) {
      auto& bundle = mBundleList[bundle_id];
      mBundleDict.add(cell_id, bundle->_name(), bundle_id);
    }
  }
}

// @brief タイミング情報を読み込む．
void
CiCellLibrary::restore_timing(
  BinDec& s
)
{
  SizeType n;
  s >> n;
  mTimingList.reserve(n);
  for ( SizeType _: Range(n) ) {
    ymuint8 ttype;
    s >> ttype;
    unique_ptr<CiTiming> timing;
    switch ( ttype ) {
    case 0:
      timing = unique_ptr<CiTiming>{new CiTimingGeneric};
      break;

    case 1:
      timing = unique_ptr<CiTiming>{new CiTimingPiecewise};
      break;

    case 2:
      timing = unique_ptr<CiTiming>{new CiTimingLut1};
      break;

    case 3:
      timing = unique_ptr<CiTiming>{new CiTimingLut2};
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    timing->restore(s);
    mTimingList.push_back(std::move(timing));
  }
}

// @brief LUT を読み込む．
void
CiCellLibrary::restore_lut(
  BinDec& s
)
{
  SizeType n;
  s >> n;
  mLutList.reserve(n);
  for ( SizeType i: Range(n)) {
    ymuint8 d;
    s >> d;
    unique_ptr<CiLut> lut;
    switch ( d ) {
    case 1:
      lut = unique_ptr<CiLut>{new CiLut1D};
      break;

    case 2:
      lut = unique_ptr<CiLut>{new CiLut2D};
      break;

    case 3:
      lut = unique_ptr<CiLut>{new CiLut3D};
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    lut->restore(s);
    mLutList.push_back(std::move(lut));
  }
}

// @brief セルグループを読み込む．
void
CiCellLibrary::restore_cell_group(
  BinDec& s
)
{
  SizeType ng;
  s >> ng;
  mGroupList.reserve(ng);
  for ( auto _: Range(ng) ) {
    auto group = unique_ptr<CiCellGroup>{new CiCellGroup};
    group->restore(s);
    mGroupList.push_back(std::move(group));
  }
  mRefGroupList.resize(ng);
  for ( SizeType id: Range(ng) ) {
    mRefGroupList[id] = id;
  }
}

// @brief セルクラスを読み込む．
void
CiCellLibrary::restore_cell_class(
  BinDec& s
)
{
  SizeType nc;
  s >> nc;
  mClassList.reserve(nc);
  for ( auto _: Range(nc) ) {
    auto cc = unique_ptr<CiCellClass>{new CiCellClass};
    cc->restore(s);
    mClassList.push_back(std::move(cc));
  }
  mRefClassList.resize(nc);
  for ( SizeType id: Range(nc) ) {
    mRefClassList[id] = id;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiBusType
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiBusType::restore(
  BinDec& s
)
{
  s >> mName
    >> mBitWidth
    >> mBitFrom
    >> mBitTo;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLutTemplate::restore_common(
  BinDec& s
)
{
  s >> mId
    >> mName;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate1D
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLutTemplate1D::restore(
  BinDec& s
)
{
  restore_common(s);
  s >> mVarType;
  restore_dvector(s, mIndexArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate2D
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLutTemplate2D::restore(
  BinDec& s
)
{
  restore_common(s);
  for ( SizeType i: Range(2) ) {
    s >> mVarType[i];
    restore_dvector(s, mIndexArray[i]);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate3D
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLutTemplate3D::restore(
  BinDec& s
)
{
  restore_common(s);
  for ( SizeType i: Range(3) ) {
    s >> mVarType[i];
    restore_dvector(s, mIndexArray[i]);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiCell::restore(
  BinDec& s
)
{
  s >> mId
    >> mName
    >> mArea
    >> mInputNum
    >> mOutputNum
    >> mInoutNum;

  // ピンリスト
  restore_vector(s, mPinList);

  // 入力ピンリスト
  restore_vector(s, mInputList);

  // 出力ピンリスト
  restore_vector(s, mOutputList);

  // 内部ピンリスト
  restore_vector(s, mInternalList);

  // バス番号のリスト
  restore_vector(s, mBusList);

  // バンドル番号のリスト
  restore_vector(s, mBundleList);

  // タイミング番号のリスト
  restore_vector(s, mTimingList);

  // タイミングマップ
  SizeType n;
  s >> n;
  mTimingMap.resize(n);
  for ( SizeType i: Range(n) ) {
    restore_vector(s, mTimingMap[i]);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiFLCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiFLCell::restore(
  BinDec& s
)
{
  CiCell::restore(s);
  s >> mVar1
    >> mVar2;
  mClear.restore(s);
  mPreset.restore(s);
  s >> mCpv1
    >> mCpv2;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiFFCell::restore(
  BinDec& s
)
{
  CiFLCell::restore(s);
  mClock.restore(s);
  mNextState.restore(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiFF2Cell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiFF2Cell::restore(
  BinDec& s
)
{
  CiFFCell::restore(s);
  mClock2.restore(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLatchCell::restore(
  BinDec& s
)
{
  CiFLCell::restore(s);
  mEnable.restore(s);
  mDataIn.restore(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatch2Cell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLatch2Cell::restore(
  BinDec& s
)
{
  CiLatchCell::restore(s);
  mEnable2.restore(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiFsmCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiFsmCell::restore(
  BinDec& s
)
{
  CiCell::restore(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiPin::restore_common(
  BinDec& s
)
{
  s >> mName
    >> mPinId;
}


//////////////////////////////////////////////////////////////////////
// クラス CiInputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiInputPin::restore(
  BinDec& s
)
{
  restore_common(s);
  s >> mInputId
    >> mCapacitance
    >> mRiseCapacitance
    >> mFallCapacitance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiOutputPin::restore(
  BinDec& s
)
{
  restore_base(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiInoutPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiInoutPin::restore(
  BinDec& s
)
{
  restore_base(s);
  s >> mInputId
    >> mCapacitance
    >> mRiseCapacitance
    >> mFallCapacitance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiInternalPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiInternalPin::restore(
  BinDec& s
)
{
  restore_common(s);
  s >> mInternalId;
}


//////////////////////////////////////////////////////////////////////
// クラス CiBus
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiBus::restore(
  BinDec& s
)
{
  s >> mName
    >> mBusType;
  restore_vector(s, mPinList);
}


//////////////////////////////////////////////////////////////////////
// クラス CiBundle
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiBundle::restore(
  BinDec& s
)
{
  s >> mName;
  restore_vector(s, mPinList);
}


//////////////////////////////////////////////////////////////////////
// クラス CiTiming
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiTiming::restore(
  BinDec& s
)
{
  s >> mId
    >> mType;
  mCond.restore(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingGP
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiTimingGP::restore(
  BinDec& s
)
{
  CiTiming::restore(s);
  s >> mIntrinsicRise
    >> mIntrinsicFall
    >> mSlopeRise
    >> mSlopeFall;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingGeneric
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiTimingGeneric::restore(
  BinDec& s
)
{
  CiTimingGP::restore(s);
  s >> mRiseResistance
    >> mFallResistance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingPiecewise
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiTimingPiecewise::restore(
  BinDec& s
)
{
  CiTimingGP::restore(s);
  s >> mRisePinResistance
    >> mFallPinResistance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiTimingLut::restore(
  BinDec& s
)
{
  CiTiming::restore(s);
  s >> mRiseTransition
    >> mFallTransition;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut1
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiTimingLut1::restore(
  BinDec& s
)
{
  CiTimingLut::restore(s);
  s >> mCellRise
    >> mCellFall;
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingLut2
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiTimingLut2::restore(
  BinDec& s
)
{
  CiTimingLut::restore(s);
  s >> mRisePropagation
    >> mFallPropagation;
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiCellGroup::restore(
  BinDec& s
)
{
  s >> mRepClass;
  mIoMap.restore(s);
  restore_vector(s, mCellList);
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellclass
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiCellClass::restore(
  BinDec& s
)
{
  SizeType n;
  s >> n;
  mIdMapList.resize(n);
  for ( auto i: Range(n) ) {
    mIdMapList[i].restore(s);
  }
  restore_vector(s, mGroupList);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLut::restore_common(
  BinDec& s
)
{
  s >> mTemplate;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut1D
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLut1D::restore(
  BinDec& s
)
{
  restore_common(s);
  restore_dvector(s, mIndexArray);
  restore_dvector(s, mValueArray);
  init();
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut2D
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLut2D::restore(
  BinDec& s
)
{
  restore_common(s);
  restore_dvector(s, mIndexArray[0]);
  restore_dvector(s, mIndexArray[1]);
  restore_dvector(s, mValueArray);
  init();
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut3D
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLut3D::restore(
  BinDec& s
)
{
  restore_common(s);
  restore_dvector(s, mIndexArray[0]);
  restore_dvector(s, mIndexArray[1]);
  restore_dvector(s, mIndexArray[2]);
  restore_dvector(s, mValueArray);
  init();
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatMgr
//////////////////////////////////////////////////////////////////////

// @brief データを読み込んでセットする．
bool
CiPatMgr::restore(
  BinDec& bis
)
{
  // ノードと枝の情報を読み込む．
  SizeType nn;
  bis >> nn;
  set_node_num(nn);
  for ( auto i: Range(node_num()) ) {
    bis >> mNodeTypeArray[i]
	>> mEdgeArray[i * 2]
	>> mEdgeArray[i * 2 + 1];
  }

  // パタングラフの情報を読み込む．
  SizeType np;
  bis >> np;
  set_pat_num(np);
  for ( auto id: Range(pat_num()) ) {
    mPatArray[id].restore(bis);
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief バイナリファイルを読み込む．
void
CiPatGraph::restore(
  BinDec& bis
)
{
  SizeType ne;

  bis >> mRepId
      >> mInputNum
      >> ne;
  mEdgeList.clear();
  mEdgeList.resize(ne);
  for ( auto i: Range(ne) ) {
    bis >> mEdgeList[i];
  }
}

END_NAMESPACE_YM_CLIB
