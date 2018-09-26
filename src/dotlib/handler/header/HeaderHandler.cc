
/// @file HeaderHandler.cc
/// @brief HeaderHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス HeaderHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
HeaderHandler::HeaderHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
HeaderHandler::~HeaderHandler()
{
}

// @brief ヘッダの開始処理
// @param[in] loc '(' のファイル上の位置
//
// '(' を読み込んだ時に呼ばれる．
void
HeaderHandler::begin_header(const FileRegion& loc)
{
  mFirstLoc = loc;
  _begin_header();
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_header_value() の呼ばれた回数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
HeaderHandler::read_header_value(int count)
{
  return _read_header_value(count);
}

// @brief 読み込みが終了した時の処理を行う．
// @param[in] loc ')' のファイル上の位置
// @param[in] count 読み込んだ要素数
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
//
// ')' を読み込んだ直後に呼ばれる．
bool
HeaderHandler::end_header(const FileRegion& loc,
			  int count)
{
  mLastLoc = loc;
  return _end_header(count);
}

END_NAMESPACE_YM_DOTLIB
