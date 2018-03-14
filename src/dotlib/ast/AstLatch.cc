
/// @file AstLatch.cc
/// @brief AstLatch の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "AstLatch.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstLatch
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstLatch::AstLatch(const FileRegion& loc,
		   const AstString* var1,
		   const AstString* var2,
		   const AstExpr* clear,
		   const AstExpr* preset,
		   int clear_preset_var1,
		   int clear_preset_var2,
		   const AstExpr* data_in,
		   const AstExpr* enable,
		   const AstExpr* enable_also) :
  AstFL(loc, var1, var2, clear, preset, clear_preset_var1, clear_preset_var2),
  mDataIn(data_in),
  mEnable(enable),
  mEnableAlso(enable_also)
{
}

// @brief デストラクタ
AstLatch::~AstLatch()
{
}

#if 0
// @brief 内容を初期化する．
bool
AstLatch::set_data(const AstNode* node)
{
  AstAttrMap attr_map(node->attr_top());

  if ( !AstFL::set_data_sub(node, attr_map) ) {
    return false;
  }

  mDataIn = nullptr;
  mEnable = nullptr;
  mEnableAlso = nullptr;

  // data_in を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_data_in, mDataIn) ) {
    return false;
  }

  // enable を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_enable, mEnable) ) {
    return false;
  }

  // enable_also を取り出す．
  if ( !attr_map.expect_singleton_or_null(ATTR_enable_also, mEnableAlso) ) {
    return false;
  }

  return true;
}
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstLatch::dump(ostream& s,
		  int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
