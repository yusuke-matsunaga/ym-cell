
/// @file AstValue.cc
/// @brief AstValue の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstValue.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloat.h"
#include "dotlib/AstString.h"
#include "dotlib/AstBool.h"
#include "dotlib/AstDelayModel.h"
#include "dotlib/AstDirection.h"
#include "dotlib/AstTechnology.h"
#include "dotlib/AstTimingSense.h"
#include "dotlib/AstTimingType.h"
#include "dotlib/AstVarType.h"
#include "dotlib/AstIntVector.h"
#include "dotlib/AstFloatVector.h"
#include "dotlib/AstStrVector.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstValue
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstValue::AstValue(const FileRegion& loc) :
  mValLoc{loc}
{
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
const AstExpr*
AstValue::expr_value() const
{
  return nullptr;
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

// @brief string vector 型の値を返す．
//
// string vector 型でない場合の値は不定
vector<ShString>
AstValue::string_vector_value() const
{
  return vector<ShString>{};
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
  s << value();
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
  s << value();
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
  dump_string(s, value());
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
  const char* tmp = value() ? "true" : "false";
  dump_string(s, tmp);
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
  switch ( mValue ) {
  case ClibDelayModel::GenericCmos:   tmp = "generic cmos"; break;
  case ClibDelayModel::TableLookup:   tmp = "table lookup"; break;
  case ClibDelayModel::PiecewiseCmos: tmp = "piesewise cmos"; break;
  case ClibDelayModel::Cmos2:         tmp = "cmos2"; break;
  case ClibDelayModel::Dcm:           tmp = "dcm"; break;
  default: break;
  }
  dump_string(s, tmp);
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
direction_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstDirection::dump(ostream& s) const
{
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibDirection::Input:    tmp = "input";    break;
  case ClibDirection::Output:   tmp = "output";   break;
  case ClibDirection::Inout:    tmp = "inout";    break;
  case ClibDirection::Internal: tmp = "internal"; break;
  default: break;
  }
  dump_string(s, tmp);
}


//////////////////////////////////////////////////////////////////////
// クラス AstExprValue
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstExprValue::AstExprValue(const AstExpr* value)
  : AstValue(value->loc()),
    mValue{value}
{
}

// @brief expr 型の値を返す．
const AstExpr*
AstExprValue::expr_value() const
{
  return mValue;
}

// @brief 内容をストリーム出力する．
void
AstExprValue::dump(ostream& s) const
{
  mValue->dump(s);
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
  switch ( mValue ) {
  case ClibTechnology::cmos: tmp = "cmos"; break;
  case ClibTechnology::fpga: tmp = "fpga"; break;
  default: break;
  }
  dump_string(s, tmp);
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
  switch ( mValue ) {
  case ClibTimingSense::PosiUnate: tmp = "positive unate"; break;
  case ClibTimingSense::NegaUnate: tmp = "negative unate"; break;
  case ClibTimingSense::NonUnate:  tmp = "non unate";      break;
  default: break;
  }
  dump_string(s, tmp);
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
  switch ( mValue ) {
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
  dump_string(s, tmp);
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
  switch ( mValue ) {
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
  dump_string(s, tmp);
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

END_NAMESPACE_YM_DOTLIB
