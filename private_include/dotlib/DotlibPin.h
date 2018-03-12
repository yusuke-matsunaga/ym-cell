#ifndef DOTLIBPIN_H
#define DOTLIBPIN_H

/// @file DotlibPin.h
/// @brief DotlibPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "DotlibNode.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibPin DotlibPin.h "DotlibPin.h"
/// @brief DotlibNode の木から取り出したピンの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibPin :
  public DotlibNode
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] pin_direction 方向
  /// @param[in] capacitance 容量
  /// @param[in] rise_capacitance 立ち上がり容量
  /// @param[in] fall_capacitance 立ち下がり容量
  /// @param[in] max_fanout 最大ファンアウト
  /// @param[in] min_fanout 最小ファンアウト
  /// @param[in] max_capacitance 最大容量
  /// @param[in] min_capacitance 最小容量
  /// @param[in] max_transition 最大遷移時間
  /// @param[in] min_transition 最小遷移時間
  /// @param[in] function 関数
  /// @param[in] three_state スリーステート条件
  /// @param[in] internal_node 対応する内部ノード
  /// @param[in] pin_func_type 'pin_func_type'
  /// @param[in] timing_top タイミングの先頭
  DotlibPin(const FileRegion& loc,
	    const DotlibPinDirection* pin_direction,
	    const DotlibFloat* capacitance,
	    const DotlibFloat* rise_capacitance,
	    const DotlibFloat* fall_capacitance,
	    const DotlibFloat* max_fanout,
	    const DotlibFloat* min_fanout,
	    const DotlibFloat* max_capacitance,
	    const DotlibFloat* min_capacitance,
	    const DotlibFloat* max_transition,
	    const DotlibFloat* min_transition,
	    const DotlibExpr* function,
	    const DotlibExpr* three_state,
	    const DotlibNode* internal_node,
	    const DotlibNode* pin_func_type,
	    const DotlibTiming* timing_top);

  /// @brief デストラクタ
  ~DotlibPin();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

#if 0
  /// @brief 内容をセットする．
  bool
  set_data(const DotlibNode* pin_node);
#endif

  /// @brief 名前のリストの要素数を返す．
  int
  num() const;

  /// @brief 名前を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < num() )
  ShString
  name(int pos) const;

  /// @brief "direction" を返す．
  const DotlibPinDirection*
  direction() const;

  /// @brief "capacitance" を返す．
  const DotlibFloat*
  capacitance() const;

  /// @brief "rise_capacitance" を返す．
  const DotlibFloat*
  rise_capacitance() const;

  /// @brief "fall_capacitance" を返す．
  const DotlibFloat*
  fall_capacitance() const;

  /// @brief "max_fanout" を返す．
  const DotlibFloat*
  max_fanout() const;

  /// @brief "min_fanout" を返す．
  const DotlibFloat*
  min_fanout() const;

  /// @brief "max_capacitance" を返す．
  const DotlibFloat*
  max_capacitance() const;

  /// @brief "min_capacitance" を返す．
  const DotlibFloat*
  min_capacitance() const;

  /// @brief "max_transition" を返す．
  const DotlibFloat*
  max_transition() const;

  /// @brief "min_transition" を返す．
  const DotlibFloat*
  min_transition() const;

  /// @brief "function" を返す．
  const DotlibExpr*
  function() const;

  /// @brief "three_state" を返す．
  const DotlibExpr*
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

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ピン名のリスト
  vector<ShString> mNameList;

  // "direction"
  const DotlibPinDirection* mPinDirection;

  // "capacitance"
  const DotlibFloat* mCapacitance;

  // "rise_capacitance"
  const DotlibFloat* mRiseCapacitance;

  // "fall_capacitance"
  const DotlibFloat* mFallCapacitance;

  // "max_fanout"
  const DotlibFloat* mMaxFanout;

  // "min_fanout"
  const DotlibFloat* mMinFanout;

  // "max_capacitance"
  const DotlibFloat* mMaxCapacitance;

  // "min_capacitance"
  const DotlibFloat* mMinCapacitance;

  // "max_transition"
  const DotlibFloat* mMaxTransition;

  // "min_transition"
  const DotlibFloat* mMinTransition;

  // "function"
  const DotlibExpr* mFunction;

  // "three_state"
  const DotlibExpr* mThreeState;

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
const DotlibPinDirection*
DotlibPin::direction() const
{
  return mPinDirection;
}

// @brief "capacitance" を返す．
inline
const DotlibFloat*
DotlibPin::capacitance() const
{
  return mCapacitance;
}

// @brief "rise_capacitance" を返す．
inline
const DotlibFloat*
DotlibPin::rise_capacitance() const
{
  return mRiseCapacitance;
}

// @brief "fall_capacitance" を返す．
inline
const DotlibFloat*
DotlibPin::fall_capacitance() const
{
  return mFallCapacitance;
}

// @brief "max_fanout" を返す．
inline
const DotlibFloat*
DotlibPin::max_fanout() const
{
  return mMaxFanout;
}

// @brief "min_fanout" を返す．
inline
const DotlibFloat*
DotlibPin::min_fanout() const
{
  return mMinFanout;
}

// @brief "max_capacitance" を返す．
inline
const DotlibFloat*
DotlibPin::max_capacitance() const
{
  return mMaxCapacitance;
}

// @brief "min_capacitance" を返す．
inline
const DotlibFloat*
DotlibPin::min_capacitance() const
{
  return mMinCapacitance;
}

// @brief "max_transition" を返す．
inline
const DotlibFloat*
DotlibPin::max_transition() const
{
  return mMaxTransition;
}

// @brief "min_transition" を返す．
inline
const DotlibFloat*
DotlibPin::min_transition() const
{
  return mMinTransition;
}

// @brief "function" を返す．
inline
const DotlibExpr*
DotlibPin::function() const
{
  return mFunction;
}

// @brief "three_state" を返す．
inline
const DotlibExpr*
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
