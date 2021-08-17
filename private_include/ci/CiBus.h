#ifndef CIBUS_H
#define CIBUS_H

/// @file CiBus.h
/// @brief CiBus のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibBus.h"
#include "ym/ClibBusType.h"
#include "ym/ClibObjList.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiBus CiBus.h "CiBus.h"
/// @brief ClibBus の実装クラス
//////////////////////////////////////////////////////////////////////
class CiBus :
  public ClibBus
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiBus() = default;

  /// @brief デストラクタ
  ~CiBus() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const override;

  /// @brief バスの型の取得
  const ClibBusType&
  bus_type() const override;

  /// @brief ピン数の取得
  int
  pin_num() const override;

  /// @brief ピンの取得
  const ClibCellPin&
  pin(
    int pos ///< [in] 位置番号 ( 0 <= pos < pin_num() )
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  void
  init(
    const ShString& name,
    const ClibBusType* bus_type,
    const vector<ClibCellPin*>& pin_list
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // バスの型
  const ClibBusType* mBusType{nullptr};

  // ピンのリスト
  ClibCellPinList mPinList;

};

END_NAMESPACE_YM_CLIB

#endif // CIBUS_H
