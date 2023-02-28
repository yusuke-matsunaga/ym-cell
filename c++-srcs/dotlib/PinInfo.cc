
/// @file PinInfo.cc
/// @brief PinInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/PinInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstExpr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 内容を設定する．
void
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
  set_direction();

  switch ( mDirection ) {
  case ClibDirection::input:
    set_input_params();
    break;

  case ClibDirection::output:
    set_output_params();
    break;

  case ClibDirection::inout:
    set_input_params();
    set_output_params();
    break;

  default:
    ASSERT_NOT_REACHED;
    break;
  }
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
void
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
}

// @brief タイミングを生成する．
void
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
}

// @brief direction 属性を取り出す．
void
PinInfo::set_direction()
{
  const char* keyword{"direction"};
  if ( !get_direction(keyword, mDirection) ) {
    // direction 属性がない．
    auto label = "No 'direction' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
}

// @brief 入力ピン用のパラメータを取り出す．
void
PinInfo::set_input_params()
{
  auto ret1 = get_capacitance("capacitance", mCapacitance);
  if ( !ret1 ) {
    // capacitance が定義されていない．
    auto label = "No 'capacitance' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }

  auto ret2 = get_capacitance("rise_capacitance", mRiseCapacitance);
  auto ret3 = get_capacitance("fall_capacitance", mFallCapacitance);

  if ( ret2 && !ret3 ) {
    // fall_capacitance だけが定義されていない．
    auto label = "No 'fall_capacitance' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
  if ( !ret2 && ret3 ) {
    // rise_capacitance だけが定義されていない．
    auto label = "No 'rise_capacitance' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
  if ( !ret2 && !ret3 ) {
    // 両方定義されていない場合には capacitance の値を用いる．
    mRiseCapacitance = mCapacitance;
    mFallCapacitance = mCapacitance;
  }
}

// @brief 出力ピン用のパラメータを取り出す．
void
PinInfo::set_output_params()
{
  auto ret1 = get_capacitance("max_fanout", mMaxFanout);
  if ( !ret1 ) {
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxFanout = ClibCapacitance::infinity();
  }

  auto ret2 = get_capacitance("min_fanout", mMinFanout);
  if ( !ret2 ) {
#warning "TODO: 今は0を代入している．要確認"
    mMinFanout = ClibCapacitance{0.0};
  }

  auto ret3 = get_capacitance("max_capacitance", mMaxCapacitance);
  if ( !ret3 ) {
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxCapacitance = ClibCapacitance::infinity();
  }

  auto ret4 = get_capacitance("min_capacitance", mMinCapacitance);
  if ( !ret4 ) {
#warning "TODO: 今は0を代入している．要確認"
    mMinCapacitance = ClibCapacitance{0.0};
  }

  auto ret5 = get_time("max_transition", mMaxTransition);
  if ( !ret5 ) {
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxTransition = ClibTime::infinity();
  }

  auto ret6 = get_time("min_transition", mMinTransition);
  if ( !ret6 ) {
#warning "TODO: 今は0を代入している．要確認"
    mMinTransition = ClibTime{0.0};
  }

  auto ret7 = get_expr("function", mFunction);
  if ( !ret7 ) {
    mFunction = nullptr;
  }

  auto ret8 = get_expr("three_state", mTristate);
  if ( !ret8 ) {
    mTristate = nullptr;
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
      timing_info.set(ast_timing);
    }
  }
}

END_NAMESPACE_YM_DOTLIB
