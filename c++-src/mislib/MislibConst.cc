﻿
/// @file MislibConst.cc
/// @brief MislibConst0, MislibConst1 の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "MislibConst.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibConst0
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibConst0::MislibConst0(const FileRegion& loc) :
  MislibExpr(loc)
{
}

// デストラクタ
MislibConst0::~MislibConst0()
{
}

// 種類を取り出す．
MislibExpr::Type
MislibConst0::type() const
{
  return Const0;
}

// @brief 対応する論理式を生成する．
// @param[in] name_map 端子名をキーにして端子番号を取り出す連想配列
Expr
MislibConst0::to_expr(const unordered_map<ShString, int>& name_map) const
{
  return Expr::zero();
}

// 内容を出力する．
// デバッグ用
void
MislibConst0::dump(ostream& s) const
{
  s << "<CONST0>" << endl;
  dump_loc(s);
  s << "</CONST0>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibConst1
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibConst1::MislibConst1(const FileRegion& loc) :
  MislibExpr(loc)
{
}

// デストラクタ
MislibConst1::~MislibConst1()
{
}

// 種類を取り出す．
MislibExpr::Type
MislibConst1::type() const
{
  return Const1;
}

// @brief 対応する論理式を生成する．
// @param[in] name_map 端子名をキーにして端子番号を取り出す連想配列
Expr
MislibConst1::to_expr(const unordered_map<ShString, int>& name_map) const
{
  return Expr::one();
}

// 内容を出力する．
// デバッグ用
void
MislibConst1::dump(ostream& s) const
{
  s << "<CONST1>" << endl;
  dump_loc(s);
  s << "</CONST1>" << endl;
}

END_NAMESPACE_YM_MISLIB
