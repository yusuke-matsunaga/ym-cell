
/// @file AstLut.cc
/// @brief AstLut
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "AstMgr.h"
#include "AstLut.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief LUT を表す AstNode を生成する．
AstLut*
AstMgr::new_lut(const FileRegion& loc,
		const AstString* name,
		const AstFloatVector* index_1,
		const AstFloatVector* index_2,
		const AstFloatVector* index_3,
		const AstFloatVector* value_list)
{
  ++ mLutNum;
  void* p = mAlloc.get_memory(sizeof(AstLut));
  return new (p) AstLut(loc, name, index_1, index_2, index_3, value_list);
}


//////////////////////////////////////////////////////////////////////
// クラス AstLut
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] index_1, index_2, index_3 インデックスのベクタ
// @param[in] value_list 値のリスト
AstLut::AstLut(const FileRegion& loc,
	       const AstString* name,
	       const AstFloatVector* index_1,
	       const AstFloatVector* index_2,
	       const AstFloatVector* index_3,
	       const AstFloatVector* value_list) :
  AstNode(loc),
  mName(name),
  mIndex1(index_1),
  mIndex2(index_2),
  mIndex3(index_3),
  mValueList(value_list)
{
}

// @brief デストラクタ
AstLut::~AstLut()
{
}

#if 0
// @brief 内容をセットする．
bool
AstLut::set_data(const AstNode* node)
{
  // 名前をセットする．
  mName = node->group_value()->get_string_from_value_list();

  // 属性を attr_map に登録する．
  AstAttrMap attr_map(node->attr_top());

  // 'index_1' を取り出す．
  const AstNode* index1_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_INDEX_1, index1_node) ) {
    return false;
  }
  if ( index1_node ) {
    mIndex1 = index1_node->list_elem(0);
  }
  else {
    mIndex1 = nullptr;
  }

  // 'index_2' を取り出す．
  const AstNode* index2_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_INDEX_2, index2_node) ) {
    return false;
  }
  if ( index2_node ) {
    mIndex2 = index2_node->list_elem(0);
  }
  else {
    mIndex2 = nullptr;
  }

  // 'index_3' を取り出す．
  const AstNode* index3_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_INDEX_3, index3_node) ) {
    return false;
  }
  if ( index3_node ) {
    mIndex3 = index3_node->list_elem(0);
  }
  else {
    mIndex3 = nullptr;
  }

  // 'values' を取り出す．
  if ( !attr_map.expect_singleton(ATTR_VALUES, node->loc(), mValueList) ) {
    return false;
  }

  return true;
}
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstLut::dump(ostream& s,
	     int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
