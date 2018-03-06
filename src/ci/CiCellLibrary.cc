﻿
/// @file CiCellLibrary.cc
/// @brief CiCellLibrary の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
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

#include "LibComp.h"
#include "LcClass.h"
#include "LcGroup.h"


BEGIN_NAMESPACE_YM_CLIB

using namespace nsLibcomp;

//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellLibrary::CiCellLibrary() :
  mRefCount(0),
  mAlloc(4096),
  mPatMgr(mAlloc)
{
  mTechnology = kClibTechCmos;
  mDelayModel = kClibDelayGenericCmos;
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

// @brief 名前の取得
string
CiCellLibrary::name() const
{
  return mName;
}

// @brief テクノロジの取得
ClibTechnology
CiCellLibrary::technology() const
{
  return mTechnology;
}

// @brief 遅延モデルの取得
// 返り値は
// - kClibDelayGenericCmos
// - kClibDelayTableLookup
// - kClibDelayPiecewiseCmos
// - kClibDelayCmos2
// - kClibDelayDcm
// のいずれか
ClibDelayModel
CiCellLibrary::delay_model() const
{
  return mDelayModel;
}

// @brief バス命名規則の取得
string
CiCellLibrary::bus_naming_style() const
{
  return mBusNamingStyle;
}

// @brief 日付情報の取得
string
CiCellLibrary::date() const
{
  return mDate;
}

/// @brief リビジョン情報の取得
string
CiCellLibrary::revision() const
{
  return mRevision;
}

// @brief コメント情報の取得
string
CiCellLibrary::comment() const
{
  return mComment;
}

// @brief 時間単位の取得
string
CiCellLibrary::time_unit() const
{
  return mTimeUnit;
}

// @brief 電圧単位の取得
string
CiCellLibrary::voltage_unit() const
{
  return mVoltageUnit;
}

// @brief 電流単位の取得
string
CiCellLibrary::current_unit() const
{
  return mCurrentUnit;
}

// @brief 抵抗単位の取得
string
CiCellLibrary::pulling_resistance_unit() const
{
  return mPullingResistanceUnit;
}

// @brief 容量単位の取得
// @note なぜかここだけインターフェイスが異なる．
double
CiCellLibrary::capacitive_load_unit() const
{
  return mCapacitiveLoadUnit;
}

// @brief 容量単位文字列の取得
// @note なぜかここだけインターフェイスが異なる．
string
CiCellLibrary::capacitive_load_unit_str() const
{
  return mCapacitiveLoadUnitStr;
}

// @brief 電力単位の取得
string
CiCellLibrary::leakage_power_unit() const
{
  return mLeakagePowerUnit;
}

// @brief 遅延テーブルのテンプレートのリストの取得
const ClibLutTemplateList&
CiCellLibrary::lu_table_template_list() const
{
  return mLutTemplateList;
}

// @brief ルックアップテーブルのテンプレートの取得
// @param[in] name テンプレート名
// @note なければ nullptr を返す．
const ClibLutTemplate*
CiCellLibrary::lu_table_template(const char* name) const
{
  return lu_table_template(ShString(name));
}

// @brief ルックアップテーブルのテンプレートの取得
// @param[in] name テンプレート名
//
// なければ nullptr を返す．
const ClibLutTemplate*
CiCellLibrary::lu_table_template(const string& name) const
{
  return lu_table_template(ShString(name));
}

// @brief ルックアップテーブルのテンプレートの取得
// @param[in] name テンプレート名
//
// なければ nullptr を返す．
const ClibLutTemplate*
CiCellLibrary::lu_table_template(const ShString& name) const
{
  return mLutHash.get(name);
}

// @brief バスタイプの取得
// @param[in] name バスタイプ名
// @note なければ nullptr を返す．
const ClibBusType*
CiCellLibrary::bus_type(const char* name) const
{
  return bus_type(ShString(name));
}

/// @brief バスタイプの取得
/// @param[in] name バスタイプ名
///
/// なければ nullptr を返す．
const ClibBusType*
CiCellLibrary::bus_type(const string& name) const
{
  return bus_type(ShString(name));
}

// @brief バスタイプの取得
// @param[in] name バスタイプ名
//
// なければ nullptr を返す．
const ClibBusType*
CiCellLibrary::bus_type(const ShString& name) const
{
  // 未完
  return nullptr;
}

// @brief セルのリストの取得
const ClibCellList&
CiCellLibrary::cell_list() const
{
  return mCellList;
}

// @brief 名前からのセルの取得
const ClibCell*
CiCellLibrary::cell(const char* name) const
{
  return cell(ShString(name));
}

// @brief 名前からのセルの取得
const ClibCell*
CiCellLibrary::cell(const string& name) const
{
  return cell(ShString(name));
}

// @brief 名前からのセルの取得
const ClibCell*
CiCellLibrary::cell(const ShString& name) const
{
  return mCellHash.get(name);
}

// @brief セルグループのリストを返す．
const ClibCellGroupList&
CiCellLibrary::group_list() const
{
  return mGroupList;
}

// @brief NPN同値クラスのリストを返す．
const ClibCellClassList&
CiCellLibrary::npn_class_list() const
{
  return mClassList;
}

// @brief 定数0セルのグループを返す．
const ClibCellGroup*
CiCellLibrary::const0_func() const
{
  // 決め打ち
  return mLogicGroup[0];
}

// @brief 定数1セルのグループを返す．
const ClibCellGroup*
CiCellLibrary::const1_func() const
{
  // 決め打ち
  return mLogicGroup[1];
}

// @brief バッファセルのグループを返す．
const ClibCellGroup*
CiCellLibrary::buf_func() const
{
  // 決め打ち
  return mLogicGroup[2];
}

// @brief インバータセルのグループを返す．
const ClibCellGroup*
CiCellLibrary::inv_func() const
{
  // 決め打ち
  return mLogicGroup[3];
}

// @brief 単純な型のFFクラスを返す．
// @param[in] has_clear クリア端子を持つとき true にする．
// @param[in] has_preset プリセット端子を持つとき true にする．
// @note 該当するセルがないときでも空のセルクラスが返される．
const ClibCellClass*
CiCellLibrary::simple_ff_class(bool has_clear,
			       bool has_preset) const
{
  int pos = 0;
  if ( has_clear ) {
    pos += 1;
  }
  if ( has_preset ) {
    pos += 2;
  }
  return mFFClass[pos];
}

// @brief 単純な型のラッチクラスを返す．
// @param[in] has_clear クリア端子を持つとき true にする．
// @param[in] has_preset プリセット端子を持つとき true にする．
// @note 該当するセルがないときでも空のセルクラスが返される．
const ClibCellClass*
CiCellLibrary::simple_latch_class(bool has_clear,
				  bool has_preset) const
{
  int pos = 0;
  if ( has_clear ) {
    pos += 1;
  }
  if ( has_preset ) {
    pos += 2;
  }
  return mLatchClass[pos];
}

// @brief 総パタン数を返す．
int
CiCellLibrary::pg_pat_num() const
{
  return mPatMgr.pat_num();
}

// @brief パタンを返す．
// @param[in] id パタン番号 ( 0 <= id < pg_pat_num() )
const ClibPatGraph&
CiCellLibrary::pg_pat(int id) const
{
  return mPatMgr.pat(id);
}

// @brief パタンの最大の入力数を得る．
int
CiCellLibrary::pg_max_input() const
{
  return mPatMgr.max_input();
}

// @brief 総ノード数を返す．
int
CiCellLibrary::pg_node_num() const
{
  return mPatMgr.node_num();
}

// @brief ノードの種類を返す．
// @param[in] id ノード番号 ( 0 <= id < pg_node_num() )
ClibPatType
CiCellLibrary::pg_node_type(int id) const
{
  return mPatMgr.node_type(id);
}

// @brief ノードが入力ノードの時に入力番号を返す．
// @param[in] id ノード番号 ( 0 <= id < pg_node_num() )
// @note 入力ノードでない場合の返り値は不定
int
CiCellLibrary::pg_input_id(int id) const
{
  return mPatMgr.input_id(id);
}

// @brief 入力のノード番号を返す．
// @param[in] input_id 入力番号 ( 0 <= input_id < pg_input_num() )
// @return input_id の入力に対応するノードのノード番号
int
CiCellLibrary::pg_input_node(int input_id) const
{
  return mPatMgr.input_node(input_id);
}

// @brief 総枝数を返す．
int
CiCellLibrary::pg_edge_num() const
{
  return mPatMgr.edge_num();
}

// @brief 枝のファンイン元のノード番号を返す．
// @param[in] id 枝番号 ( 0 <= id < pg_edge_num() )
int
CiCellLibrary::pg_edge_from(int id) const
{
  return mPatMgr.edge_from(id);
}

// @brief 枝のファンアウト先のノード番号を返す．
// @param[in] id 枝番号 ( 0 <= id < pg_edge_num() )
int
CiCellLibrary::pg_edge_to(int id) const
{
  return mPatMgr.edge_to(id);
}

// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
// @param[in] id 枝番号 ( 0 <= id < pg_edge_num() )
int
CiCellLibrary::pg_edge_pos(int id) const
{
  return mPatMgr.edge_pos(id);
}

// @brief 枝の反転属性を返す．
// @param[in] id 枝番号 ( 0 <= id < pg_edge_num() )
bool
CiCellLibrary::pg_edge_inv(int id) const
{
  return mPatMgr.edge_inv(id);
}

// @brief 名前を設定する．
// @param[in] name 名前
void
CiCellLibrary::set_name(const string& name)
{
  mName = name;
}

// @brief 'technology' を設定する．
void
CiCellLibrary::set_technology(ClibTechnology technology)
{
  mTechnology = technology;
}

// @brief 遅延モデルを設定する．
void
CiCellLibrary::set_delay_model(ClibDelayModel delay_model)
{
  mDelayModel = delay_model;
}

// @brief 'capacitive_load_unit' を設定する．
// @param[in] unit 単位
// @param[in] ustr 単位の後に表示する文字列
void
CiCellLibrary::set_capacitive_load_unit(double unit,
					const string& ustr)
{
  mCapacitiveLoadUnit = unit;
  mCapacitiveLoadUnitStr = ustr;
}

// @brief 属性を設定する(浮動小数点型)
// @param[in] attr_name 属性名
// @param[in] value 値
void
CiCellLibrary::set_attr(const string& attr_name,
			double value)
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
// @param[in] attr_name 属性名
// @param[in] value 値
void
CiCellLibrary::set_attr(const string& attr_name,
			const string& value)
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

// @brief 遅延テーブルのテンプレートのリストを設定する．
void
CiCellLibrary::set_lu_table_template_list(const vector<CiLutTemplate*>& template_list)
{
  mLutTemplateList.init(template_list, mAlloc);
  for ( auto tmpl: template_list ) {
    mLutHash.add(tmpl);
  }
}

// @brief 1次元の LUT のテンプレートを作る．
// @param[in] name 名前
// @param[in] var_type1 変数型
// @param[in] index_list1 インデックス値のリスト
CiLutTemplate*
CiCellLibrary::new_lut_template1(const ShString& name,
				 ClibVarType var_type1,
				 const vector<double>& index_list1)
{
  void* p = mAlloc.get_memory(sizeof(CiLutTemplate1D));
  CiLutTemplate* tmpl = new (p) CiLutTemplate1D(name,
						var_type1, index_list1);
  return tmpl;
}

// @brief 2次元の LUT のテンプレートを作る．
// @param[in] name 名前
// @param[in] var_type1 変数型
// @param[in] index_list1 インデックス値のリスト
// @param[in] var_type2 変数型
// @param[in] index_list2 インデックス値のリスト
CiLutTemplate*
CiCellLibrary::new_lut_template2(const ShString& name,
				 ClibVarType var_type1,
				 const vector<double>& index_list1,
				 ClibVarType var_type2,
				 const vector<double>& index_list2)
{
  void* p = mAlloc.get_memory(sizeof(CiLutTemplate2D));
  CiLutTemplate* tmpl = new (p) CiLutTemplate2D(name,
						var_type1, index_list1,
						var_type2, index_list2);
  return tmpl;
}

// @brief 3次元の LUT のテンプレートを作る．
// @param[in] name 名前
// @param[in] var_type1 変数型
// @param[in] index_list1 インデックス値のリスト
// @param[in] var_type2 変数型
// @param[in] index_list2 インデックス値のリスト
// @param[in] var_type3 変数型
// @param[in] index_list3 インデックス値のリスト
CiLutTemplate*
CiCellLibrary::new_lut_template3(const ShString& name,
				 ClibVarType var_type1,
				 const vector<double>& index_list1,
				 ClibVarType var_type2,
				 const vector<double>& index_list2,
				 ClibVarType var_type3,
				 const vector<double>& index_list3)
{
  void* p = mAlloc.get_memory(sizeof(CiLutTemplate3D));
  CiLutTemplate* tmpl = new (p) CiLutTemplate3D(name,
						var_type1, index_list1,
						var_type2, index_list2,
						var_type3, index_list3);
  return tmpl;
}

// @brief セルのリストを設定する．
// @param[in] cell_list セルのリスト
// @param[in] do_compile compile() を実行する時 true にするフラグ
//
// restore() 時には compile() を実行する必要はない．
void
CiCellLibrary::set_cell_list(const vector<CiCell*>& cell_list,
			     bool do_compile)
{
#if 0
  mCellList.init(cell_list, mAlloc);

  // セルに id を設定する．
  for ( int id = 0; id < cell_list.size(); ++ id ) {
    cell_list[id]->mId = id;
  }

  // 名前をキーにしたハッシュに登録する．
  for ( auto cell: cell_list ) {
    mCellHash.add(cell);
  }

  if ( do_compile ) {
    compile(cell_list);
  }
#endif
}

// @brief 論理セルを生成する．
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] timing_list タイミング情報のリスト
CiCell*
CiCellLibrary::new_logic_cell(const ShString& name,
			      ClibArea area,
			      const vector<CiInputPin*>& input_list,
			      const vector<CiOutputPin*>& output_list,
			      const vector<CiInoutPin*>& inout_list,
			      const vector<CiBus*>& bus_list,
			      const vector<CiBundle*>& bundle_list,
			      const vector<CiTiming*>& timing_list)
{
  void* p = mAlloc.get_memory(sizeof(CiLogicCell));
  CiCell* cell = new (p) CiLogicCell(this, name, area,
				     input_list,
				     output_list,
				     inout_list,
				     bus_list,
				     bundle_list,
				     timing_list,
				     mAlloc);

  return cell;
}

// @brief FFセルを生成する．
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] timing_list タイミング情報のリスト
// @param[in] next_state "next_state" 関数の式
// @param[in] clocked_on "clocked_on" 関数の式
// @param[in] clocked_on_also "clocked_on_also" 関数の式
// @param[in] clear "clear" 関数の式
// @param[in] preset "preset" 関数の式
CiCell*
CiCellLibrary::new_ff_cell(const ShString& name,
			   ClibArea area,
			   const vector<CiInputPin*>& input_list,
			   const vector<CiOutputPin*>& output_list,
			   const vector<CiInoutPin*>& inout_list,
			   const vector<CiBus*>& bus_list,
			   const vector<CiBundle*>& bundle_list,
			   const vector<CiTiming*>& timing_list,
			   const Expr& next_state,
			   const Expr& clocked_on,
			   const Expr& clocked_on_also,
			   const Expr& clear,
			   const Expr& preset,
			   int clear_preset_var1,
			   int clear_preset_var2)
{
  bool has_clear = !clear.is_zero();
  bool has_preset = !preset.is_zero();

  CiCell* cell = nullptr;
  if ( has_clear ) {
    if ( has_preset ) {
      void* p = mAlloc.get_memory(sizeof(CiFFSRCell));
      cell = new (p) CiFFSRCell(this, name, area,
				input_list,
				output_list,
				inout_list,
				bus_list,
				bundle_list,
				timing_list,
				next_state,
				clocked_on,
				clocked_on_also,
				clear,
				preset,
				clear_preset_var1,
				clear_preset_var2,
				mAlloc);
    }
    else {
      void* p = mAlloc.get_memory(sizeof(CiFFRCell));
      cell = new (p) CiFFRCell(this, name, area,
			       input_list,
			       output_list,
			       inout_list,
			       bus_list,
			       bundle_list,
			       timing_list,
			       next_state,
			       clocked_on,
			       clocked_on_also,
			       clear,
			       mAlloc);
    }
  }
  else {
    if ( has_preset ) {
      void* p = mAlloc.get_memory(sizeof(CiFFSCell));
      cell = new (p) CiFFSCell(this, name, area,
			       input_list,
			       output_list,
			       inout_list,
			       bus_list,
			       bundle_list,
			       timing_list,
			       next_state,
			       clocked_on,
			       clocked_on_also,
			       preset,
			       mAlloc);
    }
    else {
      void* p = mAlloc.get_memory(sizeof(CiFFCell));
      cell = new (p) CiFFCell(this, name, area,
			      input_list,
			      output_list,
			      inout_list,
			      bus_list,
			      bundle_list,
			      timing_list,
			      next_state,
			      clocked_on,
			      clocked_on_also,
			      mAlloc);
    }
  }

  return cell;
}

// @brief ラッチセルを生成する．
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] timing_list タイミング情報のリスト
// @param[in] data_in "data_in" 関数の式
// @param[in] enable "enable" 関数の式
// @param[in] enable_also "enable_also" 関数の式
// @param[in] clear "clear" 関数の式
// @param[in] preset "preset" 関数の式
// @param[in] clear_preset_var1 clear と preset が同時にオンになったときの値1
// @param[in] clear_preset_var2 clear と preset が同時にオンになったときの値2
// *1: - false 論理式なし
//     - true 論理式あり
CiCell*
CiCellLibrary::new_latch_cell(const ShString& name,
			      ClibArea area,
			      const vector<CiInputPin*>& input_list,
			      const vector<CiOutputPin*>& output_list,
			      const vector<CiInoutPin*>& inout_list,
			      const vector<CiBus*>& bus_list,
			      const vector<CiBundle*>& bundle_list,
			      const vector<CiTiming*>& timing_list,
			      const Expr& data_in,
			      const Expr& enable,
			      const Expr& enable_also,
			      const Expr& clear,
			      const Expr& preset,
			      int clear_preset_var1,
			      int clear_preset_var2)
{
  bool has_clear = !clear.is_zero();
  bool has_preset = !preset.is_zero();

  CiCell* cell = nullptr;
  if ( has_clear ) {
    if ( has_preset ) {
      void* p = mAlloc.get_memory(sizeof(CiLatchSRCell));
      cell = new (p) CiLatchSRCell(this, name, area,
				   input_list,
				   output_list,
				   inout_list,
				   bus_list,
				   bundle_list,
				   timing_list,
				   data_in,
				   enable,
				   enable_also,
				   clear,
				   preset,
				   clear_preset_var1,
				   clear_preset_var2,
				   mAlloc);
    }
    else {
      void* p = mAlloc.get_memory(sizeof(CiLatchRCell));
      cell = new (p) CiLatchRCell(this, name, area,
				  input_list,
				  output_list,
				  inout_list,
				  bus_list,
				  bundle_list,
				  timing_list,
				  data_in,
				  enable,
				  enable_also,
				  clear,
				  mAlloc);
    }
  }
  else {
    if ( has_preset ) {
      void* p = mAlloc.get_memory(sizeof(CiLatchSCell));
      cell = new (p) CiLatchSCell(this, name, area,
				  input_list,
				  output_list,
				  inout_list,
				  bus_list,
				  bundle_list,
				  timing_list,
				  data_in,
				  enable,
				  enable_also,
				  preset,
				  mAlloc);
    }
    else {
      void* p = mAlloc.get_memory(sizeof(CiLatchCell));
      cell = new (p) CiLatchCell(this, name, area,
				 input_list,
				 output_list,
				 inout_list,
				 bus_list,
				 bundle_list,
				 timing_list,
				 data_in,
				 enable,
				 enable_also,
				 mAlloc);
    }
  }

  return cell;
}

// @brief FSMセルを生成する．
// @param[in] name 名前
// @param[in] area 面積
// @param[in] input_list 入力ピンのリスト
// @param[in] output_list 出力ピンのリスト
// @param[in] inout_list 入出力ピンのリスト
// @param[in] internal_list 内部ピンのリスト
// @param[in] bus_list バスのリスト
// @param[in] bundle_list バンドルのリスト
// @param[in] timing_list タイミング情報のリスト
CiCell*
CiCellLibrary::new_fsm_cell(const ShString& name,
			    ClibArea area,
			    const vector<CiInputPin*>& input_list,
			    const vector<CiOutputPin*>& output_list,
			    const vector<CiInoutPin*>& inout_list,
			    const vector<CiInternalPin*>& internal_list,
			    const vector<CiBus*>& bus_list,
			    const vector<CiBundle*>& bundle_list,
			    const vector<CiTiming*>& timing_list)
{
  void* p = mAlloc.get_memory(sizeof(CiFsmCell));
  CiCell* cell = new (p) CiFsmCell(this, name, area,
				   input_list,
				   output_list,
				   inout_list,
				   internal_list,
				   bus_list,
				   bundle_list,
				   timing_list,
				   mAlloc);

  return cell;
}

// @brief セルの入力ピンの内容を設定する．
// @param[in] name 入力ピン名
// @param[in] capacitance 入力ピンの負荷容量
// @param[in] rise_capacitance 入力ピンの立ち上がり負荷容量
// @param[in] fall_capacitance 入力ピンの立ち下がり負荷容量
CiInputPin*
CiCellLibrary::new_cell_input(const ShString& name,
			      ClibCapacitance capacitance,
			      ClibCapacitance rise_capacitance,
			      ClibCapacitance fall_capacitance)
{
  void* p = mAlloc.get_memory(sizeof(CiInputPin));
  CiInputPin* pin = new (p) CiInputPin(name,
				       capacitance,
				       rise_capacitance, fall_capacitance);

  return pin;
}

// @brief セルの出力ピンの内容を設定する．
// @param[in] name 出力ピン名
// @param[in] has_logic 論理式を持つとき true にするフラグ
// @param[in] logic_expr 論理式
// @param[in] tristate_expr tristate 条件式
// @param[in] max_fanout 最大ファンアウト容量
// @param[in] min_fanout 最小ファンアウト容量
// @param[in] max_capacitance 最大負荷容量
// @param[in] min_capacitance 最小負荷容量
// @param[in] max_transition 最大遷移時間
// @param[in] min_transition 最小遷移時間
CiOutputPin*
CiCellLibrary::new_cell_output(const ShString& name,
			       bool has_logic,
			       const Expr& logic_expr,
			       const Expr& tristate_expr,
			       ClibCapacitance max_fanout,
			       ClibCapacitance min_fanout,
			       ClibCapacitance max_capacitance,
			       ClibCapacitance min_capacitance,
			       ClibTime max_transition,
			       ClibTime min_transition)
{
  void* p = mAlloc.get_memory(sizeof(CiOutputPin));
  CiOutputPin* pin = new (p) CiOutputPin(name,
					 has_logic, logic_expr,
					 tristate_expr,
					 max_fanout, min_fanout,
					 max_capacitance, min_capacitance,
					 max_transition, min_transition);

  return pin;
}

// @brief セルの入出力ピンの内容を設定する．
// @param[in] name 入出力ピン名
// @param[in] has_logic 論理式を持つとき true にするフラグ
// @param[in] logic_expr 論理式
// @param[in] tristate_expr tristate 条件式
// @param[in] capacitance 入力ピンの負荷容量
// @param[in] rise_capacitance 入力ピンの立ち上がり負荷容量
// @param[in] fall_capacitance 入力ピンの立ち下がり負荷容量
// @param[in] max_fanout 最大ファンアウト容量
// @param[in] min_fanout 最小ファンアウト容量
// @param[in] max_capacitance 最大負荷容量
// @param[in] min_capacitance 最小負荷容量
// @param[in] max_transition 最大遷移時間
// @param[in] min_transition 最小遷移時間
CiInoutPin*
CiCellLibrary::new_cell_inout(const ShString& name,
			      bool has_logic,
			      const Expr& logic_expr,
			      const Expr& tristate_expr,
			      ClibCapacitance capacitance,
			      ClibCapacitance rise_capacitance,
			      ClibCapacitance fall_capacitance,
			      ClibCapacitance max_fanout,
			      ClibCapacitance min_fanout,
			      ClibCapacitance max_capacitance,
			      ClibCapacitance min_capacitance,
			      ClibTime max_transition,
			      ClibTime min_transition)
{
  void* p = mAlloc.get_memory(sizeof(CiInoutPin));
  CiInoutPin* pin =  new (p) CiInoutPin(name,
					has_logic, logic_expr,
					tristate_expr,
					capacitance,
					rise_capacitance, fall_capacitance,
					max_fanout, min_fanout,
					max_capacitance, min_capacitance,
					max_transition, min_transition);

  return pin;
}

// @brief セルの内部ピンを生成する．
// @param[in] name 内部ピン名
CiInternalPin*
CiCellLibrary::new_cell_internal(const ShString& name)
{
  void* p = mAlloc.get_memory(sizeof(CiInternalPin));
  CiInternalPin* pin = new (p) CiInternalPin(name);

  return pin;
}

// @brief タイミング情報を作る(ジェネリック遅延モデル)．
// @param[in] type タイミングの型
// @param[in] cond タイミング条件を表す式
// @param[in] intrinsic_rise 立ち上がり固有遅延
// @param[in] intrinsic_fall 立ち下がり固有遅延
// @param[in] slope_rise 立ち上がりスロープ遅延
// @param[in] slope_fall 立ち下がりスロープ遅延
// @param[in] rise_resistance 立ち上がり負荷依存係数
// @param[in] fall_resistance 立ち下がり負荷依存係数
CiTiming*
CiCellLibrary::new_timing_generic(ClibTimingType type,
				  const Expr& cond,
				  ClibTime intrinsic_rise,
				  ClibTime intrinsic_fall,
				  ClibTime slope_rise,
				  ClibTime slope_fall,
				  ClibResistance rise_resistance,
				  ClibResistance fall_resistance)
{
  void* p = mAlloc.get_memory(sizeof(CiTimingGeneric));
  CiTiming* timing = new (p) CiTimingGeneric(type, cond,
					     intrinsic_rise,
					     intrinsic_fall,
					     slope_rise,
					     slope_fall,
					     rise_resistance,
					     fall_resistance);

  return timing;
}

// @brief タイミング情報を作る(折れ線近似)．
// @param[in] timing_type タイミングの型
// @param[in] cond タイミング条件を表す式
// @param[in] intrinsic_rise 立ち上がり固有遅延
// @param[in] intrinsic_fall 立ち下がり固有遅延
// @param[in] slope_rise 立ち上がりスロープ遅延
// @param[in] slope_fall 立ち下がりスロープ遅延
CiTiming*
CiCellLibrary::new_timing_piecewise(ClibTimingType timing_type,
				    const Expr& cond,
				    ClibTime intrinsic_rise,
				    ClibTime intrinsic_fall,
				    ClibTime slope_rise,
				    ClibTime slope_fall,
				    ClibResistance rise_pin_resistance,
				    ClibResistance fall_pin_resistance)
{
  void* p = mAlloc.get_memory(sizeof(CiTimingPiecewise));
  CiTiming* timing = new (p) CiTimingPiecewise(timing_type, cond,
					       intrinsic_rise,
					       intrinsic_fall,
					       slope_rise,
					       slope_fall,
					       rise_pin_resistance,
					       fall_pin_resistance);

  return timing;
}

// @brief タイミング情報を作る(非線形タイプ1)．
// @param[in] timing_type タイミングの型
// @param[in] cond タイミング条件を表す式
// @param[in] cell_rise 立ち上がりセル遅延テーブル
// @param[in] cell_fall 立ち下がりセル遅延テーブル
CiTiming*
CiCellLibrary::new_timing_lut1(ClibTimingType timing_type,
			       const Expr& cond,
			       ClibLut* cell_rise,
			       ClibLut* cell_fall,
			       ClibLut* rise_transition,
			       ClibLut* fall_transition)
{
  void* p = mAlloc.get_memory(sizeof(CiTimingLut1));
  CiTiming* timing = new (p) CiTimingLut1(timing_type, cond,
					  cell_rise,
					  cell_fall,
					  rise_transition,
					  fall_transition);

  return timing;
}

// @brief タイミング情報を作る(非線形タイプ2)．
// @param[in] timing_type タイミングの型
// @param[in] cond タイミング条件を表す式
// @param[in] rise_transition 立ち上がり遷移遅延テーブル
// @param[in] fall_transition 立ち下がり遷移遅延テーブル
// @param[in] rise_propagation 立ち上がり伝搬遅延テーブル
// @param[in] fall_propagation 立ち下がり伝搬遅延テーブル
CiTiming*
CiCellLibrary::new_timing_lut2(ClibTimingType timing_type,
			       const Expr& cond,
			       ClibLut* rise_transition,
			       ClibLut* fall_transition,
			       ClibLut* rise_propagation,
			       ClibLut* fall_propagation)
{
  void* p = mAlloc.get_memory(sizeof(CiTimingLut2));
  CiTiming* timing = new (p) CiTimingLut2(timing_type, cond,
					  rise_transition,
					  fall_transition,
					  rise_propagation,
					  fall_propagation);

  return timing;
}

// @brief タイミング情報をセットする．
// @param[in] cell セル
// @param[in] opin_id 出力(入出力)ピン番号 ( *1 )
// @param[in] ipin_id 関連する入力(入出力)ピン番号 ( *2 )
// @param[in] timing_sense タイミングセンス
// @param[in] timing_list タイミング情報のリスト
// @note ( *1 ) opin_id で入出力ピンを表す時には入出力ピン番号
//  + cell->output_num() を使う．
// @note ( *2 ) ipin_id で入出力ピンを表す時には入出力ピン番号
//  + cell->input_num() を使う．
void
CiCellLibrary::set_timing(CiCell* cell,
			  int ipin_id,
			  int opin_id,
			  ClibTimingSense timing_sense,
			  const vector<CiTiming*>& timing_list)
{
  int base = (opin_id * cell->input_num2() + ipin_id) * 2;
  switch ( timing_sense ) {
  case kClibPosiUnate: base += 0; break;
  case kClibNegaUnate: base += 1; break;
  default: ASSERT_NOT_REACHED;
  }
  cell->mTimingMap[base].init(timing_list, mAlloc);
}

// @brief 1次元の LUT を作る．
// @param[in] lut_template テンプレート
// @param[in] value_array 値の配列
// @param[in] index_array インデックス値のリスト
ClibLut*
CiCellLibrary::new_lut1(const ClibLutTemplate* lut_template,
			const vector<double>& value_array,
			const vector<double>& index_array)
{
  void* p = mAlloc.get_memory(sizeof(CiLut1D));
  ClibLut* lut = new (p) CiLut1D(lut_template, value_array, index_array);
  return lut;
}

// @brief 2次元の LUT を作る．
// @param[in] lut_template テンプレート
// @param[in] value_array 値の配列
// @param[in] index_array1 インデックス値のリスト
// @param[in] index_array2 インデックス値のリスト
ClibLut*
CiCellLibrary::new_lut2(const ClibLutTemplate* lut_template,
			const vector<double>& value_array,
			const vector<double>& index_array1,
			const vector<double>& index_array2)
{
  void* p = mAlloc.get_memory(sizeof(CiLut2D));
  ClibLut* lut = new (p) CiLut2D(lut_template, value_array,
				 index_array1, index_array2);
  return lut;
}

// @brief 3次元の LUT を作る．
// @param[in] lut_template テンプレート
// @param[in] value_array 値の配列
// @param[in] index_array1 インデックス値のリスト
// @param[in] index_array2 インデックス値のリスト
// @param[in] index_array3 インデックス値のリスト
ClibLut*
CiCellLibrary::new_lut3(const ClibLutTemplate* lut_template,
			const vector<double>& value_array,
			const vector<double>& index_array1,
			const vector<double>& index_array2,
			const vector<double>& index_array3)
{
  void* p = mAlloc.get_memory(sizeof(CiLut3D));
  ClibLut* lut = new (p) CiLut3D(lut_template, value_array,
				 index_array1, index_array2, index_array3);
  return lut;
}

// @brief セルのグループ分けを行う．
//
// 論理セルのパタングラフも作成する．
void
CiCellLibrary::compile(const vector<CiCell*>& cell_list)
{
  LibComp libcomp;

  libcomp.compile(cell_list);

  // LcGroup から CiCellGroup を作る．
  int ng = libcomp.group_num();
  vector<CiCellGroup*> group_list(ng);
  for ( int g = 0; g < ng; ++ g ) {
    const LcGroup* src_group = libcomp.group(g);
    const vector<CiCell*>& cell_list = src_group->cell_list();
    group_list[g] = new_cell_group(g, src_group->map(), 0U, cell_list);
  }
  mGroupList.init(group_list, mAlloc);

  // LcClass から CiCellClass を作る．
  int nc = libcomp.npn_class_num();
  vector<CiCellClass*> class_list(nc);
  for ( int c = 0; c < nc; ++ c ) {
    const LcClass* src_class = libcomp.npn_class(c);
    const vector<LcGroup*>& src_group_list = src_class->group_list();
    int n = src_group_list.size();
    vector<CiCellGroup*> dst_group_list(n);
    for ( int i = 0; i < n; ++ i ) {
      dst_group_list[i] = group_list[src_group_list[i]->id()];
    }
    class_list[c] = new_cell_class(c, src_class->idmap_list(), dst_group_list);
  }
  mClassList.init(class_list, mAlloc);

  for ( int i = 0; i < 4; ++ i ) {
    mLogicGroup[i] = group_list[libcomp.logic_group(i)];
  }

  // i の値
  //  0: Q のみ
  //  1: XQ のみ
  //  2: Q/XQ 両方
  for (int i = 0; i < 3; ++ i) {
    bool has_q = (i == 0 || i == 2);
    bool has_xq = (i == 1 || i == 2);

    // j の値
    //  0: クリアなし
    //  1: クリアあり
    for (int j = 0; j < 2; ++ j) {
      bool has_clear = (j == 1);

      // k の値
      //  0: プリセットなし
      //  1: プリセットあり
      for (int k = 0; k < 2; ++ k) {
	bool has_preset = (k == 1);

	int cid = libcomp.ff_class(has_q, has_xq, has_clear, has_preset);
	CiCellClass* cclass = class_list[cid];
	mFFClass[i * 4 + j * 2 + k] = cclass;

	for ( auto group: cclass->group_list() ) {
	  // ちょっと面倒な手順を踏む．
	  int gid = group->id();
	  CiCellGroup* cgroup = group_list[gid];
	  NpnMapM map = cgroup->map();
	  int pos_array[6] = { 0, 0, 0, 0, 0, 0 };
	  int ni = map.input_num() - 2;
	  ASSERT_COND( ni <= 4 );
	  for (int i = 0; i < ni; ++ i) {
	    NpnVmap imap = map.imap(VarId(i));
	    if ( !imap.is_invalid() ) {
	      int pos = imap.var().val();
	      int pol = imap.inv() ? 16U : 8U;
	      pos_array[pos] = i | pol;
	    }
	  }
#warning "TODO: 反転出力ありと決めつけていいの？"
	  pos_array[4] = 0;
	  pos_array[5] = 1 | (1 << 3);
	  cgroup->set_ff_info(pos_array);
	}
      }
    }
  }

  // i の値
  //  0: Q のみ
  //  1: XQ のみ
  //  2: Q/XQ 両方
  for (int i = 0; i < 3; ++ i) {
    bool has_q = (i == 0 || i == 2);
    bool has_xq = (i == 1 || i == 2);

    // j の値
    //  0: クリアなし
    //  1: クリアあり
    for (int j = 0; j < 2; ++ j) {
      bool has_clear = (j == 1);

      // k の値
      //  0: プリセットなし
      //  1: プリセットあり
      for (int k = 0; k < 2; ++ k) {
	bool has_preset = (k == 1);

	int cid = libcomp.latch_class(has_q, has_xq, has_clear, has_preset);
	CiCellClass* cclass = class_list[cid];
	mLatchClass[i * 4 + j * 2 + k] = cclass;

	for ( auto group: cclass->group_list() ) {
	  // ちょっと面倒な手順を踏む．
	  int gid = group->id();
	  CiCellGroup* cgroup = group_list[gid];
	  NpnMapM map = cgroup->map();
	  int pos_array[5] = { 0, 0, 0, 0, 0 };
	  int ni = map.input_num() - 2;
	  ASSERT_COND( ni <= 4 );
	  for (int i = 0; i < ni; ++ i) {
	    NpnVmap imap = map.imap(VarId(i));
	    if ( !imap.is_invalid() ) {
	      int pos = imap.var().val();
	      int pol = imap.inv() ? 16U : 8U;
	      pos_array[pos] = i | pol;
	    }
	  }
	  pos_array[4] = 0;
	  cgroup->set_latch_info(pos_array);
	}
      }
    }
  }

  mPatMgr.copy(libcomp.pat_mgr());
}

// @brief セルグループを作る．
// @param[in] id 番号
// @param[in] map 変換マップ
// @param[in] cell_list セルのリスト
CiCellGroup*
CiCellLibrary::new_cell_group(int id,
			      const NpnMapM& map,
			      int pininfo,
			      const vector<CiCell*>& cell_list)
{
  void* p = mAlloc.get_memory(sizeof(CiCellGroup));
  CiCellGroup* group = new (p) CiCellGroup(id, map, pininfo, cell_list, mAlloc);

  return group;
}

// @brief セルクラスを作る．
// @param[in] id 番号
// @param[in] idmap_list 同位体変換リスト
// @param[in] group_list グループのリスト
CiCellClass*
CiCellLibrary::new_cell_class(int id,
			      const vector<NpnMapM>& idmap_list,
			      const vector<CiCellGroup*>& group_list)
{
  void* p = mAlloc.get_memory(sizeof(CiCellClass));
  CiCellClass* cell_class = new (p) CiCellClass(id, idmap_list, group_list, mAlloc);

  return cell_class;
}

// @brief ピンを登録する．
void
CiCellLibrary::reg_pin(CiCellPin* pin)
{
  mPinHash.add(pin);
}

// @brief ピン名からピンを取り出す．
// @param[in] cell セル
// @param[in] name ピン名
CiCellPin*
CiCellLibrary::get_pin(const CiCell* cell,
		       ShString name)
{
  return mPinHash.get(cell, name);
}

END_NAMESPACE_YM_CLIB
