#ifndef CELLHANDLER_H
#define CELLHANDLER_H

/// @file CellHandler.h
/// @brief CellHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class CellHandler CellHandler.h "CellHandler.h"
/// @brief 'cell' Group Statement 用のハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 2
///           "cell and model Group Description and Syntax"
/// * ヘッダの文字列はセル名を表す．
/// * セルグループ内部の属性は以下の通り(原文中の凡例が統一されていない)
/// * さらに冒頭のサマリ中に現れない属性もある．
/// * Simple Attributes
///   - area : float ;
///   - auxiliary_pad_cell : true | false ;
///   - base_name : cell_base_name_(string) ;
///   - bus_naming_style : "string" ;
///   - cell_footprint : footprint_type_(string) ;
///   - cell_leakage_power : float ;
///   - clock_gating_integrated_cell : string ;
///   - contention_condition : "Boolean expression" ;
///   - dont_fault : sa0 | sa1 | sa01 ;
///   - dont_touch : true | false ;
///   - driver_type : name_(id) ;
///   - edif_name : name_(id) ;
///   - em_temp_degradation_factor : float ;
///   - fpga_domain_style : name_(id) ;
///   - geometry_print : string ;
///   - handle_negative_constraint : true | false ;
///   - interface_timing : true | false ;
///   - io_type : name_(id) ;
///   - is_clock_gating_cell : true | false ;
///   - map_only : true | false ;
///   - pad_cell : true | false ;
///   - pad_type : clock ;
///   - power_cell_type : ;
///   - preferred : true | false ;
///   - scaling_factors : group_name ;
///   - single_bit_degenerate : string ;
///   - slew_type : name_(id) ;
///   - timing_model_type : "string" ;
///   - use_for_size_only : true | false ;
///   - vhdl_name : "string" ;
/// * Complex Attributes
///   - pin_equal ( "name_list_(string)" ) ;
///   - pin_opposite ( "name_list1_(string), "name_list2_(string)" ) ;
///   - rail_connection ( connection_name_(string), power_supply_name_(string) ) ;
///   - resource_usage ( resource_name_(id), number_of_resources_(id) ) ;
/// * Group Statements
///   - bundle ( name_(string) ) { ... }
///   - bus ( name_(string) ) { ... }
///   - dynamic_current () { ... }
///   - ff ( variable1_(string), variable2_(string) ) { ... }
///   - ff_bank ( variable1_(string), variable2_(string), bits_(integer) ) { ... }
///   - functional_yield_metric () { ... }
///   - generated_clock () { ... }
///   - intrinsic_parasitic () { ... }
///   - latch ( variable1_(string), variable2_(string) ) { ... }
///   - latch_bank ( variable1_(string), variable2_(string), bits_(integer) ) { ... }
///   - leakage_current () { ... }
///   - leakage_power () { ... }
///   - lut ( name_(string) ) { ... }
///   - mode_definition () { ... }
///   - pin ( name_(string) | name_list_(string) ) { ... }
///   - routing_track ( routing_layer_name_(string) ) { ... }
///   - statetable ( "input node names", "internal node names" ) { ... }
///   - test_cell () { ... }
///   - type ( name_(string) ) { ... }
//////////////////////////////////////////////////////////////////////
class CellHandler :
  public GroupHandler
{
public:

  /// @brief コンストラクタ
  /// @param[in] parser パーサー
  CellHandler(DotlibParser& parser);

  /// @brief デストラクタ
  ~CellHandler();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @breif cell Group Statement の記述をパースする．
  /// @param[in] dst_list 読み込んだ値を格納するリスト
  /// @retval true 正しく読み込んだ．
  /// @retval false エラーが起きた．
  bool
  parse_value(vector<const AstCell*>& dst_list);


protected:
  //////////////////////////////////////////////////////////////////////
  // GroupHandler の仮想関数
  //////////////////////////////////////////////////////////////////////

  /// @brief グループ記述の始まり
  void
  begin_group() override;

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

  // area
  const AstFloat* mArea;

  // auxiliary_pad_cell
  const AstBool* mAuxiliaryPadCell;

  // base_name
  const AstString* mBaseName;

  // bus_naming_style
  const AstString* mBusNamingStyle;

  // cell_footprint
  const AstString* mCellFootprint;

  // cell_leakage_power
  const AstFloat* mCellLeakagePower;

  // clock_gating_integrated_cell
  const AstString* mClockIntegratedCell;

  // contention_condition
  const AstExpr* mContentionCondition;

  // dont_fault
  // none | sa0 | sa1 | as01
  const AstString* mDontFault;

  // dont_touch
  const AstBool* mDontTouch;

  // driver_type ( "4" もあり )
  // alphanumeric string identifier, enclosed in quotation marks
  const AstString* mDriverType;

  // em_temp_degradation_factor
  const AstFloat* mEmTempDegradation;

  // fpga_domain_style
  // rising_edge_clock_cell | falling_edge_clock_cell
  const AstString* mFpgaDomainStyle;

  // fpga_isd
  const AstString* mFpgaIsd;

  // geometry_print
  const AstString* mGeometryPrint;

  // handle_negative_constraint
  const AstBool* mHandleNegativeConstraint;

  // interface_timing
  const AstBool* mInterfaceTiming;

  // io_type
  // alphanumeric string identifier, enclosed in quotation marks
  const AstString* mIoType;

  // is_clock_gating_cell
  const AstBool* mIsClockGating;

  // is_level_shifter
  const AstBool* mIsLevelShifter;

  // level_shifter_type
  // LH | HL | HL_LH
  const AstString* mLevelShifterType;

  // map_only
  const AstBool* mMapOnly;

  // pad_cell
  const AstBool* mPadCell;

  // pad_type
  // clock
  const AstString* mPadType;

  // power_cell_type
  // stdcell | macro
  const AstCellType* mPowerCellType;

  // power_gating_cell_name
  const AstString* mPowerGatingCellName;

  // preferred
  const AstBool* mPreferred;

  // scaling_factors
  const AstString* mScalingFactors;

  // sensitization_master
  const AstString* mSensitizationMaster;

  // single_bit_degenerate
  const AstString* mSingleBitDegenerate;

  // slew_type
  const AstString* mSlewType;

  // switch_cell_type
  const AstString* mSwitchCellType;

  // threshold_voltage_group
  const AstString* mThreholdVoltageGroup;

  // timing_model_type
  const AstString* mTimingModelType;

  // use_for_size_only
  const AstBool* mUseForSizeOnly;

  // vhdl_name
  const AstString* mVhdlName;

  // input_voltage_range
  const AstFloat* mInputVoltageRange[2];

  // output_voltage_range
  const AstFloat* mOutputVoltageRange[2];

  // pin_equal
  const AstStringVector* mPinEqual;

  // pin_name_map
  const AstStringVector* mPinNameMap;

  // pin_opposite
  const AstStringVector* mPinOpposite[2];

  // rail_connection
  const AstString* mRailConnection[2];

  // resource_usage
  const AstString* mResourceUsageName;
  const AstInt* mResourceUsageInt;

  // bundle
  vector<const AstBundle*> mBundleList;

  // bus
  vector<const AstBus*> mBusList;

  // dynamic_current
  vector<const AstDynamicCurrent*> mDynamicCurrentList;

  // ff
  const AstFF* mFF;

  // ff_bank
  const AstFF* mFFBank;

  // functional_yield_metric
  const AstFYM* mFunctionalYieldMetric;

  // generated_clock
  vector<const AstGeneratedClock*> mGeneratedClockList;

  // intrinsic_parasitic
  vector<const AstIntrinsicParasitic*> mIntrinsicParasiticList;

  // latch
  const AstLatch* mLatch;

  // latch_bank
  const AstLatch* mLatchBank;

  // leakage_current
  vector<const AstLeakageCurrent*> mLeakageCurrentList;

  // leakage_power
  vector<const AstLeakagePower*> mLeakagePowerList;

  // lut
  // 今は無視(対象のクラス名が AstLut で被るので)

  // mode_definition
  vector<const AstMode*> mModeList;

  // pin
  vector<const AstPin*> mPinList;

  // routing_track
  vector<const AstRoutingTrack*> mRoutingTrackList;

  // statetable
  const AstStateTable* mStateTable;

  // test_cell
  const AstTestCell* mTestCell;

  // type
  vector<const AstType*> mTypeList;

  // 読み込んだ値
  const AstCell* mValue;

};

END_NAMESPACE_YM_DOTLIB

#endif // CELLHANDLER_H
