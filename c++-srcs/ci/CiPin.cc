
/// @file CiPin.cc
/// @brief CiPin の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2017, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ci/CiPin.h"


BEGIN_NAMESPACE_YM_CLIB

//////////////////////////////////////////////////////////////////////
// クラス CiPin
//////////////////////////////////////////////////////////////////////

// @brief ピン名を返す．
string
CiPin::name() const
{
  return mName;
}

// @brief 入力ピンの時に true を返す．
bool
CiPin::is_input() const
{
  return false;
}

// @brief 出力ピンの時に true を返す．
bool
CiPin::is_output() const
{
  return false;
}

// @brief 入出力ピンの時に true を返す．
bool
CiPin::is_inout() const
{
  return false;
}

// @brief 内部ピンの時に true を返す．
bool
CiPin::is_internal() const
{
  return false;
}

// @brief 入力ピン番号を返す．
SizeType
CiPin::input_id() const
{
  return 0;
}

// @brief 負荷容量を返す．
ClibCapacitance
CiPin::capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 立ち上がり時の負荷容量を返す．
ClibCapacitance
CiPin::rise_capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 立ち下がり時の負荷容量を返す．
ClibCapacitance
CiPin::fall_capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 出力ピン番号を返す．
SizeType
CiPin::output_id() const
{
  return 0;
}

// @brief 最大ファンアウト容量を返す．
ClibCapacitance
CiPin::max_fanout() const
{
  return ClibCapacitance(0.0);
}

// @brief 最小ファンアウト容量を返す．
ClibCapacitance
CiPin::min_fanout() const
{
  return ClibCapacitance(0.0);
}

// @brief 最大負荷容量を返す．
ClibCapacitance
CiPin::max_capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 最小負荷容量を返す．
ClibCapacitance
CiPin::min_capacitance() const
{
  return ClibCapacitance(0.0);
}

// @brief 最大遷移時間を返す．
ClibTime
CiPin::max_transition() const
{
  return ClibTime(0.0);
}

// @brief 最小遷移時間を返す．
ClibTime
CiPin::min_transition() const
{
  return ClibTime(0.0);
}

// @brief 内部ピン番号を返す．
SizeType
CiPin::internal_id() const
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
