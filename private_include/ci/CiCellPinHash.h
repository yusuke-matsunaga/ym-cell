#ifndef CICELLPINHASH_H
#define CICELLPINHASH_H

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
  /// @return cell の name というピンのピン番号を返す．
  ///
  /// なければ -1 を返す．
  int
  get(const CiCell* cell,
      ShString name) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief テーブルの領域を確保する．
  /// @param[in] req_size 要求するサイズ
  void
  alloc_table(SizeType req_size);

  /// @brief 要素をリンクに追加する．
  /// @param[in] pos 追加する位置
  /// @param[in] pin 追加する要素
  void
  add_pin(SizeType pos,
	  CiCellPin* pin);


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

//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

END_NAMESPACE_YM_CLIB

#endif // CICELLPINHASH_H
