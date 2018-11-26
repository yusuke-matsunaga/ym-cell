
/// @file CiCellPinHash.cc
/// @brief CiCellPinHash の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiCellPinHash.h"
#include "ci/CiCell.h"
#include "ci/CiCellPin.h"


BEGIN_NAMESPACE_YM_CLIB

BEGIN_NONAMESPACE

inline
SizeType
hash_func(const CiCell* cell,
	  ShString name)
{
  return cell->id() + name.hash() * 97;
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス CiCellPinHash
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellPinHash::CiCellPinHash() :
  mSize(0),
  mTable(nullptr),
  mLimit(0),
  mNum(0)
{
  alloc_table(1024);
}

// @brief デストラクタ
CiCellPinHash::~CiCellPinHash()
{
  delete [] mTable;
}

// @brief ピンを追加する．
// @param[in] pin 追加するピン
void
CiCellPinHash::add(CiCellPin* pin)
{
  if ( mNum > mLimit ) {
    // テーブルを拡張する．
    alloc_table(mSize * 2);
  }

  SizeType pos = hash_func(pin->mCell, pin->mName) % mSize;
  add_pin(pos, pin);
  ++ mNum;
}

// @brief ピンを取り出す．
// @param[in] cell セル
// @param[in] name 名前
// @return cell の name というピンのピン番号を返す．
//
// なければ -1 を返す．
int
CiCellPinHash::get(const CiCell* cell,
		   ShString name) const
{
  SizeType pos = hash_func(cell, name) % mSize;
  for ( CiCellPin* pin = mTable[pos]; pin; pin = pin->mLink ) {
    if ( pin->mCell == cell && pin->mName == name ) {
      return pin->mId;
    }
  }
  return -1;
}

// @brief テーブルの領域を確保する．
// @param[in] req_size 要求するサイズ
void
CiCellPinHash::alloc_table(ymuint64 req_size)
{
  SizeType old_size = mSize;
  CiCellPin** old_table = mTable;
  mSize = req_size;
  mLimit = static_cast<SizeType>(mSize * 1.8);
  mTable = new CiCellPin*[mSize];
  for ( SizeType i = 0; i < mSize; ++ i ) {
    mTable[i] = nullptr;
  }

  for ( SizeType i = 0; i < old_size; ++ i ) {
    for ( CiCellPin* pin = old_table[i]; pin; ) {
      CiCellPin* tmp = pin;
      pin = pin->mLink;
      SizeType pos = hash_func(tmp->mCell, tmp->mName) % mSize;
      add_pin(pos, tmp);
    }
  }
  delete [] old_table;
}

// @brief 要素をリンクに追加する．
// @param[in] pos 追加する位置
// @param[in] pin 追加する要素
inline
void
CiCellPinHash::add_pin(SizeType pos,
		       CiCellPin* pin)
{
  pin->mLink = mTable[pos];
  mTable[pos] = pin;
}

END_NAMESPACE_YM_CLIB
