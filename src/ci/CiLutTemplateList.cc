
/// @file CiLutTemplateList.cc
/// @brief CiLutTemplateList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiLutTemplateList.h"
#include "ci/CiLutTemplate.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLutTemplateList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
//
// 内容は不定
CiLutTemplateList::CiLutTemplateList()
{
  mNum = 0;
  mArray = nullptr;
}

// @brief デストラクタ
CiLutTemplateList::~CiLutTemplateList()
{
}

// @brief 要素数を返す．
int
CiLutTemplateList::num() const
{
  return mNum;
}

// @brief 要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
const ClibLutTemplate*
CiLutTemplateList::operator[](int pos) const
{
  ASSERT_COND( pos >= 0 && pos < num() );

  return mArray[pos];
}

// @brief 先頭の反復子を返す．
ClibLutTemplateList::iterator
CiLutTemplateList::begin() const
{
  return iterator(&mArray[0]);
}

// @brief 末尾の反復子を返す．
ClibLutTemplateList::iterator
CiLutTemplateList::end() const
{
  return iterator(&mArray[mNum]);
}

// @brief 内容を初期化する．
// @param[in] templ_list 要素のリスト
// @param[in] alloc メモリアロケータ
void
CiLutTemplateList::init(const vector<CiLutTemplate*>& templ_list,
			Alloc& alloc)
{
  mNum = templ_list.size();
  if ( mNum == 0 ) {
    return;
  }
  mArray = alloc.get_array<const ClibLutTemplate*>(mNum);
  for ( int i = 0; i < mNum; ++ i ) {
    mArray[i] = templ_list[i];
  }
}

END_NAMESPACE_YM_CLIB
