
/// @file AstPinInfo.cc
/// @brief AstPinInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstPinInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstElemDict.h"
#include "dotlib/AstExpr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 内容を設定する．
bool
AstPinInfo::set(
  const AstValue* pin_val,
  ClibDelayModel delay_model
)
{
  // ピン名のリストを得る．
  auto& pin_header = pin_val->group_header_value();
  SizeType n = pin_header.complex_elem_size();
  mNameList.reserve(n);
  for ( SizeType i = 0; i < n; ++ i ) {
    auto& pin_name_value = pin_header.complex_elem_value(i);
    mNameList.push_back(pin_name_value.string_value());
  }

  // ピンの属性の辞書を作る．
  auto elem_dict = pin_val->gen_group_elem_dict();

  // direction を取り出す．
  if ( elem_dict.get_direction("direction", mDirection) == AstElemDict::NOT_FOUND ) {
    // direction 属性がない．
#warning "TODO: エラーメッセージ"
    cerr << "'direction' is not defined." << endl;
    return false;
  }

  bool ok{true};

  switch ( mDirection ) {
  case ClibDirection::input:
    if ( !get_input_params(elem_dict) ) {
      cerr << "X1" << endl;
      ok = false;
    }
    break;
  case ClibDirection::output:
    if ( !get_output_params(elem_dict, delay_model) ) {
      cerr << "X2" << endl;
      ok = false;
    }
    break;
  case ClibDirection::inout:
    if ( !get_input_params(elem_dict) ) {
      cerr << "X3" << endl;
      ok = false;
    }
    if ( !get_output_params(elem_dict, delay_model) ) {
      cerr << "X4" << endl;
      ok = false;
    }
    break;
  default:
    ASSERT_NOT_REACHED;
    break;
  }

  return ok;
}

BEGIN_NONAMESPACE

// AstExpr を Expr に変換する．
inline
Expr
make_expr(
  const AstExpr* ast_expr,
  const unordered_map<ShString, SizeType>& pin_map
)
{
  if ( ast_expr == nullptr ) {
    // 未定義の場合のフォールバック
    return Expr::make_invalid();
  }
  return ast_expr->to_expr(pin_map);
}

END_NONAMESPACE

// @brief ピンを生成する．
bool
AstPinInfo::add_pin(
  CiCell* cell,
  const unordered_map<ShString, SizeType>& ipin_map
) const
{
  switch ( mDirection ) {
  case ClibDirection::input:
    for ( auto name: mNameList ) {
      auto pin = cell->add_input(name, mCapacitance,
				 mRiseCapacitance, mFallCapacitance);
      ASSERT_COND( pin->input_id() == ipin_map.at(name) );
    }
    break;
  case ClibDirection::output:
    {
      auto function = make_expr(mFunction, ipin_map);
      auto tristate = make_expr(mTristate, ipin_map);
      vector<SizeType> opin_list;
      for ( auto name: mNameList ) {
	auto pin = cell->add_output(name, mMaxFanout, mMinFanout,
				    mMaxCapacitance, mMinCapacitance,
				    mMaxTransition, mMinTransition,
				    function, tristate);
	//ASSERT_COND( pin->output_id() == mOpinMap.at(name) );
	opin_list.push_back(pin->output_id());
      }
      SizeType ni = cell->input_num2();
      for ( auto& timing_info: mTimingInfoList ) {
	timing_info.add_timing(cell, function, ni, opin_list, ipin_map);
      }
    }
    break;
  case ClibDirection::inout:
    {
      auto function = make_expr(mFunction, ipin_map);
      auto tristate = make_expr(mTristate, ipin_map);
      vector<SizeType> opin_list;
      for ( auto name: mNameList ) {
	auto pin = cell->add_inout(name, mCapacitance,
				   mRiseCapacitance, mFallCapacitance,
				   mMaxFanout, mMinFanout,
				   mMaxCapacitance, mMinCapacitance,
				   mMaxTransition, mMinTransition,
				   function, tristate);
	ASSERT_COND( pin->input_id() == ipin_map.at(name) );
	//ASSERT_COND( pin->output_id() == mOpinMap.at(name) );
	opin_list.push_back(pin->output_id());
      }
      SizeType ni = cell->input_num2();
      for ( auto& timing_info: mTimingInfoList ) {
	timing_info.add_timing(cell, function, ni, opin_list, ipin_map);
      }
    }
    break;
  default:
    ASSERT_NOT_REACHED;
    break;
  }

  return true;
}

// @brief 入力ピン用のパラメータを取り出す．
//
// エラーの場合には false を返す．
bool
AstPinInfo::get_input_params(
  const AstElemDict& elem_dict
)
{
  auto ret1 = elem_dict.get_capacitance("capacitance", mCapacitance);
  if ( ret1 == AstElemDict::NOT_FOUND ) {
    // capacitance が定義されていない．
#warning "TODO: エラーメッセージ"
    cerr << "capacitance が定義されていない．" << endl;
    return false;
  }

  auto ret2 = elem_dict.get_capacitance("rise_capacitance", mRiseCapacitance);
  if ( ret2 == AstElemDict::ERROR ) {
    return false;
  }
  auto ret3 = elem_dict.get_capacitance("fall_capacitance", mFallCapacitance);
  if ( ret3 == AstElemDict::ERROR ) {
    return false;
  }

  if ( ret2 == AstElemDict::OK && ret3 == AstElemDict::NOT_FOUND ) {
    // fall_capacitance だけが定義されていない．
#warning "TODO: 未完"
    cerr << "fall_capacitance だけが定義されていない．" << endl;
    return false;
  }
  else if ( ret2 == AstElemDict::NOT_FOUND && ret3 == AstElemDict::OK ) {
    // rise_capacitance だけが定義されていない．
#warning "TODO: 未完"
    cerr << "rise_capacitance だけが定義されていない．" << endl;
    return false;
  }
  else if ( ret2 == AstElemDict::NOT_FOUND && ret3 == AstElemDict::NOT_FOUND ) {
    // 両方定義されていない場合には capacitance の値を用いる．
    mRiseCapacitance = mCapacitance;
    mFallCapacitance = mCapacitance;
  }

  return true;
}

// @brief 出力ピン用のパラメータを取り出す．
bool
AstPinInfo::get_output_params(
  const AstElemDict& elem_dict,
  ClibDelayModel delay_model
)
{
  bool ok{true};

  switch ( elem_dict.get_capacitance("max_fanout", mMaxFanout) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxFanout = ClibCapacitance::infinity();
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_capacitance("min_fanout", mMinFanout) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
#warning "TODO: 今は0を代入している．要確認"
    mMinFanout = ClibCapacitance{0.0};
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_capacitance("max_capacitance", mMaxCapacitance) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxCapacitance = ClibCapacitance::infinity();
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_capacitance("min_capacitance", mMinCapacitance) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
#warning "TODO: 今は0を代入している．要確認"
    mMinCapacitance = ClibCapacitance{0.0};
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_time("max_transition", mMaxTransition) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxTransition = ClibTime::infinity();
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_time("min_transition", mMinTransition) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
#warning "TODO: 今は0を代入している．要確認"
    mMinTransition = ClibTime{0.0};
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_expr("function", mFunction) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    mFunction = nullptr;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_expr("three_state", mTristate) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    mTristate = nullptr;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  if ( elem_dict.count("timing") > 0 ) {
    auto& vec = elem_dict.at("timing");
    SizeType n = vec.size();
    mTimingInfoList.clear();
    mTimingInfoList.resize(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      auto ast_timing = vec[i];
      if ( !mTimingInfoList[i].set(ast_timing, delay_model) ) {
	cerr << " Error in TimingInfoList[" << i << "].set()" << endl;
	ok = false;
      }
    }
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
