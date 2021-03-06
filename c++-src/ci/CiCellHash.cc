﻿
/// @file CiCellHash.cc
/// @brief CiCellHash の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellHash.h"
#include "ci/CiCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellHash
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellHash::CiCellHash() :
  mSize(0),
  mTable(nullptr),
  mLimit(0),
  mNum(0)
{
  alloc_table(256);
}

// @brief デストラクタ
CiCellHash::~CiCellHash()
{
  delete [] mTable;
}

// @brief セルを追加する．
// @param[in] cell 追加するセル
void
CiCellHash::add(CiCell* cell)
{
  if ( mNum > mLimit ) {
    // テーブルを拡張する．
    int old_size = mSize;
    CiCell** old_table = mTable;
    alloc_table(old_size << 1);
    for ( int i = 0; i < old_size; ++ i ) {
      for ( CiCell* cell = old_table[i]; cell; ) {
	CiCell* tmp = cell;
	cell = tmp->mLink;
	int pos = tmp->mName.hash() % mSize;
	tmp->mLink = mTable[pos];
	mTable[pos] = tmp;
      }
    }
    delete [] old_table;
  }

  int pos = cell->mName.hash() % mSize;
  cell->mLink = mTable[pos];
  mTable[pos] = cell;
  ++ mNum;
}

// @brief セル番号を取り出す．
// @param[in] name 名前
// @return name という名前のセルのセル番号を返す．
//
// なければ -1 を返す．
int
CiCellHash::get(ShString name) const
{
  int pos = name.hash() % mSize;
  for ( CiCell* cell = mTable[pos]; cell; cell = cell->mLink ) {
    if ( cell->mName == name ) {
      return cell->mId;
    }
  }
  return -1;
}

// @brief テーブルの領域を確保する．
// @param[in] req_size 要求するサイズ
void
CiCellHash::alloc_table(int req_size)
{
  mSize = req_size;
  mLimit = static_cast<int>(mSize * 1.8);
  mTable = new CiCell*[mSize];
  for ( int i = 0; i < mSize; ++ i ) {
    mTable[i] = nullptr;
  }
}

END_NAMESPACE_YM_CLIB
