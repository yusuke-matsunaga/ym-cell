
/// @file StrListHeaderHandler.cc
/// @brief StrListHeaderHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrListHeaderHandler.h"
//#include "dotlib/AstMgr.h"
//#include "dotlib/TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrListHeaderHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrListHeaderHandler::StrListHeaderHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
StrListHeaderHandler::~StrListHeaderHandler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
StrListHeaderHandler::begin_header()
{
  mValue.clear();
}

// @brief 値を読み込む処理
// @param[in] value_type 型
// @param[in] value_loc トークンの位置
// @param[in] count read_value() の呼ばれた回数
bool
StrListHeaderHandler::read_header_value(TokenType value_type,
					const FileRegion& value_loc,
					int count)
{
  const AstString* str = new_string(value_type, value_loc);
  if ( str != nullptr ) {
    mValue.push_back(str);
    return true;
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
StrListHeaderHandler::end_header(int count)
{
  return true;
}

END_NAMESPACE_YM_DOTLIB
