#ifndef YM_CLIBTIMING_H
#define YM_CLIBTIMING_H

/// @file ym/ClibTiming.h
/// @brief ClibTiming のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
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
class ClibTiming
{
public:

  /// @brief 空のコンストラクタ
  ClibTiming() = default;

  /// @brief 内容を指定したコンストラクタ
  ClibTiming(
    const CiTiming* impl ///< [in] 本体
  );

  /// @brief デストラクタ
  ~ClibTiming();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通の属性
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  ///
  /// timing = cell->timing(id); の時，timing->id() = id となる．
  SizeType
  id() const;

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

  /// @brief 立ち上がり遷移遅延の取得
  ClibResistance
  rise_pin_resistance() const;

  /// @brief 立ち下がり遷移遅延の取得
  ClibResistance
  fall_pin_resistance() const;

  /// @brief 立ち上がり？？？
  ClibTime
  rise_delay_intercept() const;

  /// @brief 立ち下がり？？？
  ClibTime
  fall_delay_intercept() const;


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


public:
  //////////////////////////////////////////////////////////////////////
  // mImpl に関する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 適正な値を持っている時 true を返す．
  bool
  is_valid() const
  {
    return mImpl != nullptr;
  }

  /// @brief 不正値の時 true を返す．
  bool
  is_invalid() const
  {
    return !is_valid();
  }

  /// @brief 等価比較
  bool
  operator==(
    const ClibTiming& right
  ) const
  {
    return mImpl == right.mImpl;
  }

  /// @brief 非等価比較
  bool
  operator!=(
    const ClibTiming& right
  ) const
  {
    return !operator==(right);
  }

  /// @brief 適正な値を持っているかチェックする．
  void
  _check_valid() const
  {
    if ( !is_valid() ) {
      throw std::invalid_argument{"not having a valid data"};
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 実装
  const CiTiming* mImpl;

};

END_NAMESPACE_YM_CLIB

#endif // YM_CLIBTIMING_H
