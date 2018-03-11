#ifndef DOTLIBBASE_H
#define DOTLIBBASE_H

/// @file DotlibBase.h
/// @brief DotlibNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "ym/FileRegion.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ファイル上の位置を返す．
inline
FileRegion
DotlibBase::loc() const
{
  return mLoc;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBBASE_H
