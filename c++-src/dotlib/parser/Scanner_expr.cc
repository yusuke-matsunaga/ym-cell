
/// @file Scanner.cc
/// @brief Scanner の実装ファイル(expr読み込み)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2019, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Scanner.h"
#include "dotlib/AstExpr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"
#include "FuncParser.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 式を表す AstValue を生成する．
// @return 生成した AstValue を返す．
//
// エラーが起きた場合にはエラーメッセージを出力して nullptr を返す．
AstValuePtr
Scanner::read_expr()
{
  auto expr{_read_expr(TokenType::SEMI)};
  if ( expr ) {
    return AstValue::new_expr(std::move(expr));
  }
  else {
    return {};
  }
}

// @brief "式" を表す AstValue を生成する．
AstValuePtr
Scanner::read_function()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);

  FuncParser read(tmp_str, value_loc);
  return AstValuePtr{read()};
}

// @brief expression を読み込む．
AstExprPtr
Scanner::_read_expr(TokenType end_marker)
{
  auto opr1{_read_product()};
  if ( opr1 == nullptr ) {
    return {};
  }

  for ( ; ; ) {
    Token token = read_token();
    if ( token.type() == end_marker ) {
      return opr1;
    }
    if ( token.type() == TokenType::PLUS || token.type() == TokenType::MINUS ) {
      auto opr2{_read_product()};
      if ( opr2 == nullptr ) {
	return {};
      }

      if ( token.type() == TokenType::PLUS ) {
	opr1 = AstExpr::new_plus(std::move(opr1), std::move(opr2), token.loc());
      }
      else {
	opr1 = AstExpr::new_minus(std::move(opr1), std::move(opr2), token.loc());
      }
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      token.loc(),
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error.");
      return {};
    }
  }
}

// @brief primary を読み込む．
AstExprPtr
Scanner::_read_primary()
{
  Token token = read_token();
  switch ( token.type() ) {
  case TokenType::LP:
    return _read_expr(TokenType::RP);

  case TokenType::SYMBOL:
    {
      const char* name = cur_string();
      if ( strcmp(name, "VDD") == 0 ) {
	return AstExpr::new_vdd(token.loc());
      }
      else if ( strcmp(name, "VSS") == 0 ) {
	return AstExpr::new_vss(token.loc());
      }
      else if ( strcmp(name, "VCC") == 0 ) {
	return AstExpr::new_vcc(token.loc());
      }
      else {
	MsgMgr::put_msg(__FILE__, __LINE__,
			token.loc(),
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. "
			"Only 'VDD', 'VSS', and 'VCC' are allowed.");
	return {};
      }
    }
    // ここには来ない．

  case TokenType::FLOAT_NUM:
  case TokenType::INT_NUM:
    return AstExpr::new_float(cur_float(), token.loc());

  default:
    break;
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. number is expected.");
  return {};
}

// @brief prudct を読み込む．
AstExprPtr
Scanner::_read_product()
{
  auto opr1{_read_primary()};
  if ( opr1 == nullptr ) {
    return {};
  }

  for ( ; ; ) {
    Token token = peek_token();
    if ( token.type() == TokenType::MULT || token.type() == TokenType::DIV ) {
      accept_token();
      auto opr2{_read_primary()};
      if ( opr2 == nullptr ) {
	return {};
      }
      if ( token.type() == TokenType::MULT ) {
	opr1 = AstExpr::new_mult(std::move(opr1), std::move(opr2), token.loc());
      }
      else {
	opr1 = AstExpr::new_div(std::move(opr1), std::move(opr2), token.loc());
      }
    }
    else {
      return opr1;
    }
  }
}

END_NAMESPACE_YM_DOTLIB
