
/// @file DotlibLut.cc
/// @brief DotlibLut
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibLut.h"
#include "DotlibNode.h"
#include "DotlibAttr.h"
#include "DotlibAttrMap.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibLut
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibLut::DotlibLut()
{
}

// @brief デストラクタ
DotlibLut::~DotlibLut()
{
}

// @brief 内容をセットする．
bool
DotlibLut::set_data(const DotlibNode* node)
{
  // 名前をセットする．
  mName = node->group_value()->get_string_from_value_list();

  // 属性を attr_map に登録する．
  DotlibAttrMap attr_map(node->attr_top());

  // 'index_1' を取り出す．
  const DotlibNode* index1_node;
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
  const DotlibNode* index2_node;
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
  const DotlibNode* index3_node;
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

// @brief テンプレート名を返す．
ShString
DotlibLut::template_name() const
{
  return mName;
}

// @brief 'index_1' のノードを返す．
// @note 未定義なら nullptr を返す．
const DotlibNode*
DotlibLut::index_1() const
{
  return mIndex1;
}

// @brief 'index_2' のノードを返す．
// @note 未定義なら nullptr を返す．
const DotlibNode*
DotlibLut::index_2() const
{
  return mIndex2;
}

// @brief 'index_3' のノードを返す．
// @note 未定義なら nullptr を返す．
const DotlibNode*
DotlibLut::index_3() const
{
  return mIndex3;
}

// @brief 値のリストを返す．
// @note 1次元でもリストとなる．
const DotlibNode*
DotlibLut::value_list() const
{
  return mValueList;
}

END_NAMESPACE_YM_DOTLIB
