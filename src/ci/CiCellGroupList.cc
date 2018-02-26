
/// @file CiCellGroupList.cc
/// @brief CiCellGroupList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellGroupList.h"


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

// @brief デストラクタ
CiCellGroupList::~CiCellGroupList()
{
}

// @brief 内容を初期化する．
// @param[in] group_list セルグループのリスト
// @param[in] alloc メモリアロケータ
void
CiCellGroupList::init(const vector<const ClibCellGroup*>& group_list,
		      Alloc& alloc)
{
  mNum = group_list.size();
  if ( mNum == 0 ) {
    return;
  }
  void* p = alloc.get_memory(sizeof(const ClibCellGroup*) * mNum);
  mArray = new (p) const ClibCellGroup*[mNum];
  for ( int i = 0; i < mNum; ++ i ) {
    const ClibCellGroup* group = group_list[i];
    mArray[i] = group;
  }
}

// @brief 要素数を返す．
int
CiCellGroupList::num() const
{
  return mNum;
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

END_NAMESPACE_YM_CLIB
