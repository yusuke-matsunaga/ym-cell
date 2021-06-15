#ifndef YM_CLIBTIMING_H
#define YM_CLIBTIMING_H

/// @file ym/ClibTiming.h
/// @brief ClibTiming のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/logic.h"
#include "ym/ClibTime.h"
#include "ym/ClibResistance.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibTiming ClibTiming.h "ym/ClibTiming.h"
/// @brief タイミング情報を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibTiming
{
protected:

  /// @brief デストラクタ
  virtual
  ~ClibTiming() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 共通の属性
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  ///
  /// timing = cell->timing(id); の時，timing->id() = id となる．
  virtual
  int
  id() const = 0;

  /// @brief 型の取得
  virtual
  ClibTimingType
  type() const = 0;

  /// @brief タイミング条件式の取得
  ///
  /// ない場合には定数1の式が返される．
  virtual
  Expr
  timing_cond() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック/CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり固有遅延の取得
  virtual
  ClibTime
  intrinsic_rise() const = 0;

  /// @brief 立ち下がり固有遅延の取得
  virtual
  ClibTime
  intrinsic_fall() const = 0;

  /// @brief 立ち上がりスロープ遅延の取得
  virtual
  ClibTime
  slope_rise() const = 0;

  /// @brief 立ち下がりスロープ遅延の取得
  virtual
  ClibTime
  slope_fall() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延の取得
  virtual
  ClibResistance
  rise_resistance() const = 0;

  /// @brief 立ち下がり遷移遅延の取得
  virtual
  ClibResistance
  fall_resistance() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延の取得
  virtual
  ClibResistance
  rise_pin_resistance() const = 0;

  /// @brief 立ち下がり遷移遅延の取得
  virtual
  ClibResistance
  fall_pin_resistance() const = 0;

  /// @brief 立ち上がり？？？
  virtual
  ClibTime
  rise_delay_intercept() const = 0;

  /// @brief 立ち下がり？？？
  virtual
  ClibTime
  fall_delay_intercept() const = 0;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延テーブルの取得
  virtual
  const ClibLut&
  rise_transition() const = 0;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  virtual
  const ClibLut&
  fall_transition() const = 0;

  /// @brief 立ち上がり伝搬遅延テーブルの取得
  virtual
  const ClibLut&
  rise_propagation() const = 0;

  /// @brief 立ち下がり伝搬遅延テーブルの取得
  virtual
  const ClibLut&
  fall_propagation() const = 0;

  /// @brief 立ち上がりセル遅延テーブルの取得
  virtual
  const ClibLut&
  cell_rise() const = 0;

  /// @brief 立ち下がりセル遅延テーブルの取得
  virtual
  const ClibLut&
  cell_fall() const = 0;


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

#endif // YM_CLIBTIMING_H
