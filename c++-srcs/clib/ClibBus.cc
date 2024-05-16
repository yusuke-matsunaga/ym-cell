
/// @file ClibBus.cc
/// @brief ClibBus の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibBus.h"
#include "ym/ClibBusType.h"
#include "ym/ClibPin.h"
#include "ci/CiBus.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibBus
//////////////////////////////////////////////////////////////////////

// @brief 内容を指定したコンストラクタ
ClibBus::ClibBus(
  const CiBus* impl
) : ClibHandle<CiBus>{impl}
{
}

// @brief デストラクタ
ClibBus::~ClibBus()
{
}

// @brief 名前の取得
string
ClibBus::name() const
{
  _check_valid();
  return mImpl->name();
}

// @brief バスの型の取得
ClibBusType
ClibBus::bus_type() const
{
  _check_valid();
  auto bus_type = mImpl->bus_type();
  return ClibBusType{bus_type};
}

// @brief ピン数の取得
SizeType
ClibBus::pin_num() const
{
  _check_valid();
  return mImpl->pin_num();
}

// @brief ピンの取得
ClibPin
ClibBus::pin(
  SizeType pos
) const
{
  _check_valid();
  auto pin = mImpl->pin(pos);
  return ClibPin{pin};
}

// @brief ピンのリストの取得
ClibPinList
ClibBus::pin_list() const
{
  _check_valid();
  auto& pin_list = mImpl->pin_list();
  return ClibPinList{pin_list};
}

END_NAMESPACE_YM_CLIB
