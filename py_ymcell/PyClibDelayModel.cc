
/// @file PyClibDelayModel.cc
/// @brief PyClibDelayModel の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibDelayModel.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibDelayModelObject
{
  PyObject_HEAD
  ClibDelayModel mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibDelayModel_Type = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 各定数を表す文字列
const char* GENERIC_CMOS_STR   = "generic_cmos";
const char* TABLE_LOOKUP_STR   = "table_lookup";
const char* PIECEWISE_CMOS_STR = "piecewise_cmos";
const char* CMOS2_STR          = "cmos2";
const char* DCM_STR            = "dcm";
const char* POLYNOMIAL_STR     = "polynomial";

// 各定数を表す PyObject
PyObject* ClibDelayModel_GENERIC_CMOS   = nullptr;
PyObject* ClibDelayModel_TABLE_LOOKUP   = nullptr;
PyObject* ClibDelayModel_PIECEWISE_CMOS = nullptr;
PyObject* ClibDelayModel_CMOS2          = nullptr;
PyObject* ClibDelayModel_DCM            = nullptr;
PyObject* ClibDelayModel_POLYNOMIAL     = nullptr;

// 生成関数
PyObject*
ClibDelayModel_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  if ( type != &ClibDelayModel_Type ) {
    PyErr_SetString(PyExc_TypeError, "ClibDelayModel cannot be overloaded");
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
  ClibDelayModel val;
  if ( strcasecmp(name_str, GENERIC_CMOS_STR) == 0 ) {
    val = ClibDelayModel::generic_cmos;
  }
  else if ( strcasecmp(name_str, TABLE_LOOKUP_STR) == 0 ) {
    val = ClibDelayModel::table_lookup;
  }
  else if ( strcasecmp(name_str, PIECEWISE_CMOS_STR) == 0 ) {
    val = ClibDelayModel::piecewise_cmos;
  }
  else if ( strcasecmp(name_str, CMOS2_STR) == 0 ) {
    val = ClibDelayModel::cmos2;
  }
  else if ( strcasecmp(name_str, DCM_STR) == 0 ) {
    val = ClibDelayModel::dcm;
  }
  else if ( strcasecmp(name_str, POLYNOMIAL_STR) == 0 ) {
    val = ClibDelayModel::polynomial;
  }
  else if ( strcasecmp(name_str, "none") == 0 ) {
    val = ClibDelayModel::none;
  }
  else {
    // エラー
    ostringstream buf;
    buf << "argument 1 must be one of \""
        << GENERIC_CMOS_STR
        << "\", \""
        << TABLE_LOOKUP_STR
        << "\", \""
        << PIECEWISE_CMOS_STR
        << "\", \""
        << CMOS2_STR
        << "\", \""
        << DCM_STR
        << "\", \""
        << POLYNOMIAL_STR
        << "\", \""
        << "none"
        << "\"";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
  return PyClibDelayModel::ToPyObject(val);
}

// 終了関数
void
ClibDelayModel_dealloc(
  PyObject* self
)
{
  // auto val_obj = reinterpret_cast<ClibDelayModelObject*>(self);
  // 必要なら val_obj->mVal の終了処理を行う．
  Py_TYPE(self)->tp_free(self);
}

// repr() 関数
PyObject*
ClibDelayModel_repr(
  PyObject* self
)
{
  auto val = PyClibDelayModel::Get(self);
  const char* tmp_str = nullptr;
  switch ( val ) {
  case ClibDelayModel::generic_cmos:   tmp_str = GENERIC_CMOS_STR; break;
  case ClibDelayModel::table_lookup:   tmp_str = TABLE_LOOKUP_STR; break;
  case ClibDelayModel::piecewise_cmos: tmp_str = PIECEWISE_CMOS_STR; break;
  case ClibDelayModel::cmos2:          tmp_str = CMOS2_STR; break;
  case ClibDelayModel::dcm:            tmp_str = DCM_STR; break;
  case ClibDelayModel::polynomial:     tmp_str = POLYNOMIAL_STR; break;
  case ClibDelayModel::none:           tmp_str = ""; break;
  }
  return Py_BuildValue("s", tmp_str);
}

// 比較関数
PyObject*
ClibDelayModel_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibDelayModel::Check(self) &&
       PyClibDelayModel::Check(other) ) {
    auto val1 = PyClibDelayModel::Get(self);
    auto val2 = PyClibDelayModel::Get(other);
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
  ClibDelayModel val
)
{
  auto obj = ClibDelayModel_Type.tp_alloc(&ClibDelayModel_Type, 0);
  auto val_obj = reinterpret_cast<ClibDelayModelObject*>(obj);
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
  if ( PyDict_SetItemString(ClibDelayModel_Type.tp_dict, name, obj) < 0 ) {
    return false;
  }
  return true;
}

END_NONAMESPACE


// @brief 初期化する．
bool
PyClibDelayModel::init(
  PyObject* m
)
{
  ClibDelayModel_Type.tp_name = "ClibDelayModel";
  ClibDelayModel_Type.tp_basicsize = sizeof(ClibDelayModelObject);
  ClibDelayModel_Type.tp_itemsize = 0;
  ClibDelayModel_Type.tp_dealloc = ClibDelayModel_dealloc;
  ClibDelayModel_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibDelayModel_Type.tp_doc = PyDoc_STR("ClibDelayModel objects");
  ClibDelayModel_Type.tp_richcompare = ClibDelayModel_richcmpfunc;
  ClibDelayModel_Type.tp_new = ClibDelayModel_new;
  ClibDelayModel_Type.tp_repr = ClibDelayModel_repr;
  if ( PyType_Ready(&ClibDelayModel_Type) < 0 ) {
    return false;
  }

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibDelayModel", &ClibDelayModel_Type) ) {
    goto error;
  }

  // 定数オブジェクトの生成
  ClibDelayModel_GENERIC_CMOS   = new_obj(ClibDelayModel::generic_cmos);
  ClibDelayModel_TABLE_LOOKUP   = new_obj(ClibDelayModel::table_lookup);
  ClibDelayModel_PIECEWISE_CMOS = new_obj(ClibDelayModel::piecewise_cmos);
  ClibDelayModel_CMOS2          = new_obj(ClibDelayModel::cmos2);
  ClibDelayModel_DCM            = new_obj(ClibDelayModel::dcm);
  ClibDelayModel_POLYNOMIAL     = new_obj(ClibDelayModel::polynomial);

  // 定数の登録
  if ( !reg_obj(GENERIC_CMOS_STR, ClibDelayModel_GENERIC_CMOS) ) {
    goto error;
  }
  if ( !reg_obj(TABLE_LOOKUP_STR, ClibDelayModel_TABLE_LOOKUP) ) {
    goto error;
  }
  if ( !reg_obj(PIECEWISE_CMOS_STR, ClibDelayModel_PIECEWISE_CMOS) ) {
    goto error;
  }
  if ( !reg_obj(CMOS2_STR, ClibDelayModel_CMOS2) ) {
    goto error;
  }
  if ( !reg_obj(DCM_STR, ClibDelayModel_DCM) ) {
    goto error;
  }
  if ( !reg_obj(POLYNOMIAL_STR, ClibDelayModel_POLYNOMIAL) ) {
    goto error;
  }

  return true;

 error:

  Py_XDECREF(ClibDelayModel_GENERIC_CMOS);
  Py_XDECREF(ClibDelayModel_TABLE_LOOKUP);
  Py_XDECREF(ClibDelayModel_PIECEWISE_CMOS);
  Py_XDECREF(ClibDelayModel_CMOS2);
  Py_XDECREF(ClibDelayModel_DCM);
  Py_XDECREF(ClibDelayModel_POLYNOMIAL);

  return false;
}

// @brief ClibDelayModel を表す PyObject から ClibDelayModel を取り出す．
bool
PyClibDelayModel::FromPyObject(
  PyObject* obj,
  ClibDelayModel& val,
  const char* msg
)
{
  if ( obj == Py_None ) {
    // 特例: None は ClibDelayModel::none に変換する．
    val = ClibDelayModel::none;
    return true;
  }

  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibDelayModel type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibDelayModel を表す PyObject を作る．
PyObject*
PyClibDelayModel::ToPyObject(
  ClibDelayModel val
)
{
  PyObject* obj = nullptr;
  switch ( val ) {
  case ClibDelayModel::generic_cmos:   obj = ClibDelayModel_GENERIC_CMOS; break;
  case ClibDelayModel::table_lookup:   obj = ClibDelayModel_TABLE_LOOKUP; break;
  case ClibDelayModel::piecewise_cmos: obj = ClibDelayModel_PIECEWISE_CMOS; break;
  case ClibDelayModel::cmos2:          obj = ClibDelayModel_CMOS2; break;
  case ClibDelayModel::dcm:            obj = ClibDelayModel_DCM; break;
  case ClibDelayModel::polynomial:     obj = ClibDelayModel_POLYNOMIAL; break;
  case ClibDelayModel::none:           Py_RETURN_NONE;
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibDelayModel タイプか調べる．
bool
PyClibDelayModel::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibDelayModel を表す PyObject から ClibDelayModel を取り出す．
ClibDelayModel
PyClibDelayModel::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibDelayModelObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibDelayModel を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibDelayModel::_typeobject()
{
  return &ClibDelayModel_Type;
}

END_NAMESPACE_YM
