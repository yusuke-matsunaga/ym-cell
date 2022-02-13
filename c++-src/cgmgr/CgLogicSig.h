#ifndef CGLOGICSIG_H
#define CGLOGICSIG_H

/// @file CgLogicSig.h
/// @brief CgLogicSig のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "CgSignature.h"
#include "ym/TvFunc.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CgLogicSig CgLogicSig.h "CgLogicSig.h"
/// @brief 単一出力の論理関数に対するシグネチャ
//////////////////////////////////////////////////////////////////////
class CgLogicSig :
  public CgSignature
{
public:

  /// @brief コンストラクタ
  CgLogicSig(
    const TvFunc& func ///< [in] 対象の論理関数
  );

  /// @brief デストラクタ
  ~CgLogicSig() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief シグネチャ文字列を返す．
  string
  str() const override;

  /// @brief 変換を施した後のシグネチャ文字列を求める．
  string
  str(
    const ClibIOMap& iomap ///< [in] 変換マップ
  ) const override;

  /// @brief 代表シグネチャに対する変換を求める．
  ClibIOMap
  rep_map() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 論理関数
  TvFunc mFunc;
};

END_NAMESPACE_YM_CLIB

#endif // CGLOGICSIG_H
