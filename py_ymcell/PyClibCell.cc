
/// @file PyClibCell.cc
/// @brief Python ClibCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "pym/PyClibCell.h"
#include "pym/PyModule.h"


BEGIN_NAMESPACE_YM

BEGIN_NONAMESPACE

// Python 用のオブジェクト定義
struct ClibCellObject
{
  PyObject_HEAD
  ClibCell* mPtr;
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
  auto clibcelllibrary_obj = reinterpret_cast<ClibCellObject*>(self);
  delete clibcelllibrary_obj->mPtr;
  Py_TYPE(self)->tp_free(self);
}

// メソッド定義
PyMethodDef ClibCell_methods[] = {
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
  ClibCell val
)
{
  auto obj = ClibCell_Type.tp_alloc(&ClibCell_Type, 0);
  auto cell_obj = reinterpret_cast<ClibCellObject*>(obj);
  cell_obj->mPtr = new ClibCell{val};
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
  auto clibcelllibrary_obj = reinterpret_cast<ClibCellObject*>(obj);
  return *clibcelllibrary_obj->mPtr;
}

// @brief ClibCell を表すオブジェクトの型定義を返す．
PyTypeObject*
PyClibCell::_typeobject()
{
  return &ClibCell_Type;
}

END_NAMESPACE_YM
