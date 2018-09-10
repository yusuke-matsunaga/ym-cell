#! /usr/bin/env python3

### @file gen_reg_func.py
### @brief GroupHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

import sys
import argparse
import os.path


### @brief 属性の型からクラス名に変換する．
def type_to_class(attr_type) :
    # 各属性に対する AstNode のクラス
    class_dict = {
        'int' : 'Int',
        'float' : 'Float',
        'string' : 'String',
        'bool' : 'Bool',
        'direction' : 'PinDirection',
        'technology' : 'Technology',
        'timing_sense' : 'TimingSense',
        'timing_type' : ' TimingType',
        'expr' : 'Expr',
        'function' : 'Expr',

        'coefs' : 'FloatVector',
        'orders' : 'IntVector',
        'variable_range' : 'VariableRange',
        'float2complex' : 'Float2',
        'pg_pin' : 'PgPin',
        'dc_current' : 'DcCurrent',
        'electromigration' : 'Electromigration',
        'timing' : 'Timing',
        'tlatch' : 'Tlatch',
        '???' : '???',
        }
    return "Ast{}".format(class_dict[attr_type])


### @brief クラス名からインターロック用のマクロ名を作る．
def class_to_macro(class_name) :
    return "{}_H".format(class_name.upper())


### @brief 属性の型からパース関数名に変換する．
def type_to_function(attr_type) :
    return 'parse_{}'.format(attr_type)


### @brief 属性名からリスト型かどうか判別する．
def is_list_type(attr_name) :
    if attr_name == 'timing' :
        return True
    return False


### @brief 'reg_func' 用のコードを生成する．
def gen_reg_func(fout, attr) :
    attr_name, attr_type, member = attr
    str = """  reg_func(AttrType::{},
           [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool
           {{ return parser.{}({}, attr_type, attr_loc); }} );
""".format(attr_name, type_to_function(attr_type), member)
    fout.write(str);


### @brief メンバ変数の初期化文を生成する．
def gen_clear(fout, attr) :
    attr_name, attr_type, member = attr
    if is_list_type(attr_name) :
        str = "  {}.clear();\n".format(member)
    else :
        str = "  {} = nullptr;\n".format(member)
    fout.write(str)


### @brief 属性のアクセッサ関数宣言を生成する．
def gen_accessor_decl(fout, attr) :
    attr_name, attr_type, member = attr
    class_name = type_to_class(attr_type)
    fout.write("\n")
    fout.write('  /// @brief "{}" を返す．\n'.format(attr_name))
    if is_list_type(attr_name) :
        fout.write('  const vector<const {}*>&\n'.format(class_name))
    else :
        fout.write('  const {}*\n'.format(class_name))
    fout.write('  {}() const;\n'.format(attr_name))


### @brief 属性のアクセッサ関数定義を生成する．
def gen_accessor_def(fout, parent_class, attr) :
    attr_name, attr_type, member = attr
    class_name = type_to_class(attr_type)
    fout.write("\n")
    fout.write('// @brief "{}" を返す．\n'.format(attr_name))
    fout.write('inline\n')
    if is_list_type(attr_name) :
        fout.write('const vector<const {}*>&\n'.format(class_name))
    else :
        fout.write('const {}*\n'.format(class_name))
    fout.write('{}::{}() const;\n'.format(parent_class, attr_name))
    fout.write('{\n')
    fout.write('  return {};\n'.format(member))
    fout.write('}\n')


### @brief メンバ変数の定義を生成する．
def gen_member(fout, attr) :
    attr_name, attr_type, member = attr
    class_name = type_to_class(attr_type)
    fout.write("\n")
    fout.write("  // {}\n".format(attr_name))
    if is_list_type(attr_name) :
        str = "  vector<const {}*> {};\n".format(class_name, member)
    else :
        str = "  const {}* {};\n".format(class_name, member)
    fout.write(str)


if __name__ == '__main__' :

    parser = argparse.ArgumentParser()

    mode_group = parser.add_mutually_exclusive_group()
    mode_group.add_argument('--init',
                            action = 'store_true',
                            help = 'generate initialization code')
    mode_group.add_argument('--clear',
                            action = 'store_true',
                            help = 'generate clear code')
    mode_group.add_argument('--header',
                            action = 'store_true',
                            help = 'generate clear code')

    args = parser.parse_args()
    if not args :
        exit(1)

    fout = sys.stdout

    if args.init :
        for attr in attr_list :
            gen_reg_func(fout, attr)
    elif args.clear :
        for attr in attr_list :
            gen_clear(fout, attr)
    elif args.header :
        for attr in attr_list :
            gen_member(fout, attr)
