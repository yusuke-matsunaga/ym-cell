#ifndef CIPATGRAPH_H
#define CIPATGRAPH_H

/// @file CiPatGraph.h
/// @brief CiPatGraph のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/BinDec.h"
#include "ym/BinEnc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiPatGraph CiPatGraph.h "CiPatGraph.h"
/// @brief ClibPatGraph の実装クラス
//////////////////////////////////////////////////////////////////////
class CiPatGraph
{
public:

  /// @brief コンストラクタ
  CiPatGraph() = default;

  /// @brief デストラクタ
  ~CiPatGraph() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // ClibPatGraph の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 代表関数番号を返す．
  SizeType
  rep_id() const
  {
    return mRepId;
  }

  /// @brief 根のノード番号を返す．
  SizeType
  root_id() const
  {
    ASSERT_COND( mEdgeList.size() > 0 );

    // 枝の番号を2で割ればファンアウト先のノード番号
    return mEdgeList[0] / 2;
  }

  /// @brief 根の反転属性を返す．
  bool
  root_inv() const
  {
    return static_cast<bool>(mInputNum & 1U);
  }

  /// @brief 入力数を返す．
  SizeType
  input_num() const
  {
    return (mInputNum >> 1);
  }

  /// @brief 枝数を返す．
  SizeType
  edge_num() const
  {
    return mEdgeList.size();
  }

  /// @brief 枝(の番号)を返す．
  SizeType
  edge(
    SizeType pos ///< [in] 位置 ( 0 <= pos < edge_num() )
  ) const
  {
    ASSERT_COND( 0 <= pos && pos < edge_num() );
    return mEdgeList[pos];
  }


public:
  //////////////////////////////////////////////////////////////////////
  // バイナリダンプ用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief バイナリダンプを行う．
  void
  dump(
    BinEnc& bos ///< [in] 出力先のストリーム
  ) const;

  /// @brief バイナリファイルを読み込む．
  void
  restore(
    BinDec& bis ///< [in] 入力元のストリーム
  );


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  void
  init(
    SizeType rep_id,                  ///< [in] 代表番号
    SizeType input_num,               ///< [in] 入力数
    const vector<SizeType>& edge_list ///< [in] 枝情報のリスト
  )
  {
    mRepId = rep_id;
    mInputNum = input_num;
    mEdgeList.clear();
    mEdgeList.reserve(edge_list.size());
    for ( auto edge: edge_list ) {
      mEdgeList.push_back(edge);
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 代表関数番号
  SizeType mRepId{0};

  // 入力数 + 根の反転属性
  SizeType mInputNum{0};

  // 枝番号の配列
  vector<SizeType> mEdgeList;

};

END_NAMESPACE_YM_CLIB

#endif // CIPATGRAPH_H
