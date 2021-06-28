﻿#ifndef DOTLIB_TOKENtype_H
#define DOTLIB_TOKENtype_H

/// @file TokenType.h
/// @brief TokenType の定義ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"


BEGIN_NAMESPACE_YM_DOTLIB

/// @brief トークンの値
/// 基本的には dotlib のシンタックスにしたがっているが，
/// 一部，function 属性の文字列の中身をパーズする時のみ現れるシンボルがある．
/// AND, OR, XOR, PRIME がそれ．
enum class TokenType {
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
  /// @brief ブール値0
  BOOL_0,
  /// @brief ブール値1
  BOOL_1,
  /// @brief 式
  EXPRESSION,
  /// @brief 改行
  NL,

  /// @brief エラー
  ERROR,
  /// @brief ファイルの末尾
  END,
};

/// @brief TokenType 内容をストリームに出力する．
ostream&
operator<<(ostream& s,      ///< [in] 出力先のストリーム
	   TokenType type); ///< [in] トークンタイプ

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_TOKENtype_H
