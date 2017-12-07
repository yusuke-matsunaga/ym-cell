#ifndef CITIMING_H
#define CITIMING_H

/// @file　CiTiming.h
/// @brief ClibTiming の実装クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibTiming.h"
#include "ym/ClibTime.h"
#include "ym/ClibResistance.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class CiTiming CiTiming.h "CiTiming.h"
/// @brief 共通の基底クラス
//////////////////////////////////////////////////////////////////////
class CiTiming :
  public ClibTiming
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  /// @param[in] id ID番号
  /// @param[in] type タイミング条件の型
  /// @param[in] cond タイミング条件を表す式
  CiTiming(ymuint id,
	   ClibTimingType type,
	   const Expr& cond);

  /// @brief デストラクタ
  ~CiTiming();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通の属性
  //////////////////////////////////////////////////////////////////////

  /// @brief ID番号の取得
  /// @note timing = cell->timing(id); の時，timing->id() = id となる．
  virtual
  ymuint
  id() const;

  /// @brief 型の取得
  virtual
  ClibTimingType
  type() const;

  /// @brief タイミング条件式の取得
  /// @note ない場合には定数1の式が返される．
  virtual
  Expr
  timing_cond() const;


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
  const ClibLut*
  rise_transition() const;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  virtual
  const ClibLut*
  fall_transition() const;

  /// @brief 立ち上がり伝搬遅延テーブルの取得
  virtual
  const ClibLut*
  rise_propagation() const;

  /// @brief 立ち下がり伝搬遅延テーブルの取得
  virtual
  const ClibLut*
  fall_propagation() const;

  /// @brief 立ち上がりセル遅延テーブルの取得
  virtual
  const ClibLut*
  cell_rise() const;

  /// @brief 立ち下がりセル遅延テーブルの取得
  virtual
  const ClibLut*
  cell_fall() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // dump 用の下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 共通な情報をダンプする．
  /// @param[in] s 出力先のストリーム
  /// @param[in] type_id 型の ID
  void
  dump_common(ODO& s,
	      ymuint8 type_id) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ID
  ymuint32 mId;

  // 型
  ClibTimingType mType;

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
  /// @param[in] id ID番号
  /// @param[in] timing_type タイミングの型
  /// @param[in] cond タイミング条件を表す式
  /// @param[in] intrinsic_rise 立ち上がり固有遅延
  /// @param[in] intrinsic_fall 立ち下がり固有遅延
  /// @param[in] slope_rise 立ち上がりスロープ遅延
  /// @param[in] slope_fall 立ち下がりスロープ遅延
  CiTimingGP(ymuint id,
	     ClibTimingType timing_type,
	     const Expr& cond,
	     ClibTime intrinsic_rise,
	     ClibTime intrinsic_fall,
	     ClibTime slope_rise,
	     ClibTime slope_fall);

  /// @brief デストラクタ
  virtual
  ~CiTimingGP();


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
  /// @param[in] id ID番号
  /// @param[in] timing_type タイミングの型
  /// @param[in] cond タイミング条件を表す式
  /// @param[in] intrinsic_rise 立ち上がり固有遅延
  /// @param[in] intrinsic_fall 立ち下がり固有遅延
  /// @param[in] slope_rise 立ち上がりスロープ遅延
  /// @param[in] slope_fall 立ち下がりスロープ遅延
  /// @param[in] rise_resistance 立ち上がり遷移遅延パラメータ
  /// @param[in] fall_resistance 立ち下がり遷移遅延パラメータ
  CiTimingGeneric(ymuint id,
		  ClibTimingType timing_type,
		  const Expr& cond,
		  ClibTime intrinsic_rise,
		  ClibTime intrinsic_fall,
		  ClibTime slope_rise,
		  ClibTime slope_fall,
		  ClibResistance rise_resistance,
		  ClibResistance fall_resistance);

  /// @brief デストラクタ
  virtual
  ~CiTimingGeneric();


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
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  virtual
  void
  dump(ODO& s) const;


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
  /// @param[in] id ID番号
  /// @param[in] timing_type タイミングの型
  /// @param[in] cond タイミング条件を表す式
  /// @param[in] intrinsic_rise 立ち上がり固有遅延
  /// @param[in] intrinsic_fall 立ち下がり固有遅延
  /// @param[in] slope_rise 立ち上がりスロープ遅延
  /// @param[in] slope_fall 立ち下がりスロープ遅延
  CiTimingPiecewise(ymuint id,
		    ClibTimingType timing_type,
		    const Expr& cond,
		    ClibTime intrinsic_rise,
		    ClibTime intrinsic_fall,
		    ClibTime slope_rise,
		    ClibTime slope_fall,
		    ClibResistance rise_pin_resistance,
		    ClibResistance fall_pin_resistance);

  /// @brief デストラクタ
  virtual
  ~CiTimingPiecewise();


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
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  virtual
  void
  dump(ODO& s) const;


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
  /// @param[in] id ID番号
  /// @param[in] timing_type タイミングの型
  /// @param[in] cond タイミング条件を表す式
  /// @param[in] cell_rise 立ち上がりセル遅延テーブル
  /// @param[in] cell_fall 立ち下がりセル遅延テーブル
  CiTimingLut1(ymuint id,
	       ClibTimingType timing_type,
	       const Expr& cond,
	       ClibLut* cell_rise,
	       ClibLut* cell_fall,
	       ClibLut* rise_transition,
	       ClibLut* fall_transition);


  /// @brief デストラクタ
  virtual
  ~CiTimingLut1();


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がりセル遅延テーブルの取得
  virtual
  const ClibLut*
  cell_rise() const;

  /// @brief 立ち下がりセル遅延テーブルの取得
  virtual
  const ClibLut*
  cell_fall() const;

  /// @brief 立ち上がり遷移遅延テーブルの取得
  virtual
  const ClibLut*
  rise_transition() const;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  virtual
  const ClibLut*
  fall_transition() const;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  virtual
  void
  dump(ODO& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がりセル遅延テーブル
  const ClibLut* mClibRise;

  // 立ち下がりセル遅延テーブル
  const ClibLut* mClibFall;

  // 立ち上がり遷移遅延テーブル
  const ClibLut* mRiseTransition;

  // 立ち下がり遷移遅延テーブル
  const ClibLut* mFallTransition;

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
  /// @param[in] id ID番号
  /// @param[in] timing_type タイミングの型
  /// @param[in] cond タイミング条件を表す式
  /// @param[in] rise_transition 立ち上がり遷移遅延テーブル
  /// @param[in] fall_transition 立ち下がり遷移遅延テーブル
  /// @param[in] rise_propagation 立ち上がり伝搬遅延テーブル
  /// @param[in] fall_propagation 立ち下がり伝搬遅延テーブル
  CiTimingLut2(ymuint id,
	       ClibTimingType timing_type,
	       const Expr& cond,
	       ClibLut* rise_transition,
	       ClibLut* fall_transition,
	       ClibLut* rise_propagation,
	       ClibLut* fall_propagation);


  /// @brief デストラクタ
  virtual
  ~CiTimingLut2();


public:
  //////////////////////////////////////////////////////////////////////
  // CMOS非線形遅延モデルの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 立ち上がり遷移遅延テーブルの取得
  virtual
  const ClibLut*
  rise_transition() const;

  /// @brief 立ち下がり遷移遅延テーブルの取得
  virtual
  const ClibLut*
  fall_transition() const;

  /// @brief 立ち上がり伝搬遅延テーブルの取得
  virtual
  const ClibLut*
  rise_propagation() const;

  /// @brief 立ち下がり伝搬遅延テーブルの取得
  virtual
  const ClibLut*
  fall_propagation() const;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  virtual
  void
  dump(ODO& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 立ち上がり遷移遅延テーブル
  const ClibLut* mRiseTransition;

  // 立ち下がり遷移遅延テーブル
  const ClibLut* mFallTransition;

  // 立ち上がり伝搬遅延テーブル
  const ClibLut* mRisePropagation;

  // 立ち下がり伝搬遅延テーブル
  const ClibLut* mFallPropagation;

};

END_NAMESPACE_YM_CLIB

#endif // CITIMING_H
