#ifndef CITIMING_H
#define CITIMING_H

/// @file　CiTiming.h
/// @brief ClibTiming の実装クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021, 2024 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ClibTime.h"
#include "ym/ClibResistance.h"
#include "ym/Expr.h"
#include "ci/CiLibObj.h"
#include "ci/CiLut.h"


BEGIN_NAMESPACE_YM_CLIB

class Serializer;
class Deserializer;

//////////////////////////////////////////////////////////////////////
/// @class CiTiming CiTiming.h "CiTiming.h"
/// @brief 共通の基底クラス
//////////////////////////////////////////////////////////////////////
class CiTiming
{
public:

  /// @brief restore() 用のコンストラクタ
  CiTiming() = default;

  /// @brief コンストラクタ
  CiTiming(
    ClibTimingType type,      ///< [in] タイミング条件の型
    const Expr& cond          ///< [in] タイミング条件を表す式
  ) : mType{type},
      mCond{cond}
  {
  };

  /// @brief デストラクタ
  virtual
  ~CiTiming() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 共通の属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 型の取得
  ClibTimingType
  type() const
  {
    return mType;
  }

  /// @brief タイミング条件式の取得
  ///
  /// ない場合には不適正な式が返される．
  Expr
  timing_cond() const
  {
    return mCond;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック/CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり固有遅延の取得
  virtual
  ClibTime
  intrinsic_rise() const;

  /// @brief 立ち下がり固有遅延の取得
  virtual
  ClibTime
  intrinsic_fall() const;

  /// @brief 立ち上がりスロープ遅延の取得
  virtual
  ClibTime
  slope_rise() const;

  /// @brief 立ち下がりスロープ遅延の取得
  virtual
  ClibTime
  slope_fall() const;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延の取得
  virtual
  ClibResistance
  rise_resistance() const;

  /// @brief 立ち下がり遷移遅延の取得
  virtual
  ClibResistance
  fall_resistance() const;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延の取得
  virtual
  ClibResistance
  rise_pin_resistance() const;

  /// @brief 立ち下がり遷移遅延の取得
  virtual
  ClibResistance
  fall_pin_resistance() const;

  /// @brief 立ち上がり？？？
  virtual
  ClibTime
  rise_delay_intercept() const;

  /// @brief 立ち下がり？？？
  virtual
  ClibTime
  fall_delay_intercept() const;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延テーブルの取得
  virtual
  const CiLut*
  rise_transition() const;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  virtual
  const CiLut*
  fall_transition() const;

  /// @brief 立ち上がり伝搬遅延テーブルの取得
  virtual
  const CiLut*
  rise_propagation() const;

  /// @brief 立ち下がり伝搬遅延テーブルの取得
  virtual
  const CiLut*
  fall_propagation() const;

  /// @brief 立ち上がりセル遅延テーブルの取得
  virtual
  const CiLut*
  cell_rise() const;

  /// @brief 立ち下がりセル遅延テーブルの取得
  virtual
  const CiLut*
  cell_fall() const;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をシリアライズする．
  void
  serialize(
    Serializer& s ///< [in] シリアライザ
  ) const;

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(
    Serializer& s ///< [in] シリアライザ
 ) const = 0;

  /// @brief 内容を読み込む．
  static
  unique_ptr<CiTiming>
  restore(
    Deserializer& s ///< [in] デシリアライザ
  );


protected:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 用の下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通な情報をダンプする．
  void
  dump_common(
    Serializer& s, ///< [in] シリアライザ
    int type_id    ///< [in] ClibTimingType を表すシグネチャ
  ) const;

  /// @brief 内容を復元する．
  virtual
  void
  _restore(
    Deserializer& s  ///< [in] デシリアライザ
  );


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 型
  ClibTimingType mType{ClibTimingType::none};

  // タイミング条件
  Expr mCond;

};

END_NAMESPACE_YM_CLIB

#endif // CITIMING_H
