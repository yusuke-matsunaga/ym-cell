attr_list = [
   'none',
   'area',
   'auxiliary_pad_cell',
   'base_name',
   'bit_width',
   'bundle',
   'bus_naming_style',
   'bus_type',
   'bus',
   'calc_mode',
   'capacitance',
   'capacitive_load_unit',
   'cell_degradation',
   'cell_fall',
   'cell_footprint',
   'cell_leakage_power',
   'cell_rise',
   'cell',
   'clear_preset_var1',
   'clear_preset_var2',
   'clear',
   'clock_gate_clock_pin',
   'clock_gate_enable_pin',
   'clock_gate_test_pin',
   'clock_gate_obs_pin',
   'clock_gate_out_pin',
   'clock_gating_integrated_cell',
   'clock',
   'clocked_on_also',
   'clocked_on',
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
   'ff_bank',
   'ff',
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
   'latch_bank',
   'latch',
   'leakage_current',
   'leakage_power_unit',
   'leakage_power',
   'library_features',
   'library',
   'lu_table_template',
   'lut',
   'map_only',
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
   'piece_define',
   'piece_type',
   'pin_func_type',
   'pin_opposite',
   'pin',
   'poly_template',
   'power_cell_type',
   'power_level',
   'power_lut_template',
   'power_poly_template',
   'power_model',
   'power_rail',
   'power_supply_namestring',
   'power_supply',
   'power',
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
   'rail_connection',
   'related_bus_equivalent',
   'related_bus_pins',
   'related_inputs',
   'related_output_pin',
   'related_outputs',
   'related_pg_pin',
   'related_pin',
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
   'sdf_cond_end',
   'sdf_cond_start',
   'sdf_cond',
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
   'slope_fall',
   'slope_rise',
   'slope',
   'state_function',
   'statetable',
   'steady_state_current_high',
   'steady_state_current_low',
   'steady_state_current_tristate',
   'switching_interval',
   'switching_together_group',
   'table',
   'technology',
   'temperature',
   'test_cell',
   'test_output_only',
   'three_state',
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
   'variable_2',
   'variable_3',
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