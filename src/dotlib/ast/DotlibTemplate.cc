
/// @file DotlibTemplte.cc
/// @brief DotlibTemplate の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibTemplate.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibTemplate
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] name 名前
// @param[in] dimension 次元数
// @param[in] var_1, var_2, var_3 変数のタイプ
// @param[in] index_1, index_2, index_3 インデックスのベクタ
DotlibTemplate::DotlibTemplate(const FileRegion& loc,
			       const DotlibString* name,
			       const DotlibInt* dimension,
			       const DotlibVarType* var_1,
			       const DotlibVarType* var_2,
			       const DotlibVarType* var_3,
			       const DotlibFloatVector* index_1,
			       const DotlibFloatVector* index_2,
			       const DotlibFloatVector* index_3) :
  DotlibNode(loc),
  mName(name),
  mDimension(dimension),
  mVar1(var_1),
  mVar2(var_2),
  mVar3(var_3),
  mIndex1(index_1),
  mIndex2(index_2),
  mIndex3(index_3)
{
}

// @brief デストラクタ
DotlibTemplate::~DotlibTemplate()
{
}

#if 0
BEGIN_NONAMESPACE

inline
bool
node_to_var(const DotlibNode* node,
	    ClibVarType &var)
{
  if ( node == nullptr ) {
    var = kClibVarNone;
    return true;
  }

  ASSERT_COND( node->type() == DotlibNode::kVarType );
  var = node->var_type();
  return true;
}

END_NONAMESPACE

// @brief 内容をセットする．
bool
DotlibTemplate::set_data(const DotlibNode* node)
{
  // 名前を設定する．
  mName = node->group_value()->get_string_from_value_list();

  // 属性を attr_map に登録する．
  DotlibAttrMap attr_map(node->attr_top());

  // 'variable_1' の翻訳をする．
  const DotlibNode* var1_node;
  if ( !attr_map.expect_singleton(ATTR_VARIABLE_1, node->loc(), var1_node) ) {
    // 'variable_1' がないのはエラー
    return false;
  }
  if ( !node_to_var(var1_node, mVar1) ) {
    return false;
  }

  // 'variable_2' の翻訳をする．
  const DotlibNode* var2_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_VARIABLE_2, var2_node) ) {
    return false;
  }
  if ( !node_to_var(var2_node, mVar2) ) {
    return false;
  }

  // 'variable_3' の翻訳をする．
  const DotlibNode* var3_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_VARIABLE_3, var3_node) ) {
    return false;
  }
  if ( var3_node != nullptr && var2_node == nullptr ) {
    // variable_2 がなくて variable_3 があるのはエラー
    MsgMgr::put_msg(__FILE__, __LINE__,
		    var3_node->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'variable_2'.");
    return false;
  }
  if ( !node_to_var(var3_node, mVar3) ) {
    return false;
  }

  // 'index_1' を取り出す．
  const DotlibNode* index1_node;
  if ( !attr_map.expect_singleton(ATTR_INDEX_1, node->loc(), index1_node) ) {
    // index_1 がないのはエラー
    return false;
  }
  mIndex1 = index1_node->list_elem(0);

  // 'index_2' を取り出す．
  const DotlibNode* index2_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_INDEX_2, index2_node) ) {
    return false;
  }
  if ( var2_node != nullptr && index2_node == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    node->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'index_2'.");
    return false;
  }
  if ( var2_node == nullptr && index2_node != nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    node->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'variable_2'.");
    return false;
  }
  if ( index2_node ) {
    mIndex2 = index2_node->list_elem(0);
  }
  else {
    mIndex2 = nullptr;
  }

  // 'index_3' を取り出す．
  const DotlibNode* index3_node;
  if ( !attr_map.expect_singleton_or_null(ATTR_INDEX_3, index3_node) ) {
    return false;
  }
  if ( var3_node != nullptr && index3_node == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    node->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'index_3'.");
    return false;
  }
  if ( var3_node == nullptr && index3_node != nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    node->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error. missing 'variable_3'.");
    return false;
  }
  if ( index3_node ) {
    mIndex3 = index3_node->list_elem(0);
  }
  else {
    mIndex3 = nullptr;
  }

  if ( var3_node != nullptr ) {
    mDimension = 3;
  }
  else if ( var2_node != nullptr ) {
    mDimension = 2;
  }
  else {
    mDimension = 1;
  }

  return true;
}
#endif

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibTemplate::dump(ostream& s,
		     int indent) const
{
#warning "TODO: 未完成"
}

END_NAMESPACE_YM_DOTLIB
