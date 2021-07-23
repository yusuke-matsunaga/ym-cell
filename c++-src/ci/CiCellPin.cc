
/// @file CiCellPin.cc
/// @brief CiCellPin の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiCellPin.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiCellPin
//////////////////////////////////////////////////////////////////////

// @brief ピン番号を返す．
SizeType
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
SizeType
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
SizeType
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
  return Expr::make_zero();
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
  return Expr::make_zero();
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
SizeType
CiCellPin::internal_id() const
{
  return 0;
}


//////////////////////////////////////////////////////////////////////
// クラス CiInputPin
//////////////////////////////////////////////////////////////////////

// @brief 方向を返す．
ClibDirection
CiInputPin::direction() const
{
  return ClibDirection::input;
}

// @brief 入力ピンの時に true を返す．
bool
CiInputPin::is_input() const
{
  return true;
}

// @brief 入力ピン番号を返す．
SizeType
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


//////////////////////////////////////////////////////////////////////
// クラス CiOutputPinBase
//////////////////////////////////////////////////////////////////////

// @brief 出力ピン番号を返す．
SizeType
CiOutputPinBase::output_id() const
{
  return mOutputId;
}

// @brief 論理式を持っているときに true を返す．
bool
CiOutputPinBase::has_function() const
{
  return mFlags[0];
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
  return mFlags[1];
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

// @brief 方向を返す．
ClibDirection
CiOutputPin::direction() const
{
  return ClibDirection::output;
}

// @brief 出力ピンの時に true を返す．
bool
CiOutputPin::is_output() const
{
  return true;
}


//////////////////////////////////////////////////////////////////////
// クラス CiInoutPin
//////////////////////////////////////////////////////////////////////

// @brief 方向を返す．
ClibDirection
CiInoutPin::direction() const
{
  return ClibDirection::inout;
}

// @brief 入出力ピンの時に true を返す．
bool
CiInoutPin::is_inout() const
{
  return true;
}

// @brief 入力ピン番号を返す．
SizeType
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


//////////////////////////////////////////////////////////////////////
// クラス CiInternalPin
//////////////////////////////////////////////////////////////////////

// @brief 方向を返す．
ClibDirection
CiInternalPin::direction() const
{
  return ClibDirection::internal;
}

// @brief 内部ピンの時に true を返す．
bool
CiInternalPin::is_internal() const
{
  return true;
}

// @brief 内部ピン番号を返す．
SizeType
CiInternalPin::internal_id() const
{
  return mInternalId;
}

END_NAMESPACE_YM_CLIB
