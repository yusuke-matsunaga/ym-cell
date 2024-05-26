#ifndef PYCLIBTIMINGTYPE_H
#define PYCLIBTIMINGTYPE_H

/// @file PyClibTimingType.h
/// @brief PyClibTimingType のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class PyClibTimingType PyClibTimingType.h "PyClibTimingType.h"
/// @brief Python 用の ClibTimingType 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibTimingType
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

  /// @brief ClibTimingType を表す PyObject から ClibTimingType を取り出す．
  /// @return 変換が成功したら true を返す．
  ///
  /// エラーの場合には Python 例外をセットする．
  static
  bool
  FromPyObject(
    PyObject* obj,            ///< [in] ClibTimingType を表す PyObject
    ClibTimingType& val,      ///< [out] 変換された ClibTimingType を格納する変数
    const char* msg = nullptr ///< [in] エラーメッセージ(省略時にはデフォルト値を使う)
  );

  /// @brief ClibTimingType を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    ClibTimingType val ///< [in] 値
  );

  /// @brief PyObject が ClibTimingType タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibTimingType を表す PyObject から ClibTimingType を取り出す．
  /// @return ClibTimingType を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  ClibTimingType
  Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibTimingType を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM_CLIB

#endif // PYCLIBTIMINGTYPE_H
