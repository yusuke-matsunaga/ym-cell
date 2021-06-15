
/// @file IntFloatVectorHandler.cc
/// @brief IntFloatVectorHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/IntFloatVectorHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IntFloatVectorHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntFloatVectorHandler::IntFloatVectorHandler(DotlibParser& parser) :
  ElemHandler(parser, 2)
{
}

// @brief デストラクタ
IntFloatVectorHandler::~IntFloatVectorHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
IntFloatVectorHandler::initialize()
{
  mValue1 = nullptr;
  mValue2 = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
IntFloatVectorHandler::read_value(int count)
{
  if ( count == 0 ) {
    mValue1 = parser().read_int();
    return mValue1 != nullptr;
  }
  else {
    mValue2 = parser().read_float_vector();
    return mValue2 != nullptr;
  }
}

// @brief end_header() 内で呼ばれる終了処理関数
void
IntFloatVectorHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
