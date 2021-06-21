
/// @file FLHandler.cc
/// @brief FLHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FLHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FLHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
FLHandler::FLHandler(Parser& parser) :
  GroupHandler(parser)
{
}

END_NAMESPACE_YM_DOTLIB
