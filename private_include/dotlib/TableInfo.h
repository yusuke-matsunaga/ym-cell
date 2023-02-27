#ifndef TABLEINFO_H
#define TABLEINFO_H

/// @file TableInfo.h
/// @brief TableInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "ci/CiLut.h"
#include "ci/CiCellLibrary.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class TableInfo TableInfo.h "TableInfo.h"
/// @brief テーブルグループのパース情報を表すクラス
//////////////////////////////////////////////////////////////////////
class TableInfo
{
public:

  /// @brief コンストラクタ
  TableInfo() = default;

  /// @brief デストラクタ
  ~TableInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をセットする．
  bool
  set(
    const AstValue* val
  );

  SizeType
  gen_lut(
    CiCellLibrary* library
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // テンプレート名
  ShString mName;

  // index_1 の値
  vector<double> mIndex1;

  // index_2 の値
  vector<double> mIndex2;

  // index_3 の値
  vector<double> mIndex3;

  // values の値
  vector<double> mValues;

  // domain の値
  const AstValue* mDomain{nullptr};

};

END_NAMESPACE_YM_DOTLIB

#endif // TABLEINFO_H