
/// @file PyClibCellLibrary.cc
/// @brief Python ClibCellLibrary の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibCellLibrary.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibCellLibraryObject
{
  PyObject_HEAD
  ClibCellLibrary* mPtr;
};

// Python 用のタイプ定義
PyTypeObject ClibCellLibraryType = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 生成関数
PyObject*
ClibCellLibrary_new(
  PyTypeObject* type,
  PyObject* Py_UNUSED(args),
  PyObject* Py_UNUSED(kwds)
)
{
  PyErr_SetString(PyExc_TypeError, "instantiation of 'ClibCellLibrary' is disabled");
  return nullptr;
}

// 終了関数
void
ClibCellLibrary_dealloc(
  PyObject* self
)
{
  auto clibcelllibrary_obj = reinterpret_cast<ClibCellLibraryObject*>(self);
  delete clibcelllibrary_obj->mPtr;
  Py_TYPE(self)->tp_free(self);
}

// mislib 形式のファイルを読み込む．
PyObject*
ClibCellLibrary_mislib(
  PyObject* Py_UNUSED(self), // nullptr のはず
  PyObject* args
)
{
  const char* filename = nullptr;
  if ( !PyArg_ParseTuple(args, "s", &filename) ) {
    return nullptr;
  }

  try {
    // mislib ファイルを読み込む．
    auto clib = ClibCellLibrary::read_mislib(filename);
    auto obj = ClibCellLibraryType.tp_alloc(&ClibCellLibraryType, 0);
    auto clibcelllibrary_obj = reinterpret_cast<ClibCellLibraryObject*>(obj);
    clibcelllibrary_obj->mPtr = new ClibCellLibrary{clib};
    return obj;
  }
  catch ( std::invalid_argument& error ) {
    ostringstream buf;
    buf << "read_mislib(\"" << filename << "\") failed";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
}

// liberty 形式のファイルを読み込む．
PyObject*
ClibCellLibrary_liberty(
  PyObject* Py_UNUSED(self), // nullptr のはず
  PyObject* args
)
{
  const char* filename = nullptr;
  if ( !PyArg_ParseTuple(args, "s", &filename) ) {
    return nullptr;
  }

  try {
    // liberty ファイルを読み込む．
    auto clib = ClibCellLibrary::read_liberty(filename);
    auto obj = ClibCellLibraryType.tp_alloc(&ClibCellLibraryType, 0);
    auto clibcelllibrary_obj = reinterpret_cast<ClibCellLibraryObject*>(obj);
    clibcelllibrary_obj->mPtr = new ClibCellLibrary{clib};
    return obj;
  }
  catch ( std::invalid_argument& error ) {
    ostringstream buf;
    buf << "read_liberty(\"" << filename << "\") failed";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
}

PyObject*
ClibCellLibrary_is_valid(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto& lib = PyClibCellLibrary::Get(self);
  auto val = lib.is_valid();
  return PyBool_FromLong(val);
}

// 内容を表示する．
PyObject*
ClibCellLibrary_display(
  PyObject* self,
  PyObject* args
)
{
  const char* filename = nullptr;
  if ( !PyArg_ParseTuple(args, "|s", &filename) ) {
    return nullptr;
  }

  auto& lib = PyClibCellLibrary::Get(self);
  if ( filename == nullptr ) {
    lib.display(cout);
  }
  else {
    ofstream fs{filename};
    if ( !fs ) {
      ostringstream buf;
      buf << filename << ": Could not open file";
      PyErr_SetString(PyExc_ValueError, buf.str().c_str());
      return nullptr;
    }
    lib.display(fs);
  }

  Py_RETURN_NONE;
}

// 内容を表す文字列のリストを作る．
PyObject*
ClibCellLibrary_to_string_list(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto& lib = PyClibCellLibrary::Get(self);
  ostringstream buf;
  lib.display(buf);

  istringstream ibuf{buf.str()};
  string line_buff;
  vector<string> line_list;
  while ( getline(ibuf, line_buff) ) {
    line_list.push_back(line_buff);
  }

  SizeType n = line_list.size();
  auto obj = PyList_New(n);
  for ( SizeType i = 0; i < n; ++ i ) {
    auto str_obj = Py_BuildValue("s", line_list[i].c_str());
    PyList_SET_ITEM(obj, i, str_obj);
  }

  return obj;
}

// メソッド定義
PyMethodDef ClibCellLibrary_methods[] = {
  {"read_mislib", ClibCellLibrary_mislib, METH_VARARGS | METH_STATIC,
   PyDoc_STR("read mislib file")},
  {"read_liberty", ClibCellLibrary_liberty, METH_VARARGS | METH_STATIC,
   PyDoc_STR("read liberty(.lib) file")},
  {"is_valid", ClibCellLibrary_is_valid, METH_NOARGS,
   PyDoc_STR("check if valid")},
  {"display", ClibCellLibrary_display, METH_VARARGS,
   PyDoc_STR("display the contents of the cell library")},
  {"to_string_list", ClibCellLibrary_to_string_list, METH_NOARGS,
   PyDoc_STR("return the list of strings representing the cell library")},
  {nullptr, nullptr, 0, nullptr}
};

END_NONAMESPACE

// 比較関数
PyObject*
ClibCellLibrary_richcompfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibCellLibrary::Check(self) &&
       PyClibCellLibrary::Check(other) ) {
    auto& val1 = PyClibCellLibrary::Get(self);
    auto& val2 = PyClibCellLibrary::Get(other);
    if ( op == Py_EQ ) {
      return PyBool_FromLong(val1 == val2);
    }
    if ( op == Py_NE ) {
      return PyBool_FromLong(val1 != val2);
    }
  }
  Py_RETURN_NOTIMPLEMENTED;
}

// @brief 'ClibCellLibrary' オブジェクトを使用可能にする．
bool
PyClibCellLibrary::init(
  PyObject* m
)
{
  ClibCellLibraryType.tp_name = "ClibCellLibrary";
  ClibCellLibraryType.tp_basicsize = sizeof(ClibCellLibraryObject);
  ClibCellLibraryType.tp_itemsize = 0;
  ClibCellLibraryType.tp_dealloc = ClibCellLibrary_dealloc;
  ClibCellLibraryType.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibCellLibraryType.tp_doc = PyDoc_STR("ClibCellLibrary objects");
  ClibCellLibraryType.tp_richcompare = ClibCellLibrary_richcompfunc;
  ClibCellLibraryType.tp_methods = ClibCellLibrary_methods;
  ClibCellLibraryType.tp_new = ClibCellLibrary_new;

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibCellLibrary", &ClibCellLibraryType) ) {
    goto error;
  }

  return true;

 error:

  return false;
}

// @brief ClibCellLibrary を PyObject に変換する．
PyObject*
PyClibCellLibrary::ToPyObject(
  const ClibCellLibrary& val
)
{
  auto obj = ClibCellLibraryType.tp_alloc(&ClibCellLibraryType, 0);
  auto lib_obj = reinterpret_cast<ClibCellLibraryObject*>(obj);
  lib_obj->mPtr = new ClibCellLibrary{val};
  return obj;
}

// @brief PyObject が ClibCellLibrary タイプか調べる．
bool
PyClibCellLibrary::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibCellLibrary を表す PyObject から ClibCellLibrary を取り出す．
const ClibCellLibrary&
PyClibCellLibrary::Get(
  PyObject* obj
)
{
  auto clibcelllibrary_obj = reinterpret_cast<ClibCellLibraryObject*>(obj);
  return *clibcelllibrary_obj->mPtr;
}

// @brief ClibCellLibrary を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibCellLibrary::_typeobject()
{
  return &ClibCellLibraryType;
}

END_NAMESPACE_YM
