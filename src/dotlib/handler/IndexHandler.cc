
/// @file IndexHandler.cc
/// @brief IndexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "IndexHandler.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IndexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IndexHandler::IndexHandler(DotlibParser& parser) :
  ComplexHandler(parser)
{
  clear_value();
}

// @brief デストラクタ
IndexHandler::~IndexHandler()
{
}

// @brief 値をクリアする．
void
IndexHandler::clear_value()
{
  mValue = nullptr;
}

// @brief 読み込んだ値を返す．
const AstFloatVector*
IndexHandler::value() const
{
  return mValue;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
IndexHandler::begin_header()
{
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
IndexHandler::read_value(TokenType value_type,
			 const FileRegion& value_loc,
			 int count)
{
#warning "value_type を無視していいの？"

  if ( count != 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, singleton expected.");
    return false;
  }

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
			value_loc,
			MsgType::Error,
			"DOTLIB_PARSER",
			"Syntax error. Null element.");
	return false;
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

  mValue = mgr().new_vector(value_loc, value_list);

  return true;
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
IndexHandler::end_header(const FileRegion& header_loc,
			 int count)
{
  if ( count != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, singleton expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
