#ifndef CELLHANDLER_H
#define CELLHANDLER_H

/// @file CellHandler.h
/// @brief CellHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.

#include "Str1GroupHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
/// @class CellHandler CellHandler.h "CellHandler.h"
/// @brief cell 用のハンドラ
///
/// 参考文献 : Library Compiler Reference Manual, Section 2
///           "cell and model Group Description and Syntax"
/// * ヘッダの文字列はセル名を表す．
/// * セルグループ内部の属性は以下の通り(原文中の凡例が統一されていない)
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
///   - io_type : name_id ;
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
  public Str1GroupHandler
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

  /// @breif cell group statement の記述をパースする．
  /// @return 読み込んだ値を返す．
  const AstCell*
  parse_value();


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

  // area
  const AstFloat* mArea;

  // auxiliary_pad_cell
  const AstBool* mAuxiliaryPadCell;

  // base_name
  const AstString* mBaseName;

  // bus_naming_style
  const AstString* mBusNamingStyle;

  // cell_footprint

  // cell_leakage_power
  const AstFloat* mCellLeakagePower;

  // clock_gating_integrated_cell
  const AstString* mClockIntegratedCell;

  // contention_condition
  const AstExpr* mContentionCondition;

  // dont_fault
  const AstBool* mDontFault;

  // dont_touch
  const AstBool* mDontTouch;

  // driver_type
  const AstString* mDriverType;

  // em_temp_degradation_factor
  const AstFloat* mEmTempDegradation;

  // fpga_domain_style
  const AstString* mFpgaDomainStyle;

  // geometry_print
  const AstString* mGeometryPrint;

  // handle_negative_constraint
  const AstBool* mHandleNegativeConstraint;

  // interface_timing
  const AstBool* mInterfaceTiming;

  // io_type
  const AstString* mIoType;

  // is_clock_gating_cell
  const AstBool* mIsClockGating;

  // map_only
  const AstBool* mMapOnly;

  // pad_cell
  const AstBool* mPadCell;

  // power_cell_type
  const AstCellType* mPowerCellType;

  // preferred
  const AstBool* mPreferred;

  // scaling_factors
  const AstString* mScalingFactors;

  // single_bit_degenerate
  const AstString* mSingleBitDegenerate;

  // slew_type
  const AstString* mSlewType;

  // timing_model_type
  const AstString* mTimingModelType;

  // use_for_size_only
  const AstBool* mUseForSizeOnly;

  // vhdl_name
  const AstString* mVhdlName;

  // pin_equal
  const AstString* mPinEqual;

  // pin_opposite
  const AstString* mPinOpposite[2];

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
  const AstFFBank* mFFBank;

  // functional_yield_metric
  const AstFYM* mFunctionalYieldMetric;

  // generated_clock
  vector<const AstGeneratedClock*> mGeneratedClockList;

  // intrinsic_parasitic
  vector<const AstIntrinsicParasitic*> mIntrinsicParasiticList;

  // latch
  const AstLatch* mLatch;

  // latch_bank
  const AstLatchBank* mLatchBank;

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
