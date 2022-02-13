#ifndef CLIBCELLCLASSLIST_H
#define CLIBCELLCLASSLIST_H

/// @file ClibCellClassList.h
/// @brief ClibCellClassList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibObjList.h"


BEGIN_NAMESPACE_YM_CLIB

class ClibCellClass;

END_NAMESPACE_YM_CLIB

BEGIN_NAMESPACE_YM

using ClibCellClassList = nsClib::ClibObjList<ClibCellClass>;

END_NAMESPACE_YM

#endif // CLIBCELLCLASSLIST_H
