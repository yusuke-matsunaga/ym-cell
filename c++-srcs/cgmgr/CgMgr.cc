
/// @file CgMgr.cc
/// @brief CgMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "cgmgr/CgMgr.h"
#include "cgmgr/CgSignature.h"
#include "ci/CiCellLibrary.h"
#include "ci/CiSeqInfo.h"
#include "ym/TvFunc.h"
#include "ym/NpnMap.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CgMgr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CgMgr::CgMgr(
  CiCellLibrary& library ///< [in] 対象のセルライブラリ
) : mLibrary{library},
    mSimpleFFClass(CiSeqInfo::max_index(), CLIB_NULLID),
    mSimpleLatchClass(CiSeqInfo::max_index(), CLIB_NULLID)
{
  for ( SizeType i = 0; i < 4; ++ i ) {
    mLogicGroup[i] = -1;
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
    auto sig = CgSignature::make_logic_sig(TvFunc::make_zero(0));
    auto func0 = find_group(sig);
    mLogicGroup[0] = func0->id();
  }
  { // 定数1グループの登録
    auto sig = CgSignature::make_logic_sig(TvFunc::make_one(0));
    auto func1 = find_group(sig);
    mLogicGroup[1] = func1->id();
  }
  { // バッファグループの登録
    auto sig = CgSignature::make_logic_sig(TvFunc::make_posi_literal(1, VarId{0}));
    auto func2 = find_group(sig);
    mLogicGroup[2] = func2->id();
  }
  { // インバーターグループの登録
    auto sig = CgSignature::make_logic_sig(TvFunc::make_nega_literal(1, VarId{0}));
    auto func3= find_group(sig);
    mLogicGroup[3] = func3->id();
  }

  // 以降の処理は必須ではないが，
  // クラス一覧に現れる順序を統一する効果がある．

  // AND2 〜 AND8 のシグネチャを登録しておく．
  for ( auto ni: {2, 3, 4, 5, 6, 7, 8} ) {
    auto and_func = TvFunc::make_posi_literal(ni, VarId{0});
    for ( SizeType i = 1; i < ni; ++ i ) {
      and_func &= TvFunc::make_posi_literal(ni, VarId{i});
    }
    auto sig = CgSignature::make_logic_sig(and_func);
    find_group(sig);
  }

  // XOR2 〜 XOR4 のシグネチャを登録しておく．
  for ( auto ni: {2, 3, 4} ) {
    auto xor_func = TvFunc::make_posi_literal(ni, VarId{0});
    for ( SizeType i = 1; i < ni; ++ i ) {
      xor_func ^= TvFunc::make_posi_literal(ni, VarId{i});
    }
    auto sig = CgSignature::make_logic_sig(xor_func);
    find_group(sig);
  }

  // MUX2 のシグネチャを登録しておく．
  {
    SizeType ni = 3;
    auto lit0 = TvFunc::make_posi_literal(ni, VarId(0));
    auto lit1 = TvFunc::make_posi_literal(ni, VarId(1));
    auto lit2 = TvFunc::make_posi_literal(ni, VarId(2));
    auto mux2_func = lit0 & ~lit2 | lit1 & lit2;
    auto sig = CgSignature::make_logic_sig(mux2_func);
    find_group(sig);
  }

  // MUX4 のシグネチャを登録しておく．
  {
    SizeType ni = 6;
    auto lit0 = TvFunc::make_posi_literal(ni, VarId(0));
    auto lit1 = TvFunc::make_posi_literal(ni, VarId(1));
    auto lit2 = TvFunc::make_posi_literal(ni, VarId(2));
    auto lit3 = TvFunc::make_posi_literal(ni, VarId(3));
    auto lit4 = TvFunc::make_posi_literal(ni, VarId(4));
    auto lit5 = TvFunc::make_posi_literal(ni, VarId(5));
    auto mux4_func =
      lit0 & ~lit4 & ~lit5 |
      lit1 &  lit4 & ~lit5 |
      lit2 & ~lit4 &  lit5 |
      lit3 &  lit4 &  lit5;
    auto sig = CgSignature::make_logic_sig(mux4_func);
    find_group(sig);
  }
}

// @brief FFグループの初期化を行なう．
void
CgMgr::ff_init()
{
  for ( SizeType index = 0; index < CiSeqInfo::max_index(); ++ index ) {
    auto info = CiSeqInfo::decode_index(index);
    // 入力
    // 0: data-in
    // 1: clock
    // 2: clear (optional)
    // 3: preset (optional)
    // 4: q
    // 5: iq
    SizeType ni = 2;
    if ( info.has_clear() ) {
      ++ ni;
    }
    if ( info.has_preset() ) {
      ++ ni;
    }
    SizeType xni = ni + 2; // IQ, XIQ の分を足す．
    auto next = TvFunc::make_posi_literal(xni, VarId{0});
    auto clock = TvFunc::make_posi_literal(xni, VarId{1});
    auto clock2 = TvFunc::make_invalid();
    if ( info.has_slave_clock() ) {
      clock2 = TvFunc::make_nega_literal(xni, VarId{1});
    }
    auto clear = TvFunc::make_invalid();
    SizeType base = 2;
    if ( info.has_clear() ) {
      clear = TvFunc::make_posi_literal(xni, VarId{base});
      ++ base;
    }
    auto preset = TvFunc::make_invalid();
    if ( info.has_preset() ) {
      preset = TvFunc::make_posi_literal(xni, VarId{base});
      ++ base;
    }
    auto qvar = TvFunc::make_posi_literal(xni, VarId{base});
    vector<TvFunc> func_list{qvar};
    vector<TvFunc> tristate_list{TvFunc::make_invalid()};
    auto cpv1 = info.clear_preset_var1();
    auto cpv2 = info.clear_preset_var2();
    auto sig = CgSignature::make_ff_sig(ni, 1, 0,
					func_list, tristate_list,
					clock, clock2, next,
					clear, preset,
					cpv1, cpv2);
    auto g = find_group(sig);
    mSimpleFFClass[index] = g->rep_class().id();
  }
}

// @brief ラッチグループの初期化を行なう．
void
CgMgr::latch_init()
{
  for ( SizeType index = 0; index < CiSeqInfo::max_index(); ++ index ) {
    auto info = CiSeqInfo::decode_index(index);
    // 入力
    // 0: data-in
    // 1: enable
    // 2: clear (optional)
    // 3: preset (optional)
    // 4: q
    // 5: q~
    SizeType ni = 2;
    if ( info.has_clear() ) {
      ++ ni;
    }
    if ( info.has_preset() ) {
      ++ ni;
    }
    vector<TvFunc> func_list{TvFunc::make_posi_literal(ni, VarId{ni - 2})};
    vector<TvFunc> tristate_list{TvFunc::make_invalid()};
    auto enable = TvFunc::make_posi_literal(ni, VarId{1});
    auto enable2 = TvFunc::make_invalid();
    if ( info.has_slave_clock() ) {
      enable2 = TvFunc::make_nega_literal(ni, VarId{1});
    }
    auto data = TvFunc::make_posi_literal(ni, VarId{0});
    SizeType base = 2;
    auto clear = TvFunc::make_invalid();
    if ( info.has_clear() ) {
      clear = TvFunc::make_posi_literal(ni, VarId{base});
      ++ base;
    }
    auto preset = TvFunc::make_invalid();
    if ( info.has_preset() ) {
      preset = TvFunc::make_posi_literal(ni, VarId{base});
    }
    auto cpv1 = info.clear_preset_var1();
    auto cpv2 = info.clear_preset_var2();
    auto sig = CgSignature::make_latch_sig(ni - 2, 1, 0, func_list, tristate_list,
					   enable, enable2, data,
					   clear, preset,
					   cpv1, cpv2);
    auto g = find_group(sig);
    mSimpleLatchClass[index] = g->rep_class().id();
  }
}

// @brief FFクラス番号を得る．
SizeType
CgMgr::ff_class(
  bool master_slave,
  bool has_clear,
  bool has_preset,
  ClibCPV cpv1,
  ClibCPV cpv2
) const
{
  CiSeqInfo info{master_slave, has_clear, has_preset, cpv1, cpv2};
  return mSimpleFFClass[info.encode_val()];
}

// @brief ラッチクラス番号を得る．
SizeType
CgMgr::latch_class(
  bool master_slave,
  bool has_clear,
  bool has_preset,
  ClibCPV cpv1,
  ClibCPV cpv2
) const
{
  CiSeqInfo info{master_slave, has_clear, has_preset, cpv1, cpv2};
  return mSimpleLatchClass[info.encode_val()];
}

// @brief シグネチャに一致するグループを探す．
CiCellGroup*
CgMgr::find_group(
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

END_NAMESPACE_YM_CLIB
