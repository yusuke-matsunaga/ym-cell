
/// @file ClibCellList.cc
/// @brief ClibCellList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellList.h"


BEGIN_NAMESPACE_YM_CLIB

// @brief コンストラクタ
// @param[in] cell_ptr セルへのポインタ
ClibCellListIterator::ClibCellListIterator(const ClibCell** cell_ptr) :
  mCellPtr(cell_ptr)
{
}

// @brief デストラクタ
ClibCellListIterator::~ClibCellListIterator()
{
}

// @brief dereference 演算子
const ClibCell*
ClibCellListIterator::operator*() const
{
  return *mCellPtr;
}

// @brief increment 演算子
const ClibCellListIterator&
ClibCellListIterator::operator++()
{
  ++ mCellPtr;

  return *this;
}

// @brief 等価比較演算子
bool
ClibCellListIterator::operator==(const ClibCellListIterator& right) const
{
  return mCellPtr == right.mCellPtr;
}

// @relates ClibCellListIterator
// @brief 非等価比較演算子
bool
operator!=(const ClibCellListIterator& left,
	   const ClibCellListIterator& right)
{
  // お約束のコード
  return !left.operator==(right);
}

END_NAMESPACE_YM_CLIB
