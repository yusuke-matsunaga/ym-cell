
/// @file LatchHandler.cc
/// @brief LatchHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/LatchHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LatchHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LatchHandler::LatchHandler(Parser& parser) :
  FLHandler(parser)
{
}

END_NAMESPACE_YM_DOTLIB
