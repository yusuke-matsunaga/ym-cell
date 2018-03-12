
/// @file DotlibNodeImpl.cc
/// @brief DotlibNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibList.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

BEGIN_NONAMESPACE

FileRegion
get_loc(const vector<DotlibNode*>& elem_list)
{
  int n = elem_list.size();
  if ( n > 0 ) {
    return FileRegion(elem_list[0]->loc(), elem_list[n - 1]->loc());
  }
  else {
    return FileRegion();
  }
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス DotlibList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] elem_list 要素のリスト
DotlibList::DotlibList(const vector<DotlibNode*>& elem_list) :
  DotlibNode(get_loc(elem_list))
{
  mNum = elem_list.size();
  for ( int i = 0; i < mNum; ++ i ) {
    mList[i] = elem_list[i];
  }
}

// @brief デストラクタ
DotlibList::~DotlibList()
{
}

// @brief 1つの文字列からなるリストの場合に文字列を返す．
//
// 仮定が外れたらアボートする．
ShString
DotlibList::get_string_from_value_list() const
{
  ASSERT_COND( list_size() == 1 );
  const DotlibNode* value = list_elem(0);
  ShString str;
  bool r = value->expect_string(str);
  ASSERT_COND( r );
  return str;
}

// @brief 2つの文字列からなるリストの内容を取り出す．
// @param[out] str1 1つ目の文字列を格納する変数
// @param[out] str2 2つ目の文字列を格納する変数
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
// @note エラーは MsgMgr に出力する．
bool
DotlibList::expect_string_pair(ShString& str1,
			       ShString& str2) const
{
  if ( list_size() != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Expected list size is 2.");
    return false;
  }
  const DotlibNode* node1 = list_elem(0);
  ASSERT_COND( node1 != nullptr );
  if ( !node1->expect_string(str1) ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    node1->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "String value is expected.");
    return false;
  }
  const DotlibNode* node2 = list_elem(1);
  ASSERT_COND( node2 != nullptr );
  if ( !node2->expect_string(str2) ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    node2->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "String value is expected.");
    return false;
  }
  return true;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibList::dump(ostream& s,
		 int indent) const
{
  s << "(";
  const char* comma = "";
  for ( int i = 0; i < list_size(); ++ i ) {
    s << comma;
    list_elem(i)->dump(s, 0);
    comma = ", ";
  }
  s << ")";
}

END_NAMESPACE_YM_DOTLIB
