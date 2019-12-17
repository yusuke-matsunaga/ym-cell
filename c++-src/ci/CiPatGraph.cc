
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

// @brief コンストラクタ
CiPatGraph::CiPatGraph() :
  mInputNum{0},
  mEdgeNum{0},
  mEdgeList{nullptr}
{
}

// @brief デストラクタ
CiPatGraph::~CiPatGraph()
{
  delete [] mEdgeList;
}

// @brief 代表関数番号を返す．
int
CiPatGraph::rep_id() const
{
  return mRepId;
}

// @brief 根のノード番号を返す．
int
CiPatGraph::root_id() const
{
  ASSERT_COND( mEdgeNum > 0 );

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
int
CiPatGraph::input_num() const
{
  return (mInputNum >> 1);
}

// @brief 枝数を返す．
int
CiPatGraph::edge_num() const
{
  return mEdgeNum;
}

// @brief 枝(の番号)を返す．
// @param[in] pos 位置 ( 0 <= pos < edge_num() )
int
CiPatGraph::edge(int pos) const
{
  ASSERT_COND( pos < edge_num() );

  return mEdgeList[pos];
}

// @brief 初期化する．
// @param[in] rep_id 代表番号
// @param[in] input_num 入力数
// @param[in] edge_num 枝数
// @param[in] alloc メモリアロケータ
void
CiPatGraph::init(int rep_id,
		 int input_num,
		 int edge_num)
{
  mRepId = rep_id;
  mInputNum = input_num;
  mEdgeNum = edge_num;
  if ( mEdgeNum > 0 ) {
    mEdgeList = new int[mEdgeNum];
  }
  else {
    mEdgeList = nullptr;
  }
}

// @brief 枝のデータを設定する．
// @param[in] pos 位置番号 ( 0 <= pos < edge_num() )
// @param[in] edge 枝
// @note この関数を呼ぶ前に init() が呼ばれている必要がある．
void
CiPatGraph::set_edge(int pos,
		     int edge)
{
  ASSERT_COND( pos < edge_num() );

  mEdgeList[pos] = edge;
}

END_NAMESPACE_YM_CLIB
