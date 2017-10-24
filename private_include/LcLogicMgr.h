#ifndef LCLOGICMGR_H
#define LCLOGICMGR_H

/// @file LcLogicMgr.h
/// @brief LcLogicMgr.h
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "LcGroupMgr.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcLogicMgr LcLogicMgr.h "LcLogicMgr.h"
/// @brief 論理セルのグループ分けを行うクラス
//////////////////////////////////////////////////////////////////////
class LcLogicMgr :
  public LcGroupMgr
{
public:

  /// @brief コンストラクタ
  /// @param[in] libcomp 親の LibComp
  LcLogicMgr(LibComp& libcomp);

  /// @brief デストラクタ
  ~LcLogicMgr();


public:
  //////////////////////////////////////////////////////////////////////
  // このクラスのメインの関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  /// @note 定数関数，リテラル関数を登録しておく
  ///
  /// 常に定数0，定数1，肯定リテラル，否定リテラルのグループ番号が
  /// 0, 1, 2, 3 になるようにする．
  void
  init();

  /// @brief 定義済みの論理グループ番号を返す．
  /// @param[in] id 番号
  /// - 0: 定数0
  /// - 1: 定数1
  /// - 2: バッファ
  /// - 3: インバーター
  ymuint
  logic_group(ymuint id) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表シグネチャを求める．
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

  // 定義済みの論理グループ
  ymuint mLogicGroup[4];

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCLOGICMGR_H
