#ifndef CLIBCELLGROUPLIST_H
#define CLIBCELLGROUPLIST_H

/// @file ClibCellGroupList.h
/// @brief ClibCellGroupList のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibObjList.h"


BEGIN_NAMESPACE_YM_CLIB

class ClibCellGroup;

END_NAMESPACE_YM_CLIB

BEGIN_NAMESPACE_YM

using ClibCellGroupList = nsClib::ClibObjList<ClibCellGroup>;

END_NAMESPACE_YM

#endif // CLIBCELLGROUPLIST_H
