
/// @file CiFsmCell.cc
/// @brief CiFsmCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "CiFsmCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiFsmCell
//////////////////////////////////////////////////////////////////////

// @brief セルの種類を返す．
ClibCellType
CiFsmCell::type() const
{
  return ClibCellType::FSM;
}

// @brief 順序セル(非FF/非ラッチ)の場合に true を返す．
bool
CiFsmCell::is_fsm() const
{
  return true;
}

END_NAMESPACE_YM_CLIB
