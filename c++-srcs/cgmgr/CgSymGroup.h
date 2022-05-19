#ifndef CGSYMGROUP_H
#define CGSYMGROUP_H

/// @file CgSymGroup.h
/// @brief CgSymGroup のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

/// @brief 対称な入力を表す構造体
struct CgSymGroup
{
  /// @brief ID番号のリスト
  vector<SizeType> mIdList;
  /// @brief bisym フラグ
  bool mBiSym;
};

END_NAMESPACE_YM_CLIB

#endif // CGSYMGROUP_H
