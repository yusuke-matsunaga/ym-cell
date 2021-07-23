
/// @file CiCellLibrary_restore.cc
/// @brief CiCellLibrary の実装ファイル(restore()関係)
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

//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

void
CiCellLibrary::restore(
  istream& s
)
{
  string name;
  s >> name;

  set_name(name);

  ymuint8 tmp1;
  ymuint8 tmp2;
  s >> tmp1
    >> tmp2;
  ClibTechnology technology = static_cast<ClibTechnology>(tmp1);
  ClibDelayModel delay_model = static_cast<ClibDelayModel>(tmp2);

  set_technology(technology);
  set_delay_model(delay_model);

  string bus_naming_style;
  s >> bus_naming_style;

  set_attr("bus_naming_style", bus_naming_style);

  string date;
  s >> date;

  set_attr("date", date);


  string revision;
  s >> revision;

  set_attr("revision", revision);

  string comment;
  s >> comment;

  set_attr("comment", comment);

  string time_unit;
  s >> time_unit;

  set_attr("time_unit", time_unit);

  string voltage_unit;
  s >> voltage_unit;

  set_attr("voltage_unit", voltage_unit);

  string current_unit;
  s >> current_unit;

  set_attr("current_unit", current_unit);

  string pulling_resistance_unit;
  s >> pulling_resistance_unit;

  set_attr("pulling_resistance_unit", pulling_resistance_unit);

  double capacitive_unit;
  string capacitive_unit_str;
  s >> capacitive_unit
    >> capacitive_unit_str;

  set_capacitive_load_unit(capacitive_unit, capacitive_unit_str);

  string leakage_power_unit;
  s >> leakage_power_unit;

  set_attr("leakage_power_unit", leakage_power_unit);

  // LUTテンプレート情報の読み込み
  restore_lut_template(s);

  // セル情報の読み込み
  restore_cell(s);

  // セルグループ情報の読み込み
  restore_cell_group(s);

  // セルクラス情報の読み込み
  restore_cell_class(s);

  // 組み込み型の設定
  for ( auto i: { 0, 1, 2, 3 } ) {
    SizeType group_id;
    s >> group_id;
    mLogicGroup[i] = mGroupList[group_id].get();
  }
  for ( auto i: { 0, 1, 2, 3 } ) {
    SizeType class_id;
    s >> class_id;
    mFFClass[i] = mClassList[class_id].get();
  }
  for ( auto i: { 0, 1, 2, 3 } ) {
    SizeType class_id;
    s >> class_id;
    mLatchClass[i] = mClassList[class_id].get();
  }

  // パタングラフの情報の設定
  mPatMgr.restore(s);
}

BEGIN_NONAMESPACE

ClibVarType
restore_1dim(
  istream& s,
  vector<double>& index_array
)
{
  ymuint8 tmp;
  s >> tmp;
  ClibVarType var_type = static_cast<ClibVarType>(tmp);
  ymuint8 n;
  s >> n;
  index_array.resize(n);
  for ( auto i: Range(n) ) {
    s >> index_array[i];
  }
  return var_type;
}

END_NONAMESPACE

// @brief LUT テンプレートを読み込む．
void
CiCellLibrary::restore_lut_template(
  istream& s
)
{
  SizeType lut_num;
  s >> lut_num;
  vector<CiLutTemplate*> template_list(lut_num);
  for ( auto id: Range(lut_num) ) {
    string name;
    ymuint8 d;
    s >> name
      >> d;
    ShString shname(name);
    ClibVarType var_type1;
    ClibVarType var_type2;
    ClibVarType var_type3;
    vector<double> index_array1;
    vector<double> index_array2;
    vector<double> index_array3;
    CiLutTemplate* tmpl = nullptr;
    switch ( d ) {
    case 1:
      var_type1 = restore_1dim(s, index_array1);
      tmpl = new_lut_template1(shname,
			       var_type1, index_array1);
      break;

    case 2:
      var_type1 = restore_1dim(s, index_array1);
      var_type2 = restore_1dim(s, index_array2);
      tmpl = new_lut_template2(shname,
			       var_type1, index_array1,
			       var_type2, index_array2);
      break;

    case 3:
      var_type1 = restore_1dim(s, index_array1);
      var_type2 = restore_1dim(s, index_array2);
      var_type3 = restore_1dim(s, index_array3);
      tmpl = new_lut_template3(shname,
			       var_type1, index_array1,
			       var_type2, index_array2,
			       var_type3, index_array3);
      break;
    }
    template_list[id] = tmpl;
  }
  set_lu_table_template_list(template_list);
}

BEGIN_NONAMESPACE

vector<SizeType>
restore_tid_list(
  istream& s
)
{
  SizeType n;
  s >> n;
  vector<SizeType> timing_id_list(n);
  for ( auto i: Range(n) ) {
    s >> timing_id_list[i];
  }
  return timing_id_list;
}

END_NONAMESPACE

// @brief セルを読み込む．
void
CiCellLibrary::restore_cell(
  istream& s
)
{
  SizeType nc;
  s >> nc;
  mCellList.resize(nc);
  for ( auto cell_id: Range(nc) ) {
    ymuint8 type;
    string name;
    ClibArea area;
    s >> type
      >> name
      >> area;

    ShString shname(name);

    // 入力ピンの読み込み
    SizeType ni;
    s >> ni;
    vector<CiInputPin*> input_list(ni);
    for ( auto i: Range(ni) ) {
      string name;
      ClibCapacitance cap;
      ClibCapacitance r_cap;
      ClibCapacitance f_cap;
      s >> name
	>> cap
	>> r_cap
	>> f_cap;
      input_list[i] = new_cell_input(ShString(name), cap, r_cap, f_cap);
    }

    // 出力ピンの読み込み
    SizeType no;
    s >> no;
    vector<CiOutputPin*> output_list(no);
    for ( auto i: Range(no) ) {
      string name;
      bool has_logic;
      Expr logic_expr;
      Expr tristate_expr;
      ClibCapacitance max_f;
      ClibCapacitance min_f;
      ClibCapacitance max_c;
      ClibCapacitance min_c;
      ClibTime max_t;
      ClibTime min_t;
      s >> name
	>> has_logic;
      logic_expr.restore(s);
      tristate_expr.restore(s);
      s >> max_f
	>> min_f
	>> max_c
	>> min_c
	>> max_t
	>> min_t;
      output_list[i] = new_cell_output(ShString(name),
				       has_logic, logic_expr, tristate_expr,
				       max_f, min_f,
				       max_c, min_c,
				       max_t, min_t);
    }

    // 入出力ピンの読み込み
    SizeType nio;
    s >> nio;
    vector<CiInoutPin*> inout_list(nio);
    for ( auto i: Range(nio) ) {
      string name;
      bool has_logic;
      Expr logic_expr;
      Expr tristate_expr;
      ClibCapacitance cap;
      ClibCapacitance r_cap;
      ClibCapacitance f_cap;
      ClibCapacitance max_f;
      ClibCapacitance min_f;
      ClibCapacitance max_c;
      ClibCapacitance min_c;
      ClibTime max_t;
      ClibTime min_t;
      s >> name
	>> has_logic;
      logic_expr.restore(s);
      tristate_expr.restore(s);
      s >> cap
	>> r_cap
	>> f_cap
	>> max_f
	>> min_f
	>> max_c
	>> min_c
	>> max_t
	>> min_t;
      inout_list[i] = new_cell_inout(ShString(name),
				     has_logic, logic_expr, tristate_expr,
				     cap, r_cap, f_cap,
				     max_f, min_f,
				     max_c, min_c,
				     max_t, min_t);
    }

    // 内部ピンの読み込み
    SizeType nit;
    s >> nit;
    vector<CiInternalPin*> internal_list(nit);
    for ( auto i: Range(nit) ) {
      string name;
      s >> name;
      internal_list[i] = new_cell_internal(ShString(name));
    }

    // バスピンの読み込み
    SizeType nbus;
    s >> nbus;
    vector<CiBus*> bus_list(nbus);

    // バンドルピンの読み込み
    SizeType nbundle;
    s >> nbundle;
    vector<CiBundle*> bundle_list(nbundle);

    // タイミング情報の読み込み
    vector<CiTiming*> timing_list = restore_timing(s);

    // セル本体の読み込み
    CiCell* cell = nullptr;
    switch ( type ) {
    case 0: // kLogic
      cell = new_logic_cell(shname, area,
			    input_list,
			    output_list,
			    inout_list,
			    bus_list,
			    bundle_list,
			    timing_list);
      break;

    case 1: // kFF
      {
	Expr next_state;
	Expr clocked_on;
	Expr clocked_on_also;
	Expr clear;
	Expr preset;
	ymuint8 clear_preset_var1;
	ymuint8 clear_preset_var2;
	next_state.restore(s);
	clocked_on.restore(s);
	clocked_on_also.restore(s);
	clear.restore(s);
	preset.restore(s);
	s >> clear_preset_var1
	  >> clear_preset_var2;
	cell = new_ff_cell(shname, area,
			   input_list,
			   output_list,
			   inout_list,
			   bus_list,
			   bundle_list,
			   timing_list,
			   next_state,
			   clocked_on, clocked_on_also,
			   clear, preset,
			   clear_preset_var1,
			   clear_preset_var2);
      }
      break;

    case 2: // kLatch
      {
	Expr data_in;
	Expr enable;
	Expr enable_also;
	Expr clear;
	Expr preset;
	ymuint8 clear_preset_var1;
	ymuint8 clear_preset_var2;
	data_in.restore(s);
	enable.restore(s);
	enable_also.restore(s);
	clear.restore(s);
	preset.restore(s);
	s >> clear_preset_var1
	  >> clear_preset_var2;
	cell = new_latch_cell(shname, area,
			      input_list,
			      output_list,
			      inout_list,
			      bus_list,
			      bundle_list,
			      timing_list,
			      data_in,
			      enable, enable_also,
			      clear, preset,
			      clear_preset_var1,
			      clear_preset_var2);
      }
      break;

    case 3: // kFSM
      cell = new_fsm_cell(shname, area,
			  input_list,
			  output_list,
			  inout_list,
			  internal_list,
			  bus_list,
			  bundle_list,
			  timing_list);
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    mCellList[cell_id] = unique_ptr<CiCell>{cell};
    mCellHash.emplace(cell->name(), cell);

    // 個別の条件ごとのタイミング情報の設定
    for ( int ipos: Range(ni + nio) ) {
      for ( int opos: Range(no + nio) ) {
	auto timing_list1 = restore_tid_list(s);
	cell->set_timing(ipos, opos, ClibTimingSense::positive_unate, timing_list1);

	auto timing_list2 = restore_tid_list(s);
	cell->set_timing(ipos, opos, ClibTimingSense::negative_unate, timing_list2);
      }
    }
  }
}

// @brief セルグループを読み込む．
void
CiCellLibrary::restore_cell_group(
  istream& s
)
{
  SizeType ng;
  s >> ng;
  mGroupList.clear();
  mGroupList.reserve(ng);
  for ( auto g: Range(ng) ) {
    NpnMapM npnmap;
    int pininfo;
    SizeType cell_num;
    npnmap.restore(s);
    s >> pininfo
      >> cell_num;
    vector<CiCell*> cell_list(cell_num);
    for ( auto i: Range(cell_num) ) {
      SizeType cell_id;
      s >> cell_id;
      cell_list[i] = mCellList[cell_id].get();
    }
    auto group = new_cell_group(g, npnmap, pininfo, cell_list);
    mGroupList.push_back(unique_ptr<CiCellGroup>{group});
  }
}

// @brief セルクラスを読み込む．
void
CiCellLibrary::restore_cell_class(
  istream& s
)
{
  SizeType nc;
  s >> nc;
  mClassList.clear();
  mClassList.reserve(nc);
  for ( auto c: Range(nc) ) {
    SizeType idmap_num;
    s >> idmap_num;
    vector<NpnMapM> idmap_list(idmap_num);
    for ( auto i: Range(idmap_num) ) {
      idmap_list[i].restore(s);
    }

    SizeType group_num;
    s >> group_num;
    vector<CiCellGroup*> group_list(group_num);
    for ( auto i: Range(group_num) ) {
      SizeType group_id;
      s >> group_id;
      group_list[i] = mGroupList[group_id].get();
    }
    auto cclass = new_cell_class(c, idmap_list, group_list);
    mClassList.push_back(unique_ptr<CiCellClass>{cclass});
  }
}

// @brief タイミング情報を読み込む．
vector<CiTiming*>
CiCellLibrary::restore_timing(
  istream& s
)
{
  SizeType nt;
  s >> nt;
  vector<CiTiming*> timing_list;
  timing_list.reserve(nt);
  for ( auto tid: Range(nt) ) {
    ymuint8 ttype;
    ymuint8 tmp;
    Expr cond;
    s >> ttype
      >> tmp;
    cond.restore(s);

    CiTiming* timing = nullptr;
    ClibTimingType timing_type = static_cast<ClibTimingType>(tmp);
    switch ( ttype ) {
    case 0:
      {
	ClibTime i_r;
	ClibTime i_f;
	ClibTime s_r;
	ClibTime s_f;
	ClibResistance r_r;
	ClibResistance f_r;
	s >> i_r
	  >> i_f
	  >> s_r
	  >> s_f
	  >> r_r
	  >> f_r;
	timing = new_timing_generic(timing_type,
				    cond,
				    i_r, i_f,
				    s_r, s_f,
				    r_r, f_r);
      }
      break;

    case 1:
      {
#if 0 // 不明
	ClibTime i_r;
	ClibTime i_f;
	ClibTime s_r;
	ClibTime s_f;
	s >> i_r
	  >> i_f
	  >> s_r
	  >> s_f;
	timing = new_timing_piecewise(timing_type,
				      cond,
				      i_r, i_f,
				      s_r, s_f);
#endif
      }
      break;

    case 2:
      {
	CiLut* cell_rise = restore_lut(s);
	CiLut* cell_fall = restore_lut(s);
	CiLut* rise_transition = restore_lut(s);
	CiLut* fall_transition = restore_lut(s);
	timing = new_timing_lut1(timing_type,
				 cond,
				 cell_rise,
				 cell_fall,
				 rise_transition,
				 fall_transition);
      }
      break;

    case 3:
      {
	CiLut* rise_transition = restore_lut(s);
	CiLut* fall_transition = restore_lut(s);
	CiLut* rise_propagation = restore_lut(s);
	CiLut* fall_propagation = restore_lut(s);
	timing = new_timing_lut1(timing_type,
				 cond,
				 rise_transition,
				 fall_transition,
				 rise_propagation,
				 fall_propagation);
      }
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    timing_list.push_back(timing);
  }

  return timing_list;
}

// @brief LUT を読み込む．
CiLut*
CiCellLibrary::restore_lut(
  istream& s
)
{
  SizeType templ_id;
  s >> templ_id;
  if ( templ_id == CLIB_NULLID ) {
    return nullptr;
  }

  const ClibLutTemplate& templ = lu_table_template(templ_id);

  SizeType d = templ.dimension();
  switch ( d ) {
  case 1:
    {
      ymuint8 n;
      s >> n;
      vector<double> index_array(n);
      for ( auto i: Range(n) ) {
	double val;
	s >> val;
	index_array[i] = val;
      }

      vector<double> value_array(n);
      for ( auto i: Range(n) ) {
	double val;
	s >> val;
	value_array[i] = val;
      }
      return new_lut1(&templ,
		      value_array,
		      index_array);
    }

  case 2:
    {
      ymuint8 n1;
      s >> n1;
      vector<double> index_array1(n1);
      for ( auto i: Range(n1) ) {
	double val;
	s >> val;
	index_array1[i] = val;
      }

      ymuint8 n2;
      s >> n2;
      vector<double> index_array2(n2);
      for ( auto i: Range(n2) ) {
	double val;
	s >> val;
	index_array2[i] = val;
      }

      SizeType n = n1 * n2;
      vector<double> value_array(n);
      for ( auto i: Range(n) ) {
	double val;
	s >> val;
	value_array[i] = val;
      }
      return new_lut2(&templ,
		      value_array,
		      index_array1,
		      index_array2);
    }

  case 3:
    {
      ymuint8 n1;
      s >> n1;
      vector<double> index_array1(n1);
      for ( auto i: Range(n1) ) {
	double val;
	s >> val;
	index_array1[i] = val;
      }

      ymuint8 n2;
      s	>> n2;
      vector<double> index_array2(n2);
      for ( auto i: Range(n2) ) {
	double val;
	s >> val;
	index_array2[i] = val;
      }

      ymuint8 n3;
      s >> n3;
      vector<double> index_array3(n3);
      for ( auto i: Range(n3) ) {
	double val;
	s >> val;
	index_array3[i] = val;
      }

      int n = n1 * n2 * n3;
      vector<double> value_array(n);
      for ( auto i: Range(n) ) {
	double val;
	s >> val;
	value_array[i] = val;
      }

      return new_lut3(&templ,
		      value_array,
		      index_array1,
		      index_array2,
		      index_array3);
    }

  default:
    ASSERT_NOT_REACHED;
    break;
  }
  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatMgr
//////////////////////////////////////////////////////////////////////

// @brief データを読み込んでセットする．
bool
CiPatMgr::restore(
  istream& bis
)
{
  // ノードと枝の情報を読み込む．
  SizeType nn;
  bis >> nn;
  set_node_num(nn);
  for ( auto i: Range(node_num()) ) {
    bis >> mNodeTypeArray[i]
	>> mEdgeArray[i * 2]
	>> mEdgeArray[i * 2 + 1];
    if ( node_type(i) == ClibPatType::Input ) {
      ASSERT_COND( input_id(i) == i );
    }
  }

  // パタングラフの情報を読み込む．
  SizeType np;
  bis >> np;
  set_pat_num(np);
  for ( auto id: Range(pat_num()) ) {
    mPatArray[id].restore(bis);
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief バイナリファイルを読み込む．
void
CiPatGraph::restore(
  istream& bis
)
{
  SizeType ne;

  bis >> mRepId
      >> mInputNum
      >> ne;
  mEdgeList.clear();
  mEdgeList.resize(ne);
  for ( auto i: Range(ne) ) {
    bis >> mEdgeList[i];
  }
}

END_NAMESPACE_YM_CLIB
