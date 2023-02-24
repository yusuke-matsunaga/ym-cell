#ifndef YM_CLIBBUS_H
#define YM_CLIBBUS_H

/// @file ym/ClibBus.h
/// @brief ClibBus のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibHandle.h"
#include "ym/ClibList.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroupn
/// @class ClibBus ClibBus.h "ym/ClibBus.h"
/// @brief バスを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibBus :
  public ClibHandle
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 不正値となる．
  ClibBus() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibBus(
    const ClibLibraryPtr& library, ///< [in] ライブラリ
    SizeType id                    ///< [in] ID番号
  ) : ClibHandle{library, id}
  {
  }

  /// @brief デストラクタ
  ~ClibBus() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const;

  /// @brief バスの型の取得
  ClibBusType
  bus_type() const;

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

#endif // YM_CLIBBUS_H
