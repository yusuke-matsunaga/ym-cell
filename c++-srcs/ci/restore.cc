
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
#include "ci/CiPin.h"
#include "ci/CiBus.h"
#include "ci/CiBundle.h"
#include "ci/CiTiming.h"
#include "ci/CiLutTemplate.h"
#include "ci/CiLut.h"
#include "ci/CiPatMgr.h"
#include "ci/CiPatGraph.h"
#include "ym/ClibIOMap.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

void
CiCellLibrary::restore(
  istream& is
)
{
  BinDec bs{is};

  string name;
  bs >> name;

  set_name(name);

  ymuint8 tmp1;
  ymuint8 tmp2;
  bs >> tmp1
    >> tmp2;
  ClibTechnology technology = static_cast<ClibTechnology>(tmp1);
  ClibDelayModel delay_model = static_cast<ClibDelayModel>(tmp2);

  set_technology(technology);
  set_delay_model(delay_model);

  string bus_naming_style;
  bs >> bus_naming_style;

  set_attr("bus_naming_style", bus_naming_style);

  string date;
  bs >> date;

  set_attr("date", date);

  string revision;
  bs >> revision;

  set_attr("revision", revision);

  string comment;
  bs >> comment;

  set_attr("comment", comment);

  string time_unit;
  bs >> time_unit;

  set_attr("time_unit", time_unit);

  string voltage_unit;
  bs >> voltage_unit;

  set_attr("voltage_unit", voltage_unit);

  string current_unit;
  bs >> current_unit;

  set_attr("current_unit", current_unit);

  string pulling_resistance_unit;
  bs >> pulling_resistance_unit;

  set_attr("pulling_resistance_unit", pulling_resistance_unit);

  double capacitive_unit;
  string capacitive_unit_str;
  bs >> capacitive_unit
     >> capacitive_unit_str;

  set_capacitive_load_unit(capacitive_unit, capacitive_unit_str);

  string leakage_power_unit;
  bs >> leakage_power_unit;

  set_attr("leakage_power_unit", leakage_power_unit);

  // LUTテンプレート情報の読み込み
  {
    SizeType lut_num;
    bs >> lut_num;
    for ( auto _: Range(lut_num) ) {
      restore_lut_template(bs);
    }
  }

  // セル情報の読み込み
  {
    SizeType nc;
    bs >> nc;
    mCellList.clear();
    mRefCellList.clear();
    mCellHash.clear();
    mCellList.reserve(nc);
    mRefCellList.reserve(nc);
    for ( auto cell_id: Range(nc) ) {
      restore_cell(bs);
    }
  }

  // セルグループ情報の読み込み
  {
    SizeType ng;
    bs >> ng;
    mGroupList.clear();
    mGroupList.reserve(ng);
    for ( auto _: Range(ng) ) {
      restore_cell_group(bs);
    }
  }

  // セルクラス情報の読み込み
  {
    SizeType nc;
    bs >> nc;
    mClassList.clear();
    mClassList.reserve(nc);
    for ( SizeType _: Range(nc) ) {
      cout << "  #" << _ << endl;
      restore_cell_class(bs);
    }
  }

  // 組み込み型の設定
  for ( auto id: Range(4) ) {
    SizeType group_id;
    bs >> group_id;
    mLogicGroup[id] = mGroupList[group_id].get();
  }
  for ( auto id: Range(6) ) {
    SizeType class_id;
    bs >> class_id;
    mSimpleFFClass[id] = mClassList[class_id].get();
  }
  for ( auto id: Range(50) ) {
    SizeType class_id;
    bs >> class_id;
    mCpvFFClass[id] = mClassList[class_id].get();
  }
  for ( auto id: Range(6) ) {
    SizeType class_id;
    bs >> class_id;
    mSimpleLatchClass[id] = mClassList[class_id].get();
  }
  for ( auto id: Range(50) ) {
    SizeType class_id;
    bs >> class_id;
    mCpvLatchClass[id] = mClassList[class_id].get();
  }

  // パタングラフの情報の設定
  mPatMgr.restore(bs);
}

BEGIN_NONAMESPACE

ClibVarType
restore_1dim(
  BinDec& s,
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
  BinDec& s
)
{
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
    tmpl = add_lut_template1(shname,
			     var_type1, index_array1);
    break;

  case 2:
    var_type1 = restore_1dim(s, index_array1);
    var_type2 = restore_1dim(s, index_array2);
    tmpl = add_lut_template2(shname,
			     var_type1, index_array1,
			     var_type2, index_array2);
    break;

  case 3:
    var_type1 = restore_1dim(s, index_array1);
    var_type2 = restore_1dim(s, index_array2);
    var_type3 = restore_1dim(s, index_array3);
    tmpl = add_lut_template3(shname,
			     var_type1, index_array1,
			     var_type2, index_array2,
			     var_type3, index_array3);
    break;
  }
}

// @brief セルを読み込む．
void
CiCellLibrary::restore_cell(
  BinDec& s
)
{
  ymuint8 type;
  string name;
  ClibArea area;
  s >> type
    >> name
    >> area;

  ShString shname(name);

  cout << "restore_cell: " << name << endl;

  // セル本体の読み込み
  CiCell* cell{nullptr};
  switch ( type ) {
  case 0:
    cell = add_logic_cell(shname, area);
    break;
  case 1:
    {
      string var1;
      string var2;
      Expr clocked_on;
      Expr clocked_on_also;
      Expr next_state;
      Expr clear;
      Expr preset;
      ymuint8 clear_preset_var1;
      ymuint8 clear_preset_var2;
      s >> var1 >> var2;
      clocked_on.restore(s);
      clocked_on_also.restore(s);
      next_state.restore(s);
      clear.restore(s);
      preset.restore(s);
      s >> clear_preset_var1
	>> clear_preset_var2;
      cell = add_ff_cell(shname, area,
			 ShString{var1}, ShString{var2},
			 clocked_on, clocked_on_also, next_state,
			 clear, preset,
			 static_cast<ClibCPV>(clear_preset_var1),
			 static_cast<ClibCPV>(clear_preset_var2));
    }
    break;
  case 2:
    {
      string var1;
      string var2;
      Expr enable;
      Expr enable_also;
      Expr data_in;
      Expr clear;
      Expr preset;
      ymuint8 clear_preset_var1;
      ymuint8 clear_preset_var2;
      s >> var1 >> var2;
      enable.restore(s);
      enable_also.restore(s);
      data_in.restore(s);
      clear.restore(s);
      preset.restore(s);
      s >> clear_preset_var1
	>> clear_preset_var2;
      cell = add_latch_cell(shname, area,
			    ShString{var1}, ShString{var2},
			    enable, enable_also, data_in,
			    clear, preset,
			    static_cast<ClibCPV>(clear_preset_var1),
			    static_cast<ClibCPV>(clear_preset_var2));
    }
    break;
  case 3:
    {
    }
    break;
  }

  // 入力ピンの読み込み
  SizeType ni;
  s >> ni;
  for ( auto _: Range(ni) ) {
    string name;
    ClibCapacitance cap;
    ClibCapacitance r_cap;
    ClibCapacitance f_cap;
    s >> name
      >> cap
      >> r_cap
      >> f_cap;
    cell->add_input(ShString(name), cap, r_cap, f_cap);
  }

  // 出力ピンの読み込み
  SizeType no;
  s >> no;
  for ( auto _: Range(no) ) {
    string name;
    ClibCapacitance max_f;
    ClibCapacitance min_f;
    ClibCapacitance max_c;
    ClibCapacitance min_c;
    ClibTime max_t;
    ClibTime min_t;
    Expr logic_expr;
    Expr tristate_expr;
    s >> name
      >> max_f
      >> min_f
      >> max_c
      >> min_c
      >> max_t
      >> min_t;
    logic_expr.restore(s);
    tristate_expr.restore(s);
    cell->add_output(ShString(name),
		     max_f, min_f,
		     max_c, min_c,
		     max_t, min_t,
		     logic_expr,
		     tristate_expr);
  }

  // 入出力ピンの読み込み
  SizeType nio;
  s >> nio;
  for ( auto _: Range(nio) ) {
    string name;
    ClibCapacitance cap;
    ClibCapacitance r_cap;
    ClibCapacitance f_cap;
    ClibCapacitance max_f;
    ClibCapacitance min_f;
    ClibCapacitance max_c;
    ClibCapacitance min_c;
    ClibTime max_t;
    ClibTime min_t;
    Expr logic_expr;
    Expr tristate_expr;
    s >> name
      >> cap
      >> r_cap
      >> f_cap
      >> max_f
      >> min_f
      >> max_c
      >> min_c
      >> max_t
      >> min_t;
    logic_expr.restore(s);
    tristate_expr.restore(s);
    cell->add_inout(ShString(name),
		    cap, r_cap, f_cap,
		    max_f, min_f,
		    max_c, min_c,
		    max_t, min_t,
		    logic_expr,
		    tristate_expr);
  }

  // 内部ピンの読み込み
  SizeType nit;
  s >> nit;
  for ( auto _: Range(nit) ) {
    string name;
    s >> name;
    cell->add_internal(ShString(name));
  }

  // バスピンの読み込み
  SizeType nbus;
  s >> nbus;
  for ( auto _: Range(nbus) ) {
    ;
  }

  // バンドルピンの読み込み
  SizeType nbundle;
  s >> nbundle;
  for ( auto _: Range(nbundle) ) {
    ;
  }

  cell->init_timing_map(cell->input_num2(), cell->output_num2());

  // タイミング情報の読み込み
  SizeType nt;
  s >> nt;
  for ( auto tid: Range(nt) ) {
    restore_timing(cell, s);
  }

  // 個別の条件ごとのタイミング情報の設定
  for ( int ipos: Range(ni + nio) ) {
    for ( int opos: Range(no + nio) ) {
      for ( auto sense: { ClibTimingSense::positive_unate, ClibTimingSense::negative_unate } ) {
	SizeType nt;
	s >> nt;
	vector<SizeType> timing_id_list;
	timing_id_list.reserve(nt);
	for ( auto _: Range(nt) ) {
	  SizeType id;
	  s >> id;
	  timing_id_list.push_back(id);
	}
	cell->set_timing(ipos, opos, sense, timing_id_list);
      }
    }
  }
}

// @brief セルグループを読み込む．
void
CiCellLibrary::restore_cell_group(
  BinDec& s
)
{
  SizeType rep_id;
  s >> rep_id;
  ClibIOMap iomap;
  iomap.restore(s);

  auto rep_class = mRefClassList[rep_id];
  auto group = add_cell_group(rep_class, iomap);

  SizeType cell_num;
  s >> cell_num;
  for ( auto _: Range(cell_num) ) {
    SizeType cell_id;
    s >> cell_id;
    group->add_cell(mRefCellList[cell_id]);
  }
}

// @brief セルクラスを読み込む．
void
CiCellLibrary::restore_cell_class(
  BinDec& s
)
{
  SizeType idmap_num;
  s >> idmap_num;
  vector<ClibIOMap> idmap_list(idmap_num);
  for ( auto i: Range(idmap_num) ) {
    idmap_list[i].restore(s);
  }
  auto cclass = add_cell_class(idmap_list);

  SizeType group_num;
  s >> group_num;
  vector<CiCellGroup*> group_list(group_num);
  for ( auto i: Range(group_num) ) {
    SizeType group_id;
    s >> group_id;
    cclass->add_group(mRefGroupList[group_id]);
  }
}

// @brief タイミング情報を読み込む．
void
CiCellLibrary::restore_timing(
  CiCell* cell,
  BinDec& s
)
{
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
      cell->add_timing_generic(timing_type,
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
      cell->add_timing_lut1(timing_type,
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
      cell->add_timing_lut2(timing_type,
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
}

// @brief LUT を読み込む．
CiLut*
CiCellLibrary::restore_lut(
  BinDec& s
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
  BinDec& bis
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
  BinDec& bis
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
