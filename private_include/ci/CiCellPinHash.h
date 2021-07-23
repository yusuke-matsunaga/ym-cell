#ifndef CICELLPINHASH_H
#define CICELLPINHASH_H

/// @file CiCellPinHash.h
/// @brief CiCellPinHash のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCell;
class CiCellPin;

//////////////////////////////////////////////////////////////////////
/// @class CiCellPinHash CiCellPinHash.h "CiCellPinHash.h"
/// @brief ピン名のハッシュ表
//////////////////////////////////////////////////////////////////////
class CiCellPinHash
{
public:

  /// @brief コンストラクタ
  CiCellPinHash();

  /// @brief デストラクタ
  ~CiCellPinHash();


public:

  /// @brief ピンを追加する．
  void
  add(
    CiCellPin* pin ///< [in] 追加するピン
  );

  /// @brief ピンを取り出す．
  /// @return cell の name というピンのピン番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  get(
    const CiCell* cell, ///< [in] セル
    ShString name       ///< [in] 名前
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief テーブルの領域を確保する．
  void
  alloc_table(
    SizeType req_size ///< [in] 要求するサイズ
  );

  /// @brief 要素をリンクに追加する．
  void
  add_pin(
    SizeType pos,  ///< [in] 追加する位置
    CiCellPin* pin ///< [in] 追加する要素
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テーブルサイズ
  SizeType mSize;

  // ハッシュ表
  CiCellPin** mTable;

  // ハッシュ表を拡大するしきい値
  SizeType mLimit;

  // 要素数
  SizeType mNum;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLPINHASH_H
