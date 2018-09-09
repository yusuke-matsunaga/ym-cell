
/// @file AstFF.cc
/// @brief AstFF の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstFF.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ff を表す AstNode を生成する．
AstFF*
AstMgr::new_ff(const FileRegion& loc,
	       const AstString* var1,
	       const AstString* var2,
	       const AstExpr* clear,
	       const AstExpr* preset,
	       const AstCPType* clear_preset_var1,
	       const AstCPType* clear_preset_var2,
	       const AstExpr* clocked_on,
	       const AstExpr* clocked_on_also,
	       const AstExpr* next_state)
{
  ++ mFFNum;
  void* p = mAlloc.get_memory(sizeof(AstFF));
  return new (p) AstFF(loc, var1, var2, clear, preset, clear_preset_var1, clear_preset_var2,
		       clocked_on, clocked_on_also, next_state);
}


//////////////////////////////////////////////////////////////////////
// クラス AstFF
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] var1, var2 変数名
// @param[in] clear クリア条件
// @param[in] preset プリセット条件
// @param[in] clear_preset_var1 'clear_preset_var1'
// @param[in] clear_preset_var2 'clear_preset_var2'
// @param[in] clocked_on クロック条件
// @param[in] clocked_on_also 追加クロック条件
// @param[in] next_state 次状態遷移条件
AstFF::AstFF(const FileRegion& loc,
	     const AstString* var1,
	     const AstString* var2,
	     const AstExpr* clear,
	     const AstExpr* preset,
	     const AstCPType* clear_preset_var1,
	     const AstCPType* clear_preset_var2,
	     const AstExpr* clocked_on,
	     const AstExpr* clocked_on_also,
	     const AstExpr* next_state) :
  AstFL(loc, var1, var2, clear, preset, clear_preset_var1, clear_preset_var2),
  mClockedOn(clocked_on),
  mClockedOnAlso(clocked_on_also),
  mNextState(next_state)
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
