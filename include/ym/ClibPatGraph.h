#ifndef YM_CLIBPATGRAPH_H
#define YM_CLIBPATGRAPH_H

/// @file ym/ClibPatGraph.h
/// @brief ClibPatGraph のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibHandle.h"


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
class ClibPatGraph :
  public ClibHandle
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 不正値となる．
  ClibPatGraph() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibPatGraph(
    const ClibLibraryPtr& library, ///< [in] ライブラリ
    SizeType id                    ///< [in] ID番号
  ) : ClibHandle{library, id}
  {
  }

  /// @brief デストラクタ
  ~ClibPatGraph() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表関数番号を返す．
  SizeType
  rep_id() const;

  /// @brief 根のノード番号を返す．
  SizeType
  root_id() const;

  /// @brief 根の反転属性を返す．
  bool
  root_inv() const;

  /// @brief 入力数を返す．
  SizeType
  input_num() const;

  /// @brief 枝数を返す．
  SizeType
  edge_num() const;

  /// @brief 枝(の番号)を返す．
  SizeType
  edge(
    SizeType pos ///< [in] 位置 ( 0 <= pos < edge_num() )
  ) const;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBPATGRAPH_H
