
/// @file IntVectorHeaderHandler.cc
/// @brief IntVectorHeaderHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/IntVectorHeaderHandler.h"
//#include "dotlib/DotlibParser.h"
#include "dotlib/AstMgr.h"
//#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IntVectorHeaderHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntVectorHeaderHandler::IntVectorHeaderHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
IntVectorHeaderHandler::~IntVectorHeaderHandler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
IntVectorHeaderHandler::begin_header()
{
  mValue = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
IntVectorHeaderHandler::read_header_value(TokenType value_type,
					    const FileRegion& value_loc,
					    int count)
{
  switch ( count ) {
  case 0:
    // 実際の処理は最後でする．
    break;

  default:
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, singleton expected.");
    return false;
  }

  vector<int> value_list;
  bool stat = read_int_vector(value_type, value_loc, value_list);
  if ( stat ) {
    mValue = mgr().new_float_vector(value_loc, value_list);
  }
  return stat;
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
IntVectorHeaderHandler::end_header(int count)
{
  if ( count != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    header_loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, singleton expected.");
    return false;
  }
  else {
    return true;
  }
}

END_NAMESPACE_YM_DOTLIB
