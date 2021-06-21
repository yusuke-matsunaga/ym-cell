
/// @file FFHandler.cc
/// @brief FFHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/FFHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FFHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FFHandler::FFHandler(Parser& parser) :
  FLHandler(parser)
{
}

END_NAMESPACE_YM_DOTLIB
