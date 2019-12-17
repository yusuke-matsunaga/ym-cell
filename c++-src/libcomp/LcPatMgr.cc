
/// @file LcPatMgr.cc
/// @brief LcPatMgr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "lc/LcPatMgr.h"
#include "lc/LcPatNode.h"
#include "lc/LcPatHandle.h"

#include "ym/Expr.h"
#include "ym/MFSet.h"
#include "ym/PermGen.h"
#include "ym/MultiCombiGen.h"
#include "ym/MultiSetPermGen.h"
#include "ym/Range.h"


BEGIN_NONAMESPACE
#include "lcpat_table"
END_NONAMESPACE


BEGIN_NAMESPACE_YM_CLIB_LIBCOMP

//////////////////////////////////////////////////////////////////////
// クラス LcPatMgr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
LcPatMgr::LcPatMgr() :
  mHashTable(nullptr),
  mHashSize(0)
{
  alloc_table(1024);
}

// @brief デストラクタ
LcPatMgr::~LcPatMgr()
{
  delete [] mHashTable;
}

// @brief 初期化する．
void
LcPatMgr::init()
{
  mAlloc.destroy();
  mInputList.clear();
  mNodeList.clear();
  delete [] mHashTable;
  mHashTable = nullptr;
  mHashSize = 0;
  alloc_table(1024);
  mPatList.clear();
  mRepList.clear();
}

// @brief 全ノード数を返す．
int
LcPatMgr::node_num() const
{
  return mNodeList.size();
}

// @brief ノードを返す．
// @param[in] pos ノード番号 ( 0 <= pos < node_num() )
LcPatNode*
LcPatMgr::node(int pos) const
{
  return mNodeList[pos];
}

// @brief パタン数を返す．
int
LcPatMgr::pat_num() const
{
  return mPatList.size();
}

// @brief パタンの根のハンドルを返す．
// @param[in] id パタン番号 ( 0 <= id < pat_num() )
LcPatHandle
LcPatMgr::pat_root(int id) const
{
  ASSERT_COND( id >= 0 && id < pat_num() );

  return mPatList[id];
}

// @brief パタンの属している代表関数番号を返す．
// @param[in] id パタン番号 ( 0 <= id < pat_num() )
int
LcPatMgr::rep_id(int id) const
{
  ASSERT_COND( id >= 0 && id < pat_num() );

  return mRepList[id];
}

// @brief 論理式から生成されるパタンを登録する．
// @param[in] expr パタンの元となる論理式
// @param[in] rep_id このパタンが属する代表関数番号
void
LcPatMgr::reg_pat(const Expr& expr,
		  int rep_id)
{
  ASSERT_COND( rep_id >= 0 );

  if ( mExprList.size() <= rep_id ) {
    mExprList.resize(rep_id + 1, vector<Expr>());
  }

  { // 同じ論理式を処理済みならなにもしない．
    for ( auto expr1: mExprList[rep_id] ) {
      if ( check_equivalent(expr, expr1) ) {
	return;
      }
    }
    // 論理式を登録しておく．
    mExprList[rep_id].push_back(expr);
  }

  vector<LcPatHandle> tmp_pat_list;
  pg_sub(expr, tmp_pat_list);

  for ( auto pat1: tmp_pat_list ) {
    mPatList.push_back(pat1);
    mRepList.push_back(rep_id);
  }

  // 入力ノードの整列
  for ( int i = 0; i < mNodeList.size(); ++ i ) {
    LcPatNode* node = mNodeList[i];
    if ( !node->is_input() ) continue;
    int iid = node->input_id();
    if ( iid == i ) continue;
    LcPatNode* node1 = mNodeList[iid];
    mNodeList[iid] = node;
    node->mId = iid;
    mNodeList[i] = node1;
    node1->mId = i;
  }
}

// @brief 2つの論理式が同形かどうか調べる．
bool
LcPatMgr::check_equivalent(const Expr& expr1,
			   const Expr& expr2)
{
  if ( expr1.is_zero() ) {
    if ( expr2.is_zero() ) {
      return true;
    }
    return false;
  }
  if ( expr1.is_one() ) {
    if ( expr2.is_one() ) {
      return true;
    }
    return false;
  }
  if ( expr2.is_constant() ) {
    return false;
  }

  if ( expr1.is_posi_literal() ) {
    if ( expr2.is_posi_literal() && expr1.varid() == expr2.varid() ) {
      return true;
    }
    return false;
  }
  if ( expr1.is_nega_literal() ) {
    if ( expr2.is_nega_literal() && expr1.varid() == expr2.varid() ) {
      return true;
    }
    return false;
  }
  if ( expr2.is_literal() ) {
    return false;
  }

  int n = expr1.child_num();
  if ( expr2.child_num() != n ) {
    return false;
  }

  if ( expr1.is_and() && !expr2.is_and() ) {
    return false;
  }
  if ( expr1.is_or() && !expr2.is_or() ) {
    return false;
  }
  if ( expr1.is_xor() && !expr2.is_xor() ) {
    return false;
  }

  for ( PermGen pg(n, n); !pg.is_end(); ++ pg ) {
    bool match = true;
    for ( int i: Range(n) ) {
      if ( !check_equivalent(expr1.child(i), expr2.child(pg(i))) ) {
	match = false;
	break;
      }
    }
    if ( match ) {
      return true;
    }
  }
  return false;
}

// @brief 2つのパタンが同型かどうか調べる．
bool
LcPatMgr::check_equivalent(LcPatHandle handle1,
			   LcPatHandle handle2)
{
  if ( handle1.inv() != handle2.inv() ) {
    return false;
  }

  unordered_map<int, int> map1;
  unordered_map<int, int> map2;

  return ceq_sub(handle1.node(), handle2.node(), map1, map2);
}

// @brief check_equivalent の下請け関数
bool
LcPatMgr::ceq_sub(LcPatNode* node1,
		  LcPatNode* node2,
		  unordered_map<int, int>& map1,
		  unordered_map<int, int>& map2)
{
  if ( node1->is_input() && node2->is_input() ) {
    int id1 = node1->input_id();
    int id2 = node2->input_id();
    if ( map1.count(id1) == 0 ) {
      map1[id1] = id2;
    }
    else {
      int id2_reg = map1[id1];
      if ( id2_reg != id2 ) {
	return false;
      }
    }
    if ( map2.count(id2) == 0 ) {
      map2[id2] = id1;
    }
    else {
      int id1_reg = map2[id1];
      if ( id1_reg != id1 ) {
	return false;
      }
    }
    return true;
  }

  if ( (!node1->is_and() || !node2->is_and()) &&
       (!node1->is_xor() || !node2->is_xor()) ) {
    return false;
  }

  if ( node1->fanin_inv0() != node2->fanin_inv0() ||
       node1->fanin_inv1() != node2->fanin_inv1() ) {
    return false;
  }

  if ( !ceq_sub(node1->fanin0(), node2->fanin0(), map1, map2) ) {
    return false;
  }

  if ( !ceq_sub(node1->fanin1(), node2->fanin1(), map1, map2) ) {
    return false;
  }

  return true;
}

// @brief パタングラフを生成する再帰関数
// @param[in] expr 元になる論理式
// @param[out] pg_list パタングラフのリスト
void
LcPatMgr::pg_sub(const Expr& expr,
		 vector<LcPatHandle>& pg_list)
{
  if ( expr.is_literal() ) {
    LcPatNode* node = make_input(expr.varid());
    bool inv = expr.is_nega_literal();
    pg_list.push_back(LcPatHandle(node, inv));
  }
  else {
    int n = expr.child_num();
    // ファンインの式に対するパタングラフを求める．
    vector<vector<LcPatHandle> > input_pg_list(n);
    vector<pair<int, int> > nk_array(n);
    for (int i = 0; i < n; ++ i) {
      pg_sub(expr.child(i), input_pg_list[i]);
      nk_array[i] = make_pair(input_pg_list[i].size(), 1);
    }

    // ファンインのパタンの組み合わせを列挙するオブジェクト
    for (MultiCombiGen mcg(nk_array); !mcg.is_end(); ++ mcg) {
      // 各ファンインから1つずつパタンを取り出して tmp_input に入れる．
      vector<LcPatHandle> tmp_input(n);
      for (int i = 0; i < n; ++ i) {
	tmp_input[i] = input_pg_list[i][mcg(i, 0)];
      }

      // tmp_input のなかで同形なパタンを求める．
      MFSet mfset(n);
      for (int i1 = 1; i1 < n; ++ i1) {
	LcPatHandle pat1 = tmp_input[i1];
	for (int i2 = 0; i2 < i1; ++ i2) {
	  LcPatHandle pat2 = tmp_input[i2];
	  if ( check_equivalent(pat1, pat2) ) {
	    mfset.merge(i1, i2);
	  }
	}
      }
      vector<int> rep_id;
      rep_id.reserve(n);
      vector<int> rev_map(n);
      for (int i = 0; i < n; ++ i) {
	int x = mfset.find(i);
	if ( x == i ) {
	  rev_map[i] = rep_id.size();
	  rep_id.push_back(x);
	}
      }
      int ng = rep_id.size();

      // group_list[0〜(ng - 1)] に同形なパタンのリストを格納する．
      vector<vector<int> > group_list(ng);
      for (int i = 0; i < n; ++ i) {
	int x = mfset.find(i);
	int id = rev_map[x];
	group_list[id].push_back(i);
      }

      vector<int> num_array(ng);
      for (int g = 0; g < ng; ++ g) {
	num_array[g] = group_list[g].size();
      }

      vector<LcPatHandle> input(n);
      for (MultiSetPermGen mspg(num_array, n); !mspg.is_end(); ++ mspg) {
	vector<int> count(ng, 0);
	for (int i = 0; i < n; ++ i) {
	  int g = mspg(i);
	  input[i] = tmp_input[group_list[g][count[g]]];
	  ++ count[g];
	}
	switch ( n ) {
	case 2:
	  {
	    LcPatHandle handle = make_node(expr, input[0], input[1]);
	    pg_list.push_back(handle);
	  }
	  break;

	case 3:
	  for (int i = 0; i < n_pat3; ++ i) {
	    int pos = 0;
	    LcPatHandle handle = make_bintree(expr, input, pat3[i], pos);
	    pg_list.push_back(handle);
	  }
	  break;

	case 4:
	  for (int i = 0; i < n_pat4; ++ i) {
	    int pos = 0;
	    LcPatHandle handle = make_bintree(expr, input, pat4[i], pos);
	    pg_list.push_back(handle);
	  }
	  break;

	case 5:
	  for (int i = 0; i < n_pat5; ++ i) {
	    int pos = 0;
	    LcPatHandle handle = make_bintree(expr, input, pat5[i], pos);
	    pg_list.push_back(handle);
	  }
	  break;

	case 6:
	  for (int i = 0; i < n_pat6; ++ i) {
	    int pos = 0;
	    LcPatHandle handle = make_bintree(expr, input, pat6[i], pos);
	    pg_list.push_back(handle);
	  }
	  break;

	case 7:
	  for (int i = 0; i < n_pat7; ++ i) {
	    int pos = 0;
	    LcPatHandle handle = make_bintree(expr, input, pat7[i], pos);
	    pg_list.push_back(handle);
	  }
	  break;

	case 8:
	  for (int i = 0; i < n_pat8; ++ i) {
	    int pos = 0;
	    LcPatHandle handle = make_bintree(expr, input, pat8[i], pos);
	    pg_list.push_back(handle);
	  }
	  break;

	default:
	  ASSERT_NOT_REACHED;
	  break;
	}
      }
    }
  }
}

// @brief テンプレートにしたがって2分木を作る．
// @param[in] expr 論理式 (演算の種類を表すのに用いる)
// @param[in] input 入力の配列
// @param[in] pat 2分木の形を表す配列
// @param[inout] pos pat[] 中の位置を示す変数
LcPatHandle
LcPatMgr::make_bintree(const Expr& expr,
		       const vector<LcPatHandle>& input,
		       int pat[],
		       int& pos)
{
  int p = pat[pos];
  ++ pos;
  if ( p == -1 ) {
    // 演算ノード
    LcPatHandle l_handle = make_bintree(expr, input, pat, pos);
    LcPatHandle r_handle = make_bintree(expr, input, pat, pos);
    return make_node(expr, l_handle, r_handle);
  }
  else {
    // 終端ノード
    int id = static_cast<int>(p);
    return input[id];
  }
}

// @brief 入力ノードを作る．
// @param[in] var 入力変数
// @note 既にあるときはそれを返す．
LcPatNode*
LcPatMgr::make_input(VarId var)
{
  int id = var.val();
  while ( mInputList.size() <= id ) {
    LcPatNode* node = new_node();
    int input_id = mInputList.size();
    node->mType = (input_id << 2) | LcPatNode::kInput;
    mInputList.push_back(node);
  }
  LcPatNode* node = mInputList[id];
  ASSERT_COND( node != nullptr );

  return node;
}

// @brief 論理式の種類に応じてノードを作る．
// @param[in] expr 論理式 (演算の種類を表すのに用いる)
// @param[in] l_handle, r_handle 左右の子供のパタン
LcPatHandle
LcPatMgr::make_node(const Expr& expr,
		    LcPatHandle l_handle,
		    LcPatHandle r_handle)
{
  LcPatNode* l_node = l_handle.node();
  LcPatNode* r_node = r_handle.node();
  ASSERT_COND( l_node != nullptr );
  ASSERT_COND( r_node != nullptr );
  bool l_inv = l_handle.inv();
  bool r_inv = r_handle.inv();

  bool oinv = false;
  int type = 0U;
  if ( expr.is_and() ) {
    type = LcPatNode::kAnd;
  }
  else if ( expr.is_or() ) {
    type = LcPatNode::kAnd;
    l_inv = !l_inv;
    r_inv = !r_inv;
    oinv = true;
  }
  else if ( expr.is_xor() ) {
    type = LcPatNode::kXor;
    oinv = l_inv ^ r_inv;
    l_inv = false;
    r_inv = false;
  }
  else {
    ASSERT_NOT_REACHED;
  }
  if ( l_inv ) {
    type |= 4U;
  }
  if ( r_inv ) {
    type |= 8U;
  }

  // (type, l_node, r_node) というノードがすでにあったらそれを使う．
  SizeType pos = hash_func(type, l_node, r_node);
  SizeType idx = pos % mHashSize;
  for ( LcPatNode* node = mHashTable[idx]; node; node = node->mLink ) {
    if ( node->mType == type &&
	 node->mFanin[0] == l_node &&
	 node->mFanin[1] == r_node ) {
      // おなじノードがあった．
      return LcPatHandle(node, oinv);
    }
  }

  // 新しいノードを作る．
  LcPatNode* node = new_node();
  node->mType = type;
  node->mFanin[0] = l_node;
  node->mFanin[1] = r_node;

  // ハッシュ表に登録する．
  if ( node_num() >= mNextLimit ) {
    alloc_table(mHashSize * 2);
    // サイズが変わったのでインデックスを再計算する．
    idx = pos % mHashSize;
  }
  node->mLink = mHashTable[idx];
  mHashTable[idx] = node;

  return LcPatHandle(node, oinv);
}

// @brief ノードを作る．
LcPatNode*
LcPatMgr::new_node()
{
  void* p = mAlloc.get_memory(sizeof(LcPatNode));
  LcPatNode* node = new (p) LcPatNode();
  node->mId = mNodeList.size();
  mNodeList.push_back(node);
  return node;
}

// @brief ノードを削除する．
void
LcPatMgr::delete_node(LcPatNode* node)
{
  node->~LcPatNode();
  mAlloc.put_memory(sizeof(LcPatNode), static_cast<void*>(node));
}

// @brief ハッシュ表を確保する．
void
LcPatMgr::alloc_table(SizeType req_size)
{
  LcPatNode** old_table = mHashTable;
  SizeType old_size = mHashSize;

  if ( mHashSize == 0 ) {
    mHashSize = 1024;
  }
  while ( mHashSize < req_size ) {
    mHashSize <<= 1;
  }
  mNextLimit = static_cast<SizeType>(mHashSize * 1.8);
  mHashTable = new LcPatNode*[mHashSize];
  for ( SizeType i = 0; i < mHashSize; ++ i) {
    mHashTable[i] = nullptr;
  }
  for ( SizeType i = 0; i < old_size; ++ i ) {
    LcPatNode* next = nullptr;
    for ( LcPatNode* node = old_table[i]; node; node = next ) {
      next = node->mLink;
      int pos = hash_func(node->mType, node->mFanin[0], node->mFanin[1]);
      int idx = pos % mHashSize;
      node->mLink = mHashTable[idx];
      mHashTable[idx] = node;
    }
  }
  delete [] old_table;

}

// @brief LcPatNode のハッシュ関数
SizeType
LcPatMgr::hash_func(int type,
		    LcPatNode* l_node,
		    LcPatNode* r_node)
{
  ympuint l = reinterpret_cast<ympuint>(l_node);
  ympuint r = reinterpret_cast<ympuint>(r_node);

  return type + l * 5 + r;
}


BEGIN_NONAMESPACE

// @brief パタングラフを DFS でたどって内容を val_list に入れる．
// @param[in] node ノード
// @param[in] vmark 訪れたかどうかの情報を持つ配列
// @param[out] val_list ノードの情報を格納するリスト
// @return 最大入力番号+1を返す．
int
dfs(LcPatNode* node,
    vector<bool>& vmark,
    vector<int>& val_list)
{
  if ( node->is_input() ) {
    return node->input_id() + 1;
  }
  if ( vmark[node->id()] ) {
    return 0;
  }
  vmark[node->id()] = true;
  val_list.push_back(node->id() * 2);
  int id = dfs(node->fanin(0), vmark, val_list);
  val_list.push_back(node->id() * 2 + 1);
  int id1 = dfs(node->fanin(1), vmark, val_list);
  if ( id < id1 ) {
    id = id1;
  }
  return id;
}

END_NONAMESPACE

// @brief パタンのノードリストを返す．
// @param[in] id パタン番号 ( 0 <= id < pat_num() )
// @param[out] node_list パタンを DFS 順でたどった時のノード番号のリスト
// @return このパタンの入力数を返す．
int
LcPatMgr::pat_node_list(int id,
			vector<int>& node_list) const
{
  LcPatHandle root = pat_root(id);
  node_list.clear();
  node_list.reserve(node_num());
  vector<bool> vmark(node_num(), false);
  int max_input =dfs(root.node(), vmark, node_list);
  int v = max_input << 1;
  if ( root.inv() ) {
    v |= 1U;
  }
  return v;
}


//////////////////////////////////////////////////////////////////////
// display() 関係の関数
//////////////////////////////////////////////////////////////////////

// @brief 内容を出力する．(デバッグ用)
// @param[in] s 出力先のストリーム
void
LcPatMgr::display(ostream& s) const
{
  s << "*** LcPatMgr BEGIN ***" << endl;

  s << "*** NODE SECTION ***" << endl;
  int n = node_num();
  for (int i = 0; i < n; ++ i) {
    LcPatNode* node = this->node(i);

    s << "Node#" << node->id() << ": ";
    if ( node->is_input() ) {
      s << "Input#" << node->input_id();
    }
    else {
      if ( node->is_and() ) {
	s << "And";
      }
      else if ( node->is_xor() ) {
	s << "Xor";
      }
      else {
	ASSERT_NOT_REACHED;
      }
      s << "( ";
      display_edge(s, node, 0);
      s << ", ";
      display_edge(s, node, 1);
      s << ")";
    }
    s << endl;
  }
  s << endl;

  s << "*** PATTERN SECTION ***" << endl;
  int np = pat_num();
  for (int i = 0; i < np; ++ i) {
    LcPatHandle root = pat_root(i);
    s << "Pat#" << i << ": ";
    if ( root.inv() ) {
      s << "~";
    }
    s << "Node#" << root.node()->id()
      << " --> Rep#" << rep_id(i)
      << endl;
  }
  s << "*** LcPatMgr END ***" << endl;
}

// @brief 枝の情報を出力する．
// @param[in] s 出力先のストリーム
// @param[in] node 親のノード
// @param[in] fanin_pos ファンイン番号
void
LcPatMgr::display_edge(ostream& s,
		       LcPatNode* node,
		       int fanin_pos)
{
  if ( node->fanin_inv(fanin_pos) ) {
    s << "~";
  }
  s << "Node#" << node->fanin(fanin_pos)->id();
}

END_NAMESPACE_YM_CLIB_LIBCOMP
