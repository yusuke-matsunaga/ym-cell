
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
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibBus
//////////////////////////////////////////////////////////////////////

// @brief 名前の取得
string
ClibBus::name() const
{
  _check_valid();
  auto bus = mLibrary->_bus(mId);
  return bus->name();
}

// @brief バスの型の取得
ClibBusType
ClibBus::bus_type() const
{
  _check_valid();
  auto bus = mLibrary->_bus(mId);
  SizeType id = bus->bus_type();
  return ClibBusType{mLibrary, id};
}

// @brief ピン数の取得
SizeType
ClibBus::pin_num() const
{
  _check_valid();
  auto bus = mLibrary->_bus(mId);
  return bus->pin_num();
}

// @brief ピンの取得
ClibPin
ClibBus::pin(
  SizeType pos
) const
{
  _check_valid();
  auto bus = mLibrary->_bus(mId);
  SizeType pin_id = bus->pin(pos);
  return ClibPin{mLibrary, pin_id};
}

// @brief ピンのリストの取得
ClibPinList
ClibBus::pin_list() const
{
  _check_valid();
  auto bus = mLibrary->_bus(mId);
  auto& id_list = bus->pin_list();
  return ClibPinList{mLibrary, id_list};
}

END_NAMESPACE_YM_CLIB
