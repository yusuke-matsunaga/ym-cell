#ifndef YM_CLIBLUTTEMPLATE_H
#define YM_CLIBLUTTEMPLATE_H

/// @file ym/ClibLutTemplate.h
/// @brief ClibLutTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibHandle.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibLutTemplate ClibLutTemplate.h "ym/ClibLutTemplate.h"
/// @brief ルックアップテーブルのテンプレートを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibLutTemplate :
  public ClibHandle
{
public:

  /// @brief 空のコンストラクタ
  ///
  /// 不正値となる．
  ClibLutTemplate() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibLutTemplate(
    const ClibLibraryPtr& library, ///< [in] ライブラリ
    SizeType id                    ///< [in] ID番号
  ) : ClibHandle{library, id}
  {
  }

  /// @brief デストラクタ
  ~ClibLutTemplate() = default;


public:
  //////////////////////////////////////////////////////////////////////
  /// @name 属性の取得
  /// @{
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前の取得
  string
  name() const;

  /// @brief 次元数の取得
  SizeType
  dimension() const;

  /// @brief 変数型の取得
  ClibVarType
  variable_type(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const;

  /// @brief インデックス数の取得
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const;

  /// @brief デフォルトインデックス値の取得
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const;

  //////////////////////////////////////////////////////////////////////
  /// @}
  //////////////////////////////////////////////////////////////////////

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBLUTTEMPLATE_H
