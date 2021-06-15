
.. _timing_group:

timing group statement
=======================

`timing` group はタイミング情報を記述するための group statement である．

::

  timing ( string ) {
    timing 用の属性記述
  }

`string` はオプショナルである．

.. _timing_simple:

simple attributes
------------------

.. _timing_clock_gating_flag:

clock_gating_flag
^^^^^^^^^^^^^^^^^^

::

    clock_gating_flag : true | false ;


.. _timing_default_timing:

default_timing
^^^^^^^^^^^^^^^

::

    default_timing : true | false ;


.. _timing_fall_resistance:

fall_resistance
^^^^^^^^^^^^^^^^

::

    fall_resistance : float ;


.. _timing_fpga_arc_condition:

fpga_arc_condition
^^^^^^^^^^^^^^^^^^^

::

    fpga_arc_condition : "Boolean expression" ;


.. _timing_fpga_domain_style:

fpga_domain_style
^^^^^^^^^^^^^^^^^^

::

    fpga_domain_style : string ;


.. _timing_interdependence_id:

interdependence_id
^^^^^^^^^^^^^^^^^^^

::
    interdependence_id : integer ;


.. _timing_intrinsic_fall:

intrinsic_fall
^^^^^^^^^^^^^^^

::

    intrinsic_fall : float ;


.. _timing_intrinsic_rise:

intrinsic_rise
^^^^^^^^^^^^^^^

::

    intrinsic_rise : float ;


.. _timing_related_bus_equivalent:

related_bus_equivalent
^^^^^^^^^^^^^^^^^^^^^^^

::

    related_bus_equivalent : "name1 [name2 name3 ...]" ;


.. _timing_related_bus_pins:

related_bus_pins
^^^^^^^^^^^^^^^^^

::

    related_bus_pins : "name1 [name2 name3 ...]" ;


.. _timing_related_output_pin:

related_output_pin
^^^^^^^^^^^^^^^^^^^

::

    related_output_pin : string ;


.. _timing_related_pin:

related_pin
^^^^^^^^^^^^

::

    related_pin : "name1 [name2 name3 ..]" ;


.. _timing_rise_resistance:

rise_resistance
^^^^^^^^^^^^^^^^

::

    rise_resistance : float ;


.. _timing_sdf_conf:

sdf_conf
^^^^^^^^^

::

    sdf_conf : "SDF expression" ;


.. _timing_sdf_cond_end:

sdf_cond_end
^^^^^^^^^^^^^

::

    sdf_cond_end : "SDF expression" ;


.. _timing_sdf_cond_start:

sdf_cond_start
^^^^^^^^^^^^^^^

::

    sdf_cond_start : "SDF expression" ;


.. _timing_sdf_edges:

sdf_edges
^^^^^^^^^^

::

    sdf_edges : noedge | start_edge | end_edge | both_edge ;


.. _timing_slope_fall:

slope_fall
^^^^^^^^^^^

::

    slope_fall : float ;


.. _timing_slope_rise:

slope_rise
^^^^^^^^^^^

::

    slope_rise : float ;


.. _timing_steady_state_resistance_above_high:

steady_state_resistance_above_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    steady_state_resistance_above_high : float ;


.. _timing_steady_state_resistance_below_low:

steady_state_resistance_below_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    steady_state_resistance_below_low : float ;


.. _timing_steady_state_resistance_high:

steady_state_resistance_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    steady_state_resistance_high : float ;


.. _timing_steady_state_resistance_low:

steady_state_resistance_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    steady_state_resistance_low : float ;


.. _timing_tied_off:

tied_off
^^^^^^^^^

::

    tied_off : true | false ;


.. _timing_timing_sense:

timing_sense
^^^^^^^^^^^^^

::

    timing_sense : positive_unate | negative_unate | non_unate ;


.. _timing_timing_type:

timing_type
^^^^^^^^^^^^

::

    timing_type : <timing type> ;


.. _timing_wave_fall_sampling_index:

wave_fall_sampling_index
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    wave_fall_sampling_index : integer ;


.. _timing_wave_rise_sampling_index:

wave_rise_sampling_index
^^^^^^^^^^^^^^^^^^^^^^^^^

::

    wave_rise_sampling_index : integer ;


.. _timing_when:

when
^^^^^

::

    when : "Boolean expression" ;


.. _timing_when_end:

when_end
^^^^^^^^^

::

    when_end : "Boolean expression" ;


.. _timing_when_start:

when_start
^^^^^^^^^^^

::

    when_start : "Boolean expression" ;


.. _timing_complex:

complex attributes
-------------------

.. _timing_fall_delay_intercept:

fall_delay_intercept
^^^^^^^^^^^^^^^^^^^^^

::

    fall_delay_intercept ( integer, float ) ;

複数あり


.. _timing_fall_pin_resistance:

fall_pin_resistance
^^^^^^^^^^^^^^^^^^^^

::

    fall_pin_resistance ( integer, float ) ;

複数あり


.. _timing_mode:

mode
^^^^^

::

    mode ( string, string ) ;


.. _timing_pin_name_map:

pin_name_map
^^^^^^^^^^^^^

::

    pin_name_map ( string, string, ... ) ;


.. _timing_rise_delay_intercept:

rise_delay_intercept
^^^^^^^^^^^^^^^^^^^^^

::

    rise_delay_intercept ( integer, float ) ;

複数あり


.. _timing_rise_pin_resistance:

rise_pin_resistance
^^^^^^^^^^^^^^^^^^^^

::

    rise_pin_resistance ( integer, float ) ;

複数あり


.. _timing_wave_fall:

wave_fall
^^^^^^^^^^

::

    wave_fall ( integer, integer, ... ) ;


.. _timing_wave_rise:

wave_rise
^^^^^^^^^^

::

    wave_rise ( integer, integer, ... ) ;


.. _timing_wave_fall_time_interval:

wave_fall_time_interval
^^^^^^^^^^^^^^^^^^^^^^^^

::

    wave_fall_time_interval ( float, float, ... ) ;


.. _timing_wave_rise_time_interval:

wave_rise_time_interval
^^^^^^^^^^^^^^^^^^^^^^^^

::

    wave_rise_time_interval ( float, float, ... ) ;


.. _timing_group_:

group statements
-----------------

.. _timing_cell_degradation:

cell_degradation
^^^^^^^^^^^^^^^^^

::

    cell_degradation () { ... }


.. _timing_cell_fall:

cell_fall
^^^^^^^^^^

::

    cell_fall () { ... }


.. _timing_cell_rise:

cell_rise
^^^^^^^^^^

::

    cell_rise () { ... }


.. _timing_fall_constraint:

fall_constraint
^^^^^^^^^^^^^^^^

::

    fall_constraint () { ... }


.. _timing_fall_propagation:

fall_propagation
^^^^^^^^^^^^^^^^^

::

    fall_propagation () { ... }


.. _timing_fall_transition:

fall_transition
^^^^^^^^^^^^^^^^

::

    fall_transition () { ... }


.. _timing_noise_immunity_above_high:

noise_immunity_above_high
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    noise_immunity_above_high () { ... }


.. _timing_noise_immunity_below_low:

noise_immunity_below_low
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    noise_immunity_below_low () { ... }


.. _timing_noise_immunity_high:

noise_immunity_high
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    noise_immunity_high () { ... }


.. _timing_noise_immunity_low:

noise_immunity_low
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    noise_immunity_low () { ... }


.. _timing_output_current_fall:

output_current_fall
^^^^^^^^^^^^^^^^^^^^

::

    output_current_fall () { ... }


.. _timing_output_current_rise:

output_current_rise
^^^^^^^^^^^^^^^^^^^^

::

    output_current_rise () { ... }


.. _timing_propagated_noise_height_above_high:

propagated_noise_height_above_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_height_above_high () { ... }


.. _timing_propagated_noise_height_below_low:

propagated_noise_height_below_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_height_below_low () { ... }


.. _timing_propagated_noise_height_high:

propagated_noise_height_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_height_high () { ... }


.. _timing_propagated_noise_height_low:

propagated_noise_height_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_height_low () { ... }


.. _timing_propagated_noise_peak_time_ratio_above_high:

propagated_nose_peak_time_ratio_above_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_peak_time_ratio_above_high() { ... }


.. _timing_propagated_noise_peak_time_ratio_below_low:

propagated_nose_peak_time_ratio_below_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_peak_time_ratio_below_low() { ... }


.. _timing_propagated_noise_peak_time_ratio_high:

propagated_nose_peak_time_ratio_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_peak_time_ratio_high() { ... }


.. _timing_propagated_noise_peak_time_ratio_low:

propagated_nose_peak_time_ratio_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_peak_time_ratio_low() { ... }


.. _timing_propagated_noise_width_above_high:

propagated_noise_width_above_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_width_above_high() { ... }


.. _timing_propagated_noise_width_below_low:

propagated_noise_width_below_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_width_below_low() { ... }


.. _timing_propagated_noise_width_high:

propagated_noise_width_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_width_high() { ... }


.. _timing_propagated_noise_width_low:

propagated_noise_width_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    propagated_noise_width_high() { ... }


.. _timing_receiver_capacitance1_fall:

receiver_capacitance1_fall
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    receiver_capacitance1_fall() { ... }


.. _timing_receiver_capacitance1_rise:

receiver_capacitance1_rise
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    receiver_capacitance1_rise() { ... }


.. _timing_receiver_capacitance2_fall:

receiver_capacitance2_fall
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    receiver_capacitance2_fall() { ... }


.. _timing_receiver_capacitance2_rise:

receiver_capacitance2_rise
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    receiver_capacitance2_rise() { ... }


.. _timing_retaining_fall:

retaining_fall
^^^^^^^^^^^^^^^

::

    retaining_fall () { ... }


.. _timing_retaining_rise:

retaining_rise
^^^^^^^^^^^^^^^

::

    retaining_rise () { ... }


.. _timing_retain_fall_slew:

retain_fall_slew
^^^^^^^^^^^^^^^^^

    retain_fall_slew () { ... }


.. _timing_retain_rise_slew:

retain_rise_slew
^^^^^^^^^^^^^^^^^

::

    retain_rise_slew () { ... }


.. _timing_rise_constraint:

rise_constraint
^^^^^^^^^^^^^^^^

::

    rise_constraint () { ... }


.. _timing_rise_propagation:

rise_propagation
^^^^^^^^^^^^^^^^^

::

    rise_propagation () { ... }


.. _timing_rise_transition:

rise_transition
^^^^^^^^^^^^^^^^

::

    rise_transition () { ... }


.. _timing_steady_state_current_high:

steady_state_current_high
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    steady_state_current_high () { ... }


.. _timing_steady_state_current_low:

steady_state_current_low
^^^^^^^^^^^^^^^^^^^^^^^^^

::

    steady_state_current_low () { ... }


.. _timing_steady_state_current_tristate:

steady_state_current_tristate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    steady_state_current_tristate () { ... }
