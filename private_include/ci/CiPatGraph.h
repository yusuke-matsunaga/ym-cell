#ifndef CIPATGRAPH_H
#define CIPATGRAPH_H

/// @file CiPatGraph.h
/// @brief CiPatGraph のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
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
  int
  edge(
    int pos ///< [in] 位置 ( 0 <= pos < edge_num() )
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  void
  dump(
    ostream& bos ///< [in] 出力先のストリーム
  ) const;

  /// @brief バイナリファイルを読み込む．
  void
  restore(
    istream& bis ///< [in] 入力元のストリーム
  );


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  void
  init(
    int rep_id,    ///< [in] 代表番号
    int input_num, ///< [in] 入力数
    int edge_num   ///< [in] 枝数
  );

  /// @brief 枝のデータを設定する．
  ///
  /// この関数を呼ぶ前に init() が呼ばれている必要がある．
  void
  set_edge(
    int pos,  ///< [in] 位置番号 ( 0 <= pos < edge_num() )
    int edge  ///< [in] 枝
  );


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
