#! /usr/bin/env python3

### @file gen_attr_type.py
### @brief 属性値関係のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)nn
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.n

### Usage: gen_attr_code.py --header > AttrType.h
###        gen_attr_code.py --source > AttrDic.cc

import sys
import argparse
import os.path


# 予約語(属性値)のリスト
attr_list = [
   'none',
   'area',
   'auxiliary_pad_cell',
   'base_name',
   'bit_width',
   'bundle',
   'bus',
   'bus_naming_style',
   'bus_type',
   'calc_mode',
   'capacitance',
   'capacitive_load_unit',
   'cell',
   'cell_degradation',
   'cell_fall',
   'cell_footprint',
   'cell_leakage_power',
   'cell_rise',
   'clear',
   'clear_preset_var1',
   'clear_preset_var2',
   'clock',
   'clock_gate_clock_pin',
   'clock_gate_enable_pin',
   'clock_gate_test_pin',
   'clock_gate_obs_pin',
   'clock_gate_out_pin',
   'clock_gating_flag',
   'clock_gating_integrated_cell',
   'clocked_on',
   'clocked_on_also',
   'coefs',
   'comment',
   'complementary_pin',
   'connection_class',
   'contention_condition',
   'current_unit',
   'data_in',
   'date',
   'dc_current_template',
   'default_cell_leakage_power',
   'default_connection_class',
   'default_fall_delay_intercept',
   'default_fall_pin_resistance',
   'default_fanout_load',
   'default_inout_pin_cap',
   'default_inout_pin_fall_res',
   'default_inout_pin_rise_res',
   'default_input_pin_cap',
   'default_intrinsic_fall',
   'default_intrinsic_rise',
   'default_leakage_power_density',
   'default_max_capacitance',
   'default_max_fanout',
   'default_max_transition',
   'default_max_utilization',
   'default_min_porosity',
   'default_operating_conditions',
   'default_output_pin_cap',
   'default_output_pin_fall_res',
   'default_output_pin_rise_res',
   'default_part',
   'default_rise_delay_intercept',
   'default_rise_pin_resistance',
   'default_slope_fall',
   'default_slope_rise',
   'default_timing',
   'default_wire_load_area',
   'default_wire_load_capacitance',
   'default_wire_load_mode',
   'default_wire_load_resistance',
   'default_wire_load_selection',
   'default_wire_load',
   'define_cell_area',
   'define_group',
   'define',
   'delay_model',
   'direction',
   'domain',
   'dont_fault',
   'dont_touch',
   'dont_use',
   'drive_current',
   'driver_type',
   'dynamic_current',
   'edge_rate_sensitivity_f0',
   'edge_rate_sensitivity_f1',
   'edge_rate_sensitivity_r0',
   'edge_rate_sensitivity_r1',
   'edif_name',
   'electromigration',
   'em_lut_template',
   'em_temp_degradation_factor',
   'enable_also',
   'enable',
   'equal_or_opposite_output',
   'fall_capacitance_range',
   'fall_capacitance',
   'fall_constraint',
   'fall_current_slope_after_threshold',
   'fall_current_slope_before_threshold',
   'fall_delay_intercept',
   'fall_pin_resistance',
   'fall_power',
   'fall_propagation',
   'fall_resistance',
   'fall_time_after_threshold',
   'fall_time_before_threshold',
   'fall_transition_degradation',
   'fall_transition',
   'falling_together_group',
   'fanout_area',
   'fanout_capacitance',
   'fanout_length',
   'fanout_load',
   'fanout_resistance',
   'fault_model',
   'faults_lut_template',
   'ff',
   'ff_bank',
   'fpga_arc_condition',
   'fpga_domain_style',
   'fpga_technology',
   'function',
   'functional_yield_metric',
   'generated_clock',
   'geometry_print',
   'handle_negative_constraint',
   'has_builtin_pad',
   'hyperbolic_noise_above_high',
   'hyperbolic_noise_below_low',
   'hyperbolic_noise_high',
   'hyperbolic_noise_low',
   'hysteresis',
   'in_place_swap_mode',
   'index_1',
   'index_2',
   'index_3',
   'input_map',
   'input_signal_level',
   'input_threshold_pct_fall',
   'input_threshold_pct_rise',
   'input_voltage',
   'interdependence_id',
   'interface_timing',
   'internal_node',
   'internal_power',
   'intrinsic_fall',
   'intrinsic_parasitic',
   'intrinsic_rise',
   'inverted_output',
   'io_type',
   'is_clock_gating_cell',
   'is_filler_cell',
   'is_pad',
   'isolation_cell_enable_pin',
   'iv_lut_template',
   'k_process_cell_fall',
   'k_process_cell_leakage_power',
   'k_process_cell_rise',
   'k_process_drive_current',
   'k_process_drive_fall',
   'k_process_drive_rise',
   'k_process_fall_delay_intercept',
   'k_process_fall_pin_resistance',
   'k_process_fall_propagation',
   'k_process_fall_transition',
   'k_process_hold_fall',
   'k_process_hold_rise',
   'k_process_internal_power',
   'k_process_intrinsic_fall',
   'k_process_intrinsic_rise',
   'k_process_min_period',
   'k_process_min_pulse_width_high',
   'k_process_min_pulse_width_low',
   'k_process_nochange_fall',
   'k_process_nochange_rise',
   'k_process_pin_cap',
   'k_process_recovery_fall',
   'k_process_recovery_rise',
   'k_process_removal_fall',
   'k_process_removal_rise',
   'k_process_rise_transition',
   'k_process_rise_delay_intercept',
   'k_process_rise_pin_resistance',
   'k_process_rise_propagation',
   'k_process_setup_fall',
   'k_process_setup_rise',
   'k_process_skew_fall',
   'k_process_skew_rise',
   'k_process_slope_fall',
   'k_process_slope_rise',
   'k_process_wire_cap',
   'k_process_wire_res',
   'k_temp_cell_fall',
   'k_temp_cell_leakage_power',
   'k_temp_cell_rise',
   'k_temp_drive_current',
   'k_temp_drive_fall',
   'k_temp_drive_rise',
   'k_temp_fall_delay_intercept',
   'k_temp_fall_pin_resistance',
   'k_temp_fall_propagation',
   'k_temp_fall_transition',
   'k_temp_hold_fall',
   'k_temp_hold_rise',
   'k_temp_internal_power',
   'k_temp_intrinsic_fall',
   'k_temp_intrinsic_rise',
   'k_temp_min_period',
   'k_temp_min_pulse_width_high',
   'k_temp_min_pulse_width_low',
   'k_temp_nochange_fall',
   'k_temp_nochange_rise',
   'k_temp_pin_cap',
   'k_temp_recovery_fall',
   'k_temp_recovery_rise',
   'k_temp_removal_fall',
   'k_temp_removal_rise',
   'k_temp_rise_transition',
   'k_temp_rise_delay_intercept',
   'k_temp_rise_pin_resistance',
   'k_temp_rise_propagation',
   'k_temp_setup_fall',
   'k_temp_setup_rise',
   'k_temp_skew_fall',
   'k_temp_skew_rise',
   'k_temp_slope_fall',
   'k_temp_slope_rise',
   'k_temp_wire_cap',
   'k_temp_wire_res',
   'k_volt_cell_fall',
   'k_volt_cell_leakage_power',
   'k_volt_cell_rise',
   'k_volt_drive_current',
   'k_volt_drive_fall',
   'k_volt_drive_rise',
   'k_volt_fall_delay_intercept',
   'k_volt_fall_pin_resistance',
   'k_volt_fall_propagation',
   'k_volt_fall_transition',
   'k_volt_hold_fall',
   'k_volt_hold_rise',
   'k_volt_internal_power',
   'k_volt_intrinsic_fall',
   'k_volt_intrinsic_rise',
   'k_volt_min_period',
   'k_volt_min_pulse_width_high',
   'k_volt_min_pulse_width_low',
   'k_volt_nochange_fall',
   'k_volt_nochange_rise',
   'k_volt_pin_cap',
   'k_volt_recovery_fall',
   'k_volt_recovery_rise',
   'k_volt_removal_fall',
   'k_volt_removal_rise',
   'k_volt_rise_transition',
   'k_volt_rise_delay_intercept',
   'k_volt_rise_pin_resistance',
   'k_volt_rise_propagation',
   'k_volt_setup_fall',
   'k_volt_setup_rise',
   'k_volt_skew_fall',
   'k_volt_skew_rise',
   'k_volt_slope_fall',
   'k_volt_slope_rise',
   'k_volt_wire_cap',
   'k_volt_wire_res',
   'latch',
   'latch_bank',
   'leakage_current',
   'leakage_power_unit',
   'leakage_power',
   'level_shifter_enable_pin',
   'library_features',
   'library',
   'lu_table_template',
   'lut',
   'map_only',
   'map_to_logic',
   'max_capacitance',
   'max_fanout',
   'max_input_noise_width',
   'max_trans',
   'max_transition',
   'members',
   'min_capacitance',
   'min_fanout',
   'min_input_noise_width',
   'min_period',
   'min_pulse_width_high',
   'min_pulse_width_low',
   'min_pulse_width',
   'min_transition',
   'minimum_period',
   'mode_definition',
   'multicell_pad_pin',
   'next_state',
   'nextstate_type',
   'noise_immunity_above_high',
   'noise_immunity_below_low',
   'noise_immunity_high',
   'noise_immunity_low',
   'noise_lut_template',
   'nom_calc_mode',
   'nom_process',
   'nom_temperature',
   'nom_voltage',
   'operating_conditions',
   'orders',
   'output_current_fall',
   'output_current_rise',
   'output_current_template',
   'output_signal_level',
   'output_threshold_pct_fall',
   'output_threshold_pct_rise',
   'output_voltage',
   'pad_cell',
   'pad_type',
   'parameter1',
   'parameter2',
   'parameter3',
   'parameter4',
   'parameter5',
   'part',
   'pg_function',
   'piece_define',
   'piece_type',
   'pin',
   'pin_func_type',
   'pin_opposite',
   'poly_template',
   'power',
   'power_cell_type',
   'power_down_function',
   'power_level',
   'power_lut_template',
   'power_poly_template',
   'power_model',
   'power_rail',
   'power_supply_namestring',
   'power_supply',
   'prefer_tied',
   'preferred',
   'preferred_input_pad_voltage',
   'preferred_output_pad_slew_rate_control',
   'preferred_output_pad_voltage',
   'preset',
   'primary_output',
   'process',
   'propagated_noise_height_above_high',
   'propagated_noise_height_below_low',
   'propagated_noise_height_high',
   'propagated_noise_height_low',
   'propagated_noise_peak_time_ratio_above_high',
   'propagated_noise_peak_time_ratio_below_low',
   'propagated_noise_peak_time_ratio_high',
   'propagated_noise_peak_time_ratio_low',
   'propagated_noise_width_above_high',
   'propagated_noise_width_below_low',
   'propagated_noise_width_high',
   'propagated_noise_width_low',
   'propagation_lut_template',
   'pulling_current',
   'pulling_resistance_unit',
   'pulling_resistance',
   'pulse_clock',
   'rail_connection',
   'related_bus_equivalent',
   'related_bus_pins',
   'related_ground_pin',
   'related_inputs',
   'related_output_pin',
   'related_outputs',
   'related_pg_pin',
   'related_pin',
   'related_power_pin',
   'resistance',
   'resource_usage',
   'retain_fall_slew',
   'retain_rise_slew',
   'retaining_fall',
   'retaining_rise',
   'revision',
   'rise_capacitance_range',
   'rise_capacitance',
   'rise_constraint',
   'rise_current_slope_after_threshold',
   'rise_current_slope_before_threshold',
   'rise_delay_intercept',
   'rise_pin_resistance',
   'rise_power',
   'rise_propagation',
   'rise_resistance',
   'rise_time_after_threshold',
   'rise_time_before_threshold',
   'rise_transition_degradation',
   'rise_transition',
   'rising_together_group',
   'routing_layers',
   'routing_track',
   'scaled_cell',
   'scaling_factors',
   'sdf_cond',
   'sdf_cond_end',
   'sdf_cond_start',
   'sdf_edges',
   'signal_type',
   'simulation',
   'single_bit_degenerate',
   'slew_control',
   'slew_derate_from_library',
   'slew_lower_threshold_pct_fall',
   'slew_lower_threshold_pct_rise',
   'slew_type',
   'slew_upper_threshold_pct_fall',
   'slew_upper_threshold_pct_rise',
   'slope',
   'slope_fall',
   'slope_rise',
   'state_function',
   'statetable',
   'std_cell_main_rail',
   'steady_state_current_above_high',
   'steady_state_current_below_low',
   'steady_state_current_high',
   'steady_state_current_low',
   'steady_state_current_tristate',
   'steady_state_resistance_above_high',
   'steady_state_resistance_below_low',
   'switch_function',
   'switch_pin',
   'switching_interval',
   'switching_together_group',
   'table',
   'technology',
   'temperature',
   'test_cell',
   'test_output_only',
   'three_state',
   'tied_off',
   'time_unit',
   'timing_model_type',
   'timing_range',
   'timing_sense',
   'timing_type',
   'timing',
   'tlatch',
   'tree_type',
   'type',
   'use_for_size_only',
   'value',
   'values',
   'variable_1',
   'variable_1_range',
   'variable_2',
   'variable_2_range',
   'variable_3',
   'variable_3_range',
   'vhdl_name',
   'vih',
   'vil',
   'vimax',
   'vimin',
   'voh',
   'vol',
   'voltage_unit',
   'voltage',
   'vomax',
   'vomin',
   'when_end',
   'when_start',
   'when',
   'wire_load_from_area',
   'wire_load_selection',
   'wire_load_table',
   'wire_load',
   'x_function',
]

def conv_to_type(attr_str) :
    return 'AttrType::{}'.format(attr_str)

# BOMコードを出力する．
def write_BOM(fout) :
    fout.write('\ufeff')


if __name__ == '__main__' :

    parser = argparse.ArgumentParser()

    mode_group = parser.add_mutually_exclusive_group()
    mode_group.add_argument('--source',
                            action = 'store_true',
                            help = 'generate dict code')
    mode_group.add_argument('--header',
                            action = 'store_true',
                            help = 'generate attribute list')
    mode_group.add_argument('--sout',
                            action = 'store_true',
                            help = 'generate stream out code')

    args = parser.parse_args()
    if not args :
        exit(1)

    fout = sys.stdout

    if args.source :
        write_BOM(fout)
        str = """
/// @file AttrDic.cc
/// @brief AttrDic の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AttrDic.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AttrDic
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AttrDic::AttrDic()
{
"""
        fout.write(str)
        for attr_str in attr_list :
            attr_type = conv_to_type(attr_str)
            fout.write('  mDic.add("{}", {});\n'.format(attr_str, attr_type))
        str = """}

// @brief AttrType の内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   AttrType attr)
{
  switch ( attr ) {
"""
        fout.write(str)
        for attr_str in attr_list :
            attr_type = conv_to_type(attr_str)
            fout.write('  case {}: s << "{}"; break;\n'.format(attr_type, attr_str))
        str = """  }
  return s;
}

END_NAMESPACE_YM_DOTLIB
"""
        fout.write(str)
    elif args.header :
        write_BOM(fout)
        str = """#ifndef ATTRTYPE_H
#define ATTRTYPE_H

/// @file AttrType.h
/// @brief 属性を表す列挙型
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib_nsdef.h"
#include "ym/HashFunc.h"

BEGIN_NAMESPACE_YM_DOTLIB

/// @brief 属性を表す列挙型
enum class AttrType {
"""
        fout.write(str)
        for attr_str in attr_list :
            fout.write('  {},\n'.format(attr_str))
        str = """};

/// @brief AttrType の内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   AttrType attr);

END_NAMESPACE_YM_DOTLIB

BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
// HashFunc<> の特殊化
//////////////////////////////////////////////////////////////////////
template<>
struct
HashFunc<nsClib::nsDotlib::AttrType>
{
  SizeType
  operator()(nsClib::nsDotlib::AttrType key) const {
    return static_cast<SizeType>(key);
  }
};

END_NAMESPACE_YM

#endif // ATTRTYPE_H
"""
        fout.write(str)
    else :
        print('Either "--source" or "--header" should be specified.')
        exit(1)
