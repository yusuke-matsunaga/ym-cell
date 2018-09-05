
/// @file DotlibParser.cc
/// @brief DotlibParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"
#include "dotlib/SimpleHandler.h"
#include "dotlib/ComplexHandler.h"
#include "dotlib/GroupHandler.h"
#include "dotlib/AstMgr.h"
//#include "dotlib/AstLibrary.h"
#include "dotlib/TokenType.h"
#include "dotlib/LibraryHandler.h"
#include "ym/FileIDO.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief コンストラクタ
// @param[in] ido 入力データオブジェクト
// @param[in] mgr AstNode を管理するオブジェクト
// @param[in] debug デバッグモード
// @param[in] allow_no_semi 行末のセミコロンなしを許すかどうか
DotlibParser::DotlibParser(IDO& ido,
			   AstMgr& mgr,
			   bool debug,
			   bool allow_no_semi) :
  mScanner(ido),
  mAstMgr(mgr)
{
}

// デストラクタ
DotlibParser::~DotlibParser()
{
}

// @brief パーズする
// @return 読み込んだ AST を返す．
//
// エラーが起きたら nullptr を返す．
const AstLibrary*
DotlibParser::parse()
{
  // goto 文を使う関係で変数はここで宣言しておかなければならない．
  LibraryHandler handler(*this);
  const AstLibrary* library = nullptr;
  TokenType type;
  FileRegion loc;

  // 空行を読み飛ばす．
  for ( type = read_token(loc); type == TokenType::NL; type = read_token(loc) ) { }

  // 先頭のトークンが "library" であるかチェックする．
  if ( type != TokenType::SYMBOL || strcmp(cur_string(), "library") != 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'library' keyword is expected "
		    "on the top of the structure");
    goto last;
  }

  library = handler.parse_value();
  if ( library == nullptr ) {
    goto last;
  }

  if ( !expect_nl() ) {
    library = nullptr;
    goto last;
  }
  for ( ; ; ) {
    TokenType type = read_token(loc);
    if ( type == TokenType::END ) {
      break;
    }
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Warning,
		    "DOTLIB_PARSER",
		    "contents after library group are ignored.");
  }

 last:

  return library;
}

// @brief Simple Attribute を読み込む．
// @param[in] handler ハンドラ
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_simple_attribute(SimpleHandler& handler)
{
  if ( !expect(TokenType::COLON) ) {
    return false;
  }

  FileRegion value_loc;
  TokenType value_type = read_token(value_loc, handler.symbol_mode());
  if ( !handler.read_value(value_type, value_loc) ) {
    return false;
  }

  if ( !expect_nl() ) {
    return false;
  }

  return true;
}

// @brief Complex Attribute を読み込む．
// @param[in] handler ハンドラ(ComplexHandler の継承クラス)
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_complex_attribute(ComplexHandler& handler)
{
  if ( !parse_cg_header(handler) ) {
    return false;
  }

  return expect_nl();
}

// @brief Group Statement を読み込む．
// @param[in] handler ハンドラ(GroupHandler の継承クラス)
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_group_statement(GroupHandler& handler)
{
  if ( !parse_cg_header(handler) ) {
    return false;
  }

  // グループ本体の始まり
  if ( !expect(TokenType::LCB) ) {
    return false;
  }

  // 仮想関数の呼び出し
  handler.begin_group();

  FileRegion first_loc = cur_loc();
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == TokenType::NL ) {
      // 改行は読み飛ばす．
      continue;
    }
    if ( type == TokenType::RCB ) {
      // グループ本体の終わり．
      FileRegion last_loc = loc;
      if ( !handler.end_group(FileRegion(first_loc, last_loc)) ) {
	return false;
      }

      if ( !expect(TokenType::NL) ) {
	return false;
      }

      return true;
    }
    if ( type != TokenType::SYMBOL ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "string value is expected.");
      return false;
    }
    // 一般のトークンの処理
    const char* name = cur_string();
    AttrType name_type = conv_to_attr(name);
    if ( name_type == AttrType::none ) {
      ostringstream buf;
      buf << name << ": syntax error.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      buf.str());
      return false;
    }
    bool r = handler.read_group_attr(name_type, loc);
    if ( !r ) {
      return false;
    }
  }
}

// @brief Complex Attribute, GroupStatement のヘッダを読み込む．
// @param[in] handler ハンドラ(CGHandler の継承クラス)
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_cg_header(CGHandler& handler)
{
  if ( !expect(TokenType::LP) ) {
    return false;
  }

  handler.begin_header();

  FileRegion first_loc = cur_loc();

  FileRegion loc;
  TokenType type = read_token(loc);
  int count = 0;
  if ( type != TokenType::RP ) {
    for ( ; ; ) {
      if ( !handler.read_header_value(type, loc, count) ) {
	return false;
      }
      ++ count;

      TokenType type1 = read_token(loc);
      if ( type1 == TokenType::RP ) {
	break;
      }
      if ( type1 != TokenType::COMMA ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			"syntax error. ',' is expected.");
	return false;
      }
      type = read_token(loc);
    }
  }

  if ( !handler.end_header(FileRegion(first_loc, loc), count) ) {
    return false;
  }

  return true;
}

// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
bool
DotlibParser::expect(TokenType req_type)
{
  FileRegion loc;
  TokenType type = read_token(loc);
  if ( type == req_type ) {
    return true;
  }

  const char* type_str = nullptr;
  switch ( req_type ) {
  case TokenType::COLON:      type_str = "':'"; break;
  case TokenType::SEMI:       type_str = "';'"; break;
  case TokenType::COMMA:      type_str = "','"; break;
  case TokenType::PLUS:       type_str = "'+'"; break;
  case TokenType::MINUS:      type_str = "'-'"; break;
  case TokenType::MULT:       type_str = "'*'"; break;
  case TokenType::DIV:        type_str = "'/'"; break;
  case TokenType::NOT:        type_str = "'!'"; break;
  case TokenType::AND:        type_str = "'&'"; break;
  case TokenType::OR:         type_str = "'|'"; break;
  case TokenType::XOR:        type_str = "'^'"; break;
  case TokenType::PRIME:      type_str = "'"; break;
  case TokenType::LP:         type_str = "'('"; break;
  case TokenType::RP:         type_str = "')'"; break;
  case TokenType::LCB:        type_str = "'{'"; break;
  case TokenType::RCB:        type_str = "'}'"; break;
  case TokenType::SYMBOL:     type_str = "STR"; break;
  case TokenType::INT_NUM:    type_str = "INT"; break;
  case TokenType::FLOAT_NUM:  type_str = "FLOAT"; break;
  case TokenType::EXPRESSION: type_str = "EXPRESSION"; break;
  case TokenType::NL:         type_str = "new-line"; break;
  default:                    ASSERT_NOT_REACHED;
  }
  ostringstream buf;
  buf << "syntax error. " << type_str << " is expected.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  buf.str());
  return false;
}

// @brief 行末まで読み込む．
bool
DotlibParser::expect_nl()
{
  if ( mAllowNoSemi ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == TokenType::SEMI ) {
      type = read_token(loc);
    }
    if ( type == TokenType::NL || type == TokenType::END ) {
      return true;
    }
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. Semicolon is expected.");
    return false;
  }
  else {
    if ( !expect(TokenType::SEMI) ) {
      return false;
    }
    if ( !expect(TokenType::NL) ) {
      return false;
    }
  }
  return true;
}

// @brief 直前の read_token() に対応する位置を返す．
FileRegion
DotlibParser::cur_loc() const
{
  return mCurLoc;
}

// @brief 文字列を属性値に変換する．
AttrType
DotlibParser::conv_to_attr(const char* str)
{
  return mAttrDic.get(str);
}

// @brief デバッグモードの時 true を返す．
bool
DotlibParser::debug()
{
  return mDebug;
}

// @brief primary を読み込む．
AstExpr*
DotlibParser::read_primary()
{
  FileRegion loc;
  TokenType type = read_token(loc);
  if ( type == TokenType::LP ) {
    return read_expr(TokenType::RP);
  }
  if ( type == TokenType::SYMBOL ) {
    const char* name =  cur_string();
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
    double val = cur_float();
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
DotlibParser::read_product()
{
  AstExpr* opr1 = read_primary();
  if ( opr1 == nullptr ) {
    return nullptr;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
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
DotlibParser::read_expr(TokenType end_marker)
{
  // ここだけ mUngetType, mUngetLoc を考慮する必要があるので
  // じかに read_token() を呼んではいけない．

  AstExpr* opr1 = read_product();
  if ( opr1 == nullptr ) {
    return nullptr;
  }
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = _read_token(loc);
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
DotlibParser::_read_token(FileRegion& loc)
{
  if ( mUngetType != TokenType::ERROR ) {
    TokenType ans = mUngetType;
    loc = mUngetLoc;
    mUngetType = TokenType::ERROR;
    return ans;
  }
  else {
    return read_token(loc);
  }
}

END_NAMESPACE_YM_DOTLIB
