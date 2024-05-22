
/// @file CiCellClass.cc
/// @brief CiCellClass の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellClass.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

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
  auto ptr = unique_ptr<CiCellClass>{new CiCellClass{lib, idmap_list}};
  return ptr;
}

END_NAMESPACE_YM_CLIB
