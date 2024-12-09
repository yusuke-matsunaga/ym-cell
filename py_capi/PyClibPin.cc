
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
#include "ym/ClibPin.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibTime.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibPinObject
{
  PyObject_HEAD
  ClibPin mPin;
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
  auto pin_obj = reinterpret_cast<ClibPinObject*>(self);
  pin_obj->mPin.~ClibPin();
  Py_TYPE(self)->tp_free(self);
}

PyObject*
ClibPin_is_input(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.is_input();
  return PyBool_FromLong(ans);
}

PyObject*
ClibPin_is_output(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.is_output();
  return PyBool_FromLong(ans);
}

PyObject*
ClibPin_is_inout(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.is_inout();
  return PyBool_FromLong(ans);
}

PyObject*
ClibPin_is_internal(
  PyObject* self,
  PyObject* Py_UNUSED(args)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.is_internal();
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
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.name();
  return Py_BuildValue("s", ans.c_str());
}

PyObject*
ClibPin_direction(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.direction();
  return PyClibDirection::ToPyObject(ans);
}

PyObject*
ClibPin_pin_id(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.pin_id();
  return Py_BuildValue("k", ans);
}

PyObject*
ClibPin_input_id(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.input_id();
  return Py_BuildValue("k", ans);
}

PyObject*
ClibPin_output_id(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.output_id();
  return Py_BuildValue("k", ans);
}

PyObject*
ClibPin_internal_id(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.internal_id();
  return Py_BuildValue("k", ans);
}

PyObject*
ClibPin_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_rise_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.rise_capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_fall_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.fall_capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_max_fanout(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.max_fanout();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_min_fanout(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.min_fanout();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_max_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.max_capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_min_capacitance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.min_capacitance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_max_transition(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.max_transition();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_min_transition(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.min_transition();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibPin_function(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.function();
  return PyExpr::ToPyObject(ans);
}

PyObject*
ClibPin_tristate(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto& pin = PyClibPin::Get(self);
  auto ans = pin.tristate();
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
  if ( PyType_Ready(&ClibPinType) < 0 ) {
    return false;
  }

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
  new (&pin_obj->mPin) ClibPin{val};
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
const ClibPin&
PyClibPin::Get(
  PyObject* obj
)
{
  auto pin_obj = reinterpret_cast<ClibPinObject*>(obj);
  return pin_obj->mPin;
}

// @brief ClibPin を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibPin::_typeobject()
{
  return &ClibPinType;
}

END_NAMESPACE_YM
