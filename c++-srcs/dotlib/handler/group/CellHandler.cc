
/// @file CellHandler.cc
/// @brief CellHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/CellHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief コンストラクタ
// @param[in] parser パーサー
CellHandler::CellHandler(Parser& parser) :
  GroupHandler(parser)
{
}

END_NAMESPACE_YM_DOTLIB
