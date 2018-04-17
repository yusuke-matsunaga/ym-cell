
/// @file DotlibHandler.cc
/// @brief DotlibHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/TokenType.h"
#include "dotlib/AstMgr.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstFloatVector.h"
#include "dotlib/AstString.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
DotlibHandler::DotlibHandler(DotlibParser& parser) :
  mParser(parser)
{
}

// @brief デストラクタ
DotlibHandler::~DotlibHandler()
{
}

// @brief group attribute 用のパースを行う．
// @return 正しく読み込めたら true を返す．
bool
DotlibHandler::parse_complex()
{
  if ( !expect(TokenType::LP) ) {
    return false;
  }

  FileRegion first_loc = parser().cur_loc();

  FileRegion loc;
  TokenType type = parser().read_token(loc);
  int count = 0;
  if ( type != TokenType::RP ) {
    for ( ; ; ) {
      ++ count;
      if ( !read_value(type, loc, count) ) {
	return false;
      }

      TokenType type1 = parser().read_token(loc);
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
      type = parser().read_token(loc);
    }
  }

  return true;
}

// @brief AstNode を生成する．
// @param[in] loc ファイル上の位置情報
// @param[in] vector_mode ベクタモードの時 true にするフラグ
// @param[in] type 型
AstNode*
DotlibHandler::new_value(const FileRegion& loc,
			 TokenType type,
			 bool vector_mode)
{
  switch ( type ) {
  case TokenType::INT_NUM:
    return mgr().new_int(loc, parser().cur_int());

  case TokenType::FLOAT_NUM:
    return mgr().new_float(loc, parser().cur_float());

  case TokenType::SYMBOL:
    if ( vector_mode ) {
      const char* tmp_str = parser().cur_string();
      vector<double> value_list;
      string buf;
      char c = '\0';
      for ( const char* s = tmp_str; (c = *s) ; ++ s ) {
	if ( isspace(c) ) {
	  continue;
	}
	else if ( c == ',' ) {
	  if ( buf.size() == 0 ) {
	    MsgMgr::put_msg(__FILE__, __LINE__,
			    loc,
			    MsgType::Error,
			    "DOTLIB_PARSER",
			    "Syntax error. Null element.");
	    return nullptr;
	  }
	  value_list.push_back(strtod(buf.c_str(), nullptr));
	  buf.clear();
	}
	else {
	  buf += c;
	}
      }
      if ( buf.size() > 0 ) {
	value_list.push_back(strtod(buf.c_str(), nullptr));
      }
      return mgr().new_vector(loc, value_list);
    }
    else {
      return mgr().new_string(loc, ShString(parser().cur_string()));
    }

  default:
    break;
  }
  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Syntax error. int/float/string value is expected.");
  return nullptr;
}

// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
bool
DotlibHandler::expect(TokenType type)
{
  return mParser.expect(type);
}

// @brief 行末まで読み込む．
bool
DotlibHandler::expect_nl()
{
  return mParser.expect_nl();
}

// @brief パーサーを得る．
DotlibParser&
DotlibHandler::parser()
{
  return mParser;
}

// @brief AstMgr* を得る．
AstMgr&
DotlibHandler::mgr()
{
  return mParser.mgr();
}

// @brief デバッグモードの時に true を返す．
bool
DotlibHandler::debug()
{
  return mParser.debug();
}

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
