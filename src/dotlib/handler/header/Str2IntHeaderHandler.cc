
/// @file Str2IntHeaderHandler.cc
/// @brief Str2IntHeaderHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Str2IntHeaderHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Str2IntHeaderHandler
//////////////////////////////////////////////////////////////////////

// @brief ハンドラ用のコンストラクタ
// @param[in] parser パーサー
Str2IntHeaderHandler::Str2IntHeaderHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
Str2IntHeaderHandler::~Str2IntHeaderHandler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
Str2IntHeaderHandler::begin_header()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
  mValue3 = nullptr;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Str2IntHeaderHandler::read_header_value(TokenType value_type,
				       const FileRegion& value_loc,
				       int count)
{
  switch ( count ) {
  case 0:
    mValue1 = new_string(value_type, value_loc);
    return mValue1 != nullptr;

  case 1:
    mValue2 = new_string(value_type, value_loc);
    return mValue2 != nullptr;

  case 2:
    mValue3 = new_int(value_type, value_loc);
    return mValue3 != nullptr;

  default:
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "syntax error, wrong # of parameters.");
    return false;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
Str2IntHeaderHandler::end_header(int count)
{
  if ( count != 3 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "( string, string, int )-type parameters are expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
