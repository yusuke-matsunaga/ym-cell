
/// @file MislibNode.cc
/// @brief MislibNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "MislibNode.h"
#include "MislibExpr.h"
#include "MislibGate.h"


BEGIN_NAMESPACE_YM_MISLIB

//////////////////////////////////////////////////////////////////////
// クラス MislibNum
//////////////////////////////////////////////////////////////////////

// 内容を出力する．
void
MislibNum::dump(
  ostream& s
) const
{
  s << "<NUM>" << endl;
  dump_loc(s);
  s << num() << endl
    << "</NUM>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibStr
//////////////////////////////////////////////////////////////////////

// 内容を出力する．
void
MislibStr::dump(
  ostream& s
) const
{
  s << "<STR>" << endl;
  dump_loc(s);
  s << str() << endl
    << "</STR>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibNoinv
//////////////////////////////////////////////////////////////////////

// 種類を取り出す．
MislibPhase::Type
MislibNoninv::type() const
{
  return Noninv;
}

// 内容を出力する．
// デバッグ用
void
MislibNoninv::dump(
  ostream& s
) const
{
  s << "<NONINV>" << endl;
  dump_loc(s);
  s << "</NONINV>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibInv
//////////////////////////////////////////////////////////////////////

// 種類を取り出す．
MislibPhase::Type
MislibInv::type() const
{
  return Inv;
}

// 内容を出力する．
// デバッグ用
void
MislibInv::dump(
  ostream& s
) const
{
  s << "<INV>" << endl;
  dump_loc(s);
  s << "</INV>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibUnknown
//////////////////////////////////////////////////////////////////////

// 種類を取り出す．
MislibPhase::Type
MislibUnknown::type() const
{
  return Unknown;
}

// 内容を出力する．
// デバッグ用
void
MislibUnknown::dump(
  ostream& s
) const
{
  s << "<UNKNOWN>" << endl;
  dump_loc(s);
  s << "</UNKNOWN>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibExpr
//////////////////////////////////////////////////////////////////////

// @brief 変数名を取り出す
//
// デフォルトの実装ではエラー(アボート)となる．
ShString
MislibExpr::varname() const
{
  ASSERT_NOT_REACHED;
  return ShString();
}

// 1番目のオペランドを取り出す．
// デフォルトの実装ではエラー(アボート)となる．
const MislibExpr*
MislibExpr::opr1() const
{
  ASSERT_NOT_REACHED;
  return nullptr;
}

// 2番目のオペランドを取り出す．
// デフォルトの実装ではエラー(アボート)となる．
const MislibExpr*
MislibExpr::opr2() const
{
  ASSERT_NOT_REACHED;
  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibNot
//////////////////////////////////////////////////////////////////////

// 種類を取り出す．
MislibExpr::Type
MislibNot::type() const
{
  return Not;
}

// 1番目のオペランドを取り出す．
const MislibExpr*
MislibNot::opr1() const
{
  return mOpr1.get();
}

// @brief 対応する論理式を生成する．
Expr
MislibNot::to_expr(
  const unordered_map<ShString, int>& name_map
) const
{
  return ~opr1()->to_expr(name_map);
}

// 内容を出力する．
void
MislibNot::dump(
  ostream& s
) const
{
  s << "<NOT>" << endl;
  dump_loc(s);

  s << "<CHILD1>" << endl;
  opr1()->dump(s);
  s << "</CHILD1>" << endl;

  s << "</NOT>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibBop
//////////////////////////////////////////////////////////////////////

// 1番目のオペランドを取り出す．
const MislibExpr*
MislibBop::opr1() const
{
  return mOpr1.get();
}

// 2番目のオペランドを取り出す．
const MislibExpr*
MislibBop::opr2() const
{
  return mOpr2.get();
}


//////////////////////////////////////////////////////////////////////
// クラス MislibAnd
//////////////////////////////////////////////////////////////////////

// 種類を取り出す．
MislibExpr::Type
MislibAnd::type() const
{
  return And;
}

// @brief 対応する論理式を生成する．
Expr
MislibAnd::to_expr(
  const unordered_map<ShString, int>& name_map
) const
{
  return opr1()->to_expr(name_map) & opr2()->to_expr(name_map);
}

// 内容を出力する．
void
MislibAnd::dump(
  ostream& s
) const
{
  s << "<AND>" << endl;
  dump_loc(s);

  s << "<CHILD1>" << endl;
  opr1()->dump(s);
  s << "</CHILD1>" << endl;

  s << "<CHILD2>" << endl;
  opr2()->dump(s);
  s << "</CHILD2>" << endl;

  s << "</AND>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibOr
//////////////////////////////////////////////////////////////////////

// 種類を取り出す．
MislibExpr::Type
MislibOr::type() const
{
  return Or;
}

// @brief 対応する論理式を生成する．
Expr
MislibOr::to_expr(
  const unordered_map<ShString, int>& name_map
) const
{
  return opr1()->to_expr(name_map) | opr2()->to_expr(name_map);
}

// 内容を出力する．
void
MislibOr::dump(
  ostream& s
) const
{
  s << "<OR>" << endl;
  dump_loc(s);

  s << "<CHILD1>" << endl;
  opr1()->dump(s);
  s << "</CHILD1>" << endl;

  s << "<CHILD2>" << endl;
  opr2()->dump(s);
  s << "</CHILD2>" << endl;

  s << "</OR>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibXor
//////////////////////////////////////////////////////////////////////

// 種類を取り出す．
MislibExpr::Type
MislibXor::type() const
{
  return Xor;
}

// @brief 対応する論理式を生成する．
Expr
MislibXor::to_expr(
  const unordered_map<ShString, int>& name_map
) const
{
  return opr1()->to_expr(name_map) ^ opr2()->to_expr(name_map);
}

// 内容を出力する．
void
MislibXor::dump(
  ostream& s
) const
{
  s << "<XOR>" << endl;
  dump_loc(s);

  s << "<CHILD1>" << endl;
  opr1()->dump(s);
  s << "</CHILD1>" << endl;

  s << "<CHILD2>" << endl;
  opr2()->dump(s);
  s << "</CHILD2>" << endl;

  s << "</XOR>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibVarName
//////////////////////////////////////////////////////////////////////

// @brief 種類を取り出す．
MislibExpr::Type
MislibVarName::type() const
{
  return VarName;
}

// @brief 対応する論理式を生成する．
Expr
MislibVarName::to_expr(
  const unordered_map<ShString, int>& name_map
) const
{
  int c = name_map.count(varname());
  ASSERT_COND( c > 0 );

  int id = name_map.at(varname());
  VarId var(id);
  return Expr::make_posi_literal(var);
}

// @brief 変数名を取り出す
ShString
MislibVarName::varname() const
{
  return mVarName;
}

// 内容を出力する．
void
MislibVarName::dump(
  ostream& s
) const
{
  s << "<VARNAME>" << endl;
  dump_loc(s);
  s << varname() << endl
    << "</VARNAME>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibConst0
//////////////////////////////////////////////////////////////////////

// 種類を取り出す．
MislibExpr::Type
MislibConst0::type() const
{
  return Const0;
}

// @brief 対応する論理式を生成する．
Expr
MislibConst0::to_expr(
  const unordered_map<ShString, int>& name_map
) const
{
  return Expr::make_zero();
}

// 内容を出力する．
void
MislibConst0::dump(
  ostream& s
) const
{
  s << "<CONST0>" << endl;
  dump_loc(s);
  s << "</CONST0>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibConst1
//////////////////////////////////////////////////////////////////////

// 種類を取り出す．
MislibExpr::Type
MislibConst1::type() const
{
  return Const1;
}

// @brief 対応する論理式を生成する．
// @param[in] name_map 端子名をキーにして端子番号を取り出す連想配列
Expr
MislibConst1::to_expr(
  const unordered_map<ShString, int>& name_map
) const
{
  return Expr::make_one();
}

// 内容を出力する．
void
MislibConst1::dump(
  ostream& s
) const
{
  s << "<CONST1>" << endl;
  dump_loc(s);
  s << "</CONST1>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibPin
//////////////////////////////////////////////////////////////////////

// 内容を出力する．
// デバッグ用
void
MislibPin::dump(ostream& s) const
{
  s << "<PIN>" << endl;
  dump_loc(s);

  s << "<NAME>" << endl;
  if ( name() ) {
    name()->dump(s);
  }
  else {
    s << "*" << endl;
  }
  s << "</NAME>" << endl;

  s << "<PHASE>" << endl;
  phase()->dump(s);
  s << "</PHASE>" << endl;

  s << "<INPUT_LOAD>" << endl;
  input_load()->dump(s);
  s << "</INPUT_LOAD>" << endl;

  s << "<MAX_LOAD>" << endl;
  max_load()->dump(s);
  s << "</MAX_LOAD>" << endl;

  s << "<RISE_BLOCK_DELAY>" << endl;
  rise_block_delay()->dump(s);
  s << "</RISE_BLOCK_DELAY>" << endl;

  s << "<RISE_FANOUT_DELAY>" << endl;
  rise_fanout_delay()->dump(s);
  s << "</RISE_FANOUT_DELAY>" << endl;

  s << "<FALL_BLOCK_DELAY>" << endl;
  fall_block_delay()->dump(s);
  s << "</FALL_BLOCK_DELAY>" << endl;

  s << "<FALLE_FANOUT_DELAY>" << endl;
  fall_fanout_delay()->dump(s);
  s << "</FALL_FANOUT_DELAY>" << endl;

  s << "</PIN>" << endl;
}


//////////////////////////////////////////////////////////////////////
// クラス MislibGate
//////////////////////////////////////////////////////////////////////

// @brief 内容を出力する．
void
MislibGate::dump(
  ostream& s
) const
{
  s << "<GATE>" << endl;
  dump_loc(s);

  s << "<NAME>" << endl;
  name()->dump(s);
  s << "</NAME>" << endl;

  s << "<AREA>" << endl;
  area()->dump(s);
  s << "</AREA>" << endl;

  s << "<OPIN_NAME>" << endl;
  opin_name()->dump(s);
  s << "</OPIN_NAME>" << endl;

  s << "<OPIN_EXPR>" << endl;
  opin_expr()->dump(s);
  s << "</OPIN_EXPR>" << endl;

  s << "<IPIN_LIST>" << endl;
  int n = ipin_num();
  for ( int i = 0; i < n; ++ i ) {
    auto pin = ipin(i);
    pin->dump(s);
  }
  s << "</IPIN_LIST>" << endl;

  s << "</GATE>" << endl;
}

END_NAMESPACE_YM_MISLIB
