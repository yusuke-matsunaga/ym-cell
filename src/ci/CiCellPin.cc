
/// @file CiCellPin.cc
/// @brief CiCellPin の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.


#include "CiCellPin.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellPin
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] cell 親のセル
// @param[in] name ピン名
CiCellPin::CiCellPin(CiCell* cell,
		     const ShString& name) :
  mClib(cell),
  mName(name)
{
}

// @brief デストラクタ
CiCellPin::~CiCellPin()
{
}

// @brief ピン番号を返す．
ymuint
CiCellPin::pin_id() const
{
  return mId;
}

// @brief ピン名を返す．
string
CiCellPin::name() const
{
  return mName;
}

// @brief 入力ピンの時に true を返す．
bool
CiCellPin::is_input() const
{
  return false;
}

// @brief 出力ピンの時に true を返す．
bool
CiCellPin::is_output() const
{
  return false;
}

// @brief 入出力ピンの時に true を返す．
bool
CiCellPin::is_inout() const
{
  return false;
}

// @brief 内部ピンの時に true を返す．
bool
CiCellPin::is_internal() const
{
  return false;
}

// @brief 入力ピン番号を返す．
// @note 入力ピンもしくは入出力ピンの時のみ意味を持つ．
ymuint
CiCellPin::input_id() const
{
  return 0;
}

// @brief 負荷容量を返す．
ClibCapacitance
CiCellPin::capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 立ち上がり時の負荷容量を返す．
ClibCapacitance
CiCellPin::rise_capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 立ち下がり時の負荷容量を返す．
ClibCapacitance
CiCellPin::fall_capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 出力ピン番号を返す．
// @note 出力ピンもしくは入出力ピンの時のみ意味を持つ．
ymuint
CiCellPin::output_id() const
{
  return 0;
}

// @brief 論理式を持っているときに true を返す．
bool
CiCellPin::has_function() const
{
  return false;
}

// @brief 機能を表す論理式を返す．
Expr
CiCellPin::function() const
{
  return Expr::const_zero();
}

// @brief three_state 属性を持っているときに true を返す．
bool
CiCellPin::has_three_state() const
{
  return false;
}

// @brief three_state 論理式を返す．
Expr
CiCellPin::three_state() const
{
  return Expr::const_zero();
}

// @brief 最大ファンアウト容量を返す．
ClibCapacitance
CiCellPin::max_fanout() const
{
  return ClibCapacitance(0.0);
}

// @brief 最小ファンアウト容量を返す．
ClibCapacitance
CiCellPin::min_fanout() const
{
  return ClibCapacitance(0.0);
}

// @brief 最大負荷容量を返す．
ClibCapacitance
CiCellPin::max_capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 最小負荷容量を返す．
ClibCapacitance
CiCellPin::min_capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 最大遷移時間を返す．
ClibTime
CiCellPin::max_transition() const
{
  return ClibTime(0.0);
}

// @brief 最小遷移時間を返す．
ClibTime
CiCellPin::min_transition() const
{
  return ClibTime(0.0);
}

// @brief 内部ピン番号を返す．
// @note 内部ピンの時のみ意味を持つ．
ymuint
CiCellPin::internal_id() const
{
  return 0;
}

// @brief dump 用の共通情報を出力する．
void
CiCellPin::dump_common(ODO& s) const
{
  s << name()
    << pin_id();
}


//////////////////////////////////////////////////////////////////////
// クラス CiInputPin
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] cell 親のセル
// @param[in] name ピン名
// @param[in] capacitance 負荷容量
// @param[in] rise_capacitance 立ち上がり時の負荷容量
// @param[in] fall_capacitance 立ち下がり時の負荷容量
CiInputPin::CiInputPin(CiCell* cell,
		       const ShString& name,
		       ClibCapacitance capacitance,
		       ClibCapacitance rise_capacitance,
		       ClibCapacitance fall_capacitance) :
  CiCellPin(cell, name),
  mCapacitance(capacitance),
  mRiseCapacitance(rise_capacitance),
  mFallCapacitance(fall_capacitance)
{
}

// @brief デストラクタ
CiInputPin::~CiInputPin()
{
}

// @brief 方向を返す．
ClibCellPinDirection
CiInputPin::direction() const
{
  return kClibCellPinInput;
}

// @brief 入力ピンの時に true を返す．
bool
CiInputPin::is_input() const
{
  return true;
}

// @brief 入力ピン番号を返す．
// @note 入力ピンもしくは入出力ピンの時のみ意味を持つ．
ymuint
CiInputPin::input_id() const
{
  return mInputId;
}

// @brief 負荷容量を返す．
ClibCapacitance
CiInputPin::capacitance() const
{
  return mCapacitance;
}

// @brief 立ち上がり時の負荷容量を返す．
ClibCapacitance
CiInputPin::rise_capacitance() const
{
  return mRiseCapacitance;
}

// @brief 立ち下がり時の負荷容量を返す．
ClibCapacitance
CiInputPin::fall_capacitance() const
{
  return mFallCapacitance;
}

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
CiInputPin::dump(ODO& s) const
{
  dump_common(s);

  s << capacitance()
    << rise_capacitance()
    << fall_capacitance();
}


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPinBase
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] cell 親のセル
// @param[in] name ピン名
// @param[in] has_logic 論理式を持つとき true にするフラグ
// @param[in] logic_expr 論理式
// @param[in] tristate_expr tristate 条件式
// @param[in] max_fanout 最大ファンアウト容量
// @param[in] min_fanout 最小ファンアウト容量
// @param[in] max_capacitance 最大負荷容量
// @param[in] min_capacitance 最小負荷容量
// @param[in] max_transition 最大遷移時間
// @param[in] min_transition 最小遷移時間
CiOutputPinBase::CiOutputPinBase(CiCell* cell,
				 const ShString& name,
				 bool has_logic,
				 const Expr& logic_expr,
				 const Expr& tristate_expr,
				 ClibCapacitance max_fanout,
				 ClibCapacitance min_fanout,
				 ClibCapacitance max_capacitance,
				 ClibCapacitance min_capacitance,
				 ClibTime max_transition,
				 ClibTime min_transition) :
  CiCellPin(cell, name),
  mHasFunction(0U),
  mFunction(logic_expr),
  mThreeState(tristate_expr),
  mMaxFanout(max_fanout),
  mMinFanout(min_fanout),
  mMaxCapacitance(max_capacitance),
  mMinCapacitance(min_capacitance),
  mMaxTransition(max_transition),
  mMinTransition(min_transition)
{
  if ( has_logic ) {
    if ( tristate_expr.is_zero() ) {
      mHasFunction = 1U;
    }
    else {
      mHasFunction = 3U;
    }
  }
}

// @brief デストラクタ
CiOutputPinBase::~CiOutputPinBase()
{
}

// @brief 出力ピン番号を返す．
// @note 出力ピンもしくは入出力ピンの時のみ意味を持つ．
ymuint
CiOutputPinBase::output_id() const
{
  return mOutputId;
}

// @brief 論理式を持っているときに true を返す．
bool
CiOutputPinBase::has_function() const
{
  return static_cast<bool>(mHasFunction & 1U);
}

// @brief 機能を表す論理式を返す．
Expr
CiOutputPinBase::function() const
{
  return mFunction;
}

// @brief three_state 属性を持っているときに true を返す．
bool
CiOutputPinBase::has_three_state() const
{
  return static_cast<bool>((mHasFunction >> 1) & 1U);
}

// @brief three_state 論理式を返す．
Expr
CiOutputPinBase::three_state() const
{
  return mThreeState;
}

// @brief 最大ファンアウト容量を返す．
ClibCapacitance
CiOutputPinBase::max_fanout() const
{
  return mMaxFanout;
}

// @brief 最小ファンアウト容量を返す．
ClibCapacitance
CiOutputPinBase::min_fanout() const
{
  return mMinFanout;
}

// @brief 最大負荷容量を返す．
ClibCapacitance
CiOutputPinBase::max_capacitance() const
{
  return mMaxCapacitance;
}

// @brief 最小負荷容量を返す．
ClibCapacitance
CiOutputPinBase::min_capacitance() const
{
  return mMinCapacitance;
}

// @brief 最大遷移時間を返す．
ClibTime
CiOutputPinBase::max_transition() const
{
  return mMaxTransition;;
}

// @brief 最小遷移時間を返す．
ClibTime
CiOutputPinBase::min_transition() const
{
  return mMinTransition;
}


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPin
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] cell 親のセル
// @param[in] name ピン名
// @param[in] has_logic 論理式を持つとき true にするフラグ
// @param[in] logic_expr 論理式
// @param[in] tristate_expr tristate 条件式
// @param[in] max_fanout 最大ファンアウト容量
// @param[in] min_fanout 最小ファンアウト容量
// @param[in] max_capacitance 最大負荷容量
// @param[in] min_capacitance 最小負荷容量
// @param[in] max_transition 最大遷移時間
// @param[in] min_transition 最小遷移時間
CiOutputPin::CiOutputPin(CiCell* cell,
			 const ShString& name,
			 bool has_logic,
			 const Expr& logic_expr,
			 const Expr& tristate_expr,
			 ClibCapacitance max_fanout,
			 ClibCapacitance min_fanout,
			 ClibCapacitance max_capacitance,
			 ClibCapacitance min_capacitance,
			 ClibTime max_transition,
			 ClibTime min_transition) :
  CiOutputPinBase(cell, name,
		  has_logic, logic_expr, tristate_expr,
		  max_fanout, min_fanout,
		  max_capacitance, min_capacitance,
		  max_transition, min_transition)
{
}

// @brief デストラクタ
CiOutputPin::~CiOutputPin()
{
}

// @brief 方向を返す．
ClibCellPinDirection
CiOutputPin::direction() const
{
  return kClibCellPinOutput;
}

// @brief 出力ピンの時に true を返す．
bool
CiOutputPin::is_output() const
{
  return true;
}

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
CiOutputPin::dump(ODO& s) const
{
  dump_common(s);

  s << max_fanout()
    << min_fanout()
    << max_capacitance()
    << min_capacitance()
    << max_transition()
    << min_transition();
}


//////////////////////////////////////////////////////////////////////
// クラス CiInoutPin
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] cell 親のセル
// @param[in] name ピン名
// @param[in] has_logic 論理式を持つとき true にするフラグ
// @param[in] logic_expr 論理式
// @param[in] tristate_expr tristate 条件式
// @param[in] capacitance 負荷容量
// @param[in] rise_capacitance 立ち上がり時の負荷容量
// @param[in] fall_capacitance 立ち下がり時の負荷容量
// @param[in] max_fanout 最大ファンアウト容量
// @param[in] min_fanout 最小ファンアウト容量
// @param[in] max_capacitance 最大負荷容量
// @param[in] min_capacitance 最小負荷容量
// @param[in] max_transition 最大遷移時間
// @param[in] min_transition 最小遷移時間
CiInoutPin::CiInoutPin(CiCell* cell,
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
		       ClibTime min_transition) :
  CiOutputPinBase(cell, name,
		  has_logic, logic_expr, tristate_expr,
		  max_fanout, min_fanout,
		  max_capacitance, min_capacitance,
		  max_transition, min_transition),
  mCapacitance(capacitance),
  mRiseCapacitance(rise_capacitance),
  mFallCapacitance(fall_capacitance)
{
}

// @brief デストラクタ
CiInoutPin::~CiInoutPin()
{
}

// @brief 方向を返す．
ClibCellPinDirection
CiInoutPin::direction() const
{
  return kClibCellPinInput;
}

// @brief 入出力ピンの時に true を返す．
bool
CiInoutPin::is_inout() const
{
  return true;
}

// @brief 入力ピン番号を返す．
// @note 入力ピンもしくは入出力ピンの時のみ意味を持つ．
ymuint
CiInoutPin::input_id() const
{
  return mInputId;
}

// @brief 負荷容量を返す．
ClibCapacitance
CiInoutPin::capacitance() const
{
  return mCapacitance;
}

// @brief 立ち上がり時の負荷容量を返す．
ClibCapacitance
CiInoutPin::rise_capacitance() const
{
  return mRiseCapacitance;
}

// @brief 立ち下がり時の負荷容量を返す．
ClibCapacitance
CiInoutPin::fall_capacitance() const
{
  return mFallCapacitance;
}

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
CiInoutPin::dump(ODO& s) const
{
  dump_common(s);

  s << capacitance()
    << rise_capacitance()
    << fall_capacitance()
    << max_fanout()
    << min_fanout()
    << max_capacitance()
    << min_capacitance()
    << max_transition()
    << min_transition();
}


//////////////////////////////////////////////////////////////////////
// クラス CiInternalPin
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] cell 親のセル
// @param[in] name ピン名
CiInternalPin::CiInternalPin(CiCell* cell,
			     const ShString& name) :
  CiCellPin(cell, name)
{
}

// @brief デストラクタ
CiInternalPin::~CiInternalPin()
{
}

// @brief 方向を返す．
ClibCellPinDirection
CiInternalPin::direction() const
{
  return kClibCellPinInternal;
}

// @brief 内部ピンの時に true を返す．
bool
CiInternalPin::is_internal() const
{
  return true;
}

// @brief 内部ピン番号を返す．
// @note 内部ピンの時のみ意味を持つ．
ymuint
CiInternalPin::internal_id() const
{
  return mInternalId;
}

// @brief 内容をバイナリダンプする．
// @param[in] s 出力先のストリーム
void
CiInternalPin::dump(ODO& s) const
{
  dump_common(s);

  s << internal_id();
}

END_NAMESPACE_YM_CLIB
