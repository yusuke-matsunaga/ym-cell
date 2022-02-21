
/// @file CiBus.cc
/// @brief CiBus の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiBus.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBus
//////////////////////////////////////////////////////////////////////

// @brief 名前の取得
string
CiBus::name() const
{
  return mName;
}

// @brief バスの型の取得
const ClibBusType&
CiBus::bus_type() const
{
  return *mBusType;
}

// @brief ピン数の取得
SizeType
CiBus::pin_num() const
{
  return mPinList.size();
}

// @brief ピンの取得
const ClibPin&
CiBus::pin(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < pin_num() );
  return *mPinList[pos];
}

END_NAMESPACE_YM_CLIB
