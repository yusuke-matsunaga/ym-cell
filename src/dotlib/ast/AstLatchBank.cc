﻿
/// @file AstLatchBank.cc
/// @brief AstLatchBank の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstLatchBank.h"
#include "dotlib/AstMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief latch_bank を表す AstNode を生成する．
AstLatchBank*
AstMgr::new_latch_bank(const FileRegion& loc,
		       const AstString* var1,
		       const AstString* var2,
		       const AstInt* bits,
		       const AstExpr* clear,
		       const AstExpr* preset,
		       const AstCPType* clear_preset_var1,
		       const AstCPType* clear_preset_var2,
		       const AstExpr* enable_on,
		       const AstExpr* enable_on_also,
		       const AstExpr* data_in)
{
  ++ mLatchBankNum;
  void* p = mAlloc.get_memory(sizeof(AstLatchBank));
  return new (p) AstLatchBank(loc, var1, var2, bits, clear, preset,
			      clear_preset_var1, clear_preset_var2,
			      enable_on, enable_on_also, data_in);
}


//////////////////////////////////////////////////////////////////////
// クラス AstLatchBank
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstLatchBank::AstLatchBank(const FileRegion& loc,
			   const AstString* var1,
			   const AstString* var2,
			   const AstInt* bits,
			   const AstExpr* clear,
			   const AstExpr* preset,
			   const AstCPType* clear_preset_var1,
			   const AstCPType* clear_preset_var2,
			   const AstExpr* enable,
			   const AstExpr* enable_also,
			   const AstExpr* data_in) :
  AstLatch(loc, var1, var2, clear, preset, clear_preset_var1, clear_preset_var2,
	   enable, enable_also, data_in),
  mBits(bits)
{
}

// @brief デストラクタ
AstLatchBank::~AstLatchBank()
{
}

#if 0
// @brief 内容を初期化する．
bool
AstLatchBank::set_data(const AstNode* node)
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
AstLatchBank::dump(ostream& s,
		   int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
