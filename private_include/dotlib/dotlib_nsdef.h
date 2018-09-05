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
class SimpleHandler;
class ComplexHandler;
class GroupHandler;
class CGHandler;

class AstMgr;
class AstAttr;
class AstBool;
class AstBus;
class AstBundle;
class AstCell;
class AstCellType;
class AstDelayModel;
class AstDynamicCurrent;
class AstExpr;
class AstFloat;
class AstFloatVector;
class AstFF;
class AstFFBank;
class AstFYM;
class AstGeneratedClock;
class AstInputVoltage;
class AstInt;
class AstIntrinsicParasitic;
class AstLatch;
class AstLatchBank;
class AstLeakageCurrent;
class AstLeakagePower;
class AstLibrary;
class AstLut;
class AstMode;
class AstNode;
class AstOutputVoltage;
class AstPieceWise;
class AstPin;
class AstPinDirection;
class AstRoutingTrack;
class AstStateTable;
class AstString;
class AstTechnology;
class AstTemplate;
class AstTestCell;
class AstTiming;
class AstTimingSense;
class AstTimingType;
class AstType;
class AstUnit;
class AstVarType;


enum class TokenType;
enum class AttrType;

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_NSDEF_H
