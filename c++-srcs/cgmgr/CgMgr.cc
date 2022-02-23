
/// @file CgMgr.cc
/// @brief CgMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "cgmgr/CgMgr.h"
#include "cgmgr/CgSignature.h"
#include "CgLogicSig.h"
#include "ci/CiCellLibrary.h"
#include "ym/TvFunc.h"
#include "ym/NpnMap.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CgMgr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CgMgr::CgMgr(
  CiCellLibrary& library ///< [in] 対象のセルライブラリ
) : mLibrary{library}
{
  logic_init();
  ff_init();
  latch_init();
}

// @brief 論理セルグループの初期化を行なう．
void
CgMgr::logic_init()
{
  { // 定数0グループの登録
    auto func0 = _find_logic_group(Expr::make_zero());
    mLogicGroup[0] = func0->id();
  }
  { // 定数1グループの登録
    auto func1 = _find_logic_group(Expr::make_one());
    mLogicGroup[1] = func1->id();
  }
  { // バッファグループの登録
    Expr expr = Expr::make_posi_literal(VarId(0));
    auto func2 = _find_logic_group(expr);
    mLogicGroup[2] = func2->id();
  }
  { // インバーターグループの登録
    Expr expr = Expr::make_nega_literal(VarId(0));
    auto func3 = _find_logic_group(expr);
    mLogicGroup[3] = func3->id();
  }

  // 以降の処理は必須ではないが，
  // クラス一覧に現れる順序を統一する効果がある．

  // AND2 〜 AND8 のシグネチャを登録しておく．
  for ( auto ni: {2, 3, 4, 5, 6, 7, 8} ) {
    Expr and_expr = Expr::make_posi_literal(VarId(0));
    for ( auto i = 1; i < ni; ++ i ) {
      and_expr &= Expr::make_posi_literal(VarId(i));
    }
    _find_logic_group(and_expr);
  }

  // XOR2 〜 XOR4 のシグネチャを登録しておく．
  for ( auto ni: {2, 3, 4} ) {
    Expr xor_expr = Expr::make_posi_literal(VarId(0));
    for ( int i = 1; i < ni; ++ i ) {
      xor_expr ^= Expr::make_posi_literal(VarId(i));
    }
    _find_logic_group(xor_expr);
  }

  // MUX2 のシグネチャを登録しておく．
  {
    Expr lit0 = Expr::make_posi_literal(VarId(0));
    Expr lit1 = Expr::make_posi_literal(VarId(1));
    Expr lit2 = Expr::make_posi_literal(VarId(2));
    Expr mux2_expr = lit0 & ~lit2 | lit1 & lit2;
    _find_logic_group(mux2_expr);
  }

  // MUX4 のシグネチャを登録しておく．
  {
    Expr lit0 = Expr::make_posi_literal(VarId(0));
    Expr lit1 = Expr::make_posi_literal(VarId(1));
    Expr lit2 = Expr::make_posi_literal(VarId(2));
    Expr lit3 = Expr::make_posi_literal(VarId(3));
    Expr lit4 = Expr::make_posi_literal(VarId(4));
    Expr lit5 = Expr::make_posi_literal(VarId(5));
    Expr mux4_expr =
      lit0 & ~lit4 & ~lit5 |
      lit1 &  lit4 & ~lit5 |
      lit2 & ~lit4 &  lit5 |
      lit3 &  lit4 &  lit5;
    _find_logic_group(mux4_expr);
  }
}

// @brief FFグループの初期化を行なう．
void
CgMgr::ff_init()
{
}

// @brief ラッチグループの初期化を行なう．
void
CgMgr::latch_init()
{
}

#if 0
// @brief 一般的な組み合わせ論理用セルグループを得る．
CiCellGroup*
CgMgr::find_logic_group(
  SizeType input_num,
  SizeType output_num,
  SizeType inout_num,
  const vector<Expr>& expr_array
)
{
  // 論理式を持つ出力番号のリストを得る．
  vector<SizeType> true_output_list;
  true_output_list.reserve(output_num + inout_num);
  for ( SizeType i = 0; i < output_num + inout_num; ++ i ) {
    if ( expr_array[i].is_valid() ) {
      true_output_list.push_back(i);
    }
  }
  // 出力の論理関数のベクタを作る．
  SizeType no = true_output_list.size();
  vector<TvFunc> func_vect(no);
  for ( SizeType i = 0; i < no; ++ i ) {
    func_vect[i] = expr_array[true_output_list[i]].make_tv(input_num);
  }

  // シグネチャを作る．
  CgGenLogicSig sig{true_output_list, func_vect};

  return _find_group(sig);
#if 0

  // このシグネチャを持つグループを探す．
  if ( mGroupDict.count(sig) == 0 ) {
    // 未登録の場合
    // - このグループの属しているクラスを得る．
    //   func_fect の代表関数を求める．
    string rep_sig;
    ClibIOMap rep_map;

    auto rep_class = _find_class(rep_sig);

    // 新しいグループを作る．
    auto group = mLibrary.new_logic_group(rep_class, rep_map,
					  input_num, output_num, inout_num,
					  expr_array, tristate_array);

    // 登録する．
    mGroupDict.emplace(sig, group);
  }

  auto group = mGroupDict.at(sig);
  return group;
#endif
}

// @brief 一般的な組み合わせ論理用セルグループを得る．
CiCellGroup*
CgMgr::find_logic_group(
  SizeType input_num,
  SizeType output_num,
  SizeType inout_num,
  const vector<Expr>& expr_array,
  const vector<Expr>& tristate_array
)
{
  // シグネチャを作る．
  string sig;

  if ( mGroupDict.count(sig) == 0 ) {
    // このグループの属しているクラスを得る．
    string rep_sig;
    ClibIOMap rep_map;

    auto rep_class = _find_class(rep_sig);

    // 新しいグループを作る．
    auto group = mLibrary.new_logic_group(rep_class, rep_map,
					  input_num, output_num, inout_num,
					  expr_array, tristate_array);

    // 登録する．
    mGroupDict.emplace(sig, group);
  }

  auto group = mGroupDict.at(sig);
  return group;
}

// @brief フリップフロップ用セルグループを得る．
CiCellGroup*
CgMgr::find_ff_group(
  SizeType input_num,
  SizeType output_num,
  SizeType inout_num,
  const vector<Expr>& expr_array,
  const vector<Expr>& tristate_array,
  const Expr& clock,
  const Expr& clock2,
  const Expr& next_state,
  const Expr& clear,
  const Expr& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  // シグネチャを作る．
  string sig;

  if ( mGroupDict.count(sig) == 0 ) {
    // このグループの属しているクラスを得る．
    string rep_sig;
    ClibIOMap rep_map;

    auto rep_class = _find_class(rep_sig);

    // 新しいグループを作る．
    auto group = mLibrary.new_ff_group(rep_class, rep_map,
				       input_num, output_num, inout_num,
				       expr_array, tristate_array,
				       clock, clock2, next_state,
				       clear, preset,
				       clear_preset_var1, clear_preset_var2);

    // 登録する．
    mGroupDict.emplace(sig, group);
  }

  auto group = mGroupDict.at(sig);
  return group;
}

// @brief ラッチ用セルグループを得る．
CiCellGroup*
CgMgr::find_latch_group(
  SizeType input_num,
  SizeType output_num,
  SizeType inout_num,
  const vector<Expr>& expr_array,
  const vector<Expr>& tristate_array,
  const Expr& enable,
  const Expr& enable2,
  const Expr& data_in,
  const Expr& clear,
  const Expr& preset,
  ClibCPV clear_preset_var1,
  ClibCPV clear_preset_var2
)
{
  // シグネチャを作る．
  string sig;

  if ( mGroupDict.count(sig) == 0 ) {
    // このグループの属しているクラスを得る．
    string rep_sig;
    ClibIOMap rep_map;

    auto rep_class = _find_class(rep_sig);

    // 新しいグループを作る．
    auto group = mLibrary.new_latch_group(rep_class, rep_map,
					  input_num, output_num, inout_num,
					  expr_array, tristate_array,
					  enable, enable2, data_in,
					  clear, preset,
					  clear_preset_var1, clear_preset_var2);

    // 登録する．
    mGroupDict.emplace(sig, group);
  }

  auto group = mGroupDict.at(sig);
  return group;
}
#endif

// @brief セルを対応するグループに登録する．
CiCellGroup*
CgMgr::reg_group(
  const CiCell* cell
)
{
  // シグネチャを作る．
  auto sig = cell->make_signature();

  // sig に対応するグループを求める．
  auto group = _find_group(sig);
  // セルを登録する．
  group->add_cell(cell);

  return group;
}

// @brief 論理式から作られるシグネチャに一致するグループを探す．
// @return グループを返す．
//
// なければ作る．
CiCellGroup*
CgMgr::_find_logic_group(
  const Expr& expr
)
{
  SizeType ni = expr.input_size();
  auto f = expr.make_tv(ni);
  auto sig = CgSignature::make_logic_sig(f);
  return _find_group(sig);
}

// @brief シグネチャに一致するグループを探す．
CiCellGroup*
CgMgr::_find_group(
  const CgSignature& sig
)
{
  // シグネチャ文字列を作る．
  string sig_str = sig.str();

  // このシグネチャを持つグループを探す．
  if ( mGroupDict.count(sig_str) == 0 ) {
    // 未登録の場合
    // 代表シグネチャに対する変換を求める．
    auto rep_map = sig.rep_map();
    // 代表シグネチャを求める．
    auto rep_sig = sig.xform(rep_map);
    // クラスを求める．
    auto rep_class = _find_class(rep_sig);
    // そのクラスに新しいグループを追加する．
    auto group = mLibrary.add_cell_group(rep_class, rep_map);

    // 登録する．
    mGroupDict.emplace(sig_str, group);
    return group;
  }
  else {
    // 登録済みのグループを返す．
    auto group = mGroupDict.at(sig_str);
    return group;
  }
}

/// @brief 代表クラスを得る．
CiCellClass*
CgMgr::_find_class(
  const CgSignature& sig
)
{
  // 代表シグネチャの文字列を求める．
  auto sig_str = sig.str();
  // このシグネチャを持つクラスを探す．
  if ( mClassDict.count(sig_str) == 0 ) {
    // 同位体変換リストを作る．
    auto idmap_list = sig.idmap_list();
    // 新しいクラスを作って登録する．
    auto rep_class = mLibrary.add_cell_class(idmap_list);
    mClassDict.emplace(sig_str, rep_class);
    return rep_class;
  }
  else {
    // 登録済みのクラスを返す．
    auto rep_class = mClassDict.at(sig_str);
    return rep_class;
  }
}

END_NAMESPACE_YM_CLIB
