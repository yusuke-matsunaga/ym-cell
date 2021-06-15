
/// @file FloatFloatHandler.cc
/// @brief FloatFloatHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FloatFloatHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FloatFloatHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatFloatHandler::FloatFloatHandler(DotlibParser& parser) :
  ElemHandler(parser, 2)
{
}

// @brief デストラクタ
FloatFloatHandler::~FloatFloatHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
FloatFloatHandler::initialize()
{
  mValue[0] = nullptr;
  mValue[1] = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
FloatFloatHandler::read_value(int count)
{
  ASSERT_COND( count == 0 || count == 1 );

  auto tmp = parser().read_float();
  if ( tmp ) {
    mValue[count] = tmp;
    return true;
  }
  else {
    return false;
  }
}

// @brief end_header() 内で呼ばれる終了処理関数
void
FloatFloatHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
