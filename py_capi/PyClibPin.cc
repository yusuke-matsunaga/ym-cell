
/// @file PyClibPin.cc
/// @brief PyClibPin の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibPin.h"
#include "pym/PyClibDirection.h"
#include "pym/PyExpr.h"
#include "pym/PyModule.h"
#include "ci/CiCell.h"
#include "ci/CiPin.h"


BEGIN_NAMESPACE_YM

using CiCell = nsClib::CiCell;
using CiPin = nsClib::CiPin;

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibPinObject
{
  PyObject_HEAD
  const CiCell* mCell;
  const CiPin* mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibPinType = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};


// 生成関数
PyObject*
ClibPin_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  PyErr_SetString(PyExc_TypeError, "instantiation of 'ClibCell' is disabled");
  return nullptr;
}

// 終了関数
void
ClibPin_dealloc(
  PyObject* self
)
{
  auto val_obj = reinterpret_cast<ClibPinObject*>(self);
  auto ptr = val_obj->mCell;
  if ( ptr != nullptr ) {
    ptr->dec_ref();
  }
  Py_TYPE(self)->tp_free(self);
}

// repr() 関数
PyObject*
ClibPin_repr(
  PyObject* self
)
{
  auto val_obj = reinterpret_cast<ClibPinObject*>(self);
  auto cell = val_obj->mCell;
  auto pin = val_obj->mVal;
  ostringstream buf;
  buf << cell->name() << "." << pin->name();
  return Py_BuildValue("s", buf.str().c_str());
}

PyObject*
ClibPin_is_input(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->is_input();
  return PyBool_FromLong(ans);
}

PyObject*
ClibPin_is_output(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->is_output();
  return PyBool_FromLong(ans);
}

PyObject*
ClibPin_is_inout(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->is_inout();
  return PyBool_FromLong(ans);
}

PyObject*
ClibPin_is_internal(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->is_internal();
  return PyBool_FromLong(ans);
}

// メソッド定義
PyMethodDef ClibPin_methods[] = {
  {"is_input", ClibPin_is_input, METH_NOARGS,
   PyDoc_STR("check if input-type")},
  {"is_output", ClibPin_is_output, METH_NOARGS,
   PyDoc_STR("check if output-type")},
  {"is_inout", ClibPin_is_inout, METH_NOARGS,
   PyDoc_STR("check if inout-type")},
  {"is_internal", ClibPin_is_internal, METH_NOARGS,
   PyDoc_STR("check if internal-type")},
  {nullptr, nullptr, 0, nullptr}
};

PyObject*
ClibPin_name(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->name();
  return Py_BuildValue("s", ans.c_str());
}

PyObject*
ClibPin_direction(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->direction();
  return PyClibDirection::ToPyObject(ans);
}

PyObject*
ClibPin_pin_id(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->pin_id();
  return Py_BuildValue("k", ans);
}

PyObject*
ClibPin_input_id(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->input_id();
  return Py_BuildValue("k", ans);
}

PyObject*
ClibPin_output_id(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->output_id();
  return Py_BuildValue("k", ans);
}

PyObject*
ClibPin_internal_id(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->internal_id();
  return Py_BuildValue("k", ans);
}

PyObject*
ClibPin_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_rise_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->rise_capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_fall_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->fall_capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_max_fanout(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->max_fanout();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_min_fanout(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->min_fanout();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_max_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->max_capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_min_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->min_capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_max_transition(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->max_transition();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_min_transition(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->min_transition();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_function(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->function();
  return PyExpr::ToPyObject(ans);
}

PyObject*
ClibPin_tristate(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibPin::Get(self);
  auto ans = val->tristate();
  return PyExpr::ToPyObject(ans);
}

// getter/setter 関数テーブル
PyGetSetDef ClibPin_getsetters[] = {
  {"name", ClibPin_name, nullptr,
   PyDoc_STR("name"), nullptr},
  {"direction", ClibPin_direction, nullptr,
   PyDoc_STR("direction"), nullptr},
  {"pin_id", ClibPin_pin_id, nullptr,
   PyDoc_STR("pin ID"), nullptr},
  {"input_id", ClibPin_input_id, nullptr,
   PyDoc_STR("input ID"), nullptr},
  {"output_id", ClibPin_output_id, nullptr,
   PyDoc_STR("output ID"), nullptr},
  {"internal_id", ClibPin_internal_id, nullptr,
   PyDoc_STR("internal ID"), nullptr},
  {"capacitance", ClibPin_capacitance, nullptr,
   PyDoc_STR("capacitance"), nullptr},
  {"rise_capacitance", ClibPin_rise_capacitance, nullptr,
   PyDoc_STR("rise capacitance"), nullptr},
  {"fall_capacitance", ClibPin_fall_capacitance, nullptr,
   PyDoc_STR("fall capacitance"), nullptr},
  {"max_fanout", ClibPin_max_fanout, nullptr,
   PyDoc_STR("max fanout"), nullptr},
  {"min_fanout", ClibPin_min_fanout, nullptr,
   PyDoc_STR("min fanout"), nullptr},
  {"max_capacitance", ClibPin_max_capacitance, nullptr,
   PyDoc_STR("max capacitance"), nullptr},
  {"min_capacitance", ClibPin_min_capacitance, nullptr,
   PyDoc_STR("min capacitance"), nullptr},
  {"max_transition", ClibPin_max_transition, nullptr,
   PyDoc_STR("max transition"), nullptr},
  {"min_transition", ClibPin_min_transition, nullptr,
   PyDoc_STR("min transition"), nullptr},
  {"function", ClibPin_function, nullptr,
   PyDoc_STR("function"), nullptr},
  {"tristate", ClibPin_tristate, nullptr,
   PyDoc_STR("tristate"), nullptr},
  {nullptr, nullptr, nullptr, nullptr, nullptr}
};

// 比較関数
PyObject*
ClibPin_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibPin::Check(self) &&
       PyClibPin::Check(other) ) {
    auto val1 = PyClibPin::Get(self);
    auto val2 = PyClibPin::Get(other);
    if ( op == Py_EQ ) {
      return PyBool_FromLong(val1 == val2);
    }
    if ( op == Py_NE ) {
      return PyBool_FromLong(val1 != val2);
    }
  }
  Py_RETURN_NOTIMPLEMENTED;
}

END_NONAMESPACE


// @brief 初期化する．
bool
PyClibPin::init(
  PyObject* m
)
{
  ClibPinType.tp_name = "ClibPin";
  ClibPinType.tp_basicsize = sizeof(ClibPinObject);
  ClibPinType.tp_itemsize = 0;
  ClibPinType.tp_dealloc = ClibPin_dealloc;
  ClibPinType.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibPinType.tp_doc = PyDoc_STR("ClibPin objects");
  ClibPinType.tp_richcompare = ClibPin_richcmpfunc;
  ClibPinType.tp_methods = ClibPin_methods;
  ClibPinType.tp_getset = ClibPin_getsetters;
  ClibPinType.tp_new = ClibPin_new;
  ClibPinType.tp_repr = ClibPin_repr;
  if ( PyType_Ready(&ClibPinType) < 0 ) {
    return false;
  }

  return true;
}

// @brief ClibPin を表す PyObject から ClibPin を取り出す．
bool
PyClibPin::FromPyObject(
  PyObject* obj,
  const CiPin*& val,
  const char* msg
)
{
  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibPin type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibPin を表す PyObject を作る．
PyObject*
PyClibPin::ToPyObject(
  const ClibPin& val
)
{
  PyObject* obj = ClibPinType.tp_alloc(&ClibPinType, 0);
  auto pin_obj = reinterpret_cast<ClibPinObject*>(obj);
  pin_obj->mCell = val._cell();
  pin_obj->mVal = val._impl();
  if ( pin_obj->mCell != nullptr ) {
    pin_obj->mCell->inc_ref();
  }
  Py_INCREF(obj);
  return obj;
}

// @brief ClibPin を表す PyObject を作る．
PyObject*
PyClibPin::ToPyObject(
  const CiCell* cell,
  const CiPin* val
)
{
  PyObject* obj = ClibPinType.tp_alloc(&ClibPinType, 0);
  auto pin_obj = reinterpret_cast<ClibPinObject*>(obj);
  pin_obj->mCell = cell;
  pin_obj->mVal = val;
  if ( pin_obj->mCell != nullptr ) {
    pin_obj->mCell->inc_ref();
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibPin タイプか調べる．
bool
PyClibPin::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibPin を表す PyObject から ClibPin を取り出す．
const CiPin*
PyClibPin::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibPinObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibPin を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibPin::_typeobject()
{
  return &ClibPinType;
}

END_NAMESPACE_YM
