
/// @file PyClibCellLibrary.cc
/// @brief Python ClibCellLibrary の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022, 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibCellLibrary.h"
#include "pym/PyClibTechnology.h"
#include "pym/PyClibDelayModel.h"
#include "pym/PyClibCell.h"
#include "pym/PyModule.h"
#include "ym/ClibLibraryPtr.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibCellLibraryObject
{
  PyObject_HEAD
  const CiCellLibrary* mPtr;
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
  auto lib_obj = reinterpret_cast<ClibCellLibraryObject*>(self);
  auto ptr = lib_obj->mPtr;
  if ( ptr != nullptr ) {
    ptr->dec_ref();
  }
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
    return PyClibCellLibrary::ToPyObject(clib);
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
    return PyClibCellLibrary::ToPyObject(clib);
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
  auto lib = PyClibCellLibrary::Get(self);
  bool val = lib != nullptr;
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

  auto lib = ClibCellLibrary{PyClibCellLibrary::Get(self)};
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
  auto lib = ClibCellLibrary{PyClibCellLibrary::Get(self)};
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

PyObject*
ClibCellLibrary_name(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->name();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_technology(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->technology();
  return PyClibTechnology::ToPyObject(val);
}

PyObject*
ClibCellLibrary_delay_model(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->delay_model();
  return PyClibDelayModel::ToPyObject(val);
}

PyObject*
ClibCellLibrary_bus_naming_style(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->bus_naming_style();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_date(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->date();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_revision(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->revision();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_comment(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->comment();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_time_unit(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->time_unit();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_voltage_unit(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->voltage_unit();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_current_unit(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->current_unit();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_pulling_resistance_unit(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->pulling_resistance_unit();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_capacitive_load_unit(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto unit = lib->capacitive_load_unit();
  auto unit_str = lib->capacitive_load_unit_str();
  return Py_BuildValue("(d, s)", unit, unit_str.c_str());
}

PyObject*
ClibCellLibrary_leakage_power_unit(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto val = lib->leakage_power_unit();
  return Py_BuildValue("s", val.c_str());
}

PyObject*
ClibCellLibrary_cell_list(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto lib = PyClibCellLibrary::Get(self);
  auto cell_list = lib->cell_list();
  SizeType n = cell_list.size();
  auto obj = PyList_New(n);
  for ( SizeType i = 0; i < n; ++ i ) {
    auto cell = cell_list[i];
    auto cell_obj = PyClibCell::ToPyObject(cell);
    PyList_SetItem(obj, i, cell_obj);
  }
  return obj;
}

// getter/setter 関数テーブル
PyGetSetDef ClibCellLibrary_getsetters[] = {
  {"name", ClibCellLibrary_name, nullptr,
   PyDoc_STR("name"), nullptr},
  {"technology", ClibCellLibrary_technology, nullptr,
   PyDoc_STR("technology"), nullptr},
  {"delay_model", ClibCellLibrary_delay_model, nullptr,
   PyDoc_STR("delay_model"), nullptr},
  {"bus_naming_style", ClibCellLibrary_bus_naming_style, nullptr,
   PyDoc_STR("bus_naming_style"), nullptr},
  {"date", ClibCellLibrary_date, nullptr,
   PyDoc_STR("date"), nullptr},
  {"revision", ClibCellLibrary_revision, nullptr,
   PyDoc_STR("revision"), nullptr},
  {"comment", ClibCellLibrary_comment, nullptr,
   PyDoc_STR("comment"), nullptr},
  {"time_unit", ClibCellLibrary_time_unit, nullptr,
   PyDoc_STR("time_unit"), nullptr},
  {"voltage_unit", ClibCellLibrary_voltage_unit, nullptr,
   PyDoc_STR("voltage_unit"), nullptr},
  {"current_unit", ClibCellLibrary_current_unit, nullptr,
   PyDoc_STR("current_unit"), nullptr},
  {"pulling_resistance_unit", ClibCellLibrary_pulling_resistance_unit, nullptr,
   PyDoc_STR("pulling_resistance_unit"), nullptr},
  {"capacitive_load_unit", ClibCellLibrary_capacitive_load_unit, nullptr,
   PyDoc_STR("capacitive_load_unit"), nullptr},
  {"leakage_power_unit", ClibCellLibrary_leakage_power_unit, nullptr,
   PyDoc_STR("leakage_power_unit"), nullptr},
  {"cell_list", ClibCellLibrary_cell_list, nullptr,
   PyDoc_STR("cell list"), nullptr},
  {nullptr, nullptr, nullptr, nullptr}
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
    auto val1 = PyClibCellLibrary::Get(self);
    auto val2 = PyClibCellLibrary::Get(other);
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
  ClibCellLibraryType.tp_getset = ClibCellLibrary_getsetters;
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
  return ToPyObject(val._impl());
}

// @brief ClibCellLibrary を PyObject に変換する．
PyObject*
PyClibCellLibrary::ToPyObject(
  const CiCellLibrary* val
)
{
  auto obj = ClibCellLibraryType.tp_alloc(&ClibCellLibraryType, 0);
  auto lib_obj = reinterpret_cast<ClibCellLibraryObject*>(obj);
  lib_obj->mPtr = val;
  if ( val != nullptr ) {
    val->inc_ref();
  }
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
const CiCellLibrary*
PyClibCellLibrary::Get(
  PyObject* obj
)
{
  auto lib_obj = reinterpret_cast<ClibCellLibraryObject*>(obj);
  return lib_obj->mPtr;
}

// @brief ClibCellLibrary を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibCellLibrary::_typeobject()
{
  return &ClibCellLibraryType;
}

END_NAMESPACE_YM_CLIB
