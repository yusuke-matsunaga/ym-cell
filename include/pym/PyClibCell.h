#ifndef PYCLIBCELL_H
#define PYCLIBCELL_H

/// @file PyClibCell.h
/// @brief PyClibCell のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/ClibCell.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCell;

//////////////////////////////////////////////////////////////////////
/// @class PyClibCell PyClibCell.h "PyClibCell.h"
/// @brief Python 用の ClibCell 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibCell
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

  /// @brief ClibCell を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    const ClibCell& val ///< [in] 値
  );

  /// @brief ClibCell を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    const CiCell* val ///< [in] 値
  );

  /// @brief PyObject が ClibCell タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibCell を表す PyObject から ClibCell を取り出す．
  /// @return ClibCell を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  const CiCell*
  Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibCell を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM_CLIB

BEGIN_NAMESPACE_YM

using nsClib::PyClibCell;

END_NAMESPACE_YM

#endif // PYCLIBCELL_H
