#ifndef DOTLIB_NSDEF_H
#define DOTLIB_NSDEF_H

/// @file dotlib_nsdef.h
/// @brief dotlib サブモジュールの定義ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
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
class HeaderHandler;
class GroupHandler;

class FloatFloatHandler;
class FloatStrHandler;
class FloatVectorHandler;
class IntFloatHandler;
class IntFloatVectorHandler;
class IntVectorHandler;
class StrFloatHandler;
class StrHandler;
class StrIntHandler;
class StrListHandler;
class StrStrHandler;
class StrStrIntHandler;
class StrStrStrHandler;

class CellHandler;
class DomainHandler;
class FFHandler;
class FLHandler;
class InputVoltageHandler;
class LatchHandler;
class LibraryHandler;
class OutputVoltageHandler;
class PinHandler;
class TableHandler;
class TemplateHandler;
class TimingHandler;

class AstMgr;
class AstAttr;
class AstBaseCurves;
class AstBus;
class AstBundle;
class AstCCS;
class AstCell;
class AstCellDegradation;
class AstCellType;
class AstClutTemplate;
class AstCPType;
class AstDomain;
class AstDynamicCurrent;
class AstExpr;
class AstFlutTemplate;
class AstFF;
class AstFFBank;
class AstFpgaIsd;
class AstFYM;
class AstGeneratedClock;
class AstInputVoltage;
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
class AstPart;
class AstPieceWise;
class AstPin;
class AstPolyTemplate;
class AstPowerSupply;
class AstRoutingTrack;
class AstScaledCell;
class AstScalingFactors;
class AstSensitization;
class AstStateTable;
class AstTemplate;
class AstTestCell;
class AstTiming;
class AstTimingRange;
class AstType;
class AstUnit;
class AstUserParameters;
class AstValue;
class AstVariableRange;
class AstWireLoad;
class AstWireLoadSelection;
class AstWireLoadTable;

enum class TokenType;
enum class AttrType;

class AstString;
class AstFloat;
class AstInt;
class AstTechnology;
class AstVarType;
class AstIntFloat;
class AstFloatVector;
class AstFloat2;
class AstDelayModel;
class AstIntVector;
class AstTimingSense;
class AstTimingType;
class AstFloatStr;
class AstDirection;

//////////////////////////////////////////////////////////////////////
// エラー出力用の便利関数
//////////////////////////////////////////////////////////////////////

// @brief 未対応の属性名に対するエラーメッセージを出力する．
extern
void
syntax_error(AttrType attr_type,          ///< [in] 対象の属性
	     const FileRegion& attr_loc); ///< [in] attr_type のファイル上の位置

/// @brief 同じ属性が重複して定義されている時のエラーを出力する．
extern
void
duplicate_error(AttrType attr_type,         ///< [in] 属性の型
		const FileRegion& attr_loc, ///< [in] 属性のファイル上の位置
		const AstNode* prev_node);  ///< [in] 以前に定義されたノード

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_NSDEF_H
