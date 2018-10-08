
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
  ASSERT_COND( pos >= 0 && pos < num() );

  return mArray[pos];
}

// @brief 先頭の反復子を返す．
ClibCellClassList::iterator
CiCellClassList::begin() const
{
  return iterator(&mArray[0]);
}

// @brief 末尾の反復子を返す．
ClibCellClassList::iterator
CiCellClassList::end() const
{
  return iterator(&mArray[mNum]);
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
  mArray = alloc.get_array<const ClibCellClass*>(mNum);
  for ( int i = 0; i < mNum; ++ i ) {
    mArray[i] = class_list[i];
  }
}

END_NAMESPACE_YM_CLIB
