
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
// クラス CiCellGroupList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellGroupList::CiCellGroupList()
{
  mNum = 0;
  mArray = nullptr;
}

// @brief 内容を指定したコンストラクタ
// @param[in] group_list 要素のリスト
// @param[in] alloc メモリアロケータ
CiCellGroupList::CiCellGroupList(const vector<CiCellGroup*>& group_list,
				 Alloc& alloc) :
  mNum(group_list.size()),
  mArray(alloc.get_array<const ClibCellGroup*>(mNum))
{
  for ( int i = 0; i < mNum; ++ i ) {
    mArray[i] = group_list[i];
  }
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
  ASSERT_COND( pos >= 0 && pos < num() );

  return mArray[pos];
}

// @brief 先頭の反復子を返す．
ClibCellGroupList::iterator
CiCellGroupList::begin() const
{
  return iterator(&mArray[0]);
}

// @brief 末尾の反復子を返す．
ClibCellGroupList::iterator
CiCellGroupList::end() const
{
  return iterator(&mArray[mNum]);
}

// @brief 内容を初期化する．
// @param[in] group_list 要素のリスト
// @param[in] alloc メモリアロケータ
void
CiCellGroupList::init(const vector<CiCellGroup*>& group_list,
		      Alloc& alloc)
{
  mNum = group_list.size();
  mArray = alloc.get_array<const ClibCellGroup*>(mNum);
  for ( int i = 0; i < mNum; ++ i ) {
    mArray[i] = group_list[i];
  }
}

END_NAMESPACE_YM_CLIB
