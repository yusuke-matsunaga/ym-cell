#ifndef CICELLHASH_H
#define CICELLHASH_H

/// @file CiCellHash.h
/// @brief CiCellHash のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCell;

//////////////////////////////////////////////////////////////////////
/// @class CiCellHash CiCellHash.h "CiCellHash.h"
/// @brief 名前をキーにした CiCell のハッシュ表
//////////////////////////////////////////////////////////////////////
class CiCellHash
{
public:

  /// @brief コンストラクタ
  CiCellHash();

  /// @brief デストラクタ
  ~CiCellHash();


public:

  /// @brief セルを追加する．
  /// @param[in] cell 追加するセル
  void
  add(CiCell* cell);

  /// @brief セルを取り出す．
  /// @param[in] name 名前
  /// @return name という名前のセルを返す．
  /// @note なければ nullptr を返す．
  CiCell*
  get(ShString name) const;


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
  CiCell** mTable;

  // ハッシュ表を拡大するしきい値
  int mLimit;

  // 要素数
  int mNum;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLHASH_H
