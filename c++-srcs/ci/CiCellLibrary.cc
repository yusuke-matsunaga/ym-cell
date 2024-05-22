
/// @file CiCellLibrary.cc
/// @brief CiCellLibrary の実装ファイル
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
#include "ci/CiBusType.h"
#include "ci/CiPatGraph.h"
#include "ci/CiCell.h"
#include "ci/CiSeqInfo.h"
#include "cgmgr/CgMgr.h"
#include "cgmgr/CgSignature.h"
#include "cgmgr/PatMgr.h"
#include "cgmgr/PatNode.h"

#include "CiFFCell.h"
#include "CiLatchCell.h"
#include "CiFsmCell.h"
#include "CiPin_sub.h"
#include "CiTiming_sub.h"
#include "CiLutTemplate_sub.h"
#include "CiLut_sub.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellLibrary::CiCellLibrary() :
  mSimpleFFClass(CiSeqInfo::max_index()),
  mSimpleLatchClass(CiSeqInfo::max_index())
{
}

// @brief デストラクタ
CiCellLibrary::~CiCellLibrary()
{
}

// @brief 参照回数を増やす．
void
CiCellLibrary::inc_ref() const
{
  ++ mRefCount;
}

// @brief 参照回数を減らす．
void
CiCellLibrary::dec_ref() const
{
  -- mRefCount;
  if ( mRefCount == 0 ) {
    // 自殺する．
    delete this;
  }
}

#if 0
// @brief バスタイプの取得
const CiBusType*
CiCellLibrary::bus_type(
  const ShString& name
) const
{
  if ( mBusTypeDict.count(name) > 0 ) {
    return mBusTypeDict.at(name);
  }
  return nullptr;
}
#endif

// @brief 単純な型のFFクラスを返す．
const CiCellClass*
CiCellLibrary::simple_ff_class(
  bool master_slave,
  bool has_clear,
  bool has_preset,
  ClibCPV cpv1,
  ClibCPV cpv2
) const
{
  CiSeqInfo info{master_slave, has_clear, has_preset, cpv1, cpv2};
  return mSimpleFFClass[info.encode_val()];
}

// @brief 単純な型のラッチクラスを返す．
const CiCellClass*
CiCellLibrary::simple_latch_class(
  bool master_slave,
  bool has_clear,
  bool has_preset,
  ClibCPV cpv1,
  ClibCPV cpv2
) const
{
  CiSeqInfo info{master_slave, has_clear, has_preset, cpv1, cpv2};
  return mSimpleLatchClass[info.encode_val()];
}

// @brief 属性を設定する(浮動小数点型)
void
CiCellLibrary::set_attr(
  const string& attr_name,
  double value
)
{
  if ( attr_name == "em_temp_degradation_factor" ) {
  }
  else if ( attr_name == "nom_process" ) {
  }
  else if ( attr_name == "nom_temperature" ) {
  }
  else if ( attr_name == "nom_voltage" ) {
  }
  else if ( attr_name == "default_cell_leakage_power" ) {
  }
  else if ( attr_name == "default_fall_delay_intercept" ) {
  }
  else if ( attr_name == "default_fall_pin_resistance" ) {
  }
  else if ( attr_name == "default_fanout_load" ) {
  }
  else if ( attr_name == "default_inout_pin_cap" ) {
  }
  else if ( attr_name == "default_inout_pin_fall_res" ) {
  }
  else if ( attr_name == "default_inout_pin_rise_res" ) {
  }
  else if ( attr_name == "default_inout_pin_cap" ) {
  }
  else if ( attr_name == "default_intrinsic_fall" ) {
  }
  else if ( attr_name == "default_intrinsic_rise" ) {
  }
  else if ( attr_name == "default_leakage_power_density" ) {
  }
  else if ( attr_name == "default_max_capacitance" ) {
  }
  else if ( attr_name == "default_max_fanout" ) {
  }
  else if ( attr_name == "default_max_transition" ) {
  }
  else if ( attr_name == "default_max_utilization" ) {
  }
  else if ( attr_name == "default_min_porosity" ) {
  }
  else if ( attr_name == "default_output_pin_cap" ) {
  }
  else if ( attr_name == "default_output_pin_fall_res" ) {
  }
  else if ( attr_name == "default_output_pin_rise_res" ) {
  }
  else if ( attr_name == "default_rise_delay_intercept" ) {
  }
  else if ( attr_name == "default_slope_fall" ) {
  }
  else if ( attr_name == "default_slope_rise" ) {
  }
  else if ( attr_name == "default_wire_load_area" ) {
  }
  else if ( attr_name == "default_wire_load_capacitance" ) {
  }
  else if ( attr_name == "default_wire_load_resistance" ) {
  }
}

// @brief 属性を設定する(文字列型)．
void
CiCellLibrary::set_attr(
  const string& attr_name,
  const string& value
)
{
  if ( attr_name == "bus_naming_style" ) {
    mBusNamingStyle = value;
  }
  else if ( attr_name == "date" ) {
    mDate = value;
  }
  else if ( attr_name == "revision" ) {
    mRevision = value;
  }
  else if ( attr_name == "comment" ) {
    mComment = value;
  }
  else if ( attr_name == "time_unit" ) {
    mTimeUnit = value;
  }
  else if ( attr_name == "voltage_unit" ) {
    mVoltageUnit = value;
  }
  else if ( attr_name == "current_unit" ) {
    mCurrentUnit = value;
  }
  else if ( attr_name == "pulling_resistance_unit" ) {
    mPullingResistanceUnit = value;
  }
  else if ( attr_name == "leakage_power_unit" ) {
    mLeakagePowerUnit = value;
  }
}

// @brief 1次元の LUT のテンプレートを作る．
CiLutTemplate*
CiCellLibrary::add_lut_template1(
  ClibVarType var_type1,
  const vector<double>& index_list1
)
{
  auto tmpl = new CiLutTemplate1D{var_type1, index_list1};
  mLutTemplateList.push_back(unique_ptr<CiLutTemplate>(tmpl));
  //mRefLutTemplateList.push_back(tmpl);
  return tmpl;
}

// @brief 2次元の LUT のテンプレートを作る．
CiLutTemplate*
CiCellLibrary::add_lut_template2(
  ClibVarType var_type1,
  const vector<double>& index_list1,
  ClibVarType var_type2,
  const vector<double>& index_list2
)
{
  auto tmpl = new CiLutTemplate2D{var_type1, index_list1,
				  var_type2, index_list2};
  mLutTemplateList.push_back(unique_ptr<CiLutTemplate>(tmpl));
  //mRefLutTemplateList.push_back(tmpl);
  return tmpl;
}

// @brief 3次元の LUT のテンプレートを作る．
CiLutTemplate*
CiCellLibrary::add_lut_template3(
  ClibVarType var_type1,
  const vector<double>& index_list1,
  ClibVarType var_type2,
  const vector<double>& index_list2,
  ClibVarType var_type3,
  const vector<double>& index_list3
)
{
  auto tmpl = new CiLutTemplate3D{var_type1, index_list1,
				  var_type2, index_list2,
				  var_type3, index_list3};
  mLutTemplateList.push_back(unique_ptr<CiLutTemplate>(tmpl));
  //mRefLutTemplateList.push_back(tmpl);
  return tmpl;
}

// @brief セルクラスを作る．
CiCellClass*
CiCellLibrary::add_cell_class(
  const vector<ClibIOMap>& idmap_list
)
{
  auto cc = new CiCellClass{this, idmap_list};
  mClassList.push_back(unique_ptr<CiCellClass>(cc));
  //mRefClassList.push_back(cc);
  return cc;
}

// @brief セルグループを作る．
CiCellGroup*
CiCellLibrary::add_cell_group(
  const CiCellClass* rep_class,
  const ClibIOMap& iomap
)
{
  auto cg = new CiCellGroup{this, rep_class, iomap};
  mGroupList.push_back(unique_ptr<CiCellGroup>(cg));
  //mRefGroupList.push_back(cg);
  return cg;
}

// @brief 論理セルを追加する．
CiCell*
CiCellLibrary::add_logic_cell(
  const ShString& name,
  ClibArea area
)
{
  auto cell = new CiCell{this, name, area};
  return reg_cell(cell);
}

// @brief FFセルを生成する．
CiCell*
CiCellLibrary::add_ff_cell(
  const ShString& name,
  ClibArea area,
  const ShString& var1,
  const ShString& var2,
  const Expr& clock,
  const Expr& clock2,
  const Expr& next_state,
  const Expr& clear,
  const Expr& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  CiCell* cell{nullptr};
  if ( clock2.is_valid() ) {
    cell = new CiFF2Cell{this, name, area,
			 var1, var2,
			 clock, clock2, next_state,
			 clear, preset,
			 clear_preset_var1,
			 clear_preset_var2};
  }
  else {
    cell = new CiFFCell{this, name, area,
			var1, var2,
			clock, next_state,
			clear, preset,
			clear_preset_var1,
			clear_preset_var2};
  }
  return reg_cell(cell);
}

// @brief ラッチセルを追加する．
CiCell*
CiCellLibrary::add_latch_cell(
  const ShString& name,
  ClibArea area,
  const ShString& var1,
  const ShString& var2,
  const Expr& enable,
  const Expr& enable2,
  const Expr& data_in,
  const Expr& clear,
  const Expr& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  CiCell* cell{nullptr};
  if ( enable2.is_valid() ) {
    cell = new CiLatch2Cell{this, name, area,
			    var1, var2,
			    enable, enable2, data_in,
			    clear, preset,
			    clear_preset_var1,
			    clear_preset_var2};
  }
  else {
    cell = new CiLatchCell{this, name, area,
			   var1, var2,
			   enable, data_in,
			   clear, preset,
			   clear_preset_var1,
			   clear_preset_var2};
  }
  return reg_cell(cell);
}

// @brief FSMセルを追加する．
CiCell*
CiCellLibrary::add_fsm_cell(
  const ShString& name,
  ClibArea area
)
{
  auto cell = new CiFsmCell{this, name, area};
  return reg_cell(cell);
}

// @brief セルを登録する．
CiCell*
CiCellLibrary::reg_cell(
  CiCell* cell
)
{
  mCellList.push_back(unique_ptr<CiCell>{cell});
  //mRefCellList.push_back(cell);
  mCellDict.emplace(cell->name(), cell);
  return cell;
}

// @brief 入力ピンを追加する．
CiPin*
CiCellLibrary::add_input(
  CiCell* cell,
  const ShString& name,
  ClibCapacitance capacitance,
  ClibCapacitance rise_capacitance,
  ClibCapacitance fall_capacitance
)
{
  auto pin = cell->add_input(name,
			     capacitance,
			     rise_capacitance, fall_capacitance);
  reg_pin(cell, pin);
  return pin;
}

// @brief 出力ピンを追加する．
CiPin*
CiCellLibrary::add_output(
  CiCell* cell,
  const ShString& name,
  ClibCapacitance max_fanout,
  ClibCapacitance min_fanout,
  ClibCapacitance max_capacitance,
  ClibCapacitance min_capacitance,
  ClibTime max_transition,
  ClibTime min_transition,
  const Expr& function,
  const Expr& tristate
)
{
  auto pin = cell->add_output(name,
			      max_fanout, min_fanout,
			      max_capacitance, min_capacitance,
			      max_transition, min_transition,
			      function, tristate);
  reg_pin(cell, pin);
  return pin;
}

// @brief 入出力ピンを追加する．
CiPin*
CiCellLibrary::add_inout(
  CiCell* cell,
  const ShString& name,
  ClibCapacitance capacitance,
  ClibCapacitance rise_capacitance,
  ClibCapacitance fall_capacitance,
  ClibCapacitance max_fanout,
  ClibCapacitance min_fanout,
  ClibCapacitance max_capacitance,
  ClibCapacitance min_capacitance,
  ClibTime max_transition,
  ClibTime min_transition,
  const Expr& function,
  const Expr& tristate
)
{
  auto pin = cell->add_inout(name,
			     capacitance,
			     rise_capacitance, fall_capacitance,
			     max_fanout, min_fanout,
			     max_capacitance, min_capacitance,
			     max_transition, min_transition,
			     function, tristate);
  reg_pin(cell, pin);
  return pin;
}

// @brief 内部ピンを追加する．
CiPin*
CiCellLibrary::add_internal(
  CiCell* cell,
  const ShString& name
)
{
  auto pin = cell->add_internal(name);
  reg_pin(cell, pin);
  return pin;
}

// @brief バスを追加する．
CiBus*
CiCellLibrary::add_bus(
  CiCell* cell,
  const ShString& name,
  const CiBusType* bus_type,
  const vector<const CiPin*>& pin_list
)
{
  auto bus = cell->add_bus(name, bus_type, pin_list);
  reg_bus(cell, bus);
  return bus;
}

// @brief バンドルを追加する．
CiBundle*
CiCellLibrary::add_bundle(
  CiCell* cell,
  const ShString& name,
  const vector<const CiPin*>& pin_list
)
{
  auto bundle = cell->add_bundle(name, pin_list);
  reg_bundle(cell, bundle);
  return bundle;
}

#if 0
// @brief タイミング情報を作る(ジェネリック遅延モデル)．
CiTiming*
CiCellLibrary::add_timing_generic(
  ClibTimingType type,
  const Expr& cond,
  ClibTime intrinsic_rise,
  ClibTime intrinsic_fall,
  ClibTime slope_rise,
  ClibTime slope_fall,
  ClibResistance rise_resistance,
  ClibResistance fall_resistance
)
{
  auto timing = new CiTimingGeneric{this, type, cond,
				    intrinsic_rise,
				    intrinsic_fall,
				    slope_rise,
				    slope_fall,
				    rise_resistance,
				    fall_resistance};
  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return timing;
}

// @brief タイミング情報を作る(折れ線近似)．
CiTiming*
CiCellLibrary::add_timing_piecewise(
  ClibTimingType timing_type,
  const Expr& cond,
  ClibTime intrinsic_rise,
  ClibTime intrinsic_fall,
  ClibTime slope_rise,
  ClibTime slope_fall,
  ClibResistance rise_pin_resistance,
  ClibResistance fall_pin_resistance
)
{
  auto timing = new CiTimingPiecewise{this, timing_type, cond,
				      intrinsic_rise,
				      intrinsic_fall,
				      slope_rise,
				      slope_fall,
				      rise_pin_resistance,
				      fall_pin_resistance};
  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return timing;
}

// @brief タイミング情報を作る(非線形タイプ1)．
CiTiming*
CiCellLibrary::add_timing_lut1(
  ClibTimingType timing_type,
  const Expr& cond,
  const CiLut* cell_rise,
  const CiLut* cell_fall,
  const CiLut* rise_transition,
  const CiLut* fall_transition
)
{
  auto timing = new CiTimingLut1{this, timing_type, cond,
				 cell_rise,
				 cell_fall,
				 rise_transition,
				 fall_transition};

  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return timing;
}

// @brief タイミング情報を作る(非線形タイプ2)．
CiTiming*
CiCellLibrary::add_timing_lut2(
  ClibTimingType timing_type,
  const Expr& cond,
  const CiLut* rise_transition,
  const CiLut* fall_transition,
  const CiLut* rise_propagation,
  const CiLut* fall_propagation
)
{
  CiTiming* timing = new CiTimingLut2{this, timing_type, cond,
				      rise_transition,
				      fall_transition,
				      rise_propagation,
				      fall_propagation};

  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return timing;
}
#endif

#if 0
// @brief LUT を作る．
CiLut*
CiCellLibrary::add_lut(
  const CiLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array1,
  const vector<double>& index_array2,
  const vector<double>& index_array3
)
{
  SizeType d = lut_template->dimension();
  CiLut* lut{nullptr};
  switch ( d ) {
  case 1:
    lut = new CiLut1D{this, lut_template,
		      value_array,
		      make_index_array(index_array1, lut_template, 0)};
    break;

  case 2:
    lut = new CiLut2D{this, lut_template,
		      value_array,
		      make_index_array(index_array1, lut_template, 0),
		      make_index_array(index_array2, lut_template, 1)};
    break;

  case 3:
    lut = new CiLut3D{this, lut_template,
		      value_array,
		      make_index_array(index_array1, lut_template, 0),
		      make_index_array(index_array2, lut_template, 1),
		      make_index_array(index_array3, lut_template, 2)};
    break;
  }
  mLutList.push_back(unique_ptr<CiLut>(lut));
  return lut;
}
#endif

// @brief セルグループ/セルクラスの設定を行なう．
void
CiCellLibrary::compile()
{
  // シグネチャを用いてセルグループとセルクラスの設定を行う．
  CgMgr cgmgr{*this};
  for ( auto& cell: mCellList ) {
    // シグネチャを作る．
    auto sig = cell->make_signature(this);
    // sig に対応するグループを求める．
    auto group = cgmgr.find_group(sig);
    // セルを登録する．
    group->add_cell(cell.get());
  }

  // パタングラフを作る．
  cgmgr.gen_pat();

  // セルクラスの情報をコピーする．
  for ( SizeType index: { 0, 1, 2, 3 } ) {
    mLogicGroup[index] = cgmgr.logic_group(index);
  }
  for ( SizeType index = 0; index < CiSeqInfo::max_index(); ++ index ) {
    auto info = CiSeqInfo::decode_index(index);
    mSimpleFFClass[index] = cgmgr.ff_class(info);
  }
  for ( SizeType index = 0; index < CiSeqInfo::max_index(); ++ index ) {
    auto info = CiSeqInfo::decode_index(index);
    mSimpleLatchClass[info.encode_val()] = cgmgr.latch_class(info);
  }

  // パタングラフの情報をコピーする．
  SizeType nn = cgmgr.pat_node_num();
  mPatMgr.set_node_num(nn);
  for ( SizeType i = 0; i < nn; ++ i ) {
    const auto& node = cgmgr.pat_node(i);
    if ( node.is_input() ) {
      mPatMgr.set_node_info(i, node.input_id());
    }
    else {
      auto type = node.is_and() ? ClibPatType::And : ClibPatType::Xor;
      SizeType iid1 = node.fanin(0).id();
      bool iinv1 = node.fanin_inv(0);
      SizeType iid2 = node.fanin(1).id();
      bool iinv2 = node.fanin_inv(1);
      mPatMgr.set_node_info(i, type, iid1, iinv1, iid2, iinv2);
    }
  }
  SizeType np = cgmgr.pat_num();
  mPatMgr.set_pat_num(np);
  for ( SizeType i = 0; i < np; ++ i ) {
    const CiCellClass* rep_class;
    SizeType input_num;
    vector<SizeType> edge_list;
    cgmgr.get_pat_info(i, rep_class, input_num, edge_list);
    mPatMgr.set_pat_info(i, rep_class, input_num, edge_list);
  }
}

// @brief 内容をクリアする．
void
CiCellLibrary::clear()
{
  mName = {};
  mBusNamingStyle = {};
  mDate = {};
  mRevision = {};
  mComment = {};
  mTimeUnit = {};
  mVoltageUnit = {};
  mCurrentUnit = {};
  mPullingResistanceUnit = {};
  mCapacitiveLoadUnit = 0.0;
  mCapacitiveLoadUnitStr = {};
  mLeakagePowerUnit = {};
  mLutTemplateList.clear();
  //mRefLutTemplateList.clear();
  mCellList.clear();
  //mRefCellList.clear();
  mCellDict.clear();
  //mPinList.clear();
  mPinDict.clear();
  //mBusList.clear();
  mBusDict.clear();
  //mBundleList.clear();
  mBundleDict.clear();
  mGroupList.clear();
  //mRefGroupList.clear();
  mClassList.clear();
  //mRefClassList.clear();
  //mTimingList.clear();
  //mLutList.clear();
}

END_NAMESPACE_YM_CLIB
