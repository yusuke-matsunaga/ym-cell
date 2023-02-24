
/// @file CiCellGroup.cc
/// @brief CiCellGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellGroup.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellGroup
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiCellGroup::dump(
  BinEnc& s
) const
{
  s << mRepClass;
  mIoMap.dump(s);
  s << cell_num();
  for ( auto id: mCellList ) {
    s << id;
  }
}

END_NAMESPACE_YM_CLIB
