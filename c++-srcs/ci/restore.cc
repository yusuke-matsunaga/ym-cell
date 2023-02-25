
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
#include "ci/CiBundle.h"
#include "ci/CiTiming.h"
#include "ci/CiLutTemplate.h"
#include "ci/CiLut.h"
#include "ci/CiPatMgr.h"
#include "ci/CiPatGraph.h"
#include "ym/ClibIOMap.h"
#include "ym/Range.h"


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

BEGIN_NONAMESPACE

ClibVarType
restore_1dim(
  BinDec& s,
  vector<double>& index_array
)
{
  ymuint8 tmp;
  s >> tmp;
  ClibVarType var_type = static_cast<ClibVarType>(tmp);
  ymuint8 n;
  s >> n;
  index_array.resize(n);
  for ( auto i: Range(n) ) {
    s >> index_array[i];
  }
  return var_type;
}

END_NONAMESPACE

// @brief LUT テンプレートを読み込む．
void
CiCellLibrary::restore_lut_template(
  BinDec& s
)
{
  // 要素数
  SizeType n;
  s >> n;

  for ( auto _: Range(n) ) {
    ShString name;
    ymuint8 d;
    s >> name
      >> d;
    ClibVarType var_type1;
    ClibVarType var_type2;
    ClibVarType var_type3;
    vector<double> index_array1;
    vector<double> index_array2;
    vector<double> index_array3;
    switch ( d ) {
    case 1:
      var_type1 = restore_1dim(s, index_array1);
      add_lut_template1(name,
			var_type1, index_array1);
      break;

    case 2:
      var_type1 = restore_1dim(s, index_array1);
      var_type2 = restore_1dim(s, index_array2);
      add_lut_template2(name,
			var_type1, index_array1,
			var_type2, index_array2);
      break;

    case 3:
      var_type1 = restore_1dim(s, index_array1);
      var_type2 = restore_1dim(s, index_array2);
      var_type3 = restore_1dim(s, index_array3);
      add_lut_template3(name,
			var_type1, index_array1,
			var_type2, index_array2,
			var_type3, index_array3);
      break;
    }
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
  mRefCellList.reserve(nc);
  for ( auto _: Range(nc) ) {
    ShString name;
    ClibArea area;
    s >> name
      >> area;

    SizeType cell_id{CLIB_NULLID};

    // セル本体の読み込み
    ymuint8 type;
    s >> type;
    switch ( type ) {
    case 0: // logic
      cell_id = add_logic_cell(name, area);
      break;

    case 1: // FF
      {
	ShString var1;
	ShString var2;
	Expr clocked_on;
	Expr clocked_on_also;
	Expr next_state;
	Expr clear;
	Expr preset;
	ymuint8 clear_preset_var1;
	ymuint8 clear_preset_var2;
	s >> var1 >> var2;
	clocked_on.restore(s);
	clocked_on_also.restore(s);
	next_state.restore(s);
	clear.restore(s);
	preset.restore(s);
	s >> clear_preset_var1
	  >> clear_preset_var2;
	cell_id = add_ff_cell(name, area,
			      var1, var2,
			      clocked_on, clocked_on_also, next_state,
			      clear, preset,
			      static_cast<ClibCPV>(clear_preset_var1),
			      static_cast<ClibCPV>(clear_preset_var2));
      }
      break;

    case 2: // latch
      {
	ShString var1;
	ShString var2;
	Expr enable;
	Expr enable_also;
	Expr data_in;
	Expr clear;
	Expr preset;
	ymuint8 clear_preset_var1;
	ymuint8 clear_preset_var2;
	s >> var1 >> var2;
	enable.restore(s);
	enable_also.restore(s);
	data_in.restore(s);
	clear.restore(s);
	preset.restore(s);
	s >> clear_preset_var1
	  >> clear_preset_var2;
	cell_id = add_latch_cell(name, area,
				 var1, var2,
				 enable, enable_also, data_in,
				 clear, preset,
				 static_cast<ClibCPV>(clear_preset_var1),
				 static_cast<ClibCPV>(clear_preset_var2));
      }
      break;

    case 3: // FSM
      {
#warning "TODO: 未完"
      }
      break;

    default:
      ASSERT_NOT_REACHED;
    }

    auto& cell = mCellList[cell_id];
    cell->restore(s);
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
  s >> mInputNum
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
// クラス CiPin
//////////////////////////////////////////////////////////////////////

// @brief 内容を読み込む．
void
CiPin::restore_common(
  BinDec& s ///< [in] 入力元のストリーム
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
CiTiming::restore_common(
  BinDec& s
)
{
  ymuint8 tmp;
  s >> mId
    >> tmp;
  mType = static_cast<ClibTimingType>(tmp);
  mCond.restore(s);
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
  restore_GP(s);
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
  restore_GP(s);
  s >> mRisePinResistance
    >> mFallPinResistance;
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
  restore_LUT(s);
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
  restore_LUT(s);
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
