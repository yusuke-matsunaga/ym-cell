﻿#ifndef YM_CLIBBUNDLE_H
#define YM_CLIBBUNDLE_H

/// @file ym/ClibBundle.h
/// @brief ClibBundle のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibHandle.h"
#include "ym/ClibList.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibBundle ClibBundle.h "ym/ClibBundle.h"
/// @brief バンドルを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibBundle :
  public ClibHandle
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 不正値となる．
  ClibBundle() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibBundle(
    const ClibLibraryPtr& library, ///< [in] ライブラリ
    SizeType id                    ///< [in] ID番号
  ) : ClibHandle{library, id}
  {
  }

  /// @brief デストラクタ
  ~ClibBundle() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const;

  /// @brief ピン数の取得
  SizeType
  pin_num() const;

  /// @brief ピンの取得
  ClibPin
  pin(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < pin_num() )
  ) const;

  /// @brief ピンのリストの取得
  ClibPinList
  pin_list() const;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBBUNDLE_H
