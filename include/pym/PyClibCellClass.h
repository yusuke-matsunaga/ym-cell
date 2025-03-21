#ifndef PYCLIBCELLCLASS_H
#define PYCLIBCELLCLASS_H

/// @file PyClibCellClass.h
/// @brief PyClibCellClass のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/ClibCellClass.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class PyClibCell PyClibCell.h "PyClibCell.h"
/// @brief Python 用の ClibCell 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibCell
{
public:

  /// @brief ClibCellClass を PyObject* に変換するファンクタクラス
  struct Conv {
    /// @brief ClibCellClass を PyObject* に変換する．
    PyObject*
    operator()(
      const ClibCellClass& val
    );
  };

  /// @brief ClibCellClass を取り出すファンクタクラス
  struct Deconv {
    /// @brief PyObject* から ClibCellClass を取り出す．
    bool
    operator()(
      PyObject* obj,
      ClibCellClass& val
    );
  };


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

  /// @brief ClibCellClass を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    const ClibCellClass& val ///< [in] 値
  )
  {
    Conv conv;
    return conv(val);
  }

  /// @brief PyObject から ClibCellClass を取り出す．
  /// @return 正しく変換できた時に true を返す．
  static
  bool
  FromPyObject(
    PyObject* obj,     ///< [in] Python のオブジェクト
    ClibCellClass& val ///< [out] 結果を格納するリスト
  )
  {
    Deconv deconv;
    return deconv(obj, val);
  }

  /// @brief PyObject が ClibCellClass タイプか調べる．
  static
  bool
  _check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibCell を表す PyObject から ClibCell を取り出す．
  /// @return ClibCell を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  ClibCell&
  _get_ref(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibCell を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM_CLIB

#endif // PYCLIBCELLCLASS_H
