
/// @file CiPatMgr.cc
/// @brief CiPatMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiPatMgr.h"
#include "ci/CiPatGraph.h"
#include "lc/LcPatMgr.h"
#include "lc/LcPatNode.h"
#include "lc/LcPatHandle.h"


BEGIN_NAMESPACE_YM_CLIB

using namespace nsLibcomp;

//////////////////////////////////////////////////////////////////////
// クラス CiPatMgr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
CiPatMgr::CiPatMgr()
{
}

// @brief デストラクタ
CiPatMgr::~CiPatMgr()
{
  delete [] mNodeTypeArray;
  delete [] mEdgeArray;
  delete [] mPatArray;
}

// @brief このセルライブラリに含まれるセルの最大の入力数を得る．
int
CiPatMgr::max_input() const
{
  int ans = 0;
  for ( int i = 0; i < mPatNum; ++ i ) {
    const ClibPatGraph& pat = this->pat(i);
    int ni = pat.input_num();
    if ( ans < ni ) {
      ans = ni;
    }
  }
  return ans;
}

// @brief パタンを返す．
// @param[in] id パタン番号 ( 0 <= id < pat_num() )
const ClibPatGraph&
CiPatMgr::pat(int id) const
{
  ASSERT_COND( id < pat_num() );
  return mPatArray[id];
}

// @brief LcPatMgr の情報をコピーする．
// @param[in] src コピー元
void
CiPatMgr::copy(const LcPatMgr& src)
{
  // ノードの情報をコピーする．
  int nn = src.node_num();
  set_node_num(nn);
  for (int i = 0; i < nn; ++ i) {
    LcPatNode* src_node = src.node(i);
    int v = 0U;
    if ( src_node->is_input() ) {
      v = static_cast<int>(ClibPatType::Input) | (src_node->input_id() << 2);
    }
    else if ( src_node->is_and() ) {
      v = static_cast<int>(ClibPatType::And);
    }
    else if ( src_node->is_xor() ) {
      v = static_cast<int>(ClibPatType::Xor);
    }
    mNodeTypeArray[i] = v;
    for ( auto j: { 0, 1 } ) {
      int v = 0U;
      if ( !src_node->is_input() ) {
	v = src_node->fanin(j)->id() * 2;
	if ( src_node->fanin_inv(j) ) {
	  v |= 1U;
	}
      }
      mEdgeArray[i * 2 + j] = v;
    }
  }

  // パタンの情報をコピーする．
  int np = src.pat_num();
  set_pat_num(np);
  for (int i = 0; i < np; ++ i) {
    vector<int> node_list;
    int v = src.pat_node_list(i, node_list);
    int ne = node_list.size();
    CiPatGraph& pg = mPatArray[i];
    pg.init(src.rep_id(i), v, ne);
    for (int j = 0; j < ne; ++ j) {
      pg.set_edge(j, node_list[j]);
    }
  }
}

// @brief ノード数を設定する．
// @param[in] nn ノード数
void
CiPatMgr::set_node_num(int nn)
{
  mNodeNum = nn;
  mNodeTypeArray = new ymuint[mNodeNum];
  mEdgeArray = new ymuint[mNodeNum * 2];
}

// @brief パタン数を設定する．
void
CiPatMgr::set_pat_num(int np)
{
  mPatNum = np;
  mPatArray = new CiPatGraph[mPatNum];
}

END_NAMESPACE_YM_CLIB
