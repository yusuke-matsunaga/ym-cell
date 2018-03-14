
/// @file AstGenGroup.cc
/// @brief AstGenGroup の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstMgr.h"
#include "AstGenGroup.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 汎用のグループ構造を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value_list 値のリスト
// @param[in] attr_top 属性の先頭
AstGenGroup*
AstMgr::new_gen_group(const FileRegion& loc,
		      const vector<const AstNode*>& value_list,
		      const vector<const AstAttr*>& attr_list)
{
  void* p = mAlloc.get_memory(sizeof(AstGenGroup));
  return new (p) AstGenGroup(loc, value_list, attr_list, mAlloc);
}

//////////////////////////////////////////////////////////////////////
// クラス AstGenGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
AstGenGroup::AstGenGroup(const FileRegion& loc,
			 const vector<const AstNode*>& value_list,
			 const vector<const AstAttr*>& attr_list,
			 Alloc& alloc) :
  AstNode(loc),
  mValueNum(value_list.size()),
  mValueList(alloc.get_array<const AstNode*>(mValueNum)),
  mAttrNum(attr_list.size()),
  mAttrList(alloc.get_array<const AstAttr*>(mAttrNum))
{
  for ( auto i: Range(mValueNum) ) {
    mValueList[i] = value_list[i];
  }
  for ( auto i: Range(mAttrNum) ) {
    mAttrList[i] = attr_list[i];
  }
}

// @brief デストラクタ
AstGenGroup::~AstGenGroup()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstGenGroup::dump(ostream& s,
		  int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
