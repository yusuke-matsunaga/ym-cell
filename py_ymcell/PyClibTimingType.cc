
/// @file PyClibTimingType.cc
/// @brief PyClibTimingType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibTimingType.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibTimingTypeObject
{
  PyObject_HEAD
  ClibTimingType mVal;
};

// Python 用のタイプ定義
PyTypeObject ClibTimingTypeType = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 各定数を表す文字列
const char* COMBINATIONAL_STR            = "combinational";
const char* COMBINATIONAL_RISE_STR       = "combinational_rise";
const char* COMBINATIONAL_FALL_STR       = "combinational_fall";
const char* THREE_STATE_ENABLE_STR       = "three_state_enable";
const char* THREE_STATE_DISABLE_STR      = "three_state_disable";
const char* THREE_STATE_ENABLE_RISE_STR  = "three_state_enable_rise";
const char* THREE_STATE_ENABLE_FALL_STR  = "three_state_enable_fall";
const char* THREE_STATE_DISABLE_RISE_STR = "three_state_disable_rise";
const char* THREE_STATE_DISABLE_FALL_STR = "three_state_disable_fall";
const char* RISING_EDGE_STR              = "rising_edge";
const char* FALLING_EDGE_STR             = "falling_edge";
const char* PRESET_STR                   = "preset";
const char* CLEAR_STR                    = "clear";
const char* HOLD_RISING_STR              = "hold_rising";
const char* HOLD_FALLING_STR             = "hold_falling";
const char* SETUP_RISING_STR             = "setup_rising";
const char* SETUP_FALLING_STR            = "setup_falling";
const char* RECOVERY_RISING_STR          = "recovery_rising";
const char* RECOVERY_FALLING_STR         = "recovery_falling";
const char* SKEW_RISING_STR              = "skew_rising";
const char* SKEW_FALLING_STR             = "skew_falling";
const char* REMOVAL_RISING_STR           = "removal_rising";
const char* REMOVAL_FALLING_STR          = "removal_falling";
const char* NON_SEQ_SETUP_RISING_STR     = "non_seq_setup_rising";
const char* NON_SEQ_SETUP_FALLING_STR    = "non_seq_setup_falling";
const char* NON_SEQ_HOLD_RISING_STR      = "non_seq_hold_rising";
const char* NON_SEQ_HOLD_FALLING_STR     = "non_seq_hold_falling";
const char* NOCHANGE_HIGH_HIGH_STR       = "nochange_high_high";
const char* NOCHANGE_HIGH_LOW_STR        = "nochange_high_low";
const char* NOCHANGE_LOW_HIGH_STR        = "nochange_low_high";
const char* NOCHANGE_LOW_LOW_STR         = "nochange_low_low";

// 各定数を表す PyObject
PyObject* ClibTimingType_COMBINATIONAL            = nullptr;
PyObject* ClibTimingType_COMBINATIONAL_RISE       = nullptr;
PyObject* ClibTimingType_COMBINATIONAL_FALL       = nullptr;
PyObject* ClibTimingType_THREE_STATE_ENABLE       = nullptr;
PyObject* ClibTimingType_THREE_STATE_DISABLE      = nullptr;
PyObject* ClibTimingType_THREE_STATE_ENABLE_RISE  = nullptr;
PyObject* ClibTimingType_THREE_STATE_ENABLE_FALL  = nullptr;
PyObject* ClibTimingType_THREE_STATE_DISABLE_RISE = nullptr;
PyObject* ClibTimingType_THREE_STATE_DISABLE_FALL = nullptr;
PyObject* ClibTimingType_RISING_EDGE              = nullptr;
PyObject* ClibTimingType_FALLING_EDGE             = nullptr;
PyObject* ClibTimingType_PRESET                   = nullptr;
PyObject* ClibTimingType_CLEAR                    = nullptr;
PyObject* ClibTimingType_HOLD_RISING              = nullptr;
PyObject* ClibTimingType_HOLD_FALLING             = nullptr;
PyObject* ClibTimingType_SETUP_RISING             = nullptr;
PyObject* ClibTimingType_SETUP_FALLING            = nullptr;
PyObject* ClibTimingType_RECOVERY_RISING          = nullptr;
PyObject* ClibTimingType_RECOVERY_FALLING         = nullptr;
PyObject* ClibTimingType_SKEW_RISING              = nullptr;
PyObject* ClibTimingType_SKEW_FALLING             = nullptr;
PyObject* ClibTimingType_REMOVAL_RISING           = nullptr;
PyObject* ClibTimingType_REMOVAL_FALLING          = nullptr;
PyObject* ClibTimingType_NON_SEQ_SETUP_RISING     = nullptr;
PyObject* ClibTimingType_NON_SEQ_SETUP_FALLING    = nullptr;
PyObject* ClibTimingType_NON_SEQ_HOLD_RISING      = nullptr;
PyObject* ClibTimingType_NON_SEQ_HOLD_FALLING     = nullptr;
PyObject* ClibTimingType_NOCHANGE_HIGH_HIGH       = nullptr;
PyObject* ClibTimingType_NOCHANGE_HIGH_LOW        = nullptr;
PyObject* ClibTimingType_NOCHANGE_LOW_HIGH        = nullptr;
PyObject* ClibTimingType_NOCHANGE_LOW_LOW         = nullptr;

// 生成関数
PyObject*
ClibTimingType_new(
  PyTypeObject* type,
  PyObject* args,
  PyObject* kwds
)
{
  if ( type != &ClibTimingTypeType ) {
    PyErr_SetString(PyExc_TypeError, "ClibTimingType cannot be overloaded");
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
  ClibTimingType val;
  if ( strcasecmp(name_str, COMBINATIONAL_STR) == 0 ) {
    val = ClibTimingType::combinational;
  }
  else if ( strcasecmp(name_str, COMBINATIONAL_RISE_STR) == 0 ) {
    val = ClibTimingType::combinational_rise;
  }
  else if ( strcasecmp(name_str, COMBINATIONAL_FALL_STR) == 0 ) {
    val = ClibTimingType::combinational_fall;
  }
  else if ( strcasecmp(name_str, THREE_STATE_ENABLE_STR) == 0 ) {
    val = ClibTimingType::three_state_enable;
  }
  else if ( strcasecmp(name_str, THREE_STATE_DISABLE_STR) == 0 ) {
    val = ClibTimingType::three_state_disable;
  }
  else if ( strcasecmp(name_str, THREE_STATE_ENABLE_RISE_STR) == 0 ) {
    val = ClibTimingType::three_state_enable_rise;
  }
  else if ( strcasecmp(name_str, THREE_STATE_ENABLE_FALL_STR) == 0 ) {
    val = ClibTimingType::three_state_enable_fall;
  }
  else if ( strcasecmp(name_str, THREE_STATE_DISABLE_RISE_STR) == 0 ) {
    val = ClibTimingType::three_state_disable_rise;
  }
  else if ( strcasecmp(name_str, THREE_STATE_DISABLE_FALL_STR) == 0 ) {
    val = ClibTimingType::three_state_disable_fall;
  }
  else if ( strcasecmp(name_str, RISING_EDGE_STR) == 0 ) {
    val = ClibTimingType::rising_edge;
  }
  else if ( strcasecmp(name_str, FALLING_EDGE_STR) == 0 ) {
    val = ClibTimingType::falling_edge;
  }
  else if ( strcasecmp(name_str, PRESET_STR) == 0 ) {
    val = ClibTimingType::preset;
  }
  else if ( strcasecmp(name_str, CLEAR_STR) == 0 ) {
    val = ClibTimingType::clear;
  }
  else if ( strcasecmp(name_str, HOLD_RISING_STR) == 0 ) {
    val = ClibTimingType::hold_rising;
  }
  else if ( strcasecmp(name_str, HOLD_FALLING_STR) == 0 ) {
    val = ClibTimingType::hold_falling;
  }
  else if ( strcasecmp(name_str, SETUP_RISING_STR) == 0 ) {
    val = ClibTimingType::setup_rising;
  }
  else if ( strcasecmp(name_str, SETUP_FALLING_STR) == 0 ) {
    val = ClibTimingType::setup_falling;
  }
  else if ( strcasecmp(name_str, RECOVERY_RISING_STR) == 0 ) {
    val = ClibTimingType::recovery_rising;
  }
  else if ( strcasecmp(name_str, RECOVERY_FALLING_STR) == 0 ) {
    val = ClibTimingType::recovery_falling;
  }
  else if ( strcasecmp(name_str, SKEW_RISING_STR) == 0 ) {
    val = ClibTimingType::skew_rising;
  }
  else if ( strcasecmp(name_str, SKEW_FALLING_STR) == 0 ) {
    val = ClibTimingType::skew_falling;
  }
  else if ( strcasecmp(name_str, REMOVAL_RISING_STR) == 0 ) {
    val = ClibTimingType::removal_rising;
  }
  else if ( strcasecmp(name_str, REMOVAL_FALLING_STR) == 0 ) {
    val = ClibTimingType::removal_falling;
  }
  else if ( strcasecmp(name_str, NON_SEQ_SETUP_RISING_STR) == 0 ) {
    val = ClibTimingType::non_seq_setup_rising;
  }
  else if ( strcasecmp(name_str, NON_SEQ_SETUP_FALLING_STR) == 0 ) {
    val = ClibTimingType::non_seq_setup_falling;
  }
  else if ( strcasecmp(name_str, NON_SEQ_HOLD_RISING_STR) == 0 ) {
    val = ClibTimingType::non_seq_hold_rising;
  }
  else if ( strcasecmp(name_str, NON_SEQ_HOLD_FALLING_STR) == 0 ) {
    val = ClibTimingType::non_seq_hold_falling;
  }
  else if ( strcasecmp(name_str, NOCHANGE_HIGH_HIGH_STR) == 0 ) {
    val = ClibTimingType::nochange_high_high;
  }
  else if ( strcasecmp(name_str, NOCHANGE_HIGH_LOW_STR) == 0 ) {
    val = ClibTimingType::nochange_high_low;
  }
  else if ( strcasecmp(name_str, NOCHANGE_LOW_HIGH_STR) == 0 ) {
    val = ClibTimingType::nochange_low_high;
  }
  else if ( strcasecmp(name_str, NOCHANGE_LOW_LOW_STR) == 0 ) {
    val = ClibTimingType::nochange_low_low;
  }
  else if ( strcasecmp(name_str, "none") == 0 ) {
    val = ClibTimingType::none;
  }
  else {
    // エラー
    ostringstream buf;
    buf << "argument 1 must be one of \""
        << COMBINATIONAL_STR
        << "\", \""
        << COMBINATIONAL_RISE_STR
        << "\", \""
        << COMBINATIONAL_FALL_STR
        << "\", \""
        << THREE_STATE_ENABLE_STR
        << "\", \""
        << THREE_STATE_DISABLE_STR
        << "\", \""
        << THREE_STATE_ENABLE_RISE_STR
        << "\", \""
        << THREE_STATE_ENABLE_FALL_STR
        << "\", \""
        << THREE_STATE_DISABLE_RISE_STR
        << "\", \""
        << THREE_STATE_DISABLE_FALL_STR
        << "\", \""
        << RISING_EDGE_STR
        << "\", \""
        << FALLING_EDGE_STR
        << "\", \""
        << PRESET_STR
        << "\", \""
        << CLEAR_STR
        << "\", \""
        << HOLD_RISING_STR
        << "\", \""
        << HOLD_FALLING_STR
        << "\", \""
        << SETUP_RISING_STR
        << "\", \""
        << SETUP_FALLING_STR
        << "\", \""
        << RECOVERY_RISING_STR
        << "\", \""
        << RECOVERY_FALLING_STR
        << "\", \""
        << SKEW_RISING_STR
        << "\", \""
        << SKEW_FALLING_STR
        << "\", \""
        << REMOVAL_RISING_STR
        << "\", \""
        << REMOVAL_FALLING_STR
        << "\", \""
        << NON_SEQ_SETUP_RISING_STR
        << "\", \""
        << NON_SEQ_SETUP_FALLING_STR
        << "\", \""
        << NON_SEQ_HOLD_RISING_STR
        << "\", \""
        << NON_SEQ_HOLD_FALLING_STR
        << "\", \""
        << NOCHANGE_HIGH_HIGH_STR
        << "\", \""
        << NOCHANGE_HIGH_LOW_STR
        << "\", \""
        << NOCHANGE_LOW_HIGH_STR
        << "\", \""
        << NOCHANGE_LOW_LOW_STR
        << "\", \""
        << "none"
        << "\"";
    PyErr_SetString(PyExc_ValueError, buf.str().c_str());
    return nullptr;
  }
  return PyClibTimingType::ToPyObject(val);
}

// 終了関数
void
ClibTimingType_dealloc(
  PyObject* self
)
{
  // auto val_obj = reinterpret_cast<ClibTimingTypeObject*>(self);
  // 必要なら val_obj->mVal の終了処理を行う．
  Py_TYPE(self)->tp_free(self);
}

// repr() 関数
PyObject*
ClibTimingType_repr(
  PyObject* self
)
{
  auto val = PyClibTimingType::Get(self);
  const char* tmp_str = nullptr;
  switch ( val ) {
  case ClibTimingType::combinational:            tmp_str = COMBINATIONAL_STR; break;
  case ClibTimingType::combinational_rise:       tmp_str = COMBINATIONAL_RISE_STR; break;
  case ClibTimingType::combinational_fall:       tmp_str = COMBINATIONAL_FALL_STR; break;
  case ClibTimingType::three_state_enable:       tmp_str = THREE_STATE_ENABLE_STR; break;
  case ClibTimingType::three_state_disable:      tmp_str = THREE_STATE_DISABLE_STR; break;
  case ClibTimingType::three_state_enable_rise:  tmp_str = THREE_STATE_ENABLE_RISE_STR; break;
  case ClibTimingType::three_state_enable_fall:  tmp_str = THREE_STATE_ENABLE_FALL_STR; break;
  case ClibTimingType::three_state_disable_rise: tmp_str = THREE_STATE_DISABLE_RISE_STR; break;
  case ClibTimingType::three_state_disable_fall: tmp_str = THREE_STATE_DISABLE_FALL_STR; break;
  case ClibTimingType::rising_edge:              tmp_str = RISING_EDGE_STR; break;
  case ClibTimingType::falling_edge:             tmp_str = FALLING_EDGE_STR; break;
  case ClibTimingType::preset:                   tmp_str = PRESET_STR; break;
  case ClibTimingType::clear:                    tmp_str = CLEAR_STR; break;
  case ClibTimingType::hold_rising:              tmp_str = HOLD_RISING_STR; break;
  case ClibTimingType::hold_falling:             tmp_str = HOLD_FALLING_STR; break;
  case ClibTimingType::setup_rising:             tmp_str = SETUP_RISING_STR; break;
  case ClibTimingType::setup_falling:            tmp_str = SETUP_FALLING_STR; break;
  case ClibTimingType::recovery_rising:          tmp_str = RECOVERY_RISING_STR; break;
  case ClibTimingType::recovery_falling:         tmp_str = RECOVERY_FALLING_STR; break;
  case ClibTimingType::skew_rising:              tmp_str = SKEW_RISING_STR; break;
  case ClibTimingType::skew_falling:             tmp_str = SKEW_FALLING_STR; break;
  case ClibTimingType::removal_rising:           tmp_str = REMOVAL_RISING_STR; break;
  case ClibTimingType::removal_falling:          tmp_str = REMOVAL_FALLING_STR; break;
  case ClibTimingType::non_seq_setup_rising:     tmp_str = NON_SEQ_SETUP_RISING_STR; break;
  case ClibTimingType::non_seq_setup_falling:    tmp_str = NON_SEQ_SETUP_FALLING_STR; break;
  case ClibTimingType::non_seq_hold_rising:      tmp_str = NON_SEQ_HOLD_RISING_STR; break;
  case ClibTimingType::non_seq_hold_falling:     tmp_str = NON_SEQ_HOLD_FALLING_STR; break;
  case ClibTimingType::nochange_high_high:       tmp_str = NOCHANGE_HIGH_HIGH_STR; break;
  case ClibTimingType::nochange_high_low:        tmp_str = NOCHANGE_HIGH_LOW_STR; break;
  case ClibTimingType::nochange_low_high:        tmp_str = NOCHANGE_LOW_HIGH_STR; break;
  case ClibTimingType::nochange_low_low:         tmp_str = NOCHANGE_LOW_LOW_STR; break;
  case ClibTimingType::none:                     tmp_str = ""; break;
  }
  return Py_BuildValue("s", tmp_str);
}

// 比較関数
PyObject*
ClibTimingType_richcmpfunc(
  PyObject* self,
  PyObject* other,
  int op
)
{
  if ( PyClibTimingType::Check(self) &&
       PyClibTimingType::Check(other) ) {
    auto val1 = PyClibTimingType::Get(self);
    auto val2 = PyClibTimingType::Get(other);
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
  ClibTimingType val
)
{
  auto obj = ClibTimingTypeType.tp_alloc(&ClibTimingTypeType, 0);
  auto val_obj = reinterpret_cast<ClibTimingTypeObject*>(obj);
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
  if ( PyDict_SetItemString(ClibTimingTypeType.tp_dict, name, obj) < 0 ) {
    return false;
  }
  return true;
}

END_NONAMESPACE


// @brief 初期化する．
bool
PyClibTimingType::init(
  PyObject* m
)
{
  ClibTimingTypeType.tp_name = "ClibTimingType";
  ClibTimingTypeType.tp_basicsize = sizeof(ClibTimingTypeObject);
  ClibTimingTypeType.tp_itemsize = 0;
  ClibTimingTypeType.tp_dealloc = ClibTimingType_dealloc;
  ClibTimingTypeType.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibTimingTypeType.tp_doc = PyDoc_STR("ClibTimingType objects");
  ClibTimingTypeType.tp_richcompare = ClibTimingType_richcmpfunc;
  ClibTimingTypeType.tp_new = ClibTimingType_new;
  ClibTimingTypeType.tp_repr = ClibTimingType_repr;
  if ( PyType_Ready(&ClibTimingTypeType) < 0 ) {
    return false;
  }

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibTimingType", &ClibTimingTypeType) ) {
    goto error;
  }

  // 定数オブジェクトの生成
  ClibTimingType_COMBINATIONAL            = new_obj(ClibTimingType::combinational);
  ClibTimingType_COMBINATIONAL_RISE       = new_obj(ClibTimingType::combinational_rise);
  ClibTimingType_COMBINATIONAL_FALL       = new_obj(ClibTimingType::combinational_fall);
  ClibTimingType_THREE_STATE_ENABLE       = new_obj(ClibTimingType::three_state_enable);
  ClibTimingType_THREE_STATE_DISABLE      = new_obj(ClibTimingType::three_state_disable);
  ClibTimingType_THREE_STATE_ENABLE_RISE  = new_obj(ClibTimingType::three_state_enable_rise);
  ClibTimingType_THREE_STATE_ENABLE_FALL  = new_obj(ClibTimingType::three_state_enable_fall);
  ClibTimingType_THREE_STATE_DISABLE_RISE = new_obj(ClibTimingType::three_state_disable_rise);
  ClibTimingType_THREE_STATE_DISABLE_FALL = new_obj(ClibTimingType::three_state_disable_fall);
  ClibTimingType_RISING_EDGE              = new_obj(ClibTimingType::rising_edge);
  ClibTimingType_FALLING_EDGE             = new_obj(ClibTimingType::falling_edge);
  ClibTimingType_PRESET                   = new_obj(ClibTimingType::preset);
  ClibTimingType_CLEAR                    = new_obj(ClibTimingType::clear);
  ClibTimingType_HOLD_RISING              = new_obj(ClibTimingType::hold_rising);
  ClibTimingType_HOLD_FALLING             = new_obj(ClibTimingType::hold_falling);
  ClibTimingType_SETUP_RISING             = new_obj(ClibTimingType::setup_rising);
  ClibTimingType_SETUP_FALLING            = new_obj(ClibTimingType::setup_falling);
  ClibTimingType_RECOVERY_RISING          = new_obj(ClibTimingType::recovery_rising);
  ClibTimingType_RECOVERY_FALLING         = new_obj(ClibTimingType::recovery_falling);
  ClibTimingType_SKEW_RISING              = new_obj(ClibTimingType::skew_rising);
  ClibTimingType_SKEW_FALLING             = new_obj(ClibTimingType::skew_falling);
  ClibTimingType_REMOVAL_RISING           = new_obj(ClibTimingType::removal_rising);
  ClibTimingType_REMOVAL_FALLING          = new_obj(ClibTimingType::removal_falling);
  ClibTimingType_NON_SEQ_SETUP_RISING     = new_obj(ClibTimingType::non_seq_setup_rising);
  ClibTimingType_NON_SEQ_SETUP_FALLING    = new_obj(ClibTimingType::non_seq_setup_falling);
  ClibTimingType_NON_SEQ_HOLD_RISING      = new_obj(ClibTimingType::non_seq_hold_rising);
  ClibTimingType_NON_SEQ_HOLD_FALLING     = new_obj(ClibTimingType::non_seq_hold_falling);
  ClibTimingType_NOCHANGE_HIGH_HIGH       = new_obj(ClibTimingType::nochange_high_high);
  ClibTimingType_NOCHANGE_HIGH_LOW        = new_obj(ClibTimingType::nochange_high_low);
  ClibTimingType_NOCHANGE_LOW_HIGH        = new_obj(ClibTimingType::nochange_low_high);
  ClibTimingType_NOCHANGE_LOW_LOW         = new_obj(ClibTimingType::nochange_low_low);

  // 定数の登録
  if ( !reg_obj(COMBINATIONAL_STR, ClibTimingType_COMBINATIONAL) ) {
    goto error;
  }
  if ( !reg_obj(COMBINATIONAL_RISE_STR, ClibTimingType_COMBINATIONAL_RISE) ) {
    goto error;
  }
  if ( !reg_obj(COMBINATIONAL_FALL_STR, ClibTimingType_COMBINATIONAL_FALL) ) {
    goto error;
  }
  if ( !reg_obj(THREE_STATE_ENABLE_STR, ClibTimingType_THREE_STATE_ENABLE) ) {
    goto error;
  }
  if ( !reg_obj(THREE_STATE_DISABLE_STR, ClibTimingType_THREE_STATE_DISABLE) ) {
    goto error;
  }
  if ( !reg_obj(THREE_STATE_ENABLE_RISE_STR, ClibTimingType_THREE_STATE_ENABLE_RISE) ) {
    goto error;
  }
  if ( !reg_obj(THREE_STATE_ENABLE_FALL_STR, ClibTimingType_THREE_STATE_ENABLE_FALL) ) {
    goto error;
  }
  if ( !reg_obj(THREE_STATE_DISABLE_RISE_STR, ClibTimingType_THREE_STATE_DISABLE_RISE) ) {
    goto error;
  }
  if ( !reg_obj(THREE_STATE_DISABLE_FALL_STR, ClibTimingType_THREE_STATE_DISABLE_FALL) ) {
    goto error;
  }
  if ( !reg_obj(RISING_EDGE_STR, ClibTimingType_RISING_EDGE) ) {
    goto error;
  }
  if ( !reg_obj(FALLING_EDGE_STR, ClibTimingType_FALLING_EDGE) ) {
    goto error;
  }
  if ( !reg_obj(PRESET_STR, ClibTimingType_PRESET) ) {
    goto error;
  }
  if ( !reg_obj(CLEAR_STR, ClibTimingType_CLEAR) ) {
    goto error;
  }
  if ( !reg_obj(HOLD_RISING_STR, ClibTimingType_HOLD_RISING) ) {
    goto error;
  }
  if ( !reg_obj(HOLD_FALLING_STR, ClibTimingType_HOLD_FALLING) ) {
    goto error;
  }
  if ( !reg_obj(SETUP_RISING_STR, ClibTimingType_SETUP_RISING) ) {
    goto error;
  }
  if ( !reg_obj(SETUP_FALLING_STR, ClibTimingType_SETUP_FALLING) ) {
    goto error;
  }
  if ( !reg_obj(RECOVERY_RISING_STR, ClibTimingType_RECOVERY_RISING) ) {
    goto error;
  }
  if ( !reg_obj(RECOVERY_FALLING_STR, ClibTimingType_RECOVERY_FALLING) ) {
    goto error;
  }
  if ( !reg_obj(SKEW_RISING_STR, ClibTimingType_SKEW_RISING) ) {
    goto error;
  }
  if ( !reg_obj(SKEW_FALLING_STR, ClibTimingType_SKEW_FALLING) ) {
    goto error;
  }
  if ( !reg_obj(REMOVAL_RISING_STR, ClibTimingType_REMOVAL_RISING) ) {
    goto error;
  }
  if ( !reg_obj(REMOVAL_FALLING_STR, ClibTimingType_REMOVAL_FALLING) ) {
    goto error;
  }
  if ( !reg_obj(NON_SEQ_SETUP_RISING_STR, ClibTimingType_NON_SEQ_SETUP_RISING) ) {
    goto error;
  }
  if ( !reg_obj(NON_SEQ_SETUP_FALLING_STR, ClibTimingType_NON_SEQ_SETUP_FALLING) ) {
    goto error;
  }
  if ( !reg_obj(NON_SEQ_HOLD_RISING_STR, ClibTimingType_NON_SEQ_HOLD_RISING) ) {
    goto error;
  }
  if ( !reg_obj(NON_SEQ_HOLD_FALLING_STR, ClibTimingType_NON_SEQ_HOLD_FALLING) ) {
    goto error;
  }
  if ( !reg_obj(NOCHANGE_HIGH_HIGH_STR, ClibTimingType_NOCHANGE_HIGH_HIGH) ) {
    goto error;
  }
  if ( !reg_obj(NOCHANGE_HIGH_LOW_STR, ClibTimingType_NOCHANGE_HIGH_LOW) ) {
    goto error;
  }
  if ( !reg_obj(NOCHANGE_LOW_HIGH_STR, ClibTimingType_NOCHANGE_LOW_HIGH) ) {
    goto error;
  }
  if ( !reg_obj(NOCHANGE_LOW_LOW_STR, ClibTimingType_NOCHANGE_LOW_LOW) ) {
    goto error;
  }

  return true;

 error:

  Py_XDECREF(ClibTimingType_COMBINATIONAL);
  Py_XDECREF(ClibTimingType_COMBINATIONAL_RISE);
  Py_XDECREF(ClibTimingType_COMBINATIONAL_FALL);
  Py_XDECREF(ClibTimingType_THREE_STATE_ENABLE);
  Py_XDECREF(ClibTimingType_THREE_STATE_DISABLE);
  Py_XDECREF(ClibTimingType_THREE_STATE_ENABLE_RISE);
  Py_XDECREF(ClibTimingType_THREE_STATE_ENABLE_FALL);
  Py_XDECREF(ClibTimingType_THREE_STATE_DISABLE_RISE);
  Py_XDECREF(ClibTimingType_THREE_STATE_DISABLE_FALL);
  Py_XDECREF(ClibTimingType_RISING_EDGE);
  Py_XDECREF(ClibTimingType_FALLING_EDGE);
  Py_XDECREF(ClibTimingType_PRESET);
  Py_XDECREF(ClibTimingType_CLEAR);
  Py_XDECREF(ClibTimingType_HOLD_RISING);
  Py_XDECREF(ClibTimingType_HOLD_FALLING);
  Py_XDECREF(ClibTimingType_SETUP_RISING);
  Py_XDECREF(ClibTimingType_SETUP_FALLING);
  Py_XDECREF(ClibTimingType_RECOVERY_RISING);
  Py_XDECREF(ClibTimingType_RECOVERY_FALLING);
  Py_XDECREF(ClibTimingType_SKEW_RISING);
  Py_XDECREF(ClibTimingType_SKEW_FALLING);
  Py_XDECREF(ClibTimingType_REMOVAL_RISING);
  Py_XDECREF(ClibTimingType_REMOVAL_FALLING);
  Py_XDECREF(ClibTimingType_NON_SEQ_SETUP_RISING);
  Py_XDECREF(ClibTimingType_NON_SEQ_SETUP_FALLING);
  Py_XDECREF(ClibTimingType_NON_SEQ_HOLD_RISING);
  Py_XDECREF(ClibTimingType_NON_SEQ_HOLD_FALLING);
  Py_XDECREF(ClibTimingType_NOCHANGE_HIGH_HIGH);
  Py_XDECREF(ClibTimingType_NOCHANGE_HIGH_LOW);
  Py_XDECREF(ClibTimingType_NOCHANGE_LOW_HIGH);
  Py_XDECREF(ClibTimingType_NOCHANGE_LOW_LOW);

  return false;
}

// @brief ClibTimingType を表す PyObject から ClibTimingType を取り出す．
bool
PyClibTimingType::FromPyObject(
  PyObject* obj,
  ClibTimingType& val,
  const char* msg
)
{
  if ( obj == Py_None ) {
    // 特例: None は ClibTimingType::none に変換する．
    val = ClibTimingType::none;
    return true;
  }

  if ( !Check(obj) ) {
    if ( msg == nullptr ) {
      msg = "object should be a ClibTimingType type";
    }
    PyErr_SetString(PyExc_TypeError, msg);
    return false;
  }
  val = Get(obj);
  return true;
}

// @brief ClibTimingType を表す PyObject を作る．
PyObject*
PyClibTimingType::ToPyObject(
  ClibTimingType val
)
{
  PyObject* obj = nullptr;
  switch ( val ) {
  case ClibTimingType::combinational:            obj = ClibTimingType_COMBINATIONAL; break;
  case ClibTimingType::combinational_rise:       obj = ClibTimingType_COMBINATIONAL_RISE; break;
  case ClibTimingType::combinational_fall:       obj = ClibTimingType_COMBINATIONAL_FALL; break;
  case ClibTimingType::three_state_enable:       obj = ClibTimingType_THREE_STATE_ENABLE; break;
  case ClibTimingType::three_state_disable:      obj = ClibTimingType_THREE_STATE_DISABLE; break;
  case ClibTimingType::three_state_enable_rise:  obj = ClibTimingType_THREE_STATE_ENABLE_RISE; break;
  case ClibTimingType::three_state_enable_fall:  obj = ClibTimingType_THREE_STATE_ENABLE_FALL; break;
  case ClibTimingType::three_state_disable_rise: obj = ClibTimingType_THREE_STATE_DISABLE_RISE; break;
  case ClibTimingType::three_state_disable_fall: obj = ClibTimingType_THREE_STATE_DISABLE_FALL; break;
  case ClibTimingType::rising_edge:              obj = ClibTimingType_RISING_EDGE; break;
  case ClibTimingType::falling_edge:             obj = ClibTimingType_FALLING_EDGE; break;
  case ClibTimingType::preset:                   obj = ClibTimingType_PRESET; break;
  case ClibTimingType::clear:                    obj = ClibTimingType_CLEAR; break;
  case ClibTimingType::hold_rising:              obj = ClibTimingType_HOLD_RISING; break;
  case ClibTimingType::hold_falling:             obj = ClibTimingType_HOLD_FALLING; break;
  case ClibTimingType::setup_rising:             obj = ClibTimingType_SETUP_RISING; break;
  case ClibTimingType::setup_falling:            obj = ClibTimingType_SETUP_FALLING; break;
  case ClibTimingType::recovery_rising:          obj = ClibTimingType_RECOVERY_RISING; break;
  case ClibTimingType::recovery_falling:         obj = ClibTimingType_RECOVERY_FALLING; break;
  case ClibTimingType::skew_rising:              obj = ClibTimingType_SKEW_RISING; break;
  case ClibTimingType::skew_falling:             obj = ClibTimingType_SKEW_FALLING; break;
  case ClibTimingType::removal_rising:           obj = ClibTimingType_REMOVAL_RISING; break;
  case ClibTimingType::removal_falling:          obj = ClibTimingType_REMOVAL_FALLING; break;
  case ClibTimingType::non_seq_setup_rising:     obj = ClibTimingType_NON_SEQ_SETUP_RISING; break;
  case ClibTimingType::non_seq_setup_falling:    obj = ClibTimingType_NON_SEQ_SETUP_FALLING; break;
  case ClibTimingType::non_seq_hold_rising:      obj = ClibTimingType_NON_SEQ_HOLD_RISING; break;
  case ClibTimingType::non_seq_hold_falling:     obj = ClibTimingType_NON_SEQ_HOLD_FALLING; break;
  case ClibTimingType::nochange_high_high:       obj = ClibTimingType_NOCHANGE_HIGH_HIGH; break;
  case ClibTimingType::nochange_high_low:        obj = ClibTimingType_NOCHANGE_HIGH_LOW; break;
  case ClibTimingType::nochange_low_high:        obj = ClibTimingType_NOCHANGE_LOW_HIGH; break;
  case ClibTimingType::nochange_low_low:         obj = ClibTimingType_NOCHANGE_LOW_LOW; break;
  case ClibTimingType::none:                     Py_RETURN_NONE;
  }
  Py_INCREF(obj);
  return obj;
}

// @brief PyObject が ClibTimingType タイプか調べる．
bool
PyClibTimingType::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibTimingType を表す PyObject から ClibTimingType を取り出す．
ClibTimingType
PyClibTimingType::Get(
  PyObject* obj
)
{
  auto val_obj = reinterpret_cast<ClibTimingTypeObject*>(obj);
  return val_obj->mVal;
}

// @brief ClibTimingType を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibTimingType::_typeobject()
{
  return &ClibTimingTypeType;
}

END_NAMESPACE_YM_CLIB
