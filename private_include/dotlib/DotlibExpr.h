#ifndef DOTLIBEXPR_H
#define DOTLIBEXPR_H

/// @file DotlibExpr.h
/// @brief DotlibExpr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibExpr DotlibExpr.h "DotlibExpr.h"
/// @brief 式を表すノードのクラス
//////////////////////////////////////////////////////////////////////
class DotlibExpr :
  public DotlibNode
{
public:

  /// @brief 型を表す列挙型
  enum Type {
    kBool,
    kFloat,
    kStr,
    kVDD,
    kVSS,
    kVCC,
    kNot,
    kPlus,
    kMinus,
    kMult,
    kDiv,
    kAnd,
    kOr,
    kXor,
  };


protected:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  DotlibExpr(const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~DotlibExpr();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibExpr の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 型を返す．
  virtual
  Type
  type() const = 0;

  /// @brief 二項演算子型(kPlus, kMinus, kMult, kDiv, kAnd, kOr, kXor)の時に true を返す．
  virtual
  bool
  is_opr() const;

  /// @brief ブール値を返す．
  ///
  /// kBool の時のみ意味を持つ．
  virtual
  bool
  bool_value() const;

  /// @brief 文字列シンボルを返す．
  ///
  /// kStr の時のみ意味を持つ．
  virtual
  ShString
  string_value() const;

  /// @brief 第一オペランドを返す．
  ///
  /// kNot, kPlus, kMinus, kMult, kDiv, kAnd, kOr, kXor の時のみ意味を持つ．
  virtual
  const DotlibExpr*
  opr1() const;

  /// @brief 第二オペランドを返す．
  ///
  /// kPlus, kMinus, kMult, kDiv, kAnd, kOr, kXor の時のみ意味を持つ．
  virtual
  const DotlibExpr*
  opr2() const;

  /// @brief Expr を作る．
  /// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
  /// @return 対応する式(Expr)を返す．
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& pin_map) const = 0;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibBoolExpr DotlibExpr.h "DotlibExpr.h"
/// @brief ブール値を表す DotlibExpr
//////////////////////////////////////////////////////////////////////
class DotlibBoolExpr :
  public DotlibExpr
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] val 値
  DotlibBoolExpr(const FileRegion& loc,
		 bool val);

  /// @brief デストラクタ
  virtual
  ~DotlibBoolExpr();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 型を返す．
  virtual
  Type
  type() const;

  /// @brief ブール値を返す．
  ///
  /// kBool の時のみ意味を持つ．
  virtual
  bool
  bool_value() const;

  /// @brief Expr を作る．
  /// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
  /// @return 対応する式(Expr)を返す．
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& pin_map) const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  bool mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibFloatExpr DotlibExpr.h "DotlibExpr.h"
/// @brief 浮動小数点値を表す DotlibExpr
//////////////////////////////////////////////////////////////////////
class DotlibFloatExpr :
  public DotlibExpr
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] val 値
  DotlibFloatExpr(const FileRegion& loc,
		  double val);

  /// @brief デストラクタ
  virtual
  ~DotlibFloatExpr();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 型を返す．
  virtual
  Type
  type() const;

  /// @brief 浮動小数点値を返す．
  ///
  /// kFloat の時のみ意味を持つ．
  virtual
  double
  float_value() const;

  /// @brief Expr を作る．
  /// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
  /// @return 対応する式(Expr)を返す．
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& pin_map) const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  double mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibStrExpr DotlibExpr.h "DotlibExpr.h"
/// @brief 文字列値を表す DotlibExpr
//////////////////////////////////////////////////////////////////////
class DotlibStrExpr :
  public DotlibExpr
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] val 値
  DotlibStrExpr(const FileRegion& loc,
		const ShString& val);

  /// @brief デストラクタ
  virtual
  ~DotlibStrExpr();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 型を返す．
  virtual
  Type
  type() const;

  /// @brief 文字列値を返す．
  ///
  /// kStr の時のみ意味を持つ．
  virtual
  ShString
  string_value() const;

  /// @brief Expr を作る．
  /// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
  /// @return 対応する式(Expr)を返す．
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& pin_map) const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  ShString mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibSymbolExpr DotlibExpr.h "DotlibExpr.h"
//////////////////////////////////////////////////////////////////////
class DotlibSymbolExpr :
  public DotlibExpr
{
public:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] type シンボルの種類(kVDD, kVSS, kVCC)
  DotlibSymbolExpr(const FileRegion& loc,
		   Type type);

  /// @brief デストラクタ
  virtual
  ~DotlibSymbolExpr();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 型を返す．
  virtual
  Type
  type() const;

  /// @brief Expr を作る．
  /// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
  /// @return 対応する式(Expr)を返す．
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& pin_map) const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 型
  Type mType;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibNot DotlibExpr.h "DotlibExpr.h"
/// @brief NOT 演算子を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibNot :
  public DotlibExpr
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] opr オペランド
  DotlibNot(const FileRegion& loc,
	    const DotlibExpr* opr);

  /// @brief デストラクタ
  virtual
  ~DotlibNot();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief 第一オペランドを返す．
  /// @note type() が演算子の型の時のみ意味を持つ．
  virtual
  const DotlibExpr*
  opr1() const;

  /// @brief Expr を作る．
  /// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
  /// @return 対応する式(Expr)を返す．
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& pin_map) const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 第一オペランド
  const DotlibExpr* mOpr1;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibOpr DotlibExpr.h "DotlibExpr.h"
/// @brief 演算子を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibOpr :
  public DotlibExpr
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] type 演算子の型
  /// @param[in] opr1, opr2 オペランド
  DotlibOpr(Type type,
	    const DotlibExpr* opr1,
	    const DotlibExpr* opr2);

  /// @brief デストラクタ
  virtual
  ~DotlibOpr();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief 演算子型(kPlus, kMinsu, kMult, kDiv, kAnd, kOr, kXor)の時に true を返す．
  virtual
  bool
  is_opr() const;

  /// @brief ファイル上の位置を返す．
  virtual
  FileRegion
  loc() const;

  /// @brief 第一オペランドを返す．
  /// @note type() が演算子の型の時のみ意味を持つ．
  virtual
  const DotlibExpr*
  opr1() const;

  /// @brief 第二オペランドを返す．
  /// @note type() が演算子の型の時のみ意味を持つ．
  virtual
  const DotlibExpr*
  opr2() const;

  /// @brief Expr を作る．
  /// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
  /// @return 対応する式(Expr)を返す．
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& pin_map) const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 型
  Type mType;

  // 第一オペランド
  const DotlibExpr* mOpr1;

  // 第二オペランド
  const DotlibExpr* mOpr2;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBNODEIMPL_H
