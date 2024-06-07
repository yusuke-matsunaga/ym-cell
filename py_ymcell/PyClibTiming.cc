
/// @file PyClibTiming.cc
/// @brief PyClibTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibTiming.h"
#include "pym/PyClibTimingType.h"
#include "pym/PyExpr.h"
#include "pym/PyModule.h"
#include "ci/CiTiming.h"
#include "ci/CiCell.h"


BEGIN_NAMESPACE_YM

using CiCell = nsClib::CiCell;
using CiTiming = nsClib::CiTiming;

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibTimingObject
{
  PyObject_HEAD
  const CiCell* mCell;
  const CiTiming* mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibTiming_Type = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};


// 生成関数
PyObject*
ClibTiming_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  PyErr_SetString(PyExc_TypeError, "instantiation of 'ClibTiming' is disabled");
  return nullptr;
}

// 終了関数
void
ClibTiming_dealloc(
  PyObject* self
)
{
  // auto val_obj = reinterpret_cast<ClibTimingObject*>(self);
  // 必要なら val_obj->mVal の終了処理を行う．
  Py_TYPE(self)->tp_free(self);
}

// メソッド定義
PyMethodDef ClibTiming_methods[] = {
  {nullptr, nullptr, 0, nullptr}
};

PyObject*
ClibTiming_type(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->type();
  return PyClibTimingType::ToPyObject(ans);
}

PyObject*
ClibTiming_timing_cond(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->timing_cond();
  return PyExpr::ToPyObject(ans);
}

PyObject*
ClibTiming_intrinsic_rise(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->intrinsic_rise();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibTiming_intrinsic_fall(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->intrinsic_fall();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibTiming_slope_rise(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->slope_rise();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibTiming_slope_fall(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->slope_fall();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibTiming_rise_resistance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->rise_resistance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibTiming_fall_resistance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->fall_resistance();
  return Py_BuildValue("d", ans.value());
}

#if 0
PyObject*
ClibTiming_rise_pin_resistance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->rise_pin_resistance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibTiming_fall_pin_resistance(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->fall_pin_resistance();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibTiming_rise_delay_intercept(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->rise_delay_intercept();
  return Py_BuildValue("d", ans.value());
}

PyObject*
ClibTiming_fall_delay_intercept(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->rise_delay_intercept();
  return Py_BuildValue("d", ans.value());
}
#endif

#if 0
PyObject*
ClibTiming_rise_transition(
  PyObject* self,
  void* Py_UNUSED(closure)
)
{
  auto val = PyClibTiming::Get(self);
  auto ans = val->rise_transition();
  return PyClibLut::ToPyObject(val_obj->mCell, ans);
}
#endif

// getter/setter 関数テーブル
PyGetSetDef ClibTiming_getsetters[] = {
  {"type", ClibTiming_type, nullptr,
   PyDoc_STR("type"), nullptr},
  {"timing_cond", ClibTiming_timing_cond, nullptr,
   PyDoc_STR("timing condition"), nullptr},
  {"intrinsic_rise", ClibTiming_intrinsic_rise, nullptr,
   PyDoc_STR("intrinsitc_rise"), nullptr},
  {"intrinsic_fall", ClibTiming_intrinsic_fall, nullptr,
   PyDoc_STR("intrinsitc_fall"), nullptr},
  {"slope_rise", ClibTiming_slope_rise, nullptr,
   PyDoc_STR("slope_rise"), nullptr},
  {"slope_fall", ClibTiming_slope_fall, nullptr,
   PyDoc_STR("slope_fall"), nullptr},
  {"rise_resistance", ClibTiming_rise_resistance, nullptr,
   PyDoc_STR("rise_resistance"), nullptr},
  {"fall_resistance", ClibTiming_fall_resistance, nullptr,
   PyDoc_STR("fall_resistance"), nullptr},
#if 0
  {"rise_pin_resistance", ClibTiming_rise_pin_resistance, nullptr,
   PyDoc_STR("rise_pin_resistance"), nullptr},
  {"fall_pin_resistance", ClibTiming_fall_pin_resistance, nullptr,
   PyDoc_STR("fall_pin_resistance"), nullptr},
  {"rise_delay_intercept", ClibTiming_rise_delay_intercept, nullptr,
   PyDoc_STR("rise_delay_intercept"), nullptr},
  {"fall_delay_intercept", ClibTiming_fall_delay_intercept, nullptr,
   PyDoc_STR("fall_delay_intercept"), nullptr},
#endif
  {nullptr, nullptr, nullptr, nullptr, nullptr}
};

// 比較関数
PyObject*
ClibTiming_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibTiming::Check(self) &&
       PyClibTiming::Check(other) ) {
    auto val1 = PyClibTiming::Get(self);
    auto val2 = PyClibTiming::Get(other);
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
PyClibTiming::init(
  PyObject* m
)
{
  ClibTiming_Type.tp_name = "ClibTiming";
  ClibTiming_Type.tp_basicsize = sizeof(ClibTimingObject);
  ClibTiming_Type.tp_itemsize = 0;
  ClibTiming_Type.tp_dealloc = ClibTiming_dealloc;
  ClibTiming_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibTiming_Type.tp_doc = PyDoc_STR("ClibTiming objects");
  ClibTiming_Type.tp_richcompare = ClibTiming_richcmpfunc;
  ClibTiming_Type.tp_methods = ClibTiming_methods;
  ClibTiming_Type.tp_getset = ClibTiming_getsetters;
  ClibTiming_Type.tp_new = ClibTiming_new;
  if ( PyType_Ready(&ClibTiming_Type) < 0 ) {
    return false;
  }

  return true;
}

// @brief ClibTiming を表す PyObject から ClibTiming を取り出す．
bool
PyClibTiming::FromPyObject(
  PyObject* obj,
  const CiTiming*& val,
  const char* msg
)
{
  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibTiming type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibTiming を表す PyObject を作る．
PyObject*
PyClibTiming::ToPyObject(
  const ClibTiming& val
)
{
  return ToPyObject(val._cell(), val._impl());
}

// @brief ClibTiming を表す PyObject を作る．
PyObject*
PyClibTiming::ToPyObject(
  const CiCell* cell,
  const CiTiming* val
)
{
  PyObject* obj = ClibTiming_Type.tp_alloc(&ClibTiming_Type, 0);
  auto val_obj = reinterpret_cast<ClibTimingObject*>(obj);
  val_obj->mCell = cell;
  val_obj->mVal = val;
  if ( val_obj->mCell != nullptr ) {
    val_obj->mCell->inc_ref();
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibTiming タイプか調べる．
bool
PyClibTiming::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibTiming を表す PyObject から ClibTiming を取り出す．
const CiTiming*
PyClibTiming::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibTimingObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibTiming を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibTiming::_typeobject()
{
  return &ClibTiming_Type;
}

END_NAMESPACE_YM
