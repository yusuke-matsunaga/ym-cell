
/// @file CiCellClass.cc
/// @brief CiCellClass の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellClass.h"
#include "ym/ClibIOMap.h"
#include "ym/BinEnc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellClass
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiCellClass::dump(
  BinEnc& s
) const
{
  // 同位体変換情報のダンプ
  s << idmap_num();
  for ( auto& map: idmap_list() ) {
    map.dump(s);
  }
  // グループ情報のダンプ
  s << cell_group_num();
  for ( auto id: cell_group_list() ) {
    s << id;
  }
}

END_NAMESPACE_YM_CLIB
