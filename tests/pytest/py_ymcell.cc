
/// @file py_ym_cell.cc
/// @brief py_ym_cell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "ym_config.h"


BEGIN_NAMESPACE_YM

extern "C"
PyObject* PyInit_ymcell();

END_NAMESPACE_YM

int
main(
  int argc,
  char** argv
)
{
  PyImport_AppendInittab("ymcell", &YM_NAMESPACE::PyInit_ymcell);

  return Py_BytesMain(argc, argv);
}
