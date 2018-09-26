
/// @file DotlibParser_simple.cc
/// @brief DotlibParser の実装ファイル ( simple attribute 関連 )
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 直前に読んだトークンから AstInt を生成する．
// @param[out] dst 結果を格納する変数
// @retval true 読み込みが成功した．
// @retval false 読み込みが失敗した．
bool
DotlibParser::read_int(const AstInt*& dst)
{
  FileRegion value_loc;
  TokenType value_type = read_token(value_loc, false);
  if ( value_type == TokenType::INT_NUM ) {
    dst = mgr().new_int(value_loc, cur_int());
    return true;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'integer' value is expected.");
    return false;
  }
}

// @brief 直前に読んだトークンから AstFloat を生成する．
// @param[out] dst 結果を格納する変数
// @retval true 読み込みが成功した．
// @retval false 読み込みが失敗した．
bool
DotlibParser::read_float(const AstFloat*& dst)
{
  FileRegion value_loc;
  TokenType value_type = read_token(value_loc, false);
  // int 型も float 型とみなす．
  if ( value_type == TokenType::FLOAT_NUM || value_type == TokenType::INT_NUM ) {
    dst = mgr().new_float(value_loc, cur_float());
    return true;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'float' value is expected.");
    return false;
  }
}

// @brief 直前に読んだトークンから文字列を取り出す．
// @param[out] dst 結果を格納する変数
// @param[out] value_loc トークンのファイル上の位置
// @retval true 読み込みが成功した．
// @retval false 読み込みが失敗した．
bool
DotlibParser::read_raw_string(const char*& dst,
			      FileRegion& value_loc)
{
  TokenType value_type = read_token(value_loc, true);
  if ( value_type == TokenType::SYMBOL ) {
    dst = cur_string();
    return true;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return false;
  }
}

// @brief 直前に読んだトークンから AstString を生成する．
// @param[out] dst 結果を格納する変数
// @retval true 読み込みが成功した．
// @retval false 読み込みが失敗した．
bool
DotlibParser::read_string(const AstString*& dst)
{
  const char* tmp_str;
  FileRegion value_loc;
  bool stat = read_raw_string(tmp_str, value_loc);
  if ( stat ) {
    dst = mgr().new_string(value_loc, ShString(tmp_str));
    return true;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. 'string' value is expected.");
    return false;
  }
}

// @brief 直前に読んだトークンから AstIntVector を生成する．
// @param[out] dst 結果を格納する変数
// @retval true 読み込みが成功した．
// @retval false 読み込みが失敗した．
bool
DotlibParser::read_int_vector(const AstIntVector*& dst)
{
  const char* tmp_str;
  FileRegion value_loc;
  bool stat = read_raw_string(tmp_str, value_loc);
  vector<int> dst_list;
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

  dst = mgr().new_int_vector(value_loc, dst_list);

  return true;
}

// @brief 直前に読んだトークンから AstFloatVector を生成する．
// @param[out] dst 結果を格納する変数
// @retval true 読み込みが成功した．
// @retval false 読み込みが失敗した．
bool
DotlibParser::read_float_vector(const AstFloatVector*& dst)
{
  FileRegion value_loc;
  vector<double> dst_list;
  bool stat = read_float_vector(value_loc, dst_list);
  if ( stat ) {
    dst = mgr().new_float_vector(value_loc, dst_list);
  }
  return stat;
}

// @brief 直前に読んだトークンから float のリストを生成する．
// @param[int] dst_list 値を格納するリスト
// @retval true 正しく読み込んだ．
// @retval false エラーが起こった．
//
// dst_list は初期化せず，末尾に追加する．
bool
DotlibParser::read_float_vector(FileRegion& value_loc,
				vector<double>& dst_list)
{
  TokenType value_type = read_token(value_loc, false);
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
