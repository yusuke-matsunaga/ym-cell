#ifndef YM_CLIBLUT_H
#define YM_CLIBLUT_H

/// @file ym/ClibLut.h
/// @brief ClibLut のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibLut ClibLut.h "ym/ClibLut.h"
/// @brief ルックアップテーブル(LUT)を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibLut
{
protected:

  /// @brief デストラクタ
  virtual
  ~ClibLut() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 属性の取得
  //////////////////////////////////////////////////////////////////////

  /// @brief テンプレートの取得
  virtual
  const ClibLutTemplate&
  lut_template() const = 0;

  /// @brief 次元数の取得
  virtual
  SizeType
  dimension() const = 0;

  /// @brief 変数型の取得
  virtual
  ClibVarType
  variable_type(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const = 0;

  /// @brief インデックス数の取得
  virtual
  SizeType
  index_num(
    SizeType var ///< [in] 変数番号 ( 0 <= var < dimension() )
  ) const = 0;

  /// @brief インデックス値の取得
  virtual
  double
  index(
    SizeType var, ///< [in] 変数番号 ( 0 <= var < dimension() )
    SizeType pos  ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  ) const = 0;

  /// @brief 格子点の値の取得
  ///
  /// pos_array のサイズは dimension() と同じ
  virtual
  double
  grid_value(
    const vector<SizeType>& pos_array ///< [in] pos_array 格子点座標
  ) const = 0;

  /// @brief 値の取得
  ///
  /// @note val_array のサイズは dimension() と同じ
  virtual
  double
  value(
    const vector<double>& val_array ///< [in] 入力の値の配列
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

#endif // YM_CLIBLUT_H
