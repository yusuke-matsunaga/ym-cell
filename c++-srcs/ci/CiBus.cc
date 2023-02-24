
/// @file CiBus.cc
/// @brief CiBus の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiBus.h"
#include "ym/BinEnc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiBus
//////////////////////////////////////////////////////////////////////

// @brief 内容をバイナリダンプする．
void
CiBus::dump(
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
