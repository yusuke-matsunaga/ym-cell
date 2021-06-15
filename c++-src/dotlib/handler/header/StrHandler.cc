
/// @file StrHandler.cc
/// @brief StrHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrHandler::StrHandler(DotlibParser& parser) :
  ElemHandler(parser, 1)
{
}

// @brief デストラクタ
StrHandler::~StrHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
StrHandler::initialize()
{
  mValue = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
StrHandler::read_value(int count)
{
  mValue = parser().read_string();
  return mValue != nullptr;
}

// @brief end_header() 内で呼ばれる終了処理関数
void
StrHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
