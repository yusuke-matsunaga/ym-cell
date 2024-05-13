#ifndef PYCLIBDELAYMODEL_H
#define PYCLIBDELAYMODEL_H

/// @file PyClibDelayModel.h
/// @brief PyClibDelayModel のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/clib.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
/// @class PyClibDelayModel PyClibDelayModel.h "PyClibDelayModel.h"
/// @brief Python 用の ClibDelayModel 拡張
///
/// 複数の関数をひとまとめにしているだけなので実は名前空間として用いている．
//////////////////////////////////////////////////////////////////////
class PyClibDelayModel
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

  /// @brief ClibDelayModel を表す PyObject から ClibDelayModel を取り出す．
  /// @return 変換が成功したら true を返す．
  ///
  /// エラーの場合には Python 例外をセットする．
  static
  bool
  FromPyObject(
    PyObject* obj,            ///< [in] ClibDelayModel を表す PyObject
    ClibDelayModel& val,      ///< [out] 変換された ClibDelayModel を格納する変数
    const char* msg = nullptr ///< [in] エラーメッセージ(省略時にはデフォルト値を使う)
  );

  /// @brief ClibDelayModel を表す PyObject を作る．
  /// @return 生成した PyObject を返す．
  ///
  /// 返り値は新しい参照が返される．
  static
  PyObject*
  ToPyObject(
    ClibDelayModel val ///< [in] 値
  );

  /// @brief PyObject が ClibDelayModel タイプか調べる．
  static
  bool
  Check(
    PyObject* obj ///< [in] 対象の PyObject
  );

  /// @brief ClibDelayModel を表す PyObject から ClibDelayModel を取り出す．
  /// @return ClibDelayModel を返す．
  ///
  /// Check(obj) == true であると仮定している．
  static
  ClibDelayModel
  Get(
    PyObject* obj ///< [in] 変換元の PyObject
  );

  /// @brief ClibDelayModel を表すオブジェクトの型定義を返す．
  static
  PyTypeObject*
  _typeobject();

};

END_NAMESPACE_YM

#endif // PYCLIBDELAYMODEL_H
