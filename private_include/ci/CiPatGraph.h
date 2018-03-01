#ifndef CIPATGRAPH_H
#define CIPATGRAPH_H

/// @file CiPatGraph.h
/// @brief CiPatGraph のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibPatGraph.h"
#include "ym/Alloc.h"
#include "ym/IDO.h"
#include "ym/ODO.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiPatGraph CiPatGraph.h "CiPatGraph.h"
/// @brief ClibPatGraph の実装クラス
//////////////////////////////////////////////////////////////////////
class CiPatGraph :
  public ClibPatGraph
{
public:

  /// @brief コンストラクタ
  CiPatGraph();

  /// @brief デストラクタ
  virtual
  ~CiPatGraph();


public:
  //////////////////////////////////////////////////////////////////////
  // ClibPatGraph の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表関数番号を返す．
  virtual
  int
  rep_id() const;

  /// @brief 根のノード番号を返す．
  virtual
  int
  root_id() const;

  /// @brief 根の反転属性を返す．
  virtual
  bool
  root_inv() const;

  /// @brief 入力数を返す．
  virtual
  int
  input_num() const;

  /// @brief 枝数を返す．
  virtual
  int
  edge_num() const;

  /// @brief 枝(の番号)を返す．
  /// @param[in] pos 位置 ( 0 <= pos < edge_num() )
  virtual
  int
  edge(int pos) const;


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  /// @param[in] bos 出力先のストリーム
  void
  dump(ODO& bos) const;

  /// @brief バイナリファイルを読み込む．
  /// @param[in] bis 入力元のストリーム
  /// @param[in] alloc メモリアロケータ
  void
  restore(IDO& bis,
	  Alloc& alloc);


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  /// @param[in] rep_id 代表番号
  /// @param[in] input_num 入力数
  /// @param[in] edge_num 枝数
  /// @param[in] alloc メモリアロケータ
  void
  init(int rep_id,
       int input_num,
       int edge_num,
       Alloc& alloc);

  /// @brief 枝のデータを設定する．
  /// @param[in] pos 位置番号 ( 0 <= pos < edge_num() )
  /// @param[in] edge 枝
  /// @note この関数を呼ぶ前に init() が呼ばれている必要がある．
  void
  set_edge(int pos,
	   int edge);


private:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief mEdgeList を確保する．
  /// @param[in] alloc メモリアロケータ
  /// @note mEdgeNum に値が設定されているものとする．
  void
  alloc_array(Alloc& alloc);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 代表関数番号
  int mRepId;

  // 入力数 + 根の反転属性
  int mInputNum;

  // 枝数
  int mEdgeNum;

  // 枝番号の配列
  int* mEdgeList;

};

END_NAMESPACE_YM_CLIB

#endif // CIPATGRAPH_H
