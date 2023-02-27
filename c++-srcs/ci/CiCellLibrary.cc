
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

// @brief バスタイプの取得
SizeType
CiCellLibrary::bus_type(
  const ShString& name
) const
{
#warning "TODO: 未完"
  return CLIB_NULLID;
}

// @brief 単純な型のFFクラスを返す．
SizeType
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
SizeType
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
SizeType
CiCellLibrary::add_lut_template1(
  const ShString& name,
  ClibVarType var_type1,
  const vector<double>& index_list1
)
{
  SizeType id = mLutTemplateList.size();
  auto tmpl = new CiLutTemplate1D{id, name,
                                  var_type1, index_list1};
  mLutTemplateList.push_back(unique_ptr<CiLutTemplate>(tmpl));
  mRefLutTemplateList.push_back(id);
  mLutDict.emplace(name, id);
  return id;
}

// @brief 2次元の LUT のテンプレートを作る．
SizeType
CiCellLibrary::add_lut_template2(
  const ShString& name,
  ClibVarType var_type1,
  const vector<double>& index_list1,
  ClibVarType var_type2,
  const vector<double>& index_list2
)
{
  SizeType id = mLutTemplateList.size();
  auto tmpl = new CiLutTemplate2D{id, name,
				  var_type1, index_list1,
				  var_type2, index_list2};
  mLutTemplateList.push_back(unique_ptr<CiLutTemplate>(tmpl));
  mRefLutTemplateList.push_back(id);
  mLutDict.emplace(name, id);
  return id;
}

// @brief 3次元の LUT のテンプレートを作る．
SizeType
CiCellLibrary::add_lut_template3(
  const ShString& name,
  ClibVarType var_type1,
  const vector<double>& index_list1,
  ClibVarType var_type2,
  const vector<double>& index_list2,
  ClibVarType var_type3,
  const vector<double>& index_list3
)
{
  SizeType id = mLutTemplateList.size();
  auto tmpl = new CiLutTemplate3D{id, name,
				  var_type1, index_list1,
				  var_type2, index_list2,
				  var_type3, index_list3};
  mLutTemplateList.push_back(unique_ptr<CiLutTemplate>(tmpl));
  mRefLutTemplateList.push_back(id);
  mLutDict.emplace(name, id);
  return id;
}

// @brief セルクラスを作る．
SizeType
CiCellLibrary::add_cell_class(
  const vector<ClibIOMap>& idmap_list
)
{
  SizeType id = mClassList.size();
  auto cc = new CiCellClass{idmap_list};
  mClassList.push_back(unique_ptr<CiCellClass>(cc));
  mRefClassList.push_back(id);
  return id;
}

// @brief セルグループを作る．
SizeType
CiCellLibrary::add_cell_group(
  SizeType rep_class,
  const ClibIOMap& iomap
)
{
  SizeType id = mGroupList.size();
  auto cg = new CiCellGroup{rep_class, iomap};
  mGroupList.push_back(unique_ptr<CiCellGroup>(cg));
  mRefGroupList.push_back(id);
  return id;
}

// @brief 論理セルを追加する．
SizeType
CiCellLibrary::add_logic_cell(
  const ShString& name,
  ClibArea area
)
{
  auto cell = new CiCell{name, area};
  return reg_cell(cell);
}

// @brief FFセルを生成する．
SizeType
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
    cell = new CiFF2Cell{name, area,
			 var1, var2,
			 clock, clock2, next_state,
			 clear, preset,
			 clear_preset_var1,
			 clear_preset_var2};
  }
  else {
    cell = new CiFFCell{name, area,
			var1, var2,
			clock, next_state,
			clear, preset,
			clear_preset_var1,
			clear_preset_var2};
  }
  return reg_cell(cell);
}

// @brief ラッチセルを追加する．
SizeType
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
    cell = new CiLatch2Cell{name, area,
			    var1, var2,
			    enable, enable2, data_in,
			    clear, preset,
			    clear_preset_var1,
			    clear_preset_var2};
  }
  else {
    cell = new CiLatchCell{name, area,
			   var1, var2,
			   enable, data_in,
			   clear, preset,
			   clear_preset_var1,
			   clear_preset_var2};
  }
  return reg_cell(cell);
}

// @brief セルを登録する．
SizeType
CiCellLibrary::reg_cell(
  CiCell* cell
)
{
  SizeType id = mCellList.size();
  cell->set_id(id);
  mCellList.push_back(unique_ptr<CiCell>{cell});
  mRefCellList.push_back(id);
  mCellDict.emplace(cell->name(), id);
  return id;
}

// @brief 入力ピンを追加する．
SizeType
CiCellLibrary::add_input(
  SizeType cell_id,
  const ShString& name,
  ClibCapacitance capacitance,
  ClibCapacitance rise_capacitance,
  ClibCapacitance fall_capacitance
)
{
  auto pin = new CiInputPin{name, capacitance,
                            rise_capacitance,
			    fall_capacitance};
  SizeType id = reg_pin(cell_id, pin);
  auto cell = mCellList[cell_id].get();
  cell->add_input(pin, id);
  return id;
}

// @brief 出力ピンを追加する．
SizeType
CiCellLibrary::add_output(
  SizeType cell_id,
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
  auto pin = new CiOutputPin{name,
                             max_fanout,
			     min_fanout,
			     max_capacitance,
			     min_capacitance,
			     max_transition,
			     min_transition,
			     function,
			     tristate};
  SizeType id = reg_pin(cell_id, pin);
  auto cell = mCellList[cell_id].get();
  cell->add_output(pin, id);
  return id;
}

// @brief 入出力ピンを追加する．
SizeType
CiCellLibrary::add_inout(
  SizeType cell_id,
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
  auto pin = new CiInoutPin{name,
                            capacitance, rise_capacitance, fall_capacitance,
			    max_fanout, min_fanout,
			    max_capacitance, min_capacitance,
			    max_transition, min_transition,
			    function, tristate};
  SizeType id = reg_pin(cell_id, pin);
  auto cell = mCellList[cell_id].get();
  cell->add_inout(pin, id);
  return id;
}

// @brief 内部ピンを追加する．
SizeType
CiCellLibrary::add_internal(
  SizeType cell_id,
  const ShString& name
)
{
  auto pin = new CiInternalPin{name};
  SizeType id = reg_pin(cell_id, pin);
  auto cell = mCellList[cell_id].get();
  cell->add_internal(pin, id);
  return id;
}

// @brief バスを追加する．
SizeType
CiCellLibrary::add_bus(
  SizeType cell_id,
  const ShString& name,
  SizeType bus_type,
  const vector<SizeType>& pin_list
)
{
  auto bus = new CiBus{name, bus_type, pin_list};
  SizeType id = reg_bus(cell_id, bus);
  auto cell = mCellList[cell_id].get();
  cell->add_bus(id);
  return id;
}

// @brief バンドルを追加する．
SizeType
CiCellLibrary::add_bundle(
  SizeType cell_id,
  const ShString& name,
  const vector<SizeType>& pin_list
)
{
  auto bundle = new CiBundle(name, pin_list);
  SizeType id = reg_bundle(cell_id, bundle);
  auto cell = mCellList[cell_id].get();
  cell->add_bundle(id);
  return id;
}

// @brief タイミング情報を作る(ジェネリック遅延モデル)．
SizeType
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
  SizeType tid = mTimingList.size();
  auto timing = new CiTimingGeneric(tid, type, cond,
				    intrinsic_rise,
				    intrinsic_fall,
				    slope_rise,
				    slope_fall,
				    rise_resistance,
				    fall_resistance);
  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return tid;
}

// @brief タイミング情報を作る(折れ線近似)．
SizeType
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
  SizeType tid = mTimingList.size();
  auto timing = new CiTimingPiecewise(tid, timing_type, cond,
				      intrinsic_rise,
				      intrinsic_fall,
				      slope_rise,
				      slope_fall,
				      rise_pin_resistance,
				      fall_pin_resistance);
  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return tid;
}

// @brief タイミング情報を作る(非線形タイプ1)．
SizeType
CiCellLibrary::add_timing_lut1(
  ClibTimingType timing_type,
  const Expr& cond,
  SizeType cell_rise,
  SizeType cell_fall,
  SizeType rise_transition,
  SizeType fall_transition
)
{
  SizeType tid = mTimingList.size();
  auto timing = new CiTimingLut1(tid, timing_type, cond,
				 cell_rise,
				 cell_fall,
				 rise_transition,
				 fall_transition);

  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return tid;
}

// @brief タイミング情報を作る(非線形タイプ2)．
SizeType
CiCellLibrary::add_timing_lut2(
  ClibTimingType timing_type,
  const Expr& cond,
  SizeType rise_transition,
  SizeType fall_transition,
  SizeType rise_propagation,
  SizeType fall_propagation
)
{
  SizeType tid = mTimingList.size();
  CiTiming* timing = new CiTimingLut2(tid, timing_type, cond,
				      rise_transition,
				      fall_transition,
				      rise_propagation,
				      fall_propagation);

  mTimingList.push_back(unique_ptr<CiTiming>{timing});
  return tid;
}

// @brief タイミング情報用のデータ構造を初期化する．
void
CiCellLibrary::init_cell_timing_map(
  SizeType cell_id
)
{
  mCellList[cell_id]->init_timing_map();
}

// @brief 1次元の LUT を作る．
CiLut*
CiCellLibrary::new_lut1(
  const CiLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array
)
{
  vector<double> tmp_array{index_array};
  if ( tmp_array.empty() ) {
    // index_array が空だった場合，テンプレートからコピーする．
    SizeType n = lut_template->index_num(0);
    tmp_array.resize(n);
    for ( auto i: Range(n) ) {
      tmp_array[i] = lut_template->index(0, i);
    }
  }

  return new CiLut1D{lut_template->id(), value_array, tmp_array};
}

// @brief 2次元の LUT を作る．
CiLut*
CiCellLibrary::new_lut2(
  const CiLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array1,
  const vector<double>& index_array2
)
{
  vector<double> tmp_array[2]{index_array1, index_array2};
  for ( int b = 0; b < 2; ++ b ) {
    if ( tmp_array[b].empty() ) {
      // index_array が空だった場合，テンプレートからコピーする．
      SizeType n1 = lut_template->index_num(b);
      tmp_array[b].resize(n1);
      for ( auto i: Range(n1) ) {
	tmp_array[b][i] = lut_template->index(b, i);
      }
    }
  }

  return new CiLut2D{lut_template->id(), value_array,
		     tmp_array[0], tmp_array[1]};
}

// @brief 3次元の LUT を作る．
CiLut*
CiCellLibrary::new_lut3(
  const CiLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array1,
  const vector<double>& index_array2,
  const vector<double>& index_array3
)
{
  vector<double> tmp_array[3]{index_array1, index_array2, index_array3};
  for ( int b = 0; b < 3; ++ b ) {
    if ( tmp_array[b].empty() ) {
      // index_array が空だった場合，テンプレートからコピーする．
      SizeType n1 = lut_template->index_num(b);
      tmp_array[b].resize(n1);
      for ( auto i: Range(n1) ) {
	tmp_array[b][i] = lut_template->index(b, i);
      }
    }
  }

  return new CiLut3D{lut_template->id(), value_array,
		     tmp_array[0], tmp_array[1], tmp_array[2]};
}

// @brief LUT を作る．
SizeType
CiCellLibrary::add_lut(
  const ShString& templ_name,
  const vector<double>& value_array,
  const vector<double>& index_array1,
  const vector<double>& index_array2,
  const vector<double>& index_array3
)
{
  if ( mLutDict.count(templ_name) == 0 ) {
    // テンプレートが存在しない．
#warning "TODO: エラーメッセージ"
    cerr << "lut_template(" << templ_name << ") not found." << endl;
    abort();
    return CLIB_NULLID;
  }
  auto templ_id = mLutDict.at(templ_name);
  auto lut_template = mLutTemplateList[templ_id].get();

  SizeType d = lut_template->dimension();
  CiLut* lut{nullptr};
  switch ( d ) {
  case 1:
    lut = new_lut1(lut_template,
		   value_array,
		   index_array1);
    break;

  case 2:
    lut = new_lut2(lut_template,
		   value_array,
		   index_array1,
		   index_array2);
    break;

  case 3:
    lut = new_lut3(lut_template,
		   value_array,
		   index_array1,
		   index_array2,
		   index_array3);
    break;
  }
  SizeType id = mLutList.size();
  mLutList.push_back(unique_ptr<CiLut>(lut));
  return id;
}

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
    auto gid = cgmgr.find_group(sig);
    // セルを登録する．
    auto group = _cell_group(gid);
    group->add_cell(cell->id());
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
    SizeType rep_id;
    SizeType input_num;
    vector<SizeType> edge_list;
    cgmgr.get_pat_info(i, rep_id, input_num, edge_list);
    mPatMgr.set_pat_info(i, rep_id, input_num, edge_list);
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
  mRefLutTemplateList.clear();
  mLutDict.clear();
  mCellList.clear();
  mRefCellList.clear();
  mCellDict.clear();
  mPinList.clear();
  mPinDict.clear();
  mBusList.clear();
  mBusDict.clear();
  mBundleList.clear();
  mBundleDict.clear();
  mGroupList.clear();
  mRefGroupList.clear();
  mClassList.clear();
  mRefClassList.clear();
  mTimingList.clear();
  mLutList.clear();
}

END_NAMESPACE_YM_CLIB
