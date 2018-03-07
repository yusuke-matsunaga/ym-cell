﻿
/// @file DotlibNodeImpl.cc
/// @brief DotlibNode の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "DotlibNodeImpl.h"
#include "DotlibAttr.h"


BEGIN_NAMESPACE_YM_DOTLIB

BEGIN_NONAMESPACE

// インデント用の空白文字列を作る．
string
indent_str(int indent)
{
  string ans;
  for (int i = 0; i < indent; ++ i) {
    ans += ' ';
  }
  return ans;
}

// str 中に [a-zA-Z0-9_] 以外の文字が含まれていたら
// " " で囲んで出力する．
void
dump_str(ostream& s,
	 const char* str)
{
  bool need_quote = false;
  for (const char* p = str; *p; ++ p) {
    int c = *p;
    if ( !isalnum(c) && c != '_' ) {
      need_quote = true;
      break;
    }
  }
  if ( need_quote ) {
    s << "\"";
  }
  s << str;
  if ( need_quote ) {
    s << "\"";
  }
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス DotlibNodeImpl
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibNodeImpl::DotlibNodeImpl()
{
}

// @brief デストラクタ
DotlibNodeImpl::~DotlibNodeImpl()
{
}

// @brief 整数型(kInt)の時に true を返す．
bool
DotlibNodeImpl::is_int() const
{
  return false;
}

// @brief 数値型(kInt か kFloat)の時に true を返す．
bool
DotlibNodeImpl::is_float() const
{
  return false;
}

// @brief 文字列型(kString)の時に true を返す．
bool
DotlibNodeImpl::is_string() const
{
  return false;
}

// @brief ベクタ型(kVector)の時に true を返す．
bool
DotlibNodeImpl::is_vector() const
{
  return false;
}

// @brief 演算子型(kPlus, kMinsu, kMult, kDiv)の時に true を返す．
bool
DotlibNodeImpl::is_opr() const
{
  return false;
}

// @brief リスト型(kList)の時に true を返す．
bool
DotlibNodeImpl::is_list() const
{
  return false;
}

// @brief グループ型(kGroup)の時に true を返す．
bool
DotlibNodeImpl::is_group() const
{
  return false;
}

// @brief 整数値を返す．
// @note is_int() = true の時のみ意味を持つ．
int
DotlibNodeImpl::int_value() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return 0;
}

// @brief 数値を返す．
// @note is_float() = true の時のみ意味を持つ．
double
DotlibNodeImpl::float_value() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return 0.0;
}

// @brief 定数シンボルを返す．
// @note is_string() = true の時のみ意味を持つ．
ShString
DotlibNodeImpl::string_value() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return ShString();
}

// @brief ベクタの要素数を返す．
// @note is_vector() = true の時のみ意味を持つ．
int
DotlibNodeImpl::vector_size() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return 0;
}

// @brief ベクタの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < vector_size() )
// @note is_vector() = true の時のみ意味を持つ．
double
DotlibNodeImpl::vector_elem(int pos) const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return 0.0;
}

// @brief ベクタの全体を取り出す．
// @param[out] vector 結果を格納する変数
// @note is_vector() = true の時のみ意味を持つ．
void
DotlibNodeImpl::get_vector(vector<double>& vector) const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
}

// @brief 第一オペランドを返す．
// @note is_opr() = true の時のみ意味を持つ．
const DotlibNode*
DotlibNodeImpl::opr1() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return nullptr;
}

// @brief 第二オペランドを返す．
// @note is_opr() = true の時のみ意味を持つ．
const DotlibNode*
DotlibNodeImpl::opr2() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return nullptr;
}

// @brief リストの要素数を返す．
// @note is_list() = true の時のみ意味を持つ．
int
DotlibNodeImpl::list_size() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return 0;
}

// @brief リストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < list_size() )
// @note is_list() == true の時のみ意味を持つ．
const DotlibNode*
DotlibNodeImpl::list_elem(int pos) const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return nullptr;
}

// @brief グループの値を得る．
// @note is_group() = true の時のみ意味を持つ．
const DotlibNode*
DotlibNodeImpl::group_value() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return nullptr;
}

// @brief 先頭の属性を得る．
// @note is_group() = true の時のみ意味を持つ．
const DotlibAttr*
DotlibNodeImpl::attr_top() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return nullptr;
}

// @brief 要素を追加する．
// @param[in] node 追加する要素
// @note type() が kList の時のみ意味を持つ．
void
DotlibNodeImpl::add_node(DotlibNodeImpl* node)
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
}

// @brief attribute を設定する．
// @param[in] attr 属性
// @note type() が kGroup の時のみ意味を持つ．
void
DotlibNodeImpl::add_attr(DotlibAttr* attr)
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
}

// @brief Technology を返す．
//
// type() == kTechnology の時のみ意味を持つ．
ClibTechnology
DotlibNodeImpl::technology() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return kClibTechCmos;
}

// @brief DelayModel を返す．
//
// type() == kDelayModel の時のみ意味を持つ．
ClibDelayModel
DotlibNodeImpl::delay_model() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return kClibDelayGenericCmos;
}

// @brief CellPinDirection を返す．
//
// type() == kCellPinDirection の時のみ意味を持つ．
ClibCellPinDirection
DotlibNodeImpl::cell_pin_direction() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return kClibCellPinInput;
}

// @brief TimingSense を返す．
//
// type() == kTimingSense の時のみ意味を持つ．
ClibTimingSense
DotlibNodeImpl::timing_sense() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return kClibPosiUnate;
}

// @brief TimingType を返す．
//
// type() == kTimingType の時のみ意味を持つ．
ClibTimingType
DotlibNodeImpl::timing_type() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return kClibTimingCombinational;
}

// @brief VarType を返す．
//
// type() == kVarType の時のみ意味を持つ．
ClibVarType
DotlibNodeImpl::var_type() const
{
  dump(cout);
  cout << endl;
  ASSERT_NOT_REACHED;
  return kClibVarNone;
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibNodeBase
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
DotlibNodeBase::DotlibNodeBase(const FileRegion& loc) :
  mLoc(loc)
{
}

// @brief デストラクタ
DotlibNodeBase::~DotlibNodeBase()
{
}

// @brief ファイル上の位置を返す．
FileRegion
DotlibNodeBase::loc() const
{
  return mLoc;
}


//////////////////////////////////////////////////////////////////////
/// クラス DotlibInt
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibInt::DotlibInt(int value,
		     const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibInt::~DotlibInt()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibInt::type() const
{
  return kInt;
}

// @brief 整数型(kInt)の時に true を返す．
bool
DotlibInt::is_int() const
{
  return true;
}

// @brief 数値型(kInt か kFloat)の時に true を返す．
bool
DotlibInt::is_float() const
{
  return true;
}

// @brief 整数値を返す．
// @note type() が kInt の時のみ意味を持つ．
int
DotlibInt::int_value() const
{
  return mValue;
}

// @brief 数値を返す．
// @note type() が kFloat の時のみ意味を持つ．
double
DotlibInt::float_value() const
{
  return static_cast<double>(mValue);
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibInt::dump(ostream& s,
		int indent) const
{
  s << int_value();
}


//////////////////////////////////////////////////////////////////////
/// クラス DotlibFloat
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibFloat::DotlibFloat(double value,
			 const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibFloat::~DotlibFloat()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibFloat::type() const
{
  return kFloat;
}

// @brief 数値型(kInt か kFloat)の時に true を返す．
bool
DotlibFloat::is_float() const
{
  return true;
}

// @brief 数値を返す．
// @note type() が kFloat の時のみ意味を持つ．
double
DotlibFloat::float_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibFloat::dump(ostream& s,
		  int indent) const
{
  s << float_value();
}


//////////////////////////////////////////////////////////////////////
/// クラス DotlibString
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibString::DotlibString(ShString value,
			   const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibString::~DotlibString()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibString::type() const
{
  return kString;
}

// @brief 文字列型(kString)の時に true を返す．
bool
DotlibString::is_string() const
{
  return true;
}

// @brief 定数シンボルを返す．
// @note type() が SYMBOL の時のみ意味を持つ．
ShString
DotlibString::string_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibString::dump(ostream& s,
		   int indent) const
{
  dump_str(s, string_value());
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value_list 値のリスト
// @param[in] loc ファイル上の位置
DotlibVector::DotlibVector(const vector<double>& value_list,
			   const FileRegion& loc) :
  DotlibNodeBase(loc),
  mNum(value_list.size())
{
  for (int i = 0; i < mNum; ++ i) {
    mBody[i] = value_list[i];
  }
}

// @brief デストラクタ
DotlibVector::~DotlibVector()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibVector::type() const
{
  return kVector;
}

// @brief ベクタ型(kVector)の時に true を返す．
bool
DotlibVector::is_vector() const
{
  return true;
}

// @brief ベクタの要素数を返す．
// @note is_vector() = true の時のみ意味を持つ．
int
DotlibVector::vector_size() const
{
  return mNum;
}

// @brief ベクタの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < vector_size() )
// @note is_vector() = true の時のみ意味を持つ．
double
DotlibVector::vector_elem(int pos) const
{
  return mBody[pos];
}

// @brief ベクタの全体を取り出す．
// @param[out] vector 結果を格納する変数
// @note is_vector() = true の時のみ意味を持つ．
void
DotlibVector::get_vector(vector<double>& vector) const
{
  vector.clear();
  vector.resize(mNum);
  for (int i = 0; i < mNum; ++ i) {
    vector[i] = mBody[i];
  }
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibVector::dump(ostream& s,
		   int indent) const
{
  const char* comma = "";
  s << "(";
  for (int i = 0; i < mNum; ++ i) {
    s << comma << mBody[i];
    comma = ", ";
  }
  s << ")";
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibNot
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] opr オペランド
// @param[in] loc ファイル上の位置
DotlibNot::DotlibNot(const DotlibNode* opr,
		     const FileRegion& loc) :
  DotlibNodeBase(loc),
  mOpr1(opr)
{
}

// @brief デストラクタ
DotlibNot::~DotlibNot()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibNot::type() const
{
  return kNot;
}

// @brief 演算子型(kPlus, kMinsu, kMult, kDiv)の時に true を返す．
bool
DotlibNot::is_opr() const
{
  return true;
}

// @brief 第一オペランドを返す．
// @note type() が演算子の型の時のみ意味を持つ．
const DotlibNode*
DotlibNot::opr1() const
{
  return mOpr1;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibNot::dump(ostream& s,
		int indent) const
{
  for (int i = 0; i < indent; ++ i) {
    s << ' ';
  }
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
		     const DotlibNode* opr1,
		     const DotlibNode* opr2) :
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
DotlibNode::Type
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
const DotlibNode*
DotlibOpr::opr1() const
{
  return mOpr1;
}

// @brief 第二オペランドを返す．
// @note type() が演算子の型の時のみ意味を持つ．
const DotlibNode*
DotlibOpr::opr2() const
{
  return mOpr2;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibOpr::dump(ostream& s,
		int indent) const
{
  for (int i = 0; i < indent; ++ i) {
    s << ' ';
  }
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
  default:
    ASSERT_NOT_REACHED;
  }
  opr2()->dump(s, 0);
  s << " )";
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibList
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
DotlibList::DotlibList()
{
}

// @brief デストラクタ
DotlibList::~DotlibList()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibList::type() const
{
  return kList;
}

// @brief リスト型(kList)の時に true を返す．
bool
DotlibList::is_list() const
{
  return true;
}

// @brief 式全体のファイル上の位置を返す．
FileRegion
DotlibList::loc() const
{
  if ( mBody.empty() ) {
    return FileRegion();
  }
  return FileRegion(mBody.front()->loc(), mBody.back()->loc());
}

// @brief リストの要素数を返す．
// @note is_list() = true の時のみ意味を持つ．
int
DotlibList::list_size() const
{
  return mBody.size();
}

// @brief リストの要素を返す．
// @param[in] pos 位置番号 ( 0 <= pos < list_size() )
// @note is_list() == true の時のみ意味を持つ．
const DotlibNode*
DotlibList::list_elem(int pos) const
{
  return mBody[pos];
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibList::dump(ostream& s,
		 int indent) const
{
  s << "(";
  const char* comma = "";
  for (vector<const DotlibNodeImpl*>::const_iterator p = mBody.begin();
       p != mBody.end(); ++ p) {
    const DotlibNodeImpl* v = *p;
    s << comma;
    v->dump(s, 0);
    comma = ", ";
  }
  s << ")";
}

// @brief 要素を追加する．
// @param[in] node 追加する要素
// @note type() が kList の時のみ意味を持つ．
void
DotlibList::add_node(DotlibNodeImpl* node)
{
  mBody.push_back(node);
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibGroup
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibGroup::DotlibGroup(const DotlibNode* value,
			 const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value),
  mAttrTop(nullptr),
  mAttrTail(nullptr)
{
}

// @brief デストラクタ
DotlibGroup::~DotlibGroup()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibGroup::type() const
{
  return kGroup;
}

// @brief グループ型(kGroup)の時に true を返す．
bool
DotlibGroup::is_group() const
{
  return true;
}

// @brief グループの値を得る．
// @note type() が kGroup の時のみ意味を持つ．
const DotlibNode*
DotlibGroup::group_value() const
{
  return mValue;
}

// @brief 先頭の属性を得る．
// @note type() が kGroup の時のみ意味を持つ．
const DotlibAttr*
DotlibGroup::attr_top() const
{
  return mAttrTop;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibGroup::dump(ostream& s,
		  int indent) const
{
  s << ' ';
  group_value()->dump(s, 0);
  s << " {" << endl;
  for (const DotlibAttr* attr = attr_top(); attr; attr = attr->next()) {
    attr->dump(s, indent + 2);
  }
  s << indent_str(indent) << "}";
}

// @brief attribute を設定する．
// @param[in] attr 属性
// @note type() が kGroup の時のみ意味を持つ．
void
DotlibGroup::add_attr(DotlibAttr* attr)
{
  if ( mAttrTop != nullptr ) {
    mAttrTail->mNext = attr;
    mAttrTail = attr;
  }
  else {
    mAttrTop = mAttrTail = attr;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibTechnology
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibTechnology::DotlibTechnology(ClibTechnology value,
				   const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibTechnology::~DotlibTechnology()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibTechnology::type() const
{
  return kTechnology;
}

// @brief Technology を返す．
//
// type() == kTechnology の時のみ意味を持つ．
ClibTechnology
DotlibTechnology::technology() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibTechnology::dump(ostream& s,
		       int indent) const
{
  switch ( mValue ) {
  case kClibTechCmos: dump_str(s, "cmos"); break;
  case kClibTechFpga: dump_str(s, "fpga"); break;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibDelayModel
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibDelayModel::DotlibDelayModel(ClibDelayModel value,
				   const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibDelayModel::~DotlibDelayModel()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibDelayModel::type() const
{
  return kDelayModel;
}

// @brief DelayModel を返す．
//
// type() == kDelayModel の時のみ意味を持つ．
ClibDelayModel
DotlibDelayModel::delay_model() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibDelayModel::dump(ostream& s,
		       int indent) const
{
  switch ( mValue ) {
  case kClibDelayGenericCmos:   dump_str(s, "generic cmos"); break;
  case kClibDelayTableLookup:   dump_str(s, "table lookup"); break;
  case kClibDelayPiecewiseCmos: dump_str(s, "piesewise cmos"); break;
  case kClibDelayCmos2:         dump_str(s, "cmos2"); break;
  case kClibDelayDcm:           dump_str(s, "dcm"); break;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibCellPinDirection
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibCellPinDirection::DotlibCellPinDirection(ClibCellPinDirection value,
					       const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibCellPinDirection::~DotlibCellPinDirection()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibCellPinDirection::type() const
{
  return kCellPinDirection;
}

// @brief CellPinDirection を返す．
//
// type() == kCellPinDirection の時のみ意味を持つ．
ClibCellPinDirection
DotlibCellPinDirection::cell_pin_direction() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibCellPinDirection::dump(ostream& s,
		       int indent) const
{
  switch ( mValue ) {
  case kClibCellPinInput:    dump_str(s, "input"); break;
  case kClibCellPinOutput:   dump_str(s, "output"); break;
  case kClibCellPinInout:    dump_str(s, "inout"); break;
  case kClibCellPinInternal: dump_str(s, "internal"); break;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibTimingSense
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibTimingSense::DotlibTimingSense(ClibTimingSense value,
				     const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibTimingSense::~DotlibTimingSense()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibTimingSense::type() const
{
  return kTimingSense;
}

// @brief TimingSense を返す．
//
// type() == kTimingSense の時のみ意味を持つ．
ClibTimingSense
DotlibTimingSense::timing_sense() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibTimingSense::dump(ostream& s,
			int indent) const
{
  switch ( mValue ) {
  case kClibPosiUnate: dump_str(s, "positive unate"); break;
  case kClibNegaUnate: dump_str(s, "negative unate"); break;
  case kClibNonUnate:  dump_str(s, "non unate"); break;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibTimingType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibTimingType::DotlibTimingType(ClibTimingType value,
				   const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibTimingType::~DotlibTimingType()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibTimingType::type() const
{
  return kTimingType;
}

// @brief TimingType を返す．
//
// type() == kTimingType の時のみ意味を持つ．
ClibTimingType
DotlibTimingType::timing_type() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibTimingType::dump(ostream& s,
		       int indent) const
{
  switch ( mValue ) {
  case kClibTimingCombinational: dump_str(s, "combinational"); break;
  default: dump_str(s, "---"); break;
  }
}


//////////////////////////////////////////////////////////////////////
// クラス DotlibVarType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] value 値
// @param[in] loc ファイル上の位置
DotlibVarType::DotlibVarType(ClibVarType value,
			     const FileRegion& loc) :
  DotlibNodeBase(loc),
  mValue(value)
{
}

// @brief デストラクタ
DotlibVarType::~DotlibVarType()
{
}

// @brief 型を得る．
DotlibNode::Type
DotlibVarType::type() const
{
  return kVarType;
}

// @brief VarType を返す．
//
// type() == kVarType の時のみ意味を持つ．
ClibVarType
DotlibVarType::var_type() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
DotlibVarType::dump(ostream& s,
		    int indent) const
{
  switch ( mValue ) {
  case kClibVarInputNetTransition:                  dump_str(s, "input net transition"); break;
  case kClibVarTotalOutputNetCapacitance:           dump_str(s, "output net capacitance"); break;
  case kClibVarOutputNetLength:                     dump_str(s, "output net length"); break;
  case kClibVarOutputNetWireCap:                    dump_str(s, "output net wire cap"); break;
  case kClibVarOutputNetPinCap:                     dump_str(s, "output net pin cap"); break;
  case kClibVarRelatedOutTotalOutputNetCapacitance: dump_str(s, "related out total output net capacitance"); break;
  case kClibVarRelatedOutOutputNetLength:           dump_str(s, "related out output net length"); break;
  case kClibVarRelatedOutOutputNetWireCap:          dump_str(s, "related out output net wire cap"); break;
  case kClibVarRelatedOutOutputNetPinCap:           dump_str(s, "related out output net pin cap"); break;
  case kClibVarConstrainedPinTransition:            dump_str(s, "constrained pin transition"); break;
  case kClibVarRelatedPinTransition:                dump_str(s, "related pin transition"); break;
  case kClibVarNone:                                dump_str(s, "none"); break;
  }
}

END_NAMESPACE_YM_DOTLIB
