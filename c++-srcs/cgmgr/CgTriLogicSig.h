#ifndef CGTRILOGICSIG_H
#define CGTRILOGICSIG_H

/// @file CgTriLogicSig.h
/// @brief CgTriLogicSig のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgSigRep.h"
#include "ym/TvFunc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CgTriLogicSig CgTriLogicSig.h "CgTriLogicSig.h"
/// @brief tristate 条件を持つ1出力論理関数のシグネチャを表すクラス
//////////////////////////////////////////////////////////////////////
class CgTriLogicSig :
  public CgSigRep
{
public:

  /// @brief コンストラクタ
  CgTriLogicSig(
    const TvFunc& func,    ///< [in] 対象の論理関数
    const TvFunc& tristate ///< [in] tristate条件
  );

  /// @brief デストラクタ
  ~CgTriLogicSig() = default;

  /// @brief シグネチャを作る．
  static
  unique_ptr<const CgSigRep>
  make_signature(
    const TvFunc& func,    ///< [in] 対象の論理関数
    const TvFunc& tristate ///< [in] tristate条件
  )
  {
    return unique_ptr<const CgSigRep>{new CgTriLogicSig{func, tristate}};
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

  // 論理関数
  TvFunc mFunc;

  // tristate 条件
  TvFunc mTristate;

};

END_NAMESPACE_YM_CLIB

#endif // CGTRILOGICSIG_H
