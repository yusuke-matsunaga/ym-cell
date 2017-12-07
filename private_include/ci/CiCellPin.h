#ifndef CIPIN_H
#define CIPIN_H

/// @file CiCellPin.h
/// @brief CiCellPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "ym/ClibCellPin.h"
#include "ym/ClibTime.h"
#include "ym/ClibCapacitance.h"
#include "ym/Expr.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_CLIB

class CiCell;

//////////////////////////////////////////////////////////////////////
/// @class ClibCellPinBase CiCellPin.h "CiCellPin.h"
/// @brief ピンの基底クラス
//////////////////////////////////////////////////////////////////////
class CiCellPin :
  public ClibCellPin
{
  friend class CiCellLibrary;
  friend class CiCellPinHash;

protected:

  /// @brief コンストラクタ
  /// @param[in] cell 親のセル
  /// @param[in] name ピン名
  CiCellPin(CiCell* cell,
	    const ShString& name);

  /// @brief デストラクタ
  virtual
  ~CiCellPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief ピン番号を返す．
  virtual
  ymuint
  pin_id() const;

  /// @brief ピン名を返す．
  virtual
  string
  name() const;

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


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  /// @note 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  virtual
  ymuint
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
  /// @note 出力ピンもしくは入出力ピンの時のみ意味を持つ．
  virtual
  ymuint
  output_id() const;

  /// @brief 論理式を持っているときに true を返す．
  virtual
  bool
  has_function() const;

  /// @brief 機能を表す論理式を返す．
  virtual
  Expr
  function() const;

  /// @brief three_state 属性を持っているときに true を返す．
  virtual
  bool
  has_three_state() const;

  /// @brief three_state 論理式を返す．
  virtual
  Expr
  three_state() const;

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


public:
  //////////////////////////////////////////////////////////////////////
  // 内部ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 内部ピン番号を返す．
  /// @note 内部ピンの時のみ意味を持つ．
  virtual
  ymuint
  internal_id() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // 下請け関数
  //////////////////////////////////////////////////////////////////////

  /// @brief dump 用の共通情報を出力する．
  void
  dump_common(ODO& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ハッシュ表のためのリンク
  CiCellPin* mLink;

  // 親のセル
  CiCell* mClib;

  // ピン番号
  ymuint mId;

  // 名前
  ShString mName;

};


//////////////////////////////////////////////////////////////////////
/// @class CiInputPin CiCellPin.h "CiCellPin.h"
/// @brief セルの入力ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class CiInputPin :
  public CiCellPin
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  /// @param[in] cell 親のセル
  /// @param[in] name ピン名
  /// @param[in] capacitance 負荷容量
  /// @param[in] rise_capacitance 立ち上がり時の負荷容量
  /// @param[in] fall_capacitance 立ち下がり時の負荷容量
  CiInputPin(CiCell* cell,
	     const ShString& name,
	     ClibCapacitance capacitance,
	     ClibCapacitance rise_capacitance,
	     ClibCapacitance fall_capacitance);

  /// @brief デストラクタ
  virtual
  ~CiInputPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  virtual
  ClibCellPinDirection
  direction() const;

  /// @brief 入力ピンの時に true を返す．
  virtual
  bool
  is_input() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  /// @note 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  virtual
  ymuint
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

  // 入力ピン番号
  ymuint mInputId;

  // 負荷
  ClibCapacitance mCapacitance;

  // rise 負荷
  ClibCapacitance mRiseCapacitance;

  // fall 負荷
  ClibCapacitance mFallCapacitance;

};


//////////////////////////////////////////////////////////////////////
/// @class CiOutputPin CiCellPin.h "CiCellPin.h"
/// @brief セルの出力ピンと入出力ピンの基底クラス
//////////////////////////////////////////////////////////////////////
class CiOutputPinBase :
  public CiCellPin
{
  friend class CiCellLibrary;

protected:

  /// @brief コンストラクタ
  /// @param[in] cell 親のセル
  /// @param[in] name ピン名
  /// @param[in] has_logic 論理式を持つとき true にするフラグ
  /// @param[in] logic_expr 論理式
  /// @param[in] tristate_expr tristate 条件式
  /// @param[in] max_fanout 最大ファンアウト容量
  /// @param[in] min_fanout 最小ファンアウト容量
  /// @param[in] max_capacitance 最大負荷容量
  /// @param[in] min_capacitance 最小負荷容量
  /// @param[in] max_transition 最大遷移時間
  /// @param[in] min_transition 最小遷移時間
  CiOutputPinBase(CiCell* cell,
		  const ShString& name,
		  bool has_logic,
		  const Expr& logic_expr,
		  const Expr& tristate_expr,
		  ClibCapacitance max_fanout,
		  ClibCapacitance min_fanout,
		  ClibCapacitance max_capacitance,
		  ClibCapacitance min_capacitance,
		  ClibTime max_transition,
		  ClibTime min_transition);

  /// @brief デストラクタ
  virtual
  ~CiOutputPinBase();


public:
  //////////////////////////////////////////////////////////////////////
  // 出力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 出力ピン番号を返す．
  /// @note 出力ピンもしくは入出力ピンの時のみ意味を持つ．
  virtual
  ymuint
  output_id() const;

  /// @brief 論理式を持っているときに true を返す．
  virtual
  bool
  has_function() const;

  /// @brief 機能を表す論理式を返す．
  virtual
  Expr
  function() const;

  /// @brief three_state 属性を持っているときに true を返す．
  virtual
  bool
  has_three_state() const;

  /// @brief three_state 論理式を返す．
  virtual
  Expr
  three_state() const;

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


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 出力ピン番号
  ymuint mOutputId;

  // 論理式を持っているかどうかを表すフラグ
  ymuint mHasFunction;

  // 出力の論理式
  Expr mFunction;

  // three_state 属性の論理式
  Expr mThreeState;

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

};


//////////////////////////////////////////////////////////////////////
/// @class CiOutputPin CiCellPin.h "CiCellPin.h"
/// @brief セルの出力ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class CiOutputPin :
  public CiOutputPinBase
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  /// @param[in] cell 親のセル
  /// @param[in] name ピン名
  /// @param[in] has_logic 論理式を持つとき true にするフラグ
  /// @param[in] logic_expr 論理式
  /// @param[in] tristate_expr tristate 条件式
  /// @param[in] max_fanout 最大ファンアウト容量
  /// @param[in] min_fanout 最小ファンアウト容量
  /// @param[in] max_capacitance 最大負荷容量
  /// @param[in] min_capacitance 最小負荷容量
  /// @param[in] max_transition 最大遷移時間
  /// @param[in] min_transition 最小遷移時間
  CiOutputPin(CiCell* cell,
	      const ShString& name,
	      bool has_logic,
	      const Expr& logic_expr,
	      const Expr& tristate_expr,
	      ClibCapacitance max_fanout,
	      ClibCapacitance min_fanout,
	      ClibCapacitance max_capacitance,
	      ClibCapacitance min_capacitance,
	      ClibTime max_transition,
	      ClibTime min_transition);

  /// @brief デストラクタ
  virtual
  ~CiOutputPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  virtual
  ClibCellPinDirection
  direction() const;

  /// @brief 出力ピンの時に true を返す．
  virtual
  bool
  is_output() const;


public:
  //////////////////////////////////////////////////////////////////////
  // dump/restore 関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をバイナリダンプする．
  /// @param[in] s 出力先のストリーム
  virtual
  void
  dump(ODO& s) const;

};


//////////////////////////////////////////////////////////////////////
/// @class CiInoutPin CiCellPin.h "CiCellPin.h"
/// @brief セルの入出力ピンを表すクラス
/// @note 多重継承はオーバーヘッドがかかるので愚直な実装を用いている．
//////////////////////////////////////////////////////////////////////
class CiInoutPin :
  public CiOutputPinBase
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  /// @param[in] cell 親のセル
  /// @param[in] name ピン名
  /// @param[in] has_logic 論理式を持つとき true にするフラグ
  /// @param[in] logic_expr 論理式
  /// @param[in] tristate_expr tristate 条件式
  /// @param[in] capacitance 負荷容量
  /// @param[in] rise_capacitance 立ち上がり時の負荷容量
  /// @param[in] fall_capacitance 立ち下がり時の負荷容量
  /// @param[in] max_fanout 最大ファンアウト容量
  /// @param[in] min_fanout 最小ファンアウト容量
  /// @param[in] max_capacitance 最大負荷容量
  /// @param[in] min_capacitance 最小負荷容量
  /// @param[in] max_transition 最大遷移時間
  /// @param[in] min_transition 最小遷移時間
  CiInoutPin(CiCell* cell,
	     const ShString& name,
	     bool has_logic,
	     const Expr& logic_expr,
	     const Expr& tristate_expr,
	     ClibCapacitance capacitance,
	     ClibCapacitance rise_capacitance,
	     ClibCapacitance fall_capacitance,
	     ClibCapacitance max_fanout,
	     ClibCapacitance min_fanout,
	     ClibCapacitance max_capacitance,
	     ClibCapacitance min_capacitance,
	     ClibTime max_transition,
	     ClibTime min_transition);

  /// @brief デストラクタ
  virtual
  ~CiInoutPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  virtual
  ClibCellPinDirection
  direction() const;

  /// @brief 入出力ピンの時に true を返す．
  virtual
  bool
  is_inout() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 入力ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 入力ピン番号を返す．
  /// @note 入力ピンもしくは入出力ピンの時のみ意味を持つ．
  virtual
  ymuint
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

  // 入力ピン番号
  ymuint mInputId;

  // 負荷
  ClibCapacitance mCapacitance;

  // rise 負荷
  ClibCapacitance mRiseCapacitance;

  // fall 負荷
  ClibCapacitance mFallCapacitance;

};


//////////////////////////////////////////////////////////////////////
/// @class CiInternalPin CiCellPin.h "CiCellPin.h"
/// @brief セルの内部ピンを表すクラス
//////////////////////////////////////////////////////////////////////
class CiInternalPin :
  public CiCellPin
{
  friend class CiCellLibrary;

private:

  /// @brief コンストラクタ
  /// @param[in] cell 親のセル
  /// @param[in] name ピン名
  CiInternalPin(CiCell* cell,
		const ShString& name);

  /// @brief デストラクタ
  virtual
  ~CiInternalPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 共通属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 方向を返す．
  virtual
  ClibCellPinDirection
  direction() const;

  /// @brief 内部ピンの時に true を返す．
  virtual
  bool
  is_internal() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内部ピンの属性
  //////////////////////////////////////////////////////////////////////

  /// @brief 内部ピン番号を返す．
  /// @note 内部ピンの時のみ意味を持つ．
  virtual
  ymuint
  internal_id() const;


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

  // 内部ピン番号
  ymuint mInternalId;

};

END_NAMESPACE_YM_CLIB

#endif // CIPIN_H
