
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
    mBusTypeList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      s.restore(mBusTypeList[i]);
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
    s.restore(mLogicGroup[id]);
  }
  {
    SizeType n;
    s.restore(n);
    mSimpleFFClass.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      s.restore(mSimpleFFClass[i]);
    }
  }
  {
    SizeType n;
    s.restore(n);
    mSimpleLatchClass.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      s.restore(mSimpleLatchClass[i]);
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


//////////////////////////////////////////////////////////////////////
// クラス Deserializer
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
Deserializer::Deserializer(
  istream& s
) : mS{s}
{
  // 各要素の0番目は nullptr
  mBusTypeList.push_back(nullptr);
  mPinList.push_back(nullptr);
  mBusList.push_back(nullptr);
  mBundleList.push_back(nullptr);
  mTimingList.push_back(nullptr);
  mLutTemplateList.push_back(nullptr);
  mLutList.push_back(nullptr);
  mCellClassList.push_back(nullptr);
  mCellGroupList.push_back(nullptr);
  mCellList.push_back(nullptr);
}

// @brief 要素のデシリアライズを行う．
void
Deserializer::deserialize(
  CiCellLibrary* lib
)
{
  {
    SizeType n;
    restore(n);
    cout << "# of BusType: " << n << endl;
    mBusTypeList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mBusTypeList[i] = CiBusType::restore(*this);
    }
  }
  {
    SizeType n;
    restore(n);
    cout << "# of LutTemplate: " << n << endl;
    mLutTemplateList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mLutTemplateList[i] = CiLutTemplate::restore(*this);
    }
  }
  {
    SizeType n;
    restore(n);
    cout << "# of Lut: " << n << endl;
    mLutList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mLutList[i] = CiLut::restore(*this);
    }
  }
  {
    SizeType n;
    restore(n);
    cout << "# of Pin: " << n << endl;
    mPinList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mPinList[i] = CiPin::restore(*this);
    }
  }
  {
    SizeType n;
    restore(n);
    cout << "# of Bus: " << n << endl;
    mBusList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mBusList[i] = CiBus::restore(*this);
    }
  }
  {
    SizeType n;
    restore(n);
    cout << "# of Bundle: " << n << endl;
    mBundleList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mBundleList[i] = CiBundle::restore(*this);
    }
  }
  {
    SizeType n;
    restore(n);
    cout << "# of Timing: " << n << endl;
    mTimingList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mTimingList[i] = CiTiming::restore(*this);
    }
  }
  {
    SizeType n;
    restore(n);
    cout << "# of Cell: " << n << endl;
    mCellList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mCellList[i] = CiCell::restore(*this, lib);
    }
  }
  {
    SizeType n;
    restore(n);
    cout << "# of CellGroup: " << n << endl;
    mCellGroupList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mCellGroupList[i] = CiCellGroup::restore(*this, lib);
    }
  }
  {
    SizeType n;
    restore(n);
    cout << "# of CellClass: " << n << endl;
    mCellClassList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      mCellClassList[i] = CiCellClass::restore(*this, lib);
    }
  }
}

END_NAMESPACE_YM_CLIB
