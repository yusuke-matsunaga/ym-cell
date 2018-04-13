
/// @file AstFF.cc
/// @brief AstFF の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstFF.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstFF
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstFF::AstFF(const FileRegion& loc,
	     const AstString* var1,
	     const AstString* var2,
	     const AstExpr* clear,
	     const AstExpr* preset,
	     int clear_preset_var1,
	     int clear_preset_var2,
	     const AstExpr* next_state,
	     const AstExpr* clocked_on,
	     const AstExpr* clocked_on_also) :
  AstFL(loc, var1, var2, clear, preset, clear_preset_var1, clear_preset_var2),
  mNextState(next_state),
  mClockedOn(clocked_on),
  mClockedOnAlso(clocked_on_also)
{
}

// @brief デストラクタ
AstFF::~AstFF()
{
}

#if 0
// @brief 内容を初期化する．
bool
AstFF::set_data(const AstNode* node)
{
  AstAttrMap attr_map(node->attr_top());

  if ( !AstFL::set_data_sub(node, attr_map) ) {
    return false;
  }

  mNextState = nullptr;
  mClockedOn = nullptr;
  mClockedOnAlso = nullptr;

  // next_state を取り出す．
  if ( !attr_map.expect_singleton(ATTR_next_state, node->loc(), mNextState) ) {
    return false;
  }

  // clocked_on を取り出す．
  if ( !attr_map.expect_singleton(ATTR_clockED_ON, node->loc(), mClockedOn) ) {
    return false;
  }

  // clocked_on_also を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_clockED_ON_ALSO, mClockedOnAlso) ) {
    return false;
  }

  return true;
}
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFF::dump(ostream& s,
	    int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
