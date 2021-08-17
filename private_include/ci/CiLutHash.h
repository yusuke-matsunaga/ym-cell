#ifndef CILUTHASH_H
#define CILUTHASH_H

/// @file CiLutHash.h
/// @brief CiLutHash のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

class CiLutTemplate;

//////////////////////////////////////////////////////////////////////
/// @class CiLutHash CiLutHash.h "CiLutHash.h"
/// @brief 名前をキーにした CiClib のハッシュ表
//////////////////////////////////////////////////////////////////////
class CiLutHash
{
public:

  /// @brief コンストラクタ
  CiLutHash();

  /// @brief デストラクタ
  ~CiLutHash();


public:

  /// @brief テンプレートを追加する．
  void
  add(
    CiLutTemplate* templ ///< [in] 追加するテンプレート
  );

  /// @brief テンプレートを取り出す．
  /// @return name という名前のテンプレートを返す．
  ///
  /// なければ nullptr を返す．
  CiLutTemplate*
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
  CiLutTemplate** mTable;

  // ハッシュ表を拡大するしきい値
  SizeType mLimit;

  // 要素数
  SizeType mNum;

};

END_NAMESPACE_YM_CLIB

#endif // CILUTHASH_H
