
/// @file DotlibParser.cc
/// @brief DotlibParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibParser.h"
#include "AstMgr.h"
#include "DotlibHandler.h"
#include "AstLibrary.h"
#include "HandlerFactory.h"
#include "TokenType.h"
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
  mAstMgr(mgr),
  mLibraryHandler(HandlerFactory::new_library(*this))
{
}

// デストラクタ
DotlibParser::~DotlibParser()
{
  delete mLibraryHandler;
}

// @brief パーズする
// @return 読み込んだ AST を返す．
//
// エラーが起きたら nullptr を返す．
const AstLibrary*
DotlibParser::parse()
{
  // goto 文を使う関係で変数はここで宣言しておかなければならない．
  const AstLibrary* root_node = nullptr;
  bool error = false;
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
    error = true;
    goto last;
  }

  root_node = dynamic_cast<const AstLibrary*>(mLibraryHandler->parse_attr_value(AttrType::library, loc));
  if ( root_node == nullptr ) {
    error = true;
    goto last;
  }

  if ( !expect_nl() ) {
    error = true;
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
  if ( error ) {
    return nullptr;
  }

  return root_node;
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

END_NAMESPACE_YM_DOTLIB
