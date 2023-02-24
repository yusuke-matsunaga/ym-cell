
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

  // ピンの内容をダンプ
  bs << mPinList.size();
  for ( auto& pin: mPinList ) {
    pin->dump(bs);
  }

  // セルの内容をダンプ
  bs << cell_num();
  for ( auto& cell: mCellList ) {
    cell->dump(bs);
  }

  // セルクラス情報のダンプ
  bs << npn_class_num();
  for ( auto& cell_class: mClassList ) {
    cell_class->dump(bs);
  }

  // セルグループ情報のダンプ
  bs << cell_group_num();
  for ( auto& group: mGroupList ) {
    group->dump(bs);
  }

  // 組み込み型の情報のダンプ
  for ( auto g: mLogicGroup ) {
    bs << g;
  }
  bs << mSimpleFFClass.size();
  for ( auto c: mSimpleFFClass ) {
    bs << c;
  }
  bs << mSimpleLatchClass.size();
  for ( auto c: mSimpleLatchClass ) {
    bs << c;
  }

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
  s << cell_num();
  for ( auto id: mCellList ) {
    s << id;
  }
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
  s << cell_group_num();
  for ( auto id: cell_group_list() ) {
    s << id;
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

  // 入力ピンのダンプ
  s << input_num();
  for ( auto i: Range(input_num()) ) {
    s << input(i);
  }

  // 出力ピンのダンプ
  s << output_num();
  for ( auto i: Range(output_num()) ) {
    s << output(i);
  }

  // 入出力ピンのダンプ
  s << inout_num();
  for ( auto i: Range(inout_num()) ) {
    s << inout(i);
  }

  // 内部ピンのダンプ
  s << internal_num();
  for ( auto i: Range(internal_num()) ) {
    s << internal(i);
  }

  // バスのダンプ
  s << bus_num();
  for ( auto i: Range(bus_num()) ) {
    s << bus(i);
  }

  // バンドルのダンプ
  s << bundle_num();
  for ( auto i: Range(bundle_num()) ) {
    s << bundle(i);
  }

  // タイミング情報のダンプ
  s << timing_num();
  for ( auto i: Range(timing_num()) ) {
    s << timing(i);
  }

  // 個別の条件ごとのタイミング情報のダンプ
  for ( auto ipos: Range(input2_num()) ) {
    for ( auto opos: Range(output2_num()) ) {
      for ( auto sense: { ClibTimingSense::positive_unate, ClibTimingSense::negative_unate } ) {
	auto& timing_list1 = timing_list(ipos, opos, sense);
	s << timing_list1.size();
	for ( auto id: timing_list1 ) {
	  s << id;
	}
      }
    }
  }
}


//////////////////////////////////////////////////////////////////////
// クラス CiPin
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
  function().dump(s);
  tristate().dump(s);
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
  function().dump(s);
  tristate().dump(s);
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
// クラス CiLut1D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut1D::dump(
  BinEnc& s
) const
{
  s << lut_template();
  auto d = 1;
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
// クラス CiLut2D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut2D::dump(
  BinEnc& s
) const
{
  s << lut_template();
  auto d = 2;
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
// クラス CiLut3D
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiLut3D::dump(
  BinEnc& s
) const
{
  s << lut_template();
  auto d = 3;
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

END_NAMESPACE_YM_CLIB
