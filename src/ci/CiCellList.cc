
/// @file CiCellList.cc
/// @brief CiCellList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellList.h"
#include "ci/CiCell.h" // これがないと CiCell -> ClibCell へのキャストができない．


BEGIN_NAMESPACE_YM_CLIB


//////////////////////////////////////////////////////////////////////
// クラス ClibCellListIterator
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @brief obj_ptr 要素へのポインタ
ClibCellListIterator::ClibCellListIterator(CiCell** obj_ptr) :
  mObjPtr(obj_ptr)
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
  return static_cast<const ClibCell*>(*mObjPtr);
}

// @brief increment 演算子
const ClibCellListIterator&
ClibCellListIterator::operator++()
{
  ++ mObjPtr;

  return *this;
}

// @brief 等価比較演算子
bool
ClibCellListIterator::operator==(const ClibCellListIterator& right) const
{
  return mObjPtr == right.mObjPtr;
}

// @brief 非等価比較演算子
bool
ClibCellListIterator::operator!=(const ClibCellListIterator& right) const
{
  return !operator==(right);
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellList::CiCellList()
{
  mNum = 0;
  mArray = nullptr;
}

// @brief デストラクタ
CiCellList::~CiCellList()
{
}

// @brief 要素数を返す．
int
CiCellList::num() const
{
  return mNum;
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
const ClibCell*
CiCellList::operator[](int pos) const
{
  return _elem(pos);
}

// @brief 先頭の反復子を返す．
ClibCellList::iterator
CiCellList::begin() const
{
  return ClibCellList::iterator(&mArray[0]);
}

// @brief 末尾の反復子を返す．
ClibCellList::iterator
CiCellList::end() const
{
  return ClibCellList::iterator(&mArray[mNum]);
}

// @brief 内容を初期化する．
// @param[in] src_list セルのリスト
// @param[in] alloc メモリアロケータ
void
CiCellList::init(const vector<CiCell*>& cell_list,
		 Alloc& alloc)
{
  mNum = cell_list.size();
  if ( mNum == 0 ) {
    return;
  }
  void* p = alloc.get_memory(sizeof(CiCell*) * mNum);
  mArray = new (p) CiCell*[mNum];
  for ( int i = 0; i < mNum; ++ i ) {
    CiCell* cell = cell_list[i];
    mArray[i] = cell;
  }
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
const CiCell*
CiCellList::_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < num() );

  return mArray[pos];
}

END_NAMESPACE_YM_CLIB
