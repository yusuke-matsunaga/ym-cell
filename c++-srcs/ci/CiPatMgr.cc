
/// @file CiPatMgr.cc
/// @brief CiPatMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiPatMgr.h"
#include "ci/CiPatGraph.h"
#if 0
#include "lc/LcPatMgr.h"
#include "lc/LcPatNode.h"
#include "lc/LcPatHandle.h"
#endif

BEGIN_NAMESPACE_YM_CLIB

using namespace nsLibcomp;

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

#if 0
// @brief LcPatMgr の情報をコピーする．
void
CiPatMgr::copy(
  const LcPatMgr& src
)
{
  // ノードの情報をコピーする．
  auto nn = src.node_num();
  set_node_num(nn);
  for ( auto i = 0; i < nn; ++ i ) {
    auto& src_node = src.node(i);
    SizeType v = 0U;
    if ( src_node.is_input() ) {
      v = static_cast<SizeType>(ClibPatType::Input) | (src_node.input_id() << 2);
    }
    else if ( src_node.is_and() ) {
      v = static_cast<SizeType>(ClibPatType::And);
    }
    else if ( src_node.is_xor() ) {
      v = static_cast<SizeType>(ClibPatType::Xor);
    }
    mNodeTypeArray[i] = v;
    for ( auto j: { 0, 1 } ) {
      SizeType v = 0U;
      if ( !src_node.is_input() ) {
	v = src_node.fanin(j).id() * 2;
	if ( src_node.fanin_inv(j) ) {
	  v |= 1U;
	}
      }
      mEdgeArray[i * 2 + j] = v;
    }
  }

  // パタンの情報をコピーする．
  auto np = src.pat_num();
  set_pat_num(np);
  for ( auto i = 0; i < np; ++ i ) {
    vector<SizeType> node_list;
    auto v = src.pat_node_list(i, node_list);
    auto ne = node_list.size();
    CiPatGraph& pg = mPatArray[i];
    pg.init(src.rep_id(i), v, ne);
    for ( auto j = 0; j < ne; ++ j ) {
      pg.set_edge(j, node_list[j]);
    }
  }
}
#endif

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

// @brief パタン数を設定する．
void
CiPatMgr::set_pat_num(
  SizeType np
)
{
  mPatArray.clear();
  mPatArray.resize(np);
}

END_NAMESPACE_YM_CLIB
