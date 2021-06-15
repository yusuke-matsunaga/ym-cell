
/// @file IntVectorHandler.cc
/// @brief IntVectorHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/IntVectorHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IntVectorHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IntVectorHandler::IntVectorHandler(DotlibParser& parser) :
  ElemHandler(parser, 1)
{
}

// @brief デストラクタ
IntVectorHandler::~IntVectorHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
IntVectorHandler::initialize()
{
  mValue = nullptr;
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
IntVectorHandler::read_value(int count)
{
  mValue = parser().read_int_vector();
  return mValue != nullptr;
}

// @brief end_header() 内で呼ばれる終了処理関数
void
IntVectorHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
