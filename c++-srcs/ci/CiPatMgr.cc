
/// @file CiPatMgr.cc
/// @brief CiPatMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiPatMgr.h"
#include "ci/CiPatGraph.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiPatMgr
//////////////////////////////////////////////////////////////////////

CiPatMgr::CiPatMgr()
{
}

// @brief このセルライブラリに含まれるセルの最大の入力数を得る．
SizeType
CiPatMgr::max_input() const
{
  SizeType ans = 0;
  for ( auto& pat: mPatArray ) {
    auto ni = pat.input_num();
    if ( ans < ni ) {
      ans = ni;
    }
  }
  return ans;
}

// @brief 総パタン数を返す．
SizeType
CiPatMgr::pat_num() const
{
  // CiPatGraph の定義が必要なのでヘッダファイルに書けない．
  return mPatArray.size();
}

// @brief パタンを返す．
const ClibPatGraph&
CiPatMgr::pat(
  SizeType id ///< [in] パタン番号 ( 0 <= id < pat_num() )
) const
{
  // CiPatGraph の定義が必要なのでヘッダファイルに書けない．
  ASSERT_COND( 0 <= id && id < pat_num() );
  return mPatArray[id];
}

// @brief ノード数を設定する．
void
CiPatMgr::set_node_num(
  SizeType nn
)
{
  mNodeTypeArray.clear();
  mEdgeArray.clear();
  if ( nn > 0 ) {
    mNodeTypeArray.resize(nn);
    mEdgeArray.resize(nn * 2);
  }
}

// @brief 入力ノードの情報を設定する．
void
CiPatMgr::set_node_info(
  SizeType pos,
  SizeType id
)
{
  SizeType v = static_cast<SizeType>(ClibPatType::Input) | (id << 2);
  mNodeTypeArray[pos] = v;
}

// @brief 論理ノードの情報を設定する．
void
CiPatMgr::set_node_info(
  SizeType pos,
  ClibPatType type,
  SizeType iid1,
  bool iinv1,
  SizeType iid2,
  bool iinv2
)
{
  SizeType v = static_cast<SizeType>(type);
  mNodeTypeArray[pos] = v;
  SizeType fanin_id[] = {iid1, iid2};
  bool fanin_inv[] = {iinv1, iinv2};
  for ( auto i: { 0, 1 } ) {
    SizeType v = 0U;
    v = fanin_id[i] * 2;
    if ( fanin_inv[i] ) {
      v |= 1U;
    }
    mEdgeArray[pos * 2 + i] = v;
  }
}

// @brief パタン数を設定する．
void
CiPatMgr::set_pat_num(
  SizeType np
)
{
  mPatArray.clear();
  mPatArray.resize(np);
}

// @brief パタンの情報を設定する．
void
CiPatMgr::set_pat_info(
  SizeType pos,
  SizeType rep_id,
  SizeType input_num,
  const vector<SizeType>& edge_list
)
{
  CiPatGraph& pg = mPatArray[pos];
  pg.init(rep_id, input_num, edge_list);
}

END_NAMESPACE_YM_CLIB
