#ifndef CGGENLOGICSIG_H
#define CGGENLOGICSIG_H

/// @file CgGenLogicSig.h
/// @brief CgGenLogicSig のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgSigRep.h"
#include "ym/TvFunc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CgGenLogicSig CgGenLogicSig.h "CgGenLogicSig.h"
/// @brief 一般的な論理関数のシグネチャを表すクラス
//////////////////////////////////////////////////////////////////////
class CgGenLogicSig :
  public CgSigRep
{
public:

  /// @brief コンストラクタ
  CgGenLogicSig(
    SizeType ni,                        ///< [in] 入力数
    SizeType no,                        ///< [in] 出力数
    SizeType nb,                        ///< [in] 入出力数
    const vector<TvFunc>& func_list,    ///< [in] 対象の論理関数のリスト
    const vector<TvFunc>& tristate_list ///< [in] tristate条件のリスト
  );

  /// @brief デストラクタ
  ~CgGenLogicSig() = default;

  /// @brief シグネチャを作る．
  static
  unique_ptr<const CgSigRep>
  make_signature(
    SizeType ni,                        ///< [in] 入力数
    SizeType no,                        ///< [in] 出力数
    SizeType nb,                        ///< [in] 入出力数
    const vector<TvFunc>& func_list,    ///< [in] 対象の論理関数のリスト
    const vector<TvFunc>& tristate_list ///< [in] tristate条件のリスト
  )
  {
    auto ptr = new CgGenLogicSig{ni, no, nb, func_list, tristate_list};
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

};

END_NAMESPACE_YM_CLIB

#endif // CGGENLOGICSIG_H
