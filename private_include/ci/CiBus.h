#ifndef CIBUS_H
#define CIBUS_H

/// @file CiBus.h
/// @brief CiBus のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibBus.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiBus CiBus.h "CiBus.h"
/// @brief ClibBus の実装クラス
//////////////////////////////////////////////////////////////////////
class CiBus :
  public ClibBus
{
public:

  /// @brief コンストラクタ
  CiBus(
    const ShString& name,             ///< [in] 名前
    const ClibBusType* bus_type,      ///< [in] バスタイプ
    vector<const ClibPin*>& pin_list  ///< [in] ピンリスト
  ) : mName{name},
      mBusType{bus_type},
      mPinList{pin_list}
  {
  }

  /// @brief デストラクタ
  ~CiBus() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const override;

  /// @brief 名前の取得
  ShString
  _name() const
  {
    return mName;
  }

  /// @brief バスの型の取得
  const ClibBusType&
  bus_type() const override;

  /// @brief ピン数の取得
  SizeType
  pin_num() const override;

  /// @brief ピンの取得
  const ClibPin&
  pin(
    SizeType pos ///< [in] 位置番号 ( 0 <= pos < pin_num() )
  ) const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // バスの型
  const ClibBusType* mBusType{nullptr};

  // ピンのリスト
  vector<const ClibPin*> mPinList;

};

END_NAMESPACE_YM_CLIB

#endif // CIBUS_H
