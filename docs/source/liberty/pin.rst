
.. _pin_group:

pin group statement
===================

`pin` group は端子を記述するための group statement である．
::

  pin ( string, string, ... ) {
    pin 用の属性記述
  }

ヘッダ部分にはピン名を記述する．
同じ属性を持つ複数の端子を定義する時にはピン名を複数記述する．

.. _pin_simple:

simple attributes
------------------

.. _pin_bit_width:

bit_width
^^^^^^^^^^
::

    bit_width : integer ;


.. _pin_capacitance:

capacitance
^^^^^^^^^^^^
::

    capacitance : float ;


.. _pin_clock:

clock
^^^^^^

::

    clock : true | false ;


.. _pin_clock_gate_clock_pin:

clock_gate_clock_pin
^^^^^^^^^^^^^^^^^^^^^

::

    clock_gate_clock_pin : true | false ;


.. _pin_clock_gate_enable_pin:

clock_gate_enable_pin
^^^^^^^^^^^^^^^^^^^^^^

::

    clock_gate_enable_pin : true | false ;


.. _pin_clock_gate_test_pin:

clock_gate_test_pin
^^^^^^^^^^^^^^^^^^^^

::

    clock_gate_test_pin : true | false ;


.. _pin_clock_gate_obs_pin:

clock_gate_obs_pin
^^^^^^^^^^^^^^^^^^^

::

    clock_gate_obs_pin : true | false ;


.. _pin_clock_gate_out_pin:

clock_gate_out_pin
^^^^^^^^^^^^^^^^^^^

::

    clock_gate_out_pin : true | false ;


.. _pin_complementary_pin:

complementary_pin
^^^^^^^^^^^^^^^^^^

::

    complementary_pin : string ;


.. _pin_connection_class:

connection_class
^^^^^^^^^^^^^^^^^

::

    connection_class : string ;


.. _pin_direction:

direction
^^^^^^^^^^

::

    direction : input | output | inout | internal ;

.. _pin_dont_fault:

dont_fault
^^^^^^^^^^^

::

    dont_fault : sa0 | sa1 | sa01 ;


.. _pin_drive_current:

pin_drive_current
^^^^^^^^^^^^^^^^^^

::

    drive_current : float ;


.. _pin_driver_type:

driver_type
^^^^^^^^^^^^

::

    driver_type : pull_up | pull_down | open_drain | open_source |
                  bus_hold | resistive | resistive_0 | resistive_1 ;


.. _pin_fall_capacitance:

fall_capacitance
^^^^^^^^^^^^^^^^^

::

    fall_capacitance : float ;


.. _pin_fall_current_slope_after_threshod:

fall_current_slope_after_threshold
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    fall_current_slope_after_threshold : float ;


.. _pin_fall_current_slope_before_threshold:

fall_current_slope_before_threshold
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    fall_current_slope_before_threshold : float ;


.. _pin_fall_time_after_threshold:

fall_time_after_threshold
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    fall_time_after_threshold : float ;


.. _pin_fall_time_before_threshold:

fall_time_before_threshold
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    fall_time_before_threshold : float ;


.. _pin_fanout_load:

fanout_load
^^^^^^^^^^^^

::

    fanout_load : float ;


.. _pin_fault_model:

fault_model
^^^^^^^^^^^^

::

    fault_model "two-value string" ;

有効な値のパタンは `[01x][01x]`


.. _pin_function:

function
^^^^^^^^^

::

    function : "Boolean expression" ;


.. _pin_has_builtin_pad:

has_builtin_pad
^^^^^^^^^^^^^^^^

::

    has_builtin_pad : true | false ;


.. _pin_hysteresis:

hysteresis
^^^^^^^^^^^

::

    hysteresis : true | false ;


.. _pin_input_map:

input_map
^^^^^^^^^^

::

    input_map : name_(id) ;

`name` には空白で区切られた入力ピン名のリストを与える．


.. _pin_input_signal_level:

input_signal_level
^^^^^^^^^^^^^^^^^^^

::

    input_signal_level : name_(id) ;


.. _pin_input_threshold_pct_fall:

input_threshold_pct_fall
^^^^^^^^^^^^^^^^^^^^^^^^^

::

    input_threshold_pct_fall : float ;


.. _pin_input_threshold_pct_rise:

input_threshold_pct_rise
^^^^^^^^^^^^^^^^^^^^^^^^^

::

    input_threshold_pct_rise : float ;


.. pin_input_voltage:

input_voltage
^^^^^^^^^^^^^^

::

    input_voltage : name_(id) ;


.. _pin_internal_node:

internal_node
^^^^^^^^^^^^^

::

    internal_node : pin_name_(id) ;


.. _pin_inverted_output:

interted_output
^^^^^^^^^^^^^^^^

::

    inverted_output : true | false ;


.. _pin_is_pad:

is_pad
^^^^^^^

::

    is_pad : true | false ;


.. _pin_isolation_cell_enable_pin:

isolation_cell_enable_pin
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    isolation_cell_enable_pin : true | false ;


.. _pin_level_shifter_enable_pin:

level_shifter_enable_pin
^^^^^^^^^^^^^^^^^^^^^^^^^

::

    level_shifter_enable_pin : true | false ;


.. _pin_map_to_logic:

map_to_logic
^^^^^^^^^^^^^

::

    map_to_logic : 1 | 0 ;

なんでこれが Boolean expression なの？


.. _pin_max_capacitance:

max_capacitance
^^^^^^^^^^^^^^^^

::

    max_capacitance : float ;


.. _pin_max_fanout:

max_fanout
^^^^^^^^^^^

::

    max_fanout : float ;


.. _pin_max_input_noise_width:

max_input_noise_width
^^^^^^^^^^^^^^^^^^^^^^

::

    max_input_noise_width : float ;


.. _pin_max_transition:

max_transition
^^^^^^^^^^^^^^^

::

    max_transition : float ;


.. _pin_min_capacitance:

min_capacitance
^^^^^^^^^^^^^^^^

::

    min_capacitance : float ;


.. _pin_min_fanout:

min_fanout
^^^^^^^^^^^

::

    min_fanout : float ;


.. _pin_min_input_noise_width:

min_input_nose_width
^^^^^^^^^^^^^^^^^^^^^

::

    min_input_noise_width : float ;


.. _pin_min_period:

min_period
^^^^^^^^^^^

::

    min_period : float ;


.. _pin_min_pulse_width_low:

min_pulse_width_low
^^^^^^^^^^^^^^^^^^^

::

    min_pulse_width_low : float ;


.. _pin_min_pulse_width_high:

min_pulse_width_high
^^^^^^^^^^^^^^^^^^^^^^

::

    min_pulse_width_high : float ;


.. _pin_min_transition:

min_transition
^^^^^^^^^^^^^^

::

    min_transition : float ;


.. _pin_multicell_pad_pin:

multicell_pad_pin
^^^^^^^^^^^^^^^^^^

::

    multicell_pad_pin : true | false ;


.. _pin_nextstate_type:

nextstate_type
^^^^^^^^^^^^^^^

::

    nextstate_type : data | preset | clear | load | scan_in | scan_enable ;


.. _pin_output_signal_level:

output_signal_level
^^^^^^^^^^^^^^^^^^^^^

::

    output_signal_level : name_(id) ;


.. _pin_output_voltage:

output_voltage
^^^^^^^^^^^^^^^

::

    output_voltage : name_(id) ;


.. _pin_pg_function:

pg_function
^^^^^^^^^^^^

::

    pg_function : "<function_string>" ; ?? たぶん "Boolean expression"


.. _pin_pin_func_type:

pin_func_type
^^^^^^^^^^^^^^

::

    pin_func_type : clock_enable | active_high | active_low |
                     active_rising | active_falling ;


.. _pin_power_down_function:

power_down_function
^^^^^^^^^^^^^^^^^^^^

::

    power_down_function : "<function string>" ;

指定する値はたぶん "Boolean expression"


.. _pin_prefer_tied:

prefer_tied
^^^^^^^^^^^^

::

    prefer_tied : "0" | "1" ;


.. _pin_primary_output:

primary_output
^^^^^^^^^^^^^^^

::

    primary_output : true | false ;


.. _pin_pulling_current:

pulling_current
^^^^^^^^^^^^^^^^

::

    pulling_current : float ;

マニュアルには正確な記述なし．


.. _pin_pulling_resistance:

pulling_resistance
^^^^^^^^^^^^^^^^^^^

::

    pulling_resistance : float ;


.. _pin_pulse_clock:

pulse_clock
^^^^^^^^^^^^

::

    pulse_clock : rise_triggered_high_pulse |
                  rise_triggered_low_pulse |
                  fall_triggered_high_pulse |
                  fall_triggered_low_pulse ;


.. _pin_related_ground_pin:

related_ground_pin
^^^^^^^^^^^^^^^^^^^

::

    related_ground_pin : pg_pin_name_(id) ;


.. _pin_related_power_pin:

related_power_pin
^^^^^^^^^^^^^^^^^^

::

    related_power_pin : pg_pin_name_(id) ;


.. _pin_rise_capacitance:

rise_capacitance
^^^^^^^^^^^^^^^^^^

::

    rise_capacitance : float ;


.. _pin_rise_current_slope_after_threshold:

rise_current_slope_after_threshold
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    rise_current_slope_after_threshold : float ;


.. _pin_rise_current_slope_before_threshold:

rise_current_slope_before_threshold
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    rise_current_slope_before_threshold : float ;


.. _pin_rise_time_after_threshold:

rise_time_after_threshold
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    rise_time_after_threshold : float ;


.. _pin_rise_time_before_threhold:

rise_time_before_threshold
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    rise_time_before_threshold : float ;


.. _pin_signal_type:

signal_type
^^^^^^^^^^^^

::

    signal_type : test_scan_in | test_scan_in_inverted |
                  test_scan_out | test_scan_out_inverted |
                  test_scan_enable | test_scan_enable_inverted |
                  test_scan_clock | test_scan_clock_a |
                  test_scan_clock_b | test_clock ;


.. _pin_slew_control:

slew_control
^^^^^^^^^^^^^

::

    slew_control : low | medium | high | none ;


.. _pin_slew_lower_threshold_pct_fall:

slew_lower_threshold_pct_fall
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    slew_lower_threshold_pct_fall : float ;


.. _pin_slew_lower_threshold_pct_rise:

slew_lower_threshold_pct_rise
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    slew_lower_threshold_pct_rise : float ;


.. _pin_slew_upper_threshold_pct_fall:

slew_upper_threshold_pct_fall
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    slew_upper_threshold_pct_fall : float ;


.. _pin_slew_upper_threshold_pct_rise:

slew_upper_threshold_pct_rise
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    slew_upper_threshold_pct_rise : falot ;


.. _pin_state_function:

state_function
^^^^^^^^^^^^^^^

::

    state_function : "Boolean expression" ;


.. _pin_std_cell_main_rail:

std_cell_main_rail
^^^^^^^^^^^^^^^^^^^

::

    std_cell_main_rail : true | false ;


.. _pin_switch_function:

switch_function
^^^^^^^^^^^^^^^^

::

    switch_function : function_string ;

値はたぶん"Boolean expression" のこと？


.. _pin_switch_pin:

switch_pin
^^^^^^^^^^^

::

    switch_pin : true | false ;


.. _pin_test_output_only:

test_output_only
^^^^^^^^^^^^^^^^^

::

    test_output_only : true | false ;


.. _pin_three_state:

three_state
^^^^^^^^^^^^

::

    three_state : "Boolean expression" ;


.. _pin_vhdl_name:

vhdl_name
^^^^^^^^^^

::

    vhdl_name : "name_(string)" ;


.. _pin_x_function:

x_function
^^^^^^^^^^^

::

    x_function : "Boolean expression" ;


.. _pin_complex:

complex attributes
--------------------

.. _pin_fall_capacitance_range:

fall_capacitance_range
^^^^^^^^^^^^^^^^^^^^^^^

::

    fall_capacitance_range (value_1_(float), value_2_(float)) ;


.. _pin_power_gating_pin:

power_gating_pin
^^^^^^^^^^^^^^^^^

::

    power_gating_pin : (value_1_(enum), value2_(Boolean)) ;

たぶん value_1 は string, value2 は integer


.. _pin_rise_capacitance_range:

rise_capacitance_range
^^^^^^^^^^^^^^^^^^^^^^^

::

    rise_capacitance_range : (value_1_(float), value_2(float)) ;


.. _pin_group_:

group statements
-----------------

.. _pin_ccsn_first_stage:

ccsn_first_stage
^^^^^^^^^^^^^^^^^

::

    ccsn_first_stage () { ... }


.. _pin_ccsn_last_stage:

ccsn_last_stage
^^^^^^^^^^^^^^^^

::

    ccsn_last_stage () { ... }


.. _pin_dc_current:

dc_current
^^^^^^^^^^^

::

    dc_current () { ... }


.. _pin_electromigration:

electromigration
^^^^^^^^^^^^^^^^

::

    electromigration () { ... }


.. _pin_hyperbolic_noise_above_high:

hyperbolic_noise_above_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    hyperbolic_noise_above_high () { ... }


.. _pin_hyperbolic_noise_below_low:

hyperbolic_noise_below_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    hyperbolic_noise_below_low () { ... }


.. _pin_hyperbolic_noise_high:

hyperbolic_noise_high
^^^^^^^^^^^^^^^^^^^^^^

::

    hyperbolic_noise_high () { ... }


.. _pin_hyperbolic_noise_low:

hyperbolic_noise_low
^^^^^^^^^^^^^^^^^^^^

::

    hyperbolic_noise_low () { ... }


.. _pin_input_signal_swing:

input_signal_swing
^^^^^^^^^^^^^^^^^^^

::

    input_signal_swing () { ... }


.. _pin_internal_power:

internal_power
^^^^^^^^^^^^^^

::

    internal_power() { ... }


.. _pin_max_trans:

max_trans
^^^^^^^^^^^^^^^

::

    max_trans () { ... }


.. _pin_min_pulse_width:

min_pulse_width
^^^^^^^^^^^^^^^^^

::

    min_pulse_width () { ... }


.. _pin_minimum_period:

minumum_period
^^^^^^^^^^^^^^^

::

    minimum_period () { ... }


.. _pin_output_signal_swing:

output_signal_swing
^^^^^^^^^^^^^^^^^^^

::

    output_signal_swing () { ... }


.. _pin_pin_capacitance:

pin_capacitance
^^^^^^^^^^^^^^^

::

    pin_capacitance () { ... }


.. _pin_timing:

timing
^^^^^^^

::

    timing ( string ) { ... }

ヘッダの `string` はオプショナル．
:ref:`timing_group`

.. _pin_tlatch:

tlatch
^^^^^^^

::

    tlatch () { ... }
