
/// @file CiCellGroup.cc
/// @brief CiCellGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellGroup.h"
#include "ci/CiCell.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief 内容をシリアライズする．
void
CiCellGroup::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiCellGroup::dump(
  Serializer& s
) const
{
  s.dump(mIoMap);
  s.dump(mCellList);
}

// @brief 内容を読み込む．
unique_ptr<CiCellGroup>
CiCellGroup::restore(
  Deserializer& s
)
{
  auto ptr = unique_ptr<CiCellGroup>{new CiCellGroup};
  ptr->_restore(s);
  return ptr;
}

// @brief restore() の本体
void
CiCellGroup::_restore(
  Deserializer& s
)
{
  s.restore(mIoMap);
  vector<CiCell*> cell_list;
  s.restore(cell_list);
  for ( auto cell: cell_list ) {
    add_cell(cell);
    cell->set_group(this);
  }
}

END_NAMESPACE_YM_CLIB
