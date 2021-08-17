#ifndef YM_CLIBBUS_H
#define YM_CLIBBUS_H

/// @file ym/ClibBus.h
/// @brief ClibBus のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroupn
/// @class ClibBus ClibBus.h "ym/ClibBus.h"
/// @brief バスを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibBus
{
public:

  /// @brief デストラクタ
  virtual
  ~ClibBus() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  virtual
  string
  name() const = 0;

  /// @brief バスの型の取得
  virtual
  const ClibBusType&
  bus_type() const = 0;

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

#endif // YM_CLIBBUS_H
