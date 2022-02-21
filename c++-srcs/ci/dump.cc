
/// @file CiCellLibrary_dump.cc
/// @brief CiCellLibrary の実装ファイル(dump()関係)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018, 2021, 2022 Yusuke Matsunaga
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

void
dump_lut(
  BinEnc& s,
  const ClibLut& lut
)
{
  if ( lut.dimension() > 0 ) {
    lut.dump(s);
  }
  else {
    //s.write_str(string());
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
  for ( auto id: Range(lu_table_template_num()) ) {
    lu_table_template(id).dump(bs);
  }

  // セルの内容をダンプ
  bs << cell_num();
  for ( auto id: Range(cell_num()) ) {
    cell(id).dump(bs);
  }

  // セルグループ情報のダンプ
  bs << cell_group_num();
  for ( auto id: Range(cell_group_num()) ) {
    cell_group(id).dump(bs);
  }

  // セルクラス情報のダンプ
  bs << npn_class_num();
  for ( auto id: Range(npn_class_num()) ) {
    npn_class(id).dump(bs);
  }

  // 組み込み型の情報のダンプ
  for ( int i: { 0, 1, 2, 3 } ) {
    bs << mLogicGroup[i]->id();
  }
  for ( int i: { 0, 1, 2, 3 } ) {
    bs << mFFClass[i]->id();
  }
  for ( int i: { 0, 1, 2, 3 } ) {
    bs << mLatchClass[i]->id();
  }

  // パタングラフの情報のダンプ
  mPatMgr.dump(bs);
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
  ymuint8 tid = 0;
  if ( is_logic() ) {
    tid = 0;
  }
  else if ( is_ff() ) {
    tid = 1;
  }
  else if ( is_latch() ) {
    tid = 2;
  }
  else if ( type() == ClibCellType::FSM ) {
    tid = 3;
  }
  else {
    // 無視？
    ASSERT_NOT_REACHED;
  }

  // セルの共通な情報のダンプ
  s << tid
    << name()
    << area();

  // 入力ピンのダンプ
  s << input_num();
  for ( auto i: Range(input_num()) ) {
    input(i).dump(s);
  }

  // 出力ピンのダンプ
  s << output_num();
  for ( auto i: Range(output_num()) ) {
    output(i).dump(s);
  }

  // 入出力ピンのダンプ
  s << inout_num();
  for ( auto i: Range(inout_num()) ) {
    inout(i).dump(s);
  }

  // 内部ピンのダンプ
  s << internal_num();
  for ( auto i: Range(internal_num()) ) {
    internal(i).dump(s);
  }

  // バスのダンプ
  s << bus_num();
  for ( auto i: Range(bus_num()) ) {
    bus(i).dump(s);
  }

  // バンドルのダンプ
  s << bundle_num();
  for ( auto i: Range(bundle_num()) ) {
    bundle(i).dump(s);
  }

  // タイミング情報のダンプ
  s << timing_num();
  for ( auto i: Range(timing_num()) ) {
    timing(i).dump(s);
  }

  // 個別の条件ごとのタイミング情報のダンプ
  for ( auto ipos: Range(input_num2()) ) {
    for ( auto opos: Range(output_num2()) ) {
      for ( auto sense: { ClibTimingSense::positive_unate, ClibTimingSense::negative_unate } ) {
	auto& timing_id_list1 = timing_id_list(ipos, opos, sense);
	s << timing_id_list1.size();
	for ( auto id: timing_id_list1 ) {
	  s << id;
	}
      }
    }
  }

  // セルの付加的な情報のダンプ
  if ( is_ff() ) {
    s << next_state_expr()
      << clock_expr()
      << clock2_expr()
      << clear_expr()
      << preset_expr()
      << static_cast<ymuint8>(clear_preset_var1())
      << static_cast<ymuint8>(clear_preset_var2());
  }
  else if ( is_latch() ) {
    s << data_in_expr()
      << enable_expr()
      << enable2_expr()
      << clear_expr()
      << preset_expr()
      << static_cast<ymuint8>(clear_preset_var1())
      << static_cast<ymuint8>(clear_preset_var2());
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellPin
//////////////////////////////////////////////////////////////////////

// @brief dump 用の共通情報を出力する．
void
CiPin::dump_common(
  BinEnc& s
) const
{
  s << _name();
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
  dump_common(s);

  s << capacitance()
    << rise_capacitance()
    << fall_capacitance();
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
  dump_common(s);

  s << max_fanout()
    << min_fanout()
    << max_capacitance()
    << min_capacitance()
    << max_transition()
    << min_transition();
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
  dump_common(s);

  s << capacitance()
    << rise_capacitance()
    << fall_capacitance()
    << max_fanout()
    << min_fanout()
    << max_capacitance()
    << min_capacitance()
    << max_transition()
    << min_transition();
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
  dump_common(s);

  s << internal_id();
}


//////////////////////////////////////////////////////////////////////
// クラス CiBus
//////////////////////////////////////////////////////////////////////

/// @brief 内容をバイナリダンプする．
void
CiBus::dump(
  BinEnc& s ///< [in] 出力先のストリーム
) const
{
  s << mName;
  s << pin_num();
  for ( auto pin: mPinList ) {
    s << pin->name();
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiBundle
//////////////////////////////////////////////////////////////////////

/// @brief 内容をバイナリダンプする．
void
CiBundle::dump(
  BinEnc& s ///< [in] 出力先のストリーム
) const
{
  s << mName;
  s << pin_num();
  for ( auto pin: mPinList ) {
    s << pin->name();
  }
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

  dump_lut(s, cell_rise());
  dump_lut(s, cell_fall());
  dump_lut(s, rise_transition());
  dump_lut(s, fall_transition());
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

  dump_lut(s, rise_transition());
  dump_lut(s, fall_transition());
  dump_lut(s, rise_propagation());
  dump_lut(s, fall_propagation());
}


//////////////////////////////////////////////////////////////////////
// クラス CiLut
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut::dump(
  BinEnc& s
) const
{
  s << lut_template().id();
  auto d = dimension();
  for ( auto i: Range(d) ) {
    ymuint8 n = index_num(i);
    s << n;
    for ( auto j: Range(n) ) {
      s << index(i, j);
    }
  }

  vector<SizeType> pos_array(d);
  auto n = 1;
  for ( auto i: Range(d) ) {
    n *= index_num(i);
  }
  for ( auto v: Range(n) ) {
    auto v0 = v;
    for ( int j: Range(d) ) {
      auto var = d - j - 1;
      pos_array[var] = v0 % index_num(var);
      v0 /= index_num(var);
    }
    double val = grid_value(pos_array);
    s << val;
  }
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
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
CiCellGroup::dump(
  BinEnc& bos
) const
{
  mIomap.dump(bos);
  bos << mCellList.size();
  for ( auto& cell: mCellList ) {
    bos << cell->id();
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
CiCellClass::dump(
  BinEnc& bos
) const
{
  // 同位体変換情報のダンプ
  bos << mIdmapList.size();
  for ( auto& map: mIdmapList ) {
    map.dump(bos);
  }

  // グループ情報のダンプ
  bos << mGroupList.size();
  for ( auto& group: mGroupList ) {
    bos << group->id();
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatMgr
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
CiPatMgr::dump(
  BinEnc& bos
) const
{
  // パタングラフのノード情報のダンプ
  bos << node_num();
  for ( auto i: Range(node_num()) ) {
    bos << mNodeTypeArray[i]
	<< mEdgeArray[i * 2 + 0]
	<< mEdgeArray[i * 2 + 1];
  }

  // パタングラフの情報のダンプ
  bos << pat_num();
  for ( auto& pat: mPatArray ) {
    pat.dump(bos);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
void
CiPatGraph::dump(
  BinEnc& bos
) const
{
  bos << mRepId
      << mInputNum
      << mEdgeList.size();
  for ( auto e: mEdgeList ) {
    bos << e;
  }
}

END_NAMESPACE_YM_CLIB
