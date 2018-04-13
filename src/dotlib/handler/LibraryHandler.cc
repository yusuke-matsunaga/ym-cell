
/// @file LibraryHandler.cc
/// @brief LibraryHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"

#include "LibraryHandler.h"
#include "DefineHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief library group 用のハンドラを作る．
// @param[in] parser パーサー
DotlibHandler*
HandlerFactory::new_library(DotlibParser& parser)
{
  return new LibraryHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス LibraryHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
LibraryHandler::LibraryHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  DotlibHandler* simple = HandlerFactory::new_simple(parser);
  DotlibHandler* str_simple = HandlerFactory::new_string(parser, false);
  DotlibHandler* symstr_simple = HandlerFactory::new_string(parser, true);
  DotlibHandler* flt_simple = HandlerFactory::new_float(parser);
  DotlibHandler* delay_model = HandlerFactory::new_delay_model(parser);
  DotlibHandler* complex = HandlerFactory::new_complex(parser);
  DotlibHandler* str1_complex = HandlerFactory::new_str1_complex(parser);
  DotlibHandler* unit_complex = HandlerFactory::new_unit(parser);
  DotlibHandler* define = new DefineHandler(parser, this);
  DotlibHandler* tmpl_handler = HandlerFactory::new_template(parser);
  DotlibHandler* group_handler = HandlerFactory::new_group(parser);
  DotlibHandler* cell_handler = HandlerFactory::new_cell(parser);
  DotlibHandler* iv_handler = HandlerFactory::new_input_voltage(parser);
  DotlibHandler* ov_handler = HandlerFactory::new_output_voltage(parser);
  DotlibHandler* oc_handler = HandlerFactory::new_operating_conditions(parser);
  DotlibHandler* wl_handler = HandlerFactory::new_wire_load(parser);
  DotlibHandler* wls_handler = HandlerFactory::new_wire_load_selection(parser);
  DotlibHandler* wlt_handler = HandlerFactory::new_wire_load_table(parser);

  // simple attributes
  reg_handler(AttrType::bus_naming_style,                       str_simple);
  reg_handler(AttrType::comment,                                str_simple);
  reg_handler(AttrType::current_unit,                           symstr_simple);
  reg_handler(AttrType::date,                                   str_simple);
  reg_handler(AttrType::delay_model,                            delay_model);
  reg_handler(AttrType::em_temp_degradation_factor,             flt_simple);
  reg_handler(AttrType::fpga_technology,                        str_simple);
  reg_handler(AttrType::in_place_swap_mode,                     str_simple);
  reg_handler(AttrType::input_threshold_pct_fall,               simple);
  reg_handler(AttrType::input_threshold_pct_rise,               simple);
  reg_handler(AttrType::leakage_power_unit,                     symstr_simple);
  reg_handler(AttrType::NOM_calc_mode,                          str_simple);
  reg_handler(AttrType::nom_process,                            flt_simple);
  reg_handler(AttrType::nom_temperature,                        flt_simple);
  reg_handler(AttrType::nom_voltage,                            flt_simple);
  reg_handler(AttrType::output_threshold_pct_fall,              simple);
  reg_handler(AttrType::output_threshold_pct_rise,              simple);
  reg_handler(AttrType::piece_type,                             str_simple);
  reg_handler(AttrType::power_model,                            str_simple);
  reg_handler(AttrType::preferred_INPUT_PAD_volTAGE,            str_simple);
  reg_handler(AttrType::preferred_OUTPUT_PAD_volTAGE,           str_simple);
  reg_handler(AttrType::preferred_OUTPUT_PAD_SLEW_RATE_CONTROL, str_simple);
  reg_handler(AttrType::pulling_resistance_unit,                symstr_simple);
  reg_handler(AttrType::revision,                               symstr_simple);
  reg_handler(AttrType::simulation,                             str_simple);
  reg_handler(AttrType::SLEW_DERATE_FROM_library,               simple);
  reg_handler(AttrType::slew_lower_threshold_pct_fall,          simple);
  reg_handler(AttrType::slew_lower_threshold_pct_rise,          simple);
  reg_handler(AttrType::slew_upper_threshold_pct_fall,          simple);
  reg_handler(AttrType::slew_upper_threshold_pct_rise,          simple);
  reg_handler(AttrType::time_unit,                              symstr_simple);
  reg_handler(AttrType::volTAGE_UNIT,                           symstr_simple);

  // default attributes
  reg_handler(AttrType::DEFAULT_cell_leakage_power,             flt_simple);
  reg_handler(AttrType::DEFAULT_connection_class,               str_simple);
  reg_handler(AttrType::default_fall_delay_intercept,           flt_simple);
  reg_handler(AttrType::default_fall_pin_resistance,            flt_simple);
  reg_handler(AttrType::default_fanout_load,                    flt_simple);
  reg_handler(AttrType::default_inout_pin_cap,                  flt_simple);
  reg_handler(AttrType::default_inout_pin_fall_res,             flt_simple);
  reg_handler(AttrType::default_inout_pin_rise_res,             flt_simple);
  reg_handler(AttrType::default_input_pin_cap,                  flt_simple);
  reg_handler(AttrType::default_intrinsic_fall,                 flt_simple);
  reg_handler(AttrType::default_intrinsic_rise,                 flt_simple);
  reg_handler(AttrType::default_leakage_power_density,          flt_simple);
  reg_handler(AttrType::DEFAULT_MAX_capacitance,                flt_simple);
  reg_handler(AttrType::default_max_fanout,                     flt_simple);
  reg_handler(AttrType::default_max_transition,                 flt_simple);
  reg_handler(AttrType::default_max_utilization,                flt_simple);
  reg_handler(AttrType::default_min_porosity,                   flt_simple);
  reg_handler(AttrType::default_operating_conditions,           str_simple);
  reg_handler(AttrType::default_output_pin_cap,                 flt_simple);
  reg_handler(AttrType::default_output_pin_fall_res,            flt_simple);
  reg_handler(AttrType::default_output_pin_rise_res,            flt_simple);
  reg_handler(AttrType::default_rise_delay_intercept,           flt_simple);
  reg_handler(AttrType::default_rise_pin_resistance,            flt_simple);
  reg_handler(AttrType::default_slope_fall,                     flt_simple);
  reg_handler(AttrType::default_slope_rise,                     flt_simple);
  reg_handler(AttrType::default_wire_load,                      str_simple);
  reg_handler(AttrType::default_wire_load_area,                 flt_simple);
  reg_handler(AttrType::default_wire_load_capacitance,          flt_simple);
  reg_handler(AttrType::default_wire_load_mode,                 str_simple);
  reg_handler(AttrType::default_wire_load_resistance,           flt_simple);
  reg_handler(AttrType::default_wire_load_selection,            str_simple);

  // scaling attributes
  reg_handler(AttrType::K_process_cell_fall,                    flt_simple);
  reg_handler(AttrType::K_process_cell_leakage_power,           flt_simple);
  reg_handler(AttrType::K_process_cell_rise,                    flt_simple);
  reg_handler(AttrType::K_process_drive_current,                flt_simple);
  reg_handler(AttrType::k_process_drive_fall,                   flt_simple);
  reg_handler(AttrType::k_process_drive_rise,                   flt_simple);
  reg_handler(AttrType::K_process_fall_delay_intercept,         flt_simple);
  reg_handler(AttrType::K_process_fall_pin_resistance,          flt_simple);
  reg_handler(AttrType::K_process_fall_propagation,             flt_simple);
  reg_handler(AttrType::K_process_fall_transition,              flt_simple);
  reg_handler(AttrType::k_process_hold_fall,                    flt_simple);
  reg_handler(AttrType::k_process_hold_rise,                    flt_simple);
  reg_handler(AttrType::K_process_internal_power,               flt_simple);
  reg_handler(AttrType::K_process_intrinsic_fall,               flt_simple);
  reg_handler(AttrType::K_process_intrinsic_rise,               flt_simple);
  reg_handler(AttrType::k_process_min_period,                   flt_simple);
  reg_handler(AttrType::k_process_min_pulse_width_high,         flt_simple);
  reg_handler(AttrType::k_process_min_pulse_width_low,          flt_simple);
  reg_handler(AttrType::k_process_nochange_fall,                flt_simple);
  reg_handler(AttrType::k_process_nochange_rise,                flt_simple);
  reg_handler(AttrType::k_process_pin_cap,                      flt_simple);
  reg_handler(AttrType::k_process_recovery_fall,                flt_simple);
  reg_handler(AttrType::k_process_recovery_rise,                flt_simple);
  reg_handler(AttrType::k_process_removal_fall,                 flt_simple);
  reg_handler(AttrType::k_process_removal_rise,                 flt_simple);
  reg_handler(AttrType::k_process_rise_delay_intercept,         flt_simple);
  reg_handler(AttrType::k_process_rise_pin_resistance,          flt_simple);
  reg_handler(AttrType::k_process_rise_propagation,             flt_simple);
  reg_handler(AttrType::k_process_rise_transition,              flt_simple);
  reg_handler(AttrType::k_process_setup_fall,                   flt_simple);
  reg_handler(AttrType::k_process_setup_rise,                   flt_simple);
  reg_handler(AttrType::k_process_skew_fall,                    flt_simple);
  reg_handler(AttrType::k_process_skew_rise,                    flt_simple);
  reg_handler(AttrType::k_process_slope_fall,                   flt_simple);
  reg_handler(AttrType::k_process_slope_rise,                   flt_simple);
  reg_handler(AttrType::k_process_wire_cap,                     flt_simple);
  reg_handler(AttrType::k_process_wire_res,                     flt_simple);
  reg_handler(AttrType::K_TEMP_cell_fall,                       flt_simple);
  reg_handler(AttrType::K_TEMP_cell_leakage_power,              flt_simple);
  reg_handler(AttrType::K_TEMP_cell_rise,                       flt_simple);
  reg_handler(AttrType::K_TEMP_drive_current,                   flt_simple);
  reg_handler(AttrType::k_temp_drive_fall,                      flt_simple);
  reg_handler(AttrType::k_temp_drive_rise,                      flt_simple);
  reg_handler(AttrType::K_TEMP_fall_delay_intercept,            flt_simple);
  reg_handler(AttrType::K_TEMP_fall_pin_resistance,             flt_simple);
  reg_handler(AttrType::K_TEMP_fall_propagation,                flt_simple);
  reg_handler(AttrType::K_TEMP_fall_transition,                 flt_simple);
  reg_handler(AttrType::k_temp_hold_fall,                       flt_simple);
  reg_handler(AttrType::k_temp_hold_rise,                       flt_simple);
  reg_handler(AttrType::K_TEMP_internal_power,                  flt_simple);
  reg_handler(AttrType::K_TEMP_intrinsic_fall,                  flt_simple);
  reg_handler(AttrType::K_TEMP_intrinsic_rise,                  flt_simple);
  reg_handler(AttrType::k_temp_min_period,                      flt_simple);
  reg_handler(AttrType::k_temp_min_pulse_width_high,            flt_simple);
  reg_handler(AttrType::k_temp_min_pulse_width_low,             flt_simple);
  reg_handler(AttrType::k_temp_nochange_fall,                   flt_simple);
  reg_handler(AttrType::k_temp_nochange_rise,                   flt_simple);
  reg_handler(AttrType::k_temp_pin_cap,                         flt_simple);
  reg_handler(AttrType::k_temp_recovery_fall,                   flt_simple);
  reg_handler(AttrType::k_temp_recovery_rise,                   flt_simple);
  reg_handler(AttrType::k_temp_removal_fall,                    flt_simple);
  reg_handler(AttrType::k_temp_removal_rise,                    flt_simple);
  reg_handler(AttrType::k_temp_rise_delay_intercept,            flt_simple);
  reg_handler(AttrType::k_temp_rise_pin_resistance,             flt_simple);
  reg_handler(AttrType::k_temp_rise_propagation,                flt_simple);
  reg_handler(AttrType::k_temp_rise_transition,                 flt_simple);
  reg_handler(AttrType::k_temp_setup_fall,                      flt_simple);
  reg_handler(AttrType::k_temp_setup_rise,                      flt_simple);
  reg_handler(AttrType::k_temp_skew_fall,                       flt_simple);
  reg_handler(AttrType::k_temp_skew_rise,                       flt_simple);
  reg_handler(AttrType::k_temp_slope_fall,                      flt_simple);
  reg_handler(AttrType::k_temp_slope_rise,                      flt_simple);
  reg_handler(AttrType::k_temp_wire_cap,                        flt_simple);
  reg_handler(AttrType::k_temp_wire_res,                        flt_simple);
  reg_handler(AttrType::K_volT_cell_fall,                       flt_simple);
  reg_handler(AttrType::K_volT_cell_leakage_power,              flt_simple);
  reg_handler(AttrType::K_volT_cell_rise,                       flt_simple);
  reg_handler(AttrType::K_volT_drive_current,                   flt_simple);
  reg_handler(AttrType::k_volt_drive_fall,                      flt_simple);
  reg_handler(AttrType::k_volt_drive_rise,                      flt_simple);
  reg_handler(AttrType::K_volT_fall_delay_intercept,            flt_simple);
  reg_handler(AttrType::K_volT_fall_pin_resistance,             flt_simple);
  reg_handler(AttrType::K_volT_fall_propagation,                flt_simple);
  reg_handler(AttrType::K_volT_fall_transition,                 flt_simple);
  reg_handler(AttrType::k_volt_hold_fall,                       flt_simple);
  reg_handler(AttrType::k_volt_hold_rise,                       flt_simple);
  reg_handler(AttrType::K_volT_internal_power,                  flt_simple);
  reg_handler(AttrType::K_volT_intrinsic_fall,                  flt_simple);
  reg_handler(AttrType::K_volT_intrinsic_rise,                  flt_simple);
  reg_handler(AttrType::k_volt_min_period,                      flt_simple);
  reg_handler(AttrType::k_volt_min_pulse_width_high,            flt_simple);
  reg_handler(AttrType::k_volt_min_pulse_width_low,             flt_simple);
  reg_handler(AttrType::k_volt_nochange_fall,                   flt_simple);
  reg_handler(AttrType::k_volt_nochange_rise,                   flt_simple);
  reg_handler(AttrType::k_volt_pin_cap,                         flt_simple);
  reg_handler(AttrType::k_volt_recovery_fall,                   flt_simple);
  reg_handler(AttrType::k_volt_recovery_rise,                   flt_simple);
  reg_handler(AttrType::k_volt_removal_fall,                    flt_simple);
  reg_handler(AttrType::k_volt_removal_rise,                    flt_simple);
  reg_handler(AttrType::k_volt_rise_delay_intercept,            flt_simple);
  reg_handler(AttrType::k_volt_rise_pin_resistance,             flt_simple);
  reg_handler(AttrType::k_volt_rise_propagation,                flt_simple);
  reg_handler(AttrType::k_volt_rise_transition,                 flt_simple);
  reg_handler(AttrType::k_volt_setup_fall,                      flt_simple);
  reg_handler(AttrType::k_volt_setup_rise,                      flt_simple);
  reg_handler(AttrType::k_volt_skew_fall,                       flt_simple);
  reg_handler(AttrType::k_volt_skew_rise,                       flt_simple);
  reg_handler(AttrType::k_volt_slope_fall,                      flt_simple);
  reg_handler(AttrType::k_volt_slope_rise,                      flt_simple);
  reg_handler(AttrType::k_volt_wire_cap,                        flt_simple);
  reg_handler(AttrType::k_volt_wire_res,                        flt_simple);

  // complex attributes
  reg_handler(AttrType::capacitive_load_unit,                   unit_complex);
  reg_handler(AttrType::default_part,                           complex);
  reg_handler(AttrType::define,                                 define);
  reg_handler(AttrType::define_cell_area,                       complex);
  reg_handler(AttrType::define_group,                           complex);
  reg_handler(AttrType::library_features,                       str1_complex);
  reg_handler(AttrType::PIECE_define,                           str1_complex);
  reg_handler(AttrType::routing_layers,                         complex);
  reg_handler(AttrType::technology,                             str1_complex);

  //fall_net_delay : name ;
  //rise_net_delay : name ;

  // group statements
  reg_handler(AttrType::cell,   		                   cell_handler);
  reg_handler(AttrType::dc_current_template,                    tmpl_handler);
  reg_handler(AttrType::em_lut_template,                        tmpl_handler);
  reg_handler(AttrType::fall_transition_degradation,            group_handler);
  reg_handler(AttrType::faults_lut_template,                    tmpl_handler);
  reg_handler(AttrType::input_voltage,		           iv_handler);
  reg_handler(AttrType::iv_lut_template,                        tmpl_handler);
  reg_handler(AttrType::lu_table_template,                      tmpl_handler);
  reg_handler(AttrType::NOISE_lut_TEMPLATE,                     tmpl_handler);
  reg_handler(AttrType::operating_conditions,	           oc_handler);
  reg_handler(AttrType::output_current_template,                tmpl_handler);
  reg_handler(AttrType::output_voltage,		           ov_handler);
  reg_handler(AttrType::part,                                   group_handler);
  reg_handler(AttrType::poly_template,                          tmpl_handler);
  reg_handler(AttrType::power_lut_TEMPLATE,                     tmpl_handler);
  reg_handler(AttrType::power_poly_template,                    tmpl_handler);
  reg_handler(AttrType::power_supply,                           group_handler);
  reg_handler(AttrType::PROPAGATION_lut_TEMPLATE,               tmpl_handler);
  reg_handler(AttrType::rise_transition_degradation,            group_handler);
  reg_handler(AttrType::SCALED_cell,                            group_handler);
  reg_handler(AttrType::scaling_factors,                        group_handler);
  reg_handler(AttrType::timing,                                 group_handler);
  reg_handler(AttrType::timing_range,                           group_handler);
  reg_handler(AttrType::type,                                   group_handler);
  reg_handler(AttrType::wire_load,                              wl_handler);
  reg_handler(AttrType::wire_load_selection,		           wls_handler);
  reg_handler(AttrType::wire_load_table,		           wlt_handler);
}

// @brief デストラクタ
LibraryHandler::~LibraryHandler()
{
}

// @brief 値を作る．
const AstNode*
LibraryHandler::gen_node(const FileRegion& loc,
			 const AstString* name,
			 const vector<const AstAttr*>& attr_list)
{
#warning "TODO: 未完成"
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
