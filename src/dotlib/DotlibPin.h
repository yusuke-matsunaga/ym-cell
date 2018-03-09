#ifndef DOTLIBPIN_H
#define DOTLIBPIN_H

/// @file DotlibPin.h
/// @brief DotlibPin のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "ym/ShString.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibPin DotlibPin.h "DotlibPin.h"
/// @brief DotlibNode の木から取り出したピンの情報を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibPin
{
public:

  /// @brief コンストラクタ
  DotlibPin();

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

  /// @brief "timing" グループのリストを得る．
  const vector<const DotlibNode*>&
  timing_list() const;


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
  vector<const DotlibNode*> mTimingList;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBPIN_H
