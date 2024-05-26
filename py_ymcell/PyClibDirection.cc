
/// @file PyClibDirection.cc
/// @brief PyClibDirection の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibDirection.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibDirectionObject
{
  PyObject_HEAD
  ClibDirection mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibDirectionType = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 各定数を表す文字列
const char* INPUT_STR    = "input";
const char* OUTPUT_STR   = "output";
const char* INOUT_STR    = "inout";
const char* INTERNAL_STR = "internal";

// 各定数を表す PyObject
PyObject* ClibDirection_INPUT    = nullptr;
PyObject* ClibDirection_OUTPUT   = nullptr;
PyObject* ClibDirection_INOUT    = nullptr;
PyObject* ClibDirection_INTERNAL = nullptr;

// 生成関数
PyObject*
ClibDirection_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  if ( type != &ClibDirectionType ) {
    PyErr_SetString(PyExc_TypeError, "ClibDirection cannot be overloaded");
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
  ClibDirection val;
  if ( strcasecmp(name_str, INPUT_STR) == 0 ) {
    val = ClibDirection::input;
  }
  else if ( strcasecmp(name_str, OUTPUT_STR) == 0 ) {
    val = ClibDirection::output;
  }
  else if ( strcasecmp(name_str, INOUT_STR) == 0 ) {
    val = ClibDirection::inout;
  }
  else if ( strcasecmp(name_str, INTERNAL_STR) == 0 ) {
    val = ClibDirection::internal;
  }
  else if ( strcasecmp(name_str, "none") == 0 ) {
    val = ClibDirection::none;
  }
  else {
    // エラー
    ostringstream buf;
    buf << "argument 1 must be one of \""
        << INPUT_STR
        << "\", \""
        << OUTPUT_STR
        << "\", \""
        << INOUT_STR
        << "\", \""
        << INTERNAL_STR
        << "\", \""
        << "none"
        << "\"";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
  return PyClibDirection::ToPyObject(val);
}

// 終了関数
void
ClibDirection_dealloc(
  PyObject* self
)
{
  // auto val_obj = reinterpret_cast<ClibDirectionObject*>(self);
  // 必要なら val_obj->mVal の終了処理を行う．
  Py_TYPE(self)->tp_free(self);
}

// repr() 関数
PyObject*
ClibDirection_repr(
  PyObject* self
)
{
  auto val = PyClibDirection::Get(self);
  const char* tmp_str = nullptr;
  switch ( val ) {
  case ClibDirection::input:    tmp_str = INPUT_STR; break;
  case ClibDirection::output:   tmp_str = OUTPUT_STR; break;
  case ClibDirection::inout:    tmp_str = INOUT_STR; break;
  case ClibDirection::internal: tmp_str = INTERNAL_STR; break;
  case ClibDirection::none:     tmp_str = ""; break;
  }
  return Py_BuildValue("s", tmp_str);
}

// 比較関数
PyObject*
ClibDirection_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibDirection::Check(self) &&
       PyClibDirection::Check(other) ) {
    auto val1 = PyClibDirection::Get(self);
    auto val2 = PyClibDirection::Get(other);
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
  ClibDirection val
)
{
  auto obj = ClibDirectionType.tp_alloc(&ClibDirectionType, 0);
  auto val_obj = reinterpret_cast<ClibDirectionObject*>(obj);
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
  if ( PyDict_SetItemString(ClibDirectionType.tp_dict, name, obj) < 0 ) {
    return false;
  }
  return true;
}

END_NONAMESPACE


// @brief 初期化する．
bool
PyClibDirection::init(
  PyObject* m
)
{
  ClibDirectionType.tp_name = "ClibDirection";
  ClibDirectionType.tp_basicsize = sizeof(ClibDirectionObject);
  ClibDirectionType.tp_itemsize = 0;
  ClibDirectionType.tp_dealloc = ClibDirection_dealloc;
  ClibDirectionType.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibDirectionType.tp_doc = PyDoc_STR("ClibDirection objects");
  ClibDirectionType.tp_richcompare = ClibDirection_richcmpfunc;
  ClibDirectionType.tp_new = ClibDirection_new;
  ClibDirectionType.tp_repr = ClibDirection_repr;
  if ( PyType_Ready(&ClibDirectionType) < 0 ) {
    return false;
  }

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibDirection", &ClibDirectionType) ) {
    goto error;
  }

  // 定数オブジェクトの生成
  ClibDirection_INPUT    = new_obj(ClibDirection::input);
  ClibDirection_OUTPUT   = new_obj(ClibDirection::output);
  ClibDirection_INOUT    = new_obj(ClibDirection::inout);
  ClibDirection_INTERNAL = new_obj(ClibDirection::internal);

  // 定数の登録
  if ( !reg_obj(INPUT_STR, ClibDirection_INPUT) ) {
    goto error;
  }
  if ( !reg_obj(OUTPUT_STR, ClibDirection_OUTPUT) ) {
    goto error;
  }
  if ( !reg_obj(INOUT_STR, ClibDirection_INOUT) ) {
    goto error;
  }
  if ( !reg_obj(INTERNAL_STR, ClibDirection_INTERNAL) ) {
    goto error;
  }

  return true;

 error:

  Py_XDECREF(ClibDirection_INPUT);
  Py_XDECREF(ClibDirection_OUTPUT);
  Py_XDECREF(ClibDirection_INOUT);
  Py_XDECREF(ClibDirection_INTERNAL);

  return false;
}

// @brief ClibDirection を表す PyObject から ClibDirection を取り出す．
bool
PyClibDirection::FromPyObject(
  PyObject* obj,
  ClibDirection& val,
  const char* msg
)
{
  if ( obj == Py_None ) {
    // 特例: None は ClibDirection::none に変換する．
    val = ClibDirection::none;
    return true;
  }

  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibDirection type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibDirection を表す PyObject を作る．
PyObject*
PyClibDirection::ToPyObject(
  ClibDirection val
)
{
  PyObject* obj = nullptr;
  switch ( val ) {
  case ClibDirection::input:    obj = ClibDirection_INPUT; break;
  case ClibDirection::output:   obj = ClibDirection_OUTPUT; break;
  case ClibDirection::inout:    obj = ClibDirection_INOUT; break;
  case ClibDirection::internal: obj = ClibDirection_INTERNAL; break;
  case ClibDirection::none:     Py_RETURN_NONE;
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibDirection タイプか調べる．
bool
PyClibDirection::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibDirection を表す PyObject から ClibDirection を取り出す．
ClibDirection
PyClibDirection::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibDirectionObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibDirection を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibDirection::_typeobject()
{
  return &ClibDirectionType;
}

END_NAMESPACE_YM_CLIB
