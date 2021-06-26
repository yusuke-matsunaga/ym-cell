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
class Parser;
class Scanner;

class AstAttr;
class AstExpr;
class AstValue;

class Token;
class AttrKwd;

enum class TokenType;

// AstXXX の unique_ptr
using AstExprPtr = unique_ptr<const AstExpr>;
using AstValuePtr = unique_ptr<const AstValue>;
using AstAttrPtr = unique_ptr<const AstAttr>;

// simple attribute を読み込む関数の型定義
using SimpleHandler = std::function<AstValuePtr(Scanner&)>;

// group statement の要素を読み込む関数の型定義
using AttrHandler = std::function<AstAttrPtr(Parser&, const AttrKwd&)>;


//////////////////////////////////////////////////////////////////////
// エラー出力用の便利関数
//////////////////////////////////////////////////////////////////////

// @brief 未対応の属性名に対するエラーメッセージを出力する．
extern
void
syntax_error(const AttrKwd& attr); ///< [in] 対象の属性

/// @brief 同じ属性が重複して定義されている時のエラーを出力する．
extern
void
duplicate_error(const AttrKwd& attr,       ///< [in] 属性の型
		const AstAttr* prev_attr); ///< [in] 以前に定義された属性

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIB_NSDEF_H
