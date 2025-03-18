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


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
/// @class PyClibCellConv PyClibCell.h "PyClibCell.h"
/// @brief ClibCell を PyObject* に変換するファンクタクラス
///
/// 実はただの関数
//////////////////////////////////////////////////////////////////////
class PyClibCellConv
{
public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief ClibCell を PyObject* に変換する．
  PyObject*
  operator()(
    const ClibCell& val
  );

};


//////////////////////////////////////////////////////////////////////
/// @class PyClibCellDeconv PyClibCell.h "PyClibCell.h"
/// @brief ClibCell を取り出すファンクタクラス
///
/// 実はただの関数
//////////////////////////////////////////////////////////////////////
class PyClibCellDeconv
{
public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief PyObject* から ClibCell を取り出す．
  bool
  operator()(
    PyObject* obj,
    ClibCell& val
  );

};


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
  )
  {
    PyClibCellConv conv;
    return conv(val);
  }

  /// @brief PyObject が ClibCell タイプか調べる．
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

END_NAMESPACE_YM

#endif // PYCLIBCELL_H
