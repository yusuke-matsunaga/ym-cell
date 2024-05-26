
/// @file PyClibCellType.cc
/// @brief PyClibCellType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibCellType.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibCellTypeObject
{
  PyObject_HEAD
  ClibCellType mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibCellTypeType = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 各定数を表す文字列
const char* LOGIC_STR = "Logic";
const char* FF_STR    = "FF";
const char* LATCH_STR = "Latch";
const char* FSM_STR   = "FSM";

// 各定数を表す PyObject
PyObject* ClibCellType_LOGIC = nullptr;
PyObject* ClibCellType_FF    = nullptr;
PyObject* ClibCellType_LATCH = nullptr;
PyObject* ClibCellType_FSM   = nullptr;

// 生成関数
PyObject*
ClibCellType_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  if ( type != &ClibCellTypeType ) {
    PyErr_SetString(PyExc_TypeError, "ClibCellType cannot be overloaded");
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
  ClibCellType val;
  if ( strcasecmp(name_str, "none") == 0 ) {
    val = ClibCellType::none;
  }
  else if ( strcasecmp(name_str, LOGIC_STR) == 0 ) {
    val = ClibCellType::Logic;
  }
  else if ( strcasecmp(name_str, FF_STR) == 0 ) {
    val = ClibCellType::FF;
  }
  else if ( strcasecmp(name_str, LATCH_STR) == 0 ) {
    val = ClibCellType::Latch;
  }
  else if ( strcasecmp(name_str, FSM_STR) == 0 ) {
    val = ClibCellType::FSM;
  }
  else {
    // エラー
    ostringstream buf;
    buf << "argument 1 must be one of \""
        << "none"
        << "\", \""
        << LOGIC_STR
        << "\", \""
        << FF_STR
        << "\", \""
        << LATCH_STR
        << "\", \""
        << FSM_STR
        << "\"";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
  return PyClibCellType::ToPyObject(val);
}

// 終了関数
void
ClibCellType_dealloc(
  PyObject* self
)
{
  // auto val_obj = reinterpret_cast<ClibCellTypeObject*>(self);
  // 必要なら val_obj->mVal の終了処理を行う．
  Py_TYPE(self)->tp_free(self);
}

// repr() 関数
PyObject*
ClibCellType_repr(
  PyObject* self
)
{
  auto val = PyClibCellType::Get(self);
  const char* tmp_str = nullptr;
  switch ( val ) {
  case ClibCellType::none:  tmp_str = ""; break;
  case ClibCellType::Logic: tmp_str = LOGIC_STR; break;
  case ClibCellType::FF:    tmp_str = FF_STR; break;
  case ClibCellType::Latch: tmp_str = LATCH_STR; break;
  case ClibCellType::FSM:   tmp_str = FSM_STR; break;
  }
  return Py_BuildValue("s", tmp_str);
}

// 比較関数
PyObject*
ClibCellType_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibCellType::Check(self) &&
       PyClibCellType::Check(other) ) {
    auto val1 = PyClibCellType::Get(self);
    auto val2 = PyClibCellType::Get(other);
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
  ClibCellType val
)
{
  auto obj = ClibCellTypeType.tp_alloc(&ClibCellTypeType, 0);
  auto val_obj = reinterpret_cast<ClibCellTypeObject*>(obj);
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
  if ( PyDict_SetItemString(ClibCellTypeType.tp_dict, name, obj) < 0 ) {
    return false;
  }
  return true;
}

END_NONAMESPACE


// @brief 初期化する．
bool
PyClibCellType::init(
  PyObject* m
)
{
  ClibCellTypeType.tp_name = "ClibCellType";
  ClibCellTypeType.tp_basicsize = sizeof(ClibCellTypeObject);
  ClibCellTypeType.tp_itemsize = 0;
  ClibCellTypeType.tp_dealloc = ClibCellType_dealloc;
  ClibCellTypeType.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibCellTypeType.tp_doc = PyDoc_STR("ClibCellType objects");
  ClibCellTypeType.tp_richcompare = ClibCellType_richcmpfunc;
  ClibCellTypeType.tp_new = ClibCellType_new;
  ClibCellTypeType.tp_repr = ClibCellType_repr;
  if ( PyType_Ready(&ClibCellTypeType) < 0 ) {
    return false;
  }

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibCellType", &ClibCellTypeType) ) {
    goto error;
  }

  // 定数オブジェクトの生成
  ClibCellType_LOGIC = new_obj(ClibCellType::Logic);
  ClibCellType_FF    = new_obj(ClibCellType::FF);
  ClibCellType_LATCH = new_obj(ClibCellType::Latch);
  ClibCellType_FSM   = new_obj(ClibCellType::FSM);

  // 定数の登録
  if ( !reg_obj(LOGIC_STR, ClibCellType_LOGIC) ) {
    goto error;
  }
  if ( !reg_obj(FF_STR, ClibCellType_FF) ) {
    goto error;
  }
  if ( !reg_obj(LATCH_STR, ClibCellType_LATCH) ) {
    goto error;
  }
  if ( !reg_obj(FSM_STR, ClibCellType_FSM) ) {
    goto error;
  }

  return true;

 error:

  Py_XDECREF(ClibCellType_LOGIC);
  Py_XDECREF(ClibCellType_FF);
  Py_XDECREF(ClibCellType_LATCH);
  Py_XDECREF(ClibCellType_FSM);

  return false;
}

// @brief ClibCellType を表す PyObject から ClibCellType を取り出す．
bool
PyClibCellType::FromPyObject(
  PyObject* obj,
  ClibCellType& val,
  const char* msg
)
{
  if ( obj == Py_None ) {
    // 特例: None は ClibCellType::none に変換する．
    val = ClibCellType::none;
    return true;
  }

  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibCellType type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibCellType を表す PyObject を作る．
PyObject*
PyClibCellType::ToPyObject(
  ClibCellType val
)
{
  PyObject* obj = nullptr;
  switch ( val ) {
  case ClibCellType::none:  Py_RETURN_NONE;
  case ClibCellType::Logic: obj = ClibCellType_LOGIC; break;
  case ClibCellType::FF:    obj = ClibCellType_FF; break;
  case ClibCellType::Latch: obj = ClibCellType_LATCH; break;
  case ClibCellType::FSM:   obj = ClibCellType_FSM; break;
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibCellType タイプか調べる．
bool
PyClibCellType::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibCellType を表す PyObject から ClibCellType を取り出す．
ClibCellType
PyClibCellType::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibCellTypeObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibCellType を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibCellType::_typeobject()
{
  return &ClibCellTypeType;
}

END_NAMESPACE_YM_CLIB
