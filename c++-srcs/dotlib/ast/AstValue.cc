
/// @file AstValue.cc
/// @brief AstValue の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021, 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstValue.h"
#include "dotlib/AstAttr.h"
#include "dotlib/AstExpr.h"
#include "AstValue_int.h"


BEGIN_NAMESPACE_YM_DOTLIB

BEGIN_NONAMESPACE

void
print_indent(
  ostream& s,
  int ilevel
)
{
  for ( int i = 0; i < ilevel; ++ i ) {
    s << "  ";
  }
}

END_NONAMESPACE

//////////////////////////////////////////////////////////////////////
// クラス AstValue
//////////////////////////////////////////////////////////////////////

// @brief int 値を作る．
AstValuePtr
AstValue::new_int(
  int value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstInt(value, loc)};
}

// @brief float 値を作る．
AstValuePtr
AstValue::new_float(
  double value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstFloat(value, loc)};
}

// @brief string 値を作る．
AstValuePtr
AstValue::new_string(
  const ShString& value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstString(value, loc)};
}

// @brief bool 値を作る．
AstValuePtr
AstValue::new_bool(
  bool value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstBool(value, loc)};
}

// @brief delay_model 値を作る．
AstValuePtr
AstValue::new_delay_model(
  ClibDelayModel value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstDelayModel(value, loc)};
}

// @brief direction 値を作る．
AstValuePtr
AstValue::new_direction(
  ClibDirection value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstDirection(value, loc)};
}

// @brief technology 値を作る．
AstValuePtr
AstValue::new_technology(
  ClibTechnology value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstTechnology(value, loc)};
}

// @brief timing_sense 値を作る．
AstValuePtr
AstValue::new_timing_sense(
  ClibTimingSense value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstTimingSense(value, loc)};
}

// @brief timing_type 値を作る．
AstValuePtr
AstValue::new_timing_type(
  ClibTimingType value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstTimingType(value, loc)};
}

// @brief vartype 値を作る．
AstValuePtr
AstValue::new_vartype(
  ClibVarType value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstVarType(value, loc)};
}

// @brief expr 値を作る．
AstValuePtr
AstValue::new_expr(
  AstExprPtr&& value
)
{
  return AstValuePtr{new AstExprValue(std::move(value))};
}

// @brief int vector 値を作る．
AstValuePtr
AstValue::new_int_vector(
  const vector<int>& value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstIntVector(value, loc)};
}

// @brief float vector 値を作る．
AstValuePtr
AstValue::new_float_vector(
  const vector<double>& value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstFloatVector(value, loc)};
}

// @brief complex 値を作る．
AstValuePtr
AstValue::new_complex(
  vector<AstValuePtr>& value,
  const FileRegion& loc
)
{
  return AstValuePtr{new AstComplexValue(value, loc)};
}

// @brief group 値を作る．
AstValuePtr
AstValue::new_group(
  AstValuePtr&& header,
  vector<AstAttrPtr>& child_list,
  const FileRegion& loc
)
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
AstValue::AstValue(
  const FileRegion& loc
) : mLoc{loc}
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
  return ClibDelayModel::none;
}

// @brief direction 型の値を返す．
//
// direction 型でない場合の値は不定
ClibDirection
AstValue::direction_value() const
{
  return ClibDirection::none;
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
  return ClibTimingSense::none;
}

// @brief timing_type 型の値を返す．
//
// timing_type 型でない場合の値は不定
ClibTimingType
AstValue::timing_type_value() const
{
  return ClibTimingType::none;
}

// @brief vartype 型の値を返す．
//
// vartype 型でない場合の値は不定
ClibVarType
AstValue::vartype_value() const
{
  return ClibVarType::none;
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
SizeType
AstValue::complex_elem_size() const
{
  return 0;
}

// @brief complex attribute の要素を返す．
//
// 異なる型の場合の値は不定
const AstValue&
AstValue::complex_elem_value(
  SizeType pos
) const
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
SizeType
AstValue::group_elem_size() const
{
  return 0;
}

// @brief group statement の要素の属性を返す．
//
// 異なる型の場合の値は不定
const AstAttr&
AstValue::group_elem_attr(
  SizeType pos
) const
{
  static AstAttr dummy;
  return dummy;
}


//////////////////////////////////////////////////////////////////////
// クラス AstSimple
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstSimple::AstSimple(
  const FileRegion& val_loc
) : AstValue(val_loc)
{
}

// @brief 内容をストリーム出力する．
void
AstSimple::print(
  ostream& s,
  int ilevel
) const
{
  // ilevel は無視
  s << " : " << decompile() << ";" << endl;
}


//////////////////////////////////////////////////////////////////////
/// クラス AstInt
//////////////////////////////////////////////////////////////////////

/// @brief コンストラクタ
AstInt::AstInt(
  int value,                 ///< [in] 値
  const FileRegion& val_loc  ///< [in] 値のファイル上の位置
) : AstSimple(val_loc),
    mValue{value}
{
}

// @brief 整数値を返す．
int
AstInt::int_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstInt::decompile() const
{
  ostringstream buf;
  buf << int_value();
  return buf.str();
}


//////////////////////////////////////////////////////////////////////
/// クラス AstFloat
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstFloat::AstFloat(
  double value,             ///< [in] 値
  const FileRegion& val_loc ///< [in] 値のファイル上の位置
) : AstSimple(val_loc),
    mValue{value}
{
}

// @brief 数値を返す．
double
AstFloat::float_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstFloat::decompile() const
{
  ostringstream buf;
  buf << float_value();
  return buf.str();
}


//////////////////////////////////////////////////////////////////////
/// クラス AstString
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstString::AstString(
  ShString value,           ///< [in] 値
  const FileRegion& val_loc ///< [in] 値のファイル上の位置
) : AstSimple(val_loc),
    mValue{value}
{
}

/// @brief 定数シンボルを返す．
ShString
AstString::string_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstString::decompile() const
{
  // " が必要か調べる．
  string s{string_value()};
  bool need_quote = false;
  if ( !isalpha(s[0]) && s[0] != '_' ) {
    need_quote = true;
  }
  for ( auto c: s ) {
    if ( isspace(c) ) {
      need_quote = true;
      break;
    }
  }
  if ( need_quote ) {
    return "\"" + s + "\"";
  }
  else {
    return s;
  }
}


//////////////////////////////////////////////////////////////////////
/// クラス AstBool
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstBool::AstBool(
  bool value,               ///< [in] 値
  const FileRegion& val_loc ///< [in] 値のファイル上の位置
) : AstSimple(val_loc),
    mValue{value}
{
}

// @brief ブール値を返す．
bool
AstBool::bool_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstBool::decompile() const
{
  const char* tmp = bool_value() ? "true" : "false";
  return tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstDelayModel
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstDelayModel::AstDelayModel(
  ClibDelayModel value,
  const FileRegion& val_loc
) : AstSimple(val_loc),
    mValue{value}
{
}

// @brief DelayModel を返す．
ClibDelayModel
AstDelayModel::delay_model_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstDelayModel::decompile() const
{
  const char* tmp = "---";
  switch ( delay_model_value() ) {
  case ClibDelayModel::generic_cmos:   tmp = "generic_cmos"; break;
  case ClibDelayModel::table_lookup:   tmp = "table_lookup"; break;
  case ClibDelayModel::piecewise_cmos: tmp = "piecewise_cmos"; break;
  case ClibDelayModel::cmos2:         tmp = "cmos2"; break;
  case ClibDelayModel::dcm:           tmp = "dcm"; break;
  default: break;
  }
  return tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstDirection
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstDirection::AstDirection(
  ClibDirection value,      ///< [in] 値
  const FileRegion& val_loc ///< [in] 値のファイル上の位置
) : AstSimple(val_loc),
    mValue{value}
{
}

// @brief direction を返す．
ClibDirection
AstDirection::direction_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstDirection::decompile() const
{
  const char* tmp = "---";
  switch ( direction_value() ) {
  case ClibDirection::input:    tmp = "input";    break;
  case ClibDirection::output:   tmp = "output";   break;
  case ClibDirection::inout:    tmp = "inout";    break;
  case ClibDirection::internal: tmp = "internal"; break;
  default: break;
  }
  return tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstExprValue
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstExprValue::AstExprValue(
  AstExprPtr&& value
) : AstSimple(value->loc()),
    mValue{std::move(value)}
{
}

// @brief expr 型の値を返す．
const AstExpr&
AstExprValue::expr_value() const
{
  return *mValue;
}

// @brief 値を表す文字列を返す．
string
AstExprValue::decompile() const
{
  return expr_value().decompile();
}


//////////////////////////////////////////////////////////////////////
// クラス AstTechnology
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstTechnology::AstTechnology(
  ClibTechnology value,     ///< [in] 値
  const FileRegion& val_loc ///< [in] 値のファイル上の位置
) : AstSimple(val_loc),
    mValue{value}
{
}

// @brief Technology を返す．
ClibTechnology
AstTechnology::technology_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstTechnology::decompile() const
{
  const char* tmp = "---";
  switch ( technology_value() ) {
  case ClibTechnology::cmos: tmp = "cmos"; break;
  case ClibTechnology::fpga: tmp = "fpga"; break;
  default: break;
  }
  return tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstTimingSense
//////////////////////////////////////////////////////////////////////

/// @brief コンストラクタ
AstTimingSense::AstTimingSense(
  ClibTimingSense value,    ///< [in] 値
  const FileRegion& val_loc ///< [in] 値のファイル上の位置
) : AstSimple(val_loc),
    mValue{value}
{
}

// @brief TimingSense を返す．
ClibTimingSense
AstTimingSense::timing_sense_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstTimingSense::decompile() const
{
  const char* tmp = "---";
  switch ( timing_sense_value() ) {
  case ClibTimingSense::positive_unate: tmp = "positive_unate"; break;
  case ClibTimingSense::negative_unate: tmp = "negative_unate"; break;
  case ClibTimingSense::non_unate:  tmp = "non_unate";      break;
  default: break;
  }
  return tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstTimingType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstTimingType::AstTimingType(
  ClibTimingType value,     ///< [in] 値
  const FileRegion& val_loc ///< [in] 値のファイル上の位置
) : AstSimple(val_loc),
    mValue{value}
{
}

// @brief TimingType を返す．
ClibTimingType
AstTimingType::timing_type_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstTimingType::decompile() const
{
  const char* tmp = "---";
  switch ( timing_type_value() ) {
  case ClibTimingType::combinational:         tmp = "combinational"; break;
  case ClibTimingType::combinational_rise:     tmp = "combinational_rise"; break;
  case ClibTimingType::combinational_fall:     tmp = "combinational_fall"; break;
  case ClibTimingType::three_state_enable:      tmp = "three_state_enable"; break;
  case ClibTimingType::three_state_disable:     tmp = "three_state_disable"; break;
  case ClibTimingType::three_state_enable_rise:  tmp = "three_state_enable_rise"; break;
  case ClibTimingType::three_state_enable_fall:  tmp = "three_state_enable_fall"; break;
  case ClibTimingType::three_state_disable_rise: tmp = "three_state_disable_rise"; break;
  case ClibTimingType::three_state_disable_fall: tmp = "three_state_disable_fall"; break;
  case ClibTimingType::rising_edge:            tmp = "rising_edge"; break;
  case ClibTimingType::falling_edge:           tmp = "falling_edge"; break;
  case ClibTimingType::preset:                tmp = "preset"; break;
  case ClibTimingType::clear:                 tmp = "clear"; break;
  case ClibTimingType::hold_rising:            tmp = "hold_rising"; break;
  case ClibTimingType::hold_falling:           tmp = "hold_falling"; break;
  case ClibTimingType::setup_rising:           tmp = "setup_rising"; break;
  case ClibTimingType::setup_falling:          tmp = "setup_falling"; break;
  case ClibTimingType::recovery_rising:        tmp = "recovery_rising"; break;
  case ClibTimingType::recovery_falling:       tmp = "recovery_falling"; break;
  case ClibTimingType::skew_rising:            tmp = "skew_rising"; break;
  case ClibTimingType::skew_falling:           tmp = "skew_falling"; break;
  case ClibTimingType::removal_rising:         tmp = "removal_rising"; break;
  case ClibTimingType::removal_falling:        tmp = "removal_falling"; break;
  case ClibTimingType::non_seq_setup_rising:     tmp = "non_seq_setup_rising"; break;
  case ClibTimingType::non_seq_setup_falling:    tmp = "non_seq_setup_falling"; break;
  case ClibTimingType::non_seq_hold_rising:      tmp = "non_seq_hold_rising"; break;
  case ClibTimingType::non_seq_hold_falling:     tmp = "non_seq_hold_falling"; break;
  case ClibTimingType::nochange_high_high:      tmp = "nochange_high_high"; break;
  case ClibTimingType::nochange_high_low:       tmp = "nochange_high_low"; break;
  case ClibTimingType::nochange_low_high:       tmp = "nochange_low_high"; break;
  case ClibTimingType::nochange_low_low:        tmp = "nochange_low_low"; break;
  default: break;
  }
  return tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstVarType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstVarType::AstVarType(
  ClibVarType value,        ///< [in] 値
  const FileRegion& val_loc ///< [in] 値のファイル上の位置
) : AstSimple(val_loc),
    mValue{value}
{
}

// @brief VarType を返す．
ClibVarType
AstVarType::vartype_value() const
{
  return mValue;
}

// @brief 値を表す文字列を返す．
string
AstVarType::decompile() const
{
  const char* tmp = "---";
  switch ( vartype_value() ) {
  case ClibVarType::input_net_transition:                  tmp = "input_net_transition"; break;
  case ClibVarType::input_transition_time:                 tmp = "input_transition_time"; break;
  case ClibVarType::total_output_net_capacitance:           tmp = "total_output_net_capacitance"; break;
  case ClibVarType::equal_or_opposite_output_net_capacitance: tmp = "equal_or_opposite_output_net_capacitance"; break;
  case ClibVarType::output_net_length:                     tmp = "output_net_length"; break;
  case ClibVarType::output_net_wire_cap:                    tmp = "output_net_wire_cap"; break;
  case ClibVarType::output_net_pin_cap:                     tmp = "output_net_pin_cap"; break;
  case ClibVarType::related_out_total_output_net_capacitance: tmp = "related_out_total_output_net_capacitance"; break;
  case ClibVarType::related_out_output_net_length:           tmp = "related_out_output_net_length"; break;
  case ClibVarType::related_out_output_net_wire_cap:          tmp = "related_out_output_net_wire_cap"; break;
  case ClibVarType::related_out_output_net_pin_cap:           tmp = "related_out_output_net_pin_cap"; break;
  case ClibVarType::constrained_pin_transition:            tmp = "constrained_pin_transition"; break;
  case ClibVarType::related_pin_transition:                tmp = "related_pin_transition"; break;
  case ClibVarType::none:                                tmp = "none"; break;
  default: break;
  }
  return tmp;
}


//////////////////////////////////////////////////////////////////////
// クラス AstIntVector
//////////////////////////////////////////////////////////////////////

/// @brief コンストラクタ
AstIntVector::AstIntVector(
  const vector<int>& value,
  const FileRegion& loc
) : AstSimple(loc),
    mBody{value}
{
}

// @brief ベクタを取り出す．
vector<int>
AstIntVector::int_vector_value() const
{
  return mBody;
}

// @brief 値を表す文字列を返す．
string
AstIntVector::decompile() const
{
  ostringstream buf;
  const char* comma = "";
  buf << "\"";
  for ( auto i: mBody ) {
    buf << comma << i;
    comma = ", ";
  }
  buf << "\"";
  return buf.str();
}


//////////////////////////////////////////////////////////////////////
// クラス AstFloatVector
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstFloatVector::AstFloatVector(
  const vector<double>& value_list,
  const FileRegion& loc
) : AstSimple(loc),
    mBody{value_list}
{
}

// @brief ベクタの全体を取り出す．
vector<double>
AstFloatVector::float_vector_value() const
{
  return mBody;
}

// @brief 値を表す文字列を返す．
string
AstFloatVector::decompile() const
{
  ostringstream buf;
  const char* comma = "";
  buf << "\"";
  for ( auto d: mBody ) {
    buf << comma << d;
    comma = ", ";
  }
  buf << "\"";
  return buf.str();
}


//////////////////////////////////////////////////////////////////////
// クラス AstComplexValue
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ(可変引数)
AstComplexValue::AstComplexValue(
  vector<AstValuePtr>& value_list,
  const FileRegion& loc
) : AstValue(loc)
{
  for ( auto& ptr: value_list ) {
    mElemList.push_back(std::move(ptr));
  }
}

// @brief complex attribute の場合の要素数を返す．
//
// 異なる型の場合の値は不定
SizeType
AstComplexValue::complex_elem_size() const
{
  return mElemList.size();
}

// @brief complex attribute の要素を返す．
//
// 異なる型の場合の値は不定
const AstValue&
AstComplexValue::complex_elem_value(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < complex_elem_size() );
  return *mElemList[pos];
}

// @brief 内容をストリーム出力する．
void
AstComplexValue::print(
  ostream& s,
  int ilevel
) const
{
  // ilevel は無視
  s << decompile() << ";" << endl;
}

// @brief 値を表す文字列を返す．
string
AstComplexValue::decompile() const
{
  const char* comma = "";
  ostringstream buf;
  buf << "( ";
  for ( auto& ptr: mElemList ) {
    buf << comma << ptr->decompile();
    comma = ", ";
  }
  buf << ")";
  return buf.str();
}


//////////////////////////////////////////////////////////////////////
// クラス AstGroupValue
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AstGroupValue::AstGroupValue(
  AstValuePtr&& header_value,
  vector<AstAttrPtr>& child_list,
  const FileRegion& loc
) : AstValue(loc),
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
SizeType
AstGroupValue::group_elem_size() const
{
  return mChildList.size();
}

// @brief group statement の要素の属性を返す．
//
// 異なる型の場合の値は不定
const AstAttr&
AstGroupValue::group_elem_attr(
  SizeType pos
) const
{
  ASSERT_COND( 0 <= pos && pos < group_elem_size() );

  return *mChildList[pos];
}

// @brief 内容をストリーム出力する．
void
AstGroupValue::print(
  ostream& s,
  int ilevel
) const
{
  s << group_header_value().decompile()
    << " {" << endl;
  for ( auto& ptr: mChildList ) {
    ptr->print(s, ilevel + 1);
  }
  print_indent(s, ilevel);
  s << "}" << endl;
}

// @brief 値を表す文字列を返す．
string
AstGroupValue::decompile() const
{
  return string{};
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

// @brief 内容をストリーム出力する．
void
AstNullValue::print(
  ostream& s,
  int ilevel
) const
{
}

// @brief 値を表す文字列を返す．
string
AstNullValue::decompile() const
{
  return "---";
}


//////////////////////////////////////////////////////////////////////
// クラス AstAttr
//////////////////////////////////////////////////////////////////////

// @brief 内容をストリーム出力する．
void
AstAttr::print(
  ostream& s,
  int ilevel
) const
{
  print_indent(s, ilevel);
  s << kwd();
  value().print(s, ilevel);
}

END_NAMESPACE_YM_DOTLIB
