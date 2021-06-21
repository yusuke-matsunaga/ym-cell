
/// @file FuncParser.cc
/// @brief FuncParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "FuncParser.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstValue.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FuncParser
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] str 対象の文字列
// @param[in] loc ファイル上の位置
FuncParser::FuncParser(const string& str,
		       const FileRegion& loc)
  : mScanner(str, loc)
{
}

// @brief デストラクタ
FuncParser::~FuncParser()
{
}

// @brief 論理式を読み込む．
AstValuePtr
FuncParser::operator()()
{
  auto expr{read_expr(TokenType::END)};
  if ( expr == nullptr ) {
    return {};
  }

  return AstValue::new_expr(std::move(expr));
}

// @brief primary を読み込む．
AstExprPtr
FuncParser::read_primary()
{
  FileRegion loc;
  TokenType type = mScanner.read_token(loc);
  if ( type == TokenType::LP ) {
    return read_expr(TokenType::RP);
  }
  if ( type == TokenType::SYMBOL ) {
    ShString name(mScanner.cur_string());
    return AstExpr::new_string(name, loc);
  }
  if ( type == TokenType::INT_NUM ) {
    int v = mScanner.cur_int();
    if ( v != 0 && v != 1 ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. 0 or 1 is expected.");
      return nullptr;
    }
    return AstExpr::new_bool(static_cast<bool>(v), loc);
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. number is expected.");
  return {};
}

// @brief プライム付きの primary を読み込む．
AstExprPtr
FuncParser::read_primary2()
{
  FileRegion loc;
  TokenType type = mScanner.peek_token(loc);
  if ( type == TokenType::NOT ) {
    mScanner.accept_token();
    auto opr{read_primary()};
    if ( opr == nullptr ) {
      return {};
    }
    return AstExpr::new_not(std::move(opr), opr->loc());
  }

  auto expr{read_primary()};
  if ( expr == nullptr ) {
    return {};
  }

  type = mScanner.peek_token(loc);
  if ( type == TokenType::PRIME ) {
    mScanner.accept_token();
    return AstExpr::new_not(std::move(expr), loc);
  }

  return expr;
}

// @brief product を読み込む．
AstExprPtr
FuncParser::read_product()
{
  auto opr1{read_primary2()};
  if ( opr1 == nullptr ) {
    return {};
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = mScanner.peek_token(loc);
    if ( type == TokenType::AND ) {
      mScanner.accept_token();
      auto opr2{read_primary2()};
      if ( opr2 == nullptr ) {
	return {};
      }
      opr1 = AstExpr::new_and(std::move(opr1), std::move(opr2), loc);
    }
    else if ( type == TokenType::NOT || type == TokenType::LP || type == TokenType::SYMBOL ) {
      auto opr2{read_primary2()};
      if ( opr2 == nullptr ) {
	return {};
      }
      opr1 = AstExpr::new_and(std::move(opr1), std::move(opr2), loc);
    }
    else {
      return opr1;
    }
  }
}

// @brief expression を読み込む．
AstExprPtr
FuncParser::read_expr(TokenType end_marker)
{
  auto opr1{read_product()};
  if ( opr1 == nullptr ) {
    return {};
  }
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = mScanner.read_token(loc);
    if ( type == end_marker ) {
      return opr1;
    }
    if ( type == TokenType::OR || type == TokenType::XOR ) {
      auto opr2{read_product()};
      if ( opr2 == nullptr ) {
	return {};
      }
      if ( type == TokenType::XOR ) {
	opr1 = AstExpr::new_xor(std::move(opr1), std::move(opr2), loc);
      }
      else {
	opr1 = AstExpr::new_or(std::move(opr1), std::move(opr2), loc);
      }
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error.");
      return nullptr;
    }
  }
}

END_NAMESPACE_YM_DOTLIB
