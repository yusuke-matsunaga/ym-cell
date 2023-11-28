
/// @file ClibCellClass.cc
/// @brief ClibCellClass の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellClass.h"
#include "ym/ClibCellGroup.h"
#include "ci/CiCellClass.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibCellClass
//////////////////////////////////////////////////////////////////////

// @brief 同位体変換の個数を得る．
SizeType
ClibCellClass::idmap_num() const
{
  _check_valid();
  auto cc = mLibrary->_cell_class(mId);
  return cc->idmap_num();
}

// @brief 同位体変換を得る．
const ClibIOMap&
ClibCellClass::idmap(
  SizeType pos
) const
{
  _check_valid();
  auto cc = mLibrary->_cell_class(mId);
  return cc->idmap(pos);
}

// @brief 同位体変換のリストを得る．
const vector<ClibIOMap>&
ClibCellClass::idmap_list() const
{
  _check_valid();
  auto cc = mLibrary->_cell_class(mId);
  return cc->idmap_list();
}

// @brief グループ数を返す．
SizeType
ClibCellClass::cell_group_num() const
{
  _check_valid();
  auto cc = mLibrary->_cell_class(mId);
  return cc->cell_group_num();
}

// @brief グループを返す．
ClibCellGroup
ClibCellClass::cell_group(
  SizeType pos
) const
{
  _check_valid();
  auto cc = mLibrary->_cell_class(mId);
  SizeType id = cc->cell_group(pos);
  return ClibCellGroup{mLibrary, id};
}

// @brief グループのリストを返す．
ClibCellGroupList
ClibCellClass::cell_group_list() const
{
  _check_valid();
  auto cc = mLibrary->_cell_class(mId);
  return ClibCellGroupList{mLibrary, cc->cell_group_list()};
}

END_NAMESPACE_YM_CLIB
