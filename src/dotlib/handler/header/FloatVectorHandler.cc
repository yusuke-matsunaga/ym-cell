
/// @file FloatVectorHandler.cc
/// @brief FloatVectorHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/FloatVectorHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FloatVectorHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FloatVectorHandler::FloatVectorHandler(DotlibParser& parser) :
  ElemHandler(parser, 1)
{
}

// @brief デストラクタ
FloatVectorHandler::~FloatVectorHandler()
{
}

// @brief begin_header() 内で呼ばれる初期化関数
void
FloatVectorHandler::initialize()
{
  mValueList.clear();
}

// @brief ヘッダの値を読み込む処理
// @param[in] count read_value() の呼ばれた回数
bool
FloatVectorHandler::read_value(int count)
{
  FileRegion loc;
  return parser().read_float_vector(loc, mValueList);
}

// @brief end_header() 内で呼ばれる終了処理関数
void
FloatVectorHandler::finalize()
{
}

END_NAMESPACE_YM_DOTLIB
