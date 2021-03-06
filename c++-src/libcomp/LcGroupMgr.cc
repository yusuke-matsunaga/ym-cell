﻿
/// @file LcGroupMgr.cc
/// @brief LcGroupMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "lc/LcGroupMgr.h"
#include "lc/LcClass.h"
#include "lc/LcGroup.h"
#include "lc/LcSignature.h"
#include "lc/LibComp.h"
#include "ym/Clib.h"
#include "ym/MFSet.h"
#include "ym/PermGen.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcGroupMgr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] libcomp 親の LibComp
LcGroupMgr::LcGroupMgr(LibComp& libcomp) :
  mLibComp(libcomp)
{
}

// @brief デストラクタ
LcGroupMgr::~LcGroupMgr()
{
  clear();
}

// @brief 内容を空にする．
void
LcGroupMgr::clear()
{
  mGroupMap.clear();
  mClassMap.clear();
}

// @brief セルを追加する．
void
LcGroupMgr::add_cell(Clib* cell)
{
  if ( !cell->has_logic() || cell->output_num2() == 0 ) {
    // ひとつでも論理式を持たない出力があるセルは独立したグループとなる．
    LcGroup* fgroup = mLibComp.new_group();
    fgroup->add_cell(cell);

    int ni = cell->input_num2();
    int no = cell->output_num2();
    LcClass* fclass = mLibComp.new_class(LcSignature(), false);
    NpnMapM xmap;
    xmap.set_identity(ni, no);
    fclass->add_group(fgroup, xmap);
  }
  else {
    // セルのシグネチャ関数を作る．
    LcSignature sig(cell);

    // sig に対するセルグループを求める．
    LcGroup* fgroup = find_group(sig, false);

    // セル(番号)を追加する．
    fgroup->add_cell(cell);
  }
}

// @brief f に対応する LcGroup を求める．
// @param[in] sig シグネチャ
// @param[in] builtin 組み込みクラスの時 true にするフラグ
// @note なければ新規に作る．
LcGroup*
LcGroupMgr::find_group(const LcSignature& sig,
		       bool builtin)
{
  string sig_str = sig.str();
  int fgid;
  if ( mGroupMap.find(sig_str, fgid) ) {
    // 既に登録されていた．
    return mLibComp.group(fgid);
  }

  // なかったので新たに作る．
  LcGroup* fgroup = mLibComp.new_group();
  mGroupMap.add(sig_str, fgroup->id());

  // 代表関数を求める．
  LcSignature rep_sig;
  NpnMapM xmap;
  find_rep(sig, rep_sig, xmap);

  string rep_sig_str = rep_sig.str();
  LcClass* fclass = nullptr;
  int fcid;
  if ( mClassMap.find(rep_sig_str, fcid) ) {
    // 登録されていた．
    fclass = mLibComp.npn_class(fcid);
  }
  else {
    // まだ登録されていない．
    LcClass* fclass = mLibComp.new_class(rep_sig, builtin);
    mClassMap.add(rep_sig_str, fclass->id());
    find_idmap_list(rep_sig, fclass->mIdmapList);
  }

  // グループを追加する．
  fclass->add_group(fgroup, xmap);

  return fgroup;
}

#if 0
BEGIN_NONAMESPACE

// サポートを表すビットベクタを作る．
int
gen_support(const TvFunc& f)
{
  int ni = f.input_num();
  int ans = 0U;
  for (int i = 0; i < ni; ++ i) {
    VarId var(i);
    if ( f.check_sup(var) ) {
      ans |= (1U << i);
    }
  }
  return ans;
}

// f を最大化する変換を求める．
int
gen_maxmap(const LcSignature& sig,
	   int offset,
	   NpnMapM& xmap)
{
  int ni = f.input_num();
  int no = f.output_num();

  vector<VarId> i_list;
  i_list.reserve(ni);
  for (int i = 0; i < ni; ++ i) {
    VarId var(i);
    if ( f.check_sup(var) ) {
      i_list.push_back(var);
    }
  }
  int ni1 = i_list.size();
  if ( ni1 == 0 ) {
    return 0;
  }

  NpnMapM map;
  bool first = true;
  TvFuncM repfunc;
  int nip = 1U << ni1;
  for (PermGen pg(ni1, ni1); !pg.is_end(); ++ pg) {
    NpnMapM map1(ni, no);
    for (int i = 0; i < no; ++ i) {
      map1.set_omap(VarId(i), VarId(i), false);
    }
    for (int x = 0U; x < nip; ++ x) {
      for (int i = 0; i < ni1; ++ i) {
	bool inv = (x & (1U << i)) ? false : true;
	VarId src_var = i_list[i];
	VarId dst_var(pg(i) + offset);
	map1.set_imap(src_var, dst_var, inv);
      }
      TvFuncM f1 = f.xform(map1);
      if ( first || repfunc < f1 ) {
	first = false;
	repfunc = f1;
	map = map1;
      }
    }
  }

  for (vector<VarId>::iterator p = i_list.begin();
       p != i_list.end(); ++ p) {
    VarId src_var = *p;
    NpnVmap vmap = map.imap(src_var);
    xmap.set_imap(src_var, vmap);
  }

  return ni1;
}

END_NONAMESPACE

// @brief 代表関数を求める．
void
LcGroupMgr::default_repfunc(const TvFuncM& f,
			    TvFuncM& repfunc,
			    NpnMapM& xmap)
{
  int ni = f.input_num();
  int no = f.output_num();

  // 各出力のサポートをビットベクタの形で求める．
  vector<int> sup_array(no);
  for (int o = 0; o < no; ++ o) {
    VarId ovar(o);
    TvFunc func1 = f.output(ovar);
    int supbits = gen_support(func1);
    sup_array[o] = supbits;
  }

  // サポートが共通な出力を同じグループにマージする．
  MFSet mfset(no);
  for (int o = 0; o < no; ++ o) {
    int supbits0 = sup_array[o];
    for (int o1 = o + 1; o1 < no; ++o1) {
      int supbits1 = sup_array[o1];
      if ( supbits0 & supbits1 ) {
	mfset.merge(o, o1);
      }
    }
  }

  // 一つ一つのグループを独立に処理する．
  xmap.set_identity(ni, no);
  int offset = 0;
  for (int first = 0; first < no; ++ first) {
    if ( mfset.find(first) != first ) continue;
    vector<int> o_list;
    o_list.reserve(no);
    vector<TvFunc> f_list;
    f_list.reserve(no);
    for (int o = 0; o < no; ++ o) {
      VarId ovar(o);
      if ( mfset.find(o) == first ) {
	o_list.push_back(o);
	f_list.push_back(f.output(ovar));
      }
    }
    TvFuncM f1(f_list);
    NpnMapM map1;
    int ni1 = gen_maxmap(f1, offset, xmap);
    offset += ni1;
  }

  repfunc = f.xform(xmap);
}
#endif

#if 0
// @brief 内容をバイナリダンプする．
// @param[in] bos 出力先のストリーム
void
LcGroupMgr::dump(ODO& bos) const
{
  // セルグループの情報をダンプする．
  int ng = group_num();
  bos << ng;
  for (int i = 0; i < ng; ++ i) {
    const LcGroup* group = this->group(i);
    ASSERT_COND( group->id() == i );

    // 論理クラスに対する変換マップをダンプする．
    const NpnMapM& map = group->map();
    int ni = map.input_num();
    bos << ni;
    for (int i = 0; i < ni; ++ i) {
      NpnVmap imap = map.imap(i);
      // 手抜きでは imap を int にキャストすればよい．
      int j = imap.pos();
      int v = (j << 1);
      if ( imap.pol() == kPolNega ) {
	v |= 1U;
      }
      bos << v;
    }
    int no = map.output_num();
    bos << no;
    for (int i = 0; i < no; ++ i) {
      NpnVmap omap = map.omap(i);
      int j = omap.pos();
      int v = (j << 1);
      if ( omap.pol() == kPolNega ) {
	v |= 1U;
      }
      bos << v;
    }

    // 属しているセル番号をダンプする．
    const vector<const Clib*>& cell_list = group->cell_list();
    int nc = cell_list.size();
    bos << nc;
    for (int i = 0; i < nc; ++ i) {
      const Clib* cell = cell_list[i];
      bos << static_cast<int>(cell->id());
    }
  }

  // NPN同値クラスの情報をダンプする．
  int nc = npn_class_num();
  bos << nc;
  for (int i = 0; i < nc; ++ i) {
    const LcClass* rep = npn_class(i);
    ASSERT_COND( rep->id() == i  );
    const vector<LcGroup*>& group_list = rep->group_list();
    int ng = group_list.size();
    bos << ng;
    for (int j = 0; j < ng; ++ j) {
      bos << static_cast<int>(group_list[j]->id());
    }
  }
}
#endif

END_NAMESPACE_YM_CLIB_LIBCOMP
