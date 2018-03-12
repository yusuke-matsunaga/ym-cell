
/// @file DotlibNode.cc
/// @brief DotlibNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibNode.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibNode
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
DotlibNode::DotlibNode(const FileRegion& loc) :
  mLoc(loc)
{
}

// @brief デストラクタ
DotlibNode::~DotlibNode()
{
}

// @brief 1つの文字列からなるリストの場合に文字列を返す．
// @note 仮定が外れたらアボートする．
ShString
DotlibNode::get_string_from_value_list() const
{
  ASSERT_NOT_REACHED;
  return ShString();
}

// @brief 2つの文字列からなるリストの内容を取り出す．
// @param[out] str1 1つ目の文字列を格納する変数
// @param[out] str2 2つ目の文字列を格納する変数
// @retval true 正しく読み込めた．
// @retval false エラーが起こった．
// @note エラーは MsgMgr に出力する．
bool
DotlibNode::expect_string_pair(ShString& str1,
			       ShString& str2) const
{
  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc(),
		  kMsgError,
		  "DOTLIB_PARSER",
		  "Expected string list of size 2.");
  return false;
}

// @brief float 値を取り出す．
// @note 型が違ったらエラーを MsgMgr に出力する．
bool
DotlibNode::expect_float(double& value) const
{
  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc(),
		  kMsgError,
		  "DOTLIB_PARSER",
		  "Float value is expected.");
  return false;
}

// @brief 文字列を取り出す．
// @note 型が違ったらエラーを MsgMgr に出力する．
bool
DotlibNode::expect_string(ShString& value) const
{
  MsgMgr::put_msg(__FILE__, __LINE__,
		  loc(),
		  kMsgError,
		  "DOTLIB_PARSER",
		  "String value is expected.");
  return false;
}

// @brief インデント数分だけ空白を出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibNode::dump_indent(ostream& s,
			int indent)
{
  for ( int i = 0; i < indent; ++ i ) {
    s << ' ';
  }
}

// @brief 文字列を出力する．
// @param[in] s 出力先のストリーム
// @param[in] str 対象の文字列
//
// str 中に [a-zA-Z0-9_] 以外の文字が含まれていたら
// " " で囲んで出力する．
void
DotlibNode::dump_string(ostream& s,
			const char* str)
{
  bool need_quote = false;
  for ( auto p = str; *p; ++ p ) {
    int c = *p;
    if ( !isalnum(c) && c != '_' ) {
      need_quote = true;
      break;
    }
  }
  if ( need_quote ) {
    s << "\"";
  }
  s << str;
  if ( need_quote ) {
    s << "\"";
  }
}

END_NAMESPACE_YM_DOTLIB
