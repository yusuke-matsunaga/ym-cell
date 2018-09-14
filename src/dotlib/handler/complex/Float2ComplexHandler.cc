
/// @file Float2HeaderHandler.cc
/// @brief Float2HeaderHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/Float2HeaderHandler.h"
#include "dotlib/AstMgr.h"
#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Float2HeaderHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
Float2HeaderHandler::Float2HeaderHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
Float2HeaderHandler::~Float2HeaderHandler()
{
}

// @brief 1つの文字列型を取る complex attribute の記述をパースする．
// @param[in] dst1, dst2 結果を格納する変数
// @retval true 正しくパースした．
// @retval false エラーが怒った．
//
bool
Float2HeaderHandler::parse_value(const AstFloat*& dst1,
				 const AstFloat*& dst2)
{
  bool stat = parse_complex_attribute();
  if ( stat ) {
    dst1 = mValue1;
    dst2 = mValue2;
  }
  return stat;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
Float2HeaderHandler::begin_header()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
Float2HeaderHandler::read_header_value(TokenType value_type,
					const FileRegion& value_loc,
					int count)
{
  switch ( count ) {
  case 0:
    if ( value_type != TokenType::INT_NUM && value_type != TokenType::FLOAT_NUM ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error, first element should be a float number");
      return false;
    }
    mValue1 = mgr().new_float(value_loc, cur_float());
    return true;

  case 1:
    if ( value_type != TokenType::INT_NUM && value_type != TokenType::FLOAT_NUM ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error, second element should be a float number");
      return false;
    }
    mValue2 = mgr().new_float(value_loc, cur_float());
    return true;

  default:
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error");
    return false;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
Float2HeaderHandler::end_header(const FileRegion& header_loc,
				int count)
{
  if ( count != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
