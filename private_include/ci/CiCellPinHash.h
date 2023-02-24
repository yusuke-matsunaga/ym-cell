#ifndef CICELLPINHASH_H
#define CICELLPINHASH_H

/// @file CiPinHash.h
/// @brief CiPinHash のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiPinHash CiPinHash.h "CiPinHash.h"
/// @brief ピン名のハッシュ表
///
/// 実はセル番号と名前をキーに番号を格納する辞書なのでバスやバンドルにも使える．
//////////////////////////////////////////////////////////////////////
class CiCellPinHash
{
public:

  /// @brief コンストラクタ
  CiCellPinHash() = default;

  /// @brief デストラクタ
  ~CiCellPinHash() = default;


public:

  /// @brief ピンを追加する．
  void
  add(
    SizeType cell_id, ///< [in] ピンの親のセル番号
    ShString name,    ///< [in] ピン名
    SizeType pin_id   ///< [in] ピン番号
  )
  {
    Key key{cell_id, name};
    mDict.emplace(key, pin_id);
  }

  /// @brief ピンを取り出す．
  /// @return cell の name というピンのピン番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  get(
    SizeType cell_id, ///< [in] セル番号
    ShString name     ///< [in] 名前
  ) const
  {
    Key key{cell_id, name};
    if ( mDict.count(key) > 0 ) {
      return mDict.at(key);
    }
    else {
      return CLIB_NULLID;
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////

  struct Key
  {
    SizeType mCellId;
    ShString mName;

    bool
    operator==(const Key& right) const
    {
      return mCellId == right.mCellId && mName == right.mName;
    }
  };


  struct Hash
  {
    SizeType
    operator()(
      const Key& key
    ) const
    {
      return key.mCellId + key.mName.hash() * 97;
    }
  };


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ハッシュ表
  unordered_map<Key, SizeType, Hash> mDict;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLPINHASH_H
