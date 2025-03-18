#ifndef PYCLIBTIMING_H
#define PYCLIBTIMING_H

/// @file PyClibTiming.h
/// @brief PyClibTiming のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/ClibTiming.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
/// @class PyClibTimingConv PyClibTiming.h "PyClibTiming.h"
/// @brief ClibTiming を PyObject* に変換するファンクタクラス
///
/// 実はただの関数
//////////////////////////////////////////////////////////////////////
class PyClibTimingConv
{
public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ClibTiming を PyObject* に変換する．
  PyObject*
  operator()(
    const ClibTiming& val
  );

};


//////////////////////////////////////////////////////////////////////
/// @class PyClibTimingDeconv PyClibTiming.h "PyClibTiming.h"
/// @brief ClibTiming を取り出すファンクタクラス
///
/// 実はただの関数
//////////////////////////////////////////////////////////////////////
class PyClibTimingDeconv
{
public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief PyObject* から ClibTiming を取り出す．
  bool
  operator()(
    PyObject* obj,
    ClibTiming& val
  );

};


//////////////////////////////////////////////////////////////////////
/// @class PyClibTiming PyClibTiming.h "PyClibTiming.h"
/// @brief Python 用の ClibTiming 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibTiming
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

  /// @brief ClibTiming を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    const ClibTiming& val ///< [in] 値
  )
  {
    PyClibTimingConv conv;
    return conv(val);
  }

  /// @brief PyObject が ClibTiming タイプか調べる．
  static
  bool
  _check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibTiming を表す PyObject から ClibTiming を取り出す．
  /// @return ClibTiming を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  ClibTiming&
  _get_ref(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibTiming を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM

#endif // PYCLIBTIMING_H
