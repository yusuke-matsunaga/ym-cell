#ifndef CGLATCHSIG_H
#define CGLATCHSIG_H

/// @file CgLatchSig.h
/// @brief CgLatchSig のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgSigRep.h"
#include "ym/TvFunc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CgLatchSig CgLatchSig.h "CgLatchSig.h"
/// @brief FFのシグネチャを表すクラス
//////////////////////////////////////////////////////////////////////
class CgLatchSig :
  public CgSigRep
{
public:

  /// @brief コンストラクタ
  CgLatchSig(
    SizeType ni,                         ///< [in] 入力数
    SizeType no,                         ///< [in] 出力数
    SizeType nb,                         ///< [in] 入出力数
    const vector<TvFunc>& func_list,     ///< [in] 対象の論理関数のリスト
    const vector<TvFunc>& tristate_list, ///< [in] tristate条件のリスト
    const TvFunc& enable_on,            ///< [in] マスタークロック
    const TvFunc& enable_on_also,       ///< [in] スレーブクロック
    const TvFunc& data_in,            ///< [in] 次状態関数
    const TvFunc& clear,                 ///< [in] クリア条件
    const TvFunc& preset,                ///< [in] プリセット条件
    ClibCPV clear_preset_var1, ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2  ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  ) : mNi{ni},
      mNo{no},
      mNb{nb},
      mFuncList{func_list},
      mTristateList{tristate_list},
      mEnableOn{enable_on},
      mEnableOnAlso{enable_on_also},
      mDataIn{data_in},
      mClear{clear},
      mPreset{preset},
      mCpv1{clear_preset_var1},
      mCpv2{clear_preset_var2}
  {
  }

  /// @brief デストラクタ
  ~CgLatchSig() = default;

  /// @brief シグネチャを作る．
  static
  unique_ptr<const CgSigRep>
  make_signature(
    SizeType ni,                         ///< [in] 入力数
    SizeType no,                         ///< [in] 出力数
    SizeType nb,                         ///< [in] 入出力数
    const vector<TvFunc>& func_list,     ///< [in] 対象の論理関数のリスト
    const vector<TvFunc>& tristate_list, ///< [in] tristate条件のリスト
    const TvFunc& enable_on,             ///< [in] マスタークロック
    const TvFunc& enable_on_also,        ///< [in] スレーブクロック
    const TvFunc& data_in,               ///< [in] 次状態関数
    const TvFunc& clear,                 ///< [in] クリア条件
    const TvFunc& preset,                ///< [in] プリセット条件
    ClibCPV clear_preset_var1, ///< [in] クリアとプリセットが同時にアクティブになった時の値1
    ClibCPV clear_preset_var2  ///< [in] クリアとプリセットが同時にアクティブになった時の値2
  )
  {
    auto ptr = new CgLatchSig{ni, no, nb, func_list, tristate_list,
                              enable_on, enable_on_also, data_in,
			      clear, preset, clear_preset_var1, clear_preset_var2};
    return unique_ptr<const CgSigRep>{ptr};
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief シグネチャ文字列を返す．
  string
  str() const override;

  /// @brief 変換を施した後のシグネチャを返す．
  unique_ptr<const CgSigRep>
  xform(
    const ClibIOMap& iomap ///< [in] 変換マップ
  ) const override;

  /// @brief 代表シグネチャに対する変換を求める．
  ClibIOMap
  rep_map() const override;

  /// @brief 同位体変換のリストを求める．
  vector<ClibIOMap>
  idmap_list() const override;


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

  // enable_on 関数
  TvFunc mEnableOn;

  // enable_on_also 関数
  TvFunc mEnableOnAlso;

  // data_in 関数
  TvFunc mDataIn;

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

#endif // CGLATCHSIG_H
