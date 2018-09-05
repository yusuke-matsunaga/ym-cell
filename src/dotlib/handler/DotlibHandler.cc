
/// @file DotlibHandler.cc
/// @brief DotlibHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"
#include "dotlib/SimpleHandler.h"
#include "dotlib/CGHandler.h"
#include "dotlib/ComplexHandler.h"
#include "dotlib/GroupHandler.h"
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

// @brief 未対応の属性名に対するエラーメッセージを出力する．
// @param[in] attr_type 対象の属性
// @param[in] attr_loc attr_type のファイル上の位置
void
DotlibHandler::syntax_error(AttrType attr_type,
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

#if 0
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

#endif


//////////////////////////////////////////////////////////////////////
// クラス SimpleHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
SimpleHandler::SimpleHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
SimpleHandler::~SimpleHandler()
{
}

// @brief シンボルモードの値を返す．
//
// デフォルト実装では false を返す．
bool
SimpleHandler::symbol_mode()
{
  return false;
}

// @brief Simple Attribute を読み込む．
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
SimpleHandler::parse_simple_attribute()
{
  return parser().parse_simple_attribute(*this);
}


//////////////////////////////////////////////////////////////////////
// クラス CGHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser
CGHandler::CGHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
CGHandler::~CGHandler()
{
}


//////////////////////////////////////////////////////////////////////
// クラス ComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
ComplexHandler::ComplexHandler(DotlibParser& parser) :
  CGHandler(parser)
{
}

// @brief デストラクタ
ComplexHandler::~ComplexHandler()
{
}

// @brief Complex Attribute を読み込む．
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
ComplexHandler::parse_complex_attribute()
{
  return parser().parse_complex_attribute(*this);
}


//////////////////////////////////////////////////////////////////////
// クラス GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
GroupHandler::GroupHandler(DotlibParser& parser) :
  CGHandler(parser)
{
}

// @brief デストラクタ
GroupHandler::~GroupHandler()
{
}

// @brief Group Statement を読み込む．
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
bool
GroupHandler::parse_group_statement()
{
  return parser().parse_group_statement(*this);
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
