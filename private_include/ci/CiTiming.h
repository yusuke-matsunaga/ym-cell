#ifndef CITIMING_H
#define CITIMING_H

/// @file　CiTiming.h
/// @brief ClibTiming の実装クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibTiming.h"
#include "ym/ClibTime.h"
#include "ym/ClibResistance.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CLIB

class CiLut;

//////////////////////////////////////////////////////////////////////
/// @class CiTiming CiTiming.h "CiTiming.h"
/// @brief 共通の基底クラス
//////////////////////////////////////////////////////////////////////
class CiTiming :
  public ClibTiming
{
  friend class CiCell;

protected:

  /// @brief コンストラクタ
  CiTiming(
    ClibTimingType type, ///< [in] タイミング条件の型
    const Expr& cond     ///< [in] タイミング条件を表す式
  );


public:

  /// @brief デストラクタ
  ~CiTiming();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通の属性
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  ///
  /// timing = cell->timing(id); の時，timing->id() = id となる．
  SizeType
  id() const override;

  /// @brief 型の取得
  ClibTimingType
  type() const override;

  /// @brief タイミング条件式の取得
  /// @note ない場合には定数1の式が返される．
  Expr
  timing_cond() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック/CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり固有遅延の取得
  ClibTime
  intrinsic_rise() const override;

  /// @brief 立ち下がり固有遅延の取得
  ClibTime
  intrinsic_fall() const override;

  /// @brief 立ち上がりスロープ遅延の取得
  ClibTime
  slope_rise() const override;

  /// @brief 立ち下がりスロープ遅延の取得
  ClibTime
  slope_fall() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延の取得
  ClibResistance
  rise_resistance() const override;

  /// @brief 立ち下がり遷移遅延の取得
  ClibResistance
  fall_resistance() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延の取得
  ClibResistance
  rise_pin_resistance() const override;

  /// @brief 立ち下がり遷移遅延の取得
  ClibResistance
  fall_pin_resistance() const override;

  /// @brief 立ち上がり？？？
  ClibTime
  rise_delay_intercept() const override;

  /// @brief 立ち下がり？？？
  ClibTime
  fall_delay_intercept() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延テーブルの取得
  const ClibLut&
  rise_transition() const override;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  const ClibLut&
  fall_transition() const override;

  /// @brief 立ち上がり伝搬遅延テーブルの取得
  const ClibLut&
  rise_propagation() const override;

  /// @brief 立ち下がり伝搬遅延テーブルの取得
  const ClibLut&
  fall_propagation() const override;

  /// @brief 立ち上がりセル遅延テーブルの取得
  const ClibLut&
  cell_rise() const override;

  /// @brief 立ち下がりセル遅延テーブルの取得
  const ClibLut&
  cell_fall() const override;


protected:
  //////////////////////////////////////////////////////////////////////
  // dump 用の下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通な情報をダンプする．
  void
  dump_common(
    ostream& s,     ///< [in] 出力先のストリーム
    ymuint8 type_id ///< [in] 型の ID
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID
  SizeType mId{CLIB_NULLID};

  // 型
  ClibTimingType mType{ClibTimingType::none};

  // タイミング条件
  Expr mCond;

};


//////////////////////////////////////////////////////////////////////
/// @class CiTiming CiTiming.h "CiTiming.h"
/// @brief CMOSジェネリック/折れ線近似タイプ共通の ClibTiming の実装クラス
//////////////////////////////////////////////////////////////////////
class CiTimingGP :
  public CiTiming
{
protected:

  /// @brief コンストラクタ
  CiTimingGP(
    ClibTimingType timing_type, ///< [in] タイミングの型
    const Expr& cond,           ///< [in] タイミング条件を表す式
    ClibTime intrinsic_rise,    ///< [in] 立ち上がり固有遅延
    ClibTime intrinsic_fall,    ///< [in] 立ち下がり固有遅延
    ClibTime slope_rise,        ///< [in] 立ち上がりスロープ遅延
    ClibTime slope_fall         ///< [in] 立ち下がりスロープ遅延
  ) : CiTiming(timing_type, cond),
      mIntrinsicRise{intrinsic_rise},
      mIntrinsicFall{intrinsic_fall},
      mSlopeRise{slope_rise},
      mSlopeFall{slope_fall}
  {
  }

  /// @brief デストラクタ
  ~CiTimingGP() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック/CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり固有遅延の取得
  ClibTime
  intrinsic_rise() const override;

  /// @brief 立ち下がり固有遅延の取得
  ClibTime
  intrinsic_fall() const override;

  /// @brief 立ち上がりスロープ遅延の取得
  ClibTime
  slope_rise() const override;

  /// @brief 立ち下がりスロープ遅延の取得
  ClibTime
  slope_fall() const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がり固有遅延
  ClibTime mIntrinsicRise;

  // 立ち下がり固有遅延
  ClibTime mIntrinsicFall;

  // 立ち上がりスロープ遅延
  ClibTime mSlopeRise;

  // 立ち下がりスロープ遅延
  ClibTime mSlopeFall;

};


//////////////////////////////////////////////////////////////////////
/// @class CiTimingGeneric CiTiming.h "CiTiming.h"
/// @brief CMOSジェネリックタイプの ClibTiming の実装クラス
//////////////////////////////////////////////////////////////////////
class CiTimingGeneric :
  public CiTimingGP
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiTimingGeneric(
    ClibTimingType timing_type,     ///< [in] タイミングの型
    const Expr& cond,               ///< [in] タイミング条件を表す式
    ClibTime intrinsic_rise,        ///< [in] 立ち上がり固有遅延
    ClibTime intrinsic_fall,        ///< [in] 立ち下がり固有遅延
    ClibTime slope_rise,            ///< [in] 立ち上がりスロープ遅延
    ClibTime slope_fall,            ///< [in] 立ち下がりスロープ遅延
    ClibResistance rise_resistance, ///< [in] 立ち上がり遷移遅延パラメータ
    ClibResistance fall_resistance  ///< [in] 立ち下がり遷移遅延パラメータ
  ) : CiTimingGP(timing_type, cond,
		 intrinsic_rise, intrinsic_fall,
		 slope_rise, slope_fall),
      mRiseResistance(rise_resistance),
      mFallResistance(fall_resistance)
  {
  }

  /// @brief デストラクタ
  ~CiTimingGeneric() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOSジェネリック遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延の取得
  ClibResistance
  rise_resistance() const override;

  /// @brief 立ち下がり遷移遅延の取得
  ClibResistance
  fall_resistance() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がり遷移遅延
  ClibResistance mRiseResistance;

  // 立ち下がり遷移遅延
  ClibResistance mFallResistance;

};


//////////////////////////////////////////////////////////////////////
/// @class CiTimingPiecewise CiTiming.h "CiTiming.h"
/// @brief CMOS折れ線近似タイプの ClibTiming の実装クラス
//////////////////////////////////////////////////////////////////////
class CiTimingPiecewise :
  public CiTimingGP
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiTimingPiecewise(
    ClibTimingType timing_type,         ///< [in] タイミングの型
    const Expr& cond,                   ///< [in] タイミング条件を表す式
    ClibTime intrinsic_rise,            ///< [in] 立ち上がり固有遅延
    ClibTime intrinsic_fall,            ///< [in] 立ち下がり固有遅延
    ClibTime slope_rise,                ///< [in] 立ち上がりスロープ遅延
    ClibTime slope_fall,                ///< [in] 立ち下がりスロープ遅延
    ClibResistance rise_pin_resistance, ///< [in] 立ち上がりピン抵抗
    ClibResistance fall_pin_resistance  ///< [in] 立ち下がりピン抵抗
  ) : CiTimingGP(timing_type, cond,
		 intrinsic_rise, intrinsic_fall,
		 slope_rise, slope_fall),
      mRisePinResistance{rise_pin_resistance},
      mFallPinResistance{fall_pin_resistance}
  {
  }

  /// @brief デストラクタ
  ~CiTimingPiecewise() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS折れ線近似遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延の取得
  ClibResistance
  rise_pin_resistance() const override;

  /// @brief 立ち下がり遷移遅延の取得
  ClibResistance
  fall_pin_resistance() const override;

  /// @brief 立ち上がり？？？
  ClibTime
  rise_delay_intercept() const override;

  /// @brief 立ち下がり？？？
  ClibTime
  fall_delay_intercept() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がり遷移遅延
  ClibResistance mRisePinResistance;

  // 立ち下がり遷移遅延
  ClibResistance mFallPinResistance;

};


//////////////////////////////////////////////////////////////////////
/// @class CiTimingLut1 CiTiming.h "CiTiming.h"
/// @brief CMOS非線形タイプの ClibTiming の実装クラス
//////////////////////////////////////////////////////////////////////
class CiTimingLut1 :
  public CiTiming
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiTimingLut1(
    ClibTimingType timing_type, ///< [in] タイミングの型
    const Expr& cond,           ///< [in] タイミング条件を表す式
    CiLut* cell_rise,         ///< [in] 立ち上がりセル遅延テーブル
    CiLut* cell_fall,         ///< [in] 立ち下がりセル遅延テーブル
    CiLut* rise_transition,   ///< [in] 立ち上がり遷移遅延テーブル
    CiLut* fall_transition    ///< [in] 立ち下がり遷移遅延テーブル
  );

  /// @brief デストラクタ
  ~CiTimingLut1();


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がりセル遅延テーブルの取得
  const ClibLut&
  cell_rise() const override;

  /// @brief 立ち下がりセル遅延テーブルの取得
  const ClibLut&
  cell_fall() const override;

  /// @brief 立ち上がり遷移遅延テーブルの取得
  const ClibLut&
  rise_transition() const override;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  const ClibLut&
  fall_transition() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がりセル遅延テーブル
  unique_ptr<CiLut> mClibRise;

  // 立ち下がりセル遅延テーブル
  unique_ptr<CiLut> mClibFall;

  // 立ち上がり遷移遅延テーブル
  unique_ptr<CiLut> mRiseTransition;

  // 立ち下がり遷移遅延テーブル
  unique_ptr<CiLut> mFallTransition;

};


//////////////////////////////////////////////////////////////////////
/// @class CiTimingLut2 CiTiming.h "CiTiming.h"
/// @brief CMOS非線形タイプの ClibTiming の実装クラス
//////////////////////////////////////////////////////////////////////
class CiTimingLut2 :
  public CiTiming
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  CiTimingLut2(
    ClibTimingType timing_type, ///< [in] タイミングの型
    const Expr& cond,           ///< [in] タイミング条件を表す式
    CiLut* rise_transition,   ///< [in] 立ち上がり遷移遅延テーブル
    CiLut* fall_transition,   ///< [in] 立ち下がり遷移遅延テーブル
    CiLut* rise_propagation,  ///< [in] 立ち上がり伝搬遅延テーブル
    CiLut* fall_propagation   ///< [in] 立ち下がり伝搬遅延テーブル
  );

  /// @brief デストラクタ
  ~CiTimingLut2();


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延テーブルの取得
  const ClibLut&
  rise_transition() const override;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  const ClibLut&
  fall_transition() const override;

  /// @brief 立ち上がり伝搬遅延テーブルの取得
  const ClibLut&
  rise_propagation() const override;

  /// @brief 立ち下がり伝搬遅延テーブルの取得
  const ClibLut&
  fall_propagation() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    ostream& s ///< [in] 出力先のストリーム
  ) const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がり遷移遅延テーブル
  unique_ptr<CiLut> mRiseTransition;

  // 立ち下がり遷移遅延テーブル
  unique_ptr<CiLut> mFallTransition;

  // 立ち上がり伝搬遅延テーブル
  unique_ptr<CiLut> mRisePropagation;

  // 立ち下がり伝搬遅延テーブル
  unique_ptr<CiLut> mFallPropagation;

};

END_NAMESPACE_YM_CLIB

#endif // CITIMING_H
