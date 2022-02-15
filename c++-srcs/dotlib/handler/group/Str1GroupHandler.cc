
/// @file Str1GroupHandler.cc
/// @brief Str1GroupHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Str1GroupHandler.h"
#include "dotlib/Parser.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Str1GroupHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
Str1GroupHandler::Str1GroupHandler(Parser& parser) :
  GroupHandler(parser)
{
}

// @brief デストラクタ
Str1GroupHandler::~Str1GroupHandler()
{
}

// @brief ヘッダの値を取り出す．
const AstString*
Str1GroupHandler::header_value() const
{
  return mHeaderValue;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
Str1GroupHandler::begin_header()
{
  mHeaderValue = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Str1GroupHandler::read_header_value(TokenType value_type,
				    const FileRegion& value_loc,
				    int count)
{
  if ( count != 0 || value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  else {
    mHeaderValue = mgr().new_string(value_loc, ShString(cur_string()));
    return true;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
Str1GroupHandler::end_header(const FileRegion& header_loc,
			     int count)
{
  if ( count != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "string value is expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
