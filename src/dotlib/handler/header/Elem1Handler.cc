
/// @file Elem1Handler.cc
/// @brief Elem1Handler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Elem1Handler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Elem1Handler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
Elem1Handler::Elem1Handler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
Elem1Handler::~Elem1Handler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
Elem1Handler::begin_header()
{
  initialize();
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Elem1Handler::read_header_value(TokenType value_type,
				const FileRegion& value_loc,
				int count)
{
  switch ( count ) {
  case 0:
    return read_header_value1(value_type, value_loc);

  default:
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error.");
    return false;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
Elem1Handler::end_header(int count)
{
  if ( count != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
