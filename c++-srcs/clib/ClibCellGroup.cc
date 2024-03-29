
/// @file ClibCellGroup.cc
/// @brief ClibCellGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellGroup.h"
#include "ym/ClibCell.h"
#include "ci/CiCellGroup.h"
#include "ci/CiCellClass.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibCellGroup
//////////////////////////////////////////////////////////////////////

// @brief 代表クラスを返す．
ClibCellClass
ClibCellGroup::rep_class() const
{
  _check_valid();
  auto cg = mLibrary->_cell_group(mId);
  SizeType id = cg->rep_class();
  return ClibCellClass{mLibrary, id};
}

// @brief 代表クラスに対する変換マップを返す．
const ClibIOMap&
ClibCellGroup::iomap() const
{
  _check_valid();
  auto cg = mLibrary->_cell_group(mId);
  return cg->iomap();
}

// @brief セル数を返す．
SizeType
ClibCellGroup::cell_num() const
{
  _check_valid();
  auto cg = mLibrary->_cell_group(mId);
  return cg->cell_num();
}

// @brief セルを返す．
ClibCell
ClibCellGroup::cell(
  SizeType pos
) const
{
  _check_valid();
  auto cg = mLibrary->_cell_group(mId);
  SizeType id = cg->cell(pos);
  return ClibCell{mLibrary, id};
}

// @brief セルのリストを返す．
ClibCellList
ClibCellGroup::cell_list() const
{
  _check_valid();
  auto cg = mLibrary->_cell_group(mId);
  return ClibCellList{mLibrary, cg->cell_list()};
}

END_NAMESPACE_YM_CLIB
