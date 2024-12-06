
/// @file PyClibVarType.cc
/// @brief PyClibVarType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibVarType.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibVarTypeObject
{
  PyObject_HEAD
  ClibVarType mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibVarType_Type = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 各定数を表す文字列
const char* INPUT_NET_TRANSITION_STR                     = "input_net_transition";
const char* TOTAL_OUTPUT_NET_CAPACITANCE_STR             = "total_output_net_capacitance";
const char* OUTPUT_NET_LENGTH_STR                        = "output_net_length";
const char* OUTPUT_NET_WIRE_CAP_STR                      = "output_net_wire_cap";
const char* OUTPUT_NET_PIN_CAP_STR                       = "output_net_pin_cap";
const char* EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE_STR = "equal_or_opposite_output_net_capacitance";
const char* INPUT_TRANSITION_TIME_STR                    = "input_transition_time";
const char* RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE_STR = "related_out_total_output_net_capacitance";
const char* RELATED_OUT_OUTPUT_NET_LENGTH_STR            = "related_out_output_net_length";
const char* RELATED_OUT_OUTPUT_NET_WIRE_CAP_STR          = "related_out_output_net_wire_cap";
const char* RELATED_OUT_OUTPUT_NET_PIN_CAP_STR           = "related_out_output_net_pin_cap";
const char* CONSTRAINED_PIN_TRANSITION_STR               = "constrained_pin_transition";
const char* RELATED_PIN_TRANSITION_STR                   = "related_pin_transition";

// 各定数を表す PyObject
PyObject* ClibVarType_INPUT_NET_TRANSITION                     = nullptr;
PyObject* ClibVarType_TOTAL_OUTPUT_NET_CAPACITANCE             = nullptr;
PyObject* ClibVarType_OUTPUT_NET_LENGTH                        = nullptr;
PyObject* ClibVarType_OUTPUT_NET_WIRE_CAP                      = nullptr;
PyObject* ClibVarType_OUTPUT_NET_PIN_CAP                       = nullptr;
PyObject* ClibVarType_EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE = nullptr;
PyObject* ClibVarType_INPUT_TRANSITION_TIME                    = nullptr;
PyObject* ClibVarType_RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE = nullptr;
PyObject* ClibVarType_RELATED_OUT_OUTPUT_NET_LENGTH            = nullptr;
PyObject* ClibVarType_RELATED_OUT_OUTPUT_NET_WIRE_CAP          = nullptr;
PyObject* ClibVarType_RELATED_OUT_OUTPUT_NET_PIN_CAP           = nullptr;
PyObject* ClibVarType_CONSTRAINED_PIN_TRANSITION               = nullptr;
PyObject* ClibVarType_RELATED_PIN_TRANSITION                   = nullptr;

// 生成関数
PyObject*
ClibVarType_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  if ( type != &ClibVarType_Type ) {
    PyErr_SetString(PyExc_TypeError, "ClibVarType cannot be overloaded");
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
  ClibVarType val;
  if ( strcasecmp(name_str, INPUT_NET_TRANSITION_STR) == 0 ) {
    val = ClibVarType::input_net_transition;
  }
  else if ( strcasecmp(name_str, TOTAL_OUTPUT_NET_CAPACITANCE_STR) == 0 ) {
    val = ClibVarType::total_output_net_capacitance;
  }
  else if ( strcasecmp(name_str, OUTPUT_NET_LENGTH_STR) == 0 ) {
    val = ClibVarType::output_net_length;
  }
  else if ( strcasecmp(name_str, OUTPUT_NET_WIRE_CAP_STR) == 0 ) {
    val = ClibVarType::output_net_wire_cap;
  }
  else if ( strcasecmp(name_str, OUTPUT_NET_PIN_CAP_STR) == 0 ) {
    val = ClibVarType::output_net_pin_cap;
  }
  else if ( strcasecmp(name_str, EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE_STR) == 0 ) {
    val = ClibVarType::equal_or_opposite_output_net_capacitance;
  }
  else if ( strcasecmp(name_str, INPUT_TRANSITION_TIME_STR) == 0 ) {
    val = ClibVarType::input_transition_time;
  }
  else if ( strcasecmp(name_str, RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE_STR) == 0 ) {
    val = ClibVarType::related_out_total_output_net_capacitance;
  }
  else if ( strcasecmp(name_str, RELATED_OUT_OUTPUT_NET_LENGTH_STR) == 0 ) {
    val = ClibVarType::related_out_output_net_length;
  }
  else if ( strcasecmp(name_str, RELATED_OUT_OUTPUT_NET_WIRE_CAP_STR) == 0 ) {
    val = ClibVarType::related_out_output_net_wire_cap;
  }
  else if ( strcasecmp(name_str, RELATED_OUT_OUTPUT_NET_PIN_CAP_STR) == 0 ) {
    val = ClibVarType::related_out_output_net_pin_cap;
  }
  else if ( strcasecmp(name_str, CONSTRAINED_PIN_TRANSITION_STR) == 0 ) {
    val = ClibVarType::constrained_pin_transition;
  }
  else if ( strcasecmp(name_str, RELATED_PIN_TRANSITION_STR) == 0 ) {
    val = ClibVarType::related_pin_transition;
  }
  else if ( strcasecmp(name_str, "none") == 0 ) {
    val = ClibVarType::none;
  }
  else {
    // エラー
    ostringstream buf;
    buf << "argument 1 must be one of \""
        << INPUT_NET_TRANSITION_STR
        << "\", \""
        << TOTAL_OUTPUT_NET_CAPACITANCE_STR
        << "\", \""
        << OUTPUT_NET_LENGTH_STR
        << "\", \""
        << OUTPUT_NET_WIRE_CAP_STR
        << "\", \""
        << OUTPUT_NET_PIN_CAP_STR
        << "\", \""
        << EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE_STR
        << "\", \""
        << INPUT_TRANSITION_TIME_STR
        << "\", \""
        << RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE_STR
        << "\", \""
        << RELATED_OUT_OUTPUT_NET_LENGTH_STR
        << "\", \""
        << RELATED_OUT_OUTPUT_NET_WIRE_CAP_STR
        << "\", \""
        << RELATED_OUT_OUTPUT_NET_PIN_CAP_STR
        << "\", \""
        << CONSTRAINED_PIN_TRANSITION_STR
        << "\", \""
        << RELATED_PIN_TRANSITION_STR
        << "\", \""
        << "none"
        << "\"";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
  return PyClibVarType::ToPyObject(val);
}

// 終了関数
void
ClibVarType_dealloc(
  PyObject* self
)
{
  // auto val_obj = reinterpret_cast<ClibVarTypeObject*>(self);
  // 必要なら val_obj->mVal の終了処理を行う．
  Py_TYPE(self)->tp_free(self);
}

// repr() 関数
PyObject*
ClibVarType_repr(
  PyObject* self
)
{
  auto val = PyClibVarType::Get(self);
  const char* tmp_str = nullptr;
  switch ( val ) {
  case ClibVarType::input_net_transition:                     tmp_str = INPUT_NET_TRANSITION_STR; break;
  case ClibVarType::total_output_net_capacitance:             tmp_str = TOTAL_OUTPUT_NET_CAPACITANCE_STR; break;
  case ClibVarType::output_net_length:                        tmp_str = OUTPUT_NET_LENGTH_STR; break;
  case ClibVarType::output_net_wire_cap:                      tmp_str = OUTPUT_NET_WIRE_CAP_STR; break;
  case ClibVarType::output_net_pin_cap:                       tmp_str = OUTPUT_NET_PIN_CAP_STR; break;
  case ClibVarType::equal_or_opposite_output_net_capacitance: tmp_str = EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE_STR; break;
  case ClibVarType::input_transition_time:                    tmp_str = INPUT_TRANSITION_TIME_STR; break;
  case ClibVarType::related_out_total_output_net_capacitance: tmp_str = RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE_STR; break;
  case ClibVarType::related_out_output_net_length:            tmp_str = RELATED_OUT_OUTPUT_NET_LENGTH_STR; break;
  case ClibVarType::related_out_output_net_wire_cap:          tmp_str = RELATED_OUT_OUTPUT_NET_WIRE_CAP_STR; break;
  case ClibVarType::related_out_output_net_pin_cap:           tmp_str = RELATED_OUT_OUTPUT_NET_PIN_CAP_STR; break;
  case ClibVarType::constrained_pin_transition:               tmp_str = CONSTRAINED_PIN_TRANSITION_STR; break;
  case ClibVarType::related_pin_transition:                   tmp_str = RELATED_PIN_TRANSITION_STR; break;
  case ClibVarType::none:                                     tmp_str = ""; break;
  }
  return Py_BuildValue("s", tmp_str);
}

// 比較関数
PyObject*
ClibVarType_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibVarType::Check(self) &&
       PyClibVarType::Check(other) ) {
    auto val1 = PyClibVarType::Get(self);
    auto val2 = PyClibVarType::Get(other);
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
  ClibVarType val
)
{
  auto obj = ClibVarType_Type.tp_alloc(&ClibVarType_Type, 0);
  auto val_obj = reinterpret_cast<ClibVarTypeObject*>(obj);
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
  if ( PyDict_SetItemString(ClibVarType_Type.tp_dict, name, obj) < 0 ) {
    return false;
  }
  return true;
}

END_NONAMESPACE


// @brief 初期化する．
bool
PyClibVarType::init(
  PyObject* m
)
{
  ClibVarType_Type.tp_name = "ClibVarType";
  ClibVarType_Type.tp_basicsize = sizeof(ClibVarTypeObject);
  ClibVarType_Type.tp_itemsize = 0;
  ClibVarType_Type.tp_dealloc = ClibVarType_dealloc;
  ClibVarType_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibVarType_Type.tp_doc = PyDoc_STR("ClibVarType objects");
  ClibVarType_Type.tp_richcompare = ClibVarType_richcmpfunc;
  ClibVarType_Type.tp_new = ClibVarType_new;
  ClibVarType_Type.tp_repr = ClibVarType_repr;
  if ( PyType_Ready(&ClibVarType_Type) < 0 ) {
    return false;
  }

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibVarType", &ClibVarType_Type) ) {
    goto error;
  }

  // 定数オブジェクトの生成
  ClibVarType_INPUT_NET_TRANSITION                     = new_obj(ClibVarType::input_net_transition);
  ClibVarType_TOTAL_OUTPUT_NET_CAPACITANCE             = new_obj(ClibVarType::total_output_net_capacitance);
  ClibVarType_OUTPUT_NET_LENGTH                        = new_obj(ClibVarType::output_net_length);
  ClibVarType_OUTPUT_NET_WIRE_CAP                      = new_obj(ClibVarType::output_net_wire_cap);
  ClibVarType_OUTPUT_NET_PIN_CAP                       = new_obj(ClibVarType::output_net_pin_cap);
  ClibVarType_EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE = new_obj(ClibVarType::equal_or_opposite_output_net_capacitance);
  ClibVarType_INPUT_TRANSITION_TIME                    = new_obj(ClibVarType::input_transition_time);
  ClibVarType_RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE = new_obj(ClibVarType::related_out_total_output_net_capacitance);
  ClibVarType_RELATED_OUT_OUTPUT_NET_LENGTH            = new_obj(ClibVarType::related_out_output_net_length);
  ClibVarType_RELATED_OUT_OUTPUT_NET_WIRE_CAP          = new_obj(ClibVarType::related_out_output_net_wire_cap);
  ClibVarType_RELATED_OUT_OUTPUT_NET_PIN_CAP           = new_obj(ClibVarType::related_out_output_net_pin_cap);
  ClibVarType_CONSTRAINED_PIN_TRANSITION               = new_obj(ClibVarType::constrained_pin_transition);
  ClibVarType_RELATED_PIN_TRANSITION                   = new_obj(ClibVarType::related_pin_transition);

  // 定数の登録
  if ( !reg_obj(INPUT_NET_TRANSITION_STR, ClibVarType_INPUT_NET_TRANSITION) ) {
    goto error;
  }
  if ( !reg_obj(TOTAL_OUTPUT_NET_CAPACITANCE_STR, ClibVarType_TOTAL_OUTPUT_NET_CAPACITANCE) ) {
    goto error;
  }
  if ( !reg_obj(OUTPUT_NET_LENGTH_STR, ClibVarType_OUTPUT_NET_LENGTH) ) {
    goto error;
  }
  if ( !reg_obj(OUTPUT_NET_WIRE_CAP_STR, ClibVarType_OUTPUT_NET_WIRE_CAP) ) {
    goto error;
  }
  if ( !reg_obj(OUTPUT_NET_PIN_CAP_STR, ClibVarType_OUTPUT_NET_PIN_CAP) ) {
    goto error;
  }
  if ( !reg_obj(EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE_STR, ClibVarType_EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE) ) {
    goto error;
  }
  if ( !reg_obj(INPUT_TRANSITION_TIME_STR, ClibVarType_INPUT_TRANSITION_TIME) ) {
    goto error;
  }
  if ( !reg_obj(RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE_STR, ClibVarType_RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE) ) {
    goto error;
  }
  if ( !reg_obj(RELATED_OUT_OUTPUT_NET_LENGTH_STR, ClibVarType_RELATED_OUT_OUTPUT_NET_LENGTH) ) {
    goto error;
  }
  if ( !reg_obj(RELATED_OUT_OUTPUT_NET_WIRE_CAP_STR, ClibVarType_RELATED_OUT_OUTPUT_NET_WIRE_CAP) ) {
    goto error;
  }
  if ( !reg_obj(RELATED_OUT_OUTPUT_NET_PIN_CAP_STR, ClibVarType_RELATED_OUT_OUTPUT_NET_PIN_CAP) ) {
    goto error;
  }
  if ( !reg_obj(CONSTRAINED_PIN_TRANSITION_STR, ClibVarType_CONSTRAINED_PIN_TRANSITION) ) {
    goto error;
  }
  if ( !reg_obj(RELATED_PIN_TRANSITION_STR, ClibVarType_RELATED_PIN_TRANSITION) ) {
    goto error;
  }

  return true;

 error:

  Py_XDECREF(ClibVarType_INPUT_NET_TRANSITION);
  Py_XDECREF(ClibVarType_TOTAL_OUTPUT_NET_CAPACITANCE);
  Py_XDECREF(ClibVarType_OUTPUT_NET_LENGTH);
  Py_XDECREF(ClibVarType_OUTPUT_NET_WIRE_CAP);
  Py_XDECREF(ClibVarType_OUTPUT_NET_PIN_CAP);
  Py_XDECREF(ClibVarType_EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE);
  Py_XDECREF(ClibVarType_INPUT_TRANSITION_TIME);
  Py_XDECREF(ClibVarType_RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE);
  Py_XDECREF(ClibVarType_RELATED_OUT_OUTPUT_NET_LENGTH);
  Py_XDECREF(ClibVarType_RELATED_OUT_OUTPUT_NET_WIRE_CAP);
  Py_XDECREF(ClibVarType_RELATED_OUT_OUTPUT_NET_PIN_CAP);
  Py_XDECREF(ClibVarType_CONSTRAINED_PIN_TRANSITION);
  Py_XDECREF(ClibVarType_RELATED_PIN_TRANSITION);

  return false;
}

// @brief ClibVarType を表す PyObject から ClibVarType を取り出す．
bool
PyClibVarType::FromPyObject(
  PyObject* obj,
  ClibVarType& val,
  const char* msg
)
{
  if ( obj == Py_None ) {
    // 特例: None は ClibVarType::none に変換する．
    val = ClibVarType::none;
    return true;
  }

  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibVarType type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibVarType を表す PyObject を作る．
PyObject*
PyClibVarType::ToPyObject(
  ClibVarType val
)
{
  PyObject* obj = nullptr;
  switch ( val ) {
  case ClibVarType::input_net_transition:                     obj = ClibVarType_INPUT_NET_TRANSITION; break;
  case ClibVarType::total_output_net_capacitance:             obj = ClibVarType_TOTAL_OUTPUT_NET_CAPACITANCE; break;
  case ClibVarType::output_net_length:                        obj = ClibVarType_OUTPUT_NET_LENGTH; break;
  case ClibVarType::output_net_wire_cap:                      obj = ClibVarType_OUTPUT_NET_WIRE_CAP; break;
  case ClibVarType::output_net_pin_cap:                       obj = ClibVarType_OUTPUT_NET_PIN_CAP; break;
  case ClibVarType::equal_or_opposite_output_net_capacitance: obj = ClibVarType_EQUAL_OR_OPPOSITE_OUTPUT_NET_CAPACITANCE; break;
  case ClibVarType::input_transition_time:                    obj = ClibVarType_INPUT_TRANSITION_TIME; break;
  case ClibVarType::related_out_total_output_net_capacitance: obj = ClibVarType_RELATED_OUT_TOTAL_OUTPUT_NET_CAPACITANCE; break;
  case ClibVarType::related_out_output_net_length:            obj = ClibVarType_RELATED_OUT_OUTPUT_NET_LENGTH; break;
  case ClibVarType::related_out_output_net_wire_cap:          obj = ClibVarType_RELATED_OUT_OUTPUT_NET_WIRE_CAP; break;
  case ClibVarType::related_out_output_net_pin_cap:           obj = ClibVarType_RELATED_OUT_OUTPUT_NET_PIN_CAP; break;
  case ClibVarType::constrained_pin_transition:               obj = ClibVarType_CONSTRAINED_PIN_TRANSITION; break;
  case ClibVarType::related_pin_transition:                   obj = ClibVarType_RELATED_PIN_TRANSITION; break;
  case ClibVarType::none:                                     Py_RETURN_NONE;
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibVarType タイプか調べる．
bool
PyClibVarType::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibVarType を表す PyObject から ClibVarType を取り出す．
ClibVarType
PyClibVarType::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibVarTypeObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibVarType を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibVarType::_typeobject()
{
  return &ClibVarType_Type;
}

END_NAMESPACE_YM
