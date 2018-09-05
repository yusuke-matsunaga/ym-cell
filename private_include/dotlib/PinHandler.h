#ifndef PINHANDLER_H
#define PINHANDLER_H

/// @file PinHandler.h
/// @brief PinHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "Str1GroupHandler.h"


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

  /// @breif pin group statement の記述をパースする．
  /// @return 読み込んだ値を返す．
  const AstPin*
  parse_value();


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

  /// @brief attr_type に対応する属性を読み込む．
  /// @param[in] parser パーサー
  /// @param[in] attr_type 対象の属性
  /// @param[in] attr_loc attr_type のファイル上の位置
  /// @retval true 正常にパーズした．
  /// @retval false パーズ中にエラーが起こった．
  bool
  read_group_attr(AttrType attr_type,
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

  // capacitance
  const AstFloat* mCapacitance;

  // direction
  const AstPinDirection* mDirection;

  // fall_capacitance
  const AstFloat* mFallCapacitance;

  // fall_current_slope_after_threshold
  const AstFloat* mFallCurrentSlopeAfterThreshold;

  // fall_current_slope_before_threshold
  const AstFloat* mFallCurrentSlopeBeforeThreshold;

  // fall_time_after_threshold
  const AstFloat* mFallTimeAfterThreshold;

  // fall_time_before_threshold
  const AstFloat* mFallTimeBeforeThreshold;

  // fanout_load
  const AstFloat* mFanoutLoad;

  // function
  const AstExpr* mFunction;

  // input_voltage
  const AstInputVoltage* mInputVoltage;

  // max_capacitance
  const AstFloat* mMaxCapacitance;

  // max_fanout
  const AstFloat* mMaxFanout;

  // max_transition
  const AstFloat* mMaxTransition;

  // min_capacitance
  const AstFloat* mMinCapacitance;

  // min_fanout
  const AstFloat* mMinFanout;

  // min_transition
  const AstFloat* mMinTransition;

  // output_voltage
  const AstOutputVoltage* mOutputVoltage;

  // pulling_current
  const AstFloat* mPullingCurrent;

  // pulling_resistance
  const AstFloat* mPullingResistance;

  // rise_capacitance
  const AstFloat* mRiseCapacitance;

  // rise_current_slope_after_threshold
  const AstFloat* mRiseCurrentSlopeAfterThreshold;

  // rise_current_slope_before_threshold
  const AstFloat* mRiseCurrentSlopeBeforeThreshold;

  // rise_time_after_threshold
  const AstFloat* mRiseTimeAfterThreshold;

  // rise_time_before_threshold
  const AstFloat* mRiseTimeBeforeThreshold;

  // three_state
  const AstExpr* mThreeState;

  // vdhl_name
  const AstString* mVhdlName;

  // timing
  vector<const AstTiming*> mTimingList;

  // 読み込んだ値
  const AstPin* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // PINHANDLER_H
