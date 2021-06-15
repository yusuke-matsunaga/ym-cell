#ifndef LCGROUPMGR_H
#define LCGROUPMGR_H

/// @file LcGroupMgr.h
/// @brief LcGroupMgr.h
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/libcomp_nsdef.h"
#include "ym/NpnMapM.h"
#include "ym/HashMap.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcGroupMgr LcGroupMgr.h "LcGroupMgr.h"
/// @brief セルのグループ分けを行う基底クラス
//////////////////////////////////////////////////////////////////////
class LcGroupMgr
{
public:

  /// @brief コンストラクタ
  LcGroupMgr(LibComp& libcomp); ///< [in] 親の LibComp

  /// @brief デストラクタ
  ~LcGroupMgr();


public:
  //////////////////////////////////////////////////////////////////////
  // このクラスのメインの関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を空にする．
  void
  clear();

  /// @brief セルを追加する．
  void
  add_cell(Cell* cell); ///< [in] 追加するセル

  /// @brief シグネチャに対応する LcGroup を求める．
  ///
  /// なければ新規に作る．
  LcGroup*
  find_group(const LcSignature& sig, ///< [in] シグネチャ
	     bool builtin);          ///< [in] 組み込みクラスの時 true にするフラグ


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表シグネチャを求める．
  virtual
  void
  find_rep(const LcSignature& sig, ///< [in] シグネチャ
	   LcSignature& rep_sig,   ///< [out] 代表シグネチャ
	   NpnMapM& xmap) = 0;     ///< [out] 変換マップ

  /// @brief 同位体変換リストを求める．
  virtual
  void
  find_idmap_list(const LcSignature& sig,           ///< [in] シグネチャ
		  vector<NpnMapM>& idmap_list) = 0; ///< [in] 同位体変換のリスト


protected:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられるクラスメソッド
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表シグネチャを求める．
  static
  void
  default_rep(const LcSignature& sig,
	      LcSignature& rep_sig,
	      NpnMapM& xmap);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 親の LibComp
  LibComp& mLibComp;

  // シグネチャ文字列をキーとしてグループ番号を保持するハッシュ表
  HashMap<string, int> mGroupMap;

  // 代表シグネチャの文字列をキーとしてクラス番号を保持するハッシュ表
  HashMap<string, int> mClassMap;

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCGROUPMGR_H
