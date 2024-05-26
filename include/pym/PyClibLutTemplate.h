#ifndef PYCLIBCELL_H
#define PYCLIBCELL_H

/// @file PyClibLutTemplate.h
/// @brief PyClibLutTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/ClibLutTemplate.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class PyClibLutTemplate PyClibLutTemplate.h "PyClibLutTemplate.h"
/// @brief Python 用の ClibLutTemplate 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibLutTemplate
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

  /// @brief ClibLutTemplate を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    ClibLutTemplate val ///< [in] 値
  );

  /// @brief PyObject が ClibLutTemplate タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibLutTemplate を表す PyObject から ClibLutTemplate を取り出す．
  /// @return ClibLutTemplate を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  const ClibLutTemplate&
  Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibLutTemplate を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM_CLIB

#endif // PYCLIBCELL_H
