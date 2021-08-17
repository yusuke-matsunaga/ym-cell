#ifndef CIBUSTYPE_H
#define CIBUSTYPE_H

/// @file CiBusType.h
/// @brief CiBusType のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibBusType.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiBusType CiBusType.h "CiBusType.h"
/// @brief ClibBusType の実装クラス
//////////////////////////////////////////////////////////////////////
class CiBusType :
  public ClibBusType
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiBusType(
    const ShString& name, ///< [in] 名前
    int bit_from,         ///< [in] 開始位置
    int bit_to            ///< [in] 終了位置
  );

  /// @brief デストラクタ
  ~CiBusType() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const override;

  /// @brief base_type の取得
  BaseType
  base_type() const override;

  /// @brief data_type の取得
  DataType
  data_type() const override;

  /// @brief ビット幅の取得
  int
  bit_width() const override;

  /// @brief 開始ビットの取得
  int
  bit_from() const override;

  /// @brief 終了ビットの取得
  int
  bit_to() const override;

  /// @brief 向きの取得
  /// @note true の時，降順を表す．
  bool
  downto() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // ビット幅
  int mBitWidth;

  // 開始ビット
  int mBitFrom;

  // 終了ビット
  int mBitTo;

  // 向き
  bool mDownTo;

};

END_NAMESPACE_YM_CLIB

#endif // CIBUS_H
