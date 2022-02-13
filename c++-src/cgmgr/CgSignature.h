#ifndef CGSIGNATURE_H
#define CGSIGNATURE_H

/// @file CgSignature.h
/// @brief CgSignature のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CgSignature CgSignature.h "CgSignature.h"
/// @brief CgMgr 用のシグネチャを表す純粋仮想基底クラス
//////////////////////////////////////////////////////////////////////
class CgSignature
{
public:

  /// @brief デストラクタ
  virtual
  ~CgSignature() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief シグネチャ文字列を返す．
  virtual
  string
  str() const = 0;

  /// @brief 変換を施した後のシグネチャ文字列を求める．
  virtual
  string
  str(
    const ClibIOMap& iomap ///< [in] 変換マップ
  ) const = 0;

  /// @brief 代表シグネチャに対する変換を求める．
  virtual
  ClibIOMap
  rep_map() const = 0;

};

END_NAMESPACE_YM_CLIB

#endif // CGSIGNATURE_H
