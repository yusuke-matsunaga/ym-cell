﻿#ifndef CIPATGRAPH_H
#define CIPATGRAPH_H

/// @file CiPatGraph.h
/// @brief CiPatGraph のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibPatGraph.h"


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
  ~CiPatGraph();


public:
  //////////////////////////////////////////////////////////////////////
  // ClibPatGraph の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表関数番号を返す．
  int
  rep_id() const override;

  /// @brief 根のノード番号を返す．
  int
  root_id() const override;

  /// @brief 根の反転属性を返す．
  bool
  root_inv() const override;

  /// @brief 入力数を返す．
  int
  input_num() const override;

  /// @brief 枝数を返す．
  int
  edge_num() const override;

  /// @brief 枝(の番号)を返す．
  /// @param[in] pos 位置 ( 0 <= pos < edge_num() )
  int
  edge(int pos) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  /// @param[in] bos 出力先のストリーム
  void
  dump(ostream& bos) const;

  /// @brief バイナリファイルを読み込む．
  /// @param[in] bis 入力元のストリーム
  /// @param[in] alloc メモリアロケータ
  void
  restore(istream& bis);


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
       int edge_num);

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


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 代表関数番号
  int mRepId;

  // 入力数 + 根の反転属性
  ymuint mInputNum;

  // 枝数
  int mEdgeNum;

  // 枝番号の配列
  int* mEdgeList;

};

END_NAMESPACE_YM_CLIB

#endif // CIPATGRAPH_H
