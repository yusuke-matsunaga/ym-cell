﻿
/// @file CiBusType.cc
/// @brief CiBusType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "CiBusType.h"


BEGIN_NAMESPACE_YM_CELL

//////////////////////////////////////////////////////////////////////
// クラス CiBusType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] name 名前
// @param[in] bit_from 開始位置
// @param[in] bit_to 終了位置
CiBusType::CiBusType(ShString name,
		     ymint bit_from,
		     ymint bit_to) :
  mName(name),
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

// @brief デストラクタ
CiBusType::~CiBusType()
{
}

// @brief 名前の取得
string
CiBusType::name() const
{
  return mName;
}

// @brief base_type の取得
CellBusType::tBaseType
CiBusType::base_type() const
{
  return kArrayType;
}

// @brief data_type の取得
CellBusType::tDataType
CiBusType::data_type() const
{
  return kBitType;
}

// @brief ビット幅の取得
ymuint
CiBusType::bit_width() const
{
  return mBitWidth;
}

// @brief 開始ビットの取得
ymint
CiBusType::bit_from() const
{
  return mBitFrom;
}

// @brief 終了ビットの取得
ymint
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

END_NAMESPACE_YM_CELL
