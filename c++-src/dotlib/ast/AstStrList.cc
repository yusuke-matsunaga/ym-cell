﻿
/// @file AstStrList.cc
/// @brief AstStrList の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstStrList.h"
#include "dotlib/AstString.h"
#include "dotlib/StrListHandler.h"
#include "ym/Range.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 文字列のリストを表す AstNode を生成する．
// @param[in] handler ハンドラ
const AstStrList*
AstMgr::new_str_list(const StrListHandler& handler)
{
  const vector<const AstString*>& value = handler.value();
  int n = value.size();
  ++ mStrVectNum;
  mStrVectElemSize += n;
  auto node = new AstStrList(handler);
  mNodeList.push_back(node);
  return node;
}


//////////////////////////////////////////////////////////////////////
/// クラス AstStrList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] handler ハンドラ
AstStrList::AstStrList(const StrListHandler& handler) :
  AstNode(FileRegion(handler.first_loc(), handler.last_loc())),
  mNum(handler.value().size())
{
  for ( auto i: Range(mNum) ) {
    mBody[i] = handler.value()[i];
  }
}

// @brief デストラクタ
AstStrList::~AstStrList()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstStrList::dump(ostream& s,
		 int indent) const
{
  const char* comma = "";
  for ( auto i: Range(mNum) ) {
    s << comma;
    comma = ", ";
    dump_string(s, mBody[i]->value());
  }
}

END_NAMESPACE_YM_DOTLIB
