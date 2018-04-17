
/// @file CGHandler.cc
/// @brief CGHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "CGHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス CGHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
CGHandler::CGHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
CGHandler::~CGHandler()
{
}

// @brief 構文要素を処理する．
// @param[in] attr_type 属性
// @param[in] attr_loc ファイル上の位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
CGHandler::parse_header()
{
  if ( !expect(TokenType::LP) ) {
    return false;
  }

  begin_header();

  FileRegion first_loc = parser().cur_loc();

  FileRegion loc;
  TokenType type = parser().read_token(loc);
  int count = 0;
  if ( type != TokenType::RP ) {
    for ( ; ; ) {
      if ( !read_value(type, loc, count) ) {
	return false;
      }
      ++ count;

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

  if ( !end_header(attr_type, attr_loc, FileRegion(first_loc, loc), count) ) {
    return false;
  }

  return true;
}

END_NAMESPACE_YM_DOTLIB
