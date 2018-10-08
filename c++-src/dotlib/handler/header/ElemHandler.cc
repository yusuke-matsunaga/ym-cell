
/// @file ElemHandler.cc
/// @brief ElemHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/ElemHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス ElemHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
// @param[in] num ヘッダ内の要素数
ElemHandler::ElemHandler(DotlibParser& parser,
			 int num) :
  HeaderHandler(parser),
  mNum(num)
{
}

// @brief デストラクタ
ElemHandler::~ElemHandler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
ElemHandler::_begin_header()
{
  initialize();
}

// @brief 値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
ElemHandler::_read_header_value(int count)
{
  if ( count >= 0 && count < mNum ) {
    return read_value(count);
  }
  else {
    return false;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
ElemHandler::_end_header(int count)
{
  if ( count != mNum ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    FileRegion(first_loc(), last_loc()),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error.");
    return false;
  }
  else {
    finalize();
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
