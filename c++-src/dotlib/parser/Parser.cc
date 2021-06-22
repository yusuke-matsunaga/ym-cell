
/// @file Parser.cc
/// @brief Parser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstAttr.h"
#include "dotlib/TokenType.h"

#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief コンストラクタ
// @param[in] in 入力ファイルオブジェクト
// @param[in] mgr AstNode を管理するオブジェクト
// @param[in] debug デバッグモード
// @param[in] allow_no_semi 行末のセミコロンなしを許すかどうか
Parser::Parser(InputFileObj& in,
	       bool debug,
	       bool allow_no_semi)
  : mScanner{in},
    mDebug{debug},
    mAllowNoSemi{allow_no_semi}
{
}

// @brief デストラクタ
Parser::~Parser()
{
}

// @brief パーズする
// @return 読み込んだ AST を返す．
//
// エラーが起きたら nullptr を返す．
AstAttrPtr
Parser::parse()
{
  // 先頭(根本)の属性は 'library' でなければならない．
  auto attr{mScanner.read_attr()};
  if ( attr.type() != AttrType::library ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    attr.loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'library' keyword is expected "
		    "on the top of the structure");
    return {};
  }

  // 本体を読み込む．
  auto library{parse_library(attr)};
  if ( library == nullptr ) {
    return {};
  }

  if ( !read_tail() ) {
    return {};
  }

  // これより後の内容は無視される．
  for ( ; ; ) {
    Token token = mScanner.read_token();
    if ( token.type() == TokenType::END ) {
      break;
    }
    MsgMgr::put_msg(__FILE__, __LINE__,
		    token.loc(),
		    MsgType::Warning,
		    "DOTLIB_PARSER",
		    "contents after library group are ignored.");
  }

  return library;
}

// @brief Complex Attribute, GroupStatement のヘッダを読み込む．
AstValuePtr
Parser::parse_header(HeaderHandler& handler)
{
  Token lp_token = mScanner.read_and_verify(TokenType::LP);
  if ( lp_token.type() != TokenType::LP ) {
    return {};
  }

  handler.begin_header(lp_token.loc());
  for (int count = 0; ; ++ count) {
    Token token = mScanner.peek_token();
    if ( token.type() == TokenType::RP ) {
      mScanner.accept_token();
      return handler.end_header(token.loc(), count);
    }
    if ( count > 0 ) {
      Token comma = mScanner.read_and_verify(TokenType::COMMA);
      if ( comma.type() != TokenType::COMMA ) {
	return {};
      }
    }
    if ( !handler.read_header_value(mScanner, count) ) {
      return {};
    }
  }
}

// @brief 行末まで読み込む．
bool
Parser::read_tail()
{
  Token token = mScanner.read_token();
  if ( token.type() == TokenType::SEMI ) {
    token = mScanner.read_token();
  }
  else if ( !mAllowNoSemi ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    token.loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. Semicolon is expected.");
    return false;
  }
  if ( token.type() == TokenType::NL || token.type() == TokenType::END ) {
    return true;
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  token.loc(),
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. new-line is expected.");

  return false;
}

// @brief デバッグモードの時 true を返す．
bool
Parser::debug()
{
  return mDebug;
}


//////////////////////////////////////////////////////////////////////
// エラー出力用の便利関数
//////////////////////////////////////////////////////////////////////

// @brief 未対応の属性名に対するエラーメッセージを出力する．
// @param[in] attr 対象の属性
void
syntax_error(const AttrKwd& attr)
{
  ostringstream buf;
  buf << "Syntax error. Unexpected keyword: " << attr.type();
  MsgMgr::put_msg(__FILE__, __LINE__,
		  attr.loc(),
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  buf.str());
}

// @brief 同じ属性が重複して定義されている時のエラーを出力する．
// @param[in] attr 属性の型
// @param[in] prev_node 以前に定義されたノード
void
duplicate_error(const AttrKwd& attr,
		const AstAttr* prev_node)
{
  ostringstream buf;
  buf << attr.type() << " appear more than once."
      << " Previously appears at " << prev_node->attr().loc();
  MsgMgr::put_msg(__FILE__, __LINE__,
		  attr.loc(),
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  buf.str());
}


//////////////////////////////////////////////////////////////////////
// TokenType に関する関数
//////////////////////////////////////////////////////////////////////

// @brief TokenType 内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   TokenType type)
{
  const char* type_str = nullptr;
  switch ( type ) {
  case TokenType::COLON:      type_str = "':'"; break;
  case TokenType::SEMI:       type_str = "';'"; break;
  case TokenType::COMMA:      type_str = "','"; break;
  case TokenType::PLUS:       type_str = "'+'"; break;
  case TokenType::MINUS:      type_str = "'-'"; break;
  case TokenType::MULT:       type_str = "'*'"; break;
  case TokenType::DIV:        type_str = "'/'"; break;
  case TokenType::LP:         type_str = "'('"; break;
  case TokenType::RP:         type_str = "')'"; break;
  case TokenType::LCB:        type_str = "'{'"; break;
  case TokenType::RCB:        type_str = "'}'"; break;
  case TokenType::INT_NUM:    type_str = "INT"; break;
  case TokenType::FLOAT_NUM:  type_str = "FLOAT"; break;
  case TokenType::SYMBOL:     type_str = "SYMBOL"; break;
  case TokenType::EXPRESSION: type_str = "EXPRESSION"; break;
  case TokenType::NL:         type_str = "new-line"; break;
  case TokenType::ERROR :     type_str = "error"; break;
  case TokenType::END:        type_str = "end-of-file"; break;
  default:
    ASSERT_NOT_REACHED;
  }
  s << type_str;
  return s;
}

END_NAMESPACE_YM_DOTLIB
