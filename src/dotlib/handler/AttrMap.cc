
/// @file AstAttrMap.cc
/// @brief AstAttrMap の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "AstAttrMap.h"
#include "dotlib/AstAttr.h"
#include "ym/Range.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstAttrMap
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_top 先頭の属性ノード
AstAttrMap::AstAttrMap(const AstAttr* attr_top)
{
  for ( const AstAttr* attr = attr_top;
	attr; attr = attr->next() ) {
    AttrType attr_type = attr->attr_type();
    const AstNode* attr_value = attr->attr_value();
    add(attr_type, attr_value);
  }
}

// @brief デストラクタ
AstAttrMap::~AstAttrMap()
{
}

// @brief 値を得る．
// @param[in] attr 属性
// @param[out] node_list 値のリストを格納する変数
// @retval true その属性値が定義されていた．
// @retval false その属性値が定義されていなかった．
bool
AstAttrMap::get_value(AttrType attr,
			 vector<const AstNode*>& node_list) const
{
  if ( !mHash.check(attr) ) {
    return false;
  }

  const vector<const AstNode*>& src_node_list = mHash[attr];
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
AstAttrMap::expect_singleton(AttrType attr,
				const FileRegion& loc,
				const AstNode*& node) const
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
AstAttrMap::expect_singleton_or_null(AttrType attr,
					const AstNode*& node) const
{
  if ( !mHash.check(attr) ) {
    node = nullptr;
    return true;
  }

  const vector<const AstNode*>& node_list = mHash[attr];
  if ( node_list.size() != 1 ) {
    const AstNode* second = node_list[1];
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
AstAttrMap::init()
{
  mHash.clear();
}

// @brief 値を追加する．
// @param[in] attr 属性
// @param[in] node 値を表すノード
void
AstAttrMap::add(AttrType attr,
		   const AstNode* node)
{
  if ( !mHash.check(attr) ) {
    mHash.add(attr, vector<const AstNode*>());
  }
  mHash[attr].push_back(node);
}

END_NAMESPACE_YM_DOTLIB
