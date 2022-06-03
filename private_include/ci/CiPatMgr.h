﻿#ifndef CIPATMGR_H
#define CIPATMGR_H

/// @file CiPatMgr.h
/// @brief CiPatMgr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/BinDec.h"
#include "ym/BinEnc.h"
#include "lc/libcomp_nsdef.h"


BEGIN_NAMESPACE_YM_CLIB

class CiPatGraph;

//////////////////////////////////////////////////////////////////////
/// @class CiPatMgr CiPatMgr.h "CiPatMgr.h"
/// @brief パタングラフを管理するクラス
///
/// このクラスが持っている情報は
/// - パタングラフ
/// - 各々のパタングラフに対応する論理関数
/// - その論理関数とNPN同値な関数の集合
/// で，最後の関数がセルの論理関数と対応づけられる．
///
/// 情報の設定は専用形式のバイナリファイルを読み込むことでのみ行える．
/// バイナリファイルの生成は patgen/PatGen, pg_dump を参照のこと．
//////////////////////////////////////////////////////////////////////
class CiPatMgr
{
public:

  /// @brief コンストラクタ
  CiPatMgr();

  /// @brief デストラクタ
  ~CiPatMgr() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // パタングラフ関係の情報取得用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief パタンの最大の入力数を得る．
  SizeType
  max_input() const;

  /// @brief 総ノード数を返す．
  SizeType
  node_num() const
  {
    return mNodeTypeArray.size();
  }

  /// @brief ノードの種類を返す．
  ClibPatType
  node_type(
    SizeType id ///< [in] ノード番号 ( 0 <= id < node_num() )
  ) const
  {
    ASSERT_COND( 0 <= id && id < node_num() );
    return static_cast<ClibPatType>(mNodeTypeArray[id] & 3U);
  }

  /// @brief ノードが入力ノードの時に入力番号を返す．
  ///
  /// 入力ノードでない場合の返り値は不定
  SizeType
  input_id(
    SizeType id ///< [in] ノード番号 ( 0 <= id < node_num() )
  ) const
  {
    ASSERT_COND( 0 <= id && id < node_num() );
    return (mNodeTypeArray[id] >> 2);
  }

  /// @brief 入力のノード番号を返す．
  /// @return input_id の入力に対応するノードのノード番号
  SizeType
  input_node(
    SizeType input_id ///< [in] 入力番号 ( 0 <= input_id < input_num() )
  ) const
  {
    return input_id;
  }

  /// @brief 総枝数を返す．
  SizeType
  edge_num() const
  {
    return mEdgeArray.size();
  }

  /// @brief 枝のファンイン元のノード番号を返す．
  SizeType
  edge_from(
    SizeType id ///< [in] 枝番号 ( 0 <= id < edge_num() )
  ) const
  {
    ASSERT_COND( 0 <= id && id < edge_num() );
    return (mEdgeArray[id] >> 1);
  }

  /// @brief 枝のファンアウト先のノード番号を返す．
  SizeType
  edge_to(
    SizeType id ///< [in] 枝番号 ( 0 <= id < edge_num() )
  ) const
  {
    ASSERT_COND( 0 <= id && id < edge_num() );
    return (id / 2);
  }

  /// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
  SizeType
  edge_pos(
    SizeType id ///< [in] 枝番号 ( 0 <= id < node_num() * 2 )
  ) const
  {
    ASSERT_COND( 0 <= id && id < edge_num() );
    return (id & 1U);
  }

  /// @brief 枝の反転属性を返す．
  bool
  edge_inv(
    SizeType id ///< [in] 枝番号 ( 0 <= id < node_num() * 2 )
  ) const
  {
    ASSERT_COND( 0 <= id && id < edge_num() );
    return static_cast<bool>(mEdgeArray[id] & 1U);
  }

  /// @brief 総パタン数を返す．
  SizeType
  pat_num() const;

  /// @brief パタンを返す．
  const ClibPatGraph&
  pat(
    SizeType id ///< [in] パタン番号 ( 0 <= id < pat_num() )
  ) const;

  /// @brief バイナリダンプを行う．
  void
  dump(
    BinEnc& bos ///< [in] 出力先のストリーム
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 情報設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief LcPatMgr の情報をコピーする．
  void
  copy(
    const nsLibcomp::LcPatMgr& src ///< [in] コピー元
  );

  /// @brief データを読み込んでセットする．
  /// @retval true 読み込みが成功した．
  /// @retval false 読み込みが失敗した．
  bool
  restore(
    BinDec& bis ///< [in] 入力元のストリーム
  );


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ノード数を設定する．
  void
  set_node_num(
    SizeType nn ///< [in] ノード数
  );

  /// @brief パタン数を設定する．
  void
  set_pat_num(
    SizeType np ///< [in] パタン数
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ノードの種類+入力番号を納めた配列
  // サイズはノード数
  vector<SizeType> mNodeTypeArray{};

  // ファンインのノード番号＋反転属性を納めた配列
  // サイズはノード数 x 2
  vector<SizeType> mEdgeArray{};

  // パタンの配列
  // サイズはパタン数
  vector<CiPatGraph> mPatArray;

};

END_NAMESPACE_YM_CLIB

#endif // CIPATMGR_H
