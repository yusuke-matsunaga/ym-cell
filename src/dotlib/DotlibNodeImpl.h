#ifndef DOTLIBNODEIMPL_H
#define DOTLIBNODEIMPL_H

/// @file DotlibNodeImpl.h
/// @brief DotlibNode の継承クラスのヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNode.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class DotlibNodeImpl DotlibNodeImple.h "DotlibNodeImpl.h"
/// @brief DotlibNode の実装クラス
//////////////////////////////////////////////////////////////////////
class DotlibNodeImpl :
  public DotlibNode
{
  friend class DotlibList;
  friend class DotlibGroup;

protected:

  /// @brief コンストラクタ
  DotlibNodeImpl();

  /// @brief デストラクタ
  virtual
  ~DotlibNodeImpl();


public:
  //////////////////////////////////////////////////////////////////////
  // DotlibNode の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 整数型(kInt)の時に true を返す．
  virtual
  bool
  is_int() const;

  /// @brief 数値型(kInt か kFloat)の時に true を返す．
  virtual
  bool
  is_float() const;

  /// @brief 文字列型(kString)の時に true を返す．
  virtual
  bool
  is_string() const;

  /// @brief ベクタ型(kVector)の時に true を返す．
  virtual
  bool
  is_vector() const;

  /// @brief 演算子型(kPlus, kMinsu, kMult, kDiv)の時に true を返す．
  virtual
  bool
  is_opr() const;

  /// @brief リスト型(kList)の時に true を返す．
  virtual
  bool
  is_list() const;

  /// @brief グループ型(kGroup)の時に true を返す．
  virtual
  bool
  is_group() const;

  /// @brief 整数値を返す．
  /// @note is_int() = true の時のみ意味を持つ．
  virtual
  int
  int_value() const;

  /// @brief 数値を返す．
  /// @note is_float() = true の時のみ意味を持つ．
  virtual
  double
  float_value() const;

  /// @brief 文字列シンボルを返す．
  /// @note is_string() = true の時のみ意味を持つ．
  virtual
  ShString
  string_value() const;

  /// @brief ベクタの要素数を返す．
  /// @note is_vector() = true の時のみ意味を持つ．
  virtual
  int
  vector_size() const;

  /// @brief ベクタの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < vector_size() )
  /// @note is_vector() = true の時のみ意味を持つ．
  virtual
  double
  vector_elem(int pos) const;

  /// @brief ベクタの全体を取り出す．
  /// @param[out] vector 結果を格納する変数
  /// @note is_vector() = true の時のみ意味を持つ．
  virtual
  void
  get_vector(vector<double>& vector) const;

  /// @brief 第一オペランドを返す．
  /// @note is_opr() = true の時のみ意味を持つ．
  virtual
  const DotlibNode*
  opr1() const;

  /// @brief 第二オペランドを返す．
  /// @note is_opr() = true の時のみ意味を持つ．
  virtual
  const DotlibNode*
  opr2() const;

  /// @brief リストの要素数を返す．
  /// @note is_list() = true の時のみ意味を持つ．
  virtual
  int
  list_size() const;

  /// @brief リストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < list_size() )
  /// @note is_list() == true の時のみ意味を持つ．
  virtual
  const DotlibNode*
  list_elem(int pos) const;

  /// @brief グループの値を得る．
  /// @note is_group() = true の時のみ意味を持つ．
  virtual
  const DotlibNode*
  group_value() const;

  /// @brief 先頭の属性を得る．
  /// @note is_group() = true の時のみ意味を持つ．
  virtual
  const DotlibAttr*
  attr_top() const;

  /// @brief Technology を返す．
  ///
  /// type() == kTechnology の時のみ意味を持つ．
  virtual
  ClibTechnology
  technology() const;

  /// @brief DelayModel を返す．
  ///
  /// type() == kDelayModel の時のみ意味を持つ．
  virtual
  ClibDelayModel
  delay_model() const;

  /// @brief CellPinDirection を返す．
  ///
  /// type() == kCellPinDirection の時のみ意味を持つ．
  virtual
  ClibCellPinDirection
  cell_pin_direction() const;

  /// @brief TimingSense を返す．
  ///
  /// type() == kTimingSense の時のみ意味を持つ．
  virtual
  ClibTimingSense
  timing_sense() const;

  /// @brief TimingType を返す．
  ///
  /// type() == kTimingType の時のみ意味を持つ．
  virtual
  ClibTimingType
  timing_type() const;

  /// @brief VarType を返す．
  ///
  /// type() == kVarType の時のみ意味を持つ．
  virtual
  ClibVarType
  var_type() const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素を追加する．
  /// @param[in] node 追加する要素
  /// @note is_list() = true の時のみ意味を持つ．
  virtual
  void
  add_node(DotlibNodeImpl* node);

  /// @brief attribute を設定する．
  /// @param[in] attr 属性
  /// @note is_group() = true の時のみ意味を持つ．
  virtual
  void
  add_attr(DotlibAttr* attr);

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibNodeBase DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief 直接値を表すクラスの基底クラス
//////////////////////////////////////////////////////////////////////
class DotlibNodeBase :
  public DotlibNodeImpl
{
protected:

  /// @brief コンストラクタ
  /// @param[in] loc ファイル上の位置
  DotlibNodeBase(const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibNodeBase();


public:

  /// @brief ファイル上の位置を返す．
  virtual
  FileRegion
  loc() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ファイル上の位置
  FileRegion mLoc;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibInt DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief 整数値を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibInt :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibInt(int value,
	    const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibInt();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief 整数型(kInt)の時に true を返す．
  virtual
  bool
  is_int() const;

  /// @brief 数値型(kInt か kFloat)の時に true を返す．
  virtual
  bool
  is_float() const;

  /// @brief 整数値を返す．
  /// @note type() が kInt の時のみ意味を持つ．
  virtual
  int
  int_value() const;

  /// @brief 数値を返す．
  /// @note type() が kFloat の時のみ意味を持つ．
  /// @note 実は kInt でもOK
  virtual
  double
  float_value() const;

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

  // 値
  int mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibFloat DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief 実数値を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibFloat :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibFloat(double value,
	      const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibFloat();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief 数値型(kInt か kFloat)の時に true を返す．
  virtual
  bool
  is_float() const;

  /// @brief 数値を返す．
  /// @note type() が kFloat の時のみ意味を持つ．
  virtual
  double
  float_value() const;

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

  // 値
  double mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibString DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief 文字列を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibString :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibString(ShString value,
	       const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibString();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief 文字列型(kString)の時に true を返す．
  virtual
  bool
  is_string() const;

  /// @brief 定数シンボルを返す．
  /// @note type() が kString の時のみ意味を持つ．
  virtual
  ShString
  string_value() const;

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

  // 値
  ShString mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibVector DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief ベクタを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibVector :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value_list 値のリスト
  /// @param[in] loc ファイル上の位置
  DotlibVector(const vector<double>& value_list,
	       const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibVector();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief ベクタ型(kVector)の時に true を返す．
  virtual
  bool
  is_vector() const;

  /// @brief ベクタの要素数を返す．
  /// @note is_vector() = true の時のみ意味を持つ．
  virtual
  int
  vector_size() const;

  /// @brief ベクタの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < vector_size() )
  /// @note is_vector() = true の時のみ意味を持つ．
  virtual
  double
  vector_elem(int pos) const;

  /// @brief ベクタの全体を取り出す．
  /// @param[out] vector 結果を格納する変数
  /// @note is_vector() = true の時のみ意味を持つ．
  virtual
  void
  get_vector(vector<double>& vector) const;

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

  // 要素数
  int mNum;

  // ベクタの本体
  double mBody[1];

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibNot DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief NOT 演算子を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibNot :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] opr オペランド
  /// @param[in] loc ファイル上の位置
  DotlibNot(const DotlibNode* opr,
	    const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~DotlibNot();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief 演算子型(kPlus, kMinsu, kMult, kDiv)の時に true を返す．
  virtual
  bool
  is_opr() const;

  /// @brief 第一オペランドを返す．
  /// @note type() が演算子の型の時のみ意味を持つ．
  virtual
  const DotlibNode*
  opr1() const;

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
  const DotlibNode* mOpr1;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibOpr DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief 演算子を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibOpr :
  public DotlibNodeImpl
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] type 演算子の型
  /// @param[in] opr1, opr2 オペランド
  DotlibOpr(Type type,
	    const DotlibNode* opr1,
	    const DotlibNode* opr2);

  /// @brief デストラクタ
  virtual
  ~DotlibOpr();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief 演算子型(kPlus, kMinsu, kMult, kDiv)の時に true を返す．
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
  const DotlibNode*
  opr1() const;

  /// @brief 第二オペランドを返す．
  /// @note type() が演算子の型の時のみ意味を持つ．
  virtual
  const DotlibNode*
  opr2() const;

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
  const DotlibNode* mOpr1;

  // 第二オペランド
  const DotlibNode* mOpr2;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibList DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief リストを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibList :
  public DotlibNodeImpl
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  DotlibList();

  /// @brief デストラクタ
  virtual
  ~DotlibList();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief リスト型(kList)の時に true を返す．
  virtual
  bool
  is_list() const;

  /// @brief ファイル上の位置を返す．
  virtual
  FileRegion
  loc() const;

  /// @brief リストの要素数を返す．
  /// @note is_list() = true の時のみ意味を持つ．
  virtual
  int
  list_size() const;

  /// @brief リストの要素を返す．
  /// @param[in] pos 位置番号 ( 0 <= pos < list_size() )
  /// @note is_list() == true の時のみ意味を持つ．
  virtual
  const DotlibNode*
  list_elem(int pos) const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 要素を追加する．
  /// @param[in] node 追加する要素
  /// @note type() が kList の時のみ意味を持つ．
  virtual
  void
  add_node(DotlibNodeImpl* node);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 要素
  vector<const DotlibNodeImpl*> mBody;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibGroup DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief group statement を表す DotlibNode の継承クラス
//////////////////////////////////////////////////////////////////////
class DotlibGroup :
  public DotlibNodeBase
{
public:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibGroup(const DotlibNode* value,
	      const FileRegion& loc);

  /// @brief デストラクタ
  virtual
  ~DotlibGroup();


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を参照する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief グループ型(kGroup)の時に true を返す．
  virtual
  bool
  is_group() const;

  /// @brief グループの値を得る．
  /// @note type() が kGroup の時のみ意味を持つ．
  virtual
  const DotlibNode*
  group_value() const;

  /// @brief 先頭の属性を得る．
  /// @note type() が kGroup の時のみ意味を持つ．
  virtual
  const DotlibAttr*
  attr_top() const;

  /// @brief 内容をストリーム出力する．
  /// @param[in] s 出力先のストリーム
  /// @param[in] indent インデント量
  virtual
  void
  dump(ostream& s,
       int indent = 0) const;


public:
  //////////////////////////////////////////////////////////////////////
  // 内容を設定する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief attribute を設定する．
  /// @param[in] attr 属性
  /// @note type() が kGroup の時のみ意味を持つ．
  virtual
  void
  add_attr(DotlibAttr* attr);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 値
  const DotlibNode* mValue;

  // 属性の先頭
  DotlibAttr* mAttrTop;

  // 属性の末尾
  DotlibAttr* mAttrTail;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibTechnology DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief technologyを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTechnology :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibTechnology(ClibTechnology value,
		   const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibTechnology();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief Technology を返す．
  ///
  /// type() == kTechnology の時のみ意味を持つ．
  virtual
  ClibTechnology
  technology() const;

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

  // 値
  ClibTechnology mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibDelayModel DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief delay modelを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibDelayModel :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibDelayModel(ClibDelayModel value,
		   const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibDelayModel();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief DelayModel を返す．
  ///
  /// type() == kDelayModel の時のみ意味を持つ．
  virtual
  ClibDelayModel
  delay_model() const;

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

  // 値
  ClibDelayModel mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibCellPinDirection DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief cell pin directionを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibCellPinDirection :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibCellPinDirection(ClibCellPinDirection value,
			 const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibCellPinDirection();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief CellPinDirection を返す．
  ///
  /// type() == kCellPinDirection の時のみ意味を持つ．
  virtual
  ClibCellPinDirection
  cell_pin_direction() const;

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

  // 値
  ClibCellPinDirection mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibTimingSense DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief timing sense を表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTimingSense :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibTimingSense(ClibTimingSense value,
		    const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibTimingSense();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief TimingSense を返す．
  ///
  /// type() == kTimingSense の時のみ意味を持つ．
  virtual
  ClibTimingSense
  timing_sense() const;

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

  // 値
  ClibTimingSense mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibTimingType DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief timing typeを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibTimingType :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibTimingType(ClibTimingType value,
		   const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibTimingType();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief TimingType を返す．
  ///
  /// type() == kTimingType の時のみ意味を持つ．
  virtual
  ClibTimingType
  timing_type() const;

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

  // 値
  ClibTimingType mValue;

};


//////////////////////////////////////////////////////////////////////
/// @class DotlibVarType DotlibNodeImpl.h "DotlibNodeImpl.h"
/// @brief var typeを表すクラス
//////////////////////////////////////////////////////////////////////
class DotlibVarType :
  public DotlibNodeBase
{
  friend class DotlibMgrImpl;

private:

  /// @brief コンストラクタ
  /// @param[in] value 値
  /// @param[in] loc ファイル上の位置
  DotlibVarType(ClibVarType value,
		   const FileRegion& loc);

  /// @brief デストラクタ
  ~DotlibVarType();


public:

  /// @brief 型を得る．
  virtual
  Type
  type() const;

  /// @brief VarType を返す．
  ///
  /// type() == kVarType の時のみ意味を持つ．
  virtual
  ClibVarType
  var_type() const;

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

  // 値
  ClibVarType mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // DOTLIBNODEIMPL_H
