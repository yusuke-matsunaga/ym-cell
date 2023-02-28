#ifndef CITIMING_H
#define CITIMING_H

/// @file　CiTiming.h
/// @brief ClibTiming の実装クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ClibTime.h"
#include "ym/ClibResistance.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CLIB

class CiLut;

//////////////////////////////////////////////////////////////////////
/// @class CiTiming CiTiming.h "CiTiming.h"
/// @brief 共通の基底クラス
//////////////////////////////////////////////////////////////////////
class CiTiming
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiTiming() = default;

  /// @brief コンストラクタ
  CiTiming(
    ClibTimingType type, ///< [in] タイミング条件の型
    const Expr& cond     ///< [in] タイミング条件を表す式
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
  SizeType
  rise_transition() const;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  virtual
  SizeType
  fall_transition() const;

  /// @brief 立ち上がり伝搬遅延テーブルの取得
  virtual
  SizeType
  rise_propagation() const;

  /// @brief 立ち下がり伝搬遅延テーブルの取得
  virtual
  SizeType
  fall_propagation() const;

  /// @brief 立ち上がりセル遅延テーブルの取得
  virtual
  SizeType
  cell_rise() const;

  /// @brief 立ち下がりセル遅延テーブルの取得
  virtual
  SizeType
  cell_fall() const;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  virtual
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const = 0;

  /// @brief 内容を読み込む．
  virtual
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  );


protected:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 用の下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通な情報をダンプする．
  void
  dump_common(
    BinEnc& s,      ///< [in] 出力先のストリーム
    ymuint8 type_id ///< [in] 型の ID
  ) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

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

  /// @brief 空のコンストラクタ(restore用)
  CiTimingGP() = default;

  /// @brief コンストラクタ
  CiTimingGP(
    ClibTimingType timing_type, ///< [in] タイミングの型
    const Expr& cond,           ///< [in] タイミング条件を表す式
    ClibTime intrinsic_rise,    ///< [in] 立ち上がり固有遅延
    ClibTime intrinsic_fall,    ///< [in] 立ち下がり固有遅延
    ClibTime slope_rise,        ///< [in] 立ち上がりスロープ遅延
    ClibTime slope_fall         ///< [in] 立ち下がりスロープ遅延
  ) : CiTiming{timing_type, cond},
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


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


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
public:

  /// @brief 空のコンストラクタ(restore用)
  CiTimingGeneric() = default;

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
  ) : CiTimingGP{timing_type, cond,
		 intrinsic_rise, intrinsic_fall,
		 slope_rise, slope_fall},
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
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


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
public:

  /// @brief 空のコンストラクタ(restore用)
  CiTimingPiecewise() = default;

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
  ) : CiTimingGP{timing_type, cond,
		 intrinsic_rise, intrinsic_fall,
		 slope_rise, slope_fall},
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
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


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
/// @brief CMOS非線形タイプの ClibTiming の共通の基底クラス
//////////////////////////////////////////////////////////////////////
class CiTimingLut :
  public CiTiming
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiTimingLut() = default;

  /// @brief コンストラクタ
  CiTimingLut(
    ClibTimingType timing_type, ///< [in] タイミングの型
    const Expr& cond,           ///< [in] タイミング条件を表す式
    SizeType rise_transition,   ///< [in] 立ち上がり遷移遅延テーブル
    SizeType fall_transition    ///< [in] 立ち下がり遷移遅延テーブル
  ) : CiTiming{timing_type, cond},
      mRiseTransition{rise_transition},
      mFallTransition{fall_transition}
  {
  }


  /// @brief デストラクタ
  ~CiTimingLut() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延テーブルの取得
  SizeType
  rise_transition() const override;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  SizeType
  fall_transition() const override;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がり遷移遅延テーブル
  SizeType mRiseTransition;

  // 立ち下がり遷移遅延テーブル
  SizeType mFallTransition;

};


//////////////////////////////////////////////////////////////////////
/// @class CiTimingLut1 CiTiming.h "CiTiming.h"
/// @brief CMOS非線形タイプ1の ClibTiming の実装クラス
//////////////////////////////////////////////////////////////////////
class CiTimingLut1 :
  public CiTimingLut
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiTimingLut1() = default;

  /// @brief コンストラクタ
  CiTimingLut1(
    ClibTimingType timing_type, ///< [in] タイミングの型
    const Expr& cond,           ///< [in] タイミング条件を表す式
    SizeType cell_rise,         ///< [in] 立ち上がりセル遅延テーブル
    SizeType cell_fall,         ///< [in] 立ち下がりセル遅延テーブル
    SizeType rise_transition,   ///< [in] 立ち上がり遷移遅延テーブル
    SizeType fall_transition    ///< [in] 立ち下がり遷移遅延テーブル
  ) : CiTimingLut{timing_type, cond, rise_transition, fall_transition},
      mCellRise{cell_rise},
      mCellFall{cell_fall}
  {
  }


  /// @brief デストラクタ
  ~CiTimingLut1() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がりセル遅延テーブルの取得
  SizeType
  cell_rise() const override;

  /// @brief 立ち下がりセル遅延テーブルの取得
  SizeType
  cell_fall() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がりセル遅延テーブル
  SizeType mCellRise;

  // 立ち下がりセル遅延テーブル
  SizeType mCellFall;

};


//////////////////////////////////////////////////////////////////////
/// @class CiTimingLut2 CiTiming.h "CiTiming.h"
/// @brief CMOS非線形タイプ2の ClibTiming の実装クラス
//////////////////////////////////////////////////////////////////////
class CiTimingLut2 :
  public CiTimingLut
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiTimingLut2() = default;

  /// @brief コンストラクタ
  CiTimingLut2(
    ClibTimingType timing_type, ///< [in] タイミングの型
    const Expr& cond,           ///< [in] タイミング条件を表す式
    SizeType rise_transition,   ///< [in] 立ち上がり遷移遅延テーブル
    SizeType fall_transition,   ///< [in] 立ち下がり遷移遅延テーブル
    SizeType rise_propagation,  ///< [in] 立ち上がり伝搬遅延テーブル
    SizeType fall_propagation   ///< [in] 立ち下がり伝搬遅延テーブル
  ) : CiTimingLut{timing_type, cond, rise_transition, fall_transition},
    mRisePropagation{rise_propagation},
    mFallPropagation{fall_propagation}
  {
  }

  /// @brief デストラクタ
  ~CiTimingLut2() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり伝搬遅延テーブルの取得
  SizeType
  rise_propagation() const override;

  /// @brief 立ち下がり伝搬遅延テーブルの取得
  SizeType
  fall_propagation() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump(
    BinEnc& s ///< [in] 出力先のストリーム
  ) const override;

  /// @brief 内容を読み込む．
  void
  restore(
    BinDec& s ///< [in] 入力元のストリーム
  ) override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がり伝搬遅延テーブル
  SizeType mRisePropagation;

  // 立ち下がり伝搬遅延テーブル
  SizeType mFallPropagation;

};

END_NAMESPACE_YM_CLIB

#endif // CITIMING_H
