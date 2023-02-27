#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

/// @file LibraryInfo.h
/// @brief LibraryInfo のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/dotlib_nsdef.h"
#include "dotlib/ElemDict.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class LibraryInfo LibraryInfo.h "LibraryInfo.h"
/// @brief ライブラリのパース情報
//////////////////////////////////////////////////////////////////////
class LibraryInfo
{
public:

  /// @brief コンストラクタ
  LibraryInfo(
    CiCellLibrary* library ///< [in] 対象のライブラリ
  ) : mLibrary{library}
  {
  }

  /// @brief デストラクタ
  ~LibraryInfo() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を設定する．
  bool
  set(
    const AstValue& lib_val ///< [in] ライブラリ情報のパース木
  );

  /// @brief ライブラリを取り出す．
  CiCellLibrary*
  library()
  {
    return mLibrary;
  }

  /// @brief LUTテンプレート番号を取り出す．
  SizeType
  find_lut(
    const ShString& name ///< [in] テンプレート名
  )
  {
    if ( mLutDict.count(name) > 0 ) {
      return mLutDict.at(name);
    }
    return CLIB_NULLID;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 文字列型の属性をセットする．
  bool
  set_str_attr(
    const char* keyword ///< [in] キーワード
  );

  /// @brief capacitive_load_unit の属性をセットする．
  bool
  set_capacitive_load_unit();


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ライブラリ
  CiCellLibrary* mLibrary{nullptr};

  // 要素の辞書
  ElemDict mElemDict;

  // 名前をキーにしてLUTテンプレート番号を格納する辞書
  unordered_map<ShString, SizeType> mLutDict;

};

END_NAMESPACE_YM_DOTLIB

#endif // LIBRARYINFO_H
