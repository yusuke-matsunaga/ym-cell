#ifndef LCFFMGR_H
#define LCFFMGR_H

/// @file LcFFMgr.h
/// @brief LcFFMgr.h
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "LcGroupMgr.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcFFMgr LcFFMgr.h "LcFFMgr.h"
/// @brief FFセルを表すクラス
//////////////////////////////////////////////////////////////////////
class LcFFMgr :
  public LcGroupMgr
{
public:

  /// @brief コンストラクタ
  /// @param[in] libcomp 親の LibComp
  LcFFMgr(LibComp& libcomp);

  /// @brief デストラクタ
  ~LcFFMgr();


public:
  //////////////////////////////////////////////////////////////////////
  // このクラスのメインの関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  void
  init();

  /// @brief 定義済みのFFクラス番号を返す．
  /// @param[in] has_q Q端子の有無
  /// @param[in] has_xq 反転Q端子の有無
  /// @param[in] has_clear クリア端子の有無
  /// @param[in] has_preset プリセット端子の有無
  ///
  /// has_q == false && has_xq == false は不適
  ymuint
  ff_class(bool has_q,
	   bool has_xq,
	   bool has_clear,
	   bool has_preset);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表関数を求める．
  /// @param[in] sig シグネチャ
  /// @param[out] rep_sig 代表シグネチャ
  /// @param[out] xmap 変換
  virtual
  void
  find_rep(const LcSignature& sig,
	   LcSignature& rep_sig,
	   NpnMapM& xmap);

  /// @brief 同位体変換リストを求める．
  /// @param[in] sig シグネチャ
  /// @param[out] idmap_list 同位体変換のリスト
  virtual
  void
  find_idmap_list(const LcSignature& sig,
		  vector<NpnMapM>& idmap_list);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 定義済みのクラス番号
  ymuint mFFClass[12];

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCFFMGR_H
