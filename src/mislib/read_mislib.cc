
/// @file read_mislib.cc
/// @brief read_mislib の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "mislib_nsdef.h"
#include "ci/CiCellLibrary.h"

#include "ym/ClibArea.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibResistance.h"
#include "ym/ClibTime.h"
#include "ym/ClibTiming.h"

#include "MislibParser.h"
#include "MislibMgr.h"
#include "MislibNode.h"
#include "MislibGate.h"
#include "MislibPin.h"
#include "MislibPhase.h"
#include "MislibExpr.h"
#include "MislibStr.h"
#include "MislibNum.h"

#include "ym/FileIDO.h"
#include "ym/Expr.h"
#include "ym/TvFunc.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_MISLIB

BEGIN_NONAMESPACE

typedef HashMap<ShString, int> NameMap;

// 論理式を表すパース木をスキャンして端子名のリストを作る．
// param[in] node パース木の根のノード
// param[out] name_list 名前が現れた順に格納されたリスト
// param[out] name_map 名前をキーにして name_list 中の位置を返す連想配列
void
dfs(const MislibExpr* expr,
    vector<ShString>& name_list,
    NameMap& name_map)
{
  switch ( expr->type() ) {
  case MislibExpr::Const0:
  case MislibExpr::Const1:
    return;

  case MislibExpr::VarName:
    {
      ShString name = expr->varname();
      if ( !name_map.check(name) ) {
	// 登録する．
	name_map.add(name, name_list.size());
	name_list.push_back(name);
      }
    }
    break;

  case MislibExpr::Not:
    dfs(expr->child1(), name_list, name_map);
    break;

  case MislibExpr::And:
  case MislibExpr::Or:
  case MislibExpr::Xor:
    dfs(expr->child1(), name_list, name_map);
    dfs(expr->child2(), name_list, name_map);
    break;

  default:
    ASSERT_NOT_REACHED;
  }
}

CiCell*
new_gate(const MislibGate* gate,
	 CiCellLibrary* library)
{
  ShString name = gate->name()->str();
  ClibArea area(gate->area()->num());

  ShString opin_name = gate->opin_name()->str();
  const MislibExpr* opin_expr = gate->opin_expr();

  const MislibPin* ipin_top = gate->ipin_top();
  vector<const MislibPin*> ipin_array;
  vector<ShString> ipin_name_list;
  NameMap ipin_name_map;
  bool wildcard_pin = false;
  if ( ipin_top != nullptr ) {
    if ( ipin_top->name() != nullptr ) {
      // 通常の入力ピン定義がある場合
      // ipin_list の順に入力ピンを作る．
      for ( auto pin = ipin_top; pin != nullptr; pin = pin->next() ) {
	ShString name = pin->name()->str();
	ASSERT_COND( !ipin_name_map.check(name) );
	ipin_name_map.add(name, ipin_array.size());
	ipin_array.push_back(pin);
	ipin_name_list.push_back(name);
      }
    }
    else {
      // ワイルドカードの場合
      // 論理式に現れる順に入力ピンを作る．
      wildcard_pin = true;
      dfs(opin_expr, ipin_name_list, ipin_name_map);
      for ( int i = 0; i < ipin_name_list.size(); ++ i ) {
	ipin_array.push_back(ipin_top);
      }
    }
  }

  // 入力ピンのリストを作る．
  int ni = ipin_name_list.size();
  vector<CiInputPin*> input_list(ni);
  for ( int i = 0; i < ni; ++ i ) {
    // 入力ピンの設定
    ShString name = ipin_name_list[i];
    const MislibPin* pin = ipin_array[i];
    ClibCapacitance load(pin->input_load()->num());
    input_list[i] = library->new_cell_input(name, load, load, load);
  }

  // 出力ピンを作る．
  Expr function = opin_expr->to_expr(ipin_name_map);
  CiOutputPin* opin = library->new_cell_output(opin_name,
					       true, function,
					       Expr::const_zero(),
					       ClibCapacitance::infty(),
					       ClibCapacitance(0.0),
					       ClibCapacitance::infty(),
					       ClibCapacitance(0.0),
					       ClibTime::infty(),
					       ClibTime(0.0));

  // タイミング情報の生成
  vector<CiTiming*> timing_list(ni);
  if ( !wildcard_pin ) {
    for ( int i = 0; i < ni; ++ i ) {
      const MislibPin* pt_pin = ipin_array[i];
      ClibTime r_i(pt_pin->rise_block_delay()->num());
      ClibResistance r_r(pt_pin->rise_fanout_delay()->num());
      ClibTime f_i(pt_pin->fall_block_delay()->num());
      ClibResistance f_r(pt_pin->fall_fanout_delay()->num());
      CiTiming* timing = library->new_timing_generic(ClibTimingType::Combinational,
						     Expr::const_one(),
						     r_i, f_i,
						     ClibTime(0.0), ClibTime(0.0),
						     r_r, f_r);
      timing_list[i] = timing;
    }
  }
  else {
    vector<CiTiming*> timing_list(1);
    const MislibPin* pt_pin = ipin_top;
    ClibTime r_i(pt_pin->rise_block_delay()->num());
    ClibResistance r_r(pt_pin->rise_fanout_delay()->num());
    ClibTime f_i(pt_pin->fall_block_delay()->num());
    ClibResistance f_r(pt_pin->fall_fanout_delay()->num());
    CiTiming* timing = library->new_timing_generic(ClibTimingType::Combinational,
						   Expr::const_one(),
						   r_i, f_i,
						   ClibTime(0.0), ClibTime(0.0),
						   r_r, f_r);
    for ( int i = 0; i < ni; ++ i ) {
      timing_list[i] = timing;
    }
  }

  // セルを作る．
  CiCell* cell = library->new_logic_cell(name, area,
					 input_list,
					 vector<CiOutputPin*>(1, opin),
					 vector<CiInoutPin*>(),
					 vector<CiBus*>(),
					 vector<CiBundle*>(),
					 timing_list);

  TvFunc tv_function = function.make_tv(ni);
  for ( int i = 0; i < ni; ++ i ) {
    // タイミング情報の設定
    VarId var(i);
    const MislibPin* pt_pin = ipin_array[i];
    TvFunc p_func = tv_function.cofactor(var, false);
    TvFunc n_func = tv_function.cofactor(var, true);
    ClibTimingSense sense_real = ClibTimingSense::NonUnate;
    bool redundant = false;
    if ( ~p_func && n_func ) {
      if ( ~n_func && p_func ) {
	sense_real = ClibTimingSense::NonUnate;
      }
      else {
	sense_real = ClibTimingSense::NegaUnate;
      }
    }
    else {
      if ( ~n_func && p_func ) {
	sense_real = ClibTimingSense::PosiUnate;
      }
      else {
	// つまり p_func == n_func ということ．
	// つまりこの変数は出力に影響しない．
	ostringstream buf;
	buf << "The output function does not depend on the input pin, "
	    << pt_pin->name()->str() << ".";
	MsgMgr::put_msg(__FILE__, __LINE__,
			pt_pin->loc(),
			MsgType::Warning,
			"MISLIB_PARSER",
			buf.str());
	redundant = true;
      }
    }

    if ( redundant ) {
      continue;
    }

    ClibTimingSense sense = ClibTimingSense::NonUnate;
    switch ( pt_pin->phase()->type() ) {
    case MislibPhase::Noninv:  sense = ClibTimingSense::PosiUnate; break;
    case MislibPhase::Inv:     sense = ClibTimingSense::NegaUnate; break;
    case MislibPhase::Unknown: sense = ClibTimingSense::NonUnate; break;
    default: ASSERT_NOT_REACHED; break;
    }
    if ( sense != sense_real ) {
      ostringstream buf;
      buf << "Phase description does not match the logic expression. "
	  << "Ignored.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      pt_pin->phase()->loc(),
		      MsgType::Warning,
		      "MISLIB_PARSER",
		      buf.str());
      sense = sense_real;
    }
    if ( sense == ClibTimingSense::NonUnate ) {
      library->set_timing(cell, i, 0, ClibTimingSense::PosiUnate,
			  vector<CiTiming*>(1, timing_list[i]));
      library->set_timing(cell, i, 0, ClibTimingSense::NegaUnate,
			  vector<CiTiming*>(1, timing_list[i]));
    }
    else {
      library->set_timing(cell, i, 0, sense,
			  vector<CiTiming*>(1, timing_list[i]));
    }
  }

  return cell;
}

// @brief MislibNode から ClibCellLibrary に設定する．
// @param[in] lib_name ライブラリ名
// @param[in] gate_list パース木のルート
// @param[in] library 設定対象のライブラリ
void
set_library(const string& lib_name,
	    const vector<const MislibGate*>& gate_list,
	    CiCellLibrary* library)
{
  // 名前の設定
  library->set_name(lib_name);

  // セルの内容の設定
  vector<CiCell*> cell_list;
  for ( auto gate: gate_list ) {
    CiCell* cell = new_gate(gate, library);
    cell_list.push_back(cell);
  }

  library->set_cell_list(cell_list);
}

END_NONAMESPACE

END_NAMESPACE_YM_MISLIB


BEGIN_NAMESPACE_YM_CLIB

// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
// @param[in] filename ファイル名
// @param[in] library 設定対象のライブラリ
// @return 読み込みが成功したら true を返す．
bool
CiCellLibrary::read_mislib(const string& filename)
{
  using namespace nsMislib;

  FileIDO ido;
  if ( !ido.open(filename) ) {
    // エラー
    ostringstream buf;
    buf << filename << " : No such file.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(),
		    MsgType::Failure,
		    "MISLIB_PARSER",
		    buf.str());
    return false;
  }

  MislibMgr mgr;
  MislibParser parser(ido, mgr);
  vector<const MislibGate*> gate_list;
  if ( !parser.parse(gate_list) ) {
    return false;
  }

  set_library(filename, gate_list, this);

  return true;
}

END_NAMESPACE_YM_CLIB
