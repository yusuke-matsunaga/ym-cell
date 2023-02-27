
/// @file PinInfo.cc
/// @brief PinInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
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
  // ピン名のリストを得る．
  auto& pin_header = pin_val->group_header_value();
  SizeType n = pin_header.complex_elem_size();
  mNameList.reserve(n);
  for ( SizeType i = 0; i < n; ++ i ) {
    auto& pin_name_value = pin_header.complex_elem_value(i);
    mNameList.push_back(pin_name_value.string_value());
  }

  // ピンの属性の辞書を作る．
  mElemDict.set(pin_val);

  // direction を取り出す．
  if ( mElemDict.get_direction("direction", mDirection) == ElemDict::NOT_FOUND ) {
    // direction 属性がない．
#warning "TODO: エラーメッセージ"
    cerr << "'direction' is not defined." << endl;
    return false;
  }

  bool ok{true};

  switch ( mDirection ) {
  case ClibDirection::input:
    if ( !get_input_params() ) {
      cerr << "X1" << endl;
      ok = false;
    }
    break;

  case ClibDirection::output:
    if ( !get_output_params() ) {
      cerr << "X2" << endl;
      ok = false;
    }
    break;

  case ClibDirection::inout:
    if ( !get_input_params() ) {
      cerr << "X3" << endl;
      ok = false;
    }
    if ( !get_output_params() ) {
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

// @brief 入力ピン用のパラメータを取り出す．
//
// エラーの場合には false を返す．
bool
PinInfo::get_input_params()
{
  auto ret1 = mElemDict.get_capacitance("capacitance", mCapacitance);
  if ( ret1 == ElemDict::NOT_FOUND ) {
    // capacitance が定義されていない．
#warning "TODO: エラーメッセージ"
    cerr << "capacitance が定義されていない．" << endl;
    return false;
  }

  auto ret2 = mElemDict.get_capacitance("rise_capacitance", mRiseCapacitance);
  if ( ret2 == ElemDict::ERROR ) {
    return false;
  }
  auto ret3 = mElemDict.get_capacitance("fall_capacitance", mFallCapacitance);
  if ( ret3 == ElemDict::ERROR ) {
    return false;
  }

  if ( ret2 == ElemDict::OK && ret3 == ElemDict::NOT_FOUND ) {
    // fall_capacitance だけが定義されていない．
#warning "TODO: 未完"
    cerr << "fall_capacitance だけが定義されていない．" << endl;
    return false;
  }
  else if ( ret2 == ElemDict::NOT_FOUND && ret3 == ElemDict::OK ) {
    // rise_capacitance だけが定義されていない．
#warning "TODO: 未完"
    cerr << "rise_capacitance だけが定義されていない．" << endl;
    return false;
  }
  else if ( ret2 == ElemDict::NOT_FOUND && ret3 == ElemDict::NOT_FOUND ) {
    // 両方定義されていない場合には capacitance の値を用いる．
    mRiseCapacitance = mCapacitance;
    mFallCapacitance = mCapacitance;
  }

  return true;
}

// @brief 出力ピン用のパラメータを取り出す．
bool
PinInfo::get_output_params()
{
  bool ok{true};

  switch ( mElemDict.get_capacitance("max_fanout", mMaxFanout) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxFanout = ClibCapacitance::infinity();
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( mElemDict.get_capacitance("min_fanout", mMinFanout) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
#warning "TODO: 今は0を代入している．要確認"
    mMinFanout = ClibCapacitance{0.0};
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( mElemDict.get_capacitance("max_capacitance", mMaxCapacitance) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxCapacitance = ClibCapacitance::infinity();
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( mElemDict.get_capacitance("min_capacitance", mMinCapacitance) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
#warning "TODO: 今は0を代入している．要確認"
    mMinCapacitance = ClibCapacitance{0.0};
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( mElemDict.get_time("max_transition", mMaxTransition) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
#warning "TODO: 今は無限大を代入している．要確認"
    mMaxTransition = ClibTime::infinity();
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( mElemDict.get_time("min_transition", mMinTransition) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
#warning "TODO: 今は0を代入している．要確認"
    mMinTransition = ClibTime{0.0};
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( mElemDict.get_expr("function", mFunction) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
    mFunction = nullptr;
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( mElemDict.get_expr("three_state", mTristate) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
    mTristate = nullptr;
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  if ( mElemDict.count("timing") > 0 ) {
    auto& vec = mElemDict.at("timing");
    SizeType n = vec.size();
    mTimingInfoList.clear();
    mTimingInfoList.reserve(n);
    for ( SizeType i = 0; i < n; ++ i ) {
      auto ast_timing = vec[i];
      mTimingInfoList.push_back(TimingInfo{mLibraryInfo});
      auto& timing_info = mTimingInfoList.back();
      if ( !timing_info.set(ast_timing) ) {
	cerr << " Error in TimingInfoList[" << i << "].set()" << endl;
	ok = false;
      }
    }
  }

  return ok;
}

// @brief ライブラリを取り出す．
CiCellLibrary*
PinInfo::library() const
{
  return mLibraryInfo.library();
}

END_NAMESPACE_YM_DOTLIB
