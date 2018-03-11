﻿#ifndef DOTLIB_NSDEF_H
#define DOTLIB_NSDEF_H

/// @file dotlib_nsdef.h
/// @brief dotlib サブモジュールの定義ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"


//////////////////////////////////////////////////////////////////////
// 名前空間を定義するためのマクロ
//////////////////////////////////////////////////////////////////////

/// @brief dotlib の名前空間の開始
#define BEGIN_NAMESPACE_YM_DOTLIB \
BEGIN_NAMESPACE_YM_CLIB \
BEGIN_NAMESPACE(nsDotlib)

/// @brief dotlib の名前空間の終了
#define END_NAMESPACE_YM_DOTLIB \
END_NAMESPACE(nsDotlib) \
END_NAMESPACE_YM_CLIB


BEGIN_NAMESPACE_YM_DOTLIB

// クラス名の前方宣言
class DotlibAttr;
class DotlibAttrMap;
class DotlibMgr;
class DotlibParser;
class DotlibNode;
class DotlibLibrary;
class DotlibList;
class DotlibCell;
class DotlibFL;
class DotlibFF;
class DotlibLatch;
class DotlibTemplate;
class DotlibLut;
class DotlibInt;
class DotlibFloat;
class DotlibFloatVector;
class DotlibExpr;
class DotlibStateTable;
class DotlibString;
class DotlibPin;
class DotlibBus;
class DotlibBundle;
class DotlibTiming;
class DotlibTechnology;
class DotlibPinDirection;
class DotlibDelayModel;
class DotlibTimingSense;
class DotlibTimingType;
class DotlibVarType;

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_NSDEF_H
