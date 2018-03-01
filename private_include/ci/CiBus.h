#ifndef CIBUS_H
#define CIBUS_H

/// @file CiBus.h
/// @brief CiBus のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibBus.h"
#include "ym/ShString.h"
#include "ci/CiCellPinList.h"
#include "ym/Alloc.h"


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
  CiBus();

  /// @brief デストラクタ
  ~CiBus();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  virtual
  string
  name() const;

  /// @brief バスの型の取得
  virtual
  const ClibBusType*
  bus_type() const;

  /// @brief ピン数の取得
  virtual
  int
  pin_num() const;

  /// @brief ピンの取得
  /// @param[in] pos 位置番号 ( 0 <= pos < pin_num() )
  virtual
  const ClibCellPin*
  pin(int pos) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を初期化する．
  void
  init(const ShString& name,
       const ClibBusType* bus_type,
       const vector<CiCellPin*>& pin_list,
       Alloc& alloc);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // バスの型
  const ClibBusType* mBusType;

  // ピンのリスト
  CiCellPinList mPinList;

};

END_NAMESPACE_YM_CLIB

#endif // CIBUS_H
