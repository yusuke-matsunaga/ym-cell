#ifndef CGFLSIG_H
#define CGFLSIG_H

/// @file CgFLSig.h
/// @brief CgFLSig のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgSigRep.h"
#include "ym/TvFunc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CgFLSig CgFLSig.h "CgFLSig.h"
/// @brief CgFFSig と CgLatchSig の共通の親クラス
//////////////////////////////////////////////////////////////////////
class CgFLSig :
  public CgSigRep
{
public:

  /// @brief コンストラクタ
  CgFLSig(
    SizeType ni,                         ///< [in] 入力数
    SizeType no,                         ///< [in] 出力数
    SizeType nb,                         ///< [in] 入出力数
    const vector<TvFunc>& func_list,     ///< [in] 対象の論理関数のリスト
    const vector<TvFunc>& tristate_list, ///< [in] tristate条件のリスト
    const TvFunc& clocked_on,            ///< [in] マスタークロック
    const TvFunc& clocked_on_also,       ///< [in] スレーブクロック
    const TvFunc& next_state,            ///< [in] 次状態関数
    const TvFunc& clear,                 ///< [in] クリア条件
    const TvFunc& preset,                ///< [in] プリセット条件
    ClibCPV clear_preset_var1, ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2  ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  );

  /// @brief デストラクタ
  ~CgFLSig() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 変換を施した後のシグネチャを返す．
  unique_ptr<const CgSigRep>
  xform(
    const ClibIOMap& iomap ///< [in] 変換マップ
  ) const override;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief インスタンスを作る．
  virtual
  unique_ptr<const CgSigRep>
  make_instance(
    SizeType ni,                         ///< [in] 入力数
    SizeType no,                         ///< [in] 出力数
    SizeType nb,                         ///< [in] 入出力数
    const vector<TvFunc>& func_list,     ///< [in] 対象の論理関数のリスト
    const vector<TvFunc>& tristate_list, ///< [in] tristate条件のリスト
    const TvFunc& clocked_on,            ///< [in] マスタークロック
    const TvFunc& clocked_on_also,       ///< [in] スレーブクロック
    const TvFunc& next_state,            ///< [in] 次状態関数
    const TvFunc& clear,                 ///< [in] クリア条件
    const TvFunc& preset,                ///< [in] プリセット条件
    ClibCPV clear_preset_var1, ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2  ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  ) const = 0;

  /// @brief シグネチャ文字列の共通部分を返す．
  string
  base_str() const;


private:
  //////////////////////////////////////////////////////////////////////
  // CgSigRep の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 正規形への変換を求める．
  vector<ClibIOMap>
  gen_cannonical_map() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力数
  SizeType mNi;

  // 出力数
  SizeType mNo;

  // 入出力数
  SizeType mNb;

  // 論理関数
  vector<TvFunc> mFuncList;

  // tristate 条件
  vector<TvFunc> mTristateList;

  // clocked_on 関数
  TvFunc mClockedOn;

  // clocked_on_also 関数
  TvFunc mClockedOnAlso;

  // next_state 関数
  TvFunc mNextState;

  // clear 条件
  TvFunc mClear;

  // preset 条件
  TvFunc mPreset;

  // clear_preset_var1
  ClibCPV mCpv1;

  // clear_preset_var2
  ClibCPV mCpv2;

};

END_NAMESPACE_YM_CLIB

#endif // CGFFSIG_H
