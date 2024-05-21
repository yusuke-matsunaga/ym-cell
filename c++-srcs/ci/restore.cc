﻿
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
#include "ci/Deserializer.h"
#include "ym/ClibIOMap.h"
#include "ym/Range.h"

#include "CiFFCell.h"
#include "CiLatchCell.h"
#include "CiFsmCell.h"
#include "CiPin_sub.h"
#include "CiTiming_sub.h"
#include "CiLutTemplate_sub.h"
#include "CiLut_sub.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

#if 0
// 番号のベクタの読み込み
inline
void
restore_vector(
  BinDec& s,
  vector<SizeType>& vec
)
{
  SizeType n = s.read_64();
  vec.resize(n);
  for ( SizeType i: Range(n) ) {
    vec[i] = s.read_64();
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
  SizeType n = s.read_64();
  vec.resize(n);
  for ( SizeType i: Range(n) ) {
    s >> vec[i];
  }
}

// セルクラスのリストの読み込み
void
restore_class_list(
  BinDec& s,
  vector<const CiCellClass*>& dst_list,
  const vector<const CiCellClass*>& class_list
)
{
  SizeType n = s.read_64();
  dst_list.resize(n);
  for ( SizeType i: Range(n) ) {
    SizeType id;
    s >> id;
    dst_list[i] = class_list[id];
  }
}

// ピンのリストの読み込み
void
restore_pin_list(
  BinDec& s,
  vector<const CiPin*>& dst_list,
  const vector<unique_ptr<CiPin>>& src_list
)
{
  SizeType n = s.read_64();
  dst_list.resize(n);
  for ( SizeType i: Range(n) ) {
    SizeType id;
    s >> id;
    dst_list[i] = src_list[id].get();
  }
}

// バスのリストの読み込み
void
restore_bus_list(
  BinDec& s,
  vector<const CiBus*>& dst_list,
  const vector<unique_ptr<CiBus>>& src_list
)
{
  SizeType n = s.read_64();
  dst_list.resize(n);
  for ( SizeType i: Range(n) ) {
    SizeType id;
    s >> id;
    dst_list[i] = src_list[id].get();
  }
}

// バンドルのリストの読み込み
void
restore_bundle_list(
  BinDec& s,
  vector<const CiBundle*>& dst_list,
  const vector<unique_ptr<CiBundle>>& src_list
)
{
  SizeType n = s.read_64();
  dst_list.resize(n);
  for ( SizeType i: Range(n) ) {
    SizeType id;
    s >> id;
    dst_list[i] = src_list[id].get();
  }
}

// タイミングのリストの読み込み
void
restore_timing_list(
  BinDec& s,
  vector<const CiTiming*>& dst_list,
  const vector<unique_ptr<CiTiming>>& src_list
)
{
  SizeType n = s.read_64();
  dst_list.resize(n);
  for ( SizeType i: Range(n) ) {
    SizeType id;
    s >> id;
    dst_list[i] = src_list[id].get();
  }
}

// LUTの読み込み
const CiLut*
restore_lut(
  BinDec& s,
  const vector<unique_ptr<CiLut>>& src_list
)
{
  SizeType id;
  s >> id;
  return src_list[id].get();
}
#endif

END_NONAMESPACE


//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

void
CiCellLibrary::restore(
  istream& is
)
{
  Deserializer s{is};

  clear();

  // 要素を復元する．
  s.deserialize(this);

  // 名前
  restore_name(s);

  // テクノロジ
  restore_technology(s);

  // 遅延モデル
  restore_delay_model(s);

  // バス命名規則
  restore_str_attr(s, "bus_naming_style");

  // 日付情報
  restore_str_attr(s, "date");

  // リビジョン情報
  restore_str_attr(s, "revision");

  // コメント
  restore_str_attr(s, "comment");

  // 時間単位
  restore_str_attr(s, "time_unit");

  // 電圧単位
  restore_str_attr(s, "voltage_unit");

  // 電流単位
  restore_str_attr(s, "current_unit");

  // 抵抗単位
  restore_str_attr(s, "pulling_resistance_unit");

  // 容量単位
  restore_capacitive_load_unit(s);

  // 電力単位
  restore_str_attr(s, "leakage_power_unit");

  // バスタイプのリスト
  {
    SizeType n;
    s.restore(n);
    mBusTypeList.reserve(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      auto obj = s.restore_bustype();
      mBusTypeList.push_back(unique_ptr<CiBusType>{obj});
    }
  }
#if 0
  // LUTテンプレートのリスト
  s.restore(mLutTemplateList);

  // セルのリスト
  s.restore(mCellList);

  // セルグループのリスト
  s.restore(mCellGroupList);

  // セルクラスのリスト
  s.restore(mCellClassList);
#endif

  // 組み込み型の読み込み
  for ( auto id: Range(4) ) {
    mLogicGroup[id] = s.restore_cellgroup();
  }
  {
    SizeType n;
    s.restore(n);
    mSimpleFFClass.reserve(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      auto cclass = s.restore_cellclass();
      mSimpleFFClass.push_back(cclass);
    }
  }
  {
    SizeType n;
    s.restore(n);
    mSimpleLatchClass.reserve(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      auto cclass = s.restore_cellclass();
      mSimpleLatchClass.push_back(cclass);
    }
  }

  // パタングラフの情報の設定
  mPatMgr.restore(s);
}

// @brief 名前を読み込む．
void
CiCellLibrary::restore_name(
  Deserializer& s
)
{
  string name;
  s.in() >> name;
  mName = name;
}

// @brief 'technology' を読み込む．
void
CiCellLibrary::restore_technology(
  Deserializer& s
)
{
  auto tmp = s.in().read_8();
  mTechnology = static_cast<ClibTechnology>(tmp);
}

// @brief 遅延モデルを読み込む．
void
CiCellLibrary::restore_delay_model(
  Deserializer& s
)
{
  auto tmp = s.in().read_8();
  mDelayModel = static_cast<ClibDelayModel>(tmp);
}

// @brief 'capacitive_load_unit' を読み込む．
void
CiCellLibrary::restore_capacitive_load_unit(
  Deserializer& s
)
{
  double unit;
  string ustr;
  s.in() >> unit
	 >> ustr;
  mCapacitiveLoadUnit = unit;
  mCapacitiveLoadUnitStr = ustr;
}

// @brief 属性を読み込む(浮動小数点型)
void
CiCellLibrary::restore_double_attr(
  Deserializer& s,
  const string& attr_name
)
{
  double val;
  s.restore(val);
  set_attr(attr_name, val);
}

// @brief 属性を読み込む(文字列型)．
void
CiCellLibrary::restore_str_attr(
  Deserializer& s,
  const string& attr_name
)
{
  string val;
  s.in() >> val;
  set_attr(attr_name, val);
}

#if 0
// @brief バスタイプを読み込む．
void
CiCellLibrary::restore_bustype(
  Deserializer& s
)
{
  SizeType n = s.in().read_64();
  mBusTypeList.reserve(n);
  for ( SizeType id: Range(n) ) {
    ShString name;
    s.in() >> name;
    auto bit_from = s.in().read_64();
    auto bit_to = s.in().read_64();
    auto ptr = unique_ptr<CiBusType>{new CiBusType{this, name, bit_from, bit_to}};
    mBusTypeDict.emplace(name, ptr.get());
    s.reg_obj(ptr.get());
    mBusTypeList.push_back(std::move(ptr));
  }
}

// @brief LUT テンプレートを読み込む．
void
CiCellLibrary::restore_lut_template(
  Deserializer& s
)
{
  // 要素数
  SizeType n = s.in().read_64();
  mLutTemplateList.reserve(n);
  mRefLutTemplateList.reserve(n);
  for ( auto id: Range(n) ) {
    auto d = s.in().read_8();
    unique_ptr<CiLutTemplate> ptr;
    switch ( d ) {
    case 1:
      {
	ClibVarType var_type;
	s.in() >> var_type;
	vector<double> index_array;
	s.restore(index_array);
	ptr = unique_ptr<CiLutTemplate>{new CiLutTemplate1D{this, var_type,
							    index_array}};
      }
      break;
    case 2:
      {
	ClibVarType var_type1;
	s.in() >> var_type1;
	vector<double> index_array1;
	s.restore(index_array1);
	ClibVarType var_type2;
	s.in() >> var_type2;
	vector<double> index_array2;
	s.restore(index_array2);
	ptr = unique_ptr<CiLutTemplate>{new CiLutTemplate2D{this,
							    var_type1, index_array1,
							    var_type2, index_array2}};
      }
      break;
    case 3:
      {
	ClibVarType var_type1;
	s.in() >> var_type1;
	vector<double> index_array1;
	s.restore(index_array1);
	ClibVarType var_type2;
	s.in() >> var_type2;
	vector<double> index_array2;
	s.restore(index_array2);
	ClibVarType var_type3;
	s.in() >> var_type3;
	vector<double> index_array3;
	s.restore(index_array3);
	ptr = unique_ptr<CiLutTemplate>{new CiLutTemplate3D{this,
							    var_type1, index_array1,
							    var_type2, index_array2,
							    var_type3, index_array3}};
      }
      break;
    }
    s.reg_obj(ptr.get());
    mRefLutTemplateList.push_back(ptr.get());
    mLutTemplateList.push_back(std::move(ptr));
  }
}

// @brief ピン情報を読み込む．
void
CiCellLibrary::restore_pin(
  Deserializer& s
)
{
  SizeType n = s.in().read_64();
  mPinList.reserve(n);
  for ( SizeType _: Range(n) ) {
    auto sig = s.in().read_8();
    unique_ptr<CiPin> pin;
    switch ( sig ) {
    case 0: // 入力ピン
      pin = unique_ptr<CiPin>{new CiInputPin{this}};
      break;

    case 1: // 出力ピン
      pin = unique_ptr<CiPin>{new CiOutputPin{this}};
      break;

    case 2: // 入出力ピン
      pin = unique_ptr<CiPin>{new CiInoutPin{this}};
      break;

    case 3: // 内部ピン
      pin = unique_ptr<CiPin>{new CiInternalPin{this}};
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    pin->restore(s);
    s.reg_obj(pin.get());
    mPinList.push_back(std::move(pin));
  }
}

// @brief バス情報を読み込む．
void
CiCellLibrary::restore_bus(
  Deserializer& s
)
{
  SizeType n = s.in().read_64();
  mBusList.reserve(n);
  for ( SizeType _: Range(n) ) {
    ShString name;
    s.in() >> name;
    const CiBusType* bus_type;
    s.restore(bus_type);
    vector<const CiPin*> pin_list;
    s.restore(pin_list);
    auto ptr = unique_ptr<CiBus>{new CiBus{this, name, bus_type, pin_list}};
    s.reg_obj(ptr.get());
    mBusList.push_back(std::move(ptr));
  }
}

// @brief バンドル情報を読み込む．
void
CiCellLibrary::restore_bundle(
  Deserializer& s
)
{
  SizeType n = s.in().read_64();
  mBundleList.reserve(n);
  for ( SizeType _: Range(n) ) {
    ShString name;
    s.in() >> name;
    vector<const CiPin*> pin_list;
    s.restore(pin_list);
    auto ptr = unique_ptr<CiBundle>{new CiBundle{this, name, pin_list}};
    s.reg_obj(ptr.get());
    mBundleList.push_back(std::move(ptr));
  }
}

// @brief セルごとのピン，バス，バンドルの辞書を作る．
void
CiCellLibrary::construct_cellpin_dict()
{
  for ( auto cell: mRefCellList ) {
    for ( auto pin: cell->pin_list() ) {
      mPinDict.add(cell, pin->_name(), pin);
    }
    for ( auto bus: cell->bus_list() ) {
      mBusDict.add(cell, bus->_name(), bus);
    }
    for ( auto bundle: cell->bundle_list() ) {
      mBundleDict.add(cell, bundle->_name(), bundle);
    }
  }
}

// @brief タイミング情報を読み込む．
void
CiCellLibrary::restore_timing(
  Deserializer& s
)
{
  SizeType n = s.in().read_64();
  mTimingList.reserve(n);
  for ( SizeType _: Range(n) ) {
    auto ttype = s.in().read_8();
    unique_ptr<CiTiming> timing;
    switch ( ttype ) {
    case 0:
      timing = unique_ptr<CiTiming>{new CiTimingGeneric{this}};
      break;

    case 1:
      timing = unique_ptr<CiTiming>{new CiTimingPiecewise{this}};
      break;

    case 2:
      timing = unique_ptr<CiTiming>{new CiTimingLut1{this}};
      break;

    case 3:
      timing = unique_ptr<CiTiming>{new CiTimingLut2{this}};
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    timing->restore(s);
    s.reg_obj(timing.get());
    mTimingList.push_back(std::move(timing));
  }
}

// @brief LUT を読み込む．
void
CiCellLibrary::restore_lut(
  Deserializer& s
)
{
  SizeType n = s.in().read_64();
  mLutList.reserve(n);
  for ( SizeType i: Range(n)) {
    auto d = s.in().read_8();
    unique_ptr<CiLut> lut;
    switch ( d ) {
    case 1:
      lut = unique_ptr<CiLut>{new CiLut1D{this}};
      break;

    case 2:
      lut = unique_ptr<CiLut>{new CiLut2D{this}};
      break;

    case 3:
      lut = unique_ptr<CiLut>{new CiLut3D{this}};
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    lut->restore(s);
    s.reg_obj(lut.get());
    mLutList.push_back(std::move(lut));
  }
}

// @brief セルグループを読み込む．
void
CiCellLibrary::restore_cell_group(
  Deserializer& s
)
{
  SizeType ng = s.in().read_64();
  mGroupList.reserve(ng);
  mRefGroupList.reserve(ng);
  for ( auto _: Range(ng) ) {
    auto ptr = unique_ptr<CiCellGroup>{new CiCellGroup{this}};
    ptr->restore(s);
    auto group = ptr.get();
    s.reg_obj(group);
    mRefGroupList.push_back(group);
    mGroupList.push_back(std::move(ptr));
  }
}

// @brief セルクラスを読み込む．
void
CiCellLibrary::restore_cell_class(
  Deserializer& s
)
{
  SizeType nc = s.in().read_64();
  mClassList.reserve(nc);
  mRefClassList.reserve(nc);
  for ( auto _: Range(nc) ) {
    auto ptr = unique_ptr<CiCellClass>{new CiCellClass{this}};
    ptr->restore(s);
    auto cc = ptr.get();
    s.reg_obj(cc);
    mRefClassList.push_back(cc);
    mClassList.push_back(std::move(ptr));
  }
}
#endif


//////////////////////////////////////////////////////////////////////
// クラス CiBussType
//////////////////////////////////////////////////////////////////////

// @brief バスタイプを読み込む．
CiBusType*
CiBusType::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  ShString name;
  s.in() >> name;
  auto bit_from = s.in().read_64();
  auto bit_to = s.in().read_64();
  auto ptr = new CiBusType{lib, name, bit_from, bit_to};
  return ptr;
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellclass
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
CiCellClass*
CiCellClass::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  SizeType n = s.in().read_64();
  vector<ClibIOMap> idmap_list(n);
  for ( auto i: Range(n) ) {
    idmap_list[i].restore(s.in());
  }
  auto cclass = new CiCellClass{lib, idmap_list};
  return cclass;
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
CiCellGroup*
CiCellGroup::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  CiCellClass* rep_class;
  ClibIOMap iomap;
  s.restore(rep_class);
  iomap.restore(s.in());
  auto cellgroup = new CiCellGroup{lib, rep_class, iomap};
  rep_class->add_group(cellgroup);
  return cellgroup;
}


//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
CiCell*
CiCell::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  auto type = s.in().read_8();
  CiCell* cell = nullptr;
  switch ( type ) {
  case 0: cell = new CiCell{lib}; break;
  case 1: cell = new CiFFCell{lib}; break;
  case 2: cell = new CiFF2Cell{lib}; break;
  case 3: cell = new CiLatchCell{lib}; break;
  case 4: cell = new CiLatch2Cell{lib}; break;
  case 5: cell = new CiFsmCell{lib}; break;
  default:
    ASSERT_NOT_REACHED;
    break;
  }
  cell->_restore(s);
  return cell;
}

// logic タイプのセルの復元
void
CiCell::_restore(
  Deserializer& s
)
{
  s.in() >> mName
	 >> mArea;
  s.restore(mInputNum);
  s.restore(mOutputNum);
  s.restore(mInoutNum);

  // ピンリスト
  s.restore(mPinList);

  // 入力ピンリスト
  s.restore(mInputList);

  // 出力ピンリスト
  s.restore(mOutputList);

  // 内部ピンリスト
  s.restore(mInternalList);

  // バスのリスト
  s.restore(mBusList);

  // バンドルのリスト
  s.restore(mBundleList);

  // タイミングのリスト
  s.restore(mTimingList);

  // タイミングマップ
  SizeType n = s.in().read_64();
  mTimingMap.resize(n);
  for ( SizeType i: Range(n) ) {
    s.restore(mTimingMap[i]);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiFLCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiFLCell::restore_FL(
  Deserializer& s
)
{
  CiCell::_restore(s);
  s.in() >> mVar1
	 >> mVar2;
  mClear.restore(s.in());
  mPreset.restore(s.in());
  s.in() >> mCpv1
	 >> mCpv2;
}


//////////////////////////////////////////////////////////////////////
// クラス CiFFCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiFFCell::_restore(
  Deserializer& s
)
{
  restore_FL(s);
  mClock.restore(s.in());
  mNextState.restore(s.in());
}


//////////////////////////////////////////////////////////////////////
// クラス CiFF2Cell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiFF2Cell::_restore(
  Deserializer& s
)
{
  CiFFCell::_restore(s);
  mClock2.restore(s.in());
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatchCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLatchCell::_restore(
  Deserializer& s
)
{
  restore_FL(s);
  mEnable.restore(s.in());
  mDataIn.restore(s.in());
}


//////////////////////////////////////////////////////////////////////
// クラス CiLatch2Cell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLatch2Cell::_restore(
  Deserializer& s
)
{
  CiLatchCell::_restore(s);
  mEnable2.restore(s.in());
}


//////////////////////////////////////////////////////////////////////
// クラス CiFsmCell
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiFsmCell::_restore(
  Deserializer& s
)
{
  CiCell::_restore(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiPin
//////////////////////////////////////////////////////////////////////

// @brief ピン情報を復元する．
CiPin*
CiPin::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  auto sig = s.in().read_8();
  CiPin* pin = nullptr;
  switch ( sig ) {
  case 0: // 入力ピン
    pin = new CiInputPin{lib}; break;
  case 1: // 出力ピン
    pin = new CiOutputPin{lib}; break;
  case 2: // 入出力ピン
    pin = new CiInoutPin{lib}; break;
  case 3: // 内部ピン
    pin = new CiInternalPin{lib}; break;
  default:
    ASSERT_NOT_REACHED;
    break;
  }
  pin->_restore(s);
  return pin;
}

// @brief 内容を読み込む．
void
CiPin::restore_common(
  Deserializer& s
)
{
  s.in() >> mName;
  s.restore(mPinId);
}


//////////////////////////////////////////////////////////////////////
// クラス CiInputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiInputPin::_restore(
  Deserializer& s
)
{
  restore_common(s);
  s.restore(mInputId);
  s.in() >> mCapacitance
	 >> mRiseCapacitance
	 >> mFallCapacitance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPinBase
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiOutputPinBase::restore_base(
  Deserializer& s
)
{
  restore_common(s);
  s.restore(mOutputId);
  s.in() >> mFanoutLoad
	 >> mMaxFanout
	 >> mMinFanout
	 >> mMaxCapacitance
	 >> mMinCapacitance
	 >> mMaxTransition
	 >> mMinTransition;
  mFunction.restore(s.in());
  mTristate.restore(s.in());
}


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiOutputPin::_restore(
  Deserializer& s
)
{
  restore_base(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiInoutPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiInoutPin::_restore(
  Deserializer& s
)
{
  restore_base(s);
  s.restore(mInputId);
  s.in() >> mCapacitance
	 >> mRiseCapacitance
	 >> mFallCapacitance;
}


//////////////////////////////////////////////////////////////////////
// クラス CiInternalPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiInternalPin::_restore(
  Deserializer& s
)
{
  restore_common(s);
  s.restore(mInternalId);
}


//////////////////////////////////////////////////////////////////////
// クラス CiBus
//////////////////////////////////////////////////////////////////////

CiBus*
CiBus::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  ShString name;
  s.in() >> name;
  const CiBusType* bus_type;
  s.restore(bus_type);
  vector<const CiPin*> pin_list;
  s.restore(pin_list);
  return new CiBus{lib, name, bus_type, pin_list};
}


//////////////////////////////////////////////////////////////////////
// クラス CiBundle
//////////////////////////////////////////////////////////////////////

CiBundle*
CiBundle::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  ShString name;
  s.in() >> name;
  vector<const CiPin*> pin_list;
  s.restore(pin_list);
  return new CiBundle{lib, name, pin_list};
}


//////////////////////////////////////////////////////////////////////
// クラス CiTiming
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
CiTiming*
CiTiming::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  auto ttype = s.in().read_8();
  CiTiming* timing = nullptr;
  switch ( ttype ) {
  case 0: timing = new CiTimingGeneric{lib}; break;
  case 1: timing = new CiTimingPiecewise{lib}; break;
  case 2: timing = new CiTimingLut1{lib}; break;
  case 3: timing = new CiTimingLut2{lib}; break;
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
  s.in() >> mType;
  mCond.restore(s.in());
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingGP
//////////////////////////////////////////////////////////////////////

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



//////////////////////////////////////////////////////////////////////
// クラス LutTemplate
//////////////////////////////////////////////////////////////////////

// @brief 内容を復元する．
CiLutTemplate*
CiLutTemplate::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  auto d = s.in().read_8();
  unique_ptr<CiLutTemplate> ptr;
  switch ( d ) {
  case 1:
    {
      ClibVarType var_type;
      s.in() >> var_type;
      vector<double> index_array;
      s.restore(index_array);
      return new CiLutTemplate1D{lib,
				 var_type, index_array};
    }
  case 2:
    {
      ClibVarType var_type1;
      s.in() >> var_type1;
      vector<double> index_array1;
      s.restore(index_array1);
      ClibVarType var_type2;
      s.in() >> var_type2;
      vector<double> index_array2;
      s.restore(index_array2);
      return new CiLutTemplate2D{lib,
				 var_type1, index_array1,
				 var_type2, index_array2};
    }
  case 3:
    {
      ClibVarType var_type1;
      s.in() >> var_type1;
      vector<double> index_array1;
      s.restore(index_array1);
      ClibVarType var_type2;
      s.in() >> var_type2;
      vector<double> index_array2;
      s.restore(index_array2);
      ClibVarType var_type3;
      s.in() >> var_type3;
      vector<double> index_array3;
      s.restore(index_array3);
      return new CiLutTemplate3D{lib,
				 var_type1, index_array1,
				 var_type2, index_array2,
				 var_type3, index_array3};
    }
  default:
    ASSERT_NOT_REACHED;
  }
  // ダミー
  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut
//////////////////////////////////////////////////////////////////////

// @brief 内容を復元する．
CiLut*
CiLut::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  auto d = s.in().read_8();
  CiLut* lut = nullptr;
  switch ( d ) {
  case 1: lut = new CiLut1D{lib}; break;
  case 2: lut = new CiLut2D{lib}; break;
  case 3: lut = new CiLut3D{lib}; break;
  default: ASSERT_NOT_REACHED; break;
  }
  lut->_restore(s);
  return lut;
}

// @brief 内容を読み込む．
void
CiLut::restore_common(
  Deserializer& s
)
{
  s.restore(mTemplate);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut1D
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLut1D::_restore(
  Deserializer& s
)
{
  restore_common(s);
  s.restore(mIndexArray);
  s.restore(mValueArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut2D
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLut2D::_restore(
  Deserializer& s
)
{
  restore_common(s);
  s.restore(mIndexArray[0]);
  s.restore(mIndexArray[1]);
  s.restore(mValueArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut3D
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiLut3D::_restore(
  Deserializer& s
)
{
  restore_common(s);
  s.restore(mIndexArray[0]);
  s.restore(mIndexArray[1]);
  s.restore(mIndexArray[2]);
  s.restore(mValueArray);
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatMgr
//////////////////////////////////////////////////////////////////////

// @brief データを読み込んでセットする．
bool
CiPatMgr::restore(
  Deserializer& s
)
{
  // ノードと枝の情報を読み込む．
  SizeType nn;
  s.restore(nn);
  set_node_num(nn);
  for ( auto i: Range(nn) ) {
    s.restore(mNodeTypeArray[i]);
    s.restore(mEdgeArray[i * 2]);
    s.restore(mEdgeArray[i * 2 + 1]);
  }

  // パタングラフの情報を読み込む．
  SizeType np;
  s.restore(np);
  set_pat_num(np);
  for ( auto id: Range(np) ) {
    mPatArray[id].restore(s);
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief バイナリファイルを読み込む．
void
CiPatGraph::restore(
  Deserializer& s
)
{
  s.restore(mRepClass);
  s.restore(mInputNum);
  s.restore(mEdgeList);
}

END_NAMESPACE_YM_CLIB
