#ifndef CIPINHASH_H
#define CIPINHASH_H

/// @file CiCellPinHash.h
/// @brief CiCellPinHash のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
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
  /// @param[in] pin 追加するピン
  void
  add(CiCellPin* pin);

  /// @brief ピンを取り出す．
  /// @param[in] cell セル
  /// @param[in] name 名前
  /// @return cell の name というピンを返す．
  /// @note なければ nullptr を返す．
  CiCellPin*
  get(const CiCell* cell,
      ShString name) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief テーブルの領域を確保する．
  /// @param[in] req_size 要求するサイズ
  void
  alloc_table(int req_size);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テーブルサイズ
  int mSize;

  // ハッシュ表
  CiCellPin** mTable;

  // ハッシュ表を拡大するしきい値
  int mLimit;

  // 要素数
  int mNum;

};

END_NAMESPACE_YM_CLIB

#endif // CIPINHASH_H
