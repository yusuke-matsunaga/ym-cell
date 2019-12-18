
/// @file AstPin.cc
/// @brief AstPin の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstPin.h"
#include "dotlib/StrListHandler.h"
#include "dotlib/PinHandler.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ピンを表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
const AstPin*
AstMgr::new_pin(const FileRegion& attr_loc,
		const StrListHandler& header,
		const PinHandler& group)
{
  ++ mPinNum;
  auto node = new AstPin(attr_loc, header, group);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
// クラス AstPin
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダを読み込んだハンドラ
// @param[in] group グループ本体を読み込んだハンドラ
AstPin::AstPin(const FileRegion& attr_loc,
	       const StrListHandler& header,
	       const PinHandler& group) :
  AstNameListNode{FileRegion(attr_loc, group.group_loc()), header},
  mDirection{group.mDirection},
  mCapacitance{group.mCapacitance},
  mRiseCapacitance{group.mRiseCapacitance},
  mFallCapacitance{group.mFallCapacitance},
  mMaxFanout{group.mMaxFanout},
  mMinFanout{group.mMinFanout},
  mMaxCapacitance{group.mMaxCapacitance},
  mMinCapacitance{group.mMinCapacitance},
  mMaxTransition{group.mMaxTransition},
  mMinTransition{group.mMinTransition},
  mFunction{group.mFunction},
  mThreeState{group.mThreeState},
  mPinFuncType{group.mPinFuncType},
  mTimingList{group.mTimingList}
{
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
  if ( !attr_map.expect_singleton(ATTR_direction, pin_node->loc(), direction_node) ) {
    // 'direction' がないのはエラー
    return false;
  }
  ASSERT_COND( direction_node->type() == AstNode::kCellPinDirection );
  mDirection = direction_node->cell_pin_direction();

  // 'capacitance' を取り出す．
  const AstNode* cap_node = nullptr;
  if ( !attr_map.expect_singleton_or_null(ATTR_capacitance, cap_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_RISE_capacitance, rcap_node) ) {
    return false;
  }
  if ( !attr_map.expect_singleton_or_null(ATTR_FALL_capacitance, fcap_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_max_fanout, max_fo_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_min_fanout, min_fo_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_MAX_capacitance, max_cap_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_MIN_capacitance, min_cap_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_max_transITION, max_trans_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_min_transition, min_trans_node) ) {
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
  if ( !attr_map.expect_singleton_or_null(ATTR_function, mFunction) ) {
    return false;
  }

  // 'three_state' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_three_state, mThreeState) ) {
    return false;
  }

  // 'internal_node' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_internal_node, mInternalNode) ) {
    return false;
  }

  // 'pin_func_type' を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_pin_func_type, mPinFuncType) ) {
    return false;
  }

  // 'timing' を取り出す．
  vector<const AstNode*> timing_list;
  attr_map.get_value(ATTR_timing, timing_list);

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
