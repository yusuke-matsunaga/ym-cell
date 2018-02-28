
/// @file CiCellLibrary_restore.cc
/// @brief CiCellLibrary の実装ファイル(restore()関係)
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

//////////////////////////////////////////////////////////////////////
// クラス CiCellLibrary
//////////////////////////////////////////////////////////////////////

void
CiCellLibrary::restore(IDO& s)
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
  vector<CiCell*> cell_list;
  restore_cell(s, cell_list);

  // コンパイル情報は直接 restore するので
  // LibComp を呼ぶ必要はない．
  set_cell_list(cell_list, false);

  // セルグループ情報の読み込み
  vector<CiCellGroup*> group_list;
  restore_cell_group(s, cell_list, group_list);
  mGroupList.init(group_list, mAlloc);

  // セルクラス情報の読み込み
  vector<CiCellClass*> class_list;
  restore_cell_class(s, group_list, class_list);
  mClassList.init(class_list, mAlloc);

  // 組み込み型の設定
  for ( int i = 0; i < 4; ++ i ) {
    int group_id;
    s >> group_id;
    mLogicGroup[i] = group_list[group_id];
  }
  for ( int i = 0; i < 4; ++ i ) {
    int class_id;
    s >> class_id;
    mFFClass[i] = class_list[class_id];
  }
  for ( int i = 0; i < 4; ++ i ) {
    int class_id;
    s >> class_id;
    mLatchClass[i] = class_list[class_id];
  }

  // パタングラフの情報の設定
  mPatMgr.restore(s);
}

BEGIN_NONAMESPACE

ClibVarType
restore_1dim(IDO& s,
	     vector<double>& index_array)
{
  ymuint8 tmp;
  s >> tmp;
  ClibVarType var_type = static_cast<ClibVarType>(tmp);
  ymuint8 n;
  s >> n;
  index_array.resize(n);
  for ( int i = 0; i < n; ++ i ) {
    s >> index_array[i];
  }
  return var_type;
}

END_NONAMESPACE

// @brief LUT テンプレートを読み込む．
void
CiCellLibrary::restore_lut_template(IDO& s)
{
  int lut_num;
  s >> lut_num;
  vector<CiLutTemplate*> template_list(lut_num);
  for ( int id = 0; id < lut_num; ++ id ) {
    string name;
    ymuint8 d;
    s >> name
      >> d;
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
      tmpl = new_lut_template1(name,
			       var_type1, index_array1);
      break;

    case 2:
      var_type1 = restore_1dim(s, index_array1);
      var_type2 = restore_1dim(s, index_array2);
      tmpl = new_lut_template2(name,
			       var_type1, index_array1,
			       var_type2, index_array2);
      break;

    case 3:
      var_type1 = restore_1dim(s, index_array1);
      var_type2 = restore_1dim(s, index_array2);
      var_type3 = restore_1dim(s, index_array3);
      tmpl = new_lut_template3(name,
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

void
restore_tid_list(IDO& s,
		 const vector<CiTiming*>& global_timing_list,
		 vector<CiTiming*>& timing_list)
{
  int n;
  s >> n;
  timing_list.resize(n);
  for ( int i = 0; i < n; ++ i ) {
    int tid;
    s >> tid;
    timing_list[i] = global_timing_list[tid];
  }
}

END_NONAMESPACE

// @brief セルを読み込む．
void
CiCellLibrary::restore_cell(IDO& s,
			    vector<CiCell*>& cell_list)
{
  int nc;
  s >> nc;
  cell_list.resize(nc);
  for ( int cell_id = 0; cell_id < nc; ++ cell_id ) {
    ymuint8 type;
    string name;
    ClibArea area;
    s >> type
      >> name
      >> area;

    // 入力ピンの読み込み
    int ni;
    s >> ni;
    vector<CiInputPin*> input_list(ni);
    for ( int i = 0; i < ni; ++ i ) {
      string name;
      ClibCapacitance cap;
      ClibCapacitance r_cap;
      ClibCapacitance f_cap;
      s >> name
	>> cap
	>> r_cap
	>> f_cap;
      input_list[i] = new_cell_input(name, cap, r_cap, f_cap);
    }

    // 出力ピンの読み込み
    int no;
    s >> no;
    vector<CiOutputPin*> output_list(no);
    for ( int i = 0; i < no; ++ i ) {
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
	>> has_logic
	>> logic_expr
	>> tristate_expr
	>> max_f
	>> min_f
	>> max_c
	>> min_c
	>> max_t
	>> min_t;
      output_list[i] = new_cell_output(name,
				       has_logic, logic_expr, tristate_expr,
				       max_f, min_f,
				       max_c, min_c,
				       max_t, min_t);
    }

    // 入出力ピンの読み込み
    int nio;
    s >> nio;
    vector<CiInoutPin*> inout_list(nio);
    for ( int i = 0; i < nio; ++ i ) {
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
	>> has_logic
	>> logic_expr
	>> tristate_expr
	>> cap
	>> r_cap
	>> f_cap
	>> max_f
	>> min_f
	>> max_c
	>> min_c
	>> max_t
	>> min_t;
      inout_list[i] = new_cell_inout(name,
				     has_logic, logic_expr, tristate_expr,
				     cap, r_cap, f_cap,
				     max_f, min_f,
				     max_c, min_c,
				     max_t, min_t);
    }

    // 内部ピンの読み込み
    int nit;
    s >> nit;
    vector<CiInternalPin*> internal_list(nit);
    for ( int i = 0; i < nit; ++ i ) {
      string name;
      s >> name;
      internal_list[i] = new_cell_internal(name);
    }

    // バスピンの読み込み
    int nbus;
    s >> nbus;
    vector<CiBus*> bus_list(nbus);

    // バンドルピンの読み込み
    int nbundle;
    s >> nbundle;
    vector<CiBundle*> bundle_list(nbundle);

    CiCell* cell = nullptr;
    switch ( type ) {
    case 0: // kLogic
      cell = new_logic_cell(name, area,
			    input_list,
			    output_list,
			    inout_list,
			    bus_list,
			    bundle_list);
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
	s >> next_state
	  >> clocked_on
	  >> clocked_on_also
	  >> clear
	  >> preset
	  >> clear_preset_var1
	  >> clear_preset_var2;
	cell = new_ff_cell(name, area,
			   input_list,
			   output_list,
			   inout_list,
			   bus_list,
			   bundle_list,
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
	s >> data_in
	  >> enable
	  >> enable_also
	  >> clear
	  >> preset
	  >> clear_preset_var1
	  >> clear_preset_var2;
	cell = new_latch_cell(name, area,
			      input_list,
			      output_list,
			      inout_list,
			      bus_list,
			      bundle_list,
			      data_in,
			      enable, enable_also,
			      clear, preset,
			      clear_preset_var1,
			      clear_preset_var2);
      }
      break;

    case 3: // kFSM
      cell = new_fsm_cell(name, area,
			  input_list,
			  output_list,
			  inout_list,
			  internal_list,
			  bus_list,
			  bundle_list);
      break;

    default:
      ASSERT_NOT_REACHED;
      break;
    }
    cell_list[cell_id] = cell;

    // タイミング情報の生成
    vector<CiTiming*> timing_list;
    restore_timing(s, timing_list);
    set_timing_list(cell, timing_list);

    // 個別の条件ごとのタイミング情報の設定
    for ( int ipos = 0; ipos < ni + nio; ++ ipos ) {
      for ( int opos = 0; opos < no + nio; ++ opos ) {
	vector<CiTiming*> timing_list1;
	restore_tid_list(s, timing_list, timing_list1);
	set_timing(cell, ipos, opos, kClibPosiUnate, timing_list1);

	vector<CiTiming*> timing_list2;
	restore_tid_list(s, timing_list, timing_list2);
	set_timing(cell, ipos, opos, kClibNegaUnate, timing_list2);
      }
    }
  }
}

// @brief セルグループを読み込む．
void
CiCellLibrary::restore_cell_group(IDO& s,
				  const vector<CiCell*>& global_cell_list,
				  vector<CiCellGroup*>& group_list)
{
  int ng;
  s >> ng;
  group_list.resize(ng);
  for ( int g = 0; g < ng; ++ g ) {
    NpnMapM npnmap;
    ymuint pininfo;
    int cell_num;
    s >> npnmap
      >> pininfo
      >> cell_num;
    vector<CiCell*> cell_list(cell_num);
    for ( int i = 0; i < cell_num; ++ i ) {
      int cell_id;
      s >> cell_id;
      cell_list[i] = global_cell_list[cell_id];
    }
    group_list[g] = new_cell_group(g, npnmap, pininfo, cell_list);
  }
}

// @brief セルクラスを読み込む．
void
CiCellLibrary::restore_cell_class(IDO& s,
				  const vector<CiCellGroup*>& global_group_list,
				  vector<CiCellClass*>& class_list)
{
  int nc;
  s >> nc;
  class_list.resize(nc);
  for ( int c = 0; c < nc; ++ c ) {
    int idmap_num;
    s >> idmap_num;
    vector<NpnMapM> idmap_list(idmap_num);
    for ( int i = 0; i < idmap_num; ++ i ) {
      s >> idmap_list[i];
    }

    int group_num;
    s >> group_num;
    vector<CiCellGroup*> group_list(group_num);
    for ( int i = 0; i < group_num; ++ i ) {
      int group_id;
      s >> group_id;
      group_list[i] = global_group_list[group_id];
    }
    class_list[c] = new_cell_class(c, idmap_list, group_list);
  }
}

// @brief タイミング情報を読み込む．
void
CiCellLibrary::restore_timing(IDO& s,
			      vector<CiTiming*>& timing_list)
{
  int nt;
  s >> nt;
  timing_list.clear();
  timing_list.reserve(nt);
  for ( int tid = 0; tid < nt; ++ tid ) {
    ymuint8 ttype;
    ymuint8 tmp;
    Expr cond;
    s >> ttype
      >> tmp
      >> cond;

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
#if 0
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
	ClibLut* cell_rise = restore_lut(s);
	ClibLut* cell_fall = restore_lut(s);
	ClibLut* rise_transition = restore_lut(s);
	ClibLut* fall_transition = restore_lut(s);
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
	ClibLut* rise_transition = restore_lut(s);
	ClibLut* fall_transition = restore_lut(s);
	ClibLut* rise_propagation = restore_lut(s);
	ClibLut* fall_propagation = restore_lut(s);
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
}

// @brief LUT を読み込む．
ClibLut*
CiCellLibrary::restore_lut(IDO& s)
{
  string template_name;
  s >> template_name;
  if ( template_name == string() ) {
    return nullptr;
  }

  const ClibLutTemplate* templ = lu_table_template(template_name.c_str());
  ASSERT_COND( templ != nullptr );

  int d = templ->dimension();
  switch ( d ) {
  case 1:
    {
      ymuint8 n;
      s >> n;
      vector<double> index_array(n);
      for ( int i = 0; i < n; ++ i ) {
	double val;
	s >> val;
	index_array[i] = val;
      }

      vector<double> value_array(n);
      for ( int i = 0; i < n; ++ i ) {
	double val;
	s >> val;
	value_array[i] = val;
      }
      return new_lut1(templ,
		      value_array,
		      index_array);
    }

  case 2:
    {
      ymuint8 n1;
      s >> n1;
      vector<double> index_array1(n1);
      for ( int i = 0; i < n1; ++ i ) {
	double val;
	s >> val;
	index_array1[i] = val;
      }

      ymuint8 n2;
      s >> n2;
      vector<double> index_array2(n2);
      for ( int i = 0; i < n2; ++ i ) {
	double val;
	s >> val;
	index_array2[i] = val;
      }

      ymuint n = n1 * n2;
      vector<double> value_array(n);
      for ( int i = 0; i < n; ++ i ) {
	double val;
	s >> val;
	value_array[i] = val;
      }
      return new_lut2(templ,
		      value_array,
		      index_array1,
		      index_array2);
    }

  case 3:
    {
      ymuint8 n1;
      s >> n1;
      vector<double> index_array1(n1);
      for ( int i = 0; i < n1; ++ i ) {
	double val;
	s >> val;
	index_array1[i] = val;
      }

      ymuint8 n2;
      s	>> n2;
      vector<double> index_array2(n2);
      for ( int i = 0; i < n2; ++ i ) {
	double val;
	s >> val;
	index_array2[i] = val;
      }

      ymuint8 n3;
      s >> n3;
      vector<double> index_array3(n3);
      for ( int i = 0; i < n3; ++ i ) {
	double val;
	s >> val;
	index_array3[i] = val;
      }

      ymuint n = n1 * n2 * n3;
      vector<double> value_array(n);
      for ( int i = 0; i < n; ++ i ) {
	double val;
	s >> val;
	value_array[i] = val;
      }

      return new_lut3(templ,
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
// @param[in] bis 入力元のストリーム
// @retval true 読み込みが成功した．
// @retval false 読み込みが失敗した．
bool
CiPatMgr::restore(IDO& bis)
{
  // ノードと枝の情報を読み込む．
  ymuint32 nn;
  bis >> nn;
  set_node_num(nn);
  for ( int i = 0; i < nn; ++ i ) {
    bis >> mNodeTypeArray[i]
	>> mEdgeArray[i * 2]
	>> mEdgeArray[i * 2 + 1];
    if ( node_type(i) == kClibPatInput ) {
      ASSERT_COND( input_id(i) == i );
    }
  }

  // パタングラフの情報を読み込む．
  ymuint32 np;
  bis >> np;
  set_pat_num(np);
  for ( int id = 0; id < mPatNum; ++ id ) {
    mPatArray[id].restore(bis, mAlloc);
  }

  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief バイナリファイルを読み込む．
// @param[in] bis 入力元のストリーム
void
CiPatGraph::restore(IDO& bis,
		    Alloc& alloc)
{
  bis >> mRepId
      >> mInputNum
      >> mEdgeNum;
  alloc_array(alloc);
  for ( int i = 0; i < mEdgeNum; ++ i ) {
    bis >> mEdgeList[i];
  }
}

END_NAMESPACE_YM_CLIB
