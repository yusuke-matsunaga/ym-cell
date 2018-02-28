
/// @file CiCellLibrary_dump.cc
/// @brief CiCellLibrary の実装ファイル(dump()関係)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018 Yusuke Matsunaga
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


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

void
dump_lut(ODO& s,
	 const ClibLut* lut)
{
  if ( lut ) {
    lut->dump(s);
  }
  else {
    s.write_str(string());
  }
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
CiCellLibrary::dump(ODO& s) const
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
  int ntempl = lu_table_template_num();
  s << ntempl;
  for ( int i = 0; i < ntempl; ++ i ) {
    lu_table_template(i)->dump(s);
  }

  // セル数
  s << cell_list().num();
  for ( auto cell: cell_list() ) {
    // セルの内容をダンプ
    cell->dump(s);
  }

  // セルグループ情報のダンプ
  s << group_list().num();
  for ( int i = 0; i < mGroupList.num(); ++ i ) {
    const CiCellGroup* group = mGroupList._elem(i);
    group->dump(s);
  }

  // セルクラス情報のダンプ
  s << npn_class_list().num();
  for ( int i = 0; i < mClassList.num(); ++ i ) {
    const CiCellClass* cclass = mClassList._elem(i);
    cclass->dump(s);
  }

  // 組み込み型の情報のダンプ
  for ( int i = 0; i < 4; ++ i ) {
    int group_id = mLogicGroup[i]->id();
    s << group_id;
  }
  for ( int i = 0; i < 4; ++ i ) {
    int class_id = mFFClass[i]->id();
    s << class_id;
  }
  for ( int i = 0; i < 4; ++ i ) {
    int class_id = mLatchClass[i]->id();
    s << class_id;
  }

  // パタングラフの情報のダンプ
  mPatMgr.dump(s);
}


//////////////////////////////////////////////////////////////////////
// クラス CiCell
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
CiCell::dump(ODO& s) const
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

  // 入力ピンのダンプ
  int ni = input_num();
  s << ni;
  for ( int ipin = 0; ipin < ni; ++ ipin ) {
    input(ipin)->dump(s);
  }

  // 出力ピンのダンプ
  int no = output_num();
  s << no;
  for ( int opin = 0; opin < no; ++ opin ) {
    output(opin)->dump(s);
  }

  // 入出力ピンのダンプ
  int nio = inout_num();
  s << nio;
  for ( int iopin = 0; iopin < nio; ++ iopin ) {
    output(iopin)->dump(s);
  }

  // 内部ピンのダンプ
  int nit = internal_num();
  s << nit;
  for ( int itpin = 0; itpin < nit; ++ itpin ) {
    internal(itpin)->dump(s);
  }

  // バスのダンプ
  int nbus = bus_num();
  s << nbus;

  // バンドルのダンプ
  int nbundle = bundle_num();
  s << nbundle;

  // タイミング情報のダンプ
  const ClibTimingList& timing_list = this->timing_list();
  int nt = timing_list.num();
  s << nt;
  for ( auto timing: timing_list ) {
    timing->dump(s);
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
  for ( int ipos = 0; ipos < ni + nio; ++ ipos ) {
    for ( int opos = 0; opos < no + nio; ++ opos ) {
      const ClibTimingList& timing_list1 = this->timing_list(ipos, opos, kClibPosiUnate);
      s << timing_list1.num();
      for ( auto timing: timing_list1 ) {
	s << timing->id();
      }
      const ClibTimingList& timing_list2 = this->timing_list(ipos, opos, kClibNegaUnate);
      s << timing_list2.num();
      for ( auto timing: timing_list2 ) {
	s << timing->id();
      }
    }
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellPin
//////////////////////////////////////////////////////////////////////

// @brief dump 用の共通情報を出力する．
void
CiCellPin::dump_common(ODO& s) const
{
  s << name();
}


//////////////////////////////////////////////////////////////////////
// クラス CiInputPin
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
CiInputPin::dump(ODO& s) const
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
// @param[in] s 出力先のストリーム
void
CiOutputPin::dump(ODO& s) const
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
// @param[in] s 出力先のストリーム
void
CiInoutPin::dump(ODO& s) const
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
// @param[in] s 出力先のストリーム
void
CiInternalPin::dump(ODO& s) const
{
  dump_common(s);

  s << internal_id();
}


//////////////////////////////////////////////////////////////////////
// クラス CiTiming
//////////////////////////////////////////////////////////////////////

// @brief 共通な情報をダンプする．
// @param[in] s 出力先のストリーム
// @param[in] type_id 型の ID
void
CiTiming::dump_common(ODO& s,
		      ymuint8 type_id) const
{
  s << type_id
    << static_cast<ymuint8>(type())
    << timing_cond();
}


//////////////////////////////////////////////////////////////////////
// クラス CiTimingGeneric
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
CiTimingGeneric::dump(ODO& s) const
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
// @param[in] s 出力先のストリーム
void
CiTimingPiecewise::dump(ODO& s) const
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
// @param[in] s 出力先のストリーム
void
CiTimingLut1::dump(ODO& s) const
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
// @param[in] s 出力先のストリーム
void
CiTimingLut2::dump(ODO& s) const
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
// @param[in] s 出力先のストリーム
void
CiLut::dump(ODO& s) const
{
  s << template_name();
  int d = dimension();
  for ( int i = 0; i < d; ++ i ) {
    ymuint8 n = index_num(i);
    s << n;
    for ( int j = 0; j < n; ++ j ) {
      s << index(i, j);
    }
  }

  vector<ymuint32> pos_array(d);
  int n = 1;
  for ( int i = 0; i < d; ++ i ) {
    n *= index_num(i);
  }
  for ( int v = 0; v < n; ++ v ) {
    int v0 = v;
    for ( int j = 0; j < d; ++ j ) {
      int var = d - j - 1;
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
// @param[in] s 出力先のストリーム
void
CiLutTemplate::dump(ODO& s) const
{
  ymuint8 d = dimension();
  s << name()
    << d;
  for ( int i = 0; i < d; ++ i ) {
    s << static_cast<ymuint8>(variable_type(i));
    ymuint8 n = index_num(i);
    s << n;
    for ( int j = 0; j < n; ++ j ) {
      s << index(i, j);
    }
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
// @param[in] bos 出力先のストリーム
void
CiCellGroup::dump(ODO& bos) const
{
  bos << mMap
      << mPinInfo
      << mCellList.num();
  for ( auto cell: mCellList ) {
    bos << cell->id();
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
// @param[in] bos 出力先のストリーム
void
CiCellClass::dump(ODO& bos) const
{
  // 同位体変換情報のダンプ
  bos << mIdmapNum;
  for ( int i = 0; i < mIdmapNum; ++ i ) {
    bos << mIdmapList[i];
  }

  // グループ情報のダンプ
  bos << mGroupList.num();
  for ( auto group: mGroupList ) {
    bos << group->id();
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatMgr
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
// @param[in] bos 出力先のストリーム
void
CiPatMgr::dump(ODO& bos) const
{
  // パタングラフのノード情報のダンプ
  bos << mNodeNum;
  for ( int i = 0; i < mNodeNum; ++ i ) {
    bos << mNodeTypeArray[i]
	<< mEdgeArray[i * 2 + 0]
	<< mEdgeArray[i * 2 + 1];
  }

  // パタングラフの情報のダンプ
  bos << mPatNum;
  for ( int i = 0; i < mPatNum; ++ i ) {
    mPatArray[i].dump(bos);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief バイナリダンプを行う．
// @param[in] bos 出力先のストリーム
void
CiPatGraph::dump(ODO& bos) const
{
  bos << mRepId
      << mInputNum
      << mEdgeNum;
  for ( int i = 0; i < mEdgeNum; ++ i ) {
    bos << mEdgeList[i];
  }
}

END_NAMESPACE_YM_CLIB
