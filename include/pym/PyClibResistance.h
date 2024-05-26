#ifndef PYCLIBRESISTANCE_H
#define PYCLIBRESISTANCE_H

/// @file PyClibResistance.h
/// @brief PyClibResistance のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/ClibResistance.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class PyClibResistance PyClibResistance.h "PyClibResistance.h"
/// @brief Python 用の ClibResistance 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibResistance
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

  /// @brief ClibResistance を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    ClibResistance val ///< [in] 値
  );

  /// @brief PyObject が ClibResistance タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibResistance を表す PyObject から ClibResistance を取り出す．
  /// @return ClibResistance を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  const ClibResistance&
  Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibResistance を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM_CLIB

#endif // PYCLIBRESISTANCE_H
