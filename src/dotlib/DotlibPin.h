#ifndef DOTLIBPIN_H
#define DOTLIBPIN_H

/// @file DotlibPin.h
/// @brief DotlibPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibBase.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibPin DotlibPin.h "DotlibPin.h"
/// @brief DotlibNode の木から取り出したピンの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibPin :
  public DotlibBase
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  DotlibPin(const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 内容をセットする．
  bool
  set_data(const DotlibNode* pin_node);

  /// @brief 名前のリストの要素数を返す．
  int
  num() const;

  /// @brief 名前を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  ShString
  name(int pos) const;

  /// @brief "direction" を返す．
  ClibCellPinDirection
  direction() const;

  /// @brief "capacitance" を返す．
  double
  capacitance() const;

  /// @brief "rise_capacitance" を返す．
  double
  rise_capacitance() const;

  /// @brief "fall_capacitance" を返す．
  double
  fall_capacitance() const;

  /// @brief "max_fanout" を返す．
  double
  max_fanout() const;

  /// @brief "min_fanout" を返す．
  double
  min_fanout() const;

  /// @brief "max_capacitance" を返す．
  double
  max_capacitance() const;

  /// @brief "min_capacitance" を返す．
  double
  min_capacitance() const;

  /// @brief "max_transition" を返す．
  double
  max_transition() const;

  /// @brief "min_transition" を返す．
  double
  min_transition() const;

  /// @brief "function" を返す．
  const DotlibNode*
  function() const;

  /// @brief "three_state" を返す．
  const DotlibNode*
  three_state() const;

  /// @brief "internal_node" を返す．
  const DotlibNode*
  internal_node() const;

  /// @brief "pin_func_type" を返す．
  const DotlibNode*
  pin_func_type() const;

  /// @brief "timing" グループのリストの先頭を得る．
  const DotlibTiming*
  timing_top() const;

  /// @brief 次の要素を返す．
  const DotlibPin*
  next() const;

  /// @brief 次の要素を設定する．
  void
  set_next(const DotlibPin* next);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ピン名のリスト
  vector<ShString> mNameList;

  // "direction"
  ClibCellPinDirection mDirection;

  // "capacitance"
  double mCapacitance;

  // "rise_capacitance"
  double mRiseCapacitance;

  // "fall_capacitance"
  double mFallCapacitance;

  // "max_fanout"
  double mMaxFanout;

  // "min_fanout"
  double mMinFanout;

  // "max_capacitance"
  double mMaxCapacitance;

  // "min_capacitance"
  double mMinCapacitance;

  // "max_transition"
  double mMaxTransition;

  // "min_transition"
  double mMinTransition;

  // "function"
  const DotlibNode* mFunction;

  // "three_state"
  const DotlibNode* mThreeState;

  // "internal_node"
  const DotlibNode* mInternalNode;

  // "pin_func_type"
  const DotlibNode* mPinFuncType;

  // "timing"
  const DotlibTiming* mTimingTop;

  // 次の要素
  const DotlibPin* mNext;

};


//////////////////////////////////////////////////////////////////////
// インライン関数の定義
//////////////////////////////////////////////////////////////////////

// @brief 名前のリストの要素数を返す．
inline
int
DotlibPin::num() const
{
  return mNameList.size();
}

// @brief 名前を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
inline
ShString
DotlibPin::name(int pos) const
{
  ASSERT_COND( pos < num() );
  return mNameList[pos];
}

// @brief "direction" を返す．
inline
ClibCellPinDirection
DotlibPin::direction() const
{
  return mDirection;
}

// @brief "capacitance" を返す．
inline
double
DotlibPin::capacitance() const
{
  return mCapacitance;
}

// @brief "rise_capacitance" を返す．
inline
double
DotlibPin::rise_capacitance() const
{
  return mRiseCapacitance;
}

// @brief "fall_capacitance" を返す．
inline
double
DotlibPin::fall_capacitance() const
{
  return mFallCapacitance;
}

// @brief "max_fanout" を返す．
inline
double
DotlibPin::max_fanout() const
{
  return mMaxFanout;
}

// @brief "min_fanout" を返す．
inline
double
DotlibPin::min_fanout() const
{
  return mMinFanout;
}

// @brief "max_capacitance" を返す．
inline
double
DotlibPin::max_capacitance() const
{
  return mMaxCapacitance;
}

// @brief "min_capacitance" を返す．
inline
double
DotlibPin::min_capacitance() const
{
  return mMinCapacitance;
}

// @brief "max_transition" を返す．
inline
double
DotlibPin::max_transition() const
{
  return mMaxTransition;
}

// @brief "min_transition" を返す．
inline
double
DotlibPin::min_transition() const
{
  return mMinTransition;
}

// @brief "function" を返す．
inline
const DotlibNode*
DotlibPin::function() const
{
  return mFunction;
}

// @brief "three_state" を返す．
inline
const DotlibNode*
DotlibPin::three_state() const
{
  return mThreeState;
}

// @brief "internal_node" を返す．
inline
const DotlibNode*
DotlibPin::internal_node() const
{
  return mInternalNode;
}

// @brief "pin_func_type" を返す．
inline
const DotlibNode*
DotlibPin::pin_func_type() const
{
  return mPinFuncType;
}

// @brief "timing" グループのリストの先頭を得る．
inline
const DotlibTiming*
DotlibPin::timing_top() const
{
  return mTimingTop;
}

// @brief 次の要素を返す．
inline
const DotlibPin*
DotlibPin::next() const
{
  return mNext;
}

// @brief 次の要素を設定する．
inline
void
DotlibPin::set_next(const DotlibPin* next)
{
  mNext = next;
}

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBPIN_H
