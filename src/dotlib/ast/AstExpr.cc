
/// @file AstExpr.cc
/// @brief AstExpr の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstExpr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief + 演算子を表す AstExpr を生成する．
// @param[in] opr1, opr2 オペランド
AstExpr*
AstMgr::new_plus(const AstExpr* opr1,
		 const AstExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(AstOpr));
  return new (p) AstOpr(AstExprType::Plus, opr1, opr2);
}

// @brief - 演算子を表す AstExpr を生成する．
// @param[in] opr1, opr2 オペランド
AstExpr*
AstMgr::new_minus(const AstExpr* opr1,
		  const AstExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(AstOpr));
  return new (p) AstOpr(AstExprType::Minus, opr1, opr2);
}

// @brief * 演算子を表す AstExpr を生成する．
// @param[in] opr1, opr2 オペランド
AstExpr*
AstMgr::new_mult(const AstExpr* opr1,
		 const AstExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(AstOpr));
  return new (p) AstOpr(AstExprType::Mult, opr1, opr2);
}

// @brief / 演算子を表す AstExpr を生成する．
// @param[in] opr1, opr2 オペランド
AstExpr*
AstMgr::new_div(const AstExpr* opr1,
		const AstExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(AstOpr));
  return new (p) AstOpr(AstExprType::Div, opr1, opr2);
}

// @brief NOT 演算子を表す AstExpr を生成する．
// @param[in] loc ファイル上の位置
// @param[in] opr オペランド
AstExpr*
AstMgr::new_not(const FileRegion& loc,
		const AstExpr* opr)
{
  ++ mNotNum;
  void* p = mAlloc.get_memory(sizeof(AstNot));
  return new (p) AstNot(loc, opr);
}

// @brief AND 演算子を表す AstExpr を生成する．
// @param[in] opr1, opr2 オペランド
AstExpr*
AstMgr::new_and(const AstExpr* opr1,
		const AstExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(AstOpr));
  return new (p) AstOpr(AstExprType::And, opr1, opr2);
}

// @brief OR 演算子を表す AstExpr を生成する．
// @param[in] opr1, opr2 オペランド
AstExpr*
AstMgr::new_or(const AstExpr* opr1,
	       const AstExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(AstOpr));
  return new (p) AstOpr(AstExprType::Or, opr1, opr2);
}

// @brief XOR 演算子を表す AstExpr を生成する．
// @param[in] opr1, opr2 オペランド
AstExpr*
AstMgr::new_xor(const AstExpr* opr1,
		const AstExpr* opr2)
{
  ++ mOprNum;
  void* p = mAlloc.get_memory(sizeof(AstOpr));
  return new (p) AstOpr(AstExprType::Xor, opr1, opr2);
}

// @brief ブール値(0 or 1)を表す AstExpr を生成する．
// @param[in] loc ファイル上の位置
// @param[in] val 値
AstExpr*
AstMgr::new_bool_expr(const FileRegion& loc,
		      bool val)
{
  ++ mBoolExprNum;
  void* p = mAlloc.get_memory(sizeof(AstBoolExpr));
  return new (p) AstBoolExpr(loc, val);
}

// @brief 実数値を表す AstExpr を生成する．
// @param[in] loc ファイル乗の位置
// @param[in] val 値
AstExpr*
AstMgr::new_float_expr(const FileRegion& loc,
		       double val)
{
  ++ mFloatExprNum;
  void* p = mAlloc.get_memory(sizeof(AstFloatExpr));
  return new (p) AstFloatExpr(loc, val);
}

// @brief VDDを表す AstExpr を生成する．
// @param[in] loc ファイル上の位置
AstExpr*
AstMgr::new_vdd_expr(const FileRegion& loc)
{
  ++ mSymbolExprNum;
  void* p = mAlloc.get_memory(sizeof(AstSymbolExpr));
  return new (p) AstSymbolExpr(loc, AstExprType::VDD);
}

// @brief VSSを表す AstExpr を生成する．
// @param[in] loc ファイル上の位置
AstExpr*
AstMgr::new_vss_expr(const FileRegion& loc)
{
  ++ mSymbolExprNum;
  void* p = mAlloc.get_memory(sizeof(AstSymbolExpr));
  return new (p) AstSymbolExpr(loc, AstExprType::VSS);
}

// @brief VCCを表す AstExpr を生成する．
// @param[in] loc ファイル上の位置
AstExpr*
AstMgr::new_vcc_expr(const FileRegion& loc)
{
  ++ mSymbolExprNum;
  void* p = mAlloc.get_memory(sizeof(AstSymbolExpr));
  return new (p) AstSymbolExpr(loc, AstExprType::VCC);
}

// @brief 文字列を表す AstExpr を生成する．
AstExpr*
AstMgr::new_str_expr(const FileRegion& loc,
		     const ShString& str)
{
  ++ mStrExprNum;
  void* p = mAlloc.get_memory(sizeof(AstStrExpr));
  return new (p) AstStrExpr(loc, str);
}


//////////////////////////////////////////////////////////////////////
// クラス AstExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
AstExpr::AstExpr(const FileRegion& loc) :
  AstNode(loc)
{
}

// @brief デストラクタ
AstExpr::~AstExpr()
{
}

// @brief 二項演算子型(Plus, Minus, Mult, Div)の時に true を返す．
bool
AstExpr::is_opr() const
{
  return false;
}

// @brief ブール値を返す．
//
// Bool の時のみ意味を持つ．
bool
AstExpr::bool_value() const
{
  ASSERT_NOT_REACHED;

  return false;
}

// @brief 浮動小数点値を返す．
//
// Float の時のみ意味を持つ．
double
AstExpr::float_value() const
{
  ASSERT_NOT_REACHED;

  return 0.0;
}

// @brief 文字列シンボルを返す．
//
// Str の時のみ意味を持つ．
ShString
AstExpr::string_value() const
{
  ASSERT_NOT_REACHED;

  return ShString();
}

// @brief 第一オペランドを返す．
//
// Not, Plus, Minus, Mult, Div の時のみ意味を持つ．
const AstExpr*
AstExpr::opr1() const
{
  ASSERT_NOT_REACHED;

  return nullptr;
}

// @brief 第二オペランドを返す．
//
// Plus, Minus, Mult, Div の時のみ意味を持つ．
const AstExpr*
AstExpr::opr2() const
{
  ASSERT_NOT_REACHED;

  return nullptr;
}


//////////////////////////////////////////////////////////////////////
// クラス AstBoolExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] val 値
AstBoolExpr::AstBoolExpr(const FileRegion& loc,
			 bool val) :
  AstExpr(loc),
  mValue(val)
{
}

// @brief デストラクタ
AstBoolExpr::~AstBoolExpr()
{
}

// @brief 型を返す．
AstExprType
AstBoolExpr::type() const
{
  return Type::Bool;
}

// @brief ブール値を返す．
//
// Bool の時のみ意味を持つ．
bool
AstBoolExpr::bool_value() const
{
  return mValue;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
AstBoolExpr::to_expr(const HashMap<ShString, int>& pin_map) const
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
AstBoolExpr::dump(ostream& s,
		  int indent) const
{
}


//////////////////////////////////////////////////////////////////////
// クラス AstFlotExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] val 値
AstFloatExpr::AstFloatExpr(const FileRegion& loc,
			   double val) :
  AstExpr(loc),
  mValue(val)
{
}

// @brief デストラクタ
AstFloatExpr::~AstFloatExpr()
{
}

// @brief 型を返す．
AstExprType
AstFloatExpr::type() const
{
  return Type::Float;
}

// @brief 浮動小数点値を返す．
//
// Float の時のみ意味を持つ．
double
AstFloatExpr::float_value() const
{
  return mValue;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
AstFloatExpr::to_expr(const HashMap<ShString, int>& pin_map) const
{
  ASSERT_NOT_REACHED;
  return Expr();
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstFloatExpr::dump(ostream& s,
		   int indent) const
{
}


//////////////////////////////////////////////////////////////////////
// クラス AstStrExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc 位置情報
// @param[in] val 値
AstStrExpr::AstStrExpr(const FileRegion& loc,
		       const ShString& val) :
  AstExpr(loc),
  mValue(val)
{
}

// @brief デストラクタ
AstStrExpr::~AstStrExpr()
{
}

// @brief 型を返す．
AstExprType
AstStrExpr::type() const
{
  return Type::Str;
}

// @brief 文字列値を返す．
//
// Str の時のみ意味を持つ．
ShString
AstStrExpr::string_value() const
{
  return mValue;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
AstStrExpr::to_expr(const HashMap<ShString, int>& pin_map) const
{
  int id;
  if ( !pin_map.find(mValue, id) ) {
    ostringstream buf;
    buf << mValue << ": No such pin-name.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
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
AstStrExpr::dump(ostream& s,
		 int indent) const
{
}


//////////////////////////////////////////////////////////////////////
// クラス AstSymbolExpr
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] type シンボルの種類(VDD, VSS, VCC)
AstSymbolExpr::AstSymbolExpr(const FileRegion& loc,
			     Type type) :
  AstExpr(loc),
  mType(type)
{
}

// @brief デストラクタ
AstSymbolExpr::~AstSymbolExpr()
{
}

// @brief 型を返す．
AstExprType
AstSymbolExpr::type() const
{
  return mType;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
AstSymbolExpr::to_expr(const HashMap<ShString, int>& pin_map) const
{
  ASSERT_NOT_REACHED;
  return Expr();
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstSymbolExpr::dump(ostream& s,
		    int indent) const
{
#warning "TODO: 未完成"
}


//////////////////////////////////////////////////////////////////////
// クラス AstNot
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] opr オペランド
AstNot::AstNot(const FileRegion& loc,
	       const AstExpr* opr) :
  AstExpr(loc),
  mOpr1(opr)
{
}

// @brief デストラクタ
AstNot::~AstNot()
{
}

// @brief 型を得る．
AstExprType
AstNot::type() const
{
  return Type::Not;
}

// @brief 第一オペランドを返す．
// @note type() が演算子の型の時のみ意味を持つ．
const AstExpr*
AstNot::opr1() const
{
  return mOpr1;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
AstNot::to_expr(const HashMap<ShString, int>& pin_map) const
{
  Expr expr1 = opr1()->to_expr(pin_map);
  return ~expr1;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstNot::dump(ostream& s,
	     int indent) const
{
  dump_indent(s, indent);
  s << "!( ";
  opr1()->dump(s, 0);
  s << " )";
}


//////////////////////////////////////////////////////////////////////
// クラス AstOpr
//////////////////////////////////////////////////////////////////////

// @brief 表すコンストラクタ
// @param[in] type 演算子の型
// @param[in] opr1, opr2 オペランド
AstOpr::AstOpr(Type type,
	       const AstExpr* opr1,
	       const AstExpr* opr2) :
  AstExpr(FileRegion(opr1->loc(), opr2->loc())),
  mType(type),
  mOpr1(opr1),
  mOpr2(opr2)
{
}

// @brief デストラクタ
AstOpr::~AstOpr()
{
}

// @brief 型を得る．
AstExprType
AstOpr::type() const
{
  return mType;
}

// @brief 演算子型(Plus, Minsu, Mult, Div)の時に true を返す．
bool
AstOpr::is_opr() const
{
  return true;
}

// @brief 第一オペランドを返す．
// @note type() が演算子の型の時のみ意味を持つ．
const AstExpr*
AstOpr::opr1() const
{
  return mOpr1;
}

// @brief 第二オペランドを返す．
// @note type() が演算子の型の時のみ意味を持つ．
const AstExpr*
AstOpr::opr2() const
{
  return mOpr2;
}

// @brief Expr を作る．
// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
// @return 対応する式(Expr)を返す．
Expr
AstOpr::to_expr(const HashMap<ShString, int>& pin_map) const
{
  Expr expr1 = opr1()->to_expr(pin_map);
  Expr expr2 = opr2()->to_expr(pin_map);
  switch ( type() ) {
  case Type::And: return expr1 & expr2;
  case Type::Or:  return expr1 | expr2;
  case Type::Xor: return expr1 ^ expr2;
  default: break;
  }
  ASSERT_NOT_REACHED;
  return Expr();
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstOpr::dump(ostream& s,
		int indent) const
{
  dump_indent(s, indent);
  s << "( ";
  opr1()->dump(s, 0);
  switch ( type() ) {
  case Type::Plus:  s << " + "; break;
  case Type::Minus: s << " - "; break;
  case Type::Mult:  s << " * "; break;
  case Type::Div:   s << " / "; break;
  case Type::And:   s << " & "; break;
  case Type::Or:    s << " | "; break;
  case Type::Xor:   s << " ^ "; break;
  default:           ASSERT_NOT_REACHED; break;
  }
  opr2()->dump(s, 0);
  s << " )";
}

END_NAMESPACE_YM_DOTLIB
