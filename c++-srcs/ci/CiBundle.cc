
/// @file CiBundle.cc
/// @brief CiBundle の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiBundle.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBundle
//////////////////////////////////////////////////////////////////////

// @brief 名前の取得
string
CiBundle::name() const
{
  return mName;
}

// @brief ピン数の取得
SizeType
CiBundle::pin_num() const
{
  return mPinList.size();
}

// @brief ピンの取得
const ClibPin&
CiBundle::pin(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < pin_num() );
  return *mPinList[pos];
}

END_NAMESPACE_YM_CLIB
