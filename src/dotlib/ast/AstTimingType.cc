
/// @file AstTimingType.cc
/// @brief AstTimingType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstMgr.h"
#include "dotlib/AstTimingType.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing_type を表す AstNode を生成する．
// @param[in] loc ファイル上の位置
// @param[in] value 値
const AstTimingType*
AstMgr::new_timing_type(const FileRegion& loc,
			ClibTimingType value)
{
  ++ mTimingTypeNum;
  void* p = mAlloc.get_memory(sizeof(AstTimingType));
  return new (p) AstTimingType(loc, value);
}


//////////////////////////////////////////////////////////////////////
// クラス AstTimingType
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] loc ファイル上の位置
// @param[in] value 値
AstTimingType::AstTimingType(const FileRegion& loc,
			     ClibTimingType value) :
  AstNode(loc),
  mValue(value)
{
}

// @brief デストラクタ
AstTimingType::~AstTimingType()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTimingType::dump(ostream& s,
		    int indent) const
{
  const char* tmp = "---";
  switch ( mValue ) {
  case ClibTimingType::Combinational:         tmp = "combinational"; break;
  case ClibTimingType::CombinationalRise:     tmp = "combinational rise"; break;
  case ClibTimingType::CombinationalFall:     tmp = "combinational fall"; break;
  case ClibTimingType::ThreeStateEnable:      tmp = "three state enable"; break;
  case ClibTimingType::ThreeStateDisable:     tmp = "three state disable"; break;
  case ClibTimingType::ThreeStateEnableRise:  tmp = "three state enable rise"; break;
  case ClibTimingType::ThreeStateEnableFall:  tmp = "three state enable fall"; break;
  case ClibTimingType::ThreeStateDisableRise: tmp = "three state disable rise"; break;
  case ClibTimingType::ThreeStateDisableFall: tmp = "three state disable fall"; break;
  case ClibTimingType::RisingEdge:            tmp = "rising edge"; break;
  case ClibTimingType::FallingEdge:           tmp = "falling edge"; break;
  case ClibTimingType::Preset:                tmp = "preset"; break;
  case ClibTimingType::Clear:                 tmp = "clear"; break;
  case ClibTimingType::HoldRising:            tmp = "hold rising"; break;
  case ClibTimingType::HoldFalling:           tmp = "hold falling"; break;
  case ClibTimingType::SetupRising:           tmp = "setup rising"; break;
  case ClibTimingType::SetupFalling:          tmp = "setup falling"; break;
  case ClibTimingType::RecoveryRising:        tmp = "recovery rising"; break;
  case ClibTimingType::RecoveryFalling:       tmp = "recovery falling"; break;
  case ClibTimingType::SkewRising:            tmp = "skew rising"; break;
  case ClibTimingType::SkewFalling:           tmp = "skew falling"; break;
  case ClibTimingType::RemovalRising:         tmp = "removal rising"; break;
  case ClibTimingType::RemovalFalling:        tmp = "removal falling"; break;
  case ClibTimingType::NonSeqSetupRising:     tmp = "non seq setup rising"; break;
  case ClibTimingType::NonSeqSetupFalling:    tmp = "non seq setup falling"; break;
  case ClibTimingType::NonSeqHoldRising:      tmp = "non seq hold rising"; break;
  case ClibTimingType::NonSeqHoldFalling:     tmp = "non seq hold falling"; break;
  case ClibTimingType::NochangeHighHigh:      tmp = "nochange high high"; break;
  case ClibTimingType::NochangeHighLow:       tmp = "nochange high low"; break;
  case ClibTimingType::NochangeLowHigh:       tmp = "nochange low high"; break;
  case ClibTimingType::NochangeLowLow:        tmp = "nochange low low"; break;
  default: break;
  }
  dump_string(s, tmp);
}

END_NAMESPACE_YM_DOTLIB
