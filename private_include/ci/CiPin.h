﻿#ifndef CIPIN_H
#define CIPIN_H

/// @file CiPin.h
/// @brief CiPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/clib.h"
#include "ym/ClibTime.h"
#include "ym/ClibCapacitance.h"
#include "ym/Expr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
/// @class ClibCellPinBase CiPin.h "CiPin.h"
/// @brief ピンの基底クラス
//////////////////////////////////////////////////////////////////////
class CiPin
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiPin() = default;

  /// @brief コンストラクタ
  CiPin(
    const ShString& name ///< [in] ピン名
  ) : mName{name}
  {
  }

  /// @brief デストラクタ
  virtual
  ~CiPin() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン名を返す．
  string
  name() const
  {
    return mName;
  }

  /// @brief ピン名を返す．
  ShString
  _name() const
  {
    return mName;
  }

  /// @brief 方向を返す．
  virtual
  ClibDirection
  direction() const = 0;

  /// @brief 入力ピンの時に true を返す．
  virtual
  bool
  is_input() const;

  /// @brief 出力ピンの時に true を返す．
  virtual
  bool
  is_output() const;

  /// @brief 入出力ピンの時に true を返す．
  virtual
  bool
  is_inout() const;

  /// @brief 内部ピンの時に true を返す．
  virtual
  bool
  is_internal() const;

  /// @brief ピン番号を返す．
  SizeType
  pin_id() const
  {
    return mPinId;
  }


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  ///
  /// 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  virtual
  SizeType
  input_id() const;

  /// @brief 負荷容量を返す．
  virtual
  ClibCapacitance
  capacitance() const;

  /// @brief 立ち上がり時の負荷容量を返す．
  virtual
  ClibCapacitance
  rise_capacitance() const;

  /// @brief 立ち下がり時の負荷容量を返す．
  virtual
  ClibCapacitance
  fall_capacitance() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 出力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力ピン番号を返す．
  ///
  /// 出力ピンもしくは入出力ピンの時のみ意味を持つ．
  virtual
  SizeType
  output_id() const;

  /// @brief 最大ファンアウト容量を返す．
  virtual
  ClibCapacitance
  max_fanout() const;

  /// @brief 最小ファンアウト容量を返す．
  virtual
  ClibCapacitance
  min_fanout() const;

  /// @brief 最大負荷容量を返す．
  virtual
  ClibCapacitance
  max_capacitance() const;

  /// @brief 最小負荷容量を返す．
  virtual
  ClibCapacitance
  min_capacitance() const;

  /// @brief 最大遷移時間を返す．
  virtual
  ClibTime
  max_transition() const;

  /// @brief 最小遷移時間を返す．
  virtual
  ClibTime
  min_transition() const;

  /// @brief 論理式を返す．
  virtual
  Expr
  function() const;

  /// @brief tristate 条件式を返す．
  virtual
  Expr
  tristate() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内部ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 内部ピン番号を返す．
  ///
  /// 内部ピンの時のみ意味を持つ．
  virtual
  SizeType
  internal_id() const;


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
  ) = 0;


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief dump 用の共通情報を出力する．
  void
  dump_common(
    BinEnc& s, ///< [in] ストリーム
    int sig    ///< [in] シグネチャ(0, 1, 2, 3)
  ) const;

  /// @brief 内容を読み込む．
  void
  restore_common(
    BinDec& s ///< [in] 入力元のストリーム
  );


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン番号を設定する．
  void
  set_pin_id(
    SizeType pid ///< [in] ピン番号
  )
  {
    mPinId = pid;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  ShString mName;

  // ピン番号
  SizeType mPinId{CLIB_NULLID};

};


//////////////////////////////////////////////////////////////////////
/// @class CiInputPin CiPin.h "CiPin.h"
/// @brief セルの入力ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class CiInputPin :
  public CiPin
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiInputPin() = default;

  /// @brief コンストラクタ
  CiInputPin(
    const ShString& name,             ///< [in] ピン名
    ClibCapacitance capacitance,      ///< [in] 負荷容量
    ClibCapacitance rise_capacitance, ///< [in] 立ち上がり時の負荷容量
    ClibCapacitance fall_capacitance  ///< [in] 立ち下がり時の負荷容量
  ) : CiPin{name},
      mCapacitance{capacitance},
      mRiseCapacitance{rise_capacitance},
      mFallCapacitance{fall_capacitance}
  {
  }

  /// @brief デストラクタ
  ~CiInputPin() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  ClibDirection
  direction() const override;

  /// @brief 入力ピンの時に true を返す．
  bool
  is_input() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  ///
  /// 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  SizeType
  input_id() const override;

  /// @brief 負荷容量を返す．
  ClibCapacitance
  capacitance() const override;

  /// @brief 立ち上がり時の負荷容量を返す．
  ClibCapacitance
  rise_capacitance() const override;

  /// @brief 立ち下がり時の負荷容量を返す．
  ClibCapacitance
  fall_capacitance() const override;


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


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を設定する．
  void
  set_input_id(
    SizeType iid ///< [in] 入力ピン番号
  )
  {
    mInputId = iid;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ピン番号
  SizeType mInputId;

  // 負荷
  ClibCapacitance mCapacitance;

  // rise 負荷
  ClibCapacitance mRiseCapacitance;

  // fall 負荷
  ClibCapacitance mFallCapacitance;

};


//////////////////////////////////////////////////////////////////////
/// @class CiOutputPin CiPin.h "CiPin.h"
/// @brief セルの出力ピンと入出力ピンの基底クラス
//////////////////////////////////////////////////////////////////////
class CiOutputPinBase :
  public CiPin
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiOutputPinBase() = default;

  /// @brief コンストラクタ
  CiOutputPinBase(
    const ShString& name,            ///< [in] ピン名
    ClibCapacitance max_fanout,      ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,      ///< [in] 最小ファンアウト容量
    ClibCapacitance max_capacitance, ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance, ///< [in] 最小負荷容量
    ClibTime max_transition,         ///< [in] 最大遷移時間
    ClibTime min_transition,         ///< [in] 最小遷移時間
    const Expr& function,            ///< [in] 出力の論理式
    const Expr& tristate             ///< [in] tristate 条件
  ) : CiPin{name},
      mMaxFanout{max_fanout},
      mMinFanout{min_fanout},
      mMaxCapacitance{max_capacitance},
      mMinCapacitance{min_capacitance},
      mMaxTransition{max_transition},
      mMinTransition{min_transition},
      mFunction{function},
      mTristate{tristate}
  {
  }

  /// @brief デストラクタ
  ~CiOutputPinBase() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 出力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力ピン番号を返す．
  ///
  /// 出力ピンもしくは入出力ピンの時のみ意味を持つ．
  SizeType
  output_id() const override;

  /// @brief 最大ファンアウト容量を返す．
  ClibCapacitance
  max_fanout() const override;

  /// @brief 最小ファンアウト容量を返す．
  ClibCapacitance
  min_fanout() const override;

  /// @brief 最大負荷容量を返す．
  ClibCapacitance
  max_capacitance() const override;

  /// @brief 最小負荷容量を返す．
  ClibCapacitance
  min_capacitance() const override;

  /// @brief 最大遷移時間を返す．
  ClibTime
  max_transition() const override;

  /// @brief 最小遷移時間を返す．
  ClibTime
  min_transition() const override;

  /// @brief 論理式を返す．
  Expr
  function() const override;

  /// @brief tristate 条件式を返す．
  Expr
  tristate() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力ピン番号を設定する．
  void
  set_output_id(
    SizeType oid ///< [in] 出力ピン番号
  )
  {
    mOutputId = oid;
  }


protected:
  //////////////////////////////////////////////////////////////////////
  // 継承クラスから用いられる関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  void
  dump_base(
    BinEnc& s, ///< [in] 出力先のストリーム
    int sig    ///< [in] シグネチャ
  ) const;

  /// @brief 内容を読み込む．
  void
  restore_base(
    BinDec& s ///< [in] 入力元のストリーム
  )
  {
    restore_common(s);
    mOutputId = s.read_64();
    s >> mFanoutLoad
      >> mMaxFanout
      >> mMinFanout
      >> mMaxCapacitance
      >> mMinCapacitance
      >> mMaxTransition
      >> mMinTransition;
    mFunction.restore(s);
    mTristate.restore(s);
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 出力ピン番号
  SizeType mOutputId;

  // ファンアウトの負荷
  ClibCapacitance mFanoutLoad;

  // 最大ファンアウト容量
  ClibCapacitance mMaxFanout;

  // 最小ファンアウト容量
  ClibCapacitance mMinFanout;

  // 最大負荷容量
  ClibCapacitance mMaxCapacitance;

  // 最小負荷容量
  ClibCapacitance mMinCapacitance;

  // 最大遷移時間
  ClibTime mMaxTransition;

  // 最小遷移時間
  ClibTime mMinTransition;

  // 論理式
  Expr mFunction;

  // tristate 条件
  Expr mTristate;

};


//////////////////////////////////////////////////////////////////////
/// @class CiOutputPin CiPin.h "CiPin.h"
/// @brief セルの出力ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class CiOutputPin :
  public CiOutputPinBase
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiOutputPin() = default;

  /// @brief コンストラクタ
  CiOutputPin(
    const ShString& name,            ///< [in] ピン名
    ClibCapacitance max_fanout,      ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,      ///< [in] 最大ファンアウト容量
    ClibCapacitance max_capacitance, ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance, ///< [in] 最大負荷容量
    ClibTime max_transition,         ///< [in] 最大遷移時間
    ClibTime min_transition,         ///< [in] 最大遷移時間
    const Expr& function,            ///< [in] 出力の論理式
    const Expr& tristate             ///< [in] tristate 条件
  ) : CiOutputPinBase{name,
		      max_fanout, min_fanout,
		      max_capacitance, min_capacitance,
		      max_transition, min_transition,
		      function, tristate}
  {
  }

  /// @brief デストラクタ
  ~CiOutputPin() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  ClibDirection
  direction() const override;

  /// @brief 出力ピンの時に true を返す．
  bool
  is_output() const override;


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

};


//////////////////////////////////////////////////////////////////////
/// @class CiInoutPin CiPin.h "CiPin.h"
/// @brief セルの入出力ピンを表すクラス
///
/// 多重継承はオーバーヘッドがかかるので愚直な実装を用いている．
//////////////////////////////////////////////////////////////////////
class CiInoutPin :
  public CiOutputPinBase
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiInoutPin() = default;

  /// @brief コンストラクタ
  CiInoutPin(
    const ShString& name,             ///< [in] ピン名
    ClibCapacitance capacitance,      ///< [in] 負荷容量
    ClibCapacitance rise_capacitance, ///< [in] 立ち上がり時の負荷容量
    ClibCapacitance fall_capacitance, ///< [in] 立ち上がり時の負荷容量
    ClibCapacitance max_fanout,	      ///< [in] 最大ファンアウト容量
    ClibCapacitance min_fanout,	      ///< [in] 最大ファンアウト容量
    ClibCapacitance max_capacitance,  ///< [in] 最大負荷容量
    ClibCapacitance min_capacitance,  ///< [in] 最大負荷容量
    ClibTime max_transition,	      ///< [in] 最大遷移時間
    ClibTime min_transition,          ///< [in] 最大遷移時間
    const Expr& function,             ///< [in] 出力の論理式
    const Expr& tristate              ///< [in] tristate 条件
  ) : CiOutputPinBase{name,
		      max_fanout, min_fanout,
		      max_capacitance, min_capacitance,
		      max_transition, min_transition,
		      function, tristate},
      mCapacitance{capacitance},
      mRiseCapacitance{rise_capacitance},
      mFallCapacitance{fall_capacitance}
  {
  }

  /// @brief デストラクタ
  ~CiInoutPin() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  ClibDirection
  direction() const override;

  /// @brief 入出力ピンの時に true を返す．
  bool
  is_inout() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  ///
  /// 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  SizeType
  input_id() const override;

  /// @brief 負荷容量を返す．
  ClibCapacitance
  capacitance() const override;

  /// @brief 立ち上がり時の負荷容量を返す．
  ClibCapacitance
  rise_capacitance() const override;

  /// @brief 立ち下がり時の負荷容量を返す．
  ClibCapacitance
  fall_capacitance() const override;


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


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を設定する．
  void
  set_input_id(
    SizeType iid ///< [in] 入力ピン番号
  )
  {
    mInputId = iid;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 入力ピン番号
  SizeType mInputId;

  // 負荷
  ClibCapacitance mCapacitance;

  // rise 負荷
  ClibCapacitance mRiseCapacitance;

  // fall 負荷
  ClibCapacitance mFallCapacitance;

};


//////////////////////////////////////////////////////////////////////
/// @class CiInternalPin CiPin.h "CiPin.h"
/// @brief セルの内部ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class CiInternalPin :
  public CiPin
{
public:

  /// @brief 空のコンストラクタ(restore用)
  CiInternalPin() = default;

  /// @brief コンストラクタ
  CiInternalPin(
    const ShString& name ///< [in] ピン名
  ) : CiPin{name}
  {
  }

  /// @brief デストラクタ
  ~CiInternalPin() = default;


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  ClibDirection
  direction() const override;

  /// @brief 内部ピンの時に true を返す．
  bool
  is_internal() const override;


public:
  //////////////////////////////////////////////////////////////////////
  // 内部ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 内部ピン番号を返す．
  ///
  /// 内部ピンの時のみ意味を持つ．
  SizeType
  internal_id() const override;


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


public:
  //////////////////////////////////////////////////////////////////////
  // 設定用の関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内部ピン番号を設定する．
  void
  set_internal_id(
    SizeType iid ///< [in] 内部ピン番号
  )
  {
    mInternalId = iid;
  }


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 内部ピン番号
  SizeType mInternalId;

};

END_NAMESPACE_YM_CLIB

#endif // CIPIN_H
