
/// @file DotlibPin.cc
/// @brief DotlibPin の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibPin.h"
#include "DotlibNode.h"
#include "DotlibAttr.h"
#include "DotlibAttrMap.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibPin
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibPin::DotlibPin()
{
}

// @brief デストラクタ
DotlibPin::~DotlibPin()
{
}

// @brief 内容をセットする．
bool
DotlibPin::set_data(const DotlibNode* pin_node)
{
  mFunction = nullptr;
  mThreeState = nullptr;
  mInternalNode = nullptr;
  mPinFuncType = nullptr;

  mTimingList.clear();

  // 名前のリストを設定する．
  const DotlibNode* list_node = pin_node->group_value();
  int n = list_node->list_size();
  mNameList.clear();
  mNameList.resize(n);
  for ( int i = 0; i < n; ++ i ) {
    const DotlibNode* str_node = list_node->list_elem(i);
    if ( !str_node->is_string() ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      str_node->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error. string value expected");
      return false;
    }
    mNameList[i] = str_node->string_value();
  }

  // 属性を attr_map に登録する．
  DotlibAttrMap attr_map(pin_node->attr_top());

  // 'direction' の翻訳をする．
  const DotlibNode* direction_node;
  if ( !attr_map.expect_singleton(ATTR_DIRECTION, pin_node->loc(), direction_node) ) {
    // 'direction' がないのはエラー
    return false;
  }
  ASSERT_COND( direction_node->type() == DotlibNode::kCellPinDirection );
  mDirection = direction_node->cell_pin_direction();

  // 'capacitance' を取り出す．
  const DotlibNode* cap_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_CAPACITANCE, cap_node) ) {
    return false;
  }
  if ( cap_node ) {
    if ( !cap_node->expect_float(mCapacitance) ) {
      return false;
    }
  }
  else {
    mCapacitance = 0.0;
  }

  const DotlibNode* rcap_node = nullptr;
  const DotlibNode* fcap_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_CAPACITANCE, rcap_node) ) {
    return false;
  }
  if ( !attr_map.expect_singleton_or_null(ATTR_FALL_CAPACITANCE, fcap_node) ) {
    return false;
  }
  if ( rcap_node && fcap_node ) {
    if ( !rcap_node->expect_float(mRiseCapacitance) ) {
      return false;
    }
    if ( !fcap_node->expect_float(mFallCapacitance) ) {
      return false;
    }
  }
  else {
    mRiseCapacitance = mCapacitance;
    mFallCapacitance = mCapacitance;
  }

  // 'max_fanout' を取り出す．
  const DotlibNode* max_fo_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_MAX_FANOUT, max_fo_node) ) {
    return false;
  }
  if ( max_fo_node ) {
    if ( !max_fo_node->expect_float(mMaxFanout) ) {
      return false;
    }
  }
  else {
    mMaxFanout = 0.0;
  }
  // 'min_fanout' を取り出す．
  const DotlibNode* min_fo_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_MIN_FANOUT, min_fo_node) ) {
    return false;
  }
  if ( min_fo_node ) {
    if ( !min_fo_node->expect_float(mMinFanout) ) {
      return false;
    }
  }
  else {
    mMinFanout = 0.0;
  }

  // 'max_capacitance' を取り出す．
  const DotlibNode* max_cap_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_MAX_CAPACITANCE, max_cap_node) ) {
    return false;
  }
  if ( max_cap_node ) {
    if ( !max_cap_node->expect_float(mMaxCapacitance) ) {
      return false;
    }
  }
  else {
    mMaxCapacitance = 0.0;
  }
  // 'min_capacitance' を取り出す．
  const DotlibNode* min_cap_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_MIN_CAPACITANCE, min_cap_node) ) {
    return false;
  }
  if ( min_cap_node ) {
    if ( !min_cap_node->expect_float(mMinCapacitance) ) {
      return false;
    }
  }
  else {
    mMinCapacitance = 0.0;
  }

  // 'max_transition' を取り出す．
  const DotlibNode* max_trans_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_MAX_TRANSITION, max_trans_node) ) {
    return false;
  }
  if ( max_trans_node ) {
    if ( !max_trans_node->expect_float(mMaxTransition) ) {
      return false;
    }
  }
  else {
    mMaxTransition = 0.0;
  }
  // 'min_transition' を取り出す．
  const DotlibNode* min_trans_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_MIN_TRANSITION, min_trans_node) ) {
    return false;
  }
  if ( min_trans_node ) {
    if ( !min_trans_node->expect_float(mMinTransition) ) {
      return false;
    }
  }
  else {
    mMinTransition = 0.0;
  }

  // 'function' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_FUNCTION, mFunction) ) {
    return false;
  }

  // 'three_state' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_THREE_STATE, mThreeState) ) {
    return false;
  }

  // 'internal_node' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_INTERNAL_NODE, mInternalNode) ) {
    return false;
  }

  // 'pin_func_type' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_PIN_FUNC_TYPE, mPinFuncType) ) {
    return false;
  }

  // 'timing' を取り出す．
  attr_map.get_value(ATTR_TIMING, mTimingList);

  return true;
}

// @brief 名前のリストの要素数を返す．
int
DotlibPin::num() const
{
  return mNameList.size();
}

// @brief 名前を返す．
// @param[in] pos 位置番号 ( 0 <= pos < num() )
ShString
DotlibPin::name(int pos) const
{
  ASSERT_COND( pos < num() );
  return mNameList[pos];
}

// @brief "direction" を返す．
ClibCellPinDirection
DotlibPin::direction() const
{
  return mDirection;
}

// @brief "capacitance" を返す．
double
DotlibPin::capacitance() const
{
  return mCapacitance;
}

// @brief "rise_capacitance" を返す．
double
DotlibPin::rise_capacitance() const
{
  return mRiseCapacitance;
}

// @brief "fall_capacitance" を返す．
double
DotlibPin::fall_capacitance() const
{
  return mFallCapacitance;
}

// @brief "max_fanout" を返す．
double
DotlibPin::max_fanout() const
{
  return mMaxFanout;
}

// @brief "min_fanout" を返す．
double
DotlibPin::min_fanout() const
{
  return mMinFanout;
}

// @brief "max_capacitance" を返す．
double
DotlibPin::max_capacitance() const
{
  return mMaxCapacitance;
}

// @brief "min_capacitance" を返す．
double
DotlibPin::min_capacitance() const
{
  return mMinCapacitance;
}

// @brief "max_transition" を返す．
double
DotlibPin::max_transition() const
{
  return mMaxTransition;
}

// @brief "min_transition" を返す．
double
DotlibPin::min_transition() const
{
  return mMinTransition;
}

// @brief "function" を返す．
const DotlibNode*
DotlibPin::function() const
{
  return mFunction;
}

// @brief "three_state" を返す．
const DotlibNode*
DotlibPin::three_state() const
{
  return mThreeState;
}

// @brief "internal_node" を返す．
const DotlibNode*
DotlibPin::internal_node() const
{
  return mInternalNode;
}

// @brief "pin_func_type" を返す．
const DotlibNode*
DotlibPin::pin_func_type() const
{
  return mPinFuncType;
}

// @brief "timing" グループのリストを得る．
const vector<const DotlibNode*>&
DotlibPin::timing_list() const
{
  return mTimingList;
}

END_NAMESPACE_YM_DOTLIB
