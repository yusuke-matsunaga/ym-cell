
/// @file CiLogicCell.cc
/// @brief CiLogicCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiLogicCell.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiLogicCell
//////////////////////////////////////////////////////////////////////

// @brief 組み合わせ論理セルの時に true を返す．
bool
CiLogicCell::is_logic() const
{
  return true;
}

END_NAMESPACE_YM_CLIB
