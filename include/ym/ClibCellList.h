#ifndef CLIBCELLLIST_H
#define CLIBCELLLIST_H

/// @file ClibCellList.h
/// @brief ClibCellList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibObjList.h"


BEGIN_NAMESPACE_YM_CLIB

class ClibCell;

END_NAMESPACE_YM_CLIB

BEGIN_NAMESPACE_YM

using ClibCellList = nsClib::ClibObjList<ClibCell>;

END_NAMESPACE_YM

#endif // CLIBCELLLIST_H
