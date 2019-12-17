#ifndef CILUTHASH_H
#define CILUTHASH_H

/// @file CiLutHash.h
/// @brief CiLutHash のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
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
  /// @param[in] templ 追加するテンプレート
  void
  add(CiLutTemplate* templ);

  /// @brief テンプレートを取り出す．
  /// @param[in] name 名前
  /// @return name という名前のテンプレートを返す．
  /// @note なければ nullptr を返す．
  CiLutTemplate*
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
  CiLutTemplate** mTable;

  // ハッシュ表を拡大するしきい値
  int mLimit;

  // 要素数
  int mNum;

};

END_NAMESPACE_YM_CLIB

#endif // CILUTHASH_H
