
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
}

#if 0
// @brief 1出力の組み合わせ論理用セルグループを得る．
CiCellGroup*
CgMgr::find_logic_group(
  SizeType input_num,
  const Expr& expr
)
{
  // 論理関数を作る．
  auto func = expr.make_tv(input_num);

  // シグネチャを作る．
  CgLogicSig sig{func};

  return _find_group(sig);
#if 0
  // シグネチャを作る．
  string sig = make_signature(func);

  // このシグネチャを持つグループを探す．
  if ( mGroupDict.count(sig) == 0 ) {
    // 未登録の場合
    // - このグループの属しているクラスを得る．
    //   func の代表関数を求める．
    auto npnmap = func.npn_cannonical_map();
    auto rep_func = func.xform(npnmap);
    string rep_sig = make_signature(rep_func);
    ClibIOMap rep_map = from_npnmap(npnmap);

    auto rep_class = _find_class(rep_sig);

    // - そのクラスに新しいグループを追加する．
    auto group = mLibrary.new_logic_group(rep_class, rep_map, input_num, expr);

    // 登録する．
    mGroupDict.emplace(sig, group);
    return group;
  }
  else {
    // 登録済みのグループを返す．
    auto group = mGroupDict.at(sig);
    return group;
  }
#endif
}
#endif

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

// @brief グループを得る．
//
// なければ作る．
CiCellGroup*
CgMgr::_find_group(
  const CgSignature& sig ///< [in] シグネチャ
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
