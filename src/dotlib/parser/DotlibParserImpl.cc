
/// @file DotlibParserImpl.cc
/// @brief DotlibParserImpl の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibParserImpl.h"
#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/DotlibHandler.h"
#include "dotlib/HandlerFactory.h"
#include "ym/FileIDO.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief コンストラクタ
DotlibParserImpl::DotlibParserImpl() :
  mDotlibMgr(nullptr),
  mLibraryHandler( HandlerFactory::new_library(*this) )
{
  mScanner = nullptr;
}

// デストラクタ
DotlibParserImpl::~DotlibParserImpl()
{
  delete mLibraryHandler;
  delete mScanner;
}

// @brief ファイルを読み込む．
// @param[in] filename ファイル名
// @param[in] mgr DotlibNode を管理するオブジェクト
// @param[in] debug デバッグモード
// @param[in] allow_no_semi 行末のセミコロンなしを許すかどうか
// @return 読み込んだ AST を返す．
//
// エラーが起きたら nullptr を返す．
const DotlibLibrary*
DotlibParserImpl::read_file(const string& filename,
			    DotlibMgrImpl* mgr,
			    bool debug,
			    bool allow_no_semi)
{
  mDotlibMgr = mgr;
  mDebug = debug;
  mAllowNoSemi = allow_no_semi;

  FileIDO ido;
  if ( !ido.open(filename) ) {
    ostringstream buf;
    buf << filename << ": Could not open.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(),
		    kMsgFailure,
		    "DOTLIB_PARSER",
		    buf.str());
    return nullptr;
  }

  mScanner = new DotlibScanner(ido);

  bool error = false;
  TokenType type;
  FileRegion loc;
  // 空行を読み飛ばす．
  for ( type = read_token(loc); type == NL; type = read_token(loc) ) { }

  // 先頭のトークンが "library" であるかチェックする．
  if ( type != SYMBOL || strcmp(cur_string(), "library") != 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "'library' keyword is expected "
		    "on the top of the structure");
    error = true;
    goto last;
  }

  if ( !mLibraryHandler->read_attr(ATTR_LIBRARY, loc) ) {
    error = true;
    goto last;
  }

  if ( !expect_nl() ) {
    error = true;
    goto last;
  }
  for ( ; ; ) {
    TokenType type = read_token(loc);
    if ( type == END ) {
      break;
    }
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgWarning,
		    "DOTLIB_PARSER",
		    "contents after library group are ignored.");
  }

 last:
  delete mScanner;
  mScanner = nullptr;

  if ( error ) {
    return nullptr;
  }

#warning "TODO: 未完"
  return nullptr;
}

// @brief 引数の種類のトークンでなければエラーメッセージを出力する．
bool
DotlibParserImpl::expect(TokenType req_type)
{
  FileRegion loc;
  TokenType type = read_token(loc);
  if ( type == req_type ) {
    return true;
  }

  const char* type_str = nullptr;
  switch ( req_type ) {
  case COLON:      type_str = "':'"; break;
  case SEMI:       type_str = "';'"; break;
  case COMMA:      type_str = "','"; break;
  case PLUS:       type_str = "'+'"; break;
  case MINUS:      type_str = "'-'"; break;
  case MULT:       type_str = "'*'"; break;
  case DIV:        type_str = "'/'"; break;
  case NOT:        type_str = "'!'"; break;
  case AND:        type_str = "'&'"; break;
  case OR:         type_str = "'|'"; break;
  case XOR:        type_str = "'^'"; break;
  case PRIME:      type_str = "'"; break;
  case LP:         type_str = "'('"; break;
  case RP:         type_str = "')'"; break;
  case LCB:        type_str = "'{'"; break;
  case RCB:        type_str = "'}'"; break;
  case SYMBOL:     type_str = "STR"; break;
  case INT_NUM:    type_str = "INT"; break;
  case FLOAT_NUM:  type_str = "FLOAT"; break;
  case EXPRESSION: type_str = "EXPRESSION"; break;
  case NL:         type_str = "new-line"; break;
  default:         ASSERT_NOT_REACHED;
  }
  ostringstream buf;
  buf << "syntax error. " << type_str << " is expected.";
  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  kMsgError,
		  "DOTLIB_PARSER",
		  buf.str());
  return false;
}

// @brief 行末まで読み込む．
bool
DotlibParserImpl::expect_nl()
{
  if ( mAllowNoSemi ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == SEMI ) {
      type = read_token(loc);
    }
    if ( type == NL || type == END ) {
      return true;
    }
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. Semicolon is expected.");
    return false;
  }
  else {
    if ( !expect(SEMI) ) {
      return false;
    }
    if ( !expect(NL) ) {
      return false;
    }
  }
  return true;
}

// @brief 文字列を属性値に変換する．
AttrType
DotlibParserImpl::conv_to_attr(const char* str)
{
  return mAttrDic.get(str);
}

// @brief デバッグモードの時 true を返す．
bool
DotlibParserImpl::debug()
{
  return mDebug;
}

END_NAMESPACE_YM_DOTLIB
