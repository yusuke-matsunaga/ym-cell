#ifndef PYCLIBCELLTYPE_H
#define PYCLIBCELLTYPE_H

/// @file PyClibCellType.h
/// @brief PyClibCellType のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class PyClibCellType PyClibCellType.h "PyClibCellType.h"
/// @brief Python 用の ClibCellType 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibCellType
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

  /// @brief ClibCellType を表す PyObject から ClibCellType を取り出す．
  /// @return 変換が成功したら true を返す．
  ///
  /// エラーの場合には Python 例外をセットする．
  static
  bool
  FromPyObject(
    PyObject* obj,            ///< [in] ClibCellType を表す PyObject
    ClibCellType& val,      ///< [out] 変換された ClibCellType を格納する変数
    const char* msg = nullptr ///< [in] エラーメッセージ(省略時にはデフォルト値を使う)
  );

  /// @brief ClibCellType を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    ClibCellType val ///< [in] 値
  );

  /// @brief PyObject が ClibCellType タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibCellType を表す PyObject から ClibCellType を取り出す．
  /// @return ClibCellType を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  ClibCellType
  Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibCellType を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM_CLIB

#endif // PYCLIBCELLTYPE_H
