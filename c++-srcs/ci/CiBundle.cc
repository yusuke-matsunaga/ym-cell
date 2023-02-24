
/// @file CiBundle.cc
/// @brief CiBundle の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiBundle.h"
#include "ym/BinEnc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBundle
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiBundle::dump(
  BinEnc& s
) const
{
  s << mName;
  s << pin_num();
  for ( auto pin: mPinList ) {
    s << pin->name();
  }
}

END_NAMESPACE_YM_CLIB
