#ifndef YM_CLIBBUSTYPE_H
#define YM_CLIBBUSTYPE_H

/// @file ym/ClibBusType.h
/// @brief ClibBusType のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibHandle.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibBusType ClibBusType.h "ym/ClibBusType.h"
/// @brief バスタイプを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibBusType :
  public ClibHandle
{
public:

  /// @brief base_type を表す型
  enum BaseType {
    // 今はこれだけ
    ArrayType
  };

  /// @brief data_type を表す型
  enum DataType {
    // 今はこれだけ
    BitType
  };


public:

  /// @brief コンストラクタ
  ClibBusType() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibBusType(
    const ClibLibraryPtr& library, ///< [in] ライブラリ
    SizeType id                    ///< [in] ID番号
  ) : ClibHandle{library, id}
  {
  }

  /// @brief デストラクタ
  ~ClibBusType() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const;

  /// @brief base_type の取得
  BaseType
  base_type() const;

  /// @brief data_type の取得
  DataType
  data_type() const;

  /// @brief ビット幅の取得
  SizeType
  bit_width() const;

  /// @brief 開始ビットの取得
  SizeType
  bit_from() const;

  /// @brief 終了ビットの取得
  SizeType
  bit_to() const;

  /// @brief 向きの取得
  ///
  /// true の時，降順を表す．
  bool
  downto() const;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBBUS_H
