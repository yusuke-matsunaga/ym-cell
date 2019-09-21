
/// @file MislibVarName.cc
/// @brief MislibVarName の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "MislibVarName.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibVarName
//////////////////////////////////////////////////////////////////////

// コンストラクタ
MislibVarName::MislibVarName(const FileRegion& loc,
			     ShString str) :
  MislibExpr(loc),
  mVarName(str)
{
}

// デストラクタ
MislibVarName::~MislibVarName()
{
}

// @brief 種類を取り出す．
MislibExpr::Type
MislibVarName::type() const
{
  return VarName;
}

// @brief 対応する論理式を生成する．
// @param[in] name_map 端子名をキーにして端子番号を取り出す連想配列
Expr
MislibVarName::to_expr(const unordered_map<ShString, int>& name_map) const
{
  int c = name_map.count(varname());
  ASSERT_COND( c > 0 );

  int id = name_map.at(varname());
  VarId var(id);
  return Expr::posi_literal(var);
}

// @brief 変数名を取り出す
ShString
MislibVarName::varname() const
{
  return mVarName;
}

// 内容を出力する．
// デバッグ用
void
MislibVarName::dump(ostream& s) const
{
  s << "<VARNAME>" << endl;
  dump_loc(s);
  s << varname() << endl
    << "</VARNAME>" << endl;
}

END_NAMESPACE_YM_MISLIB
