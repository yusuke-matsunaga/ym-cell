﻿#ifndef YM_CLIBCELLPIN_H
#define YM_CLIBCELLPIN_H

/// @file ym/ClibCellPin.h
/// @brief ClibCellPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/logic.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibCellPin ClibCellPin.h "ym/ClibCellPin.h"
/// @brief セルのピンを表すクラス
//////////////////////////////////////////////////////////////////////
class ClibCellPin
{
protected:

  /// @brief デストラクタ
  virtual
  ~ClibCellPin() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン番号を返す．
  virtual
  int
  pin_id() const = 0;

  /// @brief ピン名を返す．
  virtual
  string
  name() const = 0;

  /// @brief 方向を返す．
  virtual
  ClibDirection
  direction() const = 0;

  /// @brief 入力ピンの時に true を返す．
  ///
  /// direction() == ClibDirection::input と等価
  virtual
  bool
  is_input() const = 0;

  /// @brief 出力ピンの時に true を返す．
  ///
  /// direction() == ClibDirection::output と等価
  virtual
  bool
  is_output() const = 0;

  /// @brief 入出力ピンの時に true を返す．
  ///
  /// direction() == ClibDirection::inout と等価
  virtual
  bool
  is_inout() const = 0;

  /// @brief 内部ピンの時に true を返す．
  ///
  /// direction() == ClibDirection::internal と等価
  virtual
  bool
  is_internal() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  ///
  /// 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  virtual
  int
  input_id() const = 0;

  /// @brief 負荷容量を返す．
  virtual
  ClibCapacitance
  capacitance() const = 0;

  /// @brief 立ち上がり時の負荷容量を返す．
  virtual
  ClibCapacitance
  rise_capacitance() const = 0;

  /// @brief 立ち下がり時の負荷容量を返す．
  virtual
  ClibCapacitance
  fall_capacitance() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // 出力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力ピン番号を返す．
  ///
  /// 出力ピンもしくは入出力ピンの時のみ意味を持つ．
  virtual
  int
  output_id() const = 0;

  /// @brief 論理式を持っているときに true を返す．
  virtual
  bool
  has_function() const = 0;

  /// @brief 機能を表す論理式を返す．
  virtual
  Expr
  function() const = 0;

  /// @brief three_state 属性を持っているときに true を返す．
  virtual
  bool
  has_three_state() const = 0;

  /// @brief three_state 論理式を返す．
  virtual
  Expr
  three_state() const = 0;

  /// @brief 最大ファンアウト容量を返す．
  virtual
  ClibCapacitance
  max_fanout() const = 0;

  /// @brief 最小ファンアウト容量を返す．
  virtual
  ClibCapacitance
  min_fanout() const = 0;

  /// @brief 最大負荷容量を返す．
  virtual
  ClibCapacitance
  max_capacitance() const = 0;

  /// @brief 最小負荷容量を返す．
  virtual
  ClibCapacitance
  min_capacitance() const = 0;

  /// @brief 最大遷移時間を返す．
  virtual
  ClibTime
  max_transition() const = 0;

  /// @brief 最小遷移時間を返す．
  virtual
  ClibTime
  min_transition() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // 内部ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 内部ピン番号を返す．
  ///
  /// 内部ピンの時のみ意味を持つ．
  virtual
  int
  internal_id() const = 0;


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

#endif // YM_CLIBCELLPIN_H
