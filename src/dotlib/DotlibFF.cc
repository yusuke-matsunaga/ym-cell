
/// @file DotlibFF.cc
/// @brief DotlibFF の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibFF.h"
#include "DotlibAttr.h"
#include "DotlibAttrMap.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibFF
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibFF::DotlibFF()
{
}

// @brief デストラクタ
DotlibFF::~DotlibFF()
{
}

// @brief 内容を初期化する．
bool
DotlibFF::set_data(const DotlibNode* node)
{
  DotlibAttrMap attr_map(node->attr_top());

  if ( !DotlibFL::set_data_sub(node, attr_map) ) {
    return false;
  }

  mNextState = nullptr;
  mClockedOn = nullptr;
  mClockedOnAlso = nullptr;

  // next_state を取り出す．
  if ( !attr_map.expect_singleton(ATTR_NEXT_STATE, node->loc(), mNextState) ) {
    return false;
  }

  // clocked_on を取り出す．
  if ( !attr_map.expect_singleton(ATTR_CLOCKED_ON, node->loc(), mClockedOn) ) {
    return false;
  }

  // clocked_on_also を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_CLOCKED_ON_ALSO, mClockedOnAlso) ) {
    return false;
  }

  return true;
}

// @brief "next_state" を返す．
const DotlibNode*
DotlibFF::next_state() const
{
  return mNextState;
}

// @brief "clocked_on" を返す．
const DotlibNode*
DotlibFF::clocked_on() const
{
  return mClockedOn;
}

// @brief "clocked_on_also" を返す．
const DotlibNode*
DotlibFF::clocked_on_also() const
{
  return mClockedOnAlso;
}

END_NAMESPACE_YM_DOTLIB
