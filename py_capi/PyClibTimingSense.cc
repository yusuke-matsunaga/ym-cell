
/// @file PyClibTimingSense.cc
/// @brief PyClibTimingSense の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibTimingSense.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibTimingSenseObject
{
  PyObject_HEAD
  ClibTimingSense mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibTimingSense_Type = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 各定数を表す文字列
const char* POSITIVE_UNATE_STR = "positive_unate";
const char* NEGATIVE_UNATE_STR = "negative_unate";
const char* NON_UNATE_STR      = "non_unate";

// 各定数を表す PyObject
PyObject* ClibTimingSense_POSITIVE_UNATE = nullptr;
PyObject* ClibTimingSense_NEGATIVE_UNATE = nullptr;
PyObject* ClibTimingSense_NON_UNATE      = nullptr;

// 生成関数
PyObject*
ClibTimingSense_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  if ( type != &ClibTimingSense_Type ) {
    PyErr_SetString(PyExc_TypeError, "ClibTimingSense cannot be overloaded");
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
  ClibTimingSense val;
  if ( strcasecmp(name_str, POSITIVE_UNATE_STR) == 0 ) {
    val = ClibTimingSense::positive_unate;
  }
  else if ( strcasecmp(name_str, NEGATIVE_UNATE_STR) == 0 ) {
    val = ClibTimingSense::negative_unate;
  }
  else if ( strcasecmp(name_str, NON_UNATE_STR) == 0 ) {
    val = ClibTimingSense::non_unate;
  }
  else if ( strcasecmp(name_str, "none") == 0 ) {
    val = ClibTimingSense::none;
  }
  else {
    // エラー
    ostringstream buf;
    buf << "argument 1 must be one of \""
        << POSITIVE_UNATE_STR
        << "\", \""
        << NEGATIVE_UNATE_STR
        << "\", \""
        << NON_UNATE_STR
        << "\", \""
        << "none"
        << "\"";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
  return PyClibTimingSense::ToPyObject(val);
}

// 終了関数
void
ClibTimingSense_dealloc(
  PyObject* self
)
{
  // auto val_obj = reinterpret_cast<ClibTimingSenseObject*>(self);
  // 必要なら val_obj->mVal の終了処理を行う．
  Py_TYPE(self)->tp_free(self);
}

// repr() 関数
PyObject*
ClibTimingSense_repr(
  PyObject* self
)
{
  auto val = PyClibTimingSense::Get(self);
  const char* tmp_str = nullptr;
  switch ( val ) {
  case ClibTimingSense::positive_unate: tmp_str = POSITIVE_UNATE_STR; break;
  case ClibTimingSense::negative_unate: tmp_str = NEGATIVE_UNATE_STR; break;
  case ClibTimingSense::non_unate:      tmp_str = NON_UNATE_STR; break;
  case ClibTimingSense::none:           tmp_str = ""; break;
  }
  return Py_BuildValue("s", tmp_str);
}

// 比較関数
PyObject*
ClibTimingSense_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibTimingSense::Check(self) &&
       PyClibTimingSense::Check(other) ) {
    auto val1 = PyClibTimingSense::Get(self);
    auto val2 = PyClibTimingSense::Get(other);
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
  ClibTimingSense val
)
{
  auto obj = ClibTimingSense_Type.tp_alloc(&ClibTimingSense_Type, 0);
  auto val_obj = reinterpret_cast<ClibTimingSenseObject*>(obj);
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
  if ( PyDict_SetItemString(ClibTimingSense_Type.tp_dict, name, obj) < 0 ) {
    return false;
  }
  return true;
}

END_NONAMESPACE


// @brief 初期化する．
bool
PyClibTimingSense::init(
  PyObject* m
)
{
  ClibTimingSense_Type.tp_name = "ClibTimingSense";
  ClibTimingSense_Type.tp_basicsize = sizeof(ClibTimingSenseObject);
  ClibTimingSense_Type.tp_itemsize = 0;
  ClibTimingSense_Type.tp_dealloc = ClibTimingSense_dealloc;
  ClibTimingSense_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibTimingSense_Type.tp_doc = PyDoc_STR("ClibTimingSense objects");
  ClibTimingSense_Type.tp_richcompare = ClibTimingSense_richcmpfunc;
  ClibTimingSense_Type.tp_new = ClibTimingSense_new;
  ClibTimingSense_Type.tp_repr = ClibTimingSense_repr;
  if ( PyType_Ready(&ClibTimingSense_Type) < 0 ) {
    return false;
  }

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibTimingSense", &ClibTimingSense_Type) ) {
    goto error;
  }

  // 定数オブジェクトの生成
  ClibTimingSense_POSITIVE_UNATE = new_obj(ClibTimingSense::positive_unate);
  ClibTimingSense_NEGATIVE_UNATE = new_obj(ClibTimingSense::negative_unate);
  ClibTimingSense_NON_UNATE      = new_obj(ClibTimingSense::non_unate);

  // 定数の登録
  if ( !reg_obj(POSITIVE_UNATE_STR, ClibTimingSense_POSITIVE_UNATE) ) {
    goto error;
  }
  if ( !reg_obj(NEGATIVE_UNATE_STR, ClibTimingSense_NEGATIVE_UNATE) ) {
    goto error;
  }
  if ( !reg_obj(NON_UNATE_STR, ClibTimingSense_NON_UNATE) ) {
    goto error;
  }

  return true;

 error:

  Py_XDECREF(ClibTimingSense_POSITIVE_UNATE);
  Py_XDECREF(ClibTimingSense_NEGATIVE_UNATE);
  Py_XDECREF(ClibTimingSense_NON_UNATE);

  return false;
}

// @brief ClibTimingSense を表す PyObject から ClibTimingSense を取り出す．
bool
PyClibTimingSense::FromPyObject(
  PyObject* obj,
  ClibTimingSense& val,
  const char* msg
)
{
  if ( obj == Py_None ) {
    // 特例: None は ClibTimingSense::none に変換する．
    val = ClibTimingSense::none;
    return true;
  }

  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibTimingSense type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibTimingSense を表す PyObject を作る．
PyObject*
PyClibTimingSense::ToPyObject(
  ClibTimingSense val
)
{
  PyObject* obj = nullptr;
  switch ( val ) {
  case ClibTimingSense::positive_unate: obj = ClibTimingSense_POSITIVE_UNATE; break;
  case ClibTimingSense::negative_unate: obj = ClibTimingSense_NEGATIVE_UNATE; break;
  case ClibTimingSense::non_unate:      obj = ClibTimingSense_NON_UNATE; break;
  case ClibTimingSense::none:           Py_RETURN_NONE;
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibTimingSense タイプか調べる．
bool
PyClibTimingSense::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibTimingSense を表す PyObject から ClibTimingSense を取り出す．
ClibTimingSense
PyClibTimingSense::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibTimingSenseObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibTimingSense を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibTimingSense::_typeobject()
{
  return &ClibTimingSense_Type;
}

END_NAMESPACE_YM
