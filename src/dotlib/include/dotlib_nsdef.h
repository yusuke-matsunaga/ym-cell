#ifndef DOTLIB_NSDEF_H
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
class DotlibParser;
class DotlibHandler;
class AstMgr;
class AstAttr;
class AstNode;
class AstLibrary;
class AstCell;
class AstFL;
class AstFF;
class AstLatch;
class AstTemplate;
class AstLut;
class AstInt;
class AstFloat;
class AstFloatVector;
class AstExpr;
class AstStateTable;
class AstString;
class AstPin;
class AstBus;
class AstBundle;
class AstTiming;
class AstInputVoltage;
class AstOutputVoltage;
class AstGenGroup;
class AstTechnology;
class AstPieceWise;
class AstPinDirection;
class AstDelayModel;
class AstTimingSense;
class AstTimingType;
class AstUnit;
class AstVarType;

class GroupHandler;

enum class TokenType;
enum class AttrType;

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_NSDEF_H
