
/// @file PyClibTechnology.cc
/// @brief PyClibTechnology の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibTechnology.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibTechnologyObject
{
  PyObject_HEAD
  ClibTechnology mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibTechnologyType = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 各定数を表す文字列
const char* CMOS_STR = "cmos";
const char* FPGA_STR = "fpga";

// 各定数を表す PyObject
PyObject* ClibTechnology_CMOS = nullptr;
PyObject* ClibTechnology_FPGA = nullptr;

// 生成関数
PyObject*
ClibTechnology_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  if ( type != &ClibTechnologyType ) {
    PyErr_SetString(PyExc_TypeError, "ClibTechnology cannot be overloaded");
    return nullptr;
  }

  // キーワード引数
  static const char* kwlist[] = {
    "name",
    nullptr
  };
  const char* name_str = nullptr;
  if ( !PyArg_ParseTupleAndKeywords(args, kwds, "s",
				    const_cast<char**>(kwlist),
				    &name_str) ) {
    return nullptr;
  }
  ClibTechnology val;
  if ( strcasecmp(name_str, CMOS_STR) == 0 ) {
    val = ClibTechnology::cmos;
  }
  else if ( strcasecmp(name_str, FPGA_STR) == 0 ) {
    val = ClibTechnology::fpga;
  }
  else if ( strcasecmp(name_str, "none") == 0 ) {
    val = ClibTechnology::none;
  }
  else {
    // エラー
    ostringstream buf;
    buf << "argument 1 must be one of \""
        << CMOS_STR
        << "\", \""
        << FPGA_STR
        << "\", \""
        << "none"
        << "\"";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
  return PyClibTechnology::ToPyObject(val);
}

// 終了関数
void
ClibTechnology_dealloc(
  PyObject* self
)
{
  // auto val_obj = reinterpret_cast<ClibTechnologyObject*>(self);
  // 必要なら val_obj->mVal の終了処理を行う．
  Py_TYPE(self)->tp_free(self);
}

// repr() 関数
PyObject*
ClibTechnology_repr(
  PyObject* self
)
{
  auto val = PyClibTechnology::Get(self);
  const char* tmp_str = nullptr;
  switch ( val ) {
  case ClibTechnology::cmos: tmp_str = CMOS_STR; break;
  case ClibTechnology::fpga: tmp_str = FPGA_STR; break;
  case ClibTechnology::none: tmp_str = ""; break;
  }
  return Py_BuildValue("s", tmp_str);
}

// 比較関数
PyObject*
ClibTechnology_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibTechnology::Check(self) &&
       PyClibTechnology::Check(other) ) {
    auto val1 = PyClibTechnology::Get(self);
    auto val2 = PyClibTechnology::Get(other);
    if ( op == Py_EQ ) {
      return PyBool_FromLong(val1 == val2);
    }
    if ( op == Py_NE ) {
      return PyBool_FromLong(val1 != val2);
    }
  }
  Py_RETURN_NOTIMPLEMENTED;
}

// 定数オブジェクトの生成
PyObject*
new_obj(
  ClibTechnology val
)
{
  auto obj = ClibTechnologyType.tp_alloc(&ClibTechnologyType, 0);
  auto val_obj = reinterpret_cast<ClibTechnologyObject*>(obj);
  val_obj->mVal = val;
  return obj;
}

// 定数オブジェクトの登録
bool
reg_obj(
  const char* name,
  PyObject* obj
)
{
  if ( PyDict_SetItemString(ClibTechnologyType.tp_dict, name, obj) < 0 ) {
    return false;
  }
  return true;
}

END_NONAMESPACE


// @brief 初期化する．
bool
PyClibTechnology::init(
  PyObject* m
)
{
  ClibTechnologyType.tp_name = "ClibTechnology";
  ClibTechnologyType.tp_basicsize = sizeof(ClibTechnologyObject);
  ClibTechnologyType.tp_itemsize = 0;
  ClibTechnologyType.tp_dealloc = ClibTechnology_dealloc;
  ClibTechnologyType.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibTechnologyType.tp_doc = PyDoc_STR("ClibTechnology objects");
  ClibTechnologyType.tp_richcompare = ClibTechnology_richcmpfunc;
  ClibTechnologyType.tp_new = ClibTechnology_new;
  ClibTechnologyType.tp_repr = ClibTechnology_repr;
  if ( PyType_Ready(&ClibTechnologyType) < 0 ) {
    return false;
  }

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibTechnology", &ClibTechnologyType) ) {
    goto error;
  }

  // 定数オブジェクトの生成
  ClibTechnology_CMOS = new_obj(ClibTechnology::cmos);
  ClibTechnology_FPGA = new_obj(ClibTechnology::fpga);

  // 定数の登録
  if ( !reg_obj(CMOS_STR, ClibTechnology_CMOS) ) {
    goto error;
  }
  if ( !reg_obj(FPGA_STR, ClibTechnology_FPGA) ) {
    goto error;
  }

  return true;

 error:

  Py_XDECREF(ClibTechnology_CMOS);
  Py_XDECREF(ClibTechnology_FPGA);

  return false;
}

// @brief ClibTechnology を表す PyObject から ClibTechnology を取り出す．
bool
PyClibTechnology::FromPyObject(
  PyObject* obj,
  ClibTechnology& val,
  const char* msg
)
{
  if ( obj == Py_None ) {
    // 特例: None は ClibTechnology::none に変換する．
    val = ClibTechnology::none;
    return true;
  }

  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibTechnology type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibTechnology を表す PyObject を作る．
PyObject*
PyClibTechnology::ToPyObject(
  ClibTechnology val
)
{
  PyObject* obj = nullptr;
  switch ( val ) {
  case ClibTechnology::cmos: obj = ClibTechnology_CMOS; break;
  case ClibTechnology::fpga: obj = ClibTechnology_FPGA; break;
  case ClibTechnology::none: Py_RETURN_NONE;
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibTechnology タイプか調べる．
bool
PyClibTechnology::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibTechnology を表す PyObject から ClibTechnology を取り出す．
ClibTechnology
PyClibTechnology::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibTechnologyObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibTechnology を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibTechnology::_typeobject()
{
  return &ClibTechnologyType;
}

END_NAMESPACE_YM
