
/// @file AstPin.cc
/// @brief AstPin の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "AstMgr.h"
#include "AstPin.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ピンを表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] name_list ピン名のリスト
// @param[in] pin_direction 方向
// @param[in] capacitance 容量
// @param[in] rise_capacitance 立ち上がり容量
// @param[in] fall_capacitance 立ち下がり容量
// @param[in] max_fanout 最大ファンアウト
// @param[in] min_fanout 最小ファンアウト
// @param[in] max_capacitance 最大容量
// @param[in] min_capacitance 最小容量
// @param[in] max_transition 最大遷移時間
// @param[in] min_transition 最小遷移時間
// @param[in] function 関数
// @param[in] three_state スリーステート条件
// @param[in] internal_node 対応する内部ノード
// @param[in] pin_func_type 'pin_func_type'
// @param[in] timing_top タイミングの先頭
AstPin*
AstMgr::new_pin(const FileRegion& loc,
		const vector<const AstString*>& name_list,
		const AstPinDirection* pin_direction,
		const AstFloat* capacitance,
		const AstFloat* rise_capacitance,
		const AstFloat* fall_capacitance,
		const AstFloat* max_fanout,
		const AstFloat* min_fanout,
		const AstFloat* max_capacitance,
		const AstFloat* min_capacitance,
		const AstFloat* max_transition,
		const AstFloat* min_transition,
		const AstExpr* function,
		const AstExpr* three_state,
		const AstNode* internal_node,
		const AstNode* pin_func_type,
		const vector<const AstTiming*>& timing_list)
{
  void* p = mAlloc.get_memory(sizeof(AstPin));
  return new (p) AstPin(loc, name_list, pin_direction,
			capacitance, rise_capacitance, fall_capacitance,
			max_fanout, min_fanout,
			max_capacitance, min_capacitance,
			max_transition, min_transition,
			function, three_state,
			internal_node, pin_func_type, timing_list,
			mAlloc);
}


//////////////////////////////////////////////////////////////////////
// クラス AstPin
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] name_list ピン名のリスト
// @param[in] pin_direction 方向
// @param[in] capacitance 容量
// @param[in] rise_capacitance 立ち上がり容量
// @param[in] fall_capacitance 立ち下がり容量
// @param[in] max_fanout 最大ファンアウト
// @param[in] min_fanout 最小ファンアウト
// @param[in] max_capacitance 最大容量
// @param[in] min_capacitance 最小容量
// @param[in] max_transition 最大遷移時間
// @param[in] min_transition 最小遷移時間
// @param[in] function 関数
// @param[in] three_state スリーステート条件
// @param[in] internal_node 対応する内部ノード
// @param[in] pin_func_type 'pin_func_type'
// @param[in] timing_top タイミングの先頭
AstPin::AstPin(const FileRegion& loc,
	       const vector<const AstString*>& name_list,
	       const AstPinDirection* pin_direction,
	       const AstFloat* capacitance,
	       const AstFloat* rise_capacitance,
	       const AstFloat* fall_capacitance,
	       const AstFloat* max_fanout,
	       const AstFloat* min_fanout,
	       const AstFloat* max_capacitance,
	       const AstFloat* min_capacitance,
	       const AstFloat* max_transition,
	       const AstFloat* min_transition,
	       const AstExpr* function,
	       const AstExpr* three_state,
	       const AstNode* internal_node,
	       const AstNode* pin_func_type,
	       const vector<const AstTiming*>& timing_list,
	       Alloc& alloc) :
  AstNode(loc),
  mNameNum(name_list.size()),
  mNameList(alloc.get_array<const AstString*>(mNameNum)),
  mPinDirection(pin_direction),
  mCapacitance(capacitance),
  mRiseCapacitance(rise_capacitance),
  mFallCapacitance(fall_capacitance),
  mMaxFanout(max_fanout),
  mMinFanout(min_fanout),
  mMaxCapacitance(max_capacitance),
  mMinCapacitance(min_capacitance),
  mMaxTransition(max_transition),
  mMinTransition(min_transition),
  mFunction(function),
  mThreeState(three_state),
  mPinFuncType(pin_func_type),
  mTimingNum(timing_list.size()),
  mTimingList(alloc.get_array<const AstTiming*>(mTimingNum))
{
  for ( auto i: Range(mNameNum) ) {
    mNameList[i] = name_list[i];
  }
  for ( auto i: Range(mTimingNum) ) {
    mTimingList[i] = timing_list[i];
  }
}

// @brief デストラクタ
AstPin::~AstPin()
{
}

#if 0
// @brief 内容をセットする．
bool
AstPin::set_data(const AstNode* pin_node)
{
  mFunction = nullptr;
  mThreeState = nullptr;
  mInternalNode = nullptr;
  mPinFuncType = nullptr;
  mTmingTop = nullptr;

  // 名前のリストを設定する．
  const AstNode* list_node = pin_node->group_value();
  int n = list_node->list_size();
  mNameList.clear();
  mNameList.resize(n);
  for ( int i = 0; i < n; ++ i ) {
    const AstNode* str_node = list_node->list_elem(i);
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
  AstAttrMap attr_map(pin_node->attr_top());

  // 'direction' の翻訳をする．
  const AstNode* direction_node;
  if ( !attr_map.expect_singleton(ATTR_DIRECTION, pin_node->loc(), direction_node) ) {
    // 'direction' がないのはエラー
    return false;
  }
  ASSERT_COND( direction_node->type() == AstNode::kCellPinDirection );
  mDirection = direction_node->cell_pin_direction();

  // 'capacitance' を取り出す．
  const AstNode* cap_node = nullptr;
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

  const AstNode* rcap_node = nullptr;
  const AstNode* fcap_node = nullptr;
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
  const AstNode* max_fo_node = nullptr;
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
  const AstNode* min_fo_node = nullptr;
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
  const AstNode* max_cap_node = nullptr;
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
  const AstNode* min_cap_node = nullptr;
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
  const AstNode* max_trans_node = nullptr;
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
  const AstNode* min_trans_node = nullptr;
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
  vector<const AstNode*> timing_list;
  attr_map.get_value(ATTR_TIMING, timing_list);

#warning "TODO: timing_list から AstTiming のリストを作る．"

  return true;
}
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstPin::dump(ostream& s,
	     int indent) const
{
  #warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
