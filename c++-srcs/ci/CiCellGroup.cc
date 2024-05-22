
/// @file CiCellGroup.cc
/// @brief CiCellGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellGroup.h"
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
  mIoMap.dump(s.out());
  s.dump(mCellList);
}

// @brief 内容を読み込む．
unique_ptr<CiCellGroup>
CiCellGroup::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  //CiCellClass* rep_class;
  //s.restore(rep_class);
  ClibIOMap iomap;
  iomap.restore(s.in());
  vector<const CiCell*> cell_list;
  s.restore(cell_list);
  auto ptr = unique_ptr<CiCellGroup>{new CiCellGroup{lib, iomap, cell_list}};
  return ptr;
}

END_NAMESPACE_YM_CLIB
