
/// @file DotlibLatch.cc
/// @brief DotlibLatch の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibLatch.h"
//#include "DotlibAttrMap.h"
//#include "DotlibNode.h"
//#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibLatch
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibLatch::DotlibLatch(const FileRegion& loc,
			 const ShString var1,
			 const ShString var2,
			 const DotlibExpr* clear,
			 const DotlibExpr* preset,
			 int clear_preset_var1,
			 int clear_preset_var2,
			 const DotlibExpr* data_in,
			 const DotlibExpr* enable,
			 const DotlibExpr* enable_also) :
  DotlibFL(loc, var1, var2, clear, preset, clear_preset_var1, clear_preset_var2),
  mDataIn(data_in),
  mEnable(enable),
  mEnableAlso(enable_also)
{
}

// @brief デストラクタ
DotlibLatch::~DotlibLatch()
{
}

#if 0
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
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibLatch::dump(ostream& s,
		  int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
