
/// @file DotlibHandler.cc
/// @brief DotlibHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
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

// @brief 直前に読んだトークンから AstInt を生成する．
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
//
// 形が異なっていたらエラーメッセージを出力して nullptr を返す．
const AstInt*
DotlibHandler::new_int(TokenType value_type,
		       const FileRegion& value_loc)
{
  if ( value_type == TokenType::INT_NUM ) {
    return mgr().new_int(value_loc, cur_int());
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'integer' value is expected.");
    return nullptr;
  }
}

// @brief 直前に読んだトークンから AstFloat を生成する．
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
//
// 形が異なっていたらエラーメッセージを出力して nullpgr を返す．
const AstFloat*
DotlibHandler::new_float(TokenType value_type,
			 const FileRegion& value_loc)
{
  // int 型も float 型とみなす．
  if ( value_type == TokenType::FLOAT_NUM || value_type == TokenType::INT_NUM ) {
    return mgr().new_float(value_loc, cur_float());
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'float' value is expected.");
    return nullptr;
  }
}

// @brief 直前に読んだトークンから AstString を生成する．
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
//
// 形が異なっていたらエラーメッセージを出力して nullpgr を返す．
const AstString*
DotlibHandler::new_string(TokenType value_type,
			  const FileRegion& value_loc)
{
  if ( value_type == TokenType::SYMBOL ) {
    return mgr().new_string(value_loc, ShString(cur_string()));
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return nullptr;
  }
}

// @brief 直前に読んだトークンから AstIntVector を生成する．
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
const AstIntVector*
DotlibHandler::new_int_vector(TokenType value_type,
			      const FileRegion& value_loc)
{
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return nullptr;
  }

  vector<int> dst_list;
  const char* tmp_str = cur_string();
  string buf;
  char c = '\0';
  for ( const char* s = tmp_str; (c = *s) ; ++ s ) {
    if ( isspace(c) ) {
      continue;
    }
    else if ( c == ',' ) {
      if ( buf.size() == 0 ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. Null element.");
	return nullptr;
      }
      dst_list.push_back(atoi(buf.c_str()));
      buf.clear();
    }
    else {
      buf += c;
    }
  }
  if ( buf.size() > 0 ) {
    dst_list.push_back(atoi(buf.c_str()));
  }

  return mgr().new_int_vector(value_loc, dst_list);
}

// @brief 直前に読んだトークンから AstFloatVector を生成する．
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
const AstFloatVector*
DotlibHandler::new_float_vector(TokenType value_type,
				const FileRegion& value_loc)
{
  vector<double> dst_list;
  bool stat = read_float_vector(value_type, value_loc, dst_list);
  if ( stat ) {
    return mgr().new_float_vector(value_loc, dst_list);
  }
  else {
    return nullptr;
  }
}

// @brief 直前に読んだトークンから float のリストを生成する．
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[int] dst_list 値を格納するリスト
// @retval true 正しく読み込んだ．
// @retval false エラーが起こった．
//
// dst_list は初期化せず，末尾に追加する．
bool
DotlibHandler::read_float_vector(TokenType value_type,
				 const FileRegion& value_loc,
				 vector<double>& dst_list)
{
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return false;
  }

  const char* tmp_str = cur_string();
  string buf;
  char c = '\0';
  for ( const char* s = tmp_str; (c = *s) ; ++ s ) {
    if ( isspace(c) ) {
      continue;
    }
    else if ( c == ',' ) {
      if ( buf.size() == 0 ) {
	MsgMgr::put_msg(__FILE__, __LINE__,
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. Null element.");
	return false;
      }
      dst_list.push_back(strtod(buf.c_str(), nullptr));
      buf.clear();
    }
    else {
      buf += c;
    }
  }
  if ( buf.size() > 0 ) {
    dst_list.push_back(strtod(buf.c_str(), nullptr));
  }

  return true;
}

END_NAMESPACE_YM_DOTLIB
