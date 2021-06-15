
.. _cell_group:

cell group statement
=====================

`cell` group は cell を記述するための group statement である．

::

  cell ( name_(string) ) {
    cell 用の属性記述
    ...
  }

ヘッダ部分にはセル名を記述する．

以下に `cell` 用の属性を記す．

.. _cell_simple:

simple attributes
------------------

.. _cell_area:

area
^^^^^

::

    area : value_(float) ;

セルの面積を指定する．


.. _cell_auxiliary_pad_cell:

auxiary_pad_cell
^^^^^^^^^^^^^^^^^

::

    auxiliary_pad_cell : true | false ;


.. _cell_base_name:

base_name
^^^^^^^^^^

::

    base_name : cell_base_name_(string) ;


.. _cell_bus_naming_style:

bus_naming_style
^^^^^^^^^^^^^^^^^

::

    bus_naming_style : "string" ;


.. _cell_cell_footprint:

cell_footprint
^^^^^^^^^^^^^^^

::

    cell_footprint : footprint_type_(string) ;


.. _cell_cell_leakage_power:

cell_leakage_power
^^^^^^^^^^^^^^^^^^^

;;

    cell_leakage_power : value_(float) ;


.. _cell_clock_gating_integrated_cell:

clock_gating_integrated_cell
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    clock_gating_integrated_cell : string_value ;


.. _cell_contention_condition:

contention_condition
^^^^^^^^^^^^^^^^^^^^^

::

    contention_condition : "Boolean expression" ;


.. _cell_dont_fault:

dont_fault
^^^^^^^^^^^

::

    dont_fault : sa0 | sa1 | sa01 ; // string


.. _cell_dont_touch:

dont_touch
^^^^^^^^^^^

::

    dont_touch : true | false ;


.. _cell_dont_use:

dont_use
^^^^^^^^^

::

    dont_use : true | false ;


.. _cell_driver_type:

driver_type
^^^^^^^^^^^^

::

    driver_type : name_(id) ;


.. _cell_edif_name:

edif_name
^^^^^^^^^^

::

    edif_name : name_(id) ;


.. _cell_em_temp_degradation_factor:

em_temp_degradation_factor
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    em_temp_degradation_factor : value_(float) ;


.. _cell_fpga_cell_type:

fpga_cell_type
^^^^^^^^^^^^^^^

::

    fpga_cell_type : value_(enum) ;

値として有効な値は以下の通り．

::

   rising_edge_clock_cell, falling_edge_clock_cell


.. _cell_fpga_domain_style:

fpga_domain_style
^^^^^^^^^^^^^^^^^^

::

    fpga_domain_style : name_(id) ;


.. _cell_geometry_print:

geometry_print
^^^^^^^^^^^^^^^

::


    geometry_print : string ;


.. _cell_handle_negative_constraint:

handle_negative_constraint
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

    handle_negative_constraint : true | false ;


.. _cell_interface_timing:

interface_timing
^^^^^^^^^^^^^^^^^

::

    interface_timing : true | false ;


.. _cell_io_type:

io_type
^^^^^^^^

::

    io_type : name_(id) ;


.. _cell_is_clock_gating_cell:

is_clock_gating_cell
^^^^^^^^^^^^^^^^^^^^^

::

    is_clock_gating_cell : true | false ;


.. _cell_is_isolation_cell:

is_isolation_cell
^^^^^^^^^^^^^^^^^

::

    is_isolation_cell : true | false ;

マニュアルには Boolean expression と書いてある．


.. _cell_is_level_shifter:

is_level_shifter
^^^^^^^^^^^^^^^^^

::

    is_level_shifter : true | false ;


.. _cell_level_shifter_type:

level_shifter_type
^^^^^^^^^^^^^^^^^^^

::

    level_shifter_type : LH | HL | HL_LH ;

デフォルト値は `HL_LH`


.. _cell_map_only:

map_only
^^^^^^^^^

::

    map_only : true | false ;


.. _cell_pad_cell:

pad_cell
^^^^^^^^^

::

    pad_cell : true | false ;


.. _cell_pad_type:

pad_type
^^^^^^^^^

::

    pad_type : clock ;

`clock` のみが有効


.. _cell_power_cell_type:

power_cell_type
^^^^^^^^^^^^^^^^

::

    power_cell_type : stdcell | macro ;


.. _cell_power_gating_cell:

power_gating_cell
^^^^^^^^^^^^^^^^^^

::

    power_gating_cell : string ;


.. _cell_preferred:

preferred
^^^^^^^^^^

::

    preferred : true | false ;


.. _cell_scaling_factors:

scaling_factors
^^^^^^^^^^^^^^^^

::

    scaling_factors : group_name ;


.. _cell_sensitization_master:

sensitization_master
^^^^^^^^^^^^^^^^^^^^^

::

    sensitization_master : string ;


.. _cell_single_bit_degenerate:

single_bit_degenerate
^^^^^^^^^^^^^^^^^^^^^^^

::

    single_bit_degenerate : string ;


.. _cell_slew_type:

slew_type
^^^^^^^^^^

::

    slew_type : name_(id) ;


.. _cell_switch_cell_type:

switch_cell_type
^^^^^^^^^^^^^^^^^

::

    switch_cell_type : string ;

例では coarse_grain


.. _cell_threshold_voltage_group:

threshold_voltage_group
^^^^^^^^^^^^^^^^^^^^^^^^

::

    threshold_voltage_group : string ;


.. _cell_timing_model_type:

timing_model_type
^^^^^^^^^^^^^^^^^^

::

    timing_model_type : abstracted | extracted | qtm ;


.. _cell_use_for_size_only:

use_for_size_only
^^^^^^^^^^^^^^^^^^

::

   use_for_size_only : true | false ;


.. _cell_vhdl_name:

vhdl_name
^^^^^^^^^^

::

    vhdl_name : "string" ;


.. _cell_complex:

complex attributes
------------------

.. _cell_input_voltage_range:

input_voltage_range
^^^^^^^^^^^^^^^^^^^^

::

    input_voltage_range ( float, float ) ;


.. _cell_output_voltage_range:

output_voltage_range
^^^^^^^^^^^^^^^^^^^^^

::

    output_voltage_range ( float, float ) ;


.. _cell_pin_equal:

pin_equal
^^^^^^^^^

::

    pin_equal ( "name_list_(string)" ) ;

多分，複数あり


.. _cell_pin_name_map:

pin_name_map
^^^^^^^^^^^^^

::

    pin_name_map ( string, string, ... ) ;

多分，複数あり


.. _cell_pin_opposite:

pin_opposite
^^^^^^^^^^^^^

::

    pin_opposite ( "name_list1_(string)", "name_list2_(string)" ) ;

多分，複数あり


.. _cell_rail_connection:

rail_connection
^^^^^^^^^^^^^^^^

::

    rail_connection ( connection_name_(string), power_supply_name_(string) ) ;

複数あり


.. _cell_resource_usage:

resource_usage
^^^^^^^^^^^^^^^

::

    resource_usage ( resource_name_(id), number_of_resources_(id) ) ;

複数あり


.. _cell_group_:

group statement
---------------------

.. _cell_bundle:

bundle
^^^^^^^

::

    bundle ( name_(string) ) { }

複数あり


.. _cell_bus:

bus
^^^^

::

    bus ( name_(string) ) { }

複数あり


.. _cell_dynamic_current:

dynamic_current
^^^^^^^^^^^^^^^^

::

    dynamic_current () { }


.. _cell_ff:

ff
^^^

::

    ff ( variable1_(string), variable2_(string) ) { }


.. _cell_ff_bank:

ff_bank
^^^^^^^^

::

    ff_bank ( variable1_(string), variable2_(string), bits_(integer) ) { }


.. _cell_functional_yield_metric:

functional_yield_metric
^^^^^^^^^^^^^^^^^^^^^^^^

::

    functional_yield_metric () { }


.. _cell_generated_clock:

generated_clock
^^^^^^^^^^^^^^^^

::

    generated_clock ( name ) { }

複数あり


.. _cell_intrinsic_parasitic:

intrinsic_parasitic
^^^^^^^^^^^^^^^^^^^^

::

    intrinsic_parasitic () { }


.. _cell_latch:

latch
^^^^^^

::

    latch ( variable1_(string), variable2_(string) ) { }


.. _cell_latch_bank:

latch_bank
^^^^^^^^^^^

::

    latch_banck ( variable1_(string), variable2_(string), bits_(integer) ) { }


.. _cell_leakage_current:

leakage_current
^^^^^^^^^^^^^^^^

::

   leakage_current () { }

たぶん複数あり


.. _cell_leakage_power:

leakage_power
^^^^^^^^^^^^^^

::

    leakage_power () { }

たぶん複数あり


.. _cell_lut:

lut
^^^^

::

    lut ( name_(string) ) { }

.. _cell_mode_definition:

mode_definition
^^^^^^^^^^^^^^^^

::

    mode_definition () { }

たぶん複数あり


.. _cell_pg_pin:

pg_pin
^^^^^^^

::

    pg_pin ( string ) { }

たぶん複数あり


.. _cell_pin:

pin
^^^^

::

    pin ( name_(string) | name_list_(string) ) { }

複数あり．
:ref:`pin_group`


.. _cell_routing_track:

routing_track
^^^^^^^^^^^^^^

::

    routing_track ( routing_layer_name_(string) ) { }

たぶん複数あり


.. _cell_statetable:

statetable
^^^^^^^^^^^

::

    statetable ( "input_node_names", "internal_node_names" ) { }


.. _cell_test_cell:

test_cell
^^^^^^^^^^

::

    test_cell () { }


.. _cell_type:

type
^^^^^

::

    type ( name_(string) ) { }

複数あり



.. _scaled_cell_group:

scaled_cell Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  sclaed_cell ( existing_cell, operating_conditions_group ) {
    area : float ;
    auxiliary_pad_cell : true | false ;
    bus_naming_style : "string" ;
    cell_footprint : string ;
    cell_leakage_power : float ;
    clock_gating_integrated_cell : string ;
    contential_condition : "Boolean expression" ;
    dont_fault : sa0 | sa1 | sa01 ;
    dont_touch : true | false ;
    dont_use : true | false ;
    geometry_print : string ;
    handle_negative_constraint : true | false ;
    is_clock_gating_cell : true | false ;
    map_only : true | false ;
    pad_cell : true | false ;
    pad_type : clock ;
    preferred : true | false ;
    scaling_factors : string ;
    use_for_size_only : true | false ;
    vhdl_name : "string" ;
    pin_equal ( "string, string, ..." ) ;
    pin_opposite ( "string, string, ...", "string, string, ..." ) ;
    rail_connection ( string, string ) ;
    bundle ( ) { ... }
    bus ( ) { ... }
    ff ( ) { ... }
    ff_bank ( ) { ... }
    generated_clock ( ) { ... }
    latch ( ) { ... }
    latch_bank ( ) { ... }
    leakage_power ( ) { ... }
    lut ( ) { ... }
    mode_definition ( ) { ... }
    pin ( ) { ... }
    routing_track ( ) { ... }
    statetable ( ) { ... }
    test_cell ( ) { ... }
    type ( ) { ... }
  }


.. _model_group:

model Group statement
^^^^^^^^^^^^^^^^^^^^^^

::

  model ( string ) {
    ...
  }

cell Group と同一の属性を持つ．
model Group 固有の属性は以下の通り

::

  cell_name : string ;
  short ( "name_list_(string)" ) ;

凡例では上のように書いてあるが，実際の例では

::

  short ( b, y ) ;

なので short ( string, string, ... ) ; が正しいと思われる．


.. _test_cell_group:

test_cell Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  test_cell () {
    ff ( string, string ) { }
    ff_bank ( string, string, integer ) { }
    latch ( string, string ) { }
    latch_bank ( string, string, integer ) { }
    pin ( string, .. ) { }
    statetable ( string, string ) { }
  }

test_cell 内の pin Group では
signal_type simple attribute を持つ場合がある．

::

  signal_type : test_scan_in | test_scan_in_inverted |
                test_scan_out | test_scan_out_inverted |
		test_scan_enable | test_scan_enable_inverted |
		test_scan_clock | test_scan_clock_a |
                test_scan_clock_b | test_clock ;

こちらも test_cell 内の pin group で使用可能な simple attribute

::

  test_output_only : true | false ;
