
/// @file HeaderHandler.cc
/// @brief HeaderHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HeaderHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス HeaderHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
HeaderHandler::HeaderHandler(DotlibParser& parser) :
  DotlibHandler(parser)
{
}

// @brief デストラクタ
HeaderHandler::~HeaderHandler()
{
}

END_NAMESPACE_YM_DOTLIB
