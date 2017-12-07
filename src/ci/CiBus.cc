
/// @file CiBus.cc
/// @brief CiBus の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiBus.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBus
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiBus::CiBus() :
  mBusType(nullptr),
  mPinNum(0),
  mPinList(nullptr)
{
}

// @brief デストラクタ
CiBus::~CiBus()
{
  // メモリ管理は他のクラスが行っている．
}

// @brief 名前の取得
string
CiBus::name() const
{
  return mName;
}

// @brief バスの型の取得
const ClibBusType*
CiBus::bus_type() const
{
  return mBusType;
}

// @brief ピン数の取得
ymuint
CiBus::pin_num() const
{
  return mPinNum;
}

// @brief ピンの取得
// @param[in] pos 位置番号 ( 0 <= pos < pin_num() )
const ClibCellPin*
CiBus::pin(ymuint pos) const
{
  return mPinList[pos];
}

END_NAMESPACE_YM_CLIB
