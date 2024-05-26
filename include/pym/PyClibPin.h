#ifndef PYCLIBPIN_H
#define PYCLIBPIN_H

/// @file PyClibPin.h
/// @brief PyClibPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/ClibPin.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
/// @class PyClibPin PyClibPin.h "PyClibPin.h"
/// @brief Python 用の ClibPin 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibPin
{
  using CiCell = nsClib::CiCell;
  using CiPin = nsClib::CiPin;

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

  /// @brief ClibPin を表す PyObject から ClibPin を取り出す．
  /// @return 変換が成功したら true を返す．
  ///
  /// エラーの場合には Python 例外をセットする．
  static
  bool
  FromPyObject(
    PyObject* obj,            ///< [in] ClibPin を表す PyObject
    const CiPin*& val,        ///< [out] 変換された ClibPin を格納する変数
    const char* msg = nullptr ///< [in] エラーメッセージ(省略時にはデフォルト値を使う)
  );

  /// @brief ClibPin を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    const ClibPin& val ///< [in] 値
  );

  /// @brief ClibPin を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    const CiCell* cell, ///< [in] 親のセル
    const CiPin* val    ///< [in] 値
  );

  /// @brief PyObject が ClibPin タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibPin を表す PyObject から ClibPin を取り出す．
  /// @return ClibPin を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  const CiPin*
  Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibPin を表す PyObject から ClibPin を取り出す．
  /// @return ClibPin を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  std::pair<const CiCell*, const CiPin*>
  _Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibPin を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM

#endif // PYCLIBPIN_H
