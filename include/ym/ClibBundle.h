#ifndef YM_CLIBBUNDLE_H
#define YM_CLIBBUNDLE_H

/// @file ym/ClibBundle.h
/// @brief ClibBundle のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibBundle ClibBundle.h "ym/ClibBundle.h"
/// @brief バンドルを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibBundle
{
public:

  /// @brief デストラクタ
  virtual
  ~ClibBundle() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  virtual
  string
  name() const = 0;

  /// @brief ピン数の取得
  virtual
  int
  pin_num() const = 0;

  /// @brief ピンの取得
  virtual
  const ClibCellPin&
  pin(
    int pos ///< [in] 位置番号 ( 0 <= pos < pin_num() )
  ) const = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBBUNDLE_H
