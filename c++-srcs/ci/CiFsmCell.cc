
/// @file CiFsmCell.cc
/// @brief CiFsmCell の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "CiFsmCell.h"
#include "ci/Serializer.h"
#include "ci/Deserializer.h"


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

// @brief 内容をバイナリダンプする．
void
CiFsmCell::dump(
  Serializer& s
) const
{
  s.out().write_8(5);
  dump_common(s);
}

// @brief 内容を読み込む．
void
CiFsmCell::_restore(
  Deserializer& s
)
{
  CiCell::_restore(s);
}

END_NAMESPACE_YM_CLIB
