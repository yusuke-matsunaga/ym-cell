#ifndef PATMGR_H
#define PATMGR_H

/// @file PatMgr.h
/// @brief PatMgr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/logic.h"
#include "ym/VarId.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class PatMgr PatMgr.h "PatMgr.h"
/// @brief パタングラフを生成するクラス
///
/// 前処理で使われるのであまり効率を考えていない．
//////////////////////////////////////////////////////////////////////
class PatMgr
{
public:

  /// @brief コンストラクタ
  PatMgr();

  /// @brief デストラクタ
  ~PatMgr();


public:
  //////////////////////////////////////////////////////////////////////
  // このクラスのメインの関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  void
  init();

  /// @brief 論理式から生成されるパタンを登録する．
  void
  reg_pat(
    const Expr& expr, ///< [in] パタンの元となる論理式
    SizeType rep_id   ///< [in] このパタンが属する代表関数番号
  );

  /// @brief 内容を出力する．(デバッグ用)
  void
  display(
    ostream& s ///< [in] 出力先のストリーム
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内容情報を取得する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 全ノード数を返す．
  SizeType
  node_num() const;

  /// @brief ノードを返す．
  const PatNode&
  node(
    SizeType pos ///< [in] ノード番号 ( 0 <= pos < node_num() )
  ) const;

  /// @brief パタン数を返す．
  SizeType
  pat_num() const;

  /// @brief パタンの根のハンドルを返す．
  PatHandle
  pat_root(
    SizeType id ///< [in] パタン番号 ( 0 <= id < pat_num() )
  ) const;

  /// @brief パタンのノードリストを返す．
  /// @return このパタンの入力数を返す．
  SizeType
  pat_node_list(
    SizeType id,                ///< [in] パタン番号 ( 0 <= id < pat_num() )
    vector<SizeType>& node_list ///< [in] パタンを DFS 順でたどった時のノード番号のリスト
  ) const;

  /// @brief パタンの属している代表関数番号を返す．
  SizeType
  rep_id(
    SizeType id ///< [in] パタン番号 ( 0 <= id < pat_num() )
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 2つの論理式が等しいかどうか調べる．
  static
  bool
  check_equivalent(
    const Expr& expr1,
    const Expr& expr2
  );

  /// @brief 2つのパタンが同型かどうか調べる．
  static
  bool
  check_equivalent(
    PatHandle handle1,
    PatHandle handle2
  );

  /// @brief check_equivalent の下請け関数
  static
  bool
  ceq_sub(
    const PatNode& node1,
    const PatNode& node2,
    unordered_map<SizeType, SizeType>& map1,
    unordered_map<SizeType, SizeType>& map2
  );

  /// @brief パタングラフを生成する再帰関数
  void
  pg_sub(
    const Expr& expr,            ///< [in] 元になる論理式
    vector<PatHandle>& pg_list ///< [in] パタングラフ番号のリスト
  );

  /// @brief テンプレートにしたがって2分木を作る．
  PatHandle
  make_bintree(
    const Expr& expr,                 ///< [in] 論理式 (演算の種類を表すのに用いる)
    const vector<LcPatHandle>& input, ///< [in] 入力の配列
    int pat[],                        ///< [in] 2分木の形を表す配列
    SizeType& pos                     ///< [inout] pat[] 中の位置を示す変数
  );

  /// @brief 入力ノードを作る．
  ///
  /// 既にあるときはそれを返す．
  PatNode*
  make_input(
    VarId var ///< [in] 入力変数
  );

  /// @brief 論理式の種類に応じてノードを作る．
  PatHandle
  make_node(
    const Expr& expr,   ///< [in] 論理式 (演算の種類を表すのに用いる)
    PatHandle l_handle, ///< [in] 左の子供のパタン
    PatHandle r_handle  ///< [in] 右の子供のパタン
  );

  /// @brief ノードを作る．
  PatNode*
  new_node();


private:
  //////////////////////////////////////////////////////////////////////
  // ハッシュ表用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ハッシュ表を確保する．
  void
  alloc_table(
    SizeType req_size ///< [in] サイズ
  );

  /// @brief LcPatNode のハッシュ関数
  static
  SizeType
  hash_func(
    SizeType type,         ///< [in] 種類
    const PatNode& l_node, ///< [in] 左の子供
    const PatNode& r_node  ///< [in] 右の子供
  );


private:
  //////////////////////////////////////////////////////////////////////
  // dump() 用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 枝の情報をエンコードする．
  static
  SizeType
  encode_edge(
    const PatNode& node, ///< [in] 親のノード
    SizeType fanin_pos   ///< [in] ファンイン番号
  );


  /// @brief パタングラフを DFS でたどって内容を val_list に入れる．
  /// @return 最大入力番号+1を返す．
  static
  SizeType
  dump_dfs(
    const PatNode& node,       ///< [in] ノード
    vector<bool>& vmark,       ///< [in] 訪れたかどうかの情報を持つ配列
    vector<SizeType>& val_list ///< [in] ノードの情報を格納するリスト
  );


private:
  //////////////////////////////////////////////////////////////////////
  // display() 用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 枝の情報を出力する．
  static
  void
  display_edge(
    ostream& s,          ///< [in] 出力先のストリーム
    const PatNode& node, ///< [in] 親のノード
    SizeType fanin_pos   ///< [in] ファンイン番号
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ノードを収める配列
  vector<PatNode*> mInputList;

  // 全ノードを収める配列
  vector<unique_ptr<PatNode>> mNodeList;

  // AND/XOR ノードのハッシュ表
  PatNode** mHashTable;

  // mHashTable のサイズ
  SizeType mHashSize;

  // ハッシュ表を拡大する目安
  SizeType mNextLimit;

  // パタンの根のハンドルと代表関数番号のペアのリスト
  // 配列のインデックスはパタン番号
  vector<pair<PatHandle, SizeType>> mPatList;

  // 処理済みの論理式を収めたリストの配列
  // 配列のキーは代表関数番号
  vector<vector<Expr>> mExprList;

};

END_NAMESPACE_YM_CLIB

#endif // PATMGR_H
