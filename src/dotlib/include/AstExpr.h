#ifndef ASTEXPR_H
#define ASTEXPR_H

/// @file AstExpr.h
/// @brief AstExpr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "AstNode.h"
#include "ym/Expr.h"


BEGIN_NAMESPACE_YM_DOTLIB

/// @brief 型を表す列挙型
enum class AstExprType {
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


//////////////////////////////////////////////////////////////////////
/// @class AstExpr AstExpr.h "AstExpr.h"
/// @brief 式を表すノードのクラス
//////////////////////////////////////////////////////////////////////
class AstExpr :
  public AstNode
{
  friend class AstMgr;

public:

  using Type = AstExprType;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  AstExpr(const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~AstExpr();


public:
  //////////////////////////////////////////////////////////////////////
  // AstExpr の仮想関数
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
  const AstExpr*
  opr1() const;

  /// @brief 第二オペランドを返す．
  ///
  /// kPlus, kMinus, kMult, kDiv, kAnd, kOr, kXor の時のみ意味を持つ．
  virtual
  const AstExpr*
  opr2() const;

  /// @brief Expr を作る．
  /// @param[in] pin_map ピン名をキーにしてピン番号を保持するハッシュ表
  /// @return 対応する式(Expr)を返す．
  virtual
  Expr
  to_expr(const HashMap<ShString, int>& pin_map) const = 0;

};


//////////////////////////////////////////////////////////////////////
/// @class AstBoolExpr AstExpr.h "AstExpr.h"
/// @brief ブール値を表す AstExpr
//////////////////////////////////////////////////////////////////////
class AstBoolExpr :
  public AstExpr
{
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] val 値
  AstBoolExpr(const FileRegion& loc,
	      bool val);

  /// @brief デストラクタ
  virtual
  ~AstBoolExpr();


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
/// @class AstFloatExpr AstExpr.h "AstExpr.h"
/// @brief 浮動小数点値を表す AstExpr
//////////////////////////////////////////////////////////////////////
class AstFloatExpr :
  public AstExpr
{
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] val 値
  AstFloatExpr(const FileRegion& loc,
	       double val);

  /// @brief デストラクタ
  virtual
  ~AstFloatExpr();


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
/// @class AstStrExpr AstExpr.h "AstExpr.h"
/// @brief 文字列値を表す AstExpr
//////////////////////////////////////////////////////////////////////
class AstStrExpr :
  public AstExpr
{
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc 位置情報
  /// @param[in] val 値
  AstStrExpr(const FileRegion& loc,
	     const ShString& val);

  /// @brief デストラクタ
  virtual
  ~AstStrExpr();


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
/// @class AstSymbolExpr AstExpr.h "AstExpr.h"
//////////////////////////////////////////////////////////////////////
class AstSymbolExpr :
  public AstExpr
{
  friend class AstMgr;

protected:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] type シンボルの種類(kVDD, kVSS, kVCC)
  AstSymbolExpr(const FileRegion& loc,
		Type type);

  /// @brief デストラクタ
  virtual
  ~AstSymbolExpr();


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
/// @class AstNot AstExpr.h "AstExpr.h"
/// @brief NOT 演算子を表すクラス
//////////////////////////////////////////////////////////////////////
class AstNot :
  public AstExpr
{
  friend class AstMgr;

private:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  /// @param[in] opr オペランド
  AstNot(const FileRegion& loc,
	 const AstExpr* opr);

  /// @brief デストラクタ
  virtual
  ~AstNot();


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
  const AstExpr*
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
  const AstExpr* mOpr1;

};


//////////////////////////////////////////////////////////////////////
/// @class AstOpr AstExpr.h "AstExpr.h"
/// @brief 演算子を表すクラス
//////////////////////////////////////////////////////////////////////
class AstOpr :
  public AstExpr
{
  friend class AstMgr;

private:

  /// @brief コンストラクタ
  /// @param[in] type 演算子の型
  /// @param[in] opr1, opr2 オペランド
  AstOpr(Type type,
	 const AstExpr* opr1,
	 const AstExpr* opr2);

  /// @brief デストラクタ
  virtual
  ~AstOpr();


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
  const AstExpr*
  opr1() const;

  /// @brief 第二オペランドを返す．
  /// @note type() が演算子の型の時のみ意味を持つ．
  virtual
  const AstExpr*
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
  const AstExpr* mOpr1;

  // 第二オペランド
  const AstExpr* mOpr2;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTEXPR_H
