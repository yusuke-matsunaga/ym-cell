#ifndef PYCLIBDIRECTION_H
#define PYCLIBDIRECTION_H

/// @file PyClibDirection.h
/// @brief PyClibDirection のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/clib.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
/// @class PyClibDirection PyClibDirection.h "PyClibDirection.h"
/// @brief Python 用の ClibDirection 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibDirection
{
  using ElemType = ClibDirection;

public:

  /// @brief ClibDirection を PyObject* に変換するファンクタクラス
  struct Conv {
    PyObject*
    operator()(
      const ElemType& val
    );
  };

  /// @brief PyObject* から ClibDirection を取り出すファンクタクラス
  struct Deconv {
    bool
    operator()(
      PyObject* obj,
      ElemType& val
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

  /// @brief ClibDirection を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    const ElemType& val ///< [in] 値
  )
  {
    Conv conv;
    return conv(val);
  }

  /// @brief ClibDirection を表す PyObject から ClibDirection を取り出す．
  /// @return 変換が成功したら true を返す．
  static
  bool
  FromPyObject(
    PyObject* obj, ///< [in] ClibDirection を表す PyObject
    ElemType& val  ///< [out] 変換された ClibDirection を格納する変数
  )
  {
    Deconv deconv;
    return deconv(obj, val);
  }

  /// @brief PyObject が ClibDirection タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibDirection を表す PyObject から ClibDirection を取り出す．
  /// @return ClibDirection を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  ElemType&
  _get_ref(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibDirection を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM

#endif // PYCLIBDIRECTION_H
