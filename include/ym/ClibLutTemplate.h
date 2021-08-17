#ifndef YM_CLIBLUTTEMPLATE_H
#define YM_CLIBLUTTEMPLATE_H

/// @file ym/ClibLutTemplate.h
/// @brief ClibLutTemplate のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibLutTemplate ClibLutTemplate.h "ym/ClibLutTemplate.h"
/// @brief ルックアップテーブルのテンプレートを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibLutTemplate
{
protected:

  /// @brief デストラクタ
  virtual
  ~ClibLutTemplate() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  virtual
  int
  id() const = 0;

  /// @brief 名前の取得
  virtual
  const char*
  name() const = 0;

  /// @brief 次元数の取得
  virtual
  int
  dimension() const = 0;

  /// @brief 変数型の取得
  virtual
  ClibVarType
  variable_type(
    int var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const = 0;

  /// @brief インデックス数の取得
  virtual
  int
  index_num(
    int var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const = 0;

  /// @brief デフォルトインデックス値の取得
  virtual
  double
  index(
    int var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    int pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBLUTTEMPLATE_H
