#ifndef YM_CLIBBUSTYPE_H
#define YM_CLIBBUSTYPE_H

/// @file ym/ClibBusType.h
/// @brief ClibBusType のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibBusType ClibBusType.h "ym/ClibBusType.h"
/// @brief バスタイプを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibBusType
{
public:

  /// @brief base_type を表す型
  enum BaseType {
    kArrayType
  };

  /// @brief data_type を表す型
  enum DataType {
    kBitType
  };


public:

  /// @brief コンストラクタ
  ClibBusType() { }

  /// @brief デストラクタ
  virtual
  ~ClibBusType() { }


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  virtual
  string
  name() const = 0;

  /// @brief base_type の取得
  virtual
  BaseType
  base_type() const = 0;

  /// @brief data_type の取得
  virtual
  DataType
  data_type() const = 0;

  /// @brief ビット幅の取得
  virtual
  ymuint
  bit_width() const = 0;

  /// @brief 開始ビットの取得
  virtual
  ymint
  bit_from() const = 0;

  /// @brief 終了ビットの取得
  virtual
  ymint
  bit_to() const = 0;

  /// @brief 向きの取得
  /// @note true の時，降順を表す．
  virtual
  bool
  downto() const = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBBUS_H
