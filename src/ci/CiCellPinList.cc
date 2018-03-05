
/// @file CiCellPinList.cc
/// @brief CiCellPinList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellPinList.h"
#include "ci/CiCellPin.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellPinList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellPinList::CiCellPinList()
{
  mNum = 0;
  mArray = nullptr;
}

// @brief デストラクタ
CiCellPinList::~CiCellPinList()
{
}

// @brief 要素数を返す．
int
CiCellPinList::num() const
{
  return mNum;
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
const ClibCellPin*
CiCellPinList::operator[](int pos) const
{
  ASSERT_COND( pos >= 0 && pos < num() );

  return mArray[pos];
}

// @brief 先頭の反復子を返す．
ClibCellPinList::iterator
CiCellPinList::begin() const
{
  return iterator(&mArray[0]);
}

// @brief 末尾の反復子を返す．
ClibCellPinList::iterator
CiCellPinList::end() const
{
  return iterator(&mArray[mNum]);
}

// @brief 内容を初期化する．
// @param[in] group_list 要素のリスト
// @param[in] alloc メモリアロケータ
void
CiCellPinList::init(const vector<CiCellPin*>& group_list,
		      Alloc& alloc)
{
  mNum = group_list.size();
  if ( mNum == 0 ) {
    return;
  }
  mArray = alloc.get_array<const ClibCellPin*>(mNum);
  for ( int i = 0; i < mNum; ++ i ) {
    mArray[i] = group_list[i];
  }
}

END_NAMESPACE_YM_CLIB
