
/// @file ExprHandler.cc
/// @brief ExprHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ExprHandler.h"
#include "HandlerFactory.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "AstExpr.h"
#include "TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 式をパーズするハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_expr(DotlibParser& parser)
{
  return new ExprHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス ExprHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
ExprHandler::ExprHandler(DotlibParser& parser) :
  SimpleHandler(parser, false),
  mUngetType(TokenType::ERROR)
{
}

// @brief デストラクタ
ExprHandler::~ExprHandler()
{
}

// @brief 属性値を読み込む．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ値を表す AstNode を返す．
//
// エラーの場合には nullptr を返す．
const AstNode*
ExprHandler::parse_attr_value(AttrType attr_type,
			      const FileRegion& attr_loc)
{
  return parse(attr_type, attr_loc);
}

// @brief パーズする．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @return 読み込んだ式を表す AstExpr を返す．
//
// エラーの場合には nullptr を返す．
const AstExpr*
ExprHandler::parse(AttrType attr_type,
		   const FileRegion& attr_loc)
{
}

// @brief パーズして代入する．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @param[out] dst 代入先
// @retval true 正常に処理した．
// @retval false 処理中にエラーが起こった．
//
// dst が nullptr でない場合には二重定義エラーとなる．
bool
ExprHandler::parse_and_assign(AttrType attr_type,
			      const FileRegion& attr_loc,
			      const AstExpr*& dst)
{
  const AstExpr* expr = parse(attr_type, attr_loc);
  if ( expr == nullptr ) {
    return false;
  }
  if ( dst != nullptr ) {
    // 二重定義エラー
    ostringstream buf;
    buf << attr_type << ": defined more than once."
	<< " Previous definition is at " << dst->loc();
    MsgMgr::put_msg(__FILE__, __LINE__,
		    attr_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  dst = expr;

  return true;
}

#if 0
// @brief 値を読み込む処理
// @return 値を表す AstNode を返す．
AstNode*
ExprHandler::gen_node()
{
  return read_expr(TokenType::SEMI);
}
#endif

// @brief primary を読み込む．
AstExpr*
ExprHandler::read_primary()
{
  FileRegion loc;
  TokenType type = parser().read_token(loc);
  if ( type == TokenType::LP ) {
    return read_expr(TokenType::RP);
  }
  if ( type == TokenType::SYMBOL ) {
    const char* name =  parser().cur_string();
    if ( strcmp(name, "VDD") == 0 ) {
      return mgr().new_vdd_expr(loc);
    }
    else if ( strcmp(name, "VSS") == 0 ) {
      return mgr().new_vss_expr(loc);
    }
    else if ( strcmp(name, "VCC") == 0 ) {
      return mgr().new_vcc_expr(loc);
    }
    else {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error. "
		      "Only 'VDD', 'VSS', and 'VCC' are allowed.");
      return nullptr;
    }
  }
  if ( type == TokenType::FLOAT_NUM || type == TokenType::INT_NUM ) {
    double val = parser().cur_float();
    return mgr().new_float_expr(loc, val);
  }

  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. number is expected.");
  return nullptr;
}

// @brief prudct を読み込む．
AstExpr*
ExprHandler::read_product()
{
  AstExpr* opr1 = read_primary();
  if ( opr1 == nullptr ) {
    return nullptr;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = parser().read_token(loc);
    if ( type == TokenType::MULT || type == TokenType::DIV ) {
      AstExpr* opr2 = read_primary();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      if ( type == TokenType::MULT ) {
	opr1 = mgr().new_mult(opr1, opr2);
      }
      else {
	opr1 = mgr().new_div(opr1, opr2);
      }
    }
    else {
      // token を戻す．
      mUngetType = type;
      mUngetLoc = loc;
      return opr1;
    }
  }
}

// @brief expression を読み込む．
AstExpr*
ExprHandler::read_expr(TokenType end_marker)
{
  // ここだけ mUngetType, mUngetLoc を考慮する必要があるので
  // じかに parser().read_token() を呼んではいけない．

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
    if ( type == TokenType::PLUS || type == TokenType::MINUS ) {
      AstExpr* opr2 = read_product();
      if ( opr2 == nullptr ) {
	return nullptr;
      }
      if ( type == TokenType::PLUS ) {
	opr1 = mgr().new_plus(opr1, opr2);
      }
      else {
	opr1 = mgr().new_minus(opr1, opr2);
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

// @brief トークンを読み込む．
// @param[out] loc 対応するファイル上の位置情報を格納する変数
TokenType
ExprHandler::read_token(FileRegion& loc)
{
  if ( mUngetType != TokenType::ERROR ) {
    TokenType ans = mUngetType;
    loc = mUngetLoc;
    mUngetType = TokenType::ERROR;
    return ans;
  }
  else {
    return parser().read_token(loc);
  }
}

END_NAMESPACE_YM_DOTLIB
