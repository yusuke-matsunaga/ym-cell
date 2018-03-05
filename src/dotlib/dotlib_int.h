#ifndef DOTLIB_INT_H
#define DOTLIB_INT_H

/// @file dotlib_int.h
/// @brief dotlib サブモジュールの内部定義ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"


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

  /// @brief VDD
  SYMBOL_VDD,
  /// @brief VSS
  SYMBOL_VSS,
  /// @brief VCC
  SYMBOL_VCC,
};

/// @brief 属性を表す列挙型
enum AttrType {
  ATTR_LIBRARY,

  ATTR_TECHNOLOGY,
  ATTR_DELAY_MODEL,
  ATTR_BUS_NAMING_STYLE,
  ATTR_COMMENT,
  ATTR_DATE,
  ATTR_REVISION,
  ATTR_CURRENT_UNIT,
  ATTR_LEAKAGE_POWER_UNIT,
  ATTR_PULLING_RESISTANCE_UNIT,
  ATTR_CAPACITIVE_LOAD_UNIT,
  ATTR_TIME_UNIT,
  ATTR_VOLTAGE_UNIT,

  ATTR_LU_TABLE_TEMPLATE,
  ATTR_VARIABLE_1,
  ATTR_VARIABLE_2,
  ATTR_VARIABLE_3,
  ATTR_INDEX_1,
  ATTR_INDEX_2,
  ATTR_INDEX_3,
  ATTR_VALUES,

  ATTR_CELL,

  ATTR_PIN,
  ATTR_BUS,
  ATTR_BUNDLE,

  ATTR_AREA,
  ATTR_FF,
  ATTR_LATCH,
  ATTR_STATETABLE,

  ATTR_CLEAR,
  ATTR_PRESET,
  ATTR_CLEAR_PRESET_VAR1,
  ATTR_CLEAR_PRESET_VAR2,

  ATTR_NEXTSTATE,
  ATTR_CLOCKED_ON,
  ATTR_CLOCKED_ON_ALSO,

  ATTR_DATA_IN,
  ATTR_ENABLE,
  ATTR_ENABLE_ALSO,

  ATTR_TIMING,
  ATTR_DIRECTION,
  ATTR_CAPACITANCE,
  ATTR_RISE_CAPACITANCE,
  ATTR_FALL_CAPACITANCE,
  ATTR_MAX_FANOUT,
  ATTR_MIN_FANOUT,
  ATTR_MAX_CAPACITANCE,
  ATTR_MIN_CAPACITANCE,
  ATTR_MAX_TRANSITION,
  ATTR_MIN_TRANSITION,
  ATTR_FUNCTION,
  ATTR_THREE_STATE,
  ATTR_INTERNAL_NODE,
  ATTR_PIN_FUNC_TYPE,

  ATTR_RELATED_PIN,
  ATTR_RELATED_BUS_PINS,
  ATTR_RELATED_BUS_EQUIVALENT,
  ATTR_TIMING_SENSE,
  ATTR_TIMING_TYPE,
  ATTR_WHEN,
  ATTR_WHEN_START,
  ATTR_WHEN_END,
  ATTR_RISE_RESISTANCE,
  ATTR_FALL_RESISTANCE,
  ATTR_INTRINSIC_RISE,
  ATTR_INTRINSIC_FALL,
  ATTR_SLOPE_RISE,
  ATTR_SLOPE_FALL,
  ATTR_RISE_DELAY_INTERCEPT,
  ATTR_FALL_DELAY_INTERCEPT,
  ATTR_RISE_PIN_RESISTANCE,
  ATTR_FALL_PIN_RESISTANCE,
  ATTR_CELL_DEGRADATION,
  ATTR_CELL_RISE,
  ATTR_CELL_FALL,
  ATTR_RISE_CONSTRAINT,
  ATTR_FALL_CONSTRAINT,
  ATTR_RISE_PROPAGATION,
  ATTR_FALL_PROPAGATION,
  ATTR_RISE_TRANSITION,
  ATTR_FALL_TRANSITION,
  ATTR_RETAINING_RISE,
  ATTR_RETAINING_FALL,
  ATTR_RETAIN_RISE_SLEW,
  ATTR_RETAIN_FALL_SLEW,
};

/// @brief TokenType 内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   TokenType type);

/// @brief AttrType の内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   AttrType attr);


// クラス名の前方宣言
class DotlibParserImpl;
class DotlibHandler;
class GroupHandler;
class DotlibMgrImpl;
class DotlibNodeImpl;

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_INT_H
