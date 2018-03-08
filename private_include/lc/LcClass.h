#ifndef LCCLASS_H
#define LCCLASS_H

/// @file LcClass.h
/// @brief LcClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
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
  /// @param[in] id ID番号
  /// @param[in] rep_sig 代表シグネチャ
  LcClass(int id,
	  const LcSignature& rep_sig);

  /// @brief デストラクタ
  ~LcClass();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号を返す．
  int
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
  int mId;

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
int
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

END_NAMESPACE_YM_CLIB_LIBCOMP

#endif // LCCLASS_H
