
/// @file CiLutHash.cc
/// @brief CiLutHash の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiLutHash.h"
#include "ci/CiLutTemplate.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLutHash
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiLutHash::CiLutHash(
) : mSize{0},
    mTable{nullptr},
    mLimit{0},
    mNum{0}
{
  alloc_table(64);
}

// @brief デストラクタ
CiLutHash::~CiLutHash()
{
  delete [] mTable;
}

// @brief テンプレートを追加する．
void
CiLutHash::add(
  CiLutTemplate* templ
)
{
  if ( mNum > mLimit ) {
    // テーブルを拡張する．
    auto old_size = mSize;
    auto old_table = mTable;
    alloc_table(old_size << 1);
    for ( auto i = 0; i < old_size; ++ i ) {
      for ( auto templ = old_table[i]; templ; ) {
	auto tmp = templ;
	templ = tmp->mLink;
	auto pos = tmp->mName.hash() % mSize;
	tmp->mLink = mTable[pos];
	mTable[pos] = tmp;
      }
    }
    delete [] old_table;
  }

  auto pos = templ->mName.hash() % mSize;
  templ->mLink = mTable[pos];
  mTable[pos] = templ;
  ++ mNum;
}

// @brief テンプレートを取り出す．
CiLutTemplate*
CiLutHash::get(
  ShString name
) const
{
  auto pos = name.hash() % mSize;
  for ( auto templ = mTable[pos]; templ; templ = templ->mLink ) {
    if ( templ->mName == name ) {
      return templ;
    }
  }
  return nullptr;
}

// @brief テーブルの領域を確保する．
void
CiLutHash::alloc_table(
  SizeType req_size
)
{
  mSize = req_size;
  mLimit = static_cast<SizeType>(mSize * 1.8);
  mTable = new CiLutTemplate*[mSize];
  for ( auto i = 0; i < mSize; ++ i ) {
    mTable[i] = nullptr;
  }
}

END_NAMESPACE_YM_CLIB
