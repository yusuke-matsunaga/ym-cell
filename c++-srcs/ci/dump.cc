
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

#if 0
#include "CiFFCell.h"
#include "CiLatchCell.h"
#include "CiFsmCell.h"
#include "CiPin_sub.h"
#include "CiTiming_sub.h"
#include "CiLutTemplate_sub.h"
#include "CiLut_sub.h"
#endif

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
  for ( auto& cclass: mClassList ) {
    cclass->serialize(s);
  }
  for ( auto& cgroup: mGroupList ) {
    cgroup->serialize(s);
  }
}


//////////////////////////////////////////////////////////////////////
// クラス Serializer
//////////////////////////////////////////////////////////////////////

// @brief 登録された要素の内容をダンプする．
void
Serializer::dump_obj()
{
  dump(mBusTypeList.obj_list().size());
  cout << "# of BusType: " << mBusTypeList.obj_list().size() << endl;
  for ( auto obj: mBusTypeList.obj_list() ) {
    obj->dump(*this);
  }
  dump(mLutTemplateList.obj_list().size());
  cout << "# of LutTemplate: " << mLutTemplateList.obj_list().size() << endl;
  for ( auto obj: mLutTemplateList.obj_list() ) {
    obj->dump(*this);
  }
  dump(mLutList.obj_list().size());
  cout << "# of Lut: " << mLutList.obj_list().size() << endl;
  for ( auto obj: mLutList.obj_list() ) {
    obj->dump(*this);
  }
  dump(mPinList.obj_list().size());
  cout << "# of Pin: " << mPinList.obj_list().size() << endl;
  for ( auto obj: mPinList.obj_list() ) {
    obj->dump(*this);
  }
  dump(mBusList.obj_list().size());
  cout << "# of Bus: " << mBusList.obj_list().size() << endl;
  for ( auto obj: mBusList.obj_list() ) {
    obj->dump(*this);
  }
  dump(mBundleList.obj_list().size());
  cout << "# of Bundle: " << mBundleList.obj_list().size() << endl;
  for ( auto obj: mBundleList.obj_list() ) {
    obj->dump(*this);
  }
  dump(mTimingList.obj_list().size());
  cout << "# of Timing: " << mTimingList.obj_list().size() << endl;
  for ( auto obj: mTimingList.obj_list() ) {
    obj->dump(*this);
  }
  dump(mCellClassList.obj_list().size());
  cout << "# of CellClass: " << mCellClassList.obj_list().size() << endl;
  for ( auto obj: mCellClassList.obj_list() ) {
    obj->dump(*this);
  }
  dump(mCellGroupList.obj_list().size());
  cout << "# of CellGroup: " << mCellGroupList.obj_list().size() << endl;
  for ( auto obj: mCellGroupList.obj_list() ) {
    obj->dump(*this);
  }
  dump(mCellList.obj_list().size());
  cout << "# of Cell: " << mCellList.obj_list().size() << endl;
  for ( auto obj: mCellList.obj_list() ) {
    obj->dump(*this);
  }
}

END_NAMESPACE_YM_CLIB
