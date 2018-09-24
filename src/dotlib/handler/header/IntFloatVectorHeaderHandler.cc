
/// @file IntFloatVectorHeaderHandler.cc
/// @brief IntFloatVectorHeaderHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/IntFloatVectorHeaderHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IntFloatVectorHeaderHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntFloatVectorHeaderHandler::IntFloatVectorHeaderHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
IntFloatVectorHeaderHandler::~IntFloatVectorHeaderHandler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
IntFloatVectorHeaderHandler::begin_header()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
IntFloatVectorHeaderHandler::read_header_value(TokenType value_type,
					       const FileRegion& value_loc,
					       int count)
{
  switch ( count ) {
  case 0:
    mValue1 = new_int(value_type, value_loc);
    return mValue1 != nullptr;

  case 1:
    mValue2 = new_float_vector(value_type, value_loc);
    return mValue2 != nullptr;

  default:
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, singleton expected.");
    return false;
  }
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
IntFloatVectorHeaderHandler::end_header(int count)
{
  if ( count != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, ( integer, \"float, float, ...\" ) type expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
