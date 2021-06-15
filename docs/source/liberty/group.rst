.. _group:

Group Statement 詳細
=====================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   ff.rst
   latch.rst

.. _base_curves_group:

base_curves Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  base_curves ( name ) {
    base_curve_type ( ccs_timing_half_curve ); // これのみ
    curve_x ( "float, float, ..." );
    curve_y ( id, "float, float, ..." );
  }

* base_curve_type complex attribute は文字列を引数にとるが，
  現在は ccs_timing_half_curve のみが適正な値

* curve_x complex attribute は浮動小数点数のリストの文字列を引数にとる．

* curve_y complex attribute はID番号(integer)と浮動小数点数のリスト
  の文字列を引数にとる．

* これら3つの属性は必須，and 唯一

.. _compact_lut_template_group:

compact_lut_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  compact_lut_template ( name ) {
    base_curves_group : string ;
    variable_1 : string ;
    variable_2 : string ;
    variable_3 : string ;
    index_1 ( "float, float, ..." ) ;
    index_2 ( "float, float, ..." ) ;
    index_3 ( "string, string, ..." ) ;
  }

* variable_1 と variable_2 の値は
  input_net_transition | total_output_net_capacitance

* variable_3 の値は curve_parameters のみ

* index_3 の文字列は init_current, peak_current, peak_voltage,
  peak_time, left_id, right_id

.. _dc_current_template_group:

dc_current_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  dc_current_template ( name ) {
    variable_1 : string ;
    variable_2 : string ;
    variable_3 : string ;
    index_1 ( "float, float, ..." ) ;
    index_2 ( "float, float, ..." ) ;
    index_3 ( "float, float, ..." ) ;
  }

* variable_1, variable_2, variable_3 の値は
  2次元の場合は variable_1 が input_voltage，
  variable_2 が output_voltage
  3次元の場合は variable_1 が input_net_transition，
  variable_2 が output_net_transition，
  variable_3 が time

.. _em_lut_template_group:

em_lut_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  em_lut_template ( name ) {
    variable_1 : string ;
    variable_2 : string ;
    index_1 : ( "float, float, ..." ) ;
    index_2 : ( "float, float, ..." ) ;
  }

* variable_1, variable2 の値は input_transition_time か
  total_output_net_capacitance

.. _rise_fall_net_delay_group:

{rise|fall}_net_delay Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  fall_net_delay ( name ) {
  index_1 ( "float, float, ..." ) ;
  index_2 ( "float, float, ..." ) ;
  values ( "float, float, ...", "float, float, ...", ... ) ;
  }

* 通常の table group

.. _rise_transition_degradation_group:

{rise|fall}_transition_degradation Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* 通常の table group

.. _fault_lut_template_group:

fault_lut_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  fault_lut_template ( name ) {
    variable_1 : string ;
    variable_2 : string ;
    index_1 ( "string, string, ..." ) ;
    index_2 ( "float, float, ..." ) ;
  }

* variable_1 は fab_name
* variable_2 は time_range

.. _input_voltage_group:

input_voltage Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  input_voltage ( name ) {
  vil : v_expr ;
  vih : v_expr ;
  vimin : v_expr ;
  vimax : v_expr ;
  }

.. _fpga_isd_group:

fpga_isd Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^

::

  fpga_isd ( name ) {
    drive : string ; // といいつつ Example では drive : 24 ; になってる．
    io_type : string ;
    slew : FAST | SLOW ;
  }

.. _iv_lut_template_group:

iv_lut_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  iv_lut_template ( name ) {
    variable_1 : iv_output_voltage ; // これ一択
    index_1 ( "float, float, ..." ) ;
  }

.. _lu_table_template_group:

lu_table_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  lu_table_template ( name ) {
    variable_1 : string ;
    variable_2 : string ;
    variable_3 : string ;
    variable_4 : string ;
    index_1 ( "float, float, ..." ) ;
    index_2 ( "float, float, ..." ) ;
    index_3 ( "float, float, ..." ) ;
    index_4 ( "float, float, ..." ) ;
    domain ( name ) { ... }
  }

* In Composite Current Source (CCS) Noise Tables
  * ccsn_first_stage, ccsn_last_stage グループ内の以下のグループで使われる．

  * dc_current group

    ::

       variable_1 : input_voltage ;
       variable_2 : output_votage ;

  * output_current_rise group and output_current_fall group

    ::

      variable_1 : input_net_transition ;
      variable_2 : total_output_net_capacitance ;
      variable_3 : time ;

  * propagated_noise_low group and propagate_noise_high group

    ::

      variable_1 : input_noise_height ;
      variable_2 : input_noise_width ;
      variable_3 : total_output_net_capacitance ;
      variable_4 : time ;

* In Timing Delay Tables

  variable_n に使える値は以下の通り

  ::

    input_net_transition
    total_output_net_capacitance
    output_net_length
    output_net_wire_cap
    output_net_pin_cap
    related_out_total_output_net_capacitance
    related_out_output_net_length
    related_out_output_net_wire_cap
    related_out_output_net_pin_cap

* In Constraint Tables

  variable_n に使える値は以下の通り

  ::

     constrained_pin_transition
     related_pin_transition
     related_out_total_output_net_capacitance
     related_out_output_net_length
     related_out_output_net_wire_cap
     related_out_output_net_pin_cap

* In Wire Delay Tables

  variable_n に使える値は以下の通り

  ::

    fanout_number
    fanout_pin_capacitance
    driver_slew

* In Net Delay Tables

  variable_{1,2} に使える値は以下の通り

  ::

    output_transition
    rc_product

* In Degradation Tables

  transition time degradation table の variable_{1,2} に使える値は以下の通り

  ::

    output_pin_transition
    connect_delay

  cell degradation table の variable_1 に使える値は以下の通り

  ::

    input_net_transition

.. _domain_group:

domain Group statement
^^^^^^^^^^^^^^^^^^^^^^^

::

  domain ( name ) {
    calc_mode : string ;
    variable_1 : string ;
    variable_2 : string ;
    variable_3 : string ;
    index_1 ( "float, float, ..." ) ;
    index_2 ( "float, float, ..." ) ;
    index_3 ( "float, float, ..." ) ;
  }

domain Group は複数あり得る．

.. _maxcap_lut_template_group:

maxcap_lut_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  variable_1 : frequency ;
  vairable_2 : input_transition_time ;

.. _maxtrans_lut_template_group:

maxtrans_lut_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  variable_1 : frequency ;
  variable_2 : input_transition_time ;
  variable_3 : total_output_net_capacitance ;

.. _noise_lut_template_group:

noise_lut_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  variable_1, variable_2 に使える値は
  input_noise_width と total_output_net_capacitance

.. _operation_conditions_group:

operating_conditions Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  operating_conditions ( name ) {
    calc_mode : string ;
    parameteri : float ; // i = 1..5
    process : float ; // 0.0 - 100.0
    temperature : float ;
    tree_type : string ; // best_case_tree, balanced_tree, worst_case_treen
    voltage : float ;
    power_rail ( string, float ) ; // one or more
  }

.. _output_current_template_group:

output_current_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  variable_1 と variable_2 に使える値は
  input_net_transition, total_output_net_capacitance
  variable_3 に使える値は time

.. _output_voltage_group:

output_voltage Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  output_voltage ( name ) {
    vol: v_expr ;
    voh: v_expr ;
    vomin: v_expr ;
    vomax: v_expr ;
  }

.. _part_group:

part Group statement
^^^^^^^^^^^^^^^^^^^^^

::

  part ( name ) {
    default_step_level : string ;
    fpga_isd : string ;
    num_blockrams : integer ;
    num_cols : integer ;
    num_ffs : integer ;
    num_luts : integer ;
    num_rows : integer ;
    pin_count : 94 ;
    max_count ( string, integer ) ; // 複数あり
    valid_speed_grade ( string, string, ... ) ;
    valid_step_levels ( string, string, ... ) ;
    speed_grade () { }
  }

.. _speed_grade_group:

speed_grade Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  speed_grade ( name ) {
    fpga_isd : string ;
    step_level ( string ) ;
  }

.. _pg_current_template_group:

pg_current_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  variable_{1,2,3,4} に使える値は
  input_net_transition
  total_output_net_capacitance
  time

  最後は必ず time でなければならない．
  input_net_transition は 0 か 1
  total_output_net_capacitance は 0 - 2

  index_n はオプション

.. _poly_template_group:

poly_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  poly_template ( name ) {
    variables ( string, string, ... ) ;
    variable_{1,2,3,4}_range ( float, float ) ;
    mapping ( string, string ) ;
    oders ( integer, integer, ... ) ;
    domain ( name ) { ... }
  }

* mapping ( value_(enum), power_rail_name_(id) )
  value_(enum) は voltage と voltage1 のみ，
  power_rail_name は power_rail の名前
  mapping は 2つ以上は定義できない (voltage と voltage1 の2つ)

* noise immunity template の場合，variables で使える値は
  input_noise_width
  total_output_net_capacitance
  voltage
  voltagei // i = 1 .. 5?
  temperature
  parametern // n ??

* noise propagation template の場合，variables で使える値は
  input_hoise_height
  input_noise_width
  input_noise_tiem_to_peak
  total_output_net_capacitance
  voltage, voltagei, temperature
  parametern

* steady state group の場合，
  iv_output_voltage
  voltage
  voltagei
  temperature
  parametern

* timing group の場合，以下の4セットとなる．
  - Set 1

    ::

       input_net_transition
       constrained_pin_transition

  - Set 2

    ::

       total_output_net_capacitance
       output_net_length, output_net_wire_cap
       output_net_pin_cap
       related_pin_transition

  - Set 3

    ::

       related_out_total_output_net_capaitance
       related_out_output_net_length
       related_out_output_net_wire_cap
       related_out_output_net_pin_cap

  - Set 4

    ::

       temperature, voltage
       voltagei

マニュアル中の ',' と '|' の使い分けの意味がわからん．


.. _poly_template_domain_group:

poly_template 中の domain Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  domain ( name ) {
    calc_mode : string ;
    variables ( string, string, ... ) ;
    variable_{1,2,3,4}_range ( float, float ) ;
    mapping ( string, string ) ;
    orders ( integer, integer, ... ) ;
  }

.. _polwer_lut_template_group:

power_lut_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

通常の template と同じ．

* variable_1 : input_transition_time
               total_output_net_capacitance
	       equal_or_opposite_output_net_capacitance

* variable_2 : input_transition_time
               total_output_net_capacitance
	       equal_or_opposite_output_net_capacitance

* variable_3 : input_transition_time
               total_output_net_capacitance
	       equal_or_opposite_output_net_capacitance

.. _power_poly_template_group:

power_poly_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* 通常の poly_template と同じ

* variables に使える値は
  equal_or_opposite_output_net_capacitance
  input_net_transition
  total_output_net_capacitance
  output_net_length
  temperature
  voltage
  voltagei
  parameteri

.. _power_supply_group:

power_supply Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  power_supply ( name ) {
    default_power_rail : string ;
    power_rail ( string, float ) ;
  }

power_rail complex attribute は複数あり得る．

.. _propagation_lut_template_group:

propagation_lut_template Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* 通常の template と同じ

* variable に使える値は以下の通り
  input_noise_width
  input_noise_height
  total_output_net_capacitance

.. _sensitization_group:

sensitization Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  sensitization ( name ) {
    pin_names ( string, string, ... ) ; // 多分唯一
    vector ( integer, string ) ; // 複数
  }

.. _scaling_factors_group:

scaling_factors Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  scaling_factors ( name ) {

  }

詳細は "Building Environments" chapter in the Library Compiler User
Guide: Modeling Timing, Signal Integrity, and Power in Technology Libraries.

.. _timing_range_group:

timing_range Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  timing_range ( name ) {
    faster_factor : float ;
    slower_factor : float ;
  }

.. _type_group:

type Group statement
^^^^^^^^^^^^^^^^^^^^^^

::

  type ( name ) {
    base_type : array ; // 'array' 一択
    bit_from : integer ;
    bit_to : integer ;
    bit_width : integer ;
    data_type : bit ; // 'bit' 一択
    downto : true | false ;
  }

.. _user_parameters_group:

user_parameters Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  user_parameters () {
    parameteri : float ; // i = 1..?
  }

.. _wier_load_group:

wire_load Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  wire_load ( name ) {
    area : float ;
    capacitance : float ;
    resistance : float ;
    slope : float ;
    fanout_length ( integer, float, float, float, integer ) ;
  }

fanout_length の各パラメータは

::

   fanout : ファンアウト数 (ドライバを除いたピン数)
   length : ネット長
   average_capacitance, standard_deviation, number_of_nets :
           Sysnopsys Floorplan Manager User Guide を見ろ

Example では最初の2つのパラメータしか定義していない．

.. _wire_load_selection_group:

wire_load_selection Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  wire_load_selection ( name ) {
    wire_load_from_area ( float, float, string ) ;
  }

詳細は "Library Deveopment Procedure" and "Defining I/O Pads"
chapters in the Library Compiler User Guide: Methodology and
Modeling Functionality in Technology Libraries and the "Building
Environments" chapter in the Library Compiler User Guide: Modeling
Timing, Signal Integrity, and Power in Technology Libraries.

.. _wire_load_table_group:

wire_load_table Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  wire_load_table ( name ) {
    fanout_area ( integer, float ) ;
    fanout_capacitance ( integer, float ) ;
    fanout_length ( integer, float ) ;
    fanout_resistance ( integer, float ) ;
  }

.. _bundle_group:

bundle Group statement
^^^^^^^^^^^^^^^^^^^^^^

::

  bundle ( string ) {
    members ( string, string, ... ) ; // 例では string のリストに見える．
    // pin Group の simple attributes
    pin ( string ) { }
  }


.. _bus_group:

bus Group statement
^^^^^^^^^^^^^^^^^^^^^

::

  bus ( string ) {
    bus_type : string ; // library の type グループ名
    pin ( string [, string, ... ] ) {
    }
  }

bus 内のピン名は A[0:3] とか A[4] という記述がある．

.. _dynamic_current_group:

dynamic_current Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  dynamic_current () {
    when : "Boolean expression" ;
    related_inputs : string ; // required, (unique?)
    related_outputs : string ; // optional, (unique?)
    typical_capacitances ( "float, float, ..." ) ; // 要素数はrelated_outputs のピン数と同じ
    switching_group () { } // たぶん，複数あり
  }

related_inputs, related_outputs は文字列だが "" 内の空白で区切られた複数のピン名のリストを表す．

.. _switching_group_group:

switching_group Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  switching_group () {
    input_switching_condition ( string, string, ... ) ; // rise | fall
    output_switching_condition ( string, string, ... ) ; // rise | fall
    min_input_switching_count : integer ;
    max_input_switching_count : integer ;
    pg_current () { }
  }

input_switching_condition, output_switching_condition は
simple attribute と書いてあるがどう見ても complex attribute．
多分，ピン数分の rise|fall が並ぶものと思われる．

.. _pg_current_group:

pg_current Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  pg_current () {
    vector () { } // 複数あり
  }


.. _vector_group:

vector Group statement
^^^^^^^^^^^^^^^^^^^^^^^

::

  vector () {
    index_1 ( "float, float, ..." ) ; // なぜかマニュアルには <float> と謎表記
    index_2 ( "float, float, ..." ) ; // なぜかマニュアルには <float> と謎表記
    index_3 ( "float, float, ..." ) ;
    index_4 ( "float, float, ..." ) ;
    index_output : string ; // <output_pin_name>
    reference_time : float ; // <float>
    values ( "float, float, ..." ) ;
  }

この辺のマニュアル書いてる人は simple attribute と complex attribute
を混同してる．
values に至っては values : ( "0.002, 0.009, .." ) ;
などとわけのわからない記述例を載せている．

.. _fpga_condition_group:

fpga_condition Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  fpga_condition ( string ) {
    fpga_condition_value ( string ) { } // たぶん，複数あり
  }

.. _fpga_condition_value_group:

fpga_condition_value Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  fpga_condition_value ( string ) {
    fpg_arc_condition : true | false ;
  }

果てしなく馬鹿で無駄な構文
fpga_condition_value を complex attribute にすればよいのでは？

.. _function_yield_metric_group:

functional_yield_metric Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  functional_yield_metric () {
    average_number_of_faults ( string ) { }
  }

.. _average_number_of_faults_group:

average_number_of_faults Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  average_number_of_faults ( string ) { // faults_lut_template 名
    values ( 例のやつ ) ;
  }

.. _generated_clock_group:

generated_clock Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  generated_clock ( string ) {
    clock_pin : string ; // 空白で区切られたピン名のリスト
    master_pin : string ;
    divided_by : integer ;
    multipled_by : integer ;
    invert : true | false ;
    duty_cycle : float ;
    edges ( integer, integer, integer ) ; // 常に 3
    shifts ( float, float, float ) ; // 常に 3
  }

.. _intrinsic_parasitic_group:

intrinsic_parasitic Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  intrinsic_parasitic ( string ) {
    when : "Boolean expression" ;
    intrinsic_capacitance ( string ) {
      related_output : string ; // マニュアルには related_outputs の記述もあり．
      value : float ;
    } // 複数あり
    intrinsic_resistance ( string ) {
      value : float ;
    } // 複数あり
    total_capacitance ( string ) {
      value : float ;
    }
  }

これ ３つとも complex attribute で出来るじゃん．

.. _leakage_current_group:

leakage_current Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  leakage_current () {
    when : "Boolean expression" ;
    value : float ; // pg_current の代わり
    pg_current ( string) { // たぶん複数あり
      value : float ;
    }
    gate_leakage ( string ) {
      input_low_value : float ;
      input_high_value : float ;
    }
  }

.. _leakage_power_group:

leakage_power Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  leakage_power () {
    power_level : string ;
    related_pg_pin : string ;
    when : "Boolean expression" ;
    value : float ;
  }

.. _lut_group:

lut Group statement
^^^^^^^^^^^^^^^^^^^^

::

  lut ( string ) {
    input_pins : string ; // 空白で区切られたピンのリスト
  }

.. _mode_definition_group:

mode_definition Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  mode_definition ( string ) {
    mode_value ( string ) { // 複数あり
      when : "Boolean expression" ;
      sdf_cond : string ;
    }
  }

.. _pg_pin_group:

pg_pin Group statement
^^^^^^^^^^^^^^^^^^^^^^^

::

  pg_pin ( string ) {
    voltage_name : string ;
    pg_type : string ; // primary_power | primary_ground |
                       // backup_power | backup_ground |
		       // internal_power | internal_ground
  }

.. _routing_track_group:

routing_track Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  routing_track ( string ) {
    tracks : integer ;
    total_track_area : float ;
    short ? complex attribute だが一切の記述なし
    /* for model group only */ とだけ書かれている．
  }

.. _statetable_group:

statetable Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  statetable ( string, string ) {
    table : string ;
  }

ヘッダの2つの文字列はそれぞれ
input_node_names, internal_node_names
を表す．例では複数のピン名を空白なしで連結しているように見える．

table は 2つの ':' で区切られた複数行からなる文字列で一行が
" input_node_values : current_internal_values : next_internal_values "
を表す．

センスのない構文．複雑なことを全部文字列の中に押し込めて構文としてな
んにもしていない．

.. _ccsn_first_stage_group:

ccsn_{first|last}_stage Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  ccsn_first_sgate () {
    is_needed : true | false ;
    is_inverting : true | false ;
    miller_cap_rise : float ;
    miller_cap_fall : float ;
    stage_type : string ; // pull_up | pull_down
    when : "Boolean expression" ;

    dc_current ( string ) {
      index_1 ( "float, float, ... " ) ;
      index_2 ( "float, float, ... " ) ;
      values ( 例のやつ ) ;
    }

    output_voltage_{rise|fall} () {
      vector ( string ) {
        index_1 ( float ) ; // ?
	index_2 ( float ) ; // ?
	index_3 ( "float, float, ... " ) ;
	values ( 例のやつ ) ;
      }
    }

    propagated_noise_{low|high} () {
      vector ( string ) {
        index_1 ( float ) ; // ?
	index_2 ( float ) ; // ?
	index_3 ( float ) ; // ?
	index_4 ( "float, float, ... " ) ;
	values ( 例のやつ ) ;
      }
    }
  }

.. _electromigration_group:

electromigration Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  electromigration () {
    related_pin : string ; // 空白で区切られたピン名のリスト
    related_bus_pins : string ; // 空白で区切られたピン名のリスト
    when : "Boolen expression" ;
    index_1 ( "float, float, ... " ) ; // optional
    index_2 ( "float, float, ... " ) ; // optional
    values ( 例のやつ ) ;
    em_max_toggle_rate ( string ) {
      // lcrm1_3 に記述なし
    }
  }

.. _hyperbolic_noise_above_high_group:

hyperbolic_noise_{above_high|below_low|high|low} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  hyperbolic_noise_above_high () {
    area_coefficient : float ;
    height_coefficient : float ;
    width_coefficient : float ;
  }

.. _internal_power_group:

internal_power Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  internal_power () {
    equal_or_opposite_output : string ; // 空白で区切られたピン名のリスト
    falling_together_group : string ;  // 空白で区切られたピン名のリスト
    power_level : string ;
    related_pin : string ;  // 空白で区切られたピン名のリスト
    rising_together_group : string ;  // 空白で区切られたピン名のリスト
    switching_interval : float ;
    switching_together_group : string ;  // 空白で区切られたピン名のリスト
    when : "Boolean expression" ;
    domain ( string ) { }
    fall_power ( string ) { }
    power ( string ) { }
    rise_power ( string ) { }
  }

power, fall_power, rise_power グループは table グループ

.. _max_capacitance_group:

{max|min}_capacitance Group statement (lcrm中では max_cap ?)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  max_capacitance ( string ) { // template 名
    // table attributes
  }

.. _max_transition_group:

{max|min}_transition Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  max_transition ( string ) { // template 名
    // table attributes
  }

.. _min_pluse_width_group:

min_pulse_width Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  min_pulse_width () {
    constraint_high : float ;
    constraint_low : float ;
    when : "Boolean expression" ;
    sdf_cond : string ; "SDFの書式のブール式"
  }

.. _minimum_period_group:

minimum_period Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  minimum_period () {
    constraint : float ;
    when : "Boolean expression" ;
    sdf_cond : string ;
  }

.. _pin_capacitance_group:

pin_capacitance Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  pin_capacitance () {
    capacitance () { }
    rise_capacitance () { }
    fall_capacitance () { }
    rise_capacitance_range() { } // optional, unique
    fall_capacitance_range() { } // optional, uniquen
  }

capacitance, rise_capacitance, fall_capacitance は table グループ
例では orders, coefs を用いている．

.. _rise_capacitance_range_group:

{rise|fall}_capacitance_range Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  rise_capacitance_range () {
    lower ( string ) { } // required, unique
    upper ( string ) { } // required, unique
  }

lower, upper は poly template table グループ

::

    variable_n_range
    orders
    coefs
    domain

.. _reciver_capacitance_group:

receiver_capacitance Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  receiver_capacitance () {
    receiver_capacitance1_fall() { }
    receiver_capacitance1_rise() { }
    receiver_capacitance2_fall() { }
    receiver_capacitance2_rise() { }
  }

4つのグループは lu_tamplate_name を引数にとり
values 属性を持つ．

.. _tlatch_group:

tlatch Group statment
^^^^^^^^^^^^^^^^^^^^^

::

  tlatch ( string ) {
    edge_type : string ; // rising | falling
    tdisable : TRUE | FALSE ; // true | false じゃないの？
  }


.. _cell_degradation_group:

cell_degradation Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  cell_degradation ( string ) {
    index_1 ( "float, float, ... " ) ;
    values ( ... ) ;
    coefs ( ) ;
    orders ( ) ;
    variable_n_range ( ) ;
    domain () { }
  }

普通の table グループ

.. _cell_fall_group:

cell_{fall|rise} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  cell_fall ( string ) {
    index_1 ( ... ) ;
    index_2 ( ... ) ;
    index_3 ( ... ) ;
    values ( ... ) ;
    domain () { }
  }

普通の table グループ

.. _compact_ccs_fall_group:

compact_ccs_{fall|rise} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  compact_ccs_fall (string ) {
    vase_curves_group : string ;
    values ( ... ) ;
  }

.. _fall_constraint_group:

{fall|rise}_constraint Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  fall_constraint (string) {
    index_1 ( ... ) ;
    index_2 ( ... ) ;
    index_3 ( ... ) ;
    values ( ... ) ;
    domain () { }
  }

普通の table グループ

.. _fall_propagation_group:

{fall|rise}_propagation Group satement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  fall_propagation (string) {
    index_1 ( ... ) ;
    index_2 ( ... ) ;
    index_3 ( ... ) ;
    values ( ... ) ;
    domain () { }
  }

普通の table グループ

.. _fall_transition_group:

{fall|rise}_transition Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  fall_transition (string) {
    index_1 ( ... ) ;
    index_2 ( ... ) ;
    index_3 ( ... ) ;
    intermediate_values ( ... ) ;
    values ( ... ) ;
    domain () { }
  }

普通の table グループに intermediate_values 属性が追加されている．

.. _noise_immunity_above_high_group:

noise_immunity_{above_high|below_low|high|low} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  noise_immunity_above_high (string) {
    coefs ( ... ) ;
    orders ( ... ) ;
    values ( ... ) ;
    domain () { }
  }

普通の table グループ

.. _output_current_fall_group:

output_current_{fall|rise} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  output_current_fall (string) {
    vector () {
      reference_time : float ;
      index_1 ( ... ) ;
      index_2 ( ... ) ;
      index_3 ( ... ) ;
      values ( ... ) ;
    }
  }

vector グループは普通の table グループに reference_time 属性が追加されたもの

.. _propagated_noise_height_above_high_group:

propagated_noise_height_{above_high|below_low|high|low} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  propagated_noise_height_above_high ( string ) {
    coefs ( ... ) ;
    orders ( ... ) ;
    values ( ... ) ;
    domain ( ) { }
  }

普通の table グループ

.. _propagated_noise_peak_time_ratio_above_high_group:

propagated_noise_peak_time_ratio_{above_high|below_low|high|low} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  propagated_noise_peak_time_ratio_above_high ( string ) {
    coefs ( ... ) ;
    orders ( ... ) ;
    values ( ... ) ;
    domain () { }
  }

propagated_noise_height_above_high と同様

.. _propagated_noise_width_above_high_group:

propagated_noise_width_{above_high|below_low|high|low} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  propagated_noise_width_above_high ( string ) {
    ...
  }

propagated_noise_height_above_high と同様

.. _receiver_capacitance1_fall_group:

receiver_capacitance{1|2}_{fall|rise} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  receiver_capacitance1_fall ( string ) { // lcrm1-3 の例ではパラメータがない
    values ( ... ) ;
  }

.. _retaining_fall_group:

retaining_{fall|rise} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  retaining_fall ( string ) {
    index_1 ( ... ) ;
    index_2 ( ... ) ;
    index_3 ( ... ) ;
    values ( ... ) ;
    domain () { }
  }

普通の table グループ

.. _retain_fall_slew_group:

retain_{fall|rise}_slew Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  retain_fall_slew (string) {
    values ( ... ) ;
  }

  retain_fall_slew (string) {
    orders ( ... ) ;
    coefs ( ... ) ;
    variable_n_range ( float, float ) ;
  }

説明と例では明示されていないが普通の table グループ？

.. _steady_state_current_high_group:

steady_state_current_{high|low} Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  steady_state_current_high ( string ) {
    coefs ( ... ) ;
    orders ( ... ) ;
    values ( ... ) ;
    domain () { }
  }

普通の table グループ

.. _steady_state_current_tristate_group:

steady_state_current_tristate Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  steady_state_current_tristate ( string ) {
    index_1 ( ... ) ;
    index_2 ( ... ) ;
    index_3 ( ... ) ;
    intermediate_values ( ... ) ;
    values ( ... ) ;
    coers ( ... ) ;
    orders ( ... ) ;
    domain () { }
  }

普通の table グループに intermediate_values 属性を加えたもの

.. _pin_based_variation_group:

pin_based_variation Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  pin_based_variation () {
    va_parameters ( string, string, ... ) ;
    nominal_va_values ( float, float, ... ) ;
    va_compact_ccs_rise () { }
    va_compact_ccs_fall () { }
    va_receiver_capacitance1_fall () { }
    va_receiver_capacitance1_rise () { }
    va_receiver_capacitance2_fall () { }
    va_receiver_capacitance2_rise () { }
  }

たぶん timing_based_variation と同じ

.. _timing_based_variation_group:

timing_based_variation Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  timing_based_variation () {
    va_parameters ( string, string, ... ) ;
    nominal_va_values ( float, float, ... ) ;
    va_compact_ccs_rise( string ) {
      va_values ( float, float, ... ) ;
      values ( "float, ...", "float, ... ", ... );
    }
    va_compact_ccs_fall ( ) { }
    va_receiver_capacitance1_fall () { }
    va_receiver_capacitance1_rise () { }
    va_receiver_capacitance2_fall () { }
    va_receiver_capacitance2_rise () { }
    va_rise_constraint () { }
    va_fall_constraint () { }
  }

va_{fall|rise}_constraint は va_compact_ccs_rise と同じ
