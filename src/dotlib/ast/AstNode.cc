
/// @file AstNode.cc
/// @brief AstNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstNode.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstNode
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
AstNode::AstNode(const FileRegion& loc) :
  mLoc(loc)
{
}

// @brief デストラクタ
AstNode::~AstNode()
{
}

// @brief インデント数分だけ空白を出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstNode::dump_indent(ostream& s,
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
AstNode::dump_string(ostream& s,
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
