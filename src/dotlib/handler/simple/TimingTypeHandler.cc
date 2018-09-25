
/// @file TimingTypeHandler.cc
/// @brief TimingTypeHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/TimingTypeHandler.h"
#include "dotlib/AstMgr.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TimingTypeHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingTypeHandler::TimingTypeHandler(DotlibParser& parser) :
  StrBaseHandler(parser)
{
}

// @brief デストラクタ
TimingTypeHandler::~TimingTypeHandler()
{
}

// @brief 文字列を読み込んだ時の処理
// @param[in] str 文字列
// @param[in] value_loc 文字列トークンの位置
// @retval true 正しく読み込んだ．
// @retval false エラーが起きた．
bool
TimingTypeHandler::read_str_value(const char* str,
				  const FileRegion& value_loc)
{
  ClibTimingType value;
  if ( strcmp(str, "combinational") == 0 ) {
    value = ClibTimingType::Combinational;
  }
  else if ( strcmp(str, "combinational_rise") == 0 ) {
    value = ClibTimingType::CombinationalRise;
  }
  else if ( strcmp(str, "combinational_fall") == 0 ) {
    value = ClibTimingType::CombinationalFall;
  }
  else if ( strcmp(str, "three_state_enable") == 0 ) {
    value = ClibTimingType::ThreeStateEnable;
  }
  else if ( strcmp(str, "three_state_enable_rise") == 0 ) {
    value = ClibTimingType::ThreeStateEnableRise;
  }
  else if ( strcmp(str, "three_state_enable_fall") == 0 ) {
    value = ClibTimingType::ThreeStateEnableFall;
  }
  else if ( strcmp(str, "three_state_disable") == 0 ) {
    value = ClibTimingType::ThreeStateDisable;
  }
  else if ( strcmp(str, "three_state_disable_rise") == 0 ) {
    value = ClibTimingType::ThreeStateDisableRise;
  }
  else if ( strcmp(str, "three_state_disable_fall") == 0 ) {
    value = ClibTimingType::ThreeStateDisableFall;
  }
  else if ( strcmp(str, "rising_edge") == 0 ) {
    value = ClibTimingType::RisingEdge;
  }
  else if ( strcmp(str, "falling_edge") == 0 ) {
    value = ClibTimingType::FallingEdge;
  }
  else if ( strcmp(str, "preset") == 0 ) {
    value = ClibTimingType::Preset;
  }
  else if ( strcmp(str, "clear") == 0 ) {
    value = ClibTimingType::Clear;
  }
  else if ( strcmp(str, "hold_rising") == 0 ) {
    value = ClibTimingType::HoldRising;
  }
  else if ( strcmp(str, "hold_falling") == 0 ) {
    value = ClibTimingType::HoldFalling;
  }
  else if ( strcmp(str, "setup_rising") == 0 ) {
    value = ClibTimingType::SetupRising;
  }
  else if ( strcmp(str, "setup_falling") == 0 ) {
    value = ClibTimingType::SetupFalling;
  }
  else if ( strcmp(str, "recovery_rising") == 0 ) {
    value = ClibTimingType::RecoveryRising;
  }
  else if ( strcmp(str, "recovery_falling") == 0 ) {
    value = ClibTimingType::RecoveryFalling;
  }
  else if ( strcmp(str, "skew_rising") == 0 ) {
    value = ClibTimingType::SkewRising;
  }
  else if ( strcmp(str, "skew_falling") == 0 ) {
    value = ClibTimingType::SkewFalling;
  }
  else if ( strcmp(str, "removal_rising") == 0 ) {
    value = ClibTimingType::RemovalRising;
  }
  else if ( strcmp(str, "removal_falling") == 0 ) {
    value = ClibTimingType::RemovalFalling;
  }
  else if ( strcmp(str, "non_seq_setup_rising") == 0 ) {
    value = ClibTimingType::NonSeqSetupRising;
  }
  else if ( strcmp(str, "non_seq_setup_falling") == 0 ) {
    value = ClibTimingType::NonSeqSetupFalling;
  }
  else if ( strcmp(str, "non_seq_hold_rising") == 0 ) {
    value = ClibTimingType::NonSeqHoldRising;
  }
  else if ( strcmp(str, "non_seq_hold_falling") == 0 ) {
    value = ClibTimingType::NonSeqHoldFalling;
  }
  else if ( strcmp(str, "nochange_high_high") == 0 ) {
    value = ClibTimingType::NochangeHighHigh;
  }
  else if ( strcmp(str, "nochange_high_low") == 0 ) {
    value = ClibTimingType::NochangeHighLow;
  }
  else if ( strcmp(str, "nochange_low_high") == 0 ) {
    value = ClibTimingType::NochangeLowHigh;
  }
  else if ( strcmp(str, "nochange_low_low") == 0 ) {
    value = ClibTimingType::NochangeLowLow;
  }
  else {
    mValue = nullptr;
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. Illegal string for timing type.");
    return false;
  }

  mValue = mgr().new_timing_type(value_loc, value);

  return true;
}

END_NAMESPACE_YM_DOTLIB
