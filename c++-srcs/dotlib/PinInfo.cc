
/// @file PinInfo.cc
/// @brief PinInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/PinInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstExpr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 内容を設定する．
bool
PinInfo::set(
  const AstValue* pin_val
)
{
  GroupInfo::set(pin_val);

  // ピン名のリストを得る．
  auto& pin_header = pin_val->group_header_value();
  SizeType n = pin_header.complex_elem_size();
  mNameList.reserve(n);
  for ( SizeType i = 0; i < n; ++ i ) {
    auto& pin_name_value = pin_header.complex_elem_value(i);
    mNameList.push_back(pin_name_value.string_value());
  }

  // direction を取り出す．
  if ( !set_direction() ) {
    return false;
  }

  bool ok{true};
  switch ( mDirection ) {
  case ClibDirection::input:
    if ( !set_input_params() ) {
      cerr << "X1" << endl;
      ok = false;
    }
    break;

  case ClibDirection::output:
    if ( !set_output_params() ) {
      cerr << "X2" << endl;
      ok = false;
    }
    break;

  case ClibDirection::inout:
    if ( !set_input_params() ) {
      cerr << "X3" << endl;
      ok = false;
    }
    if ( !set_output_params() ) {
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
PinInfo::add_pin(
  SizeType cell_id,
  const unordered_map<ShString, SizeType>& ipin_map
)
{
  switch ( mDirection ) {
  case ClibDirection::input:
    for ( auto name: mNameList ) {
      auto pin_id = library()->add_input(cell_id, name,
					mCapacitance,
					mRiseCapacitance,
					mFallCapacitance);
      auto pin = library()->_pin(pin_id);
      ASSERT_COND( pin->input_id() == ipin_map.at(name) );
    }
    break;

  case ClibDirection::output:
    {
      mFunctionExpr = make_expr(mFunction, ipin_map);
      auto tristate = make_expr(mTristate, ipin_map);
      for ( auto name: mNameList ) {
	auto pin_id = library()->add_output(cell_id, name,
					   mMaxFanout,
					   mMinFanout,
					   mMaxCapacitance,
					   mMinCapacitance,
					   mMaxTransition,
					   mMinTransition,
					   mFunctionExpr,
					   tristate);
	auto pin = library()->_pin(pin_id);
	mOpinList.push_back(pin->output_id());
      }
    }
    break;

  case ClibDirection::inout:
    {
      mFunctionExpr = make_expr(mFunction, ipin_map);
      auto tristate = make_expr(mTristate, ipin_map);
      for ( auto name: mNameList ) {
	auto pin_id = library()->add_inout(cell_id, name,
					  mCapacitance,
					  mRiseCapacitance,
					  mFallCapacitance,
					  mMaxFanout, mMinFanout,
					  mMaxCapacitance,
					  mMinCapacitance,
					  mMaxTransition,
					  mMinTransition,
					  mFunctionExpr,
					  tristate);
	auto pin = library()->_pin(pin_id);
	ASSERT_COND( pin->input_id() == ipin_map.at(name) );
	mOpinList.push_back(pin->output_id());
      }
    }
    break;

  default:
    ASSERT_NOT_REACHED;
    break;
  }

  return true;
}

// @brief タイミングを生成する．
bool
PinInfo::add_timing(
  SizeType cell_id,
  const unordered_map<ShString, SizeType>& ipin_map
) const
{
  auto cell = library()->_cell(cell_id);

  switch ( mDirection ) {
  case ClibDirection::input:
    break;

  case ClibDirection::output:
    {
      for ( auto& timing_info: mTimingInfoList ) {
	timing_info.add_timing(cell, mFunctionExpr, mOpinList, ipin_map);
      }
    }
    break;

  case ClibDirection::inout:
    {
      for ( auto& timing_info: mTimingInfoList ) {
	timing_info.add_timing(cell, mFunctionExpr, mOpinList, ipin_map);
      }
    }
    break;

  default:
    ASSERT_NOT_REACHED;
    break;
  }

  return true;
}

// @brief direction 属性を取り出す．
bool
PinInfo::set_direction()
{
  const char* keyword{"direction"};
  if ( get_direction(keyword, mDirection) == NOT_FOUND ) {
    // direction 属性がない．
#warning "TODO: エラーメッセージ"
    cerr << "'direction' is not defined." << endl;
    return false;
  }
  return true;
}

// @brief 入力ピン用のパラメータを取り出す．
//
// エラーの場合には false を返す．
bool
PinInfo::set_input_params()
{
  auto ret1 = get_capacitance("capacitance", mCapacitance);
  if ( ret1 == NOT_FOUND ) {
    // capacitance が定義されていない．
#warning "TODO: エラーメッセージ"
    cerr << "capacitance が定義されていない．" << endl;
    return false;
  }

  auto ret2 = get_capacitance("rise_capacitance", mRiseCapacitance);
  if ( ret2 == ERROR ) {
    return false;
  }
  auto ret3 = get_capacitance("fall_capacitance", mFallCapacitance);
  if ( ret3 == ERROR ) {
    return false;
  }

  if ( ret2 == OK && ret3 == NOT_FOUND ) {
    // fall_capacitance だけが定義されていない．
#warning "TODO: 未完"
    cerr << "fall_capacitance だけが定義されていない．" << endl;
    return false;
  }
  else if ( ret2 == NOT_FOUND && ret3 == OK ) {
    // rise_capacitance だけが定義されていない．
#warning "TODO: 未完"
    cerr << "rise_capacitance だけが定義されていない．" << endl;
    return false;
  }
  else if ( ret2 == NOT_FOUND && ret3 == NOT_FOUND ) {
    // 両方定義されていない場合には capacitance の値を用いる．
    mRiseCapacitance = mCapacitance;
    mFallCapacitance = mCapacitance;
  }

  return true;
}

// @brief 出力ピン用のパラメータを取り出す．
bool
PinInfo::set_output_params()
{
  bool ok{true};

  switch ( get_capacitance("max_fanout", mMaxFanout) ) {
  case OK:
    break;
  case NOT_FOUND:
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxFanout = ClibCapacitance::infinity();
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_capacitance("min_fanout", mMinFanout) ) {
  case OK:
    break;
  case NOT_FOUND:
#warning "TODO: 今は0を代入している．要確認"
    mMinFanout = ClibCapacitance{0.0};
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_capacitance("max_capacitance", mMaxCapacitance) ) {
  case OK:
    break;
  case NOT_FOUND:
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxCapacitance = ClibCapacitance::infinity();
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_capacitance("min_capacitance", mMinCapacitance) ) {
  case OK:
    break;
  case NOT_FOUND:
#warning "TODO: 今は0を代入している．要確認"
    mMinCapacitance = ClibCapacitance{0.0};
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_time("max_transition", mMaxTransition) ) {
  case OK:
    break;
  case NOT_FOUND:
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxTransition = ClibTime::infinity();
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_time("min_transition", mMinTransition) ) {
  case OK:
    break;
  case NOT_FOUND:
#warning "TODO: 今は0を代入している．要確認"
    mMinTransition = ClibTime{0.0};
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_expr("function", mFunction) ) {
  case OK:
    break;
  case NOT_FOUND:
    mFunction = nullptr;
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_expr("three_state", mTristate) ) {
  case OK:
    break;
  case NOT_FOUND:
    mTristate = nullptr;
    break;
  case ERROR:
    ok = false;
    break;
  }

  if ( elem_dict().count("timing") > 0 ) {
    auto& vec = elem_dict().at("timing");
    SizeType n = vec.size();
    mTimingInfoList.clear();
    mTimingInfoList.reserve(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      auto ast_timing = vec[i];
      mTimingInfoList.push_back(TimingInfo{library_info()});
      auto& timing_info = mTimingInfoList.back();
      if ( !timing_info.set(ast_timing) ) {
	cerr << " Error in TimingInfoList[" << i << "].set()" << endl;
	ok = false;
      }
    }
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
