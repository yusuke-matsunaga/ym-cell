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

/// @brief トークンの値
/// 基本的には dotlib のシンタックスにしたがっているが，
/// 一部，function 属性の文字列の中身をパーズする時のみ現れるシンボルがある．
/// AND, OR, XOR, PRIME がそれ．
enum TokenType {
  /// @brief コロン(:)
  COLON,
  /// @brief セミコロン(;)
  SEMI,
  /// @brief コンマ(,)
  COMMA,
  /// @brief プラス(+)
  PLUS,
  /// @brief マイナス(-)
  MINUS,
  /// @brief かける(*)
  MULT,
  /// @brief わる(/)
  DIV,
  /// @brief NOT
  NOT,
  /// @brief AND
  AND,
  /// @brief OR
  OR,
  /// @brief XOR
  XOR,
  /// @brief 左括弧( ( )
  LP,
  /// @brief 右括弧( ) )
  RP,
  /// @brief 左中括弧( { )
  LCB,
  /// @brief 右中括弧( } )
  RCB,
  /// @brief プライム( ' )
  PRIME,
  /// @brief シンボル
  SYMBOL,
  /// @brief 整数値
  INT_NUM,
  /// @brief 浮動小数点数値
  FLOAT_NUM,
  /// @brief 式
  EXPRESSION,
  /// @brief 改行
  NL,

  /// @brief 属性
  ATTR,

  /// @brief エラー
  ERROR,
  /// @brief ファイルの末尾
  END,
};

/// @brief TokenType 内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   TokenType type);

// クラス名の前方宣言
class DotlibAttr;
class DotlibAttrMap;
class DotlibMgr;
class DotlibMgrImpl;
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
