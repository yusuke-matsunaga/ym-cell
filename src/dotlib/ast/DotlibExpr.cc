
/// @file DotlibExpr.cc
/// @brief DotlibExpr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/DotlibExpr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス DotlibExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
DotlibExpr::DotlibExpr(const FileRegion& loc) :
  DotlibNode(loc)
{
}

// @brief デストラクタ
DotlibExpr::~DotlibExpr()
{
}

// @brief 二項演算子型(kPlus, kMinus, kMult, kDiv)の時に true を返す．
bool
DotlibExpr::is_opr() const
{
  return false;
}

// @brief ブール値を返す．
//
// kBool の時のみ意味を持つ．
bool
DotlibExpr::bool_value() const
{
  ASSERT_NOT_REACHED;

  return false;
}

// @brief 文字列シンボルを返す．
//
// kStr の時のみ意味を持つ．
ShString
DotlibExpr::string_value() const
{
  ASSERT_NOT_REACHED;

  return ShString();
}

// @brief 第一オペランドを返す．
//
// kNot, kPlus, kMinus, kMult, kDiv の時のみ意味を持つ．
const DotlibExpr*
DotlibExpr::opr1() const
{
  ASSERT_NOT_REACHED;

  return nullptr;
}

// @brief 第二オペランドを返す．
//
// kPlus, kMinus, kMult, kDiv の時のみ意味を持つ．
const DotlibExpr*
DotlibExpr::opr2() const
{
  ASSERT_NOT_REACHED;

  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibBoolExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] val 値
DotlibBoolExpr::DotlibBoolExpr(const FileRegion& loc,
			       bool val) :
  DotlibExpr(loc),
  mValue(val)
{
}

// @brief デストラクタ
DotlibBoolExpr::~DotlibBoolExpr()
{
}

// @brief 型を返す．
DotlibExpr::Type
DotlibBoolExpr::type() const
{
  return kBool;
}

// @brief ブール値を返す．
//
// kBool の時のみ意味を持つ．
bool
DotlibBoolExpr::bool_value() const
{
  return mValue;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
DotlibBoolExpr::to_expr(const HashMap<ShString, int>& pin_map) const
{
  if ( mValue ) {
    return Expr::const_zero();
  }
  else {
    return Expr::const_one();
  }
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibBoolExpr::dump(ostream& s,
		     int indent) const
{
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibFlotExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] val 値
DotlibFloatExpr::DotlibFloatExpr(const FileRegion& loc,
				 double val) :
  DotlibExpr(loc),
  mValue(val)
{
}

// @brief デストラクタ
DotlibFloatExpr::~DotlibFloatExpr()
{
}

// @brief 型を返す．
DotlibExpr::Type
DotlibFloatExpr::type() const
{
  return kFloat;
}

// @brief 浮動小数点値を返す．
//
// kFloat の時のみ意味を持つ．
double
DotlibFloatExpr::float_value() const
{
  return mValue;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
DotlibFloatExpr::to_expr(const HashMap<ShString, int>& pin_map) const
{
  ASSERT_NOT_REACHED;
  return Expr();
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibFloatExpr::dump(ostream& s,
		      int indent) const
{
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibStrExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] val 値
DotlibStrExpr::DotlibStrExpr(const FileRegion& loc,
			     const ShString& val) :
  DotlibExpr(loc),
  mValue(val)
{
}

// @brief デストラクタ
DotlibStrExpr::~DotlibStrExpr()
{
}

// @brief 型を返す．
DotlibExpr::Type
DotlibStrExpr::type() const
{
  return kStr;
}

// @brief 文字列値を返す．
//
// kStr の時のみ意味を持つ．
ShString
DotlibStrExpr::string_value() const
{
  return mValue;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
DotlibStrExpr::to_expr(const HashMap<ShString, int>& pin_map) const
{
  int id;
  if ( !pin_map.find(mValue, id) ) {
    ostringstream buf;
    buf << mValue << ": No such pin-name.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    buf.str());
    return Expr();
  }
  return Expr::posi_literal(VarId(id));
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibStrExpr::dump(ostream& s,
		    int indent) const
{
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibSymbolExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] type シンボルの種類(kVDD, kVSS, kVCC)
DotlibSymbolExpr::DotlibSymbolExpr(const FileRegion& loc,
				   Type type) :
  DotlibExpr(loc),
  mType(type)
{
}

// @brief デストラクタ
DotlibSymbolExpr::~DotlibSymbolExpr()
{
}

// @brief 型を返す．
DotlibExpr::Type
DotlibSymbolExpr::type() const
{
  return mType;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
DotlibSymbolExpr::to_expr(const HashMap<ShString, int>& pin_map) const
{
  ASSERT_NOT_REACHED;
  return Expr();
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibSymbolExpr::dump(ostream& s,
		       int indent) const
{
#warning "TODO: 未完成"
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibNot
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] opr オペランド
DotlibNot::DotlibNot(const FileRegion& loc,
		     const DotlibExpr* opr) :
  DotlibExpr(loc),
  mOpr1(opr)
{
}

// @brief デストラクタ
DotlibNot::~DotlibNot()
{
}

// @brief 型を得る．
DotlibExpr::Type
DotlibNot::type() const
{
  return kNot;
}

// @brief 第一オペランドを返す．
// @note type() が演算子の型の時のみ意味を持つ．
const DotlibExpr*
DotlibNot::opr1() const
{
  return mOpr1;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
DotlibNot::to_expr(const HashMap<ShString, int>& pin_map) const
{
  Expr expr1 = opr1()->to_expr(pin_map);
  return ~expr1;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibNot::dump(ostream& s,
		int indent) const
{
  dump_indent(s, indent);
  s << "!( ";
  opr1()->dump(s, 0);
  s << " )";
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibOpr
//////////////////////////////////////////////////////////////////////

// @brief 表すコンストラクタ
// @param[in] type 演算子の型
// @param[in] opr1, opr2 オペランド
DotlibOpr::DotlibOpr(Type type,
		     const DotlibExpr* opr1,
		     const DotlibExpr* opr2) :
  DotlibExpr(FileRegion(opr1->loc(), opr2->loc())),
  mType(type),
  mOpr1(opr1),
  mOpr2(opr2)
{
}

// @brief デストラクタ
DotlibOpr::~DotlibOpr()
{
}

// @brief 型を得る．
DotlibExpr::Type
DotlibOpr::type() const
{
  return mType;
}

// @brief 演算子型(kPlus, kMinsu, kMult, kDiv)の時に true を返す．
bool
DotlibOpr::is_opr() const
{
  return true;
}

// @brief 式全体のファイル上の位置を返す．
FileRegion
DotlibOpr::loc() const
{
  return FileRegion(mOpr1->loc(), mOpr2->loc());
}

// @brief 第一オペランドを返す．
// @note type() が演算子の型の時のみ意味を持つ．
const DotlibExpr*
DotlibOpr::opr1() const
{
  return mOpr1;
}

// @brief 第二オペランドを返す．
// @note type() が演算子の型の時のみ意味を持つ．
const DotlibExpr*
DotlibOpr::opr2() const
{
  return mOpr2;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
DotlibOpr::to_expr(const HashMap<ShString, int>& pin_map) const
{
  Expr expr1 = opr1()->to_expr(pin_map);
  Expr expr2 = opr2()->to_expr(pin_map);
  switch ( type() ) {
  case DotlibExpr::kAnd: return expr1 & expr2;
  case DotlibExpr::kOr:  return expr1 | expr2;
  case DotlibExpr::kXor: return expr1 ^ expr2;
  default: break;
  }
  ASSERT_NOT_REACHED;
  return Expr();
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibOpr::dump(ostream& s,
		int indent) const
{
  dump_indent(s, indent);
  s << "( ";
  opr1()->dump(s, 0);
  switch ( type() ) {
  case kPlus:  s << " + "; break;
  case kMinus: s << " - "; break;
  case kMult:  s << " * "; break;
  case kDiv:   s << " / "; break;
  case kAnd:   s << " & "; break;
  case kOr:    s << " | "; break;
  case kXor:   s << " ^ "; break;
  default:     ASSERT_NOT_REACHED; break;
  }
  opr2()->dump(s, 0);
  s << " )";
}

END_NAMESPACE_YM_DOTLIB
