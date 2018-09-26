
/// @file StrListHandler.cc
/// @brief StrListHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrListHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrListHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrListHandler::StrListHandler(DotlibParser& parser) :
  HeaderHandler(parser)
{
}

// @brief デストラクタ
StrListHandler::~StrListHandler()
{
}

// @brief ヘッダの開始処理
//
// '(' を読み込んだ時に呼ばれる．
void
StrListHandler::_begin_header()
{
  mValue.clear();
}

// @brief 値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
StrListHandler::_read_header_value(int count)
{
  const AstString* str;
  bool stat = parser().read_string(str);
  if ( stat ) {
    mValue.push_back(str);
  }
  return stat;
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
StrListHandler::_end_header(int count)
{
  return true;
}

END_NAMESPACE_YM_DOTLIB
