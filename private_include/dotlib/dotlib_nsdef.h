#ifndef DOTLIB_NSDEF_H
#define DOTLIB_NSDEF_H

/// @file dotlib_nsdef.h
/// @brief dotlib サブモジュールの定義ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
#include "ym/FileRegion.h"


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
class AstDomain;
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
class AstVariableRange;
class AstVarType;


enum class TokenType;
enum class AttrType;


//////////////////////////////////////////////////////////////////////
// エラー出力用の便利関数
//////////////////////////////////////////////////////////////////////

// @brief 未対応の属性名に対するエラーメッセージを出力する．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
void
syntax_error(AttrType attr_type,
	     const FileRegion& attr_loc);

/// @brief 同じ属性が重複して定義されている時のエラーを出力する．
/// @param[in] attr_type 属性の型
/// @param[in] attr_loc 属性のファイル上の位置
/// @param[in] prev_node 以前に定義されたノード
void
duplicate_error(AttrType attr_type,
		const FileRegion& attr_loc,
		const AstNode* prev_node);

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_NSDEF_H
