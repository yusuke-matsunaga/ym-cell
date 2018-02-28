
/// @file CiCellGroupList.cc
/// @brief CiCellGroupList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellGroupList.h"
#include "ci/CiCellGroup.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibCellGroupListIterator
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @brief obj_ptr 要素へのポインタ
ClibCellGroupListIterator::ClibCellGroupListIterator(CiCellGroup** obj_ptr) :
  mObjPtr(obj_ptr)
{
}

// @brief デストラクタ
ClibCellGroupListIterator::~ClibCellGroupListIterator()
{
}

// @brief dereference 演算子
const ClibCellGroup*
ClibCellGroupListIterator::operator*() const
{
  return *mObjPtr;
}

// @brief increment 演算子
const ClibCellGroupListIterator&
ClibCellGroupListIterator::operator++()
{
  ++ mObjPtr;

  return *this;
}

// @brief 等価比較演算子
bool
ClibCellGroupListIterator::operator==(const ClibCellGroupListIterator& right) const
{
  return mObjPtr == right.mObjPtr;
}

// @brief 非等価比較演算子
bool
ClibCellGroupListIterator::operator!=(const ClibCellGroupListIterator& right) const
{
  return !operator==(right);
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellGroupList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellGroupList::CiCellGroupList()
{
  mNum = 0;
  mArray = nullptr;
}

// @brief デストラクタ
CiCellGroupList::~CiCellGroupList()
{
}

// @brief 要素数を返す．
int
CiCellGroupList::num() const
{
  return mNum;
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
const ClibCellGroup*
CiCellGroupList::operator[](int pos) const
{
  return _elem(pos);
}

// @brief 先頭の反復子を返す．
ClibCellGroupList::iterator
CiCellGroupList::begin() const
{
  return ClibCellGroupList::iterator(&mArray[0]);
}

// @brief 末尾の反復子を返す．
ClibCellGroupList::iterator
CiCellGroupList::end() const
{
  return ClibCellGroupList::iterator(&mArray[mNum]);
}

// @brief 内容を初期化する．
// @param[in] group_list 要素のリスト
// @param[in] alloc メモリアロケータ
void
CiCellGroupList::init(const vector<CiCellGroup*>& group_list,
		      Alloc& alloc)
{
  mNum = group_list.size();
  if ( mNum == 0 ) {
    return;
  }
  void* p = alloc.get_memory(sizeof(CiCellGroup*) * mNum);
  mArray = new (p) CiCellGroup*[mNum];
  for ( int i = 0; i < mNum; ++ i ) {
    mArray[i] = group_list[i];
  }
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
const CiCellGroup*
CiCellGroupList::_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < num() );

  return mArray[pos];
}

END_NAMESPACE_YM_CLIB
