
/// @file LcLogicMgr.cc
/// @brief LcLogicMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "LcLogicMgr.h"
#include "LcGroup.h"
#include "LcSignature.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CELL_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcLogicMgr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] libcomp 親の LibComp
LcLogicMgr::LcLogicMgr(LibComp& libcomp) :
  LcGroupMgr(libcomp)
{
}

// @brief デストラクタ
LcLogicMgr::~LcLogicMgr()
{
}

// @brief 初期化する．
// 定数関数，リテラル関数を登録しておく
// 常に定数0，定数1，肯定リテラル，否定リテラルの関数番号が
// 0, 1, 2, 3 になるようにする．
void
LcLogicMgr::init()
{
  clear();

  { // 定数0グループの登録
    LcSignature sig(Expr::make_zero());
    LcGroup* func0 = find_group(sig, false);
    mLogicGroup[0] = func0->id();
  }
  { // 定数1グループの登録
    LcSignature sig(Expr::make_one());
    LcGroup* func1 = find_group(sig, false);
    mLogicGroup[1] = func1->id();
  }
  { // バッファグループの登録
    LcSignature sig(Expr::make_posiliteral(VarId(0)));
    LcGroup* func2 = find_group(sig, false);
    mLogicGroup[2] = func2->id();
  }
  { // インバーターグループの登録
    LcSignature sig(Expr::make_negaliteral(VarId(0)));
    LcGroup* func3 = find_group(sig, false);
    mLogicGroup[3] = func3->id();
  }
}

// @brief 定義済みの論理グループ番号を返す．
// @param[in] id 番号
// - 0: 定数0
// - 1: 定数1
// - 2: バッファ
// - 3: インバーター
ymuint
LcLogicMgr::logic_group(ymuint id) const
{
  ASSERT_COND( id < 4 );
  return mLogicGroup[id];
}

// @brief 代表シグネチャを求める．
// @param[in] sig シグネチャ
// @param[out] rep_sig 代表シグネチャ
// @param[out] xmap 変換
void
LcLogicMgr::find_rep(const LcSignature& sig,
		     LcSignature& rep_sig,
		     NpnMapM& xmap)
{
}

// @brief 同位体変換リストを求める．
// @param[in] sig シグネチャ
// @param[out] idmap_list 同位体変換のリスト
void
LcLogicMgr::find_idmap_list(const LcSignature& sig,
			    vector<NpnMapM>& idmap_list)
{
}

#if 0
// @brief 代表関数を求める．
// @param[in] f 関数
// @param[out] repfunc 代表関数
// @param[out] xmap 変換
void
LcLogicMgr::find_repfunc(const TvFuncM& f,
			 TvFuncM& repfunc,
			 NpnMapM& xmap)
{
  ymuint no = f.output_num();

  if ( no == 1 ) {
    TvFunc f1 = f.output(VarId(0));
    NpnMap xmap1 = f1.npn_cannonical_map();
    xmap = NpnMapM(xmap1);
    repfunc = f.xform(xmap);
    { // 一応検証
      TvFunc repfunc1 = f1.xform(xmap1);

      if ( repfunc.output(VarId(0)) != repfunc1 ) {
	cout << "Error in find_repfunc" << endl
	     << "f          = " << f1 << endl
	     << "repfunc    = " << repfunc << endl
	     << "repfunc(0) = " << repfunc.output(VarId(0)) << endl
	     << "repfunc1   = " << repfunc1 << endl;
      }
      ASSERT_COND( repfunc.output(VarId(0)) == repfunc1 );
    }
  }
  else {
    default_repfunc(f, repfunc, xmap);
  }
}

// @brief 同位体変換リストを求める．
// @param[in] func 対象の関数
// @param[out] idmap_list 同位体変換のリスト
void
LcLogicMgr::find_idmap_list(const TvFuncM& func,
			    vector<NpnMapM>& idmap_list)
{
  idmap_list.clear();

  ymuint ni = func.input_num();
  ymuint no = func.output_num();
  if ( no == 1 ) {
    vector<NpnMap> tmp_list;
    TvFunc f1 = func.output(VarId(0));
    f1.npn_cannonical_all_map(tmp_list);
    { // 検証
      NpnMap xmap1 = tmp_list.front();
      TvFunc f2 = f1.xform(xmap1);
      if ( f1 != f2 ) {
	cerr << "f1   = " << f1 << endl
	     << "f2   = " << f2 << endl
	     << "func = " << func << endl
	     << "xmap1 = " << xmap1 << endl;
      }
      ASSERT_COND( f1 == f2 );
    }
    idmap_list.reserve(tmp_list.size());
    for (vector<NpnMap>::iterator p = tmp_list.begin();
	 p != tmp_list.end(); ++ p) {
      const NpnMap& map = *p;
      // 恒等変換は追加しない．
      bool ident = true;
      for (ymuint i = 0; i < ni; ++ i) {
	VarId src_var(i);
	NpnVmap vmap = map.imap(src_var);
	if ( vmap.var() != src_var || vmap.inv() ) {
	  ident = false;
	  break;
	}
      }
      if ( !ident ) {
	idmap_list.push_back(NpnMapM(map));
      }
    }
  }
  else {
    // 今のところなし．
  }
}
#endif

END_NAMESPACE_YM_CELL_LIBCOMP
