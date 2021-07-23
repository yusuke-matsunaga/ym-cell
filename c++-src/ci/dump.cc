
/// @file CiCellLibrary_dump.cc
/// @brief CiCellLibrary の実装ファイル(dump()関係)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellLibrary.h"
#include "ci/CiCellClass.h"
#include "ci/CiCellGroup.h"
#include "ci/CiCell.h"
#include "ci/CiLogicCell.h"
#include "ci/CiFFCell.h"
#include "ci/CiLatchCell.h"
#include "ci/CiFsmCell.h"
#include "ci/CiCellPin.h"
#include "ci/CiTiming.h"
#include "ci/CiLutTemplate.h"
#include "ci/CiLut.h"
#include "ci/CiPatMgr.h"
#include "ci/CiPatGraph.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

void
dump_lut(
  ostream& s,
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
  ostream& s
) const
{
  // 名前
  s << name();

  // テクノロジ
  s << static_cast<ymuint8>(technology());

  // 遅延モデル
  s << static_cast<ymuint8>(delay_model());

  // バス命名規則
  s << bus_naming_style();

  // 日付情報
  s << date();

  // リビジョン情報
  s << revision();

  // コメント
  s << comment();

  // 時間単位
  s << time_unit();

  // 電圧単位
  s << voltage_unit();

  // 電流単位
  s << current_unit();

  // 抵抗単位
  s << pulling_resistance_unit();

  // 容量単位
  s << capacitive_load_unit();

  // 容量単位の文字列
  s << capacitive_load_unit_str();

  // 電力単位
  s << leakage_power_unit();

  // 遅延テーブルのテンプレート
  s << lu_table_template_num();
  for ( auto id: Range(lu_table_template_num()) ) {
    lu_table_template(id).dump(s);
  }

  // セルの内容をダンプ
  s << cell_num();
  for ( auto id: Range(cell_num()) ) {
    cell(id).dump(s);
  }

  // セルグループ情報のダンプ
  s << cell_group_num();
  for ( auto id: Range(cell_group_num()) ) {
    cell_group(id).dump(s);
  }

  // セルクラス情報のダンプ
  s << npn_class_num();
  for ( auto id: Range(npn_class_num()) ) {
    npn_class(id).dump(s);
  }

  // 組み込み型の情報のダンプ
  for ( int i: { 0, 1, 2, 3 } ) {
    s << mLogicGroup[i]->id();
  }
  for ( int i: { 0, 1, 2, 3 } ) {
    s << mFFClass[i]->id();
  }
  for ( int i: { 0, 1, 2, 3 } ) {
    s << mLatchClass[i]->id();
  }

  // パタングラフの情報のダンプ
  mPatMgr.dump(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiCell::dump(
  ostream& s
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
  else if ( is_fsm() ) {
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

  // input_list(), output_list() は入出力ピンを含むので
  // そのままでは使えない．

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

  // バンドルのダンプ
  s << bundle_num();

  // タイミング情報のダンプ
  s << timing_num();
  for ( auto i: Range(timing_num()) ) {
    timing(i).dump(s);
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
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellPin
//////////////////////////////////////////////////////////////////////

// @brief dump 用の共通情報を出力する．
void
CiCellPin::dump_common(
  ostream& s
) const
{
  s << name();
}


//////////////////////////////////////////////////////////////////////
// クラス CiInputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiInputPin::dump(
  ostream& s
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
  ostream& s
) const
{
  dump_common(s);

  s << has_function()
    << function()
    << three_state()
    << max_fanout()
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
  ostream& s
) const
{
  dump_common(s);

  s << has_function()
    << function()
    << three_state()
    << capacitance()
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
  ostream& s
) const
{
  dump_common(s);

  s << internal_id();
}


//////////////////////////////////////////////////////////////////////
// クラス CiTiming
//////////////////////////////////////////////////////////////////////

// @brief 共通な情報をダンプする．
void
CiTiming::dump_common(
  ostream& s,
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
  ostream& s
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
  ostream& s
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
  ostream& s
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
  ostream& s
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
  ostream& s
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
  ostream& s
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
  ostream& bos
) const
{
  bos << mMap
      << mPinInfo
      << mCellList.size();
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
  ostream& bos
) const
{
  // 同位体変換情報のダンプ
  bos << mIdmapList.size();
  for ( auto& map: mIdmapList ) {
    bos << map;
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
  ostream& bos
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
  ostream& bos
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
