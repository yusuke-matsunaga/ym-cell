
/// @file TimingInfo.cc
/// @brief TimingInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2023 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/TimingInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstExpr.h"
#include "ci/CiCell.h"
#include "ym/TvFunc.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TimingInfo
//////////////////////////////////////////////////////////////////////

// @brief 内容を設定する．
void
TimingInfo::set(
  const AstValue* timing_val
)
{
  GroupInfo::set(timing_val);

  mDelayModel = library()->delay_model();

  // 名前を得る．
  auto& header = timing_val->group_header_value();
  SizeType n = header.complex_elem_size();
  ASSERT_COND( n <= 1 );
  if ( n == 1 ) {
    mName = header.complex_elem_value(0).string_value();
  }

  // 共通なパラメータの取得
  set_timing_common_params();

  switch ( mDelayModel ) {
  case ClibDelayModel::generic_cmos:
    set_timing_generic_params();
    break;

  case ClibDelayModel::table_lookup:
    mLutType = set_timing_table_lookup_params();
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
}

// @brief タイミング情報を作る．
void
TimingInfo::add_timing(
  CiCell* cell,
  const Expr& function_expr,
  const Expr& tristate_expr,
  const vector<SizeType>& opin_list,
  const unordered_map<ShString, SizeType>& ipin_map
) const
{
  auto when = Expr::make_one();
  if ( mWhen != nullptr ) {
    when = mWhen->to_expr(ipin_map);
  }

  CiTiming* timing;
  switch ( mDelayModel ) {
  case ClibDelayModel::generic_cmos:
    timing = cell->add_timing_generic(mTimingType, when,
				      mIntrinsicRise, mIntrinsicFall,
				      mSlopeRise, mSlopeFall,
				      mRiseResistance, mFallResistance);
    break;

  case ClibDelayModel::table_lookup:
    switch ( mLutType ) {
    case 1:
      {
	auto cr_lut = mCellRise.gen_lut();
	auto cf_lut = mCellFall.gen_lut();
	auto rt_lut = mRiseTransition.gen_lut();
	auto ft_lut = mFallTransition.gen_lut();
	timing = cell->add_timing_lut1(mTimingType, when,
				       std::move(cr_lut),
				       std::move(cf_lut),
				       std::move(rt_lut),
				       std::move(ft_lut));
      }
      break;
    case 2:
      {
	auto rt_lut = mRiseTransition.gen_lut();
	auto ft_lut = mFallTransition.gen_lut();
	auto rp_lut = mRisePropagation.gen_lut();
	auto fp_lut = mFallPropagation.gen_lut();
	timing = cell->add_timing_lut2(mTimingType, when,
				       std::move(rt_lut),
				       std::move(ft_lut),
				       std::move(rp_lut),
				       std::move(fp_lut));
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
  SizeType ni = cell->input2_num();
  TvFunc function{ni};
  TvFunc tristate{ni};
  switch ( mTimingType ) {
  case ClibTimingType::combinational:
  case ClibTimingType::combinational_rise:
    function = function_expr.make_tv(ni);
    break;

  case ClibTimingType::combinational_fall:
    function = ~function_expr.make_tv(ni);
    break;

  case ClibTimingType::three_state_enable:
  case ClibTimingType::three_state_enable_rise:
  case ClibTimingType::three_state_disable:
  case ClibTimingType::three_state_disable_rise:
    tristate = tristate_expr.make_tv(ni);
    break;

  case ClibTimingType::three_state_enable_fall:
  case ClibTimingType::three_state_disable_fall:
    tristate = ~tristate_expr.make_tv(ni);
    break;

  default:
    break;
  }

  // タイミングマップの設定
  vector<SizeType> ipin_list;
  ipin_list.reserve(mRelatedPin.size());
  for ( auto name: mRelatedPin ) {
    ASSERT_COND( ipin_map.count(name) > 0 );
    auto id = ipin_map.at(name);
    ipin_list.push_back(id);
  }

  // timing_sense の抽出
  // TODO: いろいろ確かめる必要がある．
  for ( auto opin: opin_list ) {
    for ( auto ipin: ipin_list ) {
      bool p_unate{false};
      bool n_unate{false};
      if ( mTimingType == ClibTimingType::combinational ) {
	auto p_func = function.cofactor(ipin, false);
	auto n_func = function.cofactor(ipin, true);
	auto sense = mTimingSense;
	if ( p_func && ~n_func ) {
	  p_unate = true;
	}
	if ( ~p_func && n_func ) {
	  n_unate = true;
	}
      }
      else if ( mTimingType == ClibTimingType::three_state_enable ||
		mTimingType == ClibTimingType::three_state_disable ) {
	auto p_func = tristate.cofactor(ipin, false);
	auto n_func = tristate.cofactor(ipin, true);
	auto sense = mTimingSense;
	if ( p_func && ~n_func ) {
	  p_unate = true;
	}
	if ( ~p_func && n_func ) {
	  n_unate = true;
	}
      }
      else if ( mTimingType == ClibTimingType::rising_edge ||
		mTimingType == ClibTimingType::falling_edge ) {
	// クロックと出力値の rise/fall は無関係
	p_unate = true;
	n_unate = true;
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
	cell->set_timing(ipin, opin, ClibTimingSense::positive_unate, timing);
      }
      if ( n_unate ) {
	cell->set_timing(ipin, opin, ClibTimingSense::negative_unate, timing);
      }
    }
  }
}

// @brief タイミング情報の共通なパラメータを得る．
void
TimingInfo::set_timing_common_params()
{
  if ( !get_timing_type("timing_type", mTimingType) ) {
    // 省略時は combinational を指定する．要確認
    mTimingType = ClibTimingType::combinational;
  }

  if ( !get_expr("when", mWhen) ) {
    mWhen = nullptr;
  }

  if ( !get_timing_sense("timing_sense", mTimingSense) ) {
    mTimingSense = ClibTimingSense::none;
  }

  const char* keyword{"related_pin"};
  if ( elem_dict().count(keyword) == 0 ) {
    auto label = "No 'related_pin' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
  auto& vec = elem_dict().at(keyword);
  mRelatedPin.clear();
  mRelatedPin.reserve(vec.size());
  for ( auto v: vec ) {
    auto name = v->string_value();
    mRelatedPin.push_back(name);
  }
}

// @brief generic タイプのタイミング情報のパラメータを得る．
void
TimingInfo::set_timing_generic_params()
{
  if ( !get_time("intrinsic_rise", mIntrinsicRise) ) {
    auto label = "No 'intrinsic_rise' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
  if ( !get_time("intrinsic_fall", mIntrinsicFall) ) {
    auto label = "No 'intrinsic_fall' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
  if ( !get_time("slope_rise", mSlopeRise) ) {
    auto label = "No 'slope_rise' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
  if ( !get_time("slope_fall", mSlopeFall) ) {
    auto label = "No 'slope_fall' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
  if ( !get_resistance("rise_resistance", mRiseResistance) ) {
    auto label = "No 'rise_resistance' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
  if ( !get_resistance("fall_resistance", mFallResistance) ) {
    auto label = "No 'fall_resistance' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
}

// @brief table-lookup タイプのタイミング情報のパラメータを得る．
int
TimingInfo::set_timing_table_lookup_params()
{
  auto rt_val = get_value("rise_transition");
  auto ft_val = get_value("fall_transition");
  if ( rt_val == nullptr && ft_val == nullptr ) {
    // rise|fall_transition のどちらかは必須
    auto label = ": Neigther 'rise_transition' nor 'fall_transition' is not defined.";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }

  if ( rt_val ) {
    mRiseTransition.set(rt_val);
  }
  if ( ft_val ) {
    mFallTransition.set(ft_val);
  }

  auto cr_val = get_value("cell_rise");
  auto cf_val = get_value("cell_fall");

  auto rp_val = get_value("rise_propagation");
  auto fp_val = get_value("fall_propagation");

  int type = 0;
  if ( cr_val ) {
    if ( rp_val ) {
      // cell_rise と rise_propagation は同時に指定できない．
      auto label = "'cell_rise' and 'rise_propagation' are mutually exclusive.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc(),
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      label);
      throw std::invalid_argument{label};
    }
    mCellRise.set(cr_val);
    type = 1;
  }
  else if ( rp_val ) {
    mRisePropagation.set(rp_val);
    type = 2;
  }

  if ( cf_val ) {
    if ( fp_val ) {
      // cell_fall と fall_propagation は同時に指定できない．
      auto label = "'cell_fall' and 'fall_propagation' are mutually exclusive.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc(),
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      label);
      throw std::invalid_argument{label};
    }
    if ( type == 2 ) {
      auto label = "'cell_fall' and 'rise_propagation' are mutually exclusive.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc(),
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      label);
      throw std::invalid_argument{label};
    }
    mCellFall.set(cf_val);
    type = 1;
  }
  else if ( fp_val ) {
    if ( type == 1 ) {
      auto label = "'cell_rise' and 'fall_propagation' are mutually exclusive.";
      MsgMgr::put_msg(__FILE__, __LINE__,
		      loc(),
		      MsgType::Error,
		      "DOTLIB_PARSER",
		      label);
      throw std::invalid_argument{label};
    }
    mFallPropagation.set(fp_val);
    type = 2;
  }

  return type;
}

END_NAMESPACE_YM_DOTLIB
