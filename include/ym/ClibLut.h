﻿#ifndef YM_CLIBLUT_H
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
/// @brief ルックアップテーブルを表すクラス
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

  /// @brief テンプレート番号の取得
  virtual
  int
  template_id() const = 0;

  /// @brief 次元数の取得
  virtual
  int
  dimension() const = 0;

  /// @brief 変数型の取得
  virtual
  ClibVarType
  variable_type(int var) const ///< [in] 変数番号 ( 0 <= var < dimension() )
  = 0;

  /// @brief インデックス数の取得
  virtual
  int
  index_num(int var) const ///< [in] 変数番号 ( 0 <= var < dimension() )
  = 0;

  /// @brief インデックス値の取得
  virtual
  double
  index(int var,       ///< [in] 変数番号 ( 0 <= var < dimension() )
	int pos) const ///< [in] 位置番号 ( 0 <= pos < index_num(var) )
  = 0;

  /// @brief 格子点の値の取得
  ///
  /// pos_array のサイズは dimension() と同じ
  virtual
  double
  grid_value(const vector<int>& pos_array) const ///< [in] pos_array 格子点座標
  = 0;

  /// @brief 値の取得
  ///
  /// @note val_array のサイズは dimension() と同じ
  virtual
  double
  value(const vector<double>& val_array) const ///< [in] 入力の値の配列
  = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(ostream& s) const ///< [in] 出力先のストリーム
  = 0;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBLUT_H
