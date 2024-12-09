
/// @file PyClibCell.cc
/// @brief Python ClibCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibCell.h"
#include "pym/PyClibTiming.h"
#include "pym/PyClibTimingSense.h"
#include "pym/PyModule.h"
#include "ym/ClibCell.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibCellObject
{
  PyObject_HEAD
  ClibCell mCell;
};

// Python 用のタイプ定義
PyTypeObject ClibCell_Type = {
  PyVarObject_HEAD_INIT(nullptr, 0)
};

// 生成関数
PyObject*
ClibCell_new(
  PyTypeObject* type,
  PyObject* Py_UNUSED(args),
  PyObject* Py_UNUSED(kwds)
)
{
  PyErr_SetString(PyExc_TypeError, "instantiation of 'ClibCell' is disabled");
  return nullptr;
}

// 終了関数
void
ClibCell_dealloc(
  PyObject* self
)
{
  auto cell_obj = reinterpret_cast<ClibCellObject*>(self);
  cell_obj->mCell.~ClibCell();
  Py_TYPE(self)->tp_free(self);
}

PyObject*
ClibCell_timing_list(
  PyObject* self,
  PyObject* args,
  PyObject* kwds
)
{
  static const char* kwlist[] = {
    "ipos",
    "opos",
    "sense",
    nullptr
  };
  SizeType ipos = 0;
  SizeType opos = 0;
  PyObject* sense_obj = nullptr;
  if ( !PyArg_ParseTupleAndKeywords(args, kwds, "kkO!",
				    const_cast<char**>(kwlist),
				    &ipos, &opos,
				    PyClibTimingSense::_typeobject(),
				    &sense_obj) ) {
    return nullptr;
  }
  auto sense = PyClibTimingSense::Get(sense_obj);
  auto cell = PyClibCell::Get(self);
  auto timing_list = cell.timing_list(ipos, opos, sense);
  SizeType n = timing_list.size();
  auto list_obj = PyList_New(n);
  for ( SizeType i = 0; i < n; ++ i ) {
    auto timing = timing_list[i];
    auto timing_obj = PyClibTiming::ToPyObject(timing);
    PyList_SetItem(list_obj, i, timing_obj);
  }
  return list_obj;
}

// メソッド定義
PyMethodDef ClibCell_methods[] = {
  {"timing_list",
   reinterpret_cast<PyCFunction>(ClibCell_timing_list),
   METH_VARARGS | METH_KEYWORDS,
   PyDoc_STR("get timing list")},
  {nullptr, nullptr, 0, nullptr}
};

END_NONAMESPACE


// @brief 'ClibCell' オブジェクトを使用可能にする．
bool
PyClibCell::init(
  PyObject* m
)
{
  ClibCell_Type.tp_name = "ClibCell";
  ClibCell_Type.tp_basicsize = sizeof(ClibCellObject);
  ClibCell_Type.tp_itemsize = 0;
  ClibCell_Type.tp_dealloc = ClibCell_dealloc;
  ClibCell_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  ClibCell_Type.tp_doc = PyDoc_STR("ClibCell objects");
  ClibCell_Type.tp_methods = ClibCell_methods;
  ClibCell_Type.tp_new = ClibCell_new;

  // 型オブジェクトの登録
  if ( !PyModule::reg_type(m, "ClibCell", &ClibCell_Type) ) {
    goto error;
  }

  return true;

 error:

  return false;
}

// @brief ClibCell を表す PyObject を作る．
PyObject*
PyClibCell::ToPyObject(
  const ClibCell& val
)
{
  auto obj = ClibCell_Type.tp_alloc(&ClibCell_Type, 0);
  auto cell_obj = reinterpret_cast<ClibCellObject*>(obj);
  new (&cell_obj->mCell) ClibCell{val};
  return obj;
}

// @brief PyObject が ClibCell タイプか調べる．
bool
PyClibCell::Check(
  PyObject* obj
)
{
  return Py_IS_TYPE(obj, _typeobject());
}

// @brief ClibCell を表す PyObject から ClibCell を取り出す．
const ClibCell&
PyClibCell::Get(
  PyObject* obj
)
{
  auto cell_obj = reinterpret_cast<ClibCellObject*>(obj);
  return cell_obj->mCell;
}

// @brief ClibCell を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibCell::_typeobject()
{
  return &ClibCell_Type;
}

END_NAMESPACE_YM
