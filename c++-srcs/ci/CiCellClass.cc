
/// @file CiCellClass.cc
/// @brief CiCellClass の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellClass.h"
#include "ci/CiCellGroup.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiCellClass::CiCellClass(
  CiCellLibrary* lib,
  const vector<ClibIOMap>& idmap_list,
  const vector<const CiCellGroup*>& group_list
) : CiLibObj{lib},
    mIdMapList{idmap_list},
    mGroupList{group_list}
{
#if 0
  for ( auto group: mGroupList ) {
    group->mRepClass = this;
  }
#endif
}

// @brief このクラスに属しているセルグループを追加する．
void
CiCellClass::add_group(
  const CiCellGroup* group
)
{
  mGroupList.push_back(group);
  //group->mRepClass = this;
}

// @brief 内容をシリアライズする．
void
CiCellClass::serialize(
  Serializer& s
) const
{
  s.reg_obj(this);
}

// @brief 内容をバイナリダンプする．
void
CiCellClass::dump(
  Serializer& s
) const
{
  // 同位体変換情報のダンプ
  s.dump(idmap_num());
  for ( auto& map: idmap_list() ) {
    map.dump(s.out());
  }
  // セルグループのダンプ
  s.dump(cell_group_list());
}

// @brief 内容を読み込む．
unique_ptr<CiCellClass>
CiCellClass::restore(
  Deserializer& s,
  CiCellLibrary* lib
)
{
  SizeType n = s.in().read_64();
  vector<ClibIOMap> idmap_list(n);
  for ( auto i: Range(n) ) {
    idmap_list[i].restore(s.in());
  }
  vector<const CiCellGroup*> group_list;
  s.restore(group_list);
  auto ptr = unique_ptr<CiCellClass>{new CiCellClass{lib, idmap_list, group_list}};
  return ptr;
}

END_NAMESPACE_YM_CLIB
