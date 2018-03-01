#ifndef YM_CLIBPATGRAPH_H
#define YM_CLIBPATGRAPH_H

/// @file ym/ClibPatGraph.h
/// @brief ClibPatGraph のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibPatGraph ClibPatGraph.h "ym/ClibPatGraph.h"
/// @brief パタングラフを表すクラス
///
/// 実際には根の反転属性と枝のリストしか持っていない．
/// その他の情報は ClibPatMgr から補完する．
//////////////////////////////////////////////////////////////////////
class ClibPatGraph
{
public:

  /// @brief デストラクタ
  virtual
  ~ClibPatGraph() { }


public:

  /// @brief 代表関数番号を返す．
  virtual
  int
  rep_id() const = 0;

  /// @brief 根のノード番号を返す．
  virtual
  int
  root_id() const = 0;

  /// @brief 根の反転属性を返す．
  virtual
  bool
  root_inv() const = 0;

  /// @brief 入力数を返す．
  virtual
  int
  input_num() const = 0;

  /// @brief 枝数を返す．
  virtual
  int
  edge_num() const = 0;

  /// @brief 枝(の番号)を返す．
  /// @param[in] pos 位置 ( 0 <= pos < edge_num() )
  virtual
  int
  edge(int pos) const = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBPATGRAPH_H
