#! /usr/bin/env python3

### @file gen_handler_func.py
### @brief GroupHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

import sys
import argparse
import os.path
import datetime


# 各属性に対する AstNode のクラス
class_dict = {
    # simple attribute
    'bool'             : 'Bool',
    'delay_model'      : 'DelayModel',
    'direction'        : 'PinDirection',
    'expr'             : 'Expr',
    'float'            : 'Float',
    'function'         : 'Expr',
    'int'              : 'Int',
    'string'           : 'String',
    'technology'       : 'Technology',
    'timing_sense'     : 'TimingSense',
    'timing_type'      : 'TimingType',

    # complex attribute
    'base_curve_type'  : 'BaseCurveType',
    'coefs'            : 'FloatVector',
    'curve_x'          : 'CurveX',
    'curve_y'          : 'CurveY',
    'dc_current'       : 'DcCurrent',
    'float2complex'    : 'Float2',
    'library_features' : 'LibraryFeatures',
    'orders'           : 'IntVector',
    'pg_pin'           : 'PgPin',
    'routing_layers'   : 'RoutingLayers',
    'str2complex'      : 'Str2',
    'str3complex'      : 'Str3',
    'unit'             : 'FloatStr',
    'variable_range'   : 'VariableRange',
    'voltage_map'      : 'StrFloat',

    # group attribute
    'average_number_of_faults' : 'AverageNumberOfFaults',
    'base_curves'                 : 'BaseCurves',
    'bundle'                      : 'Bundle',
    'bus'                         : 'Bus',
    'ccsn_first_stage'            : 'CcsnStage',
    'ccsn_last_stage'             : 'CcsnStage',
    'compact_ccs'                 : 'CompactCCS',
    'cell'                        : 'Cell',
    'define'                      : 'Define',
    'define_cell_area'            : 'DefineCellArea',
    'define_group'                : 'DefineGroup',
    'domain'                      : 'Domain',
    'dynamic_current'             : 'DynamicCurrent',
    'electromigration'            : 'ElectroMigration',
    'fall_capacitance_range'      : 'CapacitanceRange',
    'ff'                          : 'FF',
    'fpga_condition'              : 'FpgaCondition',
    'fpga_condition_value'        : 'FpgaConditionValue',
    'fpga_isd'                    : 'FpgaIsd',
    'functional_yield_metric'     : 'FunctionalYieldMetric',
    'generated_clock'             : 'GneratedClock',
    'hyperbolic_noise_above_high' : 'HyperbolicNoise',
    'hyperbolic_noise_below_low'  : 'HyperbolicNoise',
    'hyperbolic_noise_high'       : 'HyperbolicNoise',
    'hyperbolic_noise_low'        : 'HyperbolicNoise',
    'input_voltage'               : 'InputVoltage',
    'internal_power'              : 'InternalPower',
    'intrinsic_parasitic'         : 'IntrinsicParasitic',
    'latch'                       : 'Latch',
    'latch_bank'                  : 'LatchBank',
    'leakage_current'             : 'LeakageCurrent',
    'leakage_power'               : 'LeakagePower',
    'lut'                         : 'Lut',
    'max_capacitance'             : 'Table',
    'max_transition'              : 'Table',
    'min_capacitance'             : 'Table',
    'min_transition'              : 'Table',
    'min_pulse_width'             : 'MinPulseWidth',
    'minimum_period'              : 'MinimumPweriod',
    'mode_definition'             : 'ModeDefinition',
    'operating_conditions'        : 'OperatingConditions',
    'output_current'              : 'OutputCurrrent',
    'output_voltage'              : 'OutputVoltage',
    'part'                        : 'Part',
    'pg_current'                  : 'PgCurrent',
    'pg_pin'                      : 'PgPin',
    'pin'                         : 'Pin',
    'pin_capacitance'             : 'PinCapacitance',
    'power_supply'                : 'PowerSupply',
    'receiver_capacitance'        : 'ReceiverCapacitance',
    'rise_capacitance_range'      : 'CapacitanceRange',
    'routing_track'               : 'RoutingTrack',
    'scaled_cell'                 : 'ScaledCell',
    'sensitization'               : 'Sensitization',
    'statetable'                  : 'StateTable',
    'speed_grade'                 : 'SpeedGrade',
    'switching_group'             : 'SwitchingGroup',
    'template'                    : 'Tempalte',
    'test_cell'                   : 'TestCell',
    'timing'                      : 'Timing',
    'timing_range'                : 'TimingRange',
    'tlatch'                      : 'Tlatch',
    'type'                        : 'Type',
    'user_parameters'             : 'UserParameters',
    'vector'                      : 'Vector',
    'wire_load'                   : 'WireLoad',
    'wire_load_selection'         : 'WireLoadSelection',
    'wire_load_table'             : 'WireLoadTable',

    }


### @brief BOMコードを出力する．
### @param[in] fout 出力先のファイルオブジェクト
def write_BOM(fout) :
    fout.write('\ufeff')

### @brief コピーライトのコメントを出力する．
def write_Copyright(fout) :
    fout.write('/// Copyright (C) {} Yusuke Matsunaga\n'.format(datetime.datetime.today().year))
    fout.write('/// All rights reserved.\n')
    fout.write('\n')

### @brief 属性の型からクラス名に変換する．
### @param[in] attr_type 属性の型(class_dict の値)
### @return AstNode の派生クラス名を返す．
def type_to_ast(attr_type) :
    return "Ast{}".format(class_dict[attr_type])

### @brief 属性の型からハンドラクラス名に変換する．
### @param[in] attr_type 属性の型(class_dict の値)
### @return ハンドラのクラス名を返す．
def type_to_handler(attr_type) :
    return "{}Handler".format(class_dict[attr_type])

### @brief 属性の型からパース関数名に変換する．
### @param[in] attr_type 属性の型(class_dict の値)
def type_to_function(attr_type) :
    return 'parse_{}'.format(attr_type)

### @brief クラス名からインターロック用のマクロ名を作る．
### @param[in] class_name クラス名
def class_to_macro(class_name) :
    return "{}_H".format(class_name.upper())


### @brief 属性名からリスト型かどうか判別する．
### @param[in] attr_type 属性の型(class_dict の値)
### @retval True リスト型だった．
### @retval False 単一のオブジェクト型だった．
def is_list_type(attr_name) :
    if attr_name == 'timing' :
        return True
    else :
        return False

### @brief リストタイプの属性を持っているか調べる．
def check_has_list(class_def) :
    if class_def.has_list :
        return True
    for attr_name, attr_type, member, req, multi in class_def.attr_list :
        print(attr_name)
        if multi :
            return True
    return False


### @brief AstXXX.h を生成する．
### @param[in] fout 出力先のファイルオブジェクト
### @param[in] class_def クラスの情報を持つオブジェクト
def gen_ast_header(fout, class_def) :
    ast_class = class_def.ast_class
    ast_baseclass = class_def.ast_baseclass
    header_class = class_def.header_class
    group_class = class_def.group_class
    desc = class_def.desc
    attr_list = class_def.attr_list
    macro_name = class_to_macro(ast_class)
    has_list = check_has_list(class_def)

    write_BOM(fout)
    fout.write('#ifndef {}\n'.format(macro_name))
    fout.write('#define {}\n'.format(macro_name))
    fout.write('\n')
    fout.write('/// @file {}.h\n'.format(ast_class))
    fout.write('/// @brief {} のヘッダファイル\n'.format(ast_class))
    fout.write('/// @author Yusuke Matsunaga (松永 裕介)\n')
    fout.write('\n')
    write_Copyright(fout)
    fout.write('\n')
    fout.write('#include "dotlib_nsdef.h\n')
    fout.write('#include "{}.h"\n'.format(ast_baseclass))
    if has_list :
        fout.write('#include "AstArray.h"\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('BEGIN_NAMESPACE_YM_DOTLIB\n')
    fout.write('\n')
    fout.write('class {};\n'.format(header_class))
    fout.write('class {};\n'.format(group_class))
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('/// @class {0} {0}.h "dotlib/{0}.h"\n'.format(ast_class))
    fout.write('/// @brief {} の情報を表す AstNode の派生クラス\n'.format(desc))
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('class {} :\n'.format(ast_class))
    fout.write('  public {}\n'.format(ast_baseclass))
    fout.write('{\n')
    fout.write('public:\n')
    fout.write('\n')
    fout.write('  /// @brief コンストラクタ\n')
    head_str = '  {}'.format(ast_class)
    cspc = ' ' * len(head_str)
    fout.write('{}(const {}& header,\n'.format(head_str, header_class))
    if has_list :
        fout.write('{} const {}& group,\n'.format(cspc, group_class))
        fout.write('{} Alloc& alloc);\n'.format(cspc))
    else :
        fout.write('{} const {}& group);\n'.format(cspc, group_class))
    fout.write('\n')
    fout.write('  /// @brief デストラクタ\n')
    fout.write('  ~{}()\n'.format(ast_class))
    fout.write('\n')
    fout.write('\n')
    fout.write('public:\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('  // 外部インターフェイス\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    # 固有のメンバに対するアクセッサ関数の定義
    class_def.gen_accessor_decl(fout)
    # 各属性メンバに対するアクセッサ関数の定義
    for attr_name, attr_type, member, req, multi in attr_list :
        print(attr_name)
        attr_class = type_to_ast(attr_type)
        fout.write('\n')
        if multi :
            # リストタイプの場合
            fout.write('  /// @brief "{}" リストを得る．\n'.format(attr_name))
            fout.write('  AstArray<const {}*>\n'.format(attr_class))
            fout.write('  {}_list() const;\n'.format(attr_name))
        else :
            # スカラタイプの場合
            fout.write('  /// @brief "{}" を返す．\n'.format(attr_name))
            fout.write('  const {}*\n'.format(attr_class))
            fout.write('  {}() const;\n'.format(attr_name))
    fout.write('\n')
    fout.write('  /// @brief 内容をストリームに出力する．\n')
    fout.write('  /// @param[in] s 出力先のストリーム\n')
    fout.write('  /// @param[in] indent インデント両\n')
    fout.write('  void\n')
    fout.write('  dump(ostream& s,\n')
    fout.write('       int indent = 0) const override;\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('private:\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('  // データメンバ\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    # 固有のメンバの定義
    class_def.gen_member_def(fout)
    # 各属性メンバの定義
    for attr_name, attr_type, member, req, multi in attr_list :
        attr_class = type_to_ast(attr_type)
        fout.write('\n')
        if multi :
            # リストタイプの場合
            fout.write('  // "{}" リストの本体\n'.format(attr_name))
            fout.write('  AstArray<const {}*> {}List;\n'.format(attr_class, member))
        else :
            # スカラタイプの場合
            fout.write('  // "{}"\n'.format(attr_name))
            fout.write('  const {}* {};\n'.format(attr_class, member))
    fout.write('\n')
    fout.write('};\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('// インライン関数の定義\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    # 固有のメンバに対するアクセッサ関数のインライン定義
    class_def.gen_accessor_impl(fout)
    # 各属性メンバに対するアクセッサ関数のインライン定義
    for attr_name, attr_type, member, req, multi in attr_list :
        attr_class = type_to_ast(attr_type)
        fout.write('\n')
        if multi :
            fout.write('// @brief "{}" リストを得る．\n'.format(attr_name))
            fout.write('AstArray<const {}*>\n'.format(attr_class))
            fout.write('{}::{}_list() const\n'.format(ast_class, attr_name))
            fout.write('{\n')
            fout.write('  return {}List;\n'.format(member))
            fout.write('}\n')
        else :
            # スカラタイプの場合
            fout.write('// @brief "{}" を返す．\n'.format(attr_name))
            fout.write('const {}*\n'.format(attr_class))
            fout.write('{}::{}() const\n'.format(ast_class, attr_name))
            fout.write('{\n')
            fout.write('  return {};\n'.format(member))
            fout.write('}\n')
    fout.write('\n')
    fout.write('END_NAMESPACE_YM_DOTLIB\n')
    fout.write('\n')
    fout.write('#endif // {}\n'.format(macro_name))


### @brief AstXXX.cc を生成する．
### @param[in] fout 出力先のファイルオブジェクト
### @param[in] class_def クラスの情報を持つオブジェクト
def gen_ast_source(fout, class_def) :
    ast_class = type_to_ast(class_def.data_type)
    ast_baseclass = class_def.ast_baseclass
    header_class = class_def.header_class
    group_class = class_def.group_class
    desc = class_def.desc
    attr_list = class_def.attr_list
    has_list = check_has_list(class_def)

    write_BOM(fout)
    fout.write('\n')
    fout.write('/// @file {}.cc\n'.format(ast_class))
    fout.write('/// @brief {} の実装ファイル\n'.format(ast_class))
    fout.write('/// @author Yusuke Matsunaga (松永 裕介)\n')
    fout.write('\n')
    write_Copyright(fout)
    fout.write('\n')
    fout.write('#include "dotlib/AstMgr.h"\n')
    fout.write('#include "dotlib/{}.h"\n'.format(ast_class))
    fout.write('#include "dotlib/{}.h"\n'.format(header_class))
    fout.write('#include "dotlib/{}.h"\n'.format(group_class))
    fout.write('\n')
    fout.write('\n')
    fout.write('BEGIN_NAMESPACE_YM_DOTLIB\n')
    fout.write('\n')
    fout.write('// @brief {} を表す AstNode の派生クラス ({}) を生成する．\n'.format(desc, ast_class))
    fout.write('const {}*\n'.format(ast_class))
    head_str = 'AstMgr::new_{}'.format(class_def.data_type)
    cspc = ' ' * len(head_str)
    fout.write('{}(const {}& header,\n'.format(head_str, header_class))
    fout.write('{} const {}& group)\n'.format(cspc, group_class))
    fout.write('{\n')
    fout.write('  void* p = mAlloc.get_memory(sizeof({}));\n'.format(ast_class))
    if has_list :
        fout.write('  return new (p) {}(header, group, mAlloc);\n'.format(ast_class))
    else :
        fout.write('  return new (p) {}(header, group);\n'.format(ast_class))
    fout.write('}\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('// クラス {}\n'.format(ast_class))
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('\n')
    fout.write('// @brief コンストラクタ\n')
    head_str = '{0}::{0}'.format(ast_class)
    cspc = ' ' * len(head_str)
    fout.write('{}(const {}& header,\n'.format(head_str, header_class))
    if has_list :
        fout.write('{} const {}& group,\n'.format(cspc, group_class))
        fout.write('{} Alloc& alloc) :\n'.format(cspc))
    else :
        fout.write('{} const {}& group) :\n'.format(cspc, group_class))
    if class_def.has_list :
        fout.write('  {}{{FileRegion{{header.header_loc(), group.group_loc()}}, header, alloc}},\n'.format(ast_baseclass))
    else :
        fout.write('  {}{{FileRegion{{header.header_loc(), group.group_loc()}}, header}},\n'.format(ast_baseclass))
    # 固有のメンバに対する初期化文の生成
    class_def.gen_member_init(fout)
    first = True
    # 各属性メンバに対する初期化文の生成
    for attr_name, attr_type, member, req, multi in attr_list :
        if first :
            first = False
        else :
            fout.write(',\n')
        attr_class = type_to_ast(attr_type)
        if multi :
            # リストタイプの場合
            fout.write('  {0}List{{group.{0}List, alloc}}'.format(member))
        else :
            # スカラタイプの場合
            fout.write('  {0}{{group.{0}}}'.format(member))
    fout.write('\n')
    fout.write('{\n')
    # 固有のメンバに対する初期化文の生成(その２)
    # 配列要素のコピーを想定している．
    class_def.gen_member_init2(fout)
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @brief デストラクタ\n')
    fout.write('{0}::~{0}()\n'.format(ast_class))
    fout.write('{\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @brief 内容をストリームに出力する．\n')
    fout.write('// @param[in] s 出力先のストリーム\n')
    fout.write('// @param[in] indent インデント量\n')
    fout.write('void\n')
    fout.write('{}::dump(ostream& s,\n'.format(ast_class))
    cspc = ' ' * len('{}::dump('.format(ast_class))
    fout.write('{}int indent) const\n'.format(cspc))
    fout.write('{\n')
    fout.write('  #warning "TODO: 未完成"\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('END_NAMESPACE_YM_DOTLIB\n')


### @brief XXXHandler.h を生成する．
### @param[in] fout 出力先のファイルオブジェクト
### @param[in] class_def クラスの情報を持つオブジェクト
def gen_handler_header(fout, class_def) :
    ast_class = class_def.ast_class
    group_class = class_def.group_class
    desc = class_def.desc
    attr_list = class_def.attr_list
    macro_name = class_to_macro(group_class)

    write_BOM(fout)
    fout.write('#ifndef {}\n'.format(macro_name))
    fout.write('#define {}\n'.format(macro_name))
    fout.write('\n')
    fout.write('/// @file {}.h\n'.format(group_class))
    fout.write('/// @brief {} のヘッダファイル\n'.format(group_class))
    fout.write('/// @author Yusuke Matsunaga (松永 裕介)\n')
    fout.write('///\n')
    write_Copyright(fout)
    fout.write('#include "dotlib/GroupHandler.h"\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('BEGIN_NAMESPACE_YM_DOTLIB\n')
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('/// @class {0} {0}.h "dotlib/{0}.h"\n'.format(group_class))
    fout.write('/// @brief \'{}\' Group Statement 用のハンドラ\n'.format(class_def.data_type))
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('class {} :\n'.format(group_class))
    fout.write('  public GroupHandler\n')
    fout.write('{\n')
    fout.write('  friend class {};\n'.format(ast_class))
    fout.write('public:\n')
    fout.write('\n')
    fout.write('  /// @brief コンストラクタ\n')
    fout.write('  /// @param[in] parser パーサー\n')
    fout.write('  {}(DotlibParser& parser);\n'.format(group_class))
    fout.write('\n')
    fout.write('  /// @brief デストラクタ\n')
    fout.write('  ~{}();\n'.format(group_class))
    fout.write('\n')
    fout.write('\n')
    fout.write('public:\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('  // 外部インターフェイス\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('public:\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('  // GroupHandler の仮想関数\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('\n')
    fout.write('  /// @brief グループ記述の始まり\n')
    fout.write('  void\n')
    fout.write('  begin_group() override;\n')
    fout.write('\n')
    fout.write('  /// @brief グループ記述の終わり\n')
    fout.write('  /// @retval true 正常にパースした．\n')
    fout.write('  /// @retval false パース中にエラーが起こった．\n')
    fout.write('  bool\n')
    fout.write('  end_group() override;\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('private:\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('  // 内部で用いられる関数\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('private:\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('  // データメンバ\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('\n')
    # 各属性メンバの定義
    for attr_name, attr_type, member, req, multi in attr_list :
        attr_class = type_to_ast(attr_type)
        if multi :
            fmt_str = '  vector<const {}*> {};\n'
        else :
            fmt_str = '  const {}* {};\n'
        fout.write(fmt_str.format(attr_class, member))
    fout.write('\n')
    fout.write('};\n')
    fout.write('\n')
    fout.write('END_NAMESPACE_YM_DOTBLIB\n')
    fout.write('\n')
    fout.write('#endif // {}\n'.format(macro_name))


### @brief XXXHandler.cc を生成する．
### @param[in] fout 出力先のファイルオブジェクト
### @param[in] class_def クラスの情報を持つオブジェクト
def gen_handler_source(fout, class_def) :
    ast_class = class_def.ast_class
    group_class = class_def.group_class
    desc = class_def.desc
    attr_list = class_def.attr_list

    write_BOM(fout)
    fout.write('\n')
    fout.write('/// @file {}.cc\n'.format(group_class))
    fout.write('/// @brief {} の実装ファイル\n'.format(group_class))
    fout.write('/// @author Yusuke Matsunaga (松永 裕介)\n')
    fout.write('///\n')
    write_Copyright(fout)
    fout.write('#include "dotlib/{}.h"\n'.format(group_class))
    fout.write('\n')
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('// クラス {}\n'.format(group_class))
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('\n')
    fout.write('// @brief コンストラクタ\n')
    fout.write('// @param[in] parser パーサー\n')
    fout.write('{0}::{0}(DotlibParser& parser) :\n'.format(group_class))
    fout.write('  GroupHandler(parser)\n')
    fout.write('{\n')
    fout.write('  // パース関数の登録\n')
    for attr_name, attr_type, member, req, multi in attr_list :
        attr_func = type_to_function(attr_type)
        fout.write('  reg_func(AttrType::{},\n'.format(attr_name))
        fout.write('           [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool\n')
        if multi :
            fout.write('           {{ return parser.{}({}List, attr_type, attr_loc); }} );\n'.format(attr_func, member))
        else :
            fout.write('           {{ return parser.{}({}, attr_type, attr_loc); }} );\n'.format(attr_func, member))
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @brief デストラクタ\n')
    fout.write('{0}::~{0}()\n'.format(group_class))
    fout.write('{\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @brief グループ記述の始まり\n')
    fout.write('void\n')
    fout.write('{}::begin_group()\n'.format(group_class))
    fout.write('{\n')
    # 各属性メンバの初期化
    for attr_name, attr_type, member, req, multi in attr_list :
        if is_list_type(attr_name) :
            fmt_str = '  {}.clear();\n'
        else :
            fmt_str = '  {} = nullptr;\n'
        fout.write(fmt_str.format(member))
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @brief グループ記述の終わり\n')
    fout.write('// @retval true 正常にパーズした．\n')
    fout.write('// @retval false パーズ中にエラーが起こった．\n')
    fout.write('bool\n')
    fout.write('{}::end_group()\n'.format(group_class))
    fout.write('{\n')
    # 各属性メンバのチェック
    for attr_name, attr_type, member, req, multi in attr_list :
        if not req :
            continue
        if multi :
            fmt_str = '  if ( {}.empty() ) {{\n'
        else :
            fmt_str = '  if ( {} == nullptr ) {{\n'
        fout.write(fmt_str.format(member))
        fout.write('    MsgMgr::put_msg(__FILE__, __LINE__,\n')
        fout.write('                    group_loc,\n')
        fout.write('                    MsgType::Error,\n')
        fout.write('                    "DOTLIB_PARSER",\n')
        fout.write('                    "{} is missing.");\n'.format(attr_name))
        fout.write('    return false;\n')
        fout.write('  }\n')
    fout.write('  return true;\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('END_NAMESPACE_YM_DOTLIB\n')


def main(class_def) :

    parser = argparse.ArgumentParser()

    mode_group = parser.add_mutually_exclusive_group()
    mode_group.add_argument('--ast_header',
                            action = 'store_true',
                            help = 'generate AstPin.h')
    mode_group.add_argument('--ast_source',
                            action = 'store_true',
                            help = 'generate AstPin.cc')
    mode_group.add_argument('--handler_header',
                            action = 'store_true',
                            help = 'generate PinHandler.h')
    mode_group.add_argument('--handler_source',
                            action = 'store_true',
                            help = 'generate PinHandler.cc')

    args = parser.parse_args()
    if not args :
        exit(1)

    fout = sys.stdout

    if args.ast_header :
        gen_ast_header(fout, class_def)
    elif args.ast_source :
        gen_ast_source(fout, class_def)
    elif args.handler_header :
        gen_handler_header(fout, class_def)
    elif args.handler_source :
        gen_handler_source(fout, class_def)
