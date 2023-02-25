
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
#include "ci/CiLutTemplate.h"
#include "ci/CiLut.h"
#include "ci/CiTiming.h"
#include "ym/ClibIOMap.h"
#include "ym/Range.h"


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
  s << vec.size();
  for ( auto v: vec ) {
    s << v;
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
  s << vec.size();
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
  bs << static_cast<ymuint8>(technology());

  // 遅延モデル
  bs << static_cast<ymuint8>(delay_model());

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

  // 遅延テーブルのテンプレート
  bs << lu_table_template_num();
  for ( auto& lut_templ: mLutTemplateList ) {
    lut_templ->dump(bs);
  }

  // セルの内容をダンプ
  bs << cell_num();
  for ( auto& cell: mCellList ) {
    cell->dump(bs);
  }

  // ピンの内容をダンプ
  bs << mPinList.size();
  for ( auto& pin: mPinList ) {
    pin->dump(bs);
  }

  // バスの内容をダンプ
  bs << mBusList.size();
  for ( auto& bus: mBusList ) {
    bus->dump(bs);
  }

  // バンドルの内容をダンプ
  bs << mBundleList.size();
  for ( auto& bundle: mBundleList ) {
    bundle->dump(bs);
  }

  // タイミング情報の内容をダンプ
  bs << mTimingList.size();
  for ( auto& timing: mTimingList ) {
    timing->dump(bs);
  }

  // LUTの内容をダンプ
  bs << mLutList.size();
  for ( auto& lut: mLutList ) {
    lut->dump(bs);
  }

  // セルグループ情報のダンプ
  bs << mGroupList.size();
  for ( auto& group: mGroupList ) {
    group->dump(bs);
  }

  // セルクラス情報のダンプ
  bs << mClassList.size();
  for ( auto& cell_class: mClassList ) {
    cell_class->dump(bs);
  }

  // 組み込み型の情報のダンプ
  for ( auto g: mLogicGroup ) {
    bs << g;
  }
  dump_vector(bs, mSimpleFFClass);
  dump_vector(bs, mSimpleLatchClass);

  // パタングラフの情報のダンプ
  mPatMgr.dump(bs);
}


//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplate
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLutTemplate::dump(
  BinEnc& s
) const
{
  ymuint8 d = dimension();
  s << name()
    << d;
  for ( auto i: Range(d) ) {
    s << static_cast<ymuint8>(variable_type(i));
    ymuint8 n = index_num(i);
    s << n;
    for ( int j: Range(n) ) {
      s << index(i, j);
    }
  }
}



//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiCell::dump(
  BinEnc& s
) const
{
  // セルの共通な情報のダンプ
  s << name()
    << area();

  // セルの種類ごとの属性のダンプ
  if ( is_logic() ) {
    s << static_cast<ymuint8>(0);
  }
  else if ( is_ff() ) {
    s << static_cast<ymuint8>(1)
      << qvar1()
      << qvar2()
      << clock_expr()
      << clock2_expr()
      << next_state_expr()
      << clear_expr()
      << preset_expr()
      << static_cast<ymuint8>(clear_preset_var1())
      << static_cast<ymuint8>(clear_preset_var2());
  }
  else if ( is_latch() ) {
    s << static_cast<ymuint8>(2)
      << qvar1()
      << qvar2()
      << enable_expr()
      << enable2_expr()
      << data_in_expr()
      << clear_expr()
      << preset_expr()
      << static_cast<ymuint8>(clear_preset_var1())
      << static_cast<ymuint8>(clear_preset_var2());
  }
  else if ( type() == ClibCellType::FSM ) {
    s << static_cast<ymuint8>(3);
  }
  else {
    // 無視？
    ASSERT_NOT_REACHED;
  }

  s << mInputNum
    << mOutputNum
    << mInoutNum;

  // ピンリスト
  dump_vector(s, mPinList);

  // 入力ピンリスト
  dump_vector(s, mInputList);

  // 出力ピンリスト
  dump_vector(s, mOutputList);

  // 内部ピンリスト
  dump_vector(s, mInternalList);

  // バス番号のリスト
  dump_vector(s, mBusList);

  // バンドル番号のリスト
  dump_vector(s, mBundleList);

  // タイミング番号のリスト
  dump_vector(s, mTimingList);

  // タイミングマップ
  s << mTimingMap.size();
  for ( auto& vec: mTimingMap ) {
    dump_vector(s, vec);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiPin
//////////////////////////////////////////////////////////////////////

// @brief dump 用の共通情報を出力する．
void
CiPin::dump_common(
  BinEnc& s,
  ymuint8 sig
) const
{
  s << sig
    << mName
    << mPinId;
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
  s << mInputId
    << mCapacitance
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
  ymuint8 sig
) const
{
  dump_common(s, sig);
  s << mOutputId
    << mFanoutLoad
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
  s << mInputId
    << mCapacitance
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

  s << internal_id();
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
  s << mName
    << mBusType;
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
  ymuint8 type_id
) const
{
  s << type_id
    << mId
    << static_cast<ymuint8>(type())
    << timing_cond();
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

  s << cell_rise()
    << cell_fall()
    << rise_transition()
    << fall_transition();
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

  s << rise_transition()
    << fall_transition()
    << rise_propagation()
    << fall_propagation();
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut
//////////////////////////////////////////////////////////////////////

// @brief 実際のダンプを行う関数
void
CiLut::dump_common(
  BinEnc& s,
  ymuint8 d
) const
{
  s << d
    << mTemplate;
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
  s << mRepClass;
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
  s << idmap_num();
  for ( auto& map: idmap_list() ) {
    map.dump(s);
  }
  // グループ情報のダンプ
  dump_vector(s, mGroupList);
}

END_NAMESPACE_YM_CLIB
