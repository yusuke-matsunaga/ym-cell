
/// @file AstValue.cc
/// @brief AstValue の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstValue.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstExpr.h"
#include "AstValue_int.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstValue
//////////////////////////////////////////////////////////////////////

// @brief int 値を作る．
AstValuePtr
AstValue::new_int(int value,
		  const FileRegion& loc)
{
  return AstValuePtr{new AstInt(value, loc)};
}

// @brief float 値を作る．
AstValuePtr
AstValue::new_float(double value,
		    const FileRegion& loc)
{
  return AstValuePtr{new AstFloat(value, loc)};
}

// @brief string 値を作る．
AstValuePtr
AstValue::new_string(const ShString& value,
		     const FileRegion& loc)
{
  return AstValuePtr{new AstString(value, loc)};
}

// @brief bool 値を作る．
AstValuePtr
AstValue::new_bool(bool value,
		   const FileRegion& loc)
{
  return AstValuePtr{new AstBool(value, loc)};
}

// @brief delay_model 値を作る．
AstValuePtr
AstValue::new_delay_model(ClibDelayModel value,
			  const FileRegion& loc)
{
  return AstValuePtr{new AstDelayModel(value, loc)};
}

// @brief direction 値を作る．
AstValuePtr
AstValue::new_direction(ClibDirection value,
			const FileRegion& loc)
{
  return AstValuePtr{new AstDirection(value, loc)};
}

// @brief technology 値を作る．
AstValuePtr
AstValue::new_technology(ClibTechnology value,
			 const FileRegion& loc)
{
  return AstValuePtr{new AstTechnology(value, loc)};
}

// @brief timing_sense 値を作る．
AstValuePtr
AstValue::new_timing_sense(ClibTimingSense value,
			   const FileRegion& loc)
{
  return AstValuePtr{new AstTimingSense(value, loc)};
}

// @brief timing_type 値を作る．
AstValuePtr
AstValue::new_timing_type(ClibTimingType value,
			  const FileRegion& loc)
{
  return AstValuePtr{new AstTimingType(value, loc)};
}

// @brief vartype 値を作る．
AstValuePtr
AstValue::new_vartype(ClibVarType value,
		      const FileRegion& loc)
{
  return AstValuePtr{new AstVarType(value, loc)};
}

// @brief expr 値を作る．
AstValuePtr
AstValue::new_expr(AstExprPtr&& value)
{
  return AstValuePtr{new AstExprValue(std::move(value))};
}

// @brief int vector 値を作る．
AstValuePtr
AstValue::new_int_vector(const vector<int>& value,
			 const FileRegion& loc)
{
  return AstValuePtr{new AstIntVector(value, loc)};
}

// @brief float vector 値を作る．
AstValuePtr
AstValue::new_float_vector(const vector<double>& value,
			   const FileRegion& loc)
{
  return AstValuePtr{new AstFloatVector(value, loc)};
}

// @brief complex 値を作る．
AstValuePtr
AstValue::new_complex(vector<AstValuePtr>& value,
		      const FileRegion& loc)
{
  return AstValuePtr{new AstComplexValue(value, loc)};
}

// @brief group 値を作る．
AstValuePtr
AstValue::new_group(AstValuePtr&& header,
		    vector<AstAttrPtr>& child_list,
		    const FileRegion& loc)
{
  return AstValuePtr{new AstGroupValue(std::move(header), child_list, loc)};
}

// @brief 無効な参照値を返す．
const AstValue&
AstValue::null_ref()
{
  static AstNullValue dummy;
  return dummy;
}

// @brief コンストラクタ
AstValue::AstValue(const FileRegion& loc)
  : mLoc{loc}
{
}

// @brief 適正な値を持っている時 true を返す．
bool
AstValue::is_valid() const
{
  return true;
}

// @brief int 型の値を返す．
//
// int 型でない場合の値は不定
int
AstValue::int_value() const
{
  return 0;
}

// @brief float 型の値を返す．
//
// float 型でない場合の値は不定
double
AstValue::float_value() const
{
  return 0.0;
}

// @brief string 型の値を返す．
//
// string 型でない場合の値は不定
ShString
AstValue::string_value() const
{
  return ShString{};
}

// @brief bool 型の値を返す．
//
// bool 型でない場合の値は不定
bool
AstValue::bool_value() const
{
  return false;
}

// @brief delay_model 型の値を返す．
//
// delay_model 型でない場合の値は不定
ClibDelayModel
AstValue::delay_model_value() const
{
  return ClibDelayModel::None;
}

// @brief direction 型の値を返す．
//
// direction 型でない場合の値は不定
ClibDirection
AstValue::direction_value() const
{
  return ClibDirection::None;
}

// @brief technology 型の値を返す．
//
// technology 型でない場合の値は不定
ClibTechnology
AstValue::technology_value() const
{
  return ClibTechnology::none;
}

// @brief timing_sense 型の値を返す．
//
// timing_sense 型でない場合の値は不定
ClibTimingSense
AstValue::timing_sense_value() const
{
  return ClibTimingSense::None;
}

// @brief timing_type 型の値を返す．
//
// timing_type 型でない場合の値は不定
ClibTimingType
AstValue::timing_type_value() const
{
  return ClibTimingType::None;
}

// @brief vartype 型の値を返す．
//
// vartype 型でない場合の値は不定
ClibVarType
AstValue::vartype_value() const
{
  return ClibVarType::None;
}

// @brief expr 型の値を返す．
//
// expr 型でない場合の値は不定
const AstExpr&
AstValue::expr_value() const
{
  ASSERT_NOT_REACHED;
  return AstExpr::null_ref();
}

// @brief int vector 型の値を返す．
//
// int vector 型でない場合の値は不定
vector<int>
AstValue::int_vector_value() const
{
  return vector<int>{};
}

// @brief float vector 型の値を返す．
//
// float vector 型でない場合の値は不定
vector<double>
AstValue::float_vector_value() const
{
  return vector<double>{};
}

// @brief complex attribute の場合の要素数を返す．
//
// 異なる型の場合の値は不定
int
AstValue::complex_elem_size() const
{
  return 0;
}

// @brief complex attribute の要素を返す．
//
// 異なる型の場合の値は不定
const AstValue&
AstValue::complex_elem_value(int pos) const
{
  return AstValue::null_ref();
}

// @brief group statement のヘッダを返す．
//
// 異なる型の場合の値は不定
const AstValue&
AstValue::group_header_value() const
{
  return AstValue::null_ref();
}

// @brief group statement の要素数を返す．
//
// 異なる型の場合の値は不定
int
AstValue::group_elem_size() const
{
  return 0;
}

// @brief group statement の要素の属性を返す．
//
// 異なる型の場合の値は不定
const AstAttr&
AstValue::group_elem_attr(int pos) const
{
  static AstAttr dummy;
  return dummy;
}


//////////////////////////////////////////////////////////////////////
/// クラス AstInt
//////////////////////////////////////////////////////////////////////

/// @brief コンストラクタ
AstInt::AstInt(int value,                   ///< [in] 値
	       const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief 整数値を返す．
int
AstInt::int_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
void
AstInt::dump(ostream& s) const
{
  s << int_value();
}


//////////////////////////////////////////////////////////////////////
/// クラス AstFloat
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstFloat::AstFloat(double value,                ///< [in] 値
		   const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief 数値を返す．
double
AstFloat::float_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
void
AstFloat::dump(ostream& s) const
{
  s << float_value();
}


//////////////////////////////////////////////////////////////////////
/// クラス AstString
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstString::AstString(ShString value,            ///< [in] 値
		     const FileRegion& val_loc) ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

/// @brief 定数シンボルを返す．
ShString
AstString::string_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstString::dump(ostream& s) const
{
  s << string_value();
}


//////////////////////////////////////////////////////////////////////
/// クラス AstBool
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstBool::AstBool(bool value,                 ///< [in] 値
		 const FileRegion& val_loc)  ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief ブール値を返す．
bool
AstBool::bool_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstBool::dump(ostream& s) const
{
  const char* tmp = bool_value() ? "true" : "false";
  s << tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstDelayModel
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstDelayModel::AstDelayModel(ClibDelayModel value,
			     const FileRegion& val_loc)
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief DelayModel を返す．
ClibDelayModel
AstDelayModel::delay_model_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstDelayModel::dump(ostream& s) const
{
  const char* tmp = "---";
  switch ( delay_model_value() ) {
  case ClibDelayModel::GenericCmos:   tmp = "generic cmos"; break;
  case ClibDelayModel::TableLookup:   tmp = "table lookup"; break;
  case ClibDelayModel::PiecewiseCmos: tmp = "piesewise cmos"; break;
  case ClibDelayModel::Cmos2:         tmp = "cmos2"; break;
  case ClibDelayModel::Dcm:           tmp = "dcm"; break;
  default: break;
  }
  s << tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstDirection
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstDirection::AstDirection(ClibDirection value,       ///< [in] 値
			   const FileRegion& val_loc) ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief direction を返す．
ClibDirection
AstDirection::direction_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstDirection::dump(ostream& s) const
{
  const char* tmp = "---";
  switch ( direction_value() ) {
  case ClibDirection::Input:    tmp = "input";    break;
  case ClibDirection::Output:   tmp = "output";   break;
  case ClibDirection::Inout:    tmp = "inout";    break;
  case ClibDirection::Internal: tmp = "internal"; break;
  default: break;
  }
  s << tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstExprValue
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstExprValue::AstExprValue(AstExprPtr&& value)
  : AstValue(value->loc()),
    mValue{std::move(value)}
{
}

// @brief expr 型の値を返す．
const AstExpr&
AstExprValue::expr_value() const
{
  return *mValue;
}

// @brief 内容をストリーム出力する．
void
AstExprValue::dump(ostream& s) const
{
  s << expr_value().decompile();
}


//////////////////////////////////////////////////////////////////////
// クラス AstTechnology
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstTechnology::AstTechnology(ClibTechnology value,      ///< [in] 値
			     const FileRegion& val_loc) ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief Technology を返す．
ClibTechnology
AstTechnology::technology_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstTechnology::dump(ostream& s) const
{
  const char* tmp = "---";
  switch ( technology_value() ) {
  case ClibTechnology::cmos: tmp = "cmos"; break;
  case ClibTechnology::fpga: tmp = "fpga"; break;
  default: break;
  }
  s << tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstTimingSense
//////////////////////////////////////////////////////////////////////

/// @brief コンストラクタ
AstTimingSense::AstTimingSense(ClibTimingSense value,       ///< [in] 値
			       const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief TimingSense を返す．
ClibTimingSense
AstTimingSense::timing_sense_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstTimingSense::dump(ostream& s) const
{
  const char* tmp = "---";
  switch ( timing_sense_value() ) {
  case ClibTimingSense::PosiUnate: tmp = "positive unate"; break;
  case ClibTimingSense::NegaUnate: tmp = "negative unate"; break;
  case ClibTimingSense::NonUnate:  tmp = "non unate";      break;
  default: break;
  }
  s << tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstTimingType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstTimingType::AstTimingType(ClibTimingType value,        ///< [in] 値
			     const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief TimingType を返す．
ClibTimingType
AstTimingType::timing_type_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstTimingType::dump(ostream& s) const
{
  const char* tmp = "---";
  switch ( timing_type_value() ) {
  case ClibTimingType::Combinational:         tmp = "combinational"; break;
  case ClibTimingType::CombinationalRise:     tmp = "combinational rise"; break;
  case ClibTimingType::CombinationalFall:     tmp = "combinational fall"; break;
  case ClibTimingType::ThreeStateEnable:      tmp = "three state enable"; break;
  case ClibTimingType::ThreeStateDisable:     tmp = "three state disable"; break;
  case ClibTimingType::ThreeStateEnableRise:  tmp = "three state enable rise"; break;
  case ClibTimingType::ThreeStateEnableFall:  tmp = "three state enable fall"; break;
  case ClibTimingType::ThreeStateDisableRise: tmp = "three state disable rise"; break;
  case ClibTimingType::ThreeStateDisableFall: tmp = "three state disable fall"; break;
  case ClibTimingType::RisingEdge:            tmp = "rising edge"; break;
  case ClibTimingType::FallingEdge:           tmp = "falling edge"; break;
  case ClibTimingType::Preset:                tmp = "preset"; break;
  case ClibTimingType::Clear:                 tmp = "clear"; break;
  case ClibTimingType::HoldRising:            tmp = "hold rising"; break;
  case ClibTimingType::HoldFalling:           tmp = "hold falling"; break;
  case ClibTimingType::SetupRising:           tmp = "setup rising"; break;
  case ClibTimingType::SetupFalling:          tmp = "setup falling"; break;
  case ClibTimingType::RecoveryRising:        tmp = "recovery rising"; break;
  case ClibTimingType::RecoveryFalling:       tmp = "recovery falling"; break;
  case ClibTimingType::SkewRising:            tmp = "skew rising"; break;
  case ClibTimingType::SkewFalling:           tmp = "skew falling"; break;
  case ClibTimingType::RemovalRising:         tmp = "removal rising"; break;
  case ClibTimingType::RemovalFalling:        tmp = "removal falling"; break;
  case ClibTimingType::NonSeqSetupRising:     tmp = "non seq setup rising"; break;
  case ClibTimingType::NonSeqSetupFalling:    tmp = "non seq setup falling"; break;
  case ClibTimingType::NonSeqHoldRising:      tmp = "non seq hold rising"; break;
  case ClibTimingType::NonSeqHoldFalling:     tmp = "non seq hold falling"; break;
  case ClibTimingType::NochangeHighHigh:      tmp = "nochange high high"; break;
  case ClibTimingType::NochangeHighLow:       tmp = "nochange high low"; break;
  case ClibTimingType::NochangeLowHigh:       tmp = "nochange low high"; break;
  case ClibTimingType::NochangeLowLow:        tmp = "nochange low low"; break;
  default: break;
  }
  s << tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstVarType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstVarType::AstVarType(ClibVarType value,           ///< [in] 値
		       const FileRegion& val_loc)   ///< [in] 値のファイル上の位置
  : AstValue(val_loc),
    mValue{value}
{
}

// @brief VarType を返す．
ClibVarType
AstVarType::vartype_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstVarType::dump(ostream& s) const
{
  const char* tmp = "---";
  switch ( vartype_value() ) {
  case ClibVarType::InputNetTransition:                  tmp = "input net transition"; break;
  case ClibVarType::InputTransitionTime:                 tmp = "input transition time"; break;
  case ClibVarType::TotalOutputNetCapacitance:           tmp = "output net capacitance"; break;
  case ClibVarType::EqualOrOppositeOutputNetCapacitance: tmp = "equal or opposite output net capacitance"; break;
  case ClibVarType::OutputNetLength:                     tmp = "output net length"; break;
  case ClibVarType::OutputNetWireCap:                    tmp = "output net wire cap"; break;
  case ClibVarType::OutputNetPinCap:                     tmp = "output net pin cap"; break;
  case ClibVarType::RelatedOutTotalOutputNetCapacitance: tmp = "related out total output net capacitance"; break;
  case ClibVarType::RelatedOutOutputNetLength:           tmp = "related out output net length"; break;
  case ClibVarType::RelatedOutOutputNetWireCap:          tmp = "related out output net wire cap"; break;
  case ClibVarType::RelatedOutOutputNetPinCap:           tmp = "related out output net pin cap"; break;
  case ClibVarType::ConstrainedPinTransition:            tmp = "constrained pin transition"; break;
  case ClibVarType::RelatedPinTransition:                tmp = "related pin transition"; break;
  case ClibVarType::None:                                tmp = "none"; break;
  default: break;
  }
  s << tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstIntVector
//////////////////////////////////////////////////////////////////////

/// @brief コンストラクタ
AstIntVector::AstIntVector(const vector<int>& value,
			   const FileRegion& loc)
  : AstValue(loc),
    mBody{value}
{
}

// @brief ベクタを取り出す．
vector<int>
AstIntVector::int_vector_value() const
{
  return mBody;
}

// @brief 内容をストリーム出力する．
void
AstIntVector::dump(ostream& s) const
{
  const char* comma = "";
  for ( auto i: mBody ) {
    s << comma << i;
    comma = ", ";
  }
}


//////////////////////////////////////////////////////////////////////
// クラス AstFloatVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstFloatVector::AstFloatVector(const vector<double>& value_list,
			       const FileRegion& loc)
  : AstValue(loc),
    mBody{value_list}
{
}

// @brief ベクタの全体を取り出す．
vector<double>
AstFloatVector::float_vector_value() const
{
  return mBody;
}

// @brief 内容をストリーム出力する．
void
AstFloatVector::dump(ostream& s) const
{
  const char* comma = "";
  for ( auto d: mBody ) {
    s << comma << d;
    comma = ", ";
  }
}


//////////////////////////////////////////////////////////////////////
// クラス AstComplexValue
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ(可変引数)
AstComplexValue::AstComplexValue(vector<AstValuePtr>& value_list,
				 const FileRegion& loc)
  : AstValue(loc)
{
  for ( auto& ptr: value_list ) {
    mElemList.push_back(std::move(ptr));
  }
}

// @brief complex attribute の場合の要素数を返す．
//
// 異なる型の場合の値は不定
int
AstComplexValue::complex_elem_size() const
{
  return mElemList.size();
}

// @brief complex attribute の要素を返す．
//
// 異なる型の場合の値は不定
const AstValue&
AstComplexValue::complex_elem_value(int pos) const
{
  ASSERT_COND( 0 <= pos && pos < complex_elem_size() );
  return *mElemList[pos];
}

// @brief 内容を出力する．
void
AstComplexValue::dump(ostream& s) const
{
  const char* comma = "";
  s << "( ";
  for ( auto& ptr: mElemList ) {
    s << comma;
    ptr->dump(s);
    comma = ", ";
  }
  s << ")";
}


//////////////////////////////////////////////////////////////////////
// クラス AstGroupValue
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstGroupValue::AstGroupValue(AstValuePtr&& header_value,
			     vector<AstAttrPtr>& child_list,
			     const FileRegion& loc)
  : AstValue(loc),
    mHeader{std::move(header_value)}
{
  for ( auto& p: child_list ) {
    mChildList.push_back(std::move(p));
  }
}

// @brief group statement のヘッダを返す．
//
// 異なる型の場合の値は不定
const AstValue&
AstGroupValue::group_header_value() const
{
  return *mHeader;
}

// @brief group statement の要素数を返す．
//
// 異なる型の場合の値は不定
int
AstGroupValue::group_elem_size() const
{
  return mChildList.size();
}

// @brief group statement の要素の属性を返す．
//
// 異なる型の場合の値は不定
const AstAttr&
AstGroupValue::group_elem_attr(int pos) const
{
  ASSERT_COND( 0 <= pos && pos < group_elem_size() );

  return *mChildList[pos];
}

// @brief 内容を出力する．
void
AstGroupValue::dump(ostream& s) const
{
}


//////////////////////////////////////////////////////////////////////
// クラス AstNullValue
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstNullValue::AstNullValue()
  : AstValue(FileRegion{})
{
}

// @brief 適正な値を持っている時 true を返す．
bool
AstNullValue::is_valid() const
{
  return false;
}

// @brief 内容を出力する．
void
AstNullValue::dump(ostream& s) const
{
  s << "---";
}

END_NAMESPACE_YM_DOTLIB
