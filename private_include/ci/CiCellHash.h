#ifndef CICELLHASH_H
#define CICELLHASH_H

/// @file CiCellHash.h
/// @brief CiCellHash のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCell;

//////////////////////////////////////////////////////////////////////
/// @class CiCellHash CiCellHash.h "CiCellHash.h"
/// @brief 名前をキーにした CiCell のハッシュ表
///
/// CiCell そのものをハッシュ表中のリンクトリストの要素に用いている．
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
  void
  add(
    CiCell* cell ///< [in] 追加するセル
  );

  /// @brief セル番号を取り出す．
  /// @return name という名前のセルのセル番号を返す．
  ///
  /// なければ CLIB_NULLID を返す．
  SizeType
  get(
    ShString name ///< [in] 名前
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


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テーブルサイズ
  SizeType mSize;

  // ハッシュ表
  CiCell** mTable;

  // ハッシュ表を拡大するしきい値
  SizeType mLimit;

  // 要素数
  SizeType mNum;

};

END_NAMESPACE_YM_CLIB

#endif // CICELLHASH_H
