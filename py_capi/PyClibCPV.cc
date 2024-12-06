
/// @file PyClibCPV.cc
/// @brief PyClibCPV の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibCPV.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibCPVObject
{
  PyObject_HEAD
  ClibCPV mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibCPV_Type = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 各定数を表す文字列
const char* L_STR = "L";
const char* H_STR = "H";
const char* N_STR = "N";
const char* T_STR = "T";
const char* X_STR = "X";

// 各定数を表す PyObject
PyObject* ClibCPV_L = nullptr;
PyObject* ClibCPV_H = nullptr;
PyObject* ClibCPV_N = nullptr;
PyObject* ClibCPV_T = nullptr;
PyObject* ClibCPV_X = nullptr;

// 生成関数
PyObject*
ClibCPV_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  if ( type != &ClibCPV_Type ) {
    PyErr_SetString(PyExc_TypeError, "ClibCPV cannot be overloaded");
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
  ClibCPV val;
  if ( strcasecmp(name_str, L_STR) == 0 ) {
    val = ClibCPV::L;
  }
  else if ( strcasecmp(name_str, H_STR) == 0 ) {
    val = ClibCPV::H;
  }
  else if ( strcasecmp(name_str, N_STR) == 0 ) {
    val = ClibCPV::N;
  }
  else if ( strcasecmp(name_str, T_STR) == 0 ) {
    val = ClibCPV::T;
  }
  else if ( strcasecmp(name_str, X_STR) == 0 ) {
    val = ClibCPV::X;
  }
  else {
    // エラー
    ostringstream buf;
    buf << "argument 1 must be one of \""
        << L_STR
        << "\", \""
        << H_STR
        << "\", \""
        << N_STR
        << "\", \""
        << T_STR
        << "\", \""
        << X_STR
        << "\"";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
  return PyClibCPV::ToPyObject(val);
}

// 終了関数
void
ClibCPV_dealloc(
  PyObject* self
)
{
  // auto val_obj = reinterpret_cast<ClibCPVObject*>(self);
  // 必要なら val_obj->mVal の終了処理を行う．
  Py_TYPE(self)->tp_free(self);
}

// repr() 関数
PyObject*
ClibCPV_repr(
  PyObject* self
)
{
  auto val = PyClibCPV::Get(self);
  const char* tmp_str = nullptr;
  switch ( val ) {
  case ClibCPV::L: tmp_str = L_STR; break;
  case ClibCPV::H: tmp_str = H_STR; break;
  case ClibCPV::N: tmp_str = N_STR; break;
  case ClibCPV::T: tmp_str = T_STR; break;
  case ClibCPV::X: tmp_str = X_STR; break;
  }
  return Py_BuildValue("s", tmp_str);
}

// 比較関数
PyObject*
ClibCPV_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibCPV::Check(self) &&
       PyClibCPV::Check(other) ) {
    auto val1 = PyClibCPV::Get(self);
    auto val2 = PyClibCPV::Get(other);
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
  ClibCPV val
)
{
  auto obj = ClibCPV_Type.tp_alloc(&ClibCPV_Type, 0);
  auto val_obj = reinterpret_cast<ClibCPVObject*>(obj);
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
  if ( PyDict_SetItemString(ClibCPV_Type.tp_dict, name, obj) < 0 ) {
    return false;
  }
  return true;
}

END_NONAMESPACE


// @brief 初期化する．
bool
PyClibCPV::init(
  PyObject* m
)
{
  ClibCPV_Type.tp_name = "ClibCPV";
  ClibCPV_Type.tp_basicsize = sizeof(ClibCPVObject);
  ClibCPV_Type.tp_itemsize = 0;
  ClibCPV_Type.tp_dealloc = ClibCPV_dealloc;
  ClibCPV_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibCPV_Type.tp_doc = PyDoc_STR("ClibCPV objects");
  ClibCPV_Type.tp_richcompare = ClibCPV_richcmpfunc;
  ClibCPV_Type.tp_new = ClibCPV_new;
  ClibCPV_Type.tp_repr = ClibCPV_repr;
  if ( PyType_Ready(&ClibCPV_Type) < 0 ) {
    return false;
  }

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibCPV", &ClibCPV_Type) ) {
    goto error;
  }

  // 定数オブジェクトの生成
  ClibCPV_L = new_obj(ClibCPV::L);
  ClibCPV_H = new_obj(ClibCPV::H);
  ClibCPV_N = new_obj(ClibCPV::N);
  ClibCPV_T = new_obj(ClibCPV::T);
  ClibCPV_X = new_obj(ClibCPV::X);

  // 定数の登録
  if ( !reg_obj(L_STR, ClibCPV_L) ) {
    goto error;
  }
  if ( !reg_obj(H_STR, ClibCPV_H) ) {
    goto error;
  }
  if ( !reg_obj(N_STR, ClibCPV_N) ) {
    goto error;
  }
  if ( !reg_obj(T_STR, ClibCPV_T) ) {
    goto error;
  }
  if ( !reg_obj(X_STR, ClibCPV_X) ) {
    goto error;
  }

  return true;

 error:

  Py_XDECREF(ClibCPV_L);
  Py_XDECREF(ClibCPV_H);
  Py_XDECREF(ClibCPV_N);
  Py_XDECREF(ClibCPV_T);
  Py_XDECREF(ClibCPV_X);

  return false;
}

// @brief ClibCPV を表す PyObject から ClibCPV を取り出す．
bool
PyClibCPV::FromPyObject(
  PyObject* obj,
  ClibCPV& val,
  const char* msg
)
{

  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibCPV type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibCPV を表す PyObject を作る．
PyObject*
PyClibCPV::ToPyObject(
  ClibCPV val
)
{
  PyObject* obj = nullptr;
  switch ( val ) {
  case ClibCPV::L: obj = ClibCPV_L; break;
  case ClibCPV::H: obj = ClibCPV_H; break;
  case ClibCPV::N: obj = ClibCPV_N; break;
  case ClibCPV::T: obj = ClibCPV_T; break;
  case ClibCPV::X: obj = ClibCPV_X; break;
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibCPV タイプか調べる．
bool
PyClibCPV::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibCPV を表す PyObject から ClibCPV を取り出す．
ClibCPV
PyClibCPV::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibCPVObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibCPV を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibCPV::_typeobject()
{
  return &ClibCPV_Type;
}

END_NAMESPACE_YM
