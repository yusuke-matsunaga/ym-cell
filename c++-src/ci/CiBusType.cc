
/// @file CiBusType.cc
/// @brief CiBusType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiBusType.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBusType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiBusType::CiBusType(
  const ShString& name,
  int bit_from,
  int bit_to
) : mName(name),
    mBitFrom(bit_from),
    mBitTo(bit_to)
{
  if ( bit_from <= bit_to ) {
    mBitWidth = bit_to - bit_from + 1;
    mDownTo = false;
  }
  else {
    mBitWidth = bit_from - bit_to + 1;
    mDownTo = true;
  }
}

// @brief 名前の取得
string
CiBusType::name() const
{
  return mName;
}

// @brief base_type の取得
ClibBusType::BaseType
CiBusType::base_type() const
{
  return ClibBusType::ArrayType;
}

// @brief data_type の取得
ClibBusType::DataType
CiBusType::data_type() const
{
  return ClibBusType::BitType;
}

// @brief ビット幅の取得
int
CiBusType::bit_width() const
{
  return mBitWidth;
}

// @brief 開始ビットの取得
int
CiBusType::bit_from() const
{
  return mBitFrom;
}

// @brief 終了ビットの取得
int
CiBusType::bit_to() const
{
  return mBitTo;
}

// @brief 向きの取得
// @note true の時，降順を表す．
bool
CiBusType::downto() const
{
  return mDownTo;
}

END_NAMESPACE_YM_CLIB
