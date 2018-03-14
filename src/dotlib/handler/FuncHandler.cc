
/// @file FuncHandler.cc
/// @brief FuncHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "FuncHandler.h"
#include "HandlerFactory.h"
#include "AstExpr.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief function group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_function(DotlibParser& parser)
{
  return new FuncHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス FuncHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
FuncHandler::FuncHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
FuncHandler::~FuncHandler()
{
}

// @brief 値を読み込む処理
// @return 値を表す AstNode を返す．
AstNode*
FuncHandler::gen_node()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "String value is expected.");
    return nullptr;
  }

  mScanner.init(parser().cur_string(), loc);
  mUngetType = TokenType::ERROR;

  return read_expr(TokenType::END);
}

// @brief primary を読み込む．
AstExpr*
FuncHandler::read_primary()
{
  FileRegion loc;
  TokenType type = read_token(loc);
  if ( type == TokenType::LP ) {
    return read_expr(TokenType::RP);
  }
  if ( type == TokenType::SYMBOL ) {
    ShString name(mScanner.cur_string());
    return mgr().new_str_expr(loc, name);
  }
  if ( type == TokenType::INT_NUM ) {
    int v = mScanner.cur_int();
    if ( v != 0 && v != 1 ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. 0 or 1 is expected.");
      return nullptr;
    }
    return mgr().new_bool_expr(loc, static_cast<bool>(v));
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  kMsgError,
		  "DOTLIB_PARSER",
		  "Syntax error. number is expected.");
  return nullptr;
}

// @brief プライム付きの primary を読み込む．
AstExpr*
FuncHandler::read_primary2()
{
  FileRegion loc;
  TokenType type = read_token(loc);
  if ( type == TokenType::NOT ) {
    AstExpr* opr = read_primary();
    if ( opr == nullptr ) {
      return nullptr;
    }
    return mgr().new_not(FileRegion(loc, opr->loc()), opr);
  }
  unget_token(type, loc);

  AstExpr* node = read_primary();
  if ( node == nullptr ) {
    return nullptr;
  }

  type = read_token(loc);
  if ( type == TokenType::PRIME ) {
    return mgr().new_not(FileRegion(node->loc(), loc), node);
  }
  unget_token(type, loc);

  return node;
}

// @brief product を読み込む．
AstExpr*
FuncHandler::read_product()
{
  AstExpr* opr1 = read_primary2();
  if ( opr1 == nullptr ) {
    return nullptr;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == TokenType::AND ) {
      AstExpr* opr2 = read_primary2();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      opr1 = mgr().new_and(opr1, opr2);
    }
    else if ( type == TokenType::NOT || type == TokenType::LP || type == TokenType::SYMBOL ) {
      unget_token(type, loc);
      AstExpr* opr2 = read_primary2();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      opr1 = mgr().new_and(opr1, opr2);
    }
    else {
      // token を戻す．
      unget_token(type, loc);
      return opr1;
    }
  }
}

// @brief expression を読み込む．
AstExpr*
FuncHandler::read_expr(TokenType end_marker)
{
  AstExpr* opr1 = read_product();
  if ( opr1 == nullptr ) {
    return nullptr;
  }
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == end_marker ) {
      return opr1;
    }
    if ( type == TokenType::OR || type == TokenType::XOR ) {
      AstExpr* opr2 = read_product();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      if ( type == TokenType::XOR ) {
	opr1 = mgr().new_xor(opr1, opr2);
      }
      else {
	opr1 = mgr().new_or(opr1, opr2);
      }
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error.");
      return nullptr;
    }
  }
}

// @brief トークンを読み込む．
// @param[out] loc 対応するファイル上の位置情報を格納する変数
TokenType
FuncHandler::read_token(FileRegion& loc)
{
  if ( mUngetType != TokenType::ERROR ) {
    TokenType ans = mUngetType;
    loc = mUngetLoc;
    mUngetType = TokenType::ERROR;
    return ans;
  }
  else {
    return mScanner.read_token(loc);
  }
}

// @brief 読み込んだトークンを戻す．
// @param[in] type トークンの型
// @param[in] loc トークンの位置
void
FuncHandler::unget_token(TokenType type,
			 const FileRegion& loc)
{
  mUngetType = type;
  mUngetLoc = loc;
}

END_NAMESPACE_YM_DOTLIB
