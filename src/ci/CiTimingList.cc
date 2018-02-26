
/// @file CiTimingList.cc
/// @brief CiTimingList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiTimingList.h"


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

// @brief 内容を初期化する．
// @param[in] num 要素数
// @param[in] alloc メモリアロケータ
//
// ここでは領域を確保するだけ．
void
CiTimingList::init(int num,
		   Alloc& alloc)
{
  if ( mNum == 0 ) {
    return;
  }
  void* p = alloc.get_memory(sizeof(const ClibTiming*) * mNum);
  mArray = new (p) const ClibTiming*[mNum];
}

// @brief 要素を設定する．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
// @param[in] timing 設定する要素
void
CiTimingList::set(int pos,
		  const ClibTiming* timing)
{
  ASSERT_COND( pos >= 0 && pos < num() );

  mArray[pos] = timing;
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

END_NAMESPACE_YM_CLIB
