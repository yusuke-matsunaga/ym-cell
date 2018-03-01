#ifndef CIBUSTYPE_H
#define CIBUSTYPE_H

/// @file CiBusType.h
/// @brief CiBusType のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
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
  /// @param[in] name 名前
  /// @param[in] bit_from 開始位置
  /// @param[in] bit_to 終了位置
  CiBusType(ShString name,
	    int bit_from,
	    int bit_to);

  /// @brief デストラクタ
  virtual
  ~CiBusType();


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  virtual
  string
  name() const;

  /// @brief base_type の取得
  virtual
  BaseType
  base_type() const;

  /// @brief data_type の取得
  virtual
  DataType
  data_type() const;

  /// @brief ビット幅の取得
  virtual
  int
  bit_width() const;

  /// @brief 開始ビットの取得
  virtual
  int
  bit_from() const;

  /// @brief 終了ビットの取得
  virtual
  int
  bit_to() const;

  /// @brief 向きの取得
  /// @note true の時，降順を表す．
  virtual
  bool
  downto() const;


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
