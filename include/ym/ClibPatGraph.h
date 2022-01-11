#ifndef YM_CLIBPATGRAPH_H
#define YM_CLIBPATGRAPH_H

/// @file ym/ClibPatGraph.h
/// @brief ClibPatGraph のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibPatGraph ClibPatGraph.h "ym/ClibPatGraph.h"
/// @brief パタングラフを表すクラス
///
/// このクラスは実装を隠すためにインターフェイスの定義のみとなっている．
///
/// 実際には根の反転属性と枝のリストしか持っていない．
/// その他の情報は ClibPatMgr から補完する．
//////////////////////////////////////////////////////////////////////
class ClibPatGraph
{
public:

  /// @brief デストラクタ
  virtual
  ~ClibPatGraph() = default;


public:

  /// @brief 代表関数番号を返す．
  virtual
  SizeType
  rep_id() const = 0;

  /// @brief 根のノード番号を返す．
  virtual
  SizeType
  root_id() const = 0;

  /// @brief 根の反転属性を返す．
  virtual
  bool
  root_inv() const = 0;

  /// @brief 入力数を返す．
  virtual
  SizeType
  input_num() const = 0;

  /// @brief 枝数を返す．
  virtual
  SizeType
  edge_num() const = 0;

  /// @brief 枝(の番号)を返す．
  virtual
  SizeType
  edge(
    SizeType pos ///< [in] 位置 ( 0 <= pos < edge_num() )
  ) const = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBPATGRAPH_H
