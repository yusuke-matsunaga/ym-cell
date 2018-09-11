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


# BOMコードを出力する．
def write_BOM(fout) :
    fout.write('\ufeff')

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

        'pin' : 'Pin',
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


### @brief AstXXX.h を生成する．
### @param[in] fout 出力先のファイルオブジェクト
### @param[in] class_def クラスの情報を持つオブジェクト
def gen_ast_header(fout, class_def) :
    class_name = type_to_class(class_def.data_type)
    desc = class_def.desc
    attr_list = class_def.attr_list
    macro_name = class_to_macro(class_name)

    write_BOM(fout)
    fout.write('#ifndef {}\n'.format(macro_name))
    fout.write('#define {}\n'.format(macro_name))
    fout.write('\n')
    fout.write('/// @file {}.h\n'.format(class_name))
    fout.write('/// @brief {} のヘッダファイル\n'.format(class_name))
    fout.write('/// @author Yusuke Matsunaga (松永 裕介)\n')
    fout.write('\n')
    fout.write('/// Copyright (C) 2018 Yusuke Matsunaga\n')
    fout.write('/// All rights reserved.\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('#include "dotlib_nsdef.h\n')
    fout.write('#include "AstNode.h"\n')
    fout.write('#include "ym/Alloc.h"\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('BEGIN_NAMESPACE_YM_DOTLIB\n')
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('/// @class {} {}.h "dotlib/{}.h"\n'.format(class_name, class_name, class_name))
    fout.write('/// @brief {} の情報を表す AstNode の派生クラス\n'.format(desc))
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('class {} :\n'.format(class_name))
    fout.write('  public AstNode\n')
    fout.write('{\n')
    fout.write('public:\n')
    fout.write('\n')
    fout.write('  /// @brief コンストラクタ\n')
    fout.write('  {}(const FileRegion& loc,\n'.format(class_name))
    cspc = ' ' * len('  {}('.format(class_name))
    class_def.gen_constructor_arguments(fout, cspc)
    for attr_name, attr_type, member in attr_list :
        attr_class = type_to_class(attr_type)
        fout.write('{}const {}* {},\n'.format(cspc, attr_class, attr_name))
    fout.write('{}Alloc& alloc);\n'.format(cspc))
    fout.write('\n')
    fout.write('  /// @brief デストラクタ\n')
    fout.write('  ~{}()\n'.format(class_name))
    fout.write('\n')
    fout.write('\n')
    fout.write('public:\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('  // 外部インターフェイス\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    class_def.gen_accessor_decl(fout)
    for attr_name, attr_type, member in attr_list :
        attr_class = type_to_class(attr_type)
        fout.write('\n')
        if is_list_type(attr_type) :
            fout.write('  /// @brief "{}" リストの要素数を返す．\n'.format(attr_name))
            fout.write('  int\n')
            fout.write('  {}_num() const;\n'.format(attr_name))
            fout.write('\n')
            fout.write('  /// @brief "{}" リストの要素を得る．\n'.format(attr_name))
            fout.write('  /// @param[in] pos 位置番号 ( 0 <= pos < {}_num() )\n'.format(attr_name))
            fout.write('  const {}*\n'.format(attr_class))
            fout.write('  {}_elem(int pos) const;\n'.format(attr_name))
        else :
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
    class_def.gen_member_def(fout)
    for attr_name, attr_type, member in attr_list :
        attr_class = type_to_class(attr_type)
        fout.write('\n')
        if is_list_type(attr_type) :
            fout.write('  // "{}" リストの要素数\n'.format(attr_name))
            fout.write('  int {}Num;\n'.format(member))
            fout.write('\n')
            fout.write('  // "{}" リストの本体\n'.format(attr_name))
            fout.write('  const {}** {}List;\n'.format(attr_class, member))
        else :
            fout.write('  // "{}"\n'.format(attr_name))
            fout.write('  const {}* {};\n'.format(attr_class, member))
    fout.write('\n')
    fout.write('};\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('// インライン関数の定義\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    class_def.gen_accessor_impl(fout)
    for attr_name, attr_type, member in attr_list :
        attr_class = type_to_class(attr_type)
        fout.write('\n')
        if is_list_type(attr_type) :
            fout.write('// @brief "{}" リストの要素数を返す．\n'.format(attr_name))
            fout.write('inline\n')
            fout.write('int\n')
            fout.write('{}::{}_num() const\n'.format(class_name, attr_name))
            fout.write('{\n')
            fout.write('  return {}Num;\n'.format(member))
            fout.write('}\n')
            fout.write('\n')
            fout.write('// @brief "{}" リストの要素を得る．\n'.format(attr_name))
            fout.write('// @param[in] pos 位置番号 ( 0 <= pos < {}_num() )\n'.format(attr_name))
            fout.write('const {}*\n'.format(attr_class))
            fout.write('{}::{}_elem(int pos) const\n'.format(class_name, attr_name))
            fout.write('{\n')
            fout.write('  ASSERT_COND( pos >= 0 && pos < {}_num() );\n'.format(attr_name))
            fout.write('\n')
            fout.write('  return {}List[pos];\n'.format(member))
            fout.write('}\n')
        else :
            fout.write('// @brief "{}" を返す．\n'.format(attr_name))
            fout.write('const {}*\n'.format(attr_class))
            fout.write('{}::{}() const\n'.format(class_name, attr_name))
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
    class_name = type_to_class(class_def.data_type)
    desc = class_def.desc
    attr_list = class_def.attr_list

    write_BOM(fout)
    fout.write('\n')
    fout.write('/// @file {}.cc\n'.format(class_name))
    fout.write('/// @brief {} の実装ファイル\n'.format(class_name))
    fout.write('/// @author Yusuke Matsunaga (松永 裕介)\n')
    fout.write('\n')
    fout.write('/// Copyright (C) 2018 Yusuke Matsunaga\n')
    fout.write('/// All rights reserved.\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('#include "dotlib/AstMgr.h"\n')
    fout.write('#include "dotlib/{}.h"\n'.format(class_name))
    fout.write('#include "ym/Range.h"\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('BEGIN_NAMESPACE_YM_DOTLIB\n')
    fout.write('\n')
    fout.write('// @brief {} を表す AstNode の派生クラス ({}) を生成する．\n'.format(desc, class_name))
    fout.write('const {}*\n'.format(class_name))
    fout.write('AstMgr::new_{}(const FileRegion& loc,\n'.format(class_def.data_type))
    cspc = ' ' * (len('AstMgr::new_{}('.format(class_def.data_type)))
    class_def.gen_constructor_arguments(fout, cspc)
    first = True
    for attr_name, attr_type, member in attr_list :
        if first :
            first = False
        else :
            fout.write(',\n')
        attr_class = type_to_class(attr_type)
        if is_list_type(attr_type) :
            fout.write('{}const vector<const {}*>& {}_list'.format(cspc, attr_class, attr_name))
        else :
            fout.write('{}const {}* {}'.format(cspc, attr_class, attr_name))
    fout.write(')\n')
    fout.write('{\n')
    fout.write('  void* p = mAlloc.get_memory(sizeof({}));\n'.format(class_name))
    fout.write('  return new (p) {}(loc);\n') # 未完成
    fout.write('}\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('// クラス {}\n'.format(class_name))
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('\n')
    fout.write('// @brief コンストラクタ\n')
    fout.write('{0}::{0}(const FileRegion& loc,\n'.format(class_name))
    cspc = ' ' * len('{0}::{0}('.format(class_name))
    class_def.gen_constructor_arguments(fout, cspc)
    for attr_name, attr_type, member in attr_list :
        attr_class = type_to_class(attr_type)
        if is_list_type(attr_type) :
            fout.write('{}const vector<const {}*>& {},\n'.format(cspc, attr_class, attr_name))
        else :
            fout.write('{}const {}* {},\n'.format(cspc, attr_class, attr_name))
    fout.write('{}Alloc& alloc) :\n'.format(cspc))
    fout.write('  AstNode(loc),\n')
    class_def.gen_member_init(fout)
    first = True
    for attr_name, attr_type, member in attr_list :
        if first :
            first = False
        else :
            fout.write(',\n')
        attr_class = type_to_class(attr_type)
        if is_list_type(attr_type) :
            fout.write('  {}Num({}_list.size()),\n'.format(member, attr_name))
            fout.write('  {}List(alloc.get_array<const {}*>({}Num))'.format(member, attr_class, member))
        else :
            fout.write('  {}({})'.format(member, attr_name))
    fout.write('\n')
    fout.write('{\n')
    class_def.gen_member_init2(fout)
    for attr_name, attr_type, member in attr_list :
        if is_list_type(attr_type) :
            fout.write('  for ( auto i: Range({}Num) ) {{\n'.format(member))
            fout.write('    {}List[i] = {}_list[i];\n'.format(member, attr_name))
            fout.write('  }\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @brief デストラクタ\n')
    fout.write('{0}::~{0}()\n'.format(class_name))
    fout.write('{\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @brief 内容をストリームに出力する．\n')
    fout.write('// @param[in] s 出力先のストリーム\n')
    fout.write('// @param[in] indent インデント量\n')
    fout.write('void\n')
    fout.write('{}::dump(ostream& s,\n'.format(class_name))
    cspc = ' ' * len('{}::dump('.format(class_name))
    fout.write('{}int indent) const\n'.format(cspc))
    fout.write('{\n')
    fout.write('  #warning "TODO: 未完成"\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('END_NAMESPACE_YM_DOTLIB\n')


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
