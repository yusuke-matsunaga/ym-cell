#ifndef PYCLIBCELLLIBRARY_H
#define PYCLIBCELLLIBRARY_H

/// @file PyClibCellLibrary.h
/// @brief PyClibCellLibrary のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/ClibCellLibrary.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
/// @class PyClibCellLibrary PyClibCellLibrary.h "PyClibCellLibrary.h"
/// @brief Python 用の ClibCellLibrary 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibCellLibrary
{
public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  /// @return 初期化が成功したら true を返す．
  static
  bool
  init(
    PyObject* m ///< [in] 親のモジュールを表す PyObject
  );

  /// @brief PyObject が ClibCellLibrary タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibCellLibrary を表す PyObject から ClibCellLibrary を取り出す．
  /// @return ClibCellLibrary を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  const ClibCellLibrary&
  Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibCellLibrary を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM

#endif // PYCLIBCELLLIBRARY_H
