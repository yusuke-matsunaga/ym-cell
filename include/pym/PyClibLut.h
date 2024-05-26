#ifndef PYCLIBLUT_H
#define PYCLIBLUT_H

/// @file PyClibLut.h
/// @brief PyClibLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/ClibLut.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class PyClibLut PyClibLut.h "PyClibLut.h"
/// @brief Python 用の ClibLut 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibLut
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

  /// @brief ClibLut を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    ClibLut val ///< [in] 値
  );

  /// @brief PyObject が ClibLut タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibLut を表す PyObject から ClibLut を取り出す．
  /// @return ClibLut を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  const ClibLut&
  Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibLut を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM_CLIB

#endif // PYCLIBCELL_H
