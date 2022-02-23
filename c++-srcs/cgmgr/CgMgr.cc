
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
  for ( SizeType i = 0; i < 4; ++ i ) {
    mLogicGroup[i] = -1;
  }
  for ( SizeType i = 0; i < 6; ++ i ) {
    mSimpleFFClass[i] = -1;
  }
  for ( SizeType i = 0; i < 50; ++ i ) {
    mCpvFFClass[i] = -1;
  }
  for ( SizeType i = 0; i < 6; ++ i ) {
    mSimpleLatchClass[i] = -1;
  }
  for ( SizeType i = 0; i < 50; ++ i ) {
    mCpvLatchClass[i] = -1;
  }

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
  for ( bool master_slave: { false, true } ) {
    for ( bool has_clear: { false, true } ) {
      for ( bool has_preset: { false, true } ) {
	if ( has_clear && has_preset ) {
	  for ( auto cpv1: { ClibCPV::L, ClibCPV::H, ClibCPV::N, ClibCPV::T, ClibCPV::X } ) {
	    for ( auto cpv2: { ClibCPV::L, ClibCPV::H, ClibCPV::N, ClibCPV::T, ClibCPV::X } ) {
	      SizeType idx;
	      SizeType sub_idx;
	      encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2, idx, sub_idx);
	      auto g = _find_ff_group(master_slave, has_clear, has_preset, cpv1, cpv2);
	      mCpvFFClass[sub_idx] = g->rep_class().id();
	    }
	  }
	}
	else {
	  SizeType idx;
	  SizeType sub_idx;
	  encode_attr(master_slave, has_clear, has_preset, ClibCPV::X, ClibCPV::X, idx, sub_idx);
	  auto g = _find_ff_group(master_slave, has_clear, has_preset, ClibCPV::X, ClibCPV::X);
	  mSimpleFFClass[idx] = g->rep_class().id();
	}
      }
    }
  }
}

// @brief ラッチグループの初期化を行なう．
void
CgMgr::latch_init()
{
  for ( bool master_slave: { false, true } ) {
    for ( bool has_clear: { false, true } ) {
      for ( bool has_preset: { false, true } ) {
	if ( has_clear && has_preset ) {
	  for ( auto cpv1: { ClibCPV::L, ClibCPV::H, ClibCPV::N, ClibCPV::T, ClibCPV::X } ) {
	    for ( auto cpv2: { ClibCPV::L, ClibCPV::H, ClibCPV::N, ClibCPV::T, ClibCPV::X } ) {
	      SizeType idx;
	      SizeType sub_idx;
	      encode_attr(master_slave, has_clear, has_preset, cpv1, cpv2, idx, sub_idx);
	      auto g = _find_latch_group(master_slave, has_clear, has_preset, cpv1, cpv2);
	      mCpvLatchClass[sub_idx] = g->rep_class().id();
	    }
	  }
	}
	else {
	  SizeType idx;
	  SizeType sub_idx;
	  encode_attr(master_slave, has_clear, has_preset, ClibCPV::X, ClibCPV::X, idx, sub_idx);
	  auto g = _find_latch_group(master_slave, has_clear, has_preset, ClibCPV::X, ClibCPV::X);
	  mSimpleLatchClass[idx] = g->rep_class().id();
	}
      }
    }
  }
}

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

// @brief FFのシグネチャに一致するグループを探す．
CiCellGroup*
CgMgr::_find_ff_group(
  bool master_slave,
  bool has_clear,
  bool has_preset,
  ClibCPV cpv1,
  ClibCPV cpv2
)
{
  SizeType ni = 2; // clockとnext_state
  SizeType no = 1; // q
  SizeType nb = 0;
  if ( master_slave ) {
    // clock2
    ++ ni;
  }
  if ( has_clear ) {
    // clear
    ++ ni;
  }
  if ( has_preset ) {
    // preset
    ++ ni;
  }
  vector<TvFunc> func_list{TvFunc::make_posi_literal(ni + 2, VarId{ni})};
  vector<TvFunc> tristate_list{TvFunc::make_zero(ni + 2)};
  SizeType id = 0;
  TvFunc clock = TvFunc::make_posi_literal(ni + 2, VarId{id});
  ++ id;
  TvFunc clock2 = TvFunc::make_zero(0);
  if ( master_slave ) {
    clock2 = TvFunc::make_posi_literal(ni + 2, VarId{id});
    ++ id;
  }
  TvFunc next_state = TvFunc::make_posi_literal(ni + 2, VarId{id});
  ++ id;
  TvFunc clear = TvFunc::make_zero(0);
  if ( has_clear ) {
    clear = TvFunc::make_posi_literal(ni + 2, VarId{id});
    ++ id;
  }
  TvFunc preset = TvFunc::make_zero(0);
  if ( has_preset ) {
    preset = TvFunc::make_posi_literal(ni + 2, VarId{id});
    ++ id;
  }
  auto sig = CgSignature::make_ff_sig(ni, no, nb, func_list, tristate_list,
				      clock, clock2, next_state,
				      clear, preset, cpv1, cpv2);
  return _find_group(sig);
}

// @brief ラッチのシグネチャに一致するグループを探す．
CiCellGroup*
CgMgr::_find_latch_group(
  bool master_slave,
  bool has_clear,
  bool has_preset,
  ClibCPV cpv1,
  ClibCPV cpv2
)
{
  SizeType ni = 2; // clockとnext_state
  SizeType no = 1; // q
  SizeType nb = 0;
  if ( master_slave ) {
    // clock2
    ++ ni;
  }
  if ( has_clear ) {
    // clear
    ++ ni;
  }
  if ( has_preset ) {
    // preset
    ++ ni;
  }
  vector<TvFunc> func_list{TvFunc::make_posi_literal(ni + 2, VarId{ni})};
  vector<TvFunc> tristate_list{TvFunc::make_zero(ni + 2)};
  SizeType id = 0;
  TvFunc clock = TvFunc::make_posi_literal(ni + 2, VarId{id});
  ++ id;
  TvFunc clock2 = TvFunc::make_zero(0);
  if ( master_slave ) {
    clock2 = TvFunc::make_posi_literal(ni + 2, VarId{id});
    ++ id;
  }
  TvFunc next_state = TvFunc::make_posi_literal(ni + 2, VarId{id});
  ++ id;
  TvFunc clear = TvFunc::make_zero(0);
  if ( has_clear ) {
    clear = TvFunc::make_posi_literal(ni + 2, VarId{id});
    ++ id;
  }
  TvFunc preset = TvFunc::make_zero(0);
  if ( has_preset ) {
    preset = TvFunc::make_posi_literal(ni + 2, VarId{id});
    ++ id;
  }
  auto sig = CgSignature::make_latch_sig(ni, no, nb, func_list, tristate_list,
					 clock, clock2, next_state,
					 clear, preset, cpv1, cpv2);
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
    // グループを作る．
    auto group = mLibrary.add_cell_group(rep_class, rep_map);
    // そのクラスに新しいグループを追加する．
    rep_class->add_group(group);

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

// @brief FF/ラッチの属性をエンコードする．
void
CgMgr::encode_attr(
  bool master_slave,
  bool has_clear,
  bool has_preset,
  ClibCPV cpv1,
  ClibCPV cpv2,
  SizeType& idx,
  SizeType& sub_idx
)
{
  idx = 0;
  sub_idx = 0;
  if ( master_slave ) {
    idx += 1;
  }
  if ( has_clear ) {
    idx += 2;
  }
  if ( has_preset ) {
    idx += 4;
  }
  if ( idx >= 6 ) {
    if ( idx == 6 ) {
      sub_idx = 25;
    }
    sub_idx += static_cast<SizeType>(cpv1) * 5;
    sub_idx += static_cast<SizeType>(cpv2);
  }
}

END_NAMESPACE_YM_CLIB
