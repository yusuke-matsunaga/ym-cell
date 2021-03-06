﻿#ifndef CIPATMGR_H
#define CIPATMGR_H

/// @file CiPatMgr.h
/// @brief CiPatMgr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/clib.h"
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
  ~CiPatMgr();


public:
  //////////////////////////////////////////////////////////////////////
  // パタングラフ関係の情報取得用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief パタンの最大の入力数を得る．
  int
  max_input() const;

  /// @brief 総ノード数を返す．
  int
  node_num() const;

  /// @brief ノードの種類を返す．
  /// @param[in] id ノード番号 ( 0 <= id < node_num() )
  ClibPatType
  node_type(int id) const;

  /// @brief ノードが入力ノードの時に入力番号を返す．
  /// @param[in] id ノード番号 ( 0 <= id < node_num() )
  /// @note 入力ノードでない場合の返り値は不定
  int
  input_id(int id) const;

  /// @brief 入力のノード番号を返す．
  /// @param[in] input_id 入力番号 ( 0 <= input_id < input_num() )
  /// @return input_id の入力に対応するノードのノード番号
  int
  input_node(int input_id) const;

  /// @brief 総枝数を返す．
  int
  edge_num() const;

  /// @brief 枝のファンイン元のノード番号を返す．
  /// @param[in] id 枝番号 ( 0 <= id < node_num() * 2 )
  int
  edge_from(int id) const;

  /// @brief 枝のファンアウト先のノード番号を返す．
  /// @param[in] id 枝番号 ( 0 <= id < node_num() * 2 )
  int
  edge_to(int id) const;

  /// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
  /// @param[in] id 枝番号 ( 0 <= id < node_num() * 2 )
  int
  edge_pos(int id) const;

  /// @brief 枝の反転属性を返す．
  /// @param[in] id 枝番号 ( 0 <= id < node_num() * 2 )
  bool
  edge_inv(int id) const;

  /// @brief 総パタン数を返す．
  int
  pat_num() const;

  /// @brief パタンを返す．
  /// @param[in] id パタン番号 ( 0 <= id < pat_num() )
  const ClibPatGraph&
  pat(int id) const;

  /// @brief バイナリダンプを行う．
  /// @param[in] bos 出力先のストリーム
  void
  dump(ostream& bos) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 情報設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief LcPatMgr の情報をコピーする．
  /// @param[in] src コピー元
  void
  copy(const nsLibcomp::LcPatMgr& src);

  /// @brief データを読み込んでセットする．
  /// @param[in] bis 入力元のストリーム
  /// @retval true 読み込みが成功した．
  /// @retval false 読み込みが失敗した．
  bool
  restore(istream& bis);


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ノード数を設定する．
  /// @param[in] nn ノード数
  /// @param[in] alloc メモリアロケータ
  void
  set_node_num(int nn);

  /// @brief パタン数を設定する．
  void
  set_pat_num(int np);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ノード数
  int mNodeNum{0};

  // ノードの種類+入力番号を納めた配列
  // サイズは mNodeNum
  ymuint* mNodeTypeArray{nullptr};

  // ファンインのノード番号＋反転属性を納めた配列
  // サイズは mNodeNum * 2
  ymuint* mEdgeArray{nullptr};

  // パタン数
  int mPatNum{0};

  // パタンの配列
  // サイズは mPatNum
  CiPatGraph* mPatArray{nullptr};

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief ノード数を返す．
inline
int
CiPatMgr::node_num() const
{
  return mNodeNum;
}

// @brief ノードの種類を返す．
// @param[in] id ノード番号 ( 0 <= id < node_num() )
inline
ClibPatType
CiPatMgr::node_type(int id) const
{
  return static_cast<ClibPatType>(mNodeTypeArray[id] & 3U);
}

// @brief ノードが入力ノードの時に入力番号を返す．
// @param[in] id ノード番号 ( 0 <= id < node_num() )
// @note 入力ノードでない場合の返り値は不定
inline
int
CiPatMgr::input_id(int id) const
{
  return (mNodeTypeArray[id] >> 2);
}

// @brief 入力のノード番号を返す．
// @param[in] input_id 入力番号 ( 0 <= input_id < input_num() )
// @return input_id の入力に対応するノードのノード番号
inline
int
CiPatMgr::input_node(int input_id) const
{
  return input_id;
}

// @brief 総枝数を返す．
inline
int
CiPatMgr::edge_num() const
{
  return node_num() * 2;
}

// @brief 枝のファンイン元のノード番号を返す．
// @param[in] id 枝番号 ( 0 <= id < node_num() * 2 )
inline
int
CiPatMgr::edge_from(int id) const
{
  return (mEdgeArray[id] >> 1);
}

// @brief 枝のファンアウト先のノード番号を返す．
// @param[in] id 枝番号 ( 0 <= id < node_num() * 2 )
inline
int
CiPatMgr::edge_to(int id) const
{
  return (id / 2);
}

// @brief 枝のファンアウト先の入力位置( 0 or 1 ) を返す．
// @param[in] id 枝番号 ( 0 <= id < node_num() * 2 )
inline
int
CiPatMgr::edge_pos(int id) const
{
  return (id & 1U);
}

// @brief 枝の反転属性を返す．
// @param[in] id 枝番号 ( 0 <= id < node_num() * 2 )
inline
bool
CiPatMgr::edge_inv(int id) const
{
  return static_cast<bool>(mEdgeArray[id] & 1U);
}

// @brief 総パタン数を返す．
inline
int
CiPatMgr::pat_num() const
{
  return mPatNum;
}

END_NAMESPACE_YM_CLIB

#endif // CIPATMGR_H
