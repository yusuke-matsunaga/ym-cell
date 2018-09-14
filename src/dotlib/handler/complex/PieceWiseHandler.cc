
/// @file PieceWiseHandler.cc
/// @brief PieceWiseHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/PieceWiseHandler.h"
#include "dotlib/TokenType.h"
#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス PieceWiseHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PieceWiseHandler::PieceWiseHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
PieceWiseHandler::~PieceWiseHandler()
{
}

// @brief 'piece_wise' Complex Attribute の記述をパースする．
// @param[in] dst_list 読み込んだ値を格納するリスト
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
PieceWiseHandler::parse_value(vector<const AstPieceWise*>& dst_list)
{
  bool stat = parse_complex_attribute();
  if ( stat ) {
    dst_list.push_back(mValue);
  }
  return stat;
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
PieceWiseHandler::begin_header()
{
  mValue = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
PieceWiseHandler::read_header_value(TokenType value_type,
				    const FileRegion& value_loc,
				    int count)
{
  switch ( count ) {
  case 0:
    if ( value_type != TokenType::INT_NUM ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error, first element should be an integer number.");
      return false;
    }
    else {
      mVal1 = cur_int();
      return true;
    }
    break;

  case 1:
    if ( value_type != TokenType::INT_NUM && value_type != TokenType::FLOAT_NUM ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      value_loc,
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      "Syntax error, second element should be a float number.");
      return false;
    }
    else {
      mVal2 = cur_float();
      return true;
    }
    break;

  default:
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, (integer, float) pair expected.");
    return false;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] header_loc '(' から ')' までのファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
PieceWiseHandler::end_header(const FileRegion& header_loc,
			     int count)
{
  if ( count != 2 ) {
    mValue = nullptr;
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, (integer, float) pair expected.");
    return false;
  }
  else {
    mValue = mgr().new_piecewise(header_loc, mVal1, mVal2);
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
