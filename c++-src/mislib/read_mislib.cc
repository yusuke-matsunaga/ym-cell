﻿
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
CiTiming*
new_timing(
  const MislibPin* pt_pin, // パース木のピン情報
  CiCellLibrary* library   // ライブラリ
)
{
  ClibTime       r_i{pt_pin->rise_block_delay()->num()};
  ClibResistance r_r{pt_pin->rise_fanout_delay()->num()};
  ClibTime       f_i{pt_pin->fall_block_delay()->num()};
  ClibResistance f_r{pt_pin->fall_fanout_delay()->num()};
  auto timing = library->new_timing_generic(
    ClibTimingType::combinational,
    Expr::make_one(),
    r_i, f_i,
    ClibTime(0.0), ClibTime(0.0),
    r_r, f_r
  );
  return timing;
}

// セルを作る．
void
new_gate(
  const MislibGate* gate, // パース木のゲート情報
  CiCellLibrary* library  // ライブラリ
)
{
  auto name = gate->name()->str();
  ClibArea area{gate->area()->num()};

  auto opin_name = gate->opin_name()->str();
  auto opin_expr = gate->opin_expr();

  auto npin = gate->ipin_num();
  const MislibPin* ipin_top = nullptr;
  vector<const MislibPin*> ipin_array;
  vector<ShString> ipin_name_list;
  NameMap ipin_name_map;
  bool wildcard_pin = false;
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

  // 入力ピンのリストを作る．
  auto ni = ipin_name_list.size();
  vector<CiInputPin*> input_list(ni);
  for ( auto i = 0; i < ni; ++ i ) {
    // 入力ピンの設定
    auto name = ipin_name_list[i];
    auto pin = ipin_array[i];
    ClibCapacitance load{pin->input_load()->num()};
    input_list[i] = library->new_cell_input(name, load, load, load);
  }

  // 出力ピンを作る．
  auto function = opin_expr->to_expr(ipin_name_map);
  auto opin = library->new_cell_output(opin_name,
				       true, function,
				       Expr::make_zero(),
				       ClibCapacitance::infty(),
				       ClibCapacitance(0.0),
				       ClibCapacitance::infty(),
				       ClibCapacitance(0.0),
				       ClibTime::infty(),
				       ClibTime(0.0));

  // タイミング情報の生成
  vector<CiTiming*> timing_list(ni);
  if ( wildcard_pin ) {
    // すべてのピンが同一のパラメータを持つ．
    auto timing = new_timing(ipin_top, library);
    for ( auto i = 0; i < ni; ++ i ) {
      timing_list[i] = timing;
    }
  }
  else {
    for ( auto i = 0; i < ni; ++ i ) {
      timing_list[i] = new_timing(ipin_array[i], library);
    }
  }

  // セルを作る．
  auto cell = library->new_logic_cell(name, area,
				      input_list,
				      vector<CiOutputPin*>(1, opin),
				      vector<CiInoutPin*>{},
				      vector<CiBus*>{},
				      vector<CiBundle*>{},
				      timing_list);

  auto tv_function = function.make_tv(ni);
  for ( SizeType i = 0; i < ni; ++ i ) {
    // タイミング情報の設定
    VarId var(i);
    auto pt_pin = ipin_array[i];
    auto p_func = tv_function.cofactor(var, false);
    auto n_func = tv_function.cofactor(var, true);
    auto sense_real = ClibTimingSense::non_unate;
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
      continue;
    }

    // 実際の極性情報と記述が合っているか確かめる．
    auto sense = ClibTimingSense::non_unate;
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
    if ( sense == ClibTimingSense::non_unate ) {
      cell->set_timing(i, 0, ClibTimingSense::positive_unate, {i});
      cell->set_timing(i, 0, ClibTimingSense::negative_unate, {i});
    }
    else {
      cell->set_timing(i, 0, sense, {i});
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

  // セルの内容の設定
  for ( auto& gate: gate_list ) {
    new_gate(gate.get(), lib);
  }

  lib->compile();

  return lib;
}

END_NAMESPACE_YM_CLIB
