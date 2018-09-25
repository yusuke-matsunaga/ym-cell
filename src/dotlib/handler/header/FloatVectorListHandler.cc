
/// @file FloatVectorListHandler.cc
/// @brief FloatVectorListHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/FloatVectorListHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FloatVectorListHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
/// @param[in] parser パーサー
FloatVectorListHandler::FloatVectorListHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
FloatVectorListHandler::~FloatVectorListHandler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
FloatVectorListHandler::begin_header()
{
  mValueList.clear();
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
FloatVectorListHandler::read_header_value(TokenType value_type,
					  const FileRegion& value_loc,
					  int count)
{
  return read_float_vector(value_type, value_loc, mValueList);
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
FloatVectorListHandler::end_header(int count)
{
  if ( count == 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, list of one ore more vectors expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
