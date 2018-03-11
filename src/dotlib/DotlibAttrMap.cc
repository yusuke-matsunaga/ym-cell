
/// @file DotlibAttrMap.cc
/// @brief DotlibAttrMap の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibAttrMap.h"
#include "dotlib/DotlibAttr.h"
#include "ym/Range.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibAttrMap
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_top 先頭の属性ノード
DotlibAttrMap::DotlibAttrMap(const DotlibAttr* attr_top)
{
  for ( const DotlibAttr* attr = attr_top;
	attr; attr = attr->next() ) {
    AttrType attr_type = attr->attr_type();
    const DotlibNode* attr_value = attr->attr_value();
    add(attr_type, attr_value);
  }
}

// @brief デストラクタ
DotlibAttrMap::~DotlibAttrMap()
{
}

// @brief 値を得る．
// @param[in] attr 属性
// @param[out] node_list 値のリストを格納する変数
// @retval true その属性値が定義されていた．
// @retval false その属性値が定義されていなかった．
bool
DotlibAttrMap::get_value(AttrType attr,
			 vector<const DotlibNode*>& node_list) const
{
  if ( !mHash.check(attr) ) {
    return false;
  }

  const vector<const DotlibNode*>& src_node_list = mHash[attr];
  node_list.clear();
  node_list.reserve(src_node_list.size());
  for ( auto node: src_node_list ) {
    node_list.push_back(node);
  }
  return true;
}

// @brief 値が単一と仮定してそのノードを返す．
// @param[in] attr 属性
// @param[in] loc 属性全体のファイル位置(エラー出力用)
// @param[out] node 結果のノードを格納するノード
// @retval true 値の読み出しが成功した．
// @retval false エラーが起こった．
bool
DotlibAttrMap::expect_singleton(AttrType attr,
				const FileRegion& loc,
				const DotlibNode*& node) const
{
  if ( !expect_singleton_or_null(attr, node) ) {
    return false;
  }
  if ( node == nullptr ) {
    ostringstream buf;
    buf << "No '" << attr << "' definition.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }
  return true;
}

// @brief 値が単一と仮定してそのノードを返す．
// @param[in] attr 属性
// @param[out] node 結果のノードを格納するノード
// @retval true 値の読み出しが成功した．
// @retval false エラーが起こった．
//
// 空の時は node に nullptr を入れて true を返す．
bool
DotlibAttrMap::expect_singleton_or_null(AttrType attr,
					const DotlibNode*& node) const
{
  if ( !mHash.check(attr) ) {
    node = nullptr;
    return true;
  }

  const vector<const DotlibNode*>& node_list = mHash[attr];
  if ( node_list.size() != 1 ) {
    const DotlibNode* second = node_list[1];
    ostringstream buf;
    buf << "More than one '" << attr << "' definitions."
	<< " First occurence is " << node->loc() << ".";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    second->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return false;
  }

  node = node_list[0];
  return true;
}

// @brief 内容を初期化する．
void
DotlibAttrMap::init()
{
  mHash.clear();
}

// @brief 値を追加する．
// @param[in] attr 属性
// @param[in] node 値を表すノード
void
DotlibAttrMap::add(AttrType attr,
		   const DotlibNode* node)
{
  if ( !mHash.check(attr) ) {
    mHash.add(attr, vector<const DotlibNode*>());
  }
  mHash[attr].push_back(node);
}

END_NAMESPACE_YM_DOTLIB
