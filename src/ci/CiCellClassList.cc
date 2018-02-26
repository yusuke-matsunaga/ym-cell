
/// @file CiCellClassList.cc
/// @brief CiCellClassList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellClassList.h"


BEGIN_NAMESPACE_YM_CLIB

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

// @brief 内容を初期化する．
// @param[in] group_list セルグループのリスト
// @param[in] alloc メモリアロケータ
void
CiCellClassList::init(const vector<const ClibCellClass*>& group_list,
		      Alloc& alloc)
{
  mNum = group_list.size();
  if ( mNum == 0 ) {
    return;
  }
  void* p = alloc.get_memory(sizeof(const ClibCellClass*) * mNum);
  mArray = new (p) const ClibCellClass*[mNum];
  for ( int i = 0; i < mNum; ++ i ) {
    const ClibCellClass* group = group_list[i];
    mArray[i] = group;
  }
}

// @brief 要素数を返す．
int
CiCellClassList::num() const
{
  return mNum;
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

END_NAMESPACE_YM_CLIB
