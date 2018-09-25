
/// @file EmptyHandler.cc
/// @brief EmptyHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/EmptyHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス EmptyHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
EmptyHandler::EmptyHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
EmptyHandler::~EmptyHandler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
EmptyHandler::begin_header()
{
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
EmptyHandler::read_header_value(TokenType value_type,
				const FileRegion& value_loc,
				int count)
{
  MsgMgr::put_msg(__FILE__, __LINE__,
		  value_loc,
		  MsgType::Error,
		  "DOTLIB_PARSER",
		  "Empty header block is expected");
  return false;
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
EmptyHandler::end_header(int count)
{
  if ( count > 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Empty header block is expected");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
