
/// @file CiCellClassList.cc
/// @brief CiCellClassList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellClassList.h"
#include "ci/CiCellClass.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibCellClassListIterator
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @brief obj_ptr 要素へのポインタ
ClibCellClassListIterator::ClibCellClassListIterator(CiCellClass** obj_ptr) :
  mObjPtr(obj_ptr)
{
}

// @brief デストラクタ
ClibCellClassListIterator::~ClibCellClassListIterator()
{
}

// @brief dereference 演算子
const ClibCellClass*
ClibCellClassListIterator::operator*() const
{
  return *mObjPtr;
}

// @brief increment 演算子
const ClibCellClassListIterator&
ClibCellClassListIterator::operator++()
{
  ++ mObjPtr;

  return *this;
}

// @brief 等価比較演算子
bool
ClibCellClassListIterator::operator==(const ClibCellClassListIterator& right) const
{
  return mObjPtr == right.mObjPtr;
}

// @brief 非等価比較演算子
bool
ClibCellClassListIterator::operator!=(const ClibCellClassListIterator& right) const
{
  return !operator==(right);
}


//////////////////////////////////////////////////////////////////////
// クラス CiCellClassList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellClassList::CiCellClassList()
{
  mNum = 0;
  mArray = nullptr;
}

// @brief デストラクタ
CiCellClassList::~CiCellClassList()
{
}

// @brief 要素数を返す．
int
CiCellClassList::num() const
{
  return mNum;
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
const ClibCellClass*
CiCellClassList::operator[](int pos) const
{
  return _elem(pos);
}

// @brief 先頭の反復子を返す．
ClibCellClassList::iterator
CiCellClassList::begin() const
{
  return ClibCellClassList::iterator(&mArray[0]);
}

// @brief 末尾の反復子を返す．
ClibCellClassList::iterator
CiCellClassList::end() const
{
  return ClibCellClassList::iterator(&mArray[mNum]);
}

// @brief 内容を初期化する．
// @param[in] class_list セルクラスのリスト
// @param[in] alloc メモリアロケータ
void
CiCellClassList::init(const vector<CiCellClass*>& class_list,
		      Alloc& alloc)
{
  mNum = class_list.size();
  if ( mNum == 0 ) {
    return;
  }
  void* p = alloc.get_memory(sizeof(CiCellClass*) * mNum);
  mArray = new (p) CiCellClass*[mNum];
  for ( int i = 0; i < mNum; ++ i ) {
    mArray[i] = class_list[i];
  }
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
const CiCellClass*
CiCellClassList::_elem(int pos) const
{
  ASSERT_COND( pos >= 0 && pos < num() );

  return mArray[pos];
}

END_NAMESPACE_YM_CLIB
