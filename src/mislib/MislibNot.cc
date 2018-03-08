
/// @file MislibNot.cc
/// @brief MislibNot の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "MislibNot.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibNot
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibNot::MislibNot(const FileRegion& loc,
		     const MislibExpr* child1) :
  MislibExpr(loc),
  mChild1(child1)
{
}

// デストラクタ
MislibNot::~MislibNot()
{
}

// 種類を取り出す．
MislibExpr::Type
MislibNot::type() const
{
  return kNot;
}

// 1番目の子供を取り出す．
const MislibExpr*
MislibNot::child1() const
{
  return mChild1;
}

// @brief 対応する論理式を生成する．
// @param[in] name_map 端子名をキーにして端子番号を取り出す連想配列
Expr
MislibNot::to_expr(const HashMap<ShString, int>& name_map) const
{
  return ~child1()->to_expr(name_map);
}

// 内容を出力する．
// デバッグ用
void
MislibNot::dump(ostream& s) const
{
  s << "<NOT>" << endl;
  dump_loc(s);

  s << "<CHILD1>" << endl;
  child1()->dump(s);
  s << "</CHILD1>" << endl;

  s << "</NOT>" << endl;
}

END_NAMESPACE_YM_MISLIB
