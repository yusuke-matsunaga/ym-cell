
/// @file AstTiming.cc
/// @brief AstTiming の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AstMgr.h"
#include "dotlib/AstTiming.h"
#include "dotlib/StrListHandler.h"
#include "dotlib/TimingHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing を表す AstNode を生成する．
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダのハンドラ
// @param[in] group グループ本体のハンドラ
const AstTiming*
AstMgr::new_timing(const FileRegion& attr_loc,
		   const StrListHandler& header,
		   const TimingHandler& group)
{
  void* p = mAlloc.get_memory(sizeof(AstTiming));
  return new (p) AstTiming(attr_loc, header, group, mAlloc);
}


//////////////////////////////////////////////////////////////////////
// クラス AstTiming
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] attr_loc 属性のファイル上の位置
// @param[in] header ヘッダのハンドラ
// @param[in] group グループ本体のハンドラ
// @param[in] alloc メモリアロケータ
AstTiming::AstTiming(const FileRegion& attr_loc,
		     const StrListHandler& header,
		     const TimingHandler& group,
		     Alloc& alloc) :
  AstNode(FileRegion{attr_loc, group.group_loc()}),
  mRelatedPin{group.mRelatedPin},
  mRelatedBusPins{group.mRelatedBusPins},
  mRelatedBusEquivalent{group.mRelatedBusEquivalent},
  mTimingSense{group.mTimingSense},
  mTimingType{group.mTimingType},
  mWhen{group.mWhen},
  mWhenStart{group.mWhenStart},
  mWhenEnd{group.mWhenEnd},
  mRiseResistance{group.mRiseResistance},
  mFallResistance{group.mFallResistance},
  mIntrinsicRise{group.mIntrinsicRise},
  mIntrinsicFall{group.mIntrinsicFall},
  mSlopeRise{group.mSlopeRise},
  mSlopeFall{group.mSlopeFall},
  mRiseDelayIntercept{group.mRiseDelayIntercept, alloc},
  mRisePinResistance{group.mRisePinResistance, alloc},
  mFallDelayIntercept{group.mFallDelayIntercept, alloc},
  mFallPinResistance{group.mRisePinResistance, alloc},
  mCellDegradation{group.mCellDegradation},
  mCellRise{group.mCellRise},
  mCellFall{group.mCellFall},
  mCompactCCSRise{group.mCompactCCSRise},
  mCompactCCSFall{group.mCompactCCSFall},
  mRiseConstraint{group.mRiseConstraint},
  mFallConstraint{group.mFallConstraint},
  mRisePropagation{group.mRisePropagation},
  mFallPropagation{group.mFallPropagation},
  mRiseTransition{group.mRiseTransition},
  mFallTransition{group.mFallTransition},
  mRetainingRise{group.mRetainingRise},
  mRetainingFall{group.mRetainingFall},
  mRetainRiseSlew{group.mRetainRiseSlew},
  mRetainFallSlew{group.mRetainFallSlew}
{
}

// @brief デストラクタ
AstTiming::~AstTiming()
{
}

// @brief 内容をストリーム出力する．
// @param[in] s 出力先のストリーム
// @param[in] indent インデント量
void
AstTiming::dump(ostream& s,
		   int indent) const
{
#warning"TODO: 未実装"
}

END_NAMESPACE_YM_DOTLIB
