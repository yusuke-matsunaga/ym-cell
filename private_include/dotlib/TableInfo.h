#ifndef TABLEINFO_H
#define TABLEINFO_H

/// @file TableInfo.h
/// @brief TableInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/ElemDict.h"
#include "ci/CiLut.h"
#include "ci/CiCellLibrary.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

class LibraryInfo;

//////////////////////////////////////////////////////////////////////
/// @class TableInfo TableInfo.h "TableInfo.h"
/// @brief テーブルグループのパース情報を表すクラス
//////////////////////////////////////////////////////////////////////
class TableInfo
{
public:

  /// @brief コンストラクタ
  TableInfo(
    LibraryInfo& library_info ///< [in] ライブラリのパース情報
  ) : mLibraryInfo{library_info}
  {
  }

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
  gen_lut() const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ライブラリを取り出す．
  CiCellLibrary*
  library() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ライブラリのパース情報
  LibraryInfo& mLibraryInfo;

  // 要素の辞書
  ElemDict mElemDict;

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
