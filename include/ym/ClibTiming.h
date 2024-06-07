﻿#ifndef YM_CLIBTIMING_H
#define YM_CLIBTIMING_H

/// @file ym/ClibTiming.h
/// @brief ClibTiming のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellElem.h"
#include "ym/ClibTime.h"
#include "ym/ClibResistance.h"
#include "ym/logic.h"


BEGIN_NAMESPACE_YM_CLIB

class CiTiming;

//////////////////////////////////////////////////////////////////////
/// @ingroup ClibGroup
/// @class ClibTiming ClibTiming.h "ym/ClibTiming.h"
/// @brief タイミング情報を表すクラス
//////////////////////////////////////////////////////////////////////
class ClibTiming :
  public ClibCellElem<CiTiming>
{
public:

  /// @brief 空のコンストラクタ
  ClibTiming() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibTiming(
    const CiCell* cell,  ///< [in] 親のセル
    const CiTiming* impl ///< [in] 本体
  ) : ClibCellElem{cell, impl}
  {
  }

  /// @brief デストラクタ
  ~ClibTiming() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 共通の属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 型の取得
  ClibTimingType
  type() const;

  /// @brief タイミング条件式の取得
  ///
  /// ない場合には定数1の式が返される．
  Expr
  timing_cond() const;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック/CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり固有遅延の取得
  ClibTime
  intrinsic_rise() const;

  /// @brief 立ち下がり固有遅延の取得
  ClibTime
  intrinsic_fall() const;

  /// @brief 立ち上がりスロープ遅延の取得
  ClibTime
  slope_rise() const;

  /// @brief 立ち下がりスロープ遅延の取得
  ClibTime
  slope_fall() const;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延の取得
  ClibResistance
  rise_resistance() const;

  /// @brief 立ち下がり遷移遅延の取得
  ClibResistance
  fall_resistance() const;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がりピン抵抗の取得
  ClibResistance
  rise_pin_resistance(
    SizeType piece_id ///< [in] 区間番号
  ) const;

  /// @brief 立ち下がりピン抵抗の取得
  ClibResistance
  fall_pin_resistance(
    SizeType piece_id ///< [in] 区間番号
  ) const;

  /// @brief 立ち上がりY切片
  ClibTime
  rise_delay_intercept(
    SizeType piece_id ///< [in] 区間番号
  ) const;

  /// @brief 立ち下がりY切片
  ClibTime
  fall_delay_intercept(
    SizeType piece_id ///< [in] 区間番号
  ) const;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延テーブルの取得
  ClibLut
  rise_transition() const;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  ClibLut
  fall_transition() const;

  /// @brief 立ち上がり伝搬遅延テーブルの取得
  ClibLut
  rise_propagation() const;

  /// @brief 立ち下がり伝搬遅延テーブルの取得
  ClibLut
  fall_propagation() const;

  /// @brief 立ち上がりセル遅延テーブルの取得
  ClibLut
  cell_rise() const;

  /// @brief 立ち下がりセル遅延テーブルの取得
  ClibLut
  cell_fall() const;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBTIMING_H
