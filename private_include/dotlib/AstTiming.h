#ifndef ASTTIMING_H
#define ASTTIMING_H

/// @file AstTiming.h
/// @brief DolibTiming のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2012, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"
#include "AstNode.h"
#include "AstArray.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class AstTiming AstTiming.h "AstTiming.h"
/// @brief タイミング情報を表すクラス
//////////////////////////////////////////////////////////////////////
class AstTiming :
  public AstNode
{
public:

  /// @brief コンストラクタ
  AstTiming(const FileRegion& attr_loc,   ///< [in] 属性のファイル上の位置
	    const StrListHandler& header, ///< [in] ヘッダを読み込んだハンドラ
	    const TimingHandler& group);  ///< [in] グループ本体を読み込んだハンドラ

  /// @brief デストラクタ
  ~AstTiming();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 名前を返す．
  const AstString*
  name() const;

  /// @brief "related_pin" を返す．
  const AstString*
  related_pin() const
  {
    return mRelatedPin;
  }

  /// @brief "related_bus_pins" を返す．
  const AstString*
  related_bus_pins() const
  {
    return mRelatedBusPins;
  }

  /// @brief "related_bus_equivalent" を返す．
  const AstString*
  related_bus_equivalent() const
  {
    return mRelatedBusEquivalent;
  }

  /// @brief "timing_sense" を返す．
  const AstTimingSense*
  timing_sense() const
  {
    return mTimingSense;
  }

  /// @brief "timing_type" を返す．
  const AstTimingType*
  timing_type() const
  {
    return mTimingType;
  }

  /// @brief "when" を返す．
  const AstExpr*
  when() const
  {
    return mWhen;
  }

  /// @brief "when_start" を返す．
  const AstExpr*
  when_start() const
  {
    return mWhenStart;
  }

  /// @brief "when_end" を返す．
  const AstExpr*
  when_end() const
  {
    return mWhenEnd;
  }

  /// @brief "rise_resistance" を返す．
  const AstFloat*
  rise_resistance() const
  {
    return mRiseResistance;
  }

  /// @brief "fall_resistance" を返す．
  const AstFloat*
  fall_resistance() const
  {
    return mFallResistance;
  }

  /// @brief "intrinsic_rise" を返す．
  const AstFloat*
  intrinsic_rise() const
  {
    return mIntrinsicRise;
  }

  /// @brief "intrinsic_fall" を返す．
  const AstFloat*
  intrinsic_fall() const
  {
    return mIntrinsicFall;
  }

  /// @brief "slope_rise" を返す．
  const AstFloat*
  slope_rise() const
  {
    return mSlopeRise;
  }

  /// @brief "slope_fall" を返す．
  const AstFloat*
  slope_fall() const
  {
    return mSlopeFall;
  }

  /// @brief "rise_delay_intercept" を返す．
  AstArray<const AstIntFloat*>
  rise_delay_intercept() const
  {
    return mRiseDelayIntercept;
  }

  /// @brief "fall_delay_intercept" を返す．
  AstArray<const AstIntFloat*>
  fall_delay_intercept() const
  {
    return mFallDelayIntercept;
  }

  /// @brief "rise_pin_resistance" を返す．
  AstArray<const AstIntFloat*>
  rise_pin_resistance() const
  {
    return mRisePinResistance;
  }

  /// @brief "fall_pin_resistance" を返す．
  AstArray<const AstIntFloat*>
  fall_pin_resistance() const
  {
    return mFallPinResistance;
  }

  /// @brief "cell_degradation" を返す．
  const AstCellDegradation*
  cell_degradation() const
  {
    return mCellDegradation;
  }

  /// @brief "cell_rise" を返す．
  const AstLut*
  cell_rise() const
  {
    return mCellRise;
  }

  /// @brief "cell_fall" を返す．
  const AstLut*
  cell_fall() const
  {
    return mCellFall;
  }

  /// @brief "compact_ccs_rise" を返す．
  const AstCCS*
  compact_ccs_rise() const;

  /// @brief "compact_ccs_rise" を返す．
  const AstCCS*
  compact_ccs_fall() const;

  /// @brief "rise_constraint" を返す．
  const AstLut*
  rise_constraint() const
  {
    return mRiseConstraint;
  }

  /// @brief "fall_constraint" を返す．
  const AstLut*
  fall_constraint() const
  {
    return mFallConstraint;
  }

  /// @brief "rise_propagation" を返す．
  const AstLut*
  rise_propagation() const
  {
    return mRisePropagation;
  }

  /// @brief "fall_propagation" を返す．
  const AstLut*
  fall_propagation() const
  {
    return mFallPropagation;
  }

  /// @brief "rise_transition" を返す．
  const AstLut*
  rise_transition() const
  {
    return mRiseTransition;
  }

  /// @brief "fall_transition" を返す．
  const AstLut*
  fall_transition() const
  {
    return mFallTransition;
  }

  /// @brief "retaining_rise" を返す．
  const AstLut*
  retaining_rise() const
  {
    return mRetainingRise;
  }

  /// @brief "retaining_fall" を返す．
  const AstLut*
  retaining_fall() const
  {
    return mRetainingFall;
  }

  /// @brief "retain_rise_slew" を返す．
  const AstLut*
  retain_rise_slew() const
  {
    return mRetainRiseSlew;
  }

  /// @brief "retain_fall_slew" を返す．
  const AstLut*
  retain_fall_slew() const
  {
    return mRetainFallSlew;
  }

  /// @brief 内容をストリーム出力する．
  void
  dump(ostream& s,     ///< [in] 出力先のストリーム
       int indent = 0) ///< [in] インデント量
    const override;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 名前
  const AstString* mName;

  // related_pin
  const AstString* mRelatedPin;

  // related_bus_pins
  const AstString* mRelatedBusPins;

  // related_bus_equivalent
  const AstString* mRelatedBusEquivalent;

  // timing_sense
  const AstTimingSense* mTimingSense;

  // timing_type
  const AstTimingType* mTimingType;

  // when
  const AstExpr* mWhen;

  // when_start
  const AstExpr* mWhenStart;

  // when_end
  const AstExpr* mWhenEnd;

  // rise_resistance
  const AstFloat* mRiseResistance;

  // fall_resistance
  const AstFloat* mFallResistance;

  // intrinsic_rise
  const AstFloat* mIntrinsicRise;

  // intrinsic_fall
  const AstFloat* mIntrinsicFall;

  // slope_rise
  const AstFloat* mSlopeRise;

  // slope_fall
  const AstFloat* mSlopeFall;

  // rise_delay_intercept
  AstArray<const AstIntFloat*> mRiseDelayIntercept;

  // fall_delay_intercept
  AstArray<const AstIntFloat*> mFallDelayIntercept;

  // rise_pin_resistance
  AstArray<const AstIntFloat*> mRisePinResistance;

  // fall_pin_resistance
  AstArray<const AstIntFloat*> mFallPinResistance;

  // cell_degradation
  const AstCellDegradation* mCellDegradation;

  // cell_rise
  const AstLut* mCellRise;

  // cell_fall
  const AstLut* mCellFall;

  // compact_ccs_rise
  const AstCCS* mCompactCCSRise;

  // compact_ccs_fall
  const AstCCS* mCompactCCSFall;

  // rise_constraint
  const AstLut* mRiseConstraint;

  // fall_constraint
  const AstLut* mFallConstraint;

  // rise_propagation
  const AstLut* mRisePropagation;

  // fall_propagation
  const AstLut* mFallPropagation;

  // rise_transition
  const AstLut* mRiseTransition;

  // fall_transition
  const AstLut* mFallTransition;

  // retaining_rise
  const AstLut* mRetainingRise;

  // retaining_fall
  const AstLut* mRetainingFall;

  // retain_rise_slew
  const AstLut* mRetainRiseSlew;

  // retain_fall_slew
  const AstLut* mRetainFallSlew;

};

END_NAMESPACE_YM_DOTLIB

#endif // ASTTIMING_H
