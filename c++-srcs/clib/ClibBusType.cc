
/// @file ClibBusType.cc
/// @brief ClibBusType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibBusType.h"
#include "ci/CiBusType.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibBusType
//////////////////////////////////////////////////////////////////////

// @brief 名前の取得
string
ClibBusType::name() const
{
  _check_valid();
  auto bustype = mLibrary->_bustype(mId);
  return bustype->name();
}

// @brief base_type の取得
ClibBusType::BaseType
ClibBusType::base_type() const
{
  _check_valid();
  auto bustype = mLibrary->_bustype(mId);
  return bustype->base_type();
}

// @brief data_type の取得
ClibBusType::DataType
ClibBusType::data_type() const
{
  _check_valid();
  auto bustype = mLibrary->_bustype(mId);
  return bustype->data_type();
}

// @brief ビット幅の取得
SizeType
ClibBusType::bit_width() const
{
  _check_valid();
  auto bustype = mLibrary->_bustype(mId);
  return bustype->bit_width();
}

// @brief 開始ビットの取得
SizeType
ClibBusType::bit_from() const
{
  _check_valid();
  auto bustype = mLibrary->_bustype(mId);
  return bustype->bit_from();
}

// @brief 終了ビットの取得
SizeType
ClibBusType::bit_to() const
{
  _check_valid();
  auto bustype = mLibrary->_bustype(mId);
  return bustype->bit_to();
}

/// @brief 向きの取得
bool
ClibBusType::downto() const
{
  _check_valid();
  auto bustype = mLibrary->_bustype(mId);
  return bustype->downto();
}

END_NAMESPACE_YM_CLIB
