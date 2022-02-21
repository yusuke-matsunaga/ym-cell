
/// @file read_mislib.cc
/// @brief read_mislib の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "mislib_nsdef.h"
#include "ci/CiCellLibrary.h"

#include "ym/ClibArea.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibResistance.h"
#include "ym/ClibTime.h"
#include "ym/ClibTiming.h"

#include "MislibParser.h"
#include "MislibNode.h"
#include "MislibGate.h"
#include "MislibExpr.h"

#include "ym/Expr.h"
#include "ym/TvFunc.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_MISLIB

BEGIN_NONAMESPACE

using NameMap = unordered_map<ShString, int>;

// 論理式を表すパース木をスキャンして端子名のリストを作る．
void
dfs(
  const MislibExpr* expr,      ///< [in] パース木の根のノード
  vector<ShString>& name_list, ///< [out] 名前が現れた順に格納されたリスト
  NameMap& name_map            ///< [out] 名前をキーにして name_list 中の位置を返す連想配列
)
{
  switch ( expr->type() ) {
  case MislibExpr::Const0:
  case MislibExpr::Const1:
    return;

  case MislibExpr::VarName:
    {
      ShString name = expr->varname();
      if ( name_map.count(name) == 0 ) {
	// 登録する．
	name_map[name] = name_list.size();
	name_list.push_back(name);
      }
    }
    break;

  case MislibExpr::Not:
    dfs(expr->opr1(), name_list, name_map);
    break;

  case MislibExpr::And:
  case MislibExpr::Or:
  case MislibExpr::Xor:
    dfs(expr->opr1(), name_list, name_map);
    dfs(expr->opr2(), name_list, name_map);
    break;

  default:
    ASSERT_NOT_REACHED;
  }
}

// タイミング情報を作る．
SizeType
add_timing(
  const MislibPin* pt_pin, // パース木のピン情報
  CiCell* cell             // 対象のセル
)
{
  ClibTime       r_i{pt_pin->rise_block_delay()->num()};
  ClibResistance r_r{pt_pin->rise_fanout_delay()->num()};
  ClibTime       f_i{pt_pin->fall_block_delay()->num()};
  ClibResistance f_r{pt_pin->fall_fanout_delay()->num()};
  auto tid = cell->add_timing_generic(
    ClibTimingType::combinational,
    Expr::make_one(),
    r_i, f_i,
    ClibTime(0.0), ClibTime(0.0),
    r_r, f_r
  );
  return tid;
}

// timing 情報をセットする．
void
set_timing(
  const MislibPin* pt_pin,   // パース木のピン情報
  const TvFunc& tv_function, // 出力の関数
  SizeType ipos,             // 入力ピン番号
  SizeType opos,             // 出力ピン番号(常に0だけど念の為)
  CiCell* cell,              // 対象のセル
  SizeType timing_id         // タイミング番号
)
{
  VarId var{ipos};
  auto p_func = tv_function.cofactor(var, false);
  auto n_func = tv_function.cofactor(var, true);
  auto sense_real = ClibTimingSense::none;
  if ( ~p_func && n_func ) {
    if ( ~n_func && p_func ) {
      sense_real = ClibTimingSense::non_unate;
    }
    else {
      sense_real = ClibTimingSense::negative_unate;
    }
  }
  else if ( ~n_func && p_func ) {
    sense_real = ClibTimingSense::positive_unate;
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
    // タイミング情報は設定しない．
    return;
  }

  // 実際の極性情報と記述が合っているか確かめる．
  auto sense = ClibTimingSense::none;
  switch ( pt_pin->phase()->type() ) {
  case MislibPhase::Noninv:  sense = ClibTimingSense::positive_unate; break;
  case MislibPhase::Inv:     sense = ClibTimingSense::negative_unate; break;
  case MislibPhase::Unknown: sense = ClibTimingSense::non_unate; break;
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

  vector<SizeType> timing_list{timing_id};
  if ( sense == ClibTimingSense::non_unate ) {
    cell->set_timing(ipos, opos, ClibTimingSense::positive_unate, timing_list);
    cell->set_timing(ipos, opos, ClibTimingSense::negative_unate, timing_list);
  }
  else {
    cell->set_timing(ipos, opos, sense, timing_list);
  }
}

// セルを作る．
void
new_gate(
  const MislibGate* gate, // パース木のゲート情報
  CiCellLibrary* lib
)
{
  auto name = gate->name()->str();
  ClibArea area{gate->area()->num()};

  auto opin_name = gate->opin_name()->str();
  auto opin_expr = gate->opin_expr();

  auto npin = gate->ipin_num();
  const MislibPin* ipin_top{nullptr};
  vector<const MislibPin*> ipin_array;

  // 機能情報の取得
  vector<ShString> ipin_name_list;
  bool wildcard_pin = false;
  NameMap ipin_name_map;
  if ( npin > 0 ) {
    ipin_top = gate->ipin(0);
    if ( ipin_top->name() != nullptr ) {
      // 通常の入力ピン定義がある場合
      // ipin_list の順に入力ピンを作る．
      for ( int i = 0; i < npin; ++ i ) {
	auto pin = gate->ipin(i);
	ShString name = pin->name()->str();
	ASSERT_COND( ipin_name_map.count(name) == 0 );
	ipin_name_map[name] = ipin_array.size();
	ipin_array.push_back(pin);
	ipin_name_list.push_back(name);
      }
    }
    else {
      // ワイルドカードの場合
      // 論理式に現れる順に入力ピンを作る．
      wildcard_pin = true;
      dfs(opin_expr, ipin_name_list, ipin_name_map);
      for ( auto i = 0; i < ipin_name_list.size(); ++ i ) {
	ipin_array.push_back(ipin_top);
      }
    }
  }

  // 入力ピン数
  auto ni = ipin_name_list.size();

  // セルを作る．
  auto cell = lib->add_logic_cell(name, area);

  // 入力ピンのリストを作る．
  vector<CiInputPin*> input_list(ni);
  for ( auto i = 0; i < ni; ++ i ) {
    // 入力ピンの設定
    auto name = ipin_name_list[i];
    auto pin = ipin_array[i];
    ClibCapacitance load{pin->input_load()->num()};
    auto ipin = cell->add_input(name, load, load, load);
    ASSERT_COND( ipin->input_id() == i );
  }

  // 出力の論理式
  auto oexpr = opin_expr->to_expr(ipin_name_map);

  // 出力ピンを作る．
  auto opin = cell->add_output(opin_name,
			       ClibCapacitance::infty(),
			       ClibCapacitance(0.0),
			       ClibCapacitance::infty(),
			       ClibCapacitance(0.0),
			       ClibTime::infty(),
			       ClibTime(0.0),
			       oexpr, Expr::make_zero());

  auto opin_id = opin->output_id();

  // タイミング情報の生成
  cell->init_timing_map();
  auto tv_function = oexpr.make_tv(ni);
  if ( wildcard_pin ) {
    // すべてのピンが同一のパラメータを持つ．
    auto pt_pin = ipin_top;
    auto tid = add_timing(ipin_top, cell);
    for ( SizeType i = 0; i < ni; ++ i ) {
      set_timing(pt_pin, tv_function, i, opin_id, cell, tid);
    }
  }
  else {
    // ピンごとに個別のパラメータを持つ．
    for ( SizeType i = 0; i < ni; ++ i ) {
      auto pt_pin = ipin_array[i];
      auto tid = add_timing(pt_pin, cell);
      set_timing(pt_pin, tv_function, i, opin_id, cell, tid);
    }
  }
}

END_NONAMESPACE

END_NAMESPACE_YM_MISLIB


BEGIN_NAMESPACE_YM_CLIB

// @brief mislib 形式のファイルを読み込んでライブラリに設定する．
// @return 読み込みが成功したら true を返す．
CiCellLibrary*
CiCellLibrary::read_mislib(
  const string& filename ///< [in] filename ファイル名
)
{
  using namespace nsMislib;

  MislibParser parser;
  vector<MislibGatePtr> gate_list;
  if ( !parser.parse(filename, gate_list) ) {
    return nullptr;
  }

  auto lib = new CiCellLibrary{};

  // ファイル名をライブラリ名として登録する．
  lib->set_name(filename);

  // セルを作る．
  for ( auto& gate: gate_list ) {
    new_gate(gate.get(), lib);
  }

  return lib;
}

END_NAMESPACE_YM_CLIB
