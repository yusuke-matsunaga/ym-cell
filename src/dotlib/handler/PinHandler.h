#ifndef PINHANDLER_H
#define PINHANDLER_H

/// @file PinHandler.h
/// @brief PinHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "GroupHandler.h"
#include "FloatHandler.h"
#include "FuncHandler.h"
#include "InputVoltageHandler.h"
#include "OutputVoltageHandler.h"
#include "PinDirectionHandler.h"
#include "TimingHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class PinHandler PinHandler.h "PinHandler.h"
/// @brief pin 用のハンドラ
//////////////////////////////////////////////////////////////////////
class PinHandler :
  public Str1GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  PinHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~PinHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 値をクリアする．
  void
  clear_value();

  /// @brief 読み込んだ値を返す．
  const AstPin*
  value() const;


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  parse_attr(AttrType attr_type,
	     const FileRegion& attr_loc) override;

  /// @brief グループ記述の終わり
  /// @param[in] group_loc グループ全体のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  end_group(const FileRegion& group_loc) override;


private:
  //////////////////////////////////////////////////////////////////////
  // 内部で用いられる関数
  //////////////////////////////////////////////////////////////////////


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

#if 0
  // capacitance
  FloatHandler mCapacitance;

  // direction
  PinDirectionHandler mDirection;

  // fall_capacitance
  FloatHandler mFallCapacitance;

  // fall_current_slope_after_threshold
  FloatHandler mFallCurrentSlopeAfterThreshold;

  // fall_current_slope_before_threshold
  FloatHandler mFallCurrentSlopeBeforeThreshold;

  // fall_time_after_threshold
  FloatHandler mFallTimeAfterThreshold;

  // fall_time_before_threshold
  FloatHandler mFallTimeBeforeThreshold;

  // fanout_load
  FloatHandler mFanoutLoad;

  // function
  FuncHandler mFunction;

  // input_voltage
  InputVoltageHandler mInputVoltage;

  // max_capacitance
  FloatHandler mMaxCapacitance;

  // max_fanout
  FloatHandler mMaxFanout;

  // max_transition
  FloatHandler mMaxTransition;

  // min_capacitance
  FloatHandler mMinCapacitance;

  // min_fanout
  FloatHandler mMinFanout;

  // min_transition
  FloatHandler mMinTransition;

  // output_voltage
  OutputVoltageHandler mOutputVoltage;

  // pulling_current
  FloatHandler mPullingCurrent;

  // pulling_resistance
  FloatHandler mPullingResistance;

  // rise_capacitance
  FloatHandler mRiseCapacitance;

  // rise_current_slope_after_threshold
  FloatHandler mRiseCurrentSlopeAfterThreshold;

  // rise_current_slope_before_threshold
  FloatHandler mRiseCurrentSlopeBeforeThreshold;

  // rise_time_after_threshold
  FloatHandler mRiseTimeAfterThreshold;

  // rise_time_before_threshold
  FloatHandler mRiseTimeBeforeThreshold;

  // three_state
  FuncHandler mThreeState;

  // vdhl_name
  StrHandler mVdhlName;

  // timing
  TimingHandler mTiming;
#endif

  // 読み込んだ値
  const AstPin* mValue;
};

END_NAMESPACE_YM_DOTLIB

#endif // PINHANDLER_H
