
/// @file FuncParser.cc
/// @brief FuncParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "FuncParser.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FuncParser
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] str 対象の文字列
// @param[in] loc ファイル上の位置
// @param[in] mgr AstMgr
FuncParser::FuncParser(const string& str,
		       const FileRegion& loc,
		       AstMgr& mgr) :
  mScanner(str, loc),
  mMgr(mgr)
{
}

// @brief デストラクタ
FuncParser::~FuncParser()
{
}

// @brief 論理式を読み込む．
bool
FuncParser::operator()(const AstExpr*& dst)
{
  dst = read_expr(TokenType::END);

  return dst != nullptr;
}

// @brief primary を読み込む．
const AstExpr*
FuncParser::read_primary()
{
  FileRegion loc;
  TokenType type = mScanner.read_token(loc);
  if ( type == TokenType::LP ) {
    return read_expr(TokenType::RP);
  }
  if ( type == TokenType::SYMBOL ) {
    ShString name(mScanner.cur_string());
    return mMgr.new_str_expr(loc, name);
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
    return mMgr.new_bool_expr(loc, static_cast<bool>(v));
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. number is expected.");
  return nullptr;
}

// @brief プライム付きの primary を読み込む．
const AstExpr*
FuncParser::read_primary2()
{
  FileRegion loc;
  TokenType type = mScanner.read_token(loc);
  if ( type == TokenType::NOT ) {
    const AstExpr* opr = read_primary();
    if ( opr == nullptr ) {
      return nullptr;
    }
    return mMgr.new_not(FileRegion(loc, opr->loc()), opr);
  }
  mScanner.unget_token(type, loc);

  const AstExpr* node = read_primary();
  if ( node == nullptr ) {
    return nullptr;
  }

  type = mScanner.read_token(loc);
  if ( type == TokenType::PRIME ) {
    return mMgr.new_not(FileRegion(node->loc(), loc), node);
  }
  mScanner.unget_token(type, loc);

  return node;
}

// @brief product を読み込む．
const AstExpr*
FuncParser::read_product()
{
  const AstExpr* opr1 = read_primary2();
  if ( opr1 == nullptr ) {
    return nullptr;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = mScanner.read_token(loc);
    if ( type == TokenType::AND ) {
      const AstExpr* opr2 = read_primary2();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      opr1 = mMgr.new_and(opr1, opr2);
    }
    else if ( type == TokenType::NOT || type == TokenType::LP || type == TokenType::SYMBOL ) {
      mScanner.unget_token(type, loc);
      const AstExpr* opr2 = read_primary2();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      opr1 = mMgr.new_and(opr1, opr2);
    }
    else {
      // token を戻す．
      mScanner.unget_token(type, loc);
      return opr1;
    }
  }
}

// @brief expression を読み込む．
const AstExpr*
FuncParser::read_expr(TokenType end_marker)
{
  const AstExpr* opr1 = read_product();
  if ( opr1 == nullptr ) {
    return nullptr;
  }
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = mScanner.read_token(loc);
    if ( type == end_marker ) {
      return opr1;
    }
    if ( type == TokenType::OR || type == TokenType::XOR ) {
      const AstExpr* opr2 = read_product();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      if ( type == TokenType::XOR ) {
	opr1 = mMgr.new_xor(opr1, opr2);
      }
      else {
	opr1 = mMgr.new_or(opr1, opr2);
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
