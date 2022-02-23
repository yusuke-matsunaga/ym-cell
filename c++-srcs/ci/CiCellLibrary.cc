
/// @file CiCellLibrary.cc
/// @brief CiCellLibrary の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
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
#include "cgmgr/CgMgr.h"

#include "CiFFCell.h"
#include "CiLatchCell.h"

#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

using namespace nsLibcomp;

//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellLibrary::CiCellLibrary()
{
}

// @brief デストラクタ
CiCellLibrary::~CiCellLibrary()
{
}

// @brief 参照回数を増やす．
void
CiCellLibrary::inc_ref()
{
  ++ mRefCount;
}

// @brief 参照回数を減らす．
void
CiCellLibrary::dec_ref()
{
  -- mRefCount;
  if ( mRefCount == 0 ) {
    // 自殺する．
    delete this;
  }
}

// @brief バスタイプの取得
const ClibBusType&
CiCellLibrary::bus_type(
  const ShString& name
) const
{
#warning "TODO: 未完"
  return error_bus_type();
}

// @brief 単純な型のFFクラスを返す．
const ClibCellClass&
CiCellLibrary::simple_ff_class(
  bool master_slave,
  bool has_clear,
  bool has_preset,
  ClibCPV cpv1,
  ClibCPV cpv2
) const
{
  SizeType idx;
  SizeType sub_idx;
  CgMgr::encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2, idx, sub_idx);
  if ( idx < 6 ) {
    return *mSimpleFFClass[idx];
  }
  else {
    return *mCpvFFClass[sub_idx];
  }
}

// @brief 単純な型のラッチクラスを返す．
const ClibCellClass&
CiCellLibrary::simple_latch_class(
  bool master_slave,
  bool has_clear,
  bool has_preset,
  ClibCPV cpv1,
  ClibCPV cpv2
) const
{
  SizeType idx;
  SizeType sub_idx;
  CgMgr::encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2, idx, sub_idx);
  if ( idx < 6 ) {
    return *mSimpleLatchClass[idx];
  }
  else {
    return *mCpvLatchClass[sub_idx];
  }
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
  const ShString& name,
  ClibVarType var_type1,
  const vector<double>& index_list1
)
{
  SizeType id = mLutTemplateList.size();
  auto tmpl = new CiLutTemplate1D{id, name,
                                  var_type1, index_list1};
  mLutTemplateList.push_back(unique_ptr<CiLutTemplate>(tmpl));
  mLutHash.emplace(name, id);
  return tmpl;
}

// @brief 2次元の LUT のテンプレートを作る．
CiLutTemplate*
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
  mLutHash.emplace(name, id);
  return tmpl;
}

// @brief 3次元の LUT のテンプレートを作る．
CiLutTemplate*
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
  mLutHash.emplace(name, id);
  return tmpl;
}

// @brief セルクラスを作る．
CiCellClass*
CiCellLibrary::add_cell_class(
  const vector<ClibIOMap>& idmap_list
)
{
  SizeType id = mClassList.size();
  auto cc = new CiCellClass{id, idmap_list};
  mClassList.push_back(unique_ptr<CiCellClass>(cc));
  mRefClassList.push_back(cc);
  return cc;
}

// @brief セルグループを作る．
CiCellGroup*
CiCellLibrary::add_cell_group(
  const ClibCellClass* rep_class,
  const ClibIOMap& iomap
)
{
  SizeType id = mGroupList.size();
  auto cg = new CiCellGroup{id, rep_class, iomap};
  mGroupList.push_back(unique_ptr<CiCellGroup>(cg));
  mRefGroupList.push_back(cg);
  return cg;
}

// @brief 論理セルを追加する．
CiCell*
CiCellLibrary::add_logic_cell(
  const ShString& name,
  ClibArea area
)
{
  auto cell = new CiCell(this, name, area);
  reg_cell(cell);
  return cell;
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
    cell = new CiFF2Cell(this, name, area,
			 var1, var2,
			 clock, clock2, next_state,
			 clear, preset,
			 clear_preset_var1,
			 clear_preset_var2);
  }
  else {
    cell = new CiFFCell(this, name, area,
			var1, var2,
			clock,next_state,
			clear, preset,
			clear_preset_var1,
			clear_preset_var2);
  }
  reg_cell(cell);
  return cell;
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
    cell = new CiLatch2Cell(this, name, area,
			    var1, var2,
			    enable, enable2, data_in,
			    clear, preset,
			    clear_preset_var1,
			    clear_preset_var2);
  }
  else {
    cell = new CiLatchCell(this, name, area,
			   var1, var2,
			   enable, data_in,
			   clear, preset,
			   clear_preset_var1,
			   clear_preset_var2);
  }
  reg_cell(cell);
  return cell;
}

// @brief セルを登録する．
void
CiCellLibrary::reg_cell(
  CiCell* cell ///< [in] セル
)
{
  cell->set_id(mRefCellList.size());
  mCellList.push_back(unique_ptr<CiCell>{cell});
  mRefCellList.push_back(cell);
}

// @brief 1次元の LUT を作る．
CiLut*
CiCellLibrary::new_lut1(
  const ClibLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array
)
{
  auto lut = new CiLut1D(lut_template, value_array, index_array);
  return lut;
}

// @brief 2次元の LUT を作る．
// @param[in] lut_template テンプレート
// @param[in] value_array 値の配列
// @param[in] index_array1 インデックス値のリスト
// @param[in] index_array2 インデックス値のリスト
CiLut*
CiCellLibrary::new_lut2(
  const ClibLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array1,
  const vector<double>& index_array2
)
{
  auto lut = new CiLut2D(lut_template, value_array,
			 index_array1, index_array2);
  return lut;
}

// @brief 3次元の LUT を作る．
// @param[in] lut_template テンプレート
// @param[in] value_array 値の配列
// @param[in] index_array1 インデックス値のリスト
// @param[in] index_array2 インデックス値のリスト
// @param[in] index_array3 インデックス値のリスト
CiLut*
CiCellLibrary::new_lut3(
  const ClibLutTemplate* lut_template,
  const vector<double>& value_array,
  const vector<double>& index_array1,
  const vector<double>& index_array2,
  const vector<double>& index_array3
)
{
  auto lut = new CiLut3D(lut_template, value_array,
			 index_array1, index_array2, index_array3);
  return lut;
}

// @brief 3次元の LUT を作る．
CiLut*
CiCellLibrary::new_lut(
  const ShString& templ_name,
  const vector<double>& value_array,
  const vector<double>& index_array1,
  const vector<double>& index_array2,
  const vector<double>& index_array3
)
{
  if ( mLutHash.count(templ_name) == 0 ) {
    // テンプレートが存在しない．
#warning "TODO: エラーメッセージ"
    cerr << "lut_template(" << templ_name << ") not found." << endl;
    abort();
    return nullptr;
  }
  auto lut_template = mLutTemplateList[mLutHash.at(templ_name)].get();

  SizeType d = lut_template->dimension();
  CiLut* lut{nullptr};
  switch ( d ) {
  case 1:
    lut = new CiLut1D(lut_template, value_array,
		      index_array1);
    break;
  case 2:
    lut = new CiLut2D(lut_template, value_array,
		      index_array1, index_array2);
    break;
  case 3:
    lut = new CiLut3D(lut_template, value_array,
		      index_array1, index_array2, index_array3);
    break;
  }
  return lut;
}

// @brief デフォルトの BusType を返す．
const ClibBusType&
CiCellLibrary::error_bus_type()
{
  static CiBusType bus_type(ShString(), -1, -1);

  return bus_type;
}

// @brief デフォルトの LutTemplate を返す．
const ClibLutTemplate&
CiCellLibrary::error_lut_template()
{
  static CiLutTemplateBad lut_template;

  return lut_template;
}

// @brief デフォルトの Lut を返す．
const ClibLut&
CiCellLibrary::error_lut()
{
  static CiLutBad lut;

  return lut;
}

// @brief デフォルトの Cell を返す．
const ClibCell&
CiCellLibrary::error_cell()
{
  static CiCell cell;

  return cell;
}

// @brief デフォルトの CellGroup を返す．
const ClibCellGroup&
CiCellLibrary::error_cell_group()
{
  static CiCellGroup cell_group;

  return cell_group;
}

// @brief デフォルトの CellClass を返す．
const ClibCellClass&
CiCellLibrary::error_cell_class()
{
  static CiCellClass cell_class;

  return cell_class;
}

// @brief デフォルトの PatGraph を返す．
const ClibPatGraph&
CiCellLibrary::error_patgraph()
{
  static CiPatGraph pat_graph;

  return pat_graph;
}

// @brief セルグループ/セルクラスの設定を行なう．
void
CiCellLibrary::compile()
{
  CgMgr mgr{*this};

  for ( auto& cell: mCellList ) {
    auto g = mgr.reg_group(cell.get());
  }

  for ( int i: { 0, 1, 2, 3 } ) {
    mLogicGroup[i] = mRefGroupList[mgr.logic_group(i)];
  }

  for ( bool master_slave: { false, true } ) {
    for ( bool has_clear: { false, true } ) {
      for ( bool has_preset: { false, true } ) {
	if ( has_clear && has_preset ) {
	  for ( ClibCPV cpv1: { ClibCPV::L, ClibCPV::H, ClibCPV::N, ClibCPV::T, ClibCPV::X } ) {
	    for ( ClibCPV cpv2: { ClibCPV::L, ClibCPV::H, ClibCPV::N, ClibCPV::T, ClibCPV::X } ) {
	      SizeType idx;
	      SizeType sub_idx;
	      CgMgr::encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2,
				 idx, sub_idx);
	      SizeType id = mgr.ff_class(master_slave, has_clear, has_preset, cpv1, cpv2);
	      mCpvFFClass[sub_idx] = mRefClassList[id];
	    }
	  }
	}
	else {
	  ClibCPV cpv1{ClibCPV::X};
	  ClibCPV cpv2{ClibCPV::X};
	  SizeType idx;
	  SizeType sub_idx;
	  CgMgr::encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2,
			     idx, sub_idx);
	  SizeType id = mgr.ff_class(master_slave, has_clear, has_preset, cpv1, cpv2);
	  mSimpleFFClass[idx] = mRefClassList[id];
	}
      }
    }
  }

  for ( bool master_slave: { false, true } ) {
    for ( bool has_clear: { false, true } ) {
      for ( bool has_preset: { false, true } ) {
	if ( has_clear && has_preset ) {
	  for ( ClibCPV cpv1: { ClibCPV::L, ClibCPV::H, ClibCPV::N, ClibCPV::T, ClibCPV::X } ) {
	    for ( ClibCPV cpv2: { ClibCPV::L, ClibCPV::H, ClibCPV::N, ClibCPV::T, ClibCPV::X } ) {
	      SizeType idx;
	      SizeType sub_idx;
	      CgMgr::encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2,
				 idx, sub_idx);
	      SizeType id = mgr.latch_class(master_slave, has_clear, has_preset, cpv1, cpv2);
	      mCpvLatchClass[sub_idx] = mRefClassList[id];
	    }
	  }
	}
	else {
	  ClibCPV cpv1{ClibCPV::X};
	  ClibCPV cpv2{ClibCPV::X};
	  SizeType idx;
	  SizeType sub_idx;
	  CgMgr::encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2,
			     idx, sub_idx);
	  SizeType id = mgr.latch_class(master_slave, has_clear, has_preset, cpv1, cpv2);
	  mSimpleLatchClass[idx] = mRefClassList[id];
	}
      }
    }
  }

#if 0
  mPatMgr.copy(libcomp.pat_mgr());
#endif
}

// @brief ピンを登録する．
void
CiCellLibrary::reg_pin(
  const CiCell* cell,
  ShString name,
  SizeType id
)
{
  mPinHash.add(cell->id(), name, id);
}

// @brief ピン名からピン番号を取り出す．
SizeType
CiCellLibrary::get_pin_id(
  const CiCell* cell,
  ShString name
)
{
  return mPinHash.get(cell->id(), name);
}

// @brief バスを登録する．
void
CiCellLibrary::reg_bus(
  const CiCell* cell,
  ShString name,
  SizeType id
)
{
  mBusHash.add(cell->id(), name, id);
}

// @brief バス名からバス番号を取り出す．
SizeType
CiCellLibrary::get_bus_id(
  const CiCell* cell,
  ShString name
)
{
  return mBusHash.get(cell->id(), name);
}

// @brief バンドルを登録する．
void
CiCellLibrary::reg_bundle(
  const CiCell* cell,
  ShString name,
  SizeType id
)
{
  mBundleHash.add(cell->id(), name, id);
}

// @brief バンドル名からバンドル番号を取り出す．
SizeType
CiCellLibrary::get_bundle_id(
  const CiCell* cell,
  ShString name
)
{
  return mBundleHash.get(cell->id(), name);
}

END_NAMESPACE_YM_CLIB
