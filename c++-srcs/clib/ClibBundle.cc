
/// @file ClibBundle.cc
/// @brief ClibBundle の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibBundle.h"
#include "ym/ClibPin.h"
#include "ci/CiBundle.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibBundle
//////////////////////////////////////////////////////////////////////

// @brief 名前の取得
string
ClibBundle::name() const
{
  ASSERT_COND( is_valid() );
  auto bundle = mLibrary->_bundle(mId);
  return bundle->name();
}

// @brief ピン数の取得
SizeType
ClibBundle::pin_num() const
{
  ASSERT_COND( is_valid() );
  auto bundle = mLibrary->_bundle(mId);
  return bundle->pin_num();
}

// @brief ピンの取得
ClibPin
ClibBundle::pin(
  SizeType pos
) const
{
  ASSERT_COND( is_valid() );
  auto bundle = mLibrary->_bundle(mId);
  SizeType id = bundle->pin(pos);
  return ClibPin{mLibrary, id};
}

// @brief ピンのリストの取得
ClibPinList
ClibBundle::pin_list() const
{
  ASSERT_COND( is_valid() );
  auto bundle = mLibrary->_bundle(mId);
  auto& id_list = bundle->pin_list();
  return ClibPinList{mLibrary, id_list};
}

END_NAMESPACE_YM_CLIB
