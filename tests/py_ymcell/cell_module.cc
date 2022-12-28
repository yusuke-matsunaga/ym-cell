
/// @file cell_module.cc
/// @brief Python 用の cell モジュールを定義する．
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ym/PyClibCellLibrary.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// メソッド定義構造体
PyMethodDef cell_methods[] = {
  {nullptr, nullptr, 0, nullptr},
};

// モジュール定義構造体
PyModuleDef cell_module = {
  PyModuleDef_HEAD_INIT,
  "cell",
  PyDoc_STR("Cell: Extension module for cell"),
  -1,
  cell_methods,
};

END_NONAMESPACE

PyMODINIT_FUNC
PyInit_cell()
{
  auto m = PyModule_Create(&cell_module);
  if ( m == nullptr ) {
    return nullptr;
  }

  if ( !PyClibCellLibrary::init(m) ) {
    goto error;
  }

  return m;

 error:
  Py_DECREF(m);
  return nullptr;
}

END_NAMESPACE_YM