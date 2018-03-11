
/// @file DotlibHandler.cc
/// @brief DotlibHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"
#include "dotlib/DotlibParserImpl.h"
#include "dotlib/DotlibMgrImpl.h"
#include "GroupHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibHandler
//////////////////////////////////////////////////////////////////////

// @brief 親のハンドラを持たない場合のコンストラクタ
// @param[in] parser パーサー
DotlibHandler::DotlibHandler(DotlibParserImpl& parser) :
  mParser(parser),
  mParent(nullptr)
{
}

// @brief 親のハンドラを持つ場合のコンストラクタ
// @param[in] parent 親のハンドラ
DotlibHandler::DotlibHandler(GroupHandler* parent) :
  mParser(parent->parser()),
  mParent(parent)
{
}

// @brief デストラクタ
DotlibHandler::~DotlibHandler()
{
}

// @brief group attribute 用のパースを行う．
// @param[in] vector_mode ベクタモードの時 true にするフラグ
// @param[out] end_loc 右括弧の位置を格納する変数
// @return 読み込んだ値(リスト)を返す．
//
// エラーが起きたら nullptr を返す．
DotlibList*
DotlibHandler::parse_complex(bool vector_mode,
			     FileRegion& end_loc)
{
  if ( !expect(LP) ) {
    return nullptr;
  }

  vector<const DotlibNode*> tmp_list;
  FileRegion loc;
  TokenType type = parser().read_token(loc);
  if ( type != RP ) {
    for ( ; ; ) {
      DotlibNode* value = new_value(loc, type, vector_mode);
      if ( value == nullptr ) {
	return nullptr;
      }

      tmp_list.push_back(value);

      TokenType type1 = parser().read_token(loc);
      if ( type1 == RP ) {
	break;
      }
      if ( type1 != COMMA ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			loc,
			kMsgError,
			"DOTLIB_PARSER",
			"syntax error. ',' is expected.");
	return nullptr;
      }
      type = parser().read_token(loc);
    }
  }
  end_loc = loc;

  return mgr()->new_list(tmp_list);
}

// @brief DotlibNode を生成する．
// @param[in] loc ファイル上の位置情報
// @param[in] vector_mode ベクタモードの時 true にするフラグ
// @param[in] type 型
DotlibNode*
DotlibHandler::new_value(const FileRegion& loc,
			 TokenType type,
			 bool vector_mode)
{
  switch ( type ) {
  case INT_NUM:
    return mgr()->new_int(loc, parser().cur_int());

  case FLOAT_NUM:
    return mgr()->new_float(loc, parser().cur_float());

  case SYMBOL:
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
			    kMsgError,
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
      return mgr()->new_vector(loc, value_list);
    }
    else {
      return mgr()->new_string(loc, ShString(parser().cur_string()));
    }

  default:
    break;
  }
  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc,
		  kMsgError,
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
DotlibParserImpl&
DotlibHandler::parser()
{
  return mParser;
}

// @brief DotlibMgrImpl* を得る．
DotlibMgrImpl*
DotlibHandler::mgr()
{
  return mParser.mgr();
}

// @brief 親のハンドラを得る．
GroupHandler*
DotlibHandler::parent()
{
  return mParent;
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
  case COLON:      type_str = "':'"; break;
  case SEMI:       type_str = "';'"; break;
  case COMMA:      type_str = "','"; break;
  case PLUS:       type_str = "'+'"; break;
  case MINUS:      type_str = "'-'"; break;
  case MULT:       type_str = "'*'"; break;
  case DIV:        type_str = "'/'"; break;
  case LP:         type_str = "'('"; break;
  case RP:         type_str = "')'"; break;
  case LCB:        type_str = "'{'"; break;
  case RCB:        type_str = "'}'"; break;
  case INT_NUM:    type_str = "INT"; break;
  case FLOAT_NUM:  type_str = "FLOAT"; break;
  case SYMBOL:     type_str = "SYMBOL"; break;
  case EXPRESSION: type_str = "EXPRESSION"; break;
  case NL:         type_str = "new-line"; break;
  case ERROR :     type_str = "error"; break;
  case END:        type_str = "end-of-file"; break;
  default:
    ASSERT_NOT_REACHED;
  }
  s << type_str;
  return s;
}

END_NAMESPACE_YM_DOTLIB
