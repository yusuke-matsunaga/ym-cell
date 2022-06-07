
/// @file CiPatGraph.cc
/// @brief CiPatGraph の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiPatGraph.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiPatGraph
//////////////////////////////////////////////////////////////////////

// @brief 代表関数番号を返す．
SizeType
CiPatGraph::rep_id() const
{
  return mRepId;
}

// @brief 根のノード番号を返す．
SizeType
CiPatGraph::root_id() const
{
  ASSERT_COND( mEdgeList.size() > 0 );

  // 枝の番号を2で割ればファンアウト先のノード番号
  return mEdgeList[0] / 2;
}

// @brief 根の反転属性を返す．
bool
CiPatGraph::root_inv() const
{
  return static_cast<bool>(mInputNum & 1U);
}

// @brief 入力数を返す．
SizeType
CiPatGraph::input_num() const
{
  return (mInputNum >> 1);
}

// @brief 枝数を返す．
SizeType
CiPatGraph::edge_num() const
{
  return mEdgeList.size();
}

// @brief 枝(の番号)を返す．
SizeType
CiPatGraph::edge(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < edge_num() );
  return mEdgeList[pos];
}

// @brief 初期化する．
void
CiPatGraph::init(
  SizeType rep_id,
  SizeType input_num,
  const vector<SizeType>& edge_list
)
{
  mRepId = rep_id;
  mInputNum = input_num;
  mEdgeList.clear();
  mEdgeList.reserve(edge_list.size());
  for ( auto edge: edge_list ) {
    mEdgeList.push_back(edge);
  }
}

END_NAMESPACE_YM_CLIB
