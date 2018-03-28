
/// @file TimingTypeHandler.cc
/// @brief TimingTypeHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "HandlerFactory.h"
#include "TimingTypeHandler.h"
#include "DotlibParser.h"
#include "AstMgr.h"
#include "AstTimingType.h"
#include "TokenType.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'timing type' 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_timing_type(DotlibParser& parser)
{
  return new TimingTypeHandler(parser);
}

//////////////////////////////////////////////////////////////////////
// クラス TimingTypeHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingTypeHandler::TimingTypeHandler(DotlibParser& parser) :
  SimpleHandler(parser, false)
{
}

// @brief デストラクタ
TimingTypeHandler::~TimingTypeHandler()
{
}

// @brief 値を読み込む．
AstNode*
TimingTypeHandler::read_value()
{
  FileRegion loc;
  TokenType value_type = parser().read_token(loc, false);
  if ( value_type != TokenType::SYMBOL ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. timing type value is expected.");
    return nullptr;
  }
  const char* str = parser().cur_string();
  ClibTimingType value;
  if ( strcmp(str, "combinational") == 0 ) {
    value = kClibTimingCombinational;
  }
  else if ( strcmp(str, "combinational_rise") == 0 ) {
    value = kClibTimingCombinationalRise;
  }
  else if ( strcmp(str, "combinational_fall") == 0 ) {
    value = kClibTimingCombinationalFall;
  }
  else if ( strcmp(str, "three_state_enable") == 0 ) {
    value = kClibTimingThreeStateEnable;
  }
  else if ( strcmp(str, "three_state_enable_rise") == 0 ) {
    value = kClibTimingThreeStateEnableRise;
  }
  else if ( strcmp(str, "three_state_enable_fall") == 0 ) {
    value = kClibTimingThreeStateEnableFall;
  }
  else if ( strcmp(str, "three_state_disable") == 0 ) {
    value = kClibTimingThreeStateDisable;
  }
  else if ( strcmp(str, "three_state_disable_rise") == 0 ) {
    value = kClibTimingThreeStateDisableRise;
  }
  else if ( strcmp(str, "three_state_disable_fall") == 0 ) {
    value = kClibTimingThreeStateDisableFall;
  }
  else if ( strcmp(str, "rising_edge") == 0 ) {
    value = kClibTimingRisingEdge;
  }
  else if ( strcmp(str, "falling_edge") == 0 ) {
    value = kClibTimingFallingEdge;
  }
  else if ( strcmp(str, "preset") == 0 ) {
    value = kClibTimingPreset;
  }
  else if ( strcmp(str, "clear") == 0 ) {
    value = kClibTimingClear;
  }
  else if ( strcmp(str, "hold_rising") == 0 ) {
    value = kClibTimingHoldRising;
  }
  else if ( strcmp(str, "hold_falling") == 0 ) {
    value = kClibTimingHoldFalling;
  }
  else if ( strcmp(str, "setup_rising") == 0 ) {
    value = kClibTimingSetupRising;
  }
  else if ( strcmp(str, "setup_falling") == 0 ) {
    value = kClibTimingSetupFalling;
  }
  else if ( strcmp(str, "recovery_rising") == 0 ) {
    value = kClibTimingRecoveryRising;
  }
  else if ( strcmp(str, "recovery_falling") == 0 ) {
    value = kClibTimingRecoveryFalling;
  }
  else if ( strcmp(str, "skew_rising") == 0 ) {
    value = kClibTimingSkewRising;
  }
  else if ( strcmp(str, "skew_falling") == 0 ) {
    value = kClibTimingSkewFalling;
  }
  else if ( strcmp(str, "removal_rising") == 0 ) {
    value = kClibTimingRemovalRising;
  }
  else if ( strcmp(str, "removal_falling") == 0 ) {
    value = kClibTimingRemovalFalling;
  }
  else if ( strcmp(str, "non_seq_setup_rising") == 0 ) {
    value = kClibTimingNonSeqSetupRising;
  }
  else if ( strcmp(str, "non_seq_setup_falling") == 0 ) {
    value = kClibTimingNonSeqSetupFalling;
  }
  else if ( strcmp(str, "non_seq_hold_rising") == 0 ) {
    value = kClibTimingNonSeqHoldRising;
  }
  else if ( strcmp(str, "non_seq_hold_falling") == 0 ) {
    value = kClibTimingNonSeqHoldFalling;
  }
  else if ( strcmp(str, "nochange_high_high") == 0 ) {
    value = kClibTimingNochangeHighHigh;
  }
  else if ( strcmp(str, "nochange_high_low") == 0 ) {
    value = kClibTimingNochangeHighLow;
  }
  else if ( strcmp(str, "nochange_low_high") == 0 ) {
    value = kClibTimingNochangeLowHigh;
  }
  else if ( strcmp(str, "nochange_low_low") == 0 ) {
    value = kClibTimingNochangeLowLow;
  }
  else {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error. Illegal string for timing type.");
    return nullptr;
  }

  return mgr().new_timing_type(loc, value);
}

END_NAMESPACE_YM_DOTLIB
