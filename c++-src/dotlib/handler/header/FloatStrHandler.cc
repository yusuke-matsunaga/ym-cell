
/// @file FloatStrHandler.cc
/// @brief FloatStrHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FloatStrHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FloatStrHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatStrHandler::FloatStrHandler(DotlibParser& parser) :
  ElemHandler(parser, 2)
{
}

// @brief デストラクタ
FloatStrHandler::~FloatStrHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
FloatStrHandler::initialize()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
FloatStrHandler::read_value(int count)
{
  if ( count == 0 ) {
    mValue1 = parser().read_float();
    return mValue1 != nullptr;
  }
  else {
    mValue2 = parser().read_string();
    return mValue2 != nullptr;
  }
}

// @brief end_header() 内で呼ばれる終了処理関数
void
FloatStrHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
