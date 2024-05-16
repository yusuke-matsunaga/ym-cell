
/// @file ClibPatGraph.cc
/// @brief ClibPatGraph の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibPatGraph.h"
#include "ci/CiPatGraph.h"
#include "ci/CiCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス ClibPatGraph
//////////////////////////////////////////////////////////////////////

// @brief 代表関数番号を返す．
SizeType
ClibPatGraph::rep_id() const
{
  _check_valid();
  return mImpl->rep_id();
}

// @brief 根のノード番号を返す．
SizeType
ClibPatGraph::root_id() const
{
  _check_valid();
  return mImpl->root_id();
}

// @brief 根の反転属性を返す．
bool
ClibPatGraph::root_inv() const
{
  _check_valid();
  return mImpl->root_inv();
}

// @brief 入力数を返す．
SizeType
ClibPatGraph::input_num() const
{
  _check_valid();
  return mImpl->input_num();
}

// @brief 枝数を返す．
SizeType
ClibPatGraph::edge_num() const
{
  _check_valid();
  return mImpl->edge_num();
}

// @brief 枝(の番号)を返す．
SizeType
ClibPatGraph::edge(
  SizeType pos
) const
{
  _check_valid();
  return mImpl->edge(pos);
}

END_NAMESPACE_YM_CLIB
