
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

#include "CiLogicCell.h"
#include "CiTriLogicCell.h"
#include "CiGenLogicCell.h"
#include "CiFFCell.h"

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

// @brief 遅延テーブルのテンプレートのリストを設定する．
void
CiCellLibrary::set_lu_table_template_list(
  const vector<CiLutTemplate*>& template_list
)
{
  for ( auto tmpl: template_list ) {
    tmpl->mId = mLutTemplateList.size();
    mLutTemplateList.push_back(tmpl);
    mLutHash.emplace(tmpl->_name(), tmpl->mId);
  }
}

// @brief 1次元の LUT のテンプレートを作る．
CiLutTemplate*
CiCellLibrary::new_lut_template1(
  const ShString& name,
  ClibVarType var_type1,
  const vector<double>& index_list1
)
{
  auto tmpl = new CiLutTemplate1D(name, var_type1, index_list1);
  return tmpl;
}

// @brief 2次元の LUT のテンプレートを作る．
CiLutTemplate*
CiCellLibrary::new_lut_template2(
  const ShString& name,
  ClibVarType var_type1,
  const vector<double>& index_list1,
  ClibVarType var_type2,
  const vector<double>& index_list2
)
{
  auto tmpl = new CiLutTemplate2D(name,
				  var_type1, index_list1,
				  var_type2, index_list2);
  return tmpl;
}

// @brief 3次元の LUT のテンプレートを作る．
CiLutTemplate*
CiCellLibrary::new_lut_template3(
  const ShString& name,
  ClibVarType var_type1,
  const vector<double>& index_list1,
  ClibVarType var_type2,
  const vector<double>& index_list2,
  ClibVarType var_type3,
  const vector<double>& index_list3
)
{
  auto tmpl = new CiLutTemplate3D(name,
				  var_type1, index_list1,
				  var_type2, index_list2,
				  var_type3, index_list3);
  return tmpl;
}

// @brief セルクラスを作る．
CiCellClass*
CiCellLibrary::new_cell_class(
  const vector<ClibIOMap>& idmap_list
)
{
  SizeType id = mClassList.size();
  auto cc = new CiCellClass{id, idmap_list};
  mClassList.push_back(unique_ptr<CiCellClass>(cc));
  mRefClassList.push_back(cc);
  return nullptr;
}

// @brief セルグループを作る．
CiCellGroup*
CiCellLibrary::new_cell_group(
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

// @brief 1出力の論理セルを作る．
CiCell*
CiCellLibrary::new_logic_cell(
  const ShString& name,                  ///< [in] 名前
  ClibArea area,                         ///< [in] 面積
#if 0
  const vector<CiInputPin*>& input_list, ///< [in] 入力ピンのリスト
  CiOutputPin* output,                   ///< [in] 出力ピン
  const vector<CiTiming*>& timing_list,  ///< [in] タイミング条件のリスト
#endif
  const Expr& expr                       ///< [in] 出力の論理式
)
{
  auto cell = new CiLogicCell{
    this, name, area,
#if 0
    input_list,
    output,
    timing_list,
#endif
    expr
  };
  reg_cell(cell);
  return cell;
}

// @brief 1出力のトライステートセルを作る．
CiCell*
CiCellLibrary::new_tristate_cell(
  const ShString& name,                  ///< [in] 名前
  ClibArea area,                         ///< [in] 面積
#if 0
  const vector<CiInputPin*>& input_list, ///< [in] 入力ピンのリスト
  CiOutputPin* output,                   ///< [in] 出力ピン
  const vector<CiTiming*>& timing_list,  ///< [in] タイミング条件のリスト
#endif
  const Expr& expr,                      ///< [in] 出力の論理式
  const Expr& tristate_expr              ///< [in] 出力のトライステート条件の論理式
)
{
  auto cell = new CiTriLogicCell(this, name, area,
#if 0
				 input_list,
				 output,
				 timing_list,
#endif
				 expr, tristate_expr);
  reg_cell(cell);
  return cell;
}

// @brief 一般的な論理セルを生成する．
CiCell*
CiCellLibrary::new_generic_cell(
  const ShString& name,                    ///< [in] 名前
  ClibArea area,                           ///< [in] 面積
#if 0
  const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
  const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
  const vector<CiInoutPin*>& inout_list,   ///< [in] 入出力ピンのリスト
  const vector<CiTiming*>& timing_list,    ///< [in] タイミング条件のリスト
#endif
  const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
  const vector<Expr>& tristate_expr_list   ///< [in] 出力のトライステート条件の論理式のリスト
)
{
  auto cell = new CiGenLogicCell(this, name, area,
#if 0
				 input_list,
				 output_list,
				 inout_list,
				 timing_list,
#endif
				 expr_list,
				 tristate_expr_list);
  reg_cell(cell);
  return cell;
}

// @brief FFセルを生成する．
CiCell*
CiCellLibrary::new_ff_cell(
  const ShString& name,
  ClibArea area,
#if 0
  const vector<CiInputPin*>& input_list,
  const vector<CiOutputPin*>& output_list,
  const vector<CiTiming*>& timing_list,
#endif
  const vector<Expr>& expr_list,
  const Expr& clocked_on,
  const Expr& clocked_on_also,
  const Expr& next_state,
  const Expr& clear,
  const Expr& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  // - slave clock の有無
  // - クリア端子の有無
  // - プリセット端子の有無
  // で８通りのバリエーションがある．
  bool has_clock2 = clocked_on_also.is_valid();
  bool has_clear = !clear.is_zero();
  bool has_preset = !preset.is_zero();

  CiCell* cell = nullptr;
  if ( has_clear ) {
    if ( has_preset ) {
      if ( has_clock2 ) {
	cell = new CiFFMSRCell(this, name, area,
#if 0
			       input_list,
			       output_list,
			       timing_list,
#endif
			       expr_list,
			       clocked_on,
			       clocked_on_also,
			       next_state,
			       clear,
			       preset,
			       clear_preset_var1,
			       clear_preset_var2);
      }
      else {
	cell = new CiFFSRCell(this, name, area,
#if 0
			      input_list,
			      output_list,
			      timing_list,
#endif
			      expr_list,
			      clocked_on,
			      next_state,
			      clear,
			      preset,
			      clear_preset_var1,
			      clear_preset_var2);
      }
    }
    else {
      if ( has_clock2 ) {
	cell = new CiFFMRCell(this, name, area,
#if 0
			      input_list,
			      output_list,
			      timing_list,
#endif
			      expr_list,
			      clocked_on,
			      clocked_on_also,
			      next_state,
			      clear);
      }
      else {
	cell = new CiFFRCell(this, name, area,
#if 0
			     input_list,
			     output_list,
			     timing_list,
#endif
			     expr_list,
			     clocked_on,
			     next_state,
			     clear);
      }
    }
  }
  else {
    if ( has_preset ) {
      if ( has_clock2 ) {
	cell = new CiFFMSCell(this, name, area,
#if 0
			      input_list,
			      output_list,
			      timing_list,
#endif
			      expr_list,
			      clocked_on,
			      clocked_on_also,
			      next_state,
			      preset);
      }
      else {
	cell = new CiFFSCell(this, name, area,
#if 0
			     input_list,
			     output_list,
			     timing_list,
#endif
			     expr_list,
			     clocked_on,
			     next_state,
			     preset);
      }
    }
    else {
      if ( has_clock2 ) {
	cell = new CiFFMCell(this, name, area,
#if 0
			     input_list,
			     output_list,
			     timing_list,
#endif
			     expr_list,
			     clocked_on,
			     clocked_on_also,
			     next_state);
      }
      else {
	cell = new CiFFCell(this, name, area,
#if 0
			    input_list,
			    output_list,
			    timing_list,
#endif
			    expr_list,
			    clocked_on,
			    next_state);
      }
    }
  }
  reg_cell(cell);
  return cell;
}

// @brief ラッチセルを生成する．
CiCell*
CiCellLibrary::new_latch_cell(
  const ShString& name,                    ///< [in] 名前
  ClibArea area,                           ///< [in] 面積
#if 0
  const vector<CiInputPin*>& input_list,   ///< [in] 入力ピンのリスト
  const vector<CiOutputPin*>& output_list, ///< [in] 出力ピンのリスト
  const vector<CiTiming*>& timing_list,    ///< [in] タイミング条件のリスト
#endif
  const vector<Expr>& expr_list,           ///< [in] 出力の論理式のリスト
  const Expr& enable,                 ///< [in] マスターイネーブルの論理式
  const Expr& enable2,                ///< [in] スレーブイネーブルの論理式
  const Expr& data_in,                ///< [in] データ入力の論理式
  const Expr& clear,                  ///< [in] クリア条件の論理式
  const Expr& preset,                 ///< [in] プリセット条件の論理式
  ClibCPV clear_preset_var1,          ///< [in] クリアとプリセットが同時にアクティブになった時の値1
  ClibCPV clear_preset_var2           ///< [in] クリアとプリセットが同時にアクティブになった時の値2
)
{
  #warning "TODO: 未完"
  return nullptr;
}

#if 0
// @brief ラッチセルを生成する．
CiCell*
CiCellLibrary::new_latch_cell(
  const ShString& name,
  ClibArea area,
  const vector<CiInputPin*>& input_list,
  const vector<CiOutputPin*>& output_list,
  const vector<CiInoutPin*>& inout_list,
  const vector<CiBus*>& bus_list,
  const vector<CiBundle*>& bundle_list,
  const vector<CiTiming*>& timing_list,
  const Expr& enable,
  const Expr& enable_also,
  const Expr& data_in,
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
      cell = new CiLatchSRCell(this, name, area,
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
			       clear_preset_var2);
    }
    else {
      cell = new CiLatchRCell(this, name, area,
			      input_list,
			      output_list,
			      inout_list,
			      bus_list,
			      bundle_list,
			      timing_list,
			      data_in,
			      enable,
			      enable_also,
			      clear);
    }
  }
  else {
    if ( has_preset ) {
      cell = new CiLatchSCell(this, name, area,
			      input_list,
			      output_list,
			      inout_list,
			      bus_list,
			      bundle_list,
			      timing_list,
			      data_in,
			      enable,
			      enable_also,
			      preset);
    }
    else {
      cell = new CiLatchCell(this, name, area,
			     input_list,
			     output_list,
			     inout_list,
			     bus_list,
			     bundle_list,
			     timing_list,
			     data_in,
			     enable,
			     enable_also);
    }
  }
  mCellList.push_back(unique_ptr<CiCell>{cell});
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
CiCellLibrary::new_fsm_cell(
  const ShString& name,
  ClibArea area,
  const vector<CiInputPin*>& input_list,
  const vector<CiOutputPin*>& output_list,
  const vector<CiInoutPin*>& inout_list,
  const vector<CiInternalPin*>& internal_list,
  const vector<CiBus*>& bus_list,
  const vector<CiBundle*>& bundle_list,
  const vector<CiTiming*>& timing_list
)
{
  auto cell = new CiFsmCell(this, name, area,
			    input_list,
			    output_list,
			    inout_list,
			    internal_list,
			    bus_list,
			    bundle_list,
			    timing_list);
  mCellList.push_back(unique_ptr<CiCell>{cell});
  return cell;
}
#endif

// @brief セルを登録する．
void
CiCellLibrary::reg_cell(
  CiCell* cell ///< [in] セル
)
{
  mCellList.push_back(unique_ptr<CiCell>{cell});
  mRefCellList.push_back(cell);
}


#if 0
// @brief セルの入力ピンの内容を設定する．
// @param[in] name 入力ピン名
// @param[in] capacitance 入力ピンの負荷容量
// @param[in] rise_capacitance 入力ピンの立ち上がり負荷容量
// @param[in] fall_capacitance 入力ピンの立ち下がり負荷容量
CiInputPin*
CiCellLibrary::new_cell_input(
  const ShString& name,
  ClibCapacitance capacitance,
  ClibCapacitance rise_capacitance,
  ClibCapacitance fall_capacitance
)
{
  auto pin = new CiInputPin(name, capacitance,
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
CiCellLibrary::new_cell_output(
  const ShString& name,
  ClibCapacitance max_fanout,
  ClibCapacitance min_fanout,
  ClibCapacitance max_capacitance,
  ClibCapacitance min_capacitance,
  ClibTime max_transition,
  ClibTime min_transition
)
{
  auto pin = new CiOutputPin(name,
			     max_fanout, min_fanout,
			     max_capacitance, min_capacitance,
			     max_transition, min_transition);

  return pin;
}

// @brief セルの入出力ピンの内容を設定する．
// @param[in] name 入出力ピン名
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
CiCellLibrary::new_cell_inout(
  const ShString& name,
  ClibCapacitance capacitance,
  ClibCapacitance rise_capacitance,
  ClibCapacitance fall_capacitance,
  ClibCapacitance max_fanout,
  ClibCapacitance min_fanout,
  ClibCapacitance max_capacitance,
  ClibCapacitance min_capacitance,
  ClibTime max_transition,
  ClibTime min_transition
)
{
  auto pin =  new CiInoutPin(name,
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
CiCellLibrary::new_cell_internal(
  const ShString& name
)
{
  auto pin = new CiInternalPin(name);

  return pin;
}
#endif

#if 0
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
CiCellLibrary::new_timing_generic(
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
  auto timing = new CiTimingGeneric(type, cond,
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
CiCellLibrary::new_timing_piecewise(
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
  auto timing = new CiTimingPiecewise(timing_type, cond,
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
CiCellLibrary::new_timing_lut1(
  ClibTimingType timing_type,
  const Expr& cond,
  CiLut* cell_rise,
  CiLut* cell_fall,
  CiLut* rise_transition,
  CiLut* fall_transition
)
{
  auto timing = new CiTimingLut1(timing_type, cond,
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
CiCellLibrary::new_timing_lut2(
  ClibTimingType timing_type,
  const Expr& cond,
  CiLut* rise_transition,
  CiLut* fall_transition,
  CiLut* rise_propagation,
  CiLut* fall_propagation)
{
  CiTiming* timing = new CiTimingLut2(timing_type, cond,
				      rise_transition,
				      fall_transition,
				      rise_propagation,
				      fall_propagation);

  return timing;
}
#endif

// @brief 1次元の LUT を作る．
// @param[in] lut_template テンプレート
// @param[in] value_array 値の配列
// @param[in] index_array インデックス値のリスト
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
  static CiLut1D lut(&error_lut_template(), vector<double>());

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

#if 0
// @brief セルのグループ分けを行う．
//
// 論理セルのパタングラフも作成する．
void
CiCellLibrary::compile(
  LibComp& libcomp
)
{
  libcomp.compile();

  // LcGroup から CiCellGroup を作る．
  auto ng = libcomp.group_num();
  mGroupList.clear();
  mGroupList.reserve(ng);
  for ( auto g: Range(ng) ) {
    const LcGroup& src_group = libcomp.group(g);
    const vector<CiCell*>& cell_list = src_group.cell_list();
    CiCellGroup* group = new_cell_group(g, src_group.map(), cell_list);
    mGroupList.push_back(unique_ptr<CiCellGroup>{group});
  }

  // LcClass から CiCellClass を作る．
  auto nc = libcomp.npn_class_num();
  mClassList.clear();
  mClassList.reserve(nc);
  for ( auto c: Range(nc) ) {
    const LcClass& src_class = libcomp.npn_class(c);
    const vector<LcGroup*>& src_group_list = src_class.group_list();
    auto n = src_group_list.size();
    vector<CiCellGroup*> dst_group_list(n);
    for ( auto i: Range(n) ) {
      dst_group_list[i] = mGroupList[src_group_list[i]->id()].get();
    }
    auto cclass = new_cell_class(c, src_class.idmap_list(), dst_group_list);
    mClassList.push_back(unique_ptr<CiCellClass>{cclass});
  }

  for ( int i: { 0, 1, 2, 3 } ) {
    mLogicGroup[i] = mGroupList[libcomp.logic_group(i)].get();
  }

  // i の値
  //  0: Q のみ
  //  1: XQ のみ
  //  2: Q/XQ 両方
  for ( int i: { 0, 1, 2 } ) {
    bool has_q = (i == 0 || i == 2);
    bool has_xq = (i == 1 || i == 2);

    // j の値
    //  0: クリアなし
    //  1: クリアあり
    for ( int j: { 0, 1 } ) {
      bool has_clear = (j == 1);

      // k の値
      //  0: プリセットなし
      //  1: プリセットあり
      for ( int k: { 0, 1 } ) {
	bool has_preset = (k == 1);

	auto cid = libcomp.ff_class(has_q, has_xq, has_clear, has_preset);
	ClibCellClass* cclass = mClassList[cid].get();
	mFFClass[i * 4 + j * 2 + k] = cclass;

	for ( auto id: Range(cclass->cell_group_num()) ) {
	  auto& group = cclass->cell_group(id);
	  NpnMapM map = group.map();
	  SizeType pos_array[6] = { 0, 0, 0, 0, 0, 0 };
	  auto ni = map.input_num() - 2;
	  ASSERT_COND( ni <= 4 );
	  for ( auto i: Range(ni) ) {
	    NpnVmap imap = map.imap(VarId(i));
	    if ( !imap.is_invalid() ) {
	      auto pos = imap.var().val();
	      auto pol = imap.inv() ? 16U : 8U;
	      pos_array[pos] = i | pol;
	    }
	  }
#warning "TODO: 反転出力ありと決めつけていいの？"
	  pos_array[4] = 0;
	  pos_array[5] = 1 | (1 << 3);
	  // group は const ClibCellGroup* なので
	  // CiCellGroup* を得るためにちょっと面倒な手順を踏む．
	  auto gid = group.id();
	  //mGroupList[gid]->set_ff_info(pos_array);
#warning "TODO: 根本的に考え直す"
	}
      }
    }
  }

  // i の値
  //  0: Q のみ
  //  1: XQ のみ
  //  2: Q/XQ 両方
  for ( int i: { 0, 1, 2 } ) {
    bool has_q = (i == 0 || i == 2);
    bool has_xq = (i == 1 || i == 2);

    // j の値
    //  0: クリアなし
    //  1: クリアあり
    for ( int j: { 0, 1 } ) {
      bool has_clear = (j == 1);

      // k の値
      //  0: プリセットなし
      //  1: プリセットあり
      for ( int k: { 0, 1 } ) {
	bool has_preset = (k == 1);

	auto cid = libcomp.latch_class(has_q, has_xq, has_clear, has_preset);
	ClibCellClass* cclass = mClassList[cid].get();
	mLatchClass[i * 4 + j * 2 + k] = cclass;

	for ( auto id: Range(cclass->cell_group_num()) ) {
	  auto& group = cclass->cell_group(id);
	  NpnMapM map = group.map();
	  SizeType pos_array[5] = { 0, 0, 0, 0, 0 };
	  auto ni = map.input_num() - 2;
	  ASSERT_COND( ni <= 4 );
	  for ( auto i: Range(ni) ) {
	    NpnVmap imap = map.imap(VarId(i));
	    if ( !imap.is_invalid() ) {
	      auto pos = imap.var().val();
	      auto pol = imap.inv() ? 16U : 8U;
	      pos_array[pos] = i | pol;
	    }
	  }
	  pos_array[4] = 0;
	  // group は const ClibCellGroup* なので
	  // CiCellGroup* を得るためにちょっと面倒な手順を踏む．
	  auto gid = group.id();
	  //mGroupList[gid]->set_latch_info(pos_array);
#warning "TODO: 根本的に考え直す"
	}
      }
    }
  }

  mPatMgr.copy(libcomp.pat_mgr());
}
#endif

#if 0
// @brief セルグループを作る．
// @param[in] id 番号
// @param[in] map 変換マップ
// @param[in] cell_list セルのリスト
CiCellGroup*
CiCellLibrary::new_cell_group(
  SizeType id,
  const ClibIOMap& iomap,
  const vector<CiCell*>& cell_list)
{
  auto group = new CiCellGroup(id, map, cell_list);

  return group;
}

// @brief セルクラスを作る．
// @param[in] id 番号
// @param[in] idmap_list 同位体変換リスト
// @param[in] group_list グループのリスト
CiCellClass*
CiCellLibrary::new_cell_class(
  SizeType id,
  const vector<NpnMapM>& idmap_list,
  const vector<CiCellGroup*>& group_list)
{
  auto cell_class = new CiCellClass(id, idmap_list, group_list);

  return cell_class;
}
#endif

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
