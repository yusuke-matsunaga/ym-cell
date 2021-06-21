﻿
/// @file AttrType.cc
/// @brief AttrType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AttrType.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief AttrType の内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   AttrType attr)
{
  switch ( attr ) {
  case AttrType::none: s << "none"; break;
  case AttrType::area: s << "area"; break;
  case AttrType::auxiliary_pad_cell: s << "auxiliary_pad_cell"; break;
  case AttrType::base_name: s << "base_name"; break;
  case AttrType::bit_width: s << "bit_width"; break;
  case AttrType::bundle: s << "bundle"; break;
  case AttrType::bus: s << "bus"; break;
  case AttrType::bus_naming_style: s << "bus_naming_style"; break;
  case AttrType::bus_type: s << "bus_type"; break;
  case AttrType::calc_mode: s << "calc_mode"; break;
  case AttrType::capacitance: s << "capacitance"; break;
  case AttrType::capacitive_load_unit: s << "capacitive_load_unit"; break;
  case AttrType::cell: s << "cell"; break;
  case AttrType::cell_degradation: s << "cell_degradation"; break;
  case AttrType::cell_fall: s << "cell_fall"; break;
  case AttrType::cell_footprint: s << "cell_footprint"; break;
  case AttrType::cell_leakage_power: s << "cell_leakage_power"; break;
  case AttrType::cell_rise: s << "cell_rise"; break;
  case AttrType::clear: s << "clear"; break;
  case AttrType::clear_preset_var1: s << "clear_preset_var1"; break;
  case AttrType::clear_preset_var2: s << "clear_preset_var2"; break;
  case AttrType::clock: s << "clock"; break;
  case AttrType::clock_gate_clock_pin: s << "clock_gate_clock_pin"; break;
  case AttrType::clock_gate_enable_pin: s << "clock_gate_enable_pin"; break;
  case AttrType::clock_gate_test_pin: s << "clock_gate_test_pin"; break;
  case AttrType::clock_gate_obs_pin: s << "clock_gate_obs_pin"; break;
  case AttrType::clock_gate_out_pin: s << "clock_gate_out_pin"; break;
  case AttrType::clock_gating_flag: s << "clock_gating_flag"; break;
  case AttrType::clock_gating_integrated_cell: s << "clock_gating_integrated_cell"; break;
  case AttrType::clocked_on: s << "clocked_on"; break;
  case AttrType::clocked_on_also: s << "clocked_on_also"; break;
  case AttrType::coefs: s << "coefs"; break;
  case AttrType::comment: s << "comment"; break;
  case AttrType::complementary_pin: s << "complementary_pin"; break;
  case AttrType::connection_class: s << "connection_class"; break;
  case AttrType::contention_condition: s << "contention_condition"; break;
  case AttrType::current_unit: s << "current_unit"; break;
  case AttrType::data_in: s << "data_in"; break;
  case AttrType::date: s << "date"; break;
  case AttrType::dc_current_template: s << "dc_current_template"; break;
  case AttrType::default_cell_leakage_power: s << "default_cell_leakage_power"; break;
  case AttrType::default_connection_class: s << "default_connection_class"; break;
  case AttrType::default_fall_delay_intercept: s << "default_fall_delay_intercept"; break;
  case AttrType::default_fall_pin_resistance: s << "default_fall_pin_resistance"; break;
  case AttrType::default_fanout_load: s << "default_fanout_load"; break;
  case AttrType::default_inout_pin_cap: s << "default_inout_pin_cap"; break;
  case AttrType::default_inout_pin_fall_res: s << "default_inout_pin_fall_res"; break;
  case AttrType::default_inout_pin_rise_res: s << "default_inout_pin_rise_res"; break;
  case AttrType::default_input_pin_cap: s << "default_input_pin_cap"; break;
  case AttrType::default_intrinsic_fall: s << "default_intrinsic_fall"; break;
  case AttrType::default_intrinsic_rise: s << "default_intrinsic_rise"; break;
  case AttrType::default_leakage_power_density: s << "default_leakage_power_density"; break;
  case AttrType::default_max_capacitance: s << "default_max_capacitance"; break;
  case AttrType::default_max_fanout: s << "default_max_fanout"; break;
  case AttrType::default_max_transition: s << "default_max_transition"; break;
  case AttrType::default_max_utilization: s << "default_max_utilization"; break;
  case AttrType::default_min_porosity: s << "default_min_porosity"; break;
  case AttrType::default_operating_conditions: s << "default_operating_conditions"; break;
  case AttrType::default_output_pin_cap: s << "default_output_pin_cap"; break;
  case AttrType::default_output_pin_fall_res: s << "default_output_pin_fall_res"; break;
  case AttrType::default_output_pin_rise_res: s << "default_output_pin_rise_res"; break;
  case AttrType::default_part: s << "default_part"; break;
  case AttrType::default_rise_delay_intercept: s << "default_rise_delay_intercept"; break;
  case AttrType::default_rise_pin_resistance: s << "default_rise_pin_resistance"; break;
  case AttrType::default_slope_fall: s << "default_slope_fall"; break;
  case AttrType::default_slope_rise: s << "default_slope_rise"; break;
  case AttrType::default_timing: s << "default_timing"; break;
  case AttrType::default_wire_load_area: s << "default_wire_load_area"; break;
  case AttrType::default_wire_load_capacitance: s << "default_wire_load_capacitance"; break;
  case AttrType::default_wire_load_mode: s << "default_wire_load_mode"; break;
  case AttrType::default_wire_load_resistance: s << "default_wire_load_resistance"; break;
  case AttrType::default_wire_load_selection: s << "default_wire_load_selection"; break;
  case AttrType::default_wire_load: s << "default_wire_load"; break;
  case AttrType::define_cell_area: s << "define_cell_area"; break;
  case AttrType::define_group: s << "define_group"; break;
  case AttrType::define: s << "define"; break;
  case AttrType::delay_model: s << "delay_model"; break;
  case AttrType::direction: s << "direction"; break;
  case AttrType::domain: s << "domain"; break;
  case AttrType::dont_fault: s << "dont_fault"; break;
  case AttrType::dont_touch: s << "dont_touch"; break;
  case AttrType::dont_use: s << "dont_use"; break;
  case AttrType::drive_current: s << "drive_current"; break;
  case AttrType::driver_type: s << "driver_type"; break;
  case AttrType::dynamic_current: s << "dynamic_current"; break;
  case AttrType::edge_rate_sensitivity_f0: s << "edge_rate_sensitivity_f0"; break;
  case AttrType::edge_rate_sensitivity_f1: s << "edge_rate_sensitivity_f1"; break;
  case AttrType::edge_rate_sensitivity_r0: s << "edge_rate_sensitivity_r0"; break;
  case AttrType::edge_rate_sensitivity_r1: s << "edge_rate_sensitivity_r1"; break;
  case AttrType::edif_name: s << "edif_name"; break;
  case AttrType::electromigration: s << "electromigration"; break;
  case AttrType::em_lut_template: s << "em_lut_template"; break;
  case AttrType::em_temp_degradation_factor: s << "em_temp_degradation_factor"; break;
  case AttrType::enable_also: s << "enable_also"; break;
  case AttrType::enable: s << "enable"; break;
  case AttrType::equal_or_opposite_output: s << "equal_or_opposite_output"; break;
  case AttrType::fall_capacitance_range: s << "fall_capacitance_range"; break;
  case AttrType::fall_capacitance: s << "fall_capacitance"; break;
  case AttrType::fall_constraint: s << "fall_constraint"; break;
  case AttrType::fall_current_slope_after_threshold: s << "fall_current_slope_after_threshold"; break;
  case AttrType::fall_current_slope_before_threshold: s << "fall_current_slope_before_threshold"; break;
  case AttrType::fall_delay_intercept: s << "fall_delay_intercept"; break;
  case AttrType::fall_pin_resistance: s << "fall_pin_resistance"; break;
  case AttrType::fall_power: s << "fall_power"; break;
  case AttrType::fall_propagation: s << "fall_propagation"; break;
  case AttrType::fall_resistance: s << "fall_resistance"; break;
  case AttrType::fall_time_after_threshold: s << "fall_time_after_threshold"; break;
  case AttrType::fall_time_before_threshold: s << "fall_time_before_threshold"; break;
  case AttrType::fall_transition_degradation: s << "fall_transition_degradation"; break;
  case AttrType::fall_transition: s << "fall_transition"; break;
  case AttrType::falling_together_group: s << "falling_together_group"; break;
  case AttrType::fanout_area: s << "fanout_area"; break;
  case AttrType::fanout_capacitance: s << "fanout_capacitance"; break;
  case AttrType::fanout_length: s << "fanout_length"; break;
  case AttrType::fanout_load: s << "fanout_load"; break;
  case AttrType::fanout_resistance: s << "fanout_resistance"; break;
  case AttrType::fault_model: s << "fault_model"; break;
  case AttrType::faults_lut_template: s << "faults_lut_template"; break;
  case AttrType::ff: s << "ff"; break;
  case AttrType::ff_bank: s << "ff_bank"; break;
  case AttrType::fpga_arc_condition: s << "fpga_arc_condition"; break;
  case AttrType::fpga_domain_style: s << "fpga_domain_style"; break;
  case AttrType::fpga_technology: s << "fpga_technology"; break;
  case AttrType::function: s << "function"; break;
  case AttrType::functional_yield_metric: s << "functional_yield_metric"; break;
  case AttrType::generated_clock: s << "generated_clock"; break;
  case AttrType::geometry_print: s << "geometry_print"; break;
  case AttrType::handle_negative_constraint: s << "handle_negative_constraint"; break;
  case AttrType::has_builtin_pad: s << "has_builtin_pad"; break;
  case AttrType::hyperbolic_noise_above_high: s << "hyperbolic_noise_above_high"; break;
  case AttrType::hyperbolic_noise_below_low: s << "hyperbolic_noise_below_low"; break;
  case AttrType::hyperbolic_noise_high: s << "hyperbolic_noise_high"; break;
  case AttrType::hyperbolic_noise_low: s << "hyperbolic_noise_low"; break;
  case AttrType::hysteresis: s << "hysteresis"; break;
  case AttrType::in_place_swap_mode: s << "in_place_swap_mode"; break;
  case AttrType::index_1: s << "index_1"; break;
  case AttrType::index_2: s << "index_2"; break;
  case AttrType::index_3: s << "index_3"; break;
  case AttrType::input_map: s << "input_map"; break;
  case AttrType::input_signal_level: s << "input_signal_level"; break;
  case AttrType::input_threshold_pct_fall: s << "input_threshold_pct_fall"; break;
  case AttrType::input_threshold_pct_rise: s << "input_threshold_pct_rise"; break;
  case AttrType::input_voltage: s << "input_voltage"; break;
  case AttrType::interdependence_id: s << "interdependence_id"; break;
  case AttrType::interface_timing: s << "interface_timing"; break;
  case AttrType::internal_node: s << "internal_node"; break;
  case AttrType::internal_power: s << "internal_power"; break;
  case AttrType::intrinsic_fall: s << "intrinsic_fall"; break;
  case AttrType::intrinsic_parasitic: s << "intrinsic_parasitic"; break;
  case AttrType::intrinsic_rise: s << "intrinsic_rise"; break;
  case AttrType::inverted_output: s << "inverted_output"; break;
  case AttrType::io_type: s << "io_type"; break;
  case AttrType::is_clock_gating_cell: s << "is_clock_gating_cell"; break;
  case AttrType::is_filler_cell: s << "is_filler_cell"; break;
  case AttrType::is_pad: s << "is_pad"; break;
  case AttrType::isolation_cell_enable_pin: s << "isolation_cell_enable_pin"; break;
  case AttrType::iv_lut_template: s << "iv_lut_template"; break;
  case AttrType::k_process_cell_fall: s << "k_process_cell_fall"; break;
  case AttrType::k_process_cell_leakage_power: s << "k_process_cell_leakage_power"; break;
  case AttrType::k_process_cell_rise: s << "k_process_cell_rise"; break;
  case AttrType::k_process_drive_current: s << "k_process_drive_current"; break;
  case AttrType::k_process_drive_fall: s << "k_process_drive_fall"; break;
  case AttrType::k_process_drive_rise: s << "k_process_drive_rise"; break;
  case AttrType::k_process_fall_delay_intercept: s << "k_process_fall_delay_intercept"; break;
  case AttrType::k_process_fall_pin_resistance: s << "k_process_fall_pin_resistance"; break;
  case AttrType::k_process_fall_propagation: s << "k_process_fall_propagation"; break;
  case AttrType::k_process_fall_transition: s << "k_process_fall_transition"; break;
  case AttrType::k_process_hold_fall: s << "k_process_hold_fall"; break;
  case AttrType::k_process_hold_rise: s << "k_process_hold_rise"; break;
  case AttrType::k_process_internal_power: s << "k_process_internal_power"; break;
  case AttrType::k_process_intrinsic_fall: s << "k_process_intrinsic_fall"; break;
  case AttrType::k_process_intrinsic_rise: s << "k_process_intrinsic_rise"; break;
  case AttrType::k_process_min_period: s << "k_process_min_period"; break;
  case AttrType::k_process_min_pulse_width_high: s << "k_process_min_pulse_width_high"; break;
  case AttrType::k_process_min_pulse_width_low: s << "k_process_min_pulse_width_low"; break;
  case AttrType::k_process_nochange_fall: s << "k_process_nochange_fall"; break;
  case AttrType::k_process_nochange_rise: s << "k_process_nochange_rise"; break;
  case AttrType::k_process_pin_cap: s << "k_process_pin_cap"; break;
  case AttrType::k_process_recovery_fall: s << "k_process_recovery_fall"; break;
  case AttrType::k_process_recovery_rise: s << "k_process_recovery_rise"; break;
  case AttrType::k_process_removal_fall: s << "k_process_removal_fall"; break;
  case AttrType::k_process_removal_rise: s << "k_process_removal_rise"; break;
  case AttrType::k_process_rise_transition: s << "k_process_rise_transition"; break;
  case AttrType::k_process_rise_delay_intercept: s << "k_process_rise_delay_intercept"; break;
  case AttrType::k_process_rise_pin_resistance: s << "k_process_rise_pin_resistance"; break;
  case AttrType::k_process_rise_propagation: s << "k_process_rise_propagation"; break;
  case AttrType::k_process_setup_fall: s << "k_process_setup_fall"; break;
  case AttrType::k_process_setup_rise: s << "k_process_setup_rise"; break;
  case AttrType::k_process_skew_fall: s << "k_process_skew_fall"; break;
  case AttrType::k_process_skew_rise: s << "k_process_skew_rise"; break;
  case AttrType::k_process_slope_fall: s << "k_process_slope_fall"; break;
  case AttrType::k_process_slope_rise: s << "k_process_slope_rise"; break;
  case AttrType::k_process_wire_cap: s << "k_process_wire_cap"; break;
  case AttrType::k_process_wire_res: s << "k_process_wire_res"; break;
  case AttrType::k_temp_cell_fall: s << "k_temp_cell_fall"; break;
  case AttrType::k_temp_cell_leakage_power: s << "k_temp_cell_leakage_power"; break;
  case AttrType::k_temp_cell_rise: s << "k_temp_cell_rise"; break;
  case AttrType::k_temp_drive_current: s << "k_temp_drive_current"; break;
  case AttrType::k_temp_drive_fall: s << "k_temp_drive_fall"; break;
  case AttrType::k_temp_drive_rise: s << "k_temp_drive_rise"; break;
  case AttrType::k_temp_fall_delay_intercept: s << "k_temp_fall_delay_intercept"; break;
  case AttrType::k_temp_fall_pin_resistance: s << "k_temp_fall_pin_resistance"; break;
  case AttrType::k_temp_fall_propagation: s << "k_temp_fall_propagation"; break;
  case AttrType::k_temp_fall_transition: s << "k_temp_fall_transition"; break;
  case AttrType::k_temp_hold_fall: s << "k_temp_hold_fall"; break;
  case AttrType::k_temp_hold_rise: s << "k_temp_hold_rise"; break;
  case AttrType::k_temp_internal_power: s << "k_temp_internal_power"; break;
  case AttrType::k_temp_intrinsic_fall: s << "k_temp_intrinsic_fall"; break;
  case AttrType::k_temp_intrinsic_rise: s << "k_temp_intrinsic_rise"; break;
  case AttrType::k_temp_min_period: s << "k_temp_min_period"; break;
  case AttrType::k_temp_min_pulse_width_high: s << "k_temp_min_pulse_width_high"; break;
  case AttrType::k_temp_min_pulse_width_low: s << "k_temp_min_pulse_width_low"; break;
  case AttrType::k_temp_nochange_fall: s << "k_temp_nochange_fall"; break;
  case AttrType::k_temp_nochange_rise: s << "k_temp_nochange_rise"; break;
  case AttrType::k_temp_pin_cap: s << "k_temp_pin_cap"; break;
  case AttrType::k_temp_recovery_fall: s << "k_temp_recovery_fall"; break;
  case AttrType::k_temp_recovery_rise: s << "k_temp_recovery_rise"; break;
  case AttrType::k_temp_removal_fall: s << "k_temp_removal_fall"; break;
  case AttrType::k_temp_removal_rise: s << "k_temp_removal_rise"; break;
  case AttrType::k_temp_rise_transition: s << "k_temp_rise_transition"; break;
  case AttrType::k_temp_rise_delay_intercept: s << "k_temp_rise_delay_intercept"; break;
  case AttrType::k_temp_rise_pin_resistance: s << "k_temp_rise_pin_resistance"; break;
  case AttrType::k_temp_rise_propagation: s << "k_temp_rise_propagation"; break;
  case AttrType::k_temp_setup_fall: s << "k_temp_setup_fall"; break;
  case AttrType::k_temp_setup_rise: s << "k_temp_setup_rise"; break;
  case AttrType::k_temp_skew_fall: s << "k_temp_skew_fall"; break;
  case AttrType::k_temp_skew_rise: s << "k_temp_skew_rise"; break;
  case AttrType::k_temp_slope_fall: s << "k_temp_slope_fall"; break;
  case AttrType::k_temp_slope_rise: s << "k_temp_slope_rise"; break;
  case AttrType::k_temp_wire_cap: s << "k_temp_wire_cap"; break;
  case AttrType::k_temp_wire_res: s << "k_temp_wire_res"; break;
  case AttrType::k_volt_cell_fall: s << "k_volt_cell_fall"; break;
  case AttrType::k_volt_cell_leakage_power: s << "k_volt_cell_leakage_power"; break;
  case AttrType::k_volt_cell_rise: s << "k_volt_cell_rise"; break;
  case AttrType::k_volt_drive_current: s << "k_volt_drive_current"; break;
  case AttrType::k_volt_drive_fall: s << "k_volt_drive_fall"; break;
  case AttrType::k_volt_drive_rise: s << "k_volt_drive_rise"; break;
  case AttrType::k_volt_fall_delay_intercept: s << "k_volt_fall_delay_intercept"; break;
  case AttrType::k_volt_fall_pin_resistance: s << "k_volt_fall_pin_resistance"; break;
  case AttrType::k_volt_fall_propagation: s << "k_volt_fall_propagation"; break;
  case AttrType::k_volt_fall_transition: s << "k_volt_fall_transition"; break;
  case AttrType::k_volt_hold_fall: s << "k_volt_hold_fall"; break;
  case AttrType::k_volt_hold_rise: s << "k_volt_hold_rise"; break;
  case AttrType::k_volt_internal_power: s << "k_volt_internal_power"; break;
  case AttrType::k_volt_intrinsic_fall: s << "k_volt_intrinsic_fall"; break;
  case AttrType::k_volt_intrinsic_rise: s << "k_volt_intrinsic_rise"; break;
  case AttrType::k_volt_min_period: s << "k_volt_min_period"; break;
  case AttrType::k_volt_min_pulse_width_high: s << "k_volt_min_pulse_width_high"; break;
  case AttrType::k_volt_min_pulse_width_low: s << "k_volt_min_pulse_width_low"; break;
  case AttrType::k_volt_nochange_fall: s << "k_volt_nochange_fall"; break;
  case AttrType::k_volt_nochange_rise: s << "k_volt_nochange_rise"; break;
  case AttrType::k_volt_pin_cap: s << "k_volt_pin_cap"; break;
  case AttrType::k_volt_recovery_fall: s << "k_volt_recovery_fall"; break;
  case AttrType::k_volt_recovery_rise: s << "k_volt_recovery_rise"; break;
  case AttrType::k_volt_removal_fall: s << "k_volt_removal_fall"; break;
  case AttrType::k_volt_removal_rise: s << "k_volt_removal_rise"; break;
  case AttrType::k_volt_rise_transition: s << "k_volt_rise_transition"; break;
  case AttrType::k_volt_rise_delay_intercept: s << "k_volt_rise_delay_intercept"; break;
  case AttrType::k_volt_rise_pin_resistance: s << "k_volt_rise_pin_resistance"; break;
  case AttrType::k_volt_rise_propagation: s << "k_volt_rise_propagation"; break;
  case AttrType::k_volt_setup_fall: s << "k_volt_setup_fall"; break;
  case AttrType::k_volt_setup_rise: s << "k_volt_setup_rise"; break;
  case AttrType::k_volt_skew_fall: s << "k_volt_skew_fall"; break;
  case AttrType::k_volt_skew_rise: s << "k_volt_skew_rise"; break;
  case AttrType::k_volt_slope_fall: s << "k_volt_slope_fall"; break;
  case AttrType::k_volt_slope_rise: s << "k_volt_slope_rise"; break;
  case AttrType::k_volt_wire_cap: s << "k_volt_wire_cap"; break;
  case AttrType::k_volt_wire_res: s << "k_volt_wire_res"; break;
  case AttrType::latch: s << "latch"; break;
  case AttrType::latch_bank: s << "latch_bank"; break;
  case AttrType::leakage_current: s << "leakage_current"; break;
  case AttrType::leakage_power_unit: s << "leakage_power_unit"; break;
  case AttrType::leakage_power: s << "leakage_power"; break;
  case AttrType::level_shifter_enable_pin: s << "level_shifter_enable_pin"; break;
  case AttrType::library_features: s << "library_features"; break;
  case AttrType::library: s << "library"; break;
  case AttrType::lu_table_template: s << "lu_table_template"; break;
  case AttrType::lut: s << "lut"; break;
  case AttrType::map_only: s << "map_only"; break;
  case AttrType::map_to_logic: s << "map_to_logic"; break;
  case AttrType::max_capacitance: s << "max_capacitance"; break;
  case AttrType::max_fanout: s << "max_fanout"; break;
  case AttrType::max_input_noise_width: s << "max_input_noise_width"; break;
  case AttrType::max_trans: s << "max_trans"; break;
  case AttrType::max_transition: s << "max_transition"; break;
  case AttrType::members: s << "members"; break;
  case AttrType::min_capacitance: s << "min_capacitance"; break;
  case AttrType::min_fanout: s << "min_fanout"; break;
  case AttrType::min_input_noise_width: s << "min_input_noise_width"; break;
  case AttrType::min_period: s << "min_period"; break;
  case AttrType::min_pulse_width_high: s << "min_pulse_width_high"; break;
  case AttrType::min_pulse_width_low: s << "min_pulse_width_low"; break;
  case AttrType::min_pulse_width: s << "min_pulse_width"; break;
  case AttrType::min_transition: s << "min_transition"; break;
  case AttrType::minimum_period: s << "minimum_period"; break;
  case AttrType::mode_definition: s << "mode_definition"; break;
  case AttrType::multicell_pad_pin: s << "multicell_pad_pin"; break;
  case AttrType::next_state: s << "next_state"; break;
  case AttrType::nextstate_type: s << "nextstate_type"; break;
  case AttrType::noise_immunity_above_high: s << "noise_immunity_above_high"; break;
  case AttrType::noise_immunity_below_low: s << "noise_immunity_below_low"; break;
  case AttrType::noise_immunity_high: s << "noise_immunity_high"; break;
  case AttrType::noise_immunity_low: s << "noise_immunity_low"; break;
  case AttrType::noise_lut_template: s << "noise_lut_template"; break;
  case AttrType::nom_calc_mode: s << "nom_calc_mode"; break;
  case AttrType::nom_process: s << "nom_process"; break;
  case AttrType::nom_temperature: s << "nom_temperature"; break;
  case AttrType::nom_voltage: s << "nom_voltage"; break;
  case AttrType::operating_conditions: s << "operating_conditions"; break;
  case AttrType::orders: s << "orders"; break;
  case AttrType::output_current_fall: s << "output_current_fall"; break;
  case AttrType::output_current_rise: s << "output_current_rise"; break;
  case AttrType::output_current_template: s << "output_current_template"; break;
  case AttrType::output_signal_level: s << "output_signal_level"; break;
  case AttrType::output_threshold_pct_fall: s << "output_threshold_pct_fall"; break;
  case AttrType::output_threshold_pct_rise: s << "output_threshold_pct_rise"; break;
  case AttrType::output_voltage: s << "output_voltage"; break;
  case AttrType::pad_cell: s << "pad_cell"; break;
  case AttrType::pad_type: s << "pad_type"; break;
  case AttrType::parameter1: s << "parameter1"; break;
  case AttrType::parameter2: s << "parameter2"; break;
  case AttrType::parameter3: s << "parameter3"; break;
  case AttrType::parameter4: s << "parameter4"; break;
  case AttrType::parameter5: s << "parameter5"; break;
  case AttrType::part: s << "part"; break;
  case AttrType::pg_function: s << "pg_function"; break;
  case AttrType::piece_define: s << "piece_define"; break;
  case AttrType::piece_type: s << "piece_type"; break;
  case AttrType::pin: s << "pin"; break;
  case AttrType::pin_func_type: s << "pin_func_type"; break;
  case AttrType::pin_opposite: s << "pin_opposite"; break;
  case AttrType::poly_template: s << "poly_template"; break;
  case AttrType::power: s << "power"; break;
  case AttrType::power_cell_type: s << "power_cell_type"; break;
  case AttrType::power_down_function: s << "power_down_function"; break;
  case AttrType::power_level: s << "power_level"; break;
  case AttrType::power_lut_template: s << "power_lut_template"; break;
  case AttrType::power_poly_template: s << "power_poly_template"; break;
  case AttrType::power_model: s << "power_model"; break;
  case AttrType::power_rail: s << "power_rail"; break;
  case AttrType::power_supply_namestring: s << "power_supply_namestring"; break;
  case AttrType::power_supply: s << "power_supply"; break;
  case AttrType::prefer_tied: s << "prefer_tied"; break;
  case AttrType::preferred: s << "preferred"; break;
  case AttrType::preferred_input_pad_voltage: s << "preferred_input_pad_voltage"; break;
  case AttrType::preferred_output_pad_slew_rate_control: s << "preferred_output_pad_slew_rate_control"; break;
  case AttrType::preferred_output_pad_voltage: s << "preferred_output_pad_voltage"; break;
  case AttrType::preset: s << "preset"; break;
  case AttrType::primary_output: s << "primary_output"; break;
  case AttrType::process: s << "process"; break;
  case AttrType::propagated_noise_height_above_high: s << "propagated_noise_height_above_high"; break;
  case AttrType::propagated_noise_height_below_low: s << "propagated_noise_height_below_low"; break;
  case AttrType::propagated_noise_height_high: s << "propagated_noise_height_high"; break;
  case AttrType::propagated_noise_height_low: s << "propagated_noise_height_low"; break;
  case AttrType::propagated_noise_peak_time_ratio_above_high: s << "propagated_noise_peak_time_ratio_above_high"; break;
  case AttrType::propagated_noise_peak_time_ratio_below_low: s << "propagated_noise_peak_time_ratio_below_low"; break;
  case AttrType::propagated_noise_peak_time_ratio_high: s << "propagated_noise_peak_time_ratio_high"; break;
  case AttrType::propagated_noise_peak_time_ratio_low: s << "propagated_noise_peak_time_ratio_low"; break;
  case AttrType::propagated_noise_width_above_high: s << "propagated_noise_width_above_high"; break;
  case AttrType::propagated_noise_width_below_low: s << "propagated_noise_width_below_low"; break;
  case AttrType::propagated_noise_width_high: s << "propagated_noise_width_high"; break;
  case AttrType::propagated_noise_width_low: s << "propagated_noise_width_low"; break;
  case AttrType::propagation_lut_template: s << "propagation_lut_template"; break;
  case AttrType::pulling_current: s << "pulling_current"; break;
  case AttrType::pulling_resistance_unit: s << "pulling_resistance_unit"; break;
  case AttrType::pulling_resistance: s << "pulling_resistance"; break;
  case AttrType::pulse_clock: s << "pulse_clock"; break;
  case AttrType::rail_connection: s << "rail_connection"; break;
  case AttrType::related_bus_equivalent: s << "related_bus_equivalent"; break;
  case AttrType::related_bus_pins: s << "related_bus_pins"; break;
  case AttrType::related_ground_pin: s << "related_ground_pin"; break;
  case AttrType::related_inputs: s << "related_inputs"; break;
  case AttrType::related_output_pin: s << "related_output_pin"; break;
  case AttrType::related_outputs: s << "related_outputs"; break;
  case AttrType::related_pg_pin: s << "related_pg_pin"; break;
  case AttrType::related_pin: s << "related_pin"; break;
  case AttrType::related_power_pin: s << "related_power_pin"; break;
  case AttrType::resistance: s << "resistance"; break;
  case AttrType::resource_usage: s << "resource_usage"; break;
  case AttrType::retain_fall_slew: s << "retain_fall_slew"; break;
  case AttrType::retain_rise_slew: s << "retain_rise_slew"; break;
  case AttrType::retaining_fall: s << "retaining_fall"; break;
  case AttrType::retaining_rise: s << "retaining_rise"; break;
  case AttrType::revision: s << "revision"; break;
  case AttrType::rise_capacitance_range: s << "rise_capacitance_range"; break;
  case AttrType::rise_capacitance: s << "rise_capacitance"; break;
  case AttrType::rise_constraint: s << "rise_constraint"; break;
  case AttrType::rise_current_slope_after_threshold: s << "rise_current_slope_after_threshold"; break;
  case AttrType::rise_current_slope_before_threshold: s << "rise_current_slope_before_threshold"; break;
  case AttrType::rise_delay_intercept: s << "rise_delay_intercept"; break;
  case AttrType::rise_pin_resistance: s << "rise_pin_resistance"; break;
  case AttrType::rise_power: s << "rise_power"; break;
  case AttrType::rise_propagation: s << "rise_propagation"; break;
  case AttrType::rise_resistance: s << "rise_resistance"; break;
  case AttrType::rise_time_after_threshold: s << "rise_time_after_threshold"; break;
  case AttrType::rise_time_before_threshold: s << "rise_time_before_threshold"; break;
  case AttrType::rise_transition_degradation: s << "rise_transition_degradation"; break;
  case AttrType::rise_transition: s << "rise_transition"; break;
  case AttrType::rising_together_group: s << "rising_together_group"; break;
  case AttrType::routing_layers: s << "routing_layers"; break;
  case AttrType::routing_track: s << "routing_track"; break;
  case AttrType::scaled_cell: s << "scaled_cell"; break;
  case AttrType::scaling_factors: s << "scaling_factors"; break;
  case AttrType::sdf_cond: s << "sdf_cond"; break;
  case AttrType::sdf_cond_end: s << "sdf_cond_end"; break;
  case AttrType::sdf_cond_start: s << "sdf_cond_start"; break;
  case AttrType::sdf_edges: s << "sdf_edges"; break;
  case AttrType::signal_type: s << "signal_type"; break;
  case AttrType::simulation: s << "simulation"; break;
  case AttrType::single_bit_degenerate: s << "single_bit_degenerate"; break;
  case AttrType::slew_control: s << "slew_control"; break;
  case AttrType::slew_derate_from_library: s << "slew_derate_from_library"; break;
  case AttrType::slew_lower_threshold_pct_fall: s << "slew_lower_threshold_pct_fall"; break;
  case AttrType::slew_lower_threshold_pct_rise: s << "slew_lower_threshold_pct_rise"; break;
  case AttrType::slew_type: s << "slew_type"; break;
  case AttrType::slew_upper_threshold_pct_fall: s << "slew_upper_threshold_pct_fall"; break;
  case AttrType::slew_upper_threshold_pct_rise: s << "slew_upper_threshold_pct_rise"; break;
  case AttrType::slope: s << "slope"; break;
  case AttrType::slope_fall: s << "slope_fall"; break;
  case AttrType::slope_rise: s << "slope_rise"; break;
  case AttrType::state_function: s << "state_function"; break;
  case AttrType::statetable: s << "statetable"; break;
  case AttrType::std_cell_main_rail: s << "std_cell_main_rail"; break;
  case AttrType::steady_state_current_above_high: s << "steady_state_current_above_high"; break;
  case AttrType::steady_state_current_below_low: s << "steady_state_current_below_low"; break;
  case AttrType::steady_state_current_high: s << "steady_state_current_high"; break;
  case AttrType::steady_state_current_low: s << "steady_state_current_low"; break;
  case AttrType::steady_state_current_tristate: s << "steady_state_current_tristate"; break;
  case AttrType::steady_state_resistance_above_high: s << "steady_state_resistance_above_high"; break;
  case AttrType::steady_state_resistance_below_low: s << "steady_state_resistance_below_low"; break;
  case AttrType::switch_function: s << "switch_function"; break;
  case AttrType::switch_pin: s << "switch_pin"; break;
  case AttrType::switching_interval: s << "switching_interval"; break;
  case AttrType::switching_together_group: s << "switching_together_group"; break;
  case AttrType::table: s << "table"; break;
  case AttrType::technology: s << "technology"; break;
  case AttrType::temperature: s << "temperature"; break;
  case AttrType::test_cell: s << "test_cell"; break;
  case AttrType::test_output_only: s << "test_output_only"; break;
  case AttrType::three_state: s << "three_state"; break;
  case AttrType::tied_off: s << "tied_off"; break;
  case AttrType::time_unit: s << "time_unit"; break;
  case AttrType::timing_model_type: s << "timing_model_type"; break;
  case AttrType::timing_range: s << "timing_range"; break;
  case AttrType::timing_sense: s << "timing_sense"; break;
  case AttrType::timing_type: s << "timing_type"; break;
  case AttrType::timing: s << "timing"; break;
  case AttrType::tlatch: s << "tlatch"; break;
  case AttrType::tree_type: s << "tree_type"; break;
  case AttrType::type: s << "type"; break;
  case AttrType::use_for_size_only: s << "use_for_size_only"; break;
  case AttrType::value: s << "value"; break;
  case AttrType::values: s << "values"; break;
  case AttrType::variable_1: s << "variable_1"; break;
  case AttrType::variable_1_range: s << "variable_1_range"; break;
  case AttrType::variable_2: s << "variable_2"; break;
  case AttrType::variable_2_range: s << "variable_2_range"; break;
  case AttrType::variable_3: s << "variable_3"; break;
  case AttrType::variable_3_range: s << "variable_3_range"; break;
  case AttrType::vhdl_name: s << "vhdl_name"; break;
  case AttrType::vih: s << "vih"; break;
  case AttrType::vil: s << "vil"; break;
  case AttrType::vimax: s << "vimax"; break;
  case AttrType::vimin: s << "vimin"; break;
  case AttrType::voh: s << "voh"; break;
  case AttrType::vol: s << "vol"; break;
  case AttrType::voltage_unit: s << "voltage_unit"; break;
  case AttrType::voltage: s << "voltage"; break;
  case AttrType::vomax: s << "vomax"; break;
  case AttrType::vomin: s << "vomin"; break;
  case AttrType::when_end: s << "when_end"; break;
  case AttrType::when_start: s << "when_start"; break;
  case AttrType::when: s << "when"; break;
  case AttrType::wire_load_from_area: s << "wire_load_from_area"; break;
  case AttrType::wire_load_selection: s << "wire_load_selection"; break;
  case AttrType::wire_load_table: s << "wire_load_table"; break;
  case AttrType::wire_load: s << "wire_load"; break;
  case AttrType::x_function: s << "x_function"; break;
  }
  return s;
}

END_NAMESPACE_YM_DOTLIB
