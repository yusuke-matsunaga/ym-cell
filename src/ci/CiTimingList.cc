
/// @file CiTimingList.cc
/// @brief CiTimingList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiTimingList.h"
#include "ci/CiTiming.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiTimingList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiTimingList::CiTimingList()
{
  mNum = 0;
  mArray = nullptr;
}

// @brief デストラクタ
CiTimingList::~CiTimingList()
{
}

// @brief 要素数を返す．
int
CiTimingList::num() const
{
  return mNum;
}

// @brief 先頭の反復子を返す．
ClibTimingList::iterator
CiTimingList::begin() const
{
  return ClibTimingList::iterator(&mArray[0]);
}

// @brief 末尾の反復子を返す．
ClibTimingList::iterator
CiTimingList::end() const
{
  return ClibTimingList::iterator(&mArray[mNum]);
}

// @brief 指定された位置の要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
const ClibTiming*
CiTimingList::operator[](int pos) const
{
  ASSERT_COND( pos >= 0 && pos < num() );

  return mArray[pos];
}

// @brief 内容を初期化する．
// @param[in] timing_list 要素のリスト
// @param[in] alloc メモリアロケータ
void
CiTimingList::init(const vector<CiTiming*>& timing_list,
		   Alloc& alloc)
{
  mNum = timing_list.size();
  if ( mNum == 0 ) {
    return;
  }
  mArray = alloc.get_array<const ClibTiming*>(mNum);
  for ( int i = 0; i < mNum; ++ i ) {
    mArray[i] = timing_list[i];
  }
}

END_NAMESPACE_YM_CLIB
