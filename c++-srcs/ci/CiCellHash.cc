
/// @file CiCellHash.cc
/// @brief CiCellHash の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellHash.h"
#include "ci/CiCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellHash
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellHash::CiCellHash(
) : mSize{0},
    mTable{nullptr},
    mLimit{0},
    mNum{0}
{
  alloc_table(256);
}

// @brief デストラクタ
CiCellHash::~CiCellHash()
{
  delete [] mTable;
}

// @brief セルを追加する．
void
CiCellHash::add(
  CiCell* cell
)
{
  if ( mNum > mLimit ) {
    // テーブルを拡張する．
    auto old_size = mSize;
    auto old_table = mTable;
    alloc_table(old_size << 1);
    for ( auto i = 0; i < old_size; ++ i ) {
      for ( auto cell = old_table[i]; cell; ) {
	auto tmp = cell;
	cell = tmp->mLink;
	auto pos = tmp->mName.hash() % mSize;
	tmp->mLink = mTable[pos];
	mTable[pos] = tmp;
      }
    }
    delete [] old_table;
  }

  auto pos = cell->mName.hash() % mSize;
  cell->mLink = mTable[pos];
  mTable[pos] = cell;
  ++ mNum;
}

// @brief セル番号を取り出す．
SizeType
CiCellHash::get(
  ShString name
) const
{
  auto pos = name.hash() % mSize;
  for ( auto cell = mTable[pos]; cell; cell = cell->mLink ) {
    if ( cell->mName == name ) {
      return cell->mId;
    }
  }
  return CLIB_NULLID;
}

// @brief テーブルの領域を確保する．
void
CiCellHash::alloc_table(
  SizeType req_size
)
{
  mSize = req_size;
  mLimit = static_cast<int>(mSize * 1.8);
  mTable = new CiCell*[mSize];
  for ( auto i = 0; i < mSize; ++ i ) {
    mTable[i] = nullptr;
  }
}

END_NAMESPACE_YM_CLIB
