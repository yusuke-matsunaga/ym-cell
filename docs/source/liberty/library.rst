.. _library_group:

library group
==============

`library` group は liberty ファイルの根本の group statement である．

::

   library ( name_(string) ) {
     library 用の属性記述
     ...
   }


`library` group のヘッダ部分にはライブラリ名を表す文字列を指定する．

以下に `library` 用の属性を記す．

.. _library_simple:

simple attributes
-----------------

.. _library_bus_naming_style:

bus_naming_style
^^^^^^^^^^^^^^^^^

::

   bus_nameing_style : "string" ;

string は一つの `%s` と `%d` を含む．
この2つの記号の現れる順序に制約はない．
ただし，この2つの記号の間に最低１つの
数値以外の文字が含まれていなければならない．
コロン(:)は範囲を表す文字として用いられるので，
`bus_naming_style` の文字列には含めることはできない．

`bus_naming_style` 属性が定義されていない場合のデフォルト定義は
以下のようになる．

::

   bus_naming_style : "%s[%d]" ;

バス `A` の1番めの要素は `A[1]` となる．

デフォルト以外の指定例は以下のようになる．

::

   bus_naming_style : "Bus%sPin%d" ;

バス `A` の1番めの要素は `BusAPin1` となる．


.. _library_comment:

comment
^^^^^^^^

::

   comment : "string" ;

ダブルクォート(")に囲まれている限り任意の文字を使うことができる．


.. _library_current_unit:

current_unit
^^^^^^^^^^^^^

::

   current_unit : value_(enum) ;

可能な値は以下の通り．

::

   1uA, 10uA, 100uA, 1mA, 10mA, 100mA, 1A

`current_unit` が省略された場合のデフォルト値はない．

.. _library_date:

date
^^^^^

::

   date : "date" ;

ダブルクォート(")に囲まれている限り任意の文字を使うことができる．


.. _library_delay_model:

delay_model
^^^^^^^^^^^^

::

   delay_model : value_(enum) ;

遅延値の計算で用いるディレイモデルを指定する．
可能な値は以下の通り．

::

   generic_cmos, table_lookup, piecewise_cmos, dcm, polynomial

この属性が省略された場合のデフォルト値は `generic_cmos` .


.. _library_em_temp_degradation_factor:

em_temp_degradation_factor
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   em_temp_degradation_factor : value_(float) ;

エレクトロマイグレーションのデグラデーションファクターを指定する．
`value` には浮動小数点を指定する．


.. _library_fall_net_delay:

fall_net_delay
^^^^^^^^^^^^^^^

::

   fall_net_delay : name_(id) ;



.. _library_fpga_domain_style:

fpga_domain_style
^^^^^^^^^^^^^^^^^^

::

   fpga_domain_style : name_(id) ;

`domain` group 中の `calc_mode` で参照する名前を指定する．



.. _library_fpga_technology:

fpga_technology
^^^^^^^^^^^^^^^^

::

   fpga_technology : fpga_technology_name_(string) ;

FPGA ライブラリの場合の FPGA テクノロジ名を指定する．


.. _library_in_place_swap_mode:

in_place_swap_mode
^^^^^^^^^^^^^^^^^^^

::

   in_place_swap_mode : match_footprint | no_swappping ;

使用可能な属性値は上の2つ．


.. _library_input_threshold_pct_fall:

input_threshold_pct_fall
^^^^^^^^^^^^^^^^^^^^^^^^^

::

   input_threshold_pct_fall : trip_point_(float) ;

入力が1から0に変化する時ののしきい値を 0.0 から 100.0 の値で指定する．


.. _library_input_threshold_pct_rise:

input_threshold_pct_rise
^^^^^^^^^^^^^^^^^^^^^^^^^

::

   input_threshold_pct_fall : trip_point_(float) ;

入力が0から1に変化する時のしきい値を 0.0 から 100.0 の値で指定する．


.. _library_leakage_power_unit:

leakage_power_unit
^^^^^^^^^^^^^^^^^^^

::

   leakage_power_unit : value_(enum) ;

リーク電力の単位を指定する．
可能な値は以下の通り．

::

   1mW, 100uW, 100mW, 10uW, 1uW, 100nW, 10nW, 1nW, 100pW, 10pW, 1pW


.. _library_nom_calc_mode:

nom_calc_mode
^^^^^^^^^^^^^^

::

   nom_calc_mode : name_(id) ;

nominal operating condition のデフォルト process point を指定する．


.. _library_nom_process:

nom_process
^^^^^^^^^^^^

::

   nom_process : value_(float) ;

nominal operating condition のプロセススケーリングファクターを指定する．


.. _library_nom_temperature:

nom_temperature
^^^^^^^^^^^^^^^^

::

   nom_temperature : value_(float) ;

nominal operating condition の温度を指定する．


.. _library_nom_voltage:

nom_voltage
^^^^^^^^^^^^^^

::

   nom_voltage : value_(float) ;

nominal operating condition の電圧を指定する．


.. _library_output_threshold_pct_fall:

output_threshold_pct_fall
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   output_threshold_pct_fall : trip_point_(float)

出力が1から0に変化する時のしきい値を 0.0 から 100.0 の範囲で指定する．


.. _library_output_threshold_pct_rise:

output_threshold_pct_rise
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   output_threshold_pct_rise : trip_point_(float)

出力が0から1に変化する時のしきい値を 0.0 から 100.0 の範囲で指定する．


.. _library_piece_type:

piece_type
^^^^^^^^^^^

::

   piece_type : value_(enum) ;

piecewise linear モデルの用いる容量のモデルを指定する．
可能な値は以下の通り．

::

   piece_length, piece_wire_cap, piece_pin_cap, piece_total_cap


.. _library_power_model:

power_model
^^^^^^^^^^^^

::

   power_model : table_lookup | polynomial ;

電力計算のモデルを指定する．

この属性が指定されなかった場合のデフォルト値は `table_lookup`


.. _library_power_unit:

power_unit
^^^^^^^^^^^^

::

   power_unit : value_(enum) ;

電力の単位を指定する．
可能な値は以下の通り．

::

   1mW, 100uW, 10uW, 1uW, 100nW, 10nW, 1nW, 100pW, 10pW, 1pW



.. _library_preferred_output_pad_slew_rate_control:

preferred_output_pad_slew_rate_control
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   preferred_output_pad_slew_rate_control : value_(enum) ;

可能な値は以下の通り．

::

   high, medium, low, none


.. _library_preferred_input_pad_voltage:

preferred_input_pad_voltage
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   preferred_input_pad_voltage : name_(string) ;

`name` には `input voltage group` 名を指定する．



.. _library_preferred_output_pad_voltage:

preferred_output_pad_voltage
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   preferred_output_pad_voltage : name_(string) ;

`name` には `output voltage group` 名を指定する．


.. _library_pulling_resistance_unit:

pulling_resistance_unit
^^^^^^^^^^^^^^^^^^^^^^^^

::

   pulling_resistance_unit : unit_(enum) ;

プルアップとプルダウン時の抵抗の単位を指定する．
可能な値は以下の通り．

::

   1ohm, 10ohm, 100ohm, 1kohm

この属性が指定されなかった場合のデフォルト値はない．


.. _library_rise_net_delay:

rise_net_delay
^^^^^^^^^^^^^^^

::

   rise_net_delay : name_(id) ;


.. _library_resistance_unit:

resistance_unit
^^^^^^^^^^^^^^^^

::

   resistance_unit : unit_(enum) ;

抵抗値の単位を指定する．
可能な値は以下の通り．

::

   1ohm, 10ohm, 100ohm, 1kohm


.. _library_revision:

revision
^^^^^^^^^

::

   revision: value ;

リビジョンを表す値を指定する．

`revision` の値は仕様書では string or number といっているが，
実際には `1.01a` というどちらにも属さない例のもあるので
`[0-9a-zA-Z.]*` でいいのでは？
もしくは非空白印字可能文字は全部含めてしまってもいいかも．


.. _library_simulation:

simulation
^^^^^^^^^^^

::

   simulation : true | false ;

Synopsys Library Analyzer がシミュレーション用ライブラリを生成するかど
うかを指定する．

この属性が指定されなかった場合のデフォルト値は true．


.. _library_slew_derate_from_library:

slew_derate_from_library
^^^^^^^^^^^^^^^^^^^^^^^^^

::

   slew_derate_from_library : derate_(float) ;

0.0 から 1.0 の範囲の浮動小数点数を指定する．


.. _library_slew_lower_threshold_pct_fall:

slew_lower_threshold_pct_fall
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   slew_lower_threshold_pct_fall : trip_pont_(float) ;

端子の値が 1 から 0 に変化する時のlower thresoldを 0.0 から100.0 の範囲で指定する．


.. _library_slew_lower_threshold_pct_rise:

slew_lower_threshold_pct_rise
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   slew_lower_threshold_pct_rise : trip_point_(float) ;

端子の値が 0 から 1 に変化する時のlower thresholdを 0.0 から100.0 の範囲で指定する．


.. _library_slew_upper_threshold_pct_fall:

slew_upper_threshold_pct_fall
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   slew_upper_threshold_pct_fall : trip_pont_(float) ;

端子の値が 1 から 0 に変化する時のupper thresholdを 0.0 から100.0 の範囲で指定する．


.. _library_slew_upper_threshold_pct_rise:

slew_upper_threshold_pct_rise
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   slew_upper_threshold_pct_rise : trip_point_(float) ;

端子の値が 0 から 1 に変化する時のupper thresholdを 0.0 から100.0 の範囲で指定する．


.. _library_threshold_voltage_group:

default_threshold_voltage_group
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_threshold_voltage_group : group_name_(id) ;

セルが属するカテゴリを指定する．
`group_name` にはカテゴリ名(string)を指定する．


.. _library_time_unit:

time_unit
^^^^^^^^^^

::

   time_unit : unit ;

時間の定義を指定する．
可能な値は以下の通り．

::

  1ps, 10ps, 100ps, 1ns

デフォルトは `1ns`


.. _library_voltage_unit:

voltage_unit
^^^^^^^^^^^^^

::

   voltage_unit : unit ;

電圧の単位を指定する．
可能な値は以下の通り．

::

   1mV, 10mV, 100mV, 1V．

デフォルトは `1V` ．


.. _library_default:

default attributes
-------------------

.. _library_default_cell_leakage_power:

default_cell_leakage_power
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_cell_leakage_power : value_(float) ;


.. _library_default_connection_class:

default_connection_class
^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_connection_class : name | name_list_(string) ;


.. _library_default_fall_delay_intercept:

default_fall_delay_intercept
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_fall_delay_intercept : value_(float) ;


.. _library_default_fall_pin_resistance:

default_fall_pin_resistance
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_fall_pin_resistance : value_(float) ;


.. _library_default_fanout_load:

default_fanout_load
^^^^^^^^^^^^^^^^^^^^

::

   default_fanout_load : value_(float) ;



.. _library_default_fpga_isd:

default_fpga_isd
^^^^^^^^^^^^^^^^^

::

   default_fpga_isd : fpga_isd_name_(id) ;

`fpga_isd` group を複数定義した場合，
デフォルトの `fpga_isd` を指定するために用いる．
`fpga_isd_name` は定義した `fpga_isd` の名前(string)を指定する．


.. _library_default_inout_pin_cap:

default_inout_pin_cap
^^^^^^^^^^^^^^^^^^^^^^

::

   default_inout_pin_cap : value_(float) ;


.. _library_default_inout_pin_fall_res:

default_inout_pin_fall_res
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_inout_pin_fall_res : value_(float) ;


.. _library_default_inout_pin_rise_res:

default_inout_pin_rise_res
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_inout_pin_rise_res : value_(float) ;


.. _library_default_input_pin_cap:

default_input_pin_cap
^^^^^^^^^^^^^^^^^^^^^^

::

   default_input_pin_cap : value_(float) ;


.. _library_default_intrinsic_fall:

default_intrinsic_fall
^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_intrinsic_fall : value_(float) ;


.. _library_default_intrinsic_rise:

default_intrinsic_rise
^^^^^^^^^^^^^^^^^^^^^^^

::

   default_intrinsic_rise : value_(float) ;


.. _library_default_leakage_power_density:

default_leakage_power_density
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_leakage_power_density : value_(float) ;


.. _library_default_max_capacitance:

default_max_capacitance
^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_max_capacitance : value_(float) ;


.. _library_default_max_fanout:

default_max_fanout
^^^^^^^^^^^^^^^^^^^^

::

   default_max_fanout : value_(float) ;


.. _library_default_max_transition:

default_max_transition
^^^^^^^^^^^^^^^^^^^^^^

::

   default_max_transition : value_(float) ;


.. _library_default_max_utilization:

default_max_utilization
^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_max_utilization : value_(float) ;


.. _library_default_min_porosity:

default_min_porosity
^^^^^^^^^^^^^^^^^^^^^

::

   default_min_porosity : value_(float) ;


.. _library_default_operating_conditions:

default_operating_conditions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_operating_conditions : name_(string) ;


.. _library_default_output_pin_cap:

default_output_pin_cap
^^^^^^^^^^^^^^^^^^^^^^

::

   default_output_pin_cap : value_(float) ;


.. _library_default_output_pin_fall_res:

default_output_pin_fall_res
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_output_pin_fall_res : value_(float) ;


.. _library_default_output_pin_rise_res:

default_output_pin_rise_res
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_output_pin_rise_res : value_(float) ;


.. _library_default_rise_delay_intercept:

default_rise_delay_intercept
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_rise_delay_intercept : value_(float) ;


.. _library_default_rise_pin_resistance:

default_rise_pin_resistance
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_rise_pin_resistance : value_(float) ;


.. _library_default_slope_fall:

default_slope_fall
^^^^^^^^^^^^^^^^^^^^

::

   default_slope_fall : value_(float) ;


.. _library_default_slope_rise:

default_slope_rise
^^^^^^^^^^^^^^^^^^^

::

   default_slope_rise : value_(float) ;


.. _library_default_wire_load:

default_wire_load
^^^^^^^^^^^^^^^^^^

::

   default_wire_load : name_(string) ;


.. _library_default_wire_load_area:

default_wire_load_area
^^^^^^^^^^^^^^^^^^^^^^^

::

   default_wire_load_area : value_(float) ;


.. _library_default_wire_load_capacitance:

default_wire_load_capacitance
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_wire_load_capacitance : value_(float) ;


.. _library_default_wire_load_mode:

default_wire_load_mode
^^^^^^^^^^^^^^^^^^^^^^^

::

   default_wire_load_mode : top | segmented | enclosed ;


.. _library_default_wire_load_resistance:

default_wire_load_resistance
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_wire_load_resistance : value_(float) ;


.. _library_default_wire_load_selection:

default_wire_load_selection
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   default_wire_load_selection : name_(string) ;


.. _library_scaling:

scaling attributes
-------------------

.. _library_k_process_cell_fall:

k_process_cell_fall
^^^^^^^^^^^^^^^^^^^^

::

   k_process_cell_fall : value_(float) ;


.. _library_k_process_cell_leakage_power:

k_process_cell_leakage_power
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_cell_leakage_power : value_(float) ;


.. _library_k_process_cell_rise:

k_process_cell_rise
^^^^^^^^^^^^^^^^^^^^

::

   k_process_cell_rise : value_(float) ;


.. _library_k_process_drive_current:

k_process_drive_current
^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_drive_current : value_(float) ;


.. _library_k_process_drive_fall:

k_process_drive_fall
^^^^^^^^^^^^^^^^^^^^^

::

   k_process_drive_fall : value_(float) ;


.. _library_k_process_drive_rise:

k_process_drive_rise
^^^^^^^^^^^^^^^^^^^^^

::

   k_process_drive_rise : value_(float) ;


.. _library_k_process_fall_delay_intercept:

k_process_fall_delay_intercept
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_fall_delay_intercept : value_(float) ;


.. _library_k_process_fall_pin_resistance:

k_process_fall_pin_resistance
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_fall_pin_resistance : value_(float) ;


.. _library_k_process_fall_propagation:

k_process_fall_propagation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_fall_propagation : value_(float) ;


.. _library_k_process_fall_transition:

k_process_fall_transition
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_fall_transition : value_(float) ;


.. _library_k_process_hold_fall:

k_process_hold_fall
^^^^^^^^^^^^^^^^^^^^

::

   k_process_hold_fall : value_(float) ;


.. _library_k_process_hold_rise:

k_process_hold_rise
^^^^^^^^^^^^^^^^^^^^

::

   k_process_hold_rise : value_(float) ;


.. _library_k_process_internal_power:

k_process_internal_power
^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_internal_power : value_(float) ;


.. _library_k_process_intrinsic_fall:

k_process_intrinsic_fall
^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_intrinsic_fall : value_(float) ;


.. _library_k_process_intrinsic_rise:

k_process_intrinsic_rise
^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_intrinsic_rise : value_(float) ;


.. _library_k_process_min_period:

k_process_min_period
^^^^^^^^^^^^^^^^^^^^

::

   k_process_min_period : value_(float) ;


.. _library_k_process_min_pulse_width_high:

k_process_min_pulse_width_high
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_min_pulse_width_high : value_(float) ;


.. _library_k_process_min_pulse_width_low:

k_process_min_pulse_width_low
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_min_pulse_width_low : value_(float) ;


.. _library_k_process_nochange_fall:

k_process_nochange_fall
^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_nochange_fall : value_(float) ;


.. _library_k_process_nochange_rise:

k_process_nochange_rise
^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_nochange_rise : value_(float) ;


.. _library_k_process_pin_cap:

k_process_pin_cap
^^^^^^^^^^^^^^^^^^

::

   k_process_pin_cap : value_(float) ;


.. _library_k_process_recovery_fall:

k_process_recovery_fall
^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_recovery_fall : value_(float) ;


.. _library_k_process_recovery_rise:

k_process_recovery_rise
^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_recovery_rise : value_(float) ;


.. _library_k_process_removal_fall:

k_process_removal_fall
^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_removal_fall : value_(float) ;


.. _library_k_process_removal_rise:

k_process_removal_rise
^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_removal_rise : value_(float) ;


.. _library_k_process_rise_delay_intercept:

k_process_rise_delay_intercept
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_rise_delay_intercept : value_(float) ;


.. _library_k_process_rise_pin_resistance:

k_process_rise_pin_resistance
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_rise_pin_resistance : value_(float) ;


.. _library_k_process_rise_propagation:

k_process_rise_propagation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_rise_propagation : value_(float) ;


.. _library_k_process_rise_transition:

k_process_rise_transition
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_rise_transition : value_(float) ;


.. _library_k_process_setup_fall:

k_process_setup_fall
^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_setup_fall : value_(float) ;



.. _library_k_process_setup_rise:

k_process_setup_rise
^^^^^^^^^^^^^^^^^^^^^^

::

   k_process_setup_rise : value_(float) ;


.. _library_k_process_skew_fall:

k_process_skew_fall
^^^^^^^^^^^^^^^^^^^^

::

   k_process_skew_fall : value_(float) ;


.. _library_k_process_skew_rise:

k_process_skew_rise
^^^^^^^^^^^^^^^^^^^^

::

   k_process_skew_rise : value_(float) ;


.. _library_k_process_slope_fall:

k_process_slope_fall
^^^^^^^^^^^^^^^^^^^^^

::

   k_process_slope_fall : value_(float) ;


.. _library_k_process_slope_rise:

k_process_slope_rise
^^^^^^^^^^^^^^^^^^^^^

::

   k_process_slope_rise : value_(float) ;


.. _library_k_process_wire_cap:

k_process_wire_cap
^^^^^^^^^^^^^^^^^^

::

   k_process_wire_cap : value_(float) ;



.. _library_k_process_wire_res:

k_process_wire_res
^^^^^^^^^^^^^^^^^^

::

   k_process_wire_res : value_(float) ;


.. _library_complex:

complex attributes
-------------------

.. _library_capacitive_load_unit:

capacitive_load_unit
^^^^^^^^^^^^^^^^^^^^^

::

   capacitive_load_unit ( value_(float), unit_(enum) ) ;

容量の単位を指定する．
`value` には任意の浮動小数点数を用いることができる．
`unit` は `ff` か `pf`


.. _library_default_part:

default_part
^^^^^^^^^^^^^

::

   default_part ( name_(string), speed_grade_(string) ) ;


.. _library_define:

define
^^^^^^^

::

   define ( "attribute_name", "group_name", "attribute_type" ) ;

新たな属性を定義する．

各属性の意味は下記の通り．

.. table::
   :align: left
   :widths: auto

   =============== ===========================================
   パラメータ      意味
   =============== ===========================================
   attribute_name  属性名
   group_name      この属性が属するグループ名
   attribute_type  Boolean, string, integer, float のいずれか
   =============== ===========================================


.. _library_define_cell_area:

define_cell_area
^^^^^^^^^^^^^^^^^

::

   define_cell_area ( area_name_(string), resource_type_(enum) ) ;

`resorce_type` に用いることのできる値は下記の通り．

::

   pad_slots, pad_input_driver_sites,
   pad_output_driver_sites, pad_driver_sites


.. _library_define_group:

define_group
^^^^^^^^^^^^^

::

   define_group ( group_(id), parent_name_(id) ) ;

新たな group を定義する．

各属性の意味は下記の通り．

.. table::
   :align: left
   :widths: auto

   =============== ===========================================
   パラメータ      意味
   =============== ===========================================
   group           グループ名
   parent_name     親のグループ名
   =============== ===========================================


.. _library_library_features:

library_features
^^^^^^^^^^^^^^^^^

::

   library_features ( value_1, value_2, ..., value_n ) ;

`value` の値は下記の通り．

::

   report_delay_calculation, report_power_calculation,
   report noise_calculation, report_user_data,
   allow_update_attribute


.. _library_piece_define:

piece_define
^^^^^^^^^^^^^

::

   piece_define ( "range0 [range1 range2 ...]" );


.. _library_routing_layers:

routing_layers
^^^^^^^^^^^^^^^^

::

   routing_layers ( "routing_layer_1_name", ..., "routing_layer_n_name" ) ;


.. _library_technology:

technology
^^^^^^^^^^^

::

   technology ( "name" ) ;

テクノロジを指定する．なぜ，この属性が simple attribute ではなく
complex attribute になっているのかは謎．

`name` は  `cmos` か `fpga` ．
デフォルトは `cmos` ．


.. _library_group_:

group statements
-----------------

.. _library_cell:

cell
^^^^^

::

   cell ( name_(string) ) { }

セルを表すグループ．
:ref:`cell_group` 参照．


.. _library_dc_current_template:

dc_current_template
^^^^^^^^^^^^^^^^^^^^

::

   dc_current_template ( name_(id) ) { }


DCカレントのテンプレートを表すグループ．
.. :ref:`dc_current_template` 参照．


.. _library_em_lut_template:

em_lut_template
^^^^^^^^^^^^^^^^

::

   em_lut_template ( name_(id) ) { }

エレクトロマイグレーション用の LUT テンプレートを表すグループ．
.. :ref:`em_lut_template` 参照．


.. _library_fall_transition_degradation:

fall_transition_degradation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   fall_transition_degradation ( name_(id) ) { }


1から0に変化する時の遷移時間の劣化を表すグループ．
.. :ref:`fall_transition_degradation` 参照．


.. _library_faults_lut_template:

faults_lut_template
^^^^^^^^^^^^^^^^^^^^

::

   faults_lut_template ( name_(id) ) { }

.. :ref:`faults_lut_template` 参照．


.. _library_input_voltage:

input_voltage
^^^^^^^^^^^^^^

::

   input_voltage ( name_(id) ) { }


.. _library_iv_lut_template:

iv_lut_template
^^^^^^^^^^^^^^^^

::

   iv_lut_template ( name_(id) ) { }

.. :ref:`iv_lut_template` 参照．


.. _library_lu_table_template:

lu_table_template
^^^^^^^^^^^^^^^^^^

::

   lu_table_template ( name_(id) ) { }


.. _library_noise_lut_template:

noise_lut_template
^^^^^^^^^^^^^^^^^^^

::

   noise_lut_template ( name_(id) ) { }


.. _library_operating_conditions:

operating_conditions
^^^^^^^^^^^^^^^^^^^^^

::

   operating_conditions ( name_(id) ) { }


.. _library_output_voltage:

output_voltage
^^^^^^^^^^^^^^^

::

   output_voltage ( name_(id) ) { }


.. _library_part:

part
^^^^^

::

   part ( name_(id) ) { }


.. _library_poly_template:

poly_template
^^^^^^^^^^^^^^

::

   poly_template ( name_(id) ) { }


.. _library_power_lut_template:

power_lut_template
^^^^^^^^^^^^^^^^^^^

::

   power_lut_template ( name_(id) ) { }


.. _library_power_poly_template:

power_poly_template
^^^^^^^^^^^^^^^^^^^^

::

   power_poly_template ( ) { }


.. _library_power_supply:

power_supply
^^^^^^^^^^^^^

::

   power_supply () { }


.. _library_propagation_lut_template:

propagation_lut_template
^^^^^^^^^^^^^^^^^^^^^^^^^

::

   propagation_lut_template ( name_(id) ) { }


.. _library_rise_transition_degradation:

rise_transition_degradation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

   rise_transition_degradation ( name_(id) ) { }


.. _library_scaled_cell:

scaled_cell
^^^^^^^^^^^^

::

   scaled_cell ( name_(id), op_conds ) { }


.. _library_scaling_factors:

scaling_factors
^^^^^^^^^^^^^^^^

::

   scaling_factors ( name_(id) ) { }


.. _library_timing:

timing
^^^^^^^

::

   timing ( name_(id) | name_list ) { }


.. _library_timing_range:

timing_range
^^^^^^^^^^^^^

::

   timing_range (name_(id) ) { }


.. _library_type:

type
^^^^^

::

   type ( name_(id) ) { }


.. _library_wire_load:

wire_load
^^^^^^^^^^

::

   wire_load ( name_(id) ) { }


.. _library_wire_load_selection:

wire_load_selection
^^^^^^^^^^^^^^^^^^^^

::

   wire_load_selection ( name_(id) ) { }


.. _library_wire_load_table:

wire_load_table
^^^^^^^^^^^^^^^^

::

   wire_load_table ( name_(id) ) { }
