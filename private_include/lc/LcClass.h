#ifndef LCCLASS_H
#define LCCLASS_H

/// @file LcClass.h
/// @brief LcClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "lc/libcomp_nsdef.h"
#include "lc/LcSignature.h"


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcClass LcClass.h "LcClass.h"
/// @brief テンポラリに使用するセルクラス用のクラス
//////////////////////////////////////////////////////////////////////
class LcClass
{
  friend class LibComp;

public:

  /// @brief コンストラクタ
  LcClass(int id,                      ///< [in] ID番号
	  const LcSignature& rep_sig); ///< [in] 代表シグネチャ

  /// @brief デストラクタ
  ~LcClass();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  int
  id() const
  {
    return mId;
  }

  /// @brief 代表シグネチャを返す．
  const LcSignature&
  rep_sig() const
  {
    return mRepSig;
  }

  /// @brief 同位体変換のリストを返す．
  const vector<NpnMapM>&
  idmap_list() const
  {
    return mIdmapList;
  }

  /// @brief このクラスに属しているグループのリストを返す．
  const vector<LcGroup*>&
  group_list() const
  {
    return mGroupList;
  }

  /// @brief グループを追加する．
  void
  add_group(LcGroup* group,      ///< [in] グループ
	    const NpnMapM& map); ///< [in] 代表シグネチャへの変換マップ


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID番号
  int mId;

  // 代表シグネチャ
  LcSignature mRepSig;

  // 同位体変換のリスト
  vector<NpnMapM> mIdmapList;

  // グループのリスト
  vector<LcGroup*> mGroupList;

};

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCCLASS_H
