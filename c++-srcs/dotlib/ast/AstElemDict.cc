
/// @file AstElemDict.cc
/// @brief AstElemDict の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstElemDict.h"
#include "dotlib/AstExpr.h"
#include "dotlib/AstValue.h"
#include "ym/ClibArea.h"
#include "ym/ClibCapacitance.h"
#include "ym/ClibResistance.h"
#include "ym/ClibTime.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief string の値を取り出す．
AstElemDict::RetType
AstElemDict::get_string(
  const char* keyword,
  ShString& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = _val->string_value();
  }
  return ret;
}

// @brief area の値を取り出す．
AstElemDict::RetType
AstElemDict::get_area(
  const char* keyword,
  ClibArea& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = ClibArea{_val->float_value()};
  }
  return ret;
}

// @brief capacitance の値を取り出す．
AstElemDict::RetType
AstElemDict::get_capacitance(
  const char* keyword,
  ClibCapacitance& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = ClibCapacitance{_val->float_value()};
  }
  return ret;
}

// @brief resistance の値を取り出す．
AstElemDict::RetType
AstElemDict::get_resistance(
  const char* keyword,
  ClibResistance& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = ClibResistance{_val->float_value()};
  }
  return ret;
}

// @brief technology の値を取り出す．
AstElemDict::RetType
AstElemDict::get_technology(
  const char* keyword,
  ClibTechnology& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = ClibTechnology{_val->technology_value()};
  }
  return ret;
}

// @brief time の値を取り出す．
AstElemDict::RetType
AstElemDict::get_time(
  const char* keyword,
  ClibTime& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = ClibTime{_val->float_value()};
  }
  return ret;
}

// @brief ClibCPV の値を取り出す．
AstElemDict::RetType
AstElemDict::get_cpv(
  const char* keyword,
  ClibCPV& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    auto tmp_str = _val->string_value();
    if ( tmp_str == "L" || tmp_str == "l" ) {
      val = ClibCPV::L;
    }
    else if ( tmp_str == "H" || tmp_str == "h" ) {
      val = ClibCPV::H;
    }
    else if ( tmp_str == "N" || tmp_str == "n" ) {
      val = ClibCPV::N;
    }
    else if ( tmp_str == "T" || tmp_str == "t" ) {
      val = ClibCPV::T;
    }
    else if ( tmp_str == "X" || tmp_str == "x" ) {
      val = ClibCPV::X;
    }
    else {
#warning "TODO: エラーメッセージ"
      ret = ERROR;
    }
  }
  return ret;
}

// @brief ClibVarType の値を取り出す．
AstElemDict::RetType
AstElemDict::get_vartype(
  const char* keyword,
  ClibVarType& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    auto tmp_str = _val->string_value();
    if ( tmp_str == "input_net_transition" ) {
      val = ClibVarType::input_net_transition;
    }
    else if ( tmp_str == "total_output_net_capacitance" ) {
      val = ClibVarType::total_output_net_capacitance;
    }
    else if ( tmp_str == "output_net_length" ) {
      val = ClibVarType::output_net_length;
    }
    else if ( tmp_str == "output_net_wire_cap" ) {
      val = ClibVarType::output_net_wire_cap;
    }
    else if ( tmp_str == "output_net_pin_cap" ) {
      val = ClibVarType::output_net_pin_cap;
    }
    else if ( tmp_str == "equal_or_opposite_output_net_capacitance" ) {
      val = ClibVarType::equal_or_opposite_output_net_capacitance;
    }
    else if ( tmp_str == "input_transition_time" ) {
      val = ClibVarType::input_transition_time;
    }
    else if ( tmp_str == "related_out_total_output_net_capacitance" ) {
      val = ClibVarType::related_out_total_output_net_capacitance;
    }
    else if ( tmp_str == "related_out_output_net_length" ) {
      val = ClibVarType::related_out_output_net_length;
    }
    else if ( tmp_str == "related_out_output_net_pin_cap" ) {
      val = ClibVarType::related_out_output_net_pin_cap;
    }
    else if ( tmp_str == "constrained_pin_transition" ) {
      val = ClibVarType::constrained_pin_transition;
    }
    else if ( tmp_str == "related_pin_transition" ) {
      val = ClibVarType::related_pin_transition;
    }
    else {
#warning "TODO: エラーメッセージ"
      ret = ERROR;
    }
  }
  return ret;
}

// @brief expr の値を取り出す．
AstElemDict::RetType
AstElemDict::get_expr(
  const char* keyword,
  const AstExpr*& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = &(_val->expr_value());
  }
  return ret;
}

// @brief direction の値を取り出す．
AstElemDict::RetType
AstElemDict::get_direction(
  const char* keyword,
  ClibDirection& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = _val->direction_value();
  }
  return ret;
}

// @brief timing_type の値を取り出す．
AstElemDict::RetType
AstElemDict::get_timing_type(
  const char* keyword,
  ClibTimingType& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = _val->timing_type_value();
  }
  return ret;
}

// @brief timing_sense の値を取り出す．
AstElemDict::RetType
AstElemDict::get_timing_sense(
  const char* keyword,
  ClibTimingSense& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = _val->timing_sense_value();
  }
  return ret;
}

// @brief delay_model の値を取り出す．
AstElemDict::RetType
AstElemDict::get_delay_model(
  const char* keyword,
  ClibDelayModel& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = _val->delay_model_value();
  }
  return ret;
}

// @brief float_vector の値を取り出す．
AstElemDict::RetType
AstElemDict::get_float_vector(
  const char* keyword,
  vector<double>& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    val = _val->float_vector_value();
  }
  return ret;
}

// @brief complex 形式の float_vector の値を取り出す．
AstElemDict::RetType
AstElemDict::get_complex_float_vector(
  const char* keyword,
  vector<double>& val
) const
{
  const AstValue* _val;
  auto ret = get_value(keyword, _val);
  if ( ret == OK ) {
    SizeType n = _val->complex_elem_size();
    for ( SizeType i = 0; i < n; ++ i ) {
      auto tmp = _val->complex_elem_value(i).float_vector_value();
      val.insert(val.end(), tmp.begin(), tmp.end());
    }
  }
  return ret;
}

// @brief キーワードの値を返す．
AstElemDict::RetType
AstElemDict::get_value(
  const char* keyword,
  const AstValue*& val
) const
{
  if ( count(keyword) == 0 ) {
    // 指定なし
    return NOT_FOUND;
  }

  auto& vec = at(keyword);
  if ( vec.size() > 1 ) {
    // 2回以上指定されている．
#warning "TODO: エラーメッセージ"
    cerr << keyword << " appears more than once." << endl;
    return ERROR;
  }

  val = vec[0];
  return OK;
}

END_NAMESPACE_YM_DOTLIB
