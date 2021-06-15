
/// @file StrFloatHandler.cc
/// @brief StrFloatHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/StrFloatHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス StrFloatHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
StrFloatHandler::StrFloatHandler(DotlibParser& parser) :
  ElemHandler(parser, 2)
{
}

// @brief デストラクタ
StrFloatHandler::~StrFloatHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
StrFloatHandler::initialize()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
StrFloatHandler::read_value(int count)
{
  if ( count == 0 ) {
    mValue1 = parser().read_string();
    return mValue1 != nullptr;
  }
  else {
    mValue2 = parser().read_float();
    return mValue2 != nullptr;
  }
}

// @brief end_header() 内で呼ばれる終了処理関数
void
StrFloatHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
