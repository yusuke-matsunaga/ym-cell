
/// @file TimingHandler.cc
/// @brief TimingHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/TimingHandler.h"
#include "dotlib/TokenType.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TimingHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
TimingHandler::TimingHandler(Parser& parser) :
  GroupHandler(parser)
{
  // パース関数の登録
  reg_func("clock_gating_flag,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("default_timing,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("fall_resistance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("fpga_arc_condition,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_function(attr_type, attr_loc); });
  reg_func("fpga_domain_style,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("interdependence_id,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_int(attr_type, attr_loc); });
  reg_func("intrinsic_fall,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("intrinsic_rise,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("related_bus_equivalent,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("related_bus_pins,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("related_output_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("related_pin,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_string(attr_type, attr_loc); });
  reg_func("rise_resistance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  // sdf_cond
  // sdf_cond_end
  // sdf_cond_start
  // sdf_edges
  reg_func("slope_fall,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("slope_rise,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("steady_state_resistance_above_high,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("steady_state_resistance_below_low,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_float(attr_type, attr_loc); });
  reg_func("tied_off,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_bool(attr_type, attr_loc); });
  reg_func("timing_sense,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_timing_sense(attr_type, attr_loc); });
  reg_func("timing_type,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_timing_type(attr_type, attr_loc); });
  reg_func("when,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_function(attr_type, attr_loc); });
  reg_func("when_end,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_function(attr_type, attr_loc); });
  reg_func("when_start,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_function(attr_type, attr_loc); });

  reg_func("fall_delay_intercept,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_int_float(attr_type, attr_loc); });
  reg_func("fall_pin_resistance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_int_float(attr_type, attr_loc); });
  reg_func("rise_delay_intercept,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_int_float(attr_type, attr_loc); });
  reg_func("rise_pin_resistance,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_int_float(attr_type, attr_loc); });

  // cell_degradation

  reg_func("cell_fall,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_table(attr_type, attr_loc); });
  reg_func("cell_rise,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_table(attr_type, attr_loc); });
  reg_func("fall_constraint,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_table(attr_type, attr_loc); });
  reg_func("fall_propagation,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_table(attr_type, attr_loc); });
  reg_func("fall_transition,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_table(attr_type, attr_loc); });

  // noise_immunity_above_high
  // noise_immunity_below_low
  // noise_immunity_high
  // noise_immunity_low

  reg_func("output_current_fall,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_table(attr_type, attr_loc); });
  reg_func("output_current_rise,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_table(attr_type, attr_loc); });

  // propagated_noise_height_above_high
  // propagated_noise_height_below_low
  // propagated_noise_height_high
  // propagated_noise_height_low
  // propagated_noise_peak_time_ratio_above_high
  // propagated_noise_peak_time_ratio_below_low
  // propagated_noise_peak_time_ratio_high
  // propagated_noise_peak_time_ratio_low
  // propagated_noise_width_above_high
  // propagated_noise_width_below_low
  // propagated_noise_width_high
  // propagated_noise_width_low
  // receiver_capacitance1_fall
  // receiver_capacitance1_rise
  // receiver_capacitance2_fall
  // receiver_capacitance2_rise
  // retaining_fall
  // retaining_rise
  // retain_fall_slew
  // retain_rise_slew

  reg_func("rise_constraint,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_table(attr_type, attr_loc); });
  reg_func("rise_propagation,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   -> unique_ptr<const AstAttr>
	   { return parser.parse_table(attr_type, attr_loc); });
  reg_func("rise_transition,"
	   [=](Parser& parser, AttrType attr_type, const FileRegion& attr_loc)
	   { return parser.parse_table(attr_type, attr_loc); });

  // steady_state_current_high
  // steady_state_current_low
  // steady_state_current_tristate
}

END_NAMESPACE_YM_DOTLIB
