﻿#ifndef LCCLASS_H
#define LCCLASS_H

/// @file LcClass.h
/// @brief LcClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "libcomp_nsdef.h"
#include "LcSignature.h"


BEGIN_NAMESPACE_YM_CELL_LIBCOMP

//////////////////////////////////////////////////////////////////////
/// @class LcClass LcClass.h "LcClass.h"
/// @brief テンポラリに使用するセルクラス用のクラス
//////////////////////////////////////////////////////////////////////
class LcClass
{
  friend class LibComp;

public:

  /// @brief コンストラクタ
  /// @param[in] id ID番号
  /// @param[in] rep_sig 代表シグネチャ
  LcClass(ymuint id,
	  const LcSignature& rep_sig);

  /// @brief デストラクタ
  ~LcClass();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  ymuint
  id() const;

  /// @brief 代表シグネチャを返す．
  const LcSignature&
  rep_sig() const;

  /// @brief 同位体変換のリストを返す．
  const vector<NpnMapM>&
  idmap_list() const;

  /// @brief このクラスに属しているグループのリストを返す．
  const vector<LcGroup*>&
  group_list() const;

  /// @brief グループを追加する．
  void
  add_group(LcGroup* group,
	    const NpnMapM& map);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID番号
  ymuint mId;

  // 代表シグネチャ
  LcSignature mRepSig;

  // 同位体変換のリスト
  vector<NpnMapM> mIdmapList;

  // グループのリスト
  vector<LcGroup*> mGroupList;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ID番号を返す．
inline
ymuint
LcClass::id() const
{
  return mId;
}

// @brief 代表シグネチャを返す．
inline
const LcSignature&
LcClass::rep_sig() const
{
  return mRepSig;
}

// @brief 同位体変換のリストを返す．
inline
const vector<NpnMapM>&
LcClass::idmap_list() const
{
  return mIdmapList;
}

// @brief このクラスに属しているグループのリストを返す．
inline
const vector<LcGroup*>&
LcClass::group_list() const
{
  return mGroupList;
}

END_NAMESPACE_YM_CELL_LIBCOMP

#endif // LCCLASS_H
