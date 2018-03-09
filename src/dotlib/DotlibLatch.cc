
/// @file DotlibLatch.cc
/// @brief DotlibLatch の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibLatch.h"
#include "DotlibAttrMap.h"
#include "DotlibNode.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibLatch
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibLatch::DotlibLatch()
{
}

// @brief デストラクタ
DotlibLatch::~DotlibLatch()
{
}

// @brief 内容を初期化する．
bool
DotlibLatch::set_data(const DotlibNode* node)
{
  DotlibAttrMap attr_map(node->attr_top());

  if ( !DotlibFL::set_data_sub(node, attr_map) ) {
    return false;
  }

  mDataIn = nullptr;
  mEnable = nullptr;
  mEnableAlso = nullptr;

  // data_in を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_DATA_IN, mDataIn) ) {
    return false;
  }

  // enable を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_ENABLE, mEnable) ) {
    return false;
  }

  // enable_also を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_ENABLE_ALSO, mEnableAlso) ) {
    return false;
  }

  return true;
}

// @brief "data_in" を返す．
const DotlibNode*
DotlibLatch::data_in() const
{
  return mDataIn;
}

// @brief "enable" を返す．
const DotlibNode*
DotlibLatch::enable() const
{
  return mEnable;
}

// @brief "enable_also" を返す．
const DotlibNode*
DotlibLatch::enable_also() const
{
  return mEnableAlso;
}

END_NAMESPACE_YM_DOTLIB
