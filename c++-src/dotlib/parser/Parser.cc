
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

#include "parse_simple.h"
#include "parse_complex.h"
#include "parse_group.h"


BEGIN_NAMESPACE_YM_DOTLIB

FixedElemHeader Parser::sEmptyHeader({});

FixedElemHeader Parser::sFloatFloatHeader(
  { read_float, read_float }
);

FixedElemHeader Parser::sFloatFloatStrHeader(
  { read_float, read_float, read_string }
);

FixedElemHeader Parser::sFloatStrHeader(
  { read_float, read_string }
);

FixedElemHeader Parser::sFloatVectorHeader(
  { read_float_vector }
);

FixedElemHeader Parser::sIntFloatHeader(
  { read_int, read_float }
);

FixedElemHeader Parser::sIntFloatVectorHeader(
  { read_int, read_float_vector }
);

FixedElemHeader Parser::sIntStrHeader(
  { read_int, read_string }
);

FixedElemHeader Parser::sIntVectorHeader(
  { read_int_vector }
);

FixedElemHeader Parser::sStrFloatHeader(
  { read_string, read_float }
);

FixedElemHeader Parser::sStrHeader(
  { read_string }
);

FixedElemHeader Parser::sStrIntHeader(
  { read_string, read_int }
);

FixedElemHeader Parser::sStrStrHeader(
  { read_string, read_string }
);

FixedElemHeader Parser::sStrStrIntHeader(
  { read_string, read_string, read_int }
);

FixedElemHeader Parser::sStrStrStrHeader(
  { read_string, read_string, read_string }
);

FixedElemHeader Parser::sTechnologyHeader(
  { read_technology }
);

FanoutLengthHeader Parser::sFanoutLengthHeader;

ListHeader Parser::sFloatVectorListHeader( read_float_vector );

ListHeader Parser::sIntListHeader( read_int );

ListHeader Parser::sStrListHeader( read_string );

unordered_map<string, AttrHandler> Parser::sHandlerDict{
#include "Parser_dict.cc"
};

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
  if ( attr.name() != "library" ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    attr.loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "'library' keyword is expected "
		    "on the top of the structure");
    return {};
  }

  // 本体を読み込む．
  auto library{parse_group_statement(attr, "library", sStrHeader)};
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

// @brief Simple Attribute を読み込む．
// @retrun 結果の AstAttr を返す．
//
// エラーが起こったら nullptr を返す．
AstAttrPtr
Parser::parse_simple_attribute(const AttrKwd& attr,
				     SimpleHandler handler)
{
  // 属性名の直後は必ず ':' でなければならない．
  Token token = mScanner.read_and_verify(TokenType::COLON);
  if ( token.type() != TokenType::COLON ) {
    return {};
  }

  // その後の値を読み込む．
  auto value{handler(mScanner)};
  if ( value == nullptr ) {
    // エラー
    return {};
  }

  // 末尾の ';' を確認
  if ( !read_tail() ) {
    // エラー
    return {};
  }

  // 値を返す．
  return AstAttrPtr{new AstAttr(attr, std::move(value))};
}

// @brief Complex Attribute を読み込む．
AstAttrPtr
Parser::parse_complex_attribute(const AttrKwd& attr,
				HeaderHandler& handler)
{
  auto value{parse_header(handler)};
  if ( value == nullptr ) {
    return {};
  }

  if ( !read_tail() ) {
    return {};
  }

  return AstAttrPtr{new AstAttr(attr, std::move(value))};
}

// @brief Group Statement を読み込む．
// @retrun 結果の AstAttr を返す．
//
// エラーが起こったら nullptr を返す．
AstAttrPtr
Parser::parse_group_statement(const AttrKwd& attr,
			      const char* group_name,
			      HeaderHandler& header_handler)
{
  // ヘッダをパースする．
  auto header_value{parse_header(header_handler)};
  if ( header_value == nullptr ) {
    // エラー
    return {};
  }

  // グループ本体の始まり
  Token lcb_token = mScanner.read_and_verify(TokenType::LCB);
  if ( lcb_token.type() != TokenType::LCB ) {
    return {};
  }

  vector<AstAttrPtr> child_list;
  for ( ; ; ) {
    Token token = mScanner.peek_token();
    if ( token.type() == TokenType::NL ) {
      mScanner.accept_token();
      // 改行は読み飛ばす．
      continue;
    }
    if ( token.type() == TokenType::RCB ) {
      // '}' ならグループ記述の終わり
      FileRegion rcb_loc{token.loc()};
      mScanner.accept_token();

      // グループ本体の終わり．
      Token token = mScanner.read_and_verify(TokenType::NL);
      if ( token.type() != TokenType::NL ) {
	return {};
      }

      // 値を作る．
      FileRegion loc{lcb_token.loc(), rcb_loc};
      auto group_value{AstValue::new_group(std::move(header_value), child_list, loc)};
      return AstAttrPtr{new AstAttr(attr, std::move(group_value))};
    }

    // 子供の要素を読み込む．
    AttrKwd child_attr{mScanner.read_attr()};
    if ( child_attr.name() == "none" ) {
      return {};
    }
    string key = string(group_name) + ":" + child_attr.name();
    if ( sHandlerDict.count(key) > 0 ) {
      auto handler{sHandlerDict.at(key)};
      auto child{handler(*this, child_attr)};
      if ( child == nullptr ) {
	return {};
      }
      child_list.push_back(std::move(child));
    }
    else {
      // 対応するハンドラが登録されていない．
      syntax_error(child_attr);
      return {};
    }
  }
}

// @brief Complex Attribute, GroupStatement のヘッダを読み込む．
AstValuePtr
Parser::parse_header(HeaderHandler& handler)
{
  // まず '(' があるか確認する．
  Token lp_token = mScanner.read_and_verify(TokenType::LP);
  if ( lp_token.type() != TokenType::LP ) {
    // エラー
    return {};
  }

  // complex attribute の始まり
  handler.begin_header(lp_token.loc());
  for (int count = 0; ; ++ count) {
    Token token = mScanner.peek_token();
    if ( token.type() == TokenType::RP ) {
      // ')' を読み込んだので終わる．
      mScanner.accept_token();
      // complex attribute の終わり
      return handler.end_header(token.loc(), count);
    }
    if ( count > 0 ) {
      // 要素と要素の間には ',' が必要
      Token comma = mScanner.read_and_verify(TokenType::COMMA);
      if ( comma.type() != TokenType::COMMA ) {
	// エラー
	return {};
      }
    }
    // ハンドラを用いて値を読み込む．
    if ( !handler.read_header_value(mScanner, token.loc(), count) ) {
      return {};
    }
  }
}

// @brief 行末まで読み込む．
bool
Parser::read_tail()
{
  // 通常は ';' '\n' を適正なパタンとみなす．
  // ただし，mAllowNoSemi が true の場合には
  // ';' がなくてもよい．．
  // またファイルの末尾の場合には改行は不要
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
		  "Syntax error. New-line is expected.");

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
  buf << "Syntax error. Unexpected keyword: " << attr.name();
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
  buf << attr.name() << " appear more than once."
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
  case TokenType::SYMBOL:     type_str = "SYMBOL"; break;
  case TokenType::BOOL_0:     type_str = "BOOL_0"; break;
  case TokenType::BOOL_1:     type_str = "BOOL_1"; break;
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
