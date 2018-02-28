
/// @file CiPatMgr.cc
/// @brief CiPatMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ci/CiPatMgr.h"
#include "ci/CiPatGraph.h"
#include "LcPatMgr.h"
#include "LcPatNode.h"
#include "LcPatHandle.h"


BEGIN_NAMESPACE_YM_CLIB

using namespace nsLibcomp;

//////////////////////////////////////////////////////////////////////
// クラス CiPatMgr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] alloc メモリアロケータ
CiPatMgr::CiPatMgr(Alloc& alloc) :
  mAlloc(alloc),
  mNodeNum(0U),
  mNodeTypeArray(nullptr),
  mEdgeArray(nullptr),
  mPatNum(0),
  mPatArray(nullptr)
{
}

// @brief デストラクタ
CiPatMgr::~CiPatMgr()
{
}

// @brief このセルライブラリに含まれるセルの最大の入力数を得る．
ymuint
CiPatMgr::max_input() const
{
  ymuint ans = 0;
  for (ymuint i = 0; i < mPatNum; ++ i) {
    const ClibPatGraph& pat = this->pat(i);
    ymuint ni = pat.input_num();
    if ( ans < ni ) {
      ans = ni;
    }
  }
  return ans;
}

// @brief パタンを返す．
// @param[in] id パタン番号 ( 0 <= id < pat_num() )
const ClibPatGraph&
CiPatMgr::pat(ymuint id) const
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
  ymuint nn = src.node_num();
  set_node_num(nn);
  for (ymuint i = 0; i < nn; ++ i) {
    LcPatNode* src_node = src.node(i);
    ymuint32 v = 0U;
    if ( src_node->is_input() ) {
      v = kClibPatInput | (src_node->input_id() << 2);
    }
    else if ( src_node->is_and() ) {
      v = kClibPatAnd;
    }
    else if ( src_node->is_xor() ) {
      v = kClibPatXor;
    }
    mNodeTypeArray[i] = v;
    for (ymuint j = 0; j < 2; ++ j) {
      ymuint v = 0U;
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
  ymuint np = src.pat_num();
  set_pat_num(np);
  for (ymuint i = 0; i < np; ++ i) {
    vector<ymuint> node_list;
    ymuint v = src.pat_node_list(i, node_list);
    ymuint ne = node_list.size();
    CiPatGraph& pg = mPatArray[i];
    pg.init(src.rep_id(i), v, ne, mAlloc);
    for (ymuint j = 0; j < ne; ++ j) {
      pg.set_edge(j, node_list[j]);
    }
  }
}

// @brief ノード数を設定する．
// @param[in] nn ノード数
void
CiPatMgr::set_node_num(ymuint nn)
{
  mNodeNum = nn;
  void* p = mAlloc.get_memory(sizeof(ymuint32) * mNodeNum);
  mNodeTypeArray = new (p) ymuint32[mNodeNum];
  void* q = mAlloc.get_memory(sizeof(ymuint32) * mNodeNum * 2);
  mEdgeArray = new (q) ymuint32[mNodeNum * 2];
}

// @brief パタン数を設定する．
void
CiPatMgr::set_pat_num(ymuint np)
{
  mPatNum = np;
  void* p = mAlloc.get_memory(sizeof(CiPatGraph) * mPatNum);
  mPatArray = new (p) CiPatGraph[mPatNum];
}

END_NAMESPACE_YM_CLIB
