
/// @file DotlibParser.cc
/// @brief DotlibParser の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/DotlibParser.h"
#include "dotlib/HeaderHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"

#include "dotlib/StrHandler.h"
#include "dotlib/StrIntHandler.h"
#include "dotlib/StrListHandler.h"
#include "dotlib/StrStrHandler.h"
#include "dotlib/StrStrIntHandler.h"

#include "dotlib/CellHandler.h"
#include "dotlib/DomainHandler.h"
#include "dotlib/FFHandler.h"
#include "dotlib/InputVoltageHandler.h"
#include "dotlib/LatchHandler.h"
#include "dotlib/LibraryHandler.h"
#include "dotlib/OutputVoltageHandler.h"
#include "dotlib/PinHandler.h"
#include "dotlib/TableHandler.h"
#include "dotlib/TemplateHandler.h"
#include "dotlib/TimingHandler.h"

#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief コンストラクタ
// @param[in] in 入力ファイルオブジェクト
// @param[in] mgr AstNode を管理するオブジェクト
// @param[in] debug デバッグモード
// @param[in] allow_no_semi 行末のセミコロンなしを許すかどうか
DotlibParser::DotlibParser(InputFileObj& in,
			   AstMgr& mgr,
			   bool debug,
			   bool allow_no_semi) :
  mScanner{in},
  mAstMgr{mgr},
  mDebug{debug},
  mAllowNoSemi{allow_no_semi}
{
}

// @brief デストラクタ
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
  const AstLibrary* library = nullptr;
  TokenType type;
  FileRegion loc;
  bool stat = false;

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

  stat = parse_library(library, AttrType::library, loc);
  if ( !stat ) {
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
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_simple_attribute(SimpleHandler handler)
{
  if ( !expect(TokenType::COLON) ) {
    return false;
  }

  if ( !handler(*this) ) {
    return false;
  }

  return expect_nl();
}

// @brief Complex Attribute を読み込む．
// @param[in] handler ヘッダ読み込みハンドラ (HeaderHandler の継承クラス)
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_complex_attribute(HeaderHandler& handler)
{
  if ( !parse_header(handler) ) {
    return false;
  }

  return expect_nl();
}

// @brief Complex Attribute, GroupStatement のヘッダを読み込む．
// @param[in] handler ハンドラ(CGHandler の継承クラス)
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
DotlibParser::parse_header(HeaderHandler& handler)
{
  if ( !expect(TokenType::LP) ) {
    return false;
  }

  FileRegion first_loc = cur_loc();
  handler.begin_header(first_loc);

  FileRegion loc;
  TokenType type = read_token(loc);
  int count = 0;
  if ( type != TokenType::RP ) {
    unget_token(type, loc);
    for ( ; ; ) {
      if ( !handler.read_header_value(count) ) {
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
    }
  }

  if ( !handler.end_header(loc, count) ) {
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

  {
    // エラーメッセージを作る．
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
    case TokenType::PRIME:      type_str = "'";   break;
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
  }
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

// @brief トークンを一つ読み込む．
// @param[out] loc ファイル上の位置情報を格納する変数
// @param[in] symbol_mode 数字も文字とみなすモード
// @return トークンの型を返す．
TokenType
DotlibParser::read_token(FileRegion& loc,
			 bool symbol_mode)
{
  if ( mUngetType != TokenType::ERROR ) {
    auto ans = mUngetType;
    loc = mUngetLoc;
    mUngetType = TokenType::ERROR;
    return ans;
  }
  else {
    auto ans = mScanner.read_token(loc, symbol_mode);
    mCurLoc = loc;
    return ans;
  }
}

// @brief トークンを戻す．
// @param[in] token_type トークンの種類
// @param[in] token_loc トークンの場所
void
DotlibParser::unget_token(TokenType token_type,
			  const FileRegion& token_loc)
{
  ASSERT_COND( mUngetType == TokenType::ERROR );

  mUngetType = token_type;
  mUngetLoc = token_loc;
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


//////////////////////////////////////////////////////////////////////
// エラー出力用の便利関数
//////////////////////////////////////////////////////////////////////

// @brief 未対応の属性名に対するエラーメッセージを出力する．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
void
syntax_error(AttrType attr_type,
	     const FileRegion& attr_loc)
{
  ostringstream buf;
  buf << "Syntax error. Unexpected keyword: " << attr_type;
  MsgMgr::put_msg(__FILE__, __LINE__,
		  attr_loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  buf.str());
}

// @brief 同じ属性が重複して定義されている時のエラーを出力する．
// @param[in] attr_type 属性の型
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] prev_node 以前に定義されたノード
void
duplicate_error(AttrType attr_type,
		const FileRegion& attr_loc,
		const AstNode* prev_node)
{
  ostringstream buf;
  buf << attr_type << " appear more than once."
      << " Previously appears at " << prev_node->loc();
  MsgMgr::put_msg(__FILE__, __LINE__,
		    attr_loc,
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
