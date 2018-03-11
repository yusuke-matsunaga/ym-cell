
/// @file DotlibFF.cc
/// @brief DotlibFF の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibFF.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibFF
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibFF::DotlibFF(const FileRegion& loc,
		   const ShString var1,
		   const ShString var2,
		   const DotlibExpr* clear,
		   const DotlibExpr* preset,
		   int clear_preset_var1,
		   int clear_preset_var2,
		   const DotlibExpr* next_state,
		   const DotlibExpr* clocked_on,
		   const DotlibExpr* clocked_on_also) :
  DotlibFL(loc, var1, var2, clear, preset, clear_preset_var1, clear_preset_var2),
  mNextState(next_state),
  mClockedOn(clocked_on),
  mClockedOnAlso(clocked_on_also)
{
}

// @brief デストラクタ
DotlibFF::~DotlibFF()
{
}

#if 0
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
#endif

END_NAMESPACE_YM_DOTLIB
