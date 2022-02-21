
/// @file AstTimingInfo.cc
/// @brief AstTimingInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstTimingInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstElemDict.h"
#include "dotlib/AstExpr.h"
#include "ym/TvFunc.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstTimingInfo
//////////////////////////////////////////////////////////////////////

// @brief 内容を設定する．
bool
AstTimingInfo::set(
  const AstValue* timing_val,
  ClibDelayModel delay_model
)
{
  mDelayModel = delay_model;

  // 名前を得る．
  auto& header = timing_val->group_header_value();
  SizeType n = header.complex_elem_size();
  ASSERT_COND( n <= 1 );
  if ( n == 1 ) {
    mName = header.complex_elem_value(0).string_value();
  }

  // 属性の辞書を作る．
  auto elem_dict = timing_val->gen_group_elem_dict();

  bool ok{true};

  // 共通なパラメータの取得
  if ( !get_timing_common_params(elem_dict) ) {
    ok = false;
  }

  switch ( mDelayModel ) {
  case ClibDelayModel::generic_cmos:
    if ( !get_timing_generic_params(elem_dict) ) {
      ok = false;
    }
    break;

  case ClibDelayModel::table_lookup:
    mLutType = get_timing_table_lookup_params(elem_dict);
    if ( mLutType == 0 ) {
      ok = false;
    }
    break;

  case ClibDelayModel::piecewise_cmos:
#warning "TODO: piecewise モデル"
    ok = false;
    break;

  case ClibDelayModel::cmos2:
#warning "TODO: cmos2 モデル"
    ok = false;
    break;

  case ClibDelayModel::dcm:
#warning "TODO: dcm モデル"
    ok = false;
    break;

  case ClibDelayModel::polynomial:
#warning "TODO: polynomial モデル"
    ok = false;
    break;

  case ClibDelayModel::none:
    ASSERT_NOT_REACHED;
    break;
  }

  return ok;
}

// @brief タイミング情報を作る．
bool
AstTimingInfo::add_timing(
  CiCell* cell,
  const Expr& function_expr,
  SizeType ni,
  const vector<SizeType>& opin_list,
  const unordered_map<ShString, SizeType>& ipin_map
) const
{
  Expr when{Expr::make_one()};
  if ( mWhen != nullptr ) {
    when = mWhen->to_expr(ipin_map);
  }
  auto library = cell->library();

  SizeType tid;
  switch ( mDelayModel ) {
  case ClibDelayModel::generic_cmos:
    tid = cell->add_timing_generic(mTimingType, when,
				   mIntrinsicRise, mIntrinsicFall,
				   mSlopeRise, mSlopeFall,
				   mRiseResistance, mFallResistance);
    break;

  case ClibDelayModel::table_lookup:
    switch ( mLutType ) {
    case 1:
      {
	auto cr_lut = mCellRise.gen_lut(library);
	auto cf_lut = mCellFall.gen_lut(library);
	auto rt_lut = mRiseTransition.gen_lut(library);
	auto ft_lut = mFallTransition.gen_lut(library);
	tid = cell->add_timing_lut1(mTimingType, when,
				    cr_lut, cf_lut,
				    rt_lut, ft_lut);
      }
      break;
    case 2:
      {
	auto rt_lut = mRiseTransition.gen_lut(library);
	auto ft_lut = mFallTransition.gen_lut(library);
	auto rp_lut = mRisePropagation.gen_lut(library);
	auto fp_lut = mFallPropagation.gen_lut(library);
	tid = cell->add_timing_lut2(mTimingType, when,
				    rt_lut, ft_lut,
				    rp_lut, fp_lut);
      }
      break;
    default:
      ASSERT_NOT_REACHED;
      break;
    }
    break;

  case ClibDelayModel::piecewise_cmos:
#warning "TODO: piecewise モデル"
    break;

  case ClibDelayModel::cmos2:
#warning "TODO: cmos2 モデル"
    break;

  case ClibDelayModel::dcm:
#warning "TODO: dcm モデル"
    break;

  case ClibDelayModel::polynomial:
#warning "TODO: polynomial モデル"
    break;

  case ClibDelayModel::none:
    ASSERT_NOT_REACHED;
    break;
  }

  // timing_type が combinational の場合には実際の論理関数を調べて
  // timing_sense を設定する．
  TvFunc function{ni};
  if ( mTimingType == ClibTimingType::combinational ) {
    function = function_expr.make_tv(ni);
  }

  // タイミングマップの設定
  vector<SizeType> ipin_list;
  ipin_list.reserve(mRelatedPin.size());
  for ( auto name: mRelatedPin ) {
    ASSERT_COND( ipin_map.count(name) > 0 );
    auto id = ipin_map.at(name);
    ipin_list.push_back(id);
  }

  for ( auto opin: opin_list ) {
    for ( auto ipin: ipin_list ) {
      bool p_unate{false};
      bool n_unate{false};
      if ( mTimingType == ClibTimingType::combinational ) {
	auto p_func = function.cofactor(VarId{ipin}, false);
	auto n_func = function.cofactor(VarId{ipin}, true);
	auto sense = mTimingSense;
	if ( p_func && ~n_func ) {
	  p_unate = true;
	}
	if ( ~p_func && n_func ) {
	  n_unate = true;
	}
      }
      else {
	if ( mTimingSense == ClibTimingSense::positive_unate ||
	     mTimingSense == ClibTimingSense::non_unate ) {
	  p_unate = true;
	}
	if ( mTimingSense == ClibTimingSense::negative_unate ||
	     mTimingSense == ClibTimingSense::non_unate ) {
	  n_unate = true;
	}
      }
      if ( p_unate ) {
	cell->set_timing(ipin, opin, ClibTimingSense::positive_unate, tid);
      }
      if ( n_unate ) {
	cell->set_timing(ipin, opin, ClibTimingSense::negative_unate, tid);
      }
    }
  }

  return true;
}

// @brief タイミング情報の共通なパラメータを得る．
bool
AstTimingInfo::get_timing_common_params(
  const AstElemDict& elem_dict
)
{
  bool ok{true};
  switch ( elem_dict.get_timing_type("timing_type", mTimingType) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    // 省略時は combinational を指定する．要確認
    mTimingType = ClibTimingType::combinational;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_expr("when", mWhen) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    mWhen = nullptr;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  if ( elem_dict.get_timing_sense("timing_sense", mTimingSense) == AstElemDict::ERROR ) {
    ok = false;
  }

  if ( elem_dict.count("related_pin") == 0 ) {
#warning "TODO: エラーメッセージ"
    cerr << "related_pin がない．" << endl;
    ok = false;
  }
  else {
    auto& vec = elem_dict.at("related_pin");
    mRelatedPin.clear();
    mRelatedPin.reserve(vec.size());
    for ( auto v: vec ) {
      auto name = v->string_value();
      mRelatedPin.push_back(name);
    }
  }

  return ok;
}

/// @brief generic タイプのタイミング情報のパラメータを得る．
bool
AstTimingInfo::get_timing_generic_params(
  const AstElemDict& elem_dict
)
{
  bool ok{true};
  if ( elem_dict.get_time("intrinsic_rise", mIntrinsicRise) != AstElemDict::OK ) {
    cerr << "No intrinsic_rise definition" << endl;
    ok = false;
  }
  if ( elem_dict.get_time("intrinsic_fall", mIntrinsicFall) != AstElemDict::OK ) {
    cerr << "No intrinsic_fall definition" << endl;
    ok = false;
  }
  if ( elem_dict.get_time("slope_rise", mSlopeRise) != AstElemDict::OK ) {
    cerr << "No slope_rise definition" << endl;
    ok = false;
  }
  if ( elem_dict.get_time("slope_fall", mSlopeFall) != AstElemDict::OK ) {
    cerr << "No slope_fall definition" << endl;
    ok = false;
  }
  if ( elem_dict.get_resistance("rise_resistance", mRiseResistance) != AstElemDict::OK ) {
    cerr << "No rise_resistance definition" << endl;
    ok = false;
  }
  if ( elem_dict.get_resistance("fall_resistance", mFallResistance) != AstElemDict::OK ) {
    cerr << "No fall_resistance definition" << endl;
    ok = false;
  }
  return ok;
}

// @brief table-lookup タイプのタイミング情報のパラメータを得る．
int
AstTimingInfo::get_timing_table_lookup_params(
  const AstElemDict& elem_dict
)
{
  const AstValue* rt_val;
  const AstValue* ft_val;
  auto rt_ret = elem_dict.get_value("rise_transition", rt_val);
  auto ft_ret = elem_dict.get_value("fall_transition", ft_val);
  if ( rt_ret == AstElemDict::ERROR || ft_ret == AstElemDict::ERROR ) {
    return 0;
  }
  if ( rt_ret == AstElemDict::NOT_FOUND && ft_ret == AstElemDict::NOT_FOUND ) {
    // rise|fall_transition は必須
#warning "TODO: メッセージ"
    cerr << "Neigther rise_transition nor fall_transition is not defined." << endl;
    return 0;
  }
  if ( rt_ret == AstElemDict::OK && !mRiseTransition.set(rt_val) ) {
#warning "TODO: メッセージ"
    cerr << "Error in rise_transition" << endl;
    return 0;
  }
  if ( ft_ret == AstElemDict::OK && !mFallTransition.set(ft_val) ) {
#warning "TODO: メッセージ"
    cerr << "Error in fall_transition" << endl;
    return 0;
  }

  const AstValue* cr_val;
  const AstValue* cf_val;
  auto cr_ret = elem_dict.get_value("cell_rise", cr_val);
  auto cf_ret = elem_dict.get_value("cell_fall", cf_val);
  if ( cr_ret == AstElemDict::ERROR || cf_ret == AstElemDict::ERROR ) {
#warning "TODO: メッセージ"
    return 0;
  }

  const AstValue* rp_val;
  const AstValue* fp_val;
  auto rp_ret = elem_dict.get_value("rise_propagation", rp_val);
  auto fp_ret = elem_dict.get_value("fall_propagation", fp_val);
  if ( rp_ret == AstElemDict::ERROR || fp_ret == AstElemDict::ERROR ) {
    return 0;
  }

  int type = 0;
  if ( cr_ret == AstElemDict::OK ) {
    if ( rp_ret == AstElemDict::OK ) {
      // cell_rise と rise_propagation は同時に指定できない．
#warning "TODO: メッセージ"
      cerr << "cell_rise and rise_propagation are mutually exclusive." << endl;
      return 0;
    }
    else {
      if ( !mCellRise.set(cr_val) ) {
#warning "TODO: メッセージ"
	cerr << "Error in cell_rise" << endl;
	return 0;
      }
      type = 1;
    }
  }
  else if ( rp_ret == AstElemDict::OK ) {
    if ( !mRisePropagation.set(rp_val) ) {
      cerr << "Error in rise_propagation" << endl;
      return 0;
    }
    type = 2;
  }

  if ( cf_ret == AstElemDict::OK ) {
    if ( fp_ret == AstElemDict::OK ) {
      // cell_fall と fall_propagation は同時に指定できない．
#warning "TODO: メッセージ"
      cerr << "cell_fall and fall_propagation are mutually exclusive." << endl;
      return 0;
    }
    else {
      if ( type == 2 ) {
	cerr << "cell_fall and rise_propagation are mutually exclusive." << endl;
	return 0;
      }
      if ( !mCellFall.set(cf_val) ) {
#warning "TODO: メッセージ"
	cerr << "Error in cell_fall" << endl;
	return 0;
      }
      type = 1;
    }
  }
  else if ( fp_ret == AstElemDict::OK ) {
    if ( type == 1 ) {
      cerr << "cell_rise and fall_propagation are mutually exclusive." << endl;
      return 0;
    }
    if ( !mFallPropagation.set(fp_val) ) {
      cerr << "Error in fall_propagation" << endl;
      return 0;
    }
    type = 2;
  }

  return type;
}

END_NAMESPACE_YM_DOTLIB
