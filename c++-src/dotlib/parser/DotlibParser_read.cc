
/// @file DotlibParser_simple.cc
/// @brief DotlibParser の実装ファイル ( simple attribute 関連 )
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 直前に読んだトークンから AstInt を生成する．
const AstInt*
DotlibParser::read_int()
{
  FileRegion value_loc;
  TokenType value_type = read_token(value_loc, false);
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
const AstFloat*
DotlibParser::read_float()
{
  FileRegion value_loc;
  TokenType value_type = read_token(value_loc, false);
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

// @brief 直前に読んだトークンから文字列を取り出す．
const char*
DotlibParser::read_raw_string(FileRegion& value_loc)
{
  TokenType value_type = read_token(value_loc, true);
  if ( value_type == TokenType::SYMBOL ) {
    return cur_string();
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

// @brief 直前に読んだトークンから AstString を生成する．
const AstString*
DotlibParser::read_string()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  if ( tmp_str ) {
    return mgr().new_string(value_loc, ShString(tmp_str));
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
const AstIntVector*
DotlibParser::read_int_vector()
{
  FileRegion value_loc;
  auto tmp_str = read_raw_string(value_loc);
  if ( tmp_str == nullptr ) {
    return nullptr;
  }

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
const AstFloatVector*
DotlibParser::read_float_vector()
{
  FileRegion value_loc;
  vector<double> dst_list;
  bool stat = read_float_vector(dst_list, value_loc);
  if ( stat ) {
    return mgr().new_float_vector(value_loc, dst_list);
  }
  else {
    return nullptr;
  }
}

// @brief 直前に読んだトークンから float のリストを生成する．
// @retval true 正しく読み込んだ．
// @retval false エラーが起こった．
//
// dst_list は初期化せず，末尾に追加する．
bool
DotlibParser::read_float_vector(vector<double>& dst_list,
				FileRegion& value_loc)
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

// @brief primary を読み込む．
const AstExpr*
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
const AstExpr*
DotlibParser::read_product()
{
  const AstExpr* opr1 = read_primary();
  if ( opr1 == nullptr ) {
    return nullptr;
  }

  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == TokenType::MULT || type == TokenType::DIV ) {
      const AstExpr* opr2 = read_primary();
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
      unget_token(type, loc);
      return opr1;
    }
  }
}

// @brief expression を読み込む．
const AstExpr*
DotlibParser::read_expr(TokenType end_marker)
{
  const AstExpr* opr1 = read_product();
  if ( opr1 == nullptr ) {
    return nullptr;
  }
  for ( ; ; ) {
    FileRegion loc;
    TokenType type = read_token(loc);
    if ( type == end_marker ) {
      return opr1;
    }
    if ( type == TokenType::PLUS || type == TokenType::MINUS ) {
      const AstExpr* opr2 = read_product();
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

END_NAMESPACE_YM_DOTLIB
