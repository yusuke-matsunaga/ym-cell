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

# BOMコードを出力する．
def write_BOM(fout) :
    fout.write('\ufeff')

### @brief 属性の型からクラス名に変換する．
def type_to_class(attr_type) :
    return "Ast{}".format(class_dict[attr_type])

def type_to_handler(attr_type) :
    return "{}Handler".format(class_dict[attr_type])


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


### @brief XXXHandler.h を生成する．
### @param[in] fout 出力先のファイルオブジェクト
### @param[in] class_def クラスの情報を持つオブジェクト
def gen_handler_header(fout, class_def) :
    class_name = type_to_class(class_def.data_type)
    handler_name = type_to_handler(class_def.data_type)
    desc = class_def.desc
    attr_list = class_def.attr_list
    macro_name = class_to_macro(handler_name)

    write_BOM(fout)
    fout.write('#ifndef {}\n'.format(macro_name))
    fout.write('#define {}\n'.format(macro_name))
    fout.write('\n')
    fout.write('/// @file {}.h\n'.format(handler_name))
    fout.write('/// @brief {} のヘッダファイル\n'.format(handler_name))
    fout.write('/// @author Yusuke Matsunaga (松永 裕介)\n')
    fout.write('///\n')
    fout.write('/// Copyright (C) 2018 Yusuke Matsunaga\n')
    fout.write('/// All rights reserved.\n')
    fout.write('\n')
    fout.write('#include "dotlib/{}.h"\n'.format(class_def.parent_class))
    fout.write('\n')
    fout.write('\n')
    fout.write('BEGIN_NAMESPACE_YM_DOTLIB\n')
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('/// @class {0} {0}.h "dotlib/{0}.h"\n'.format(handler_name))
    fout.write('/// @brief \'{}\' Group Statement 用のハンドラ\n'.format(class_def.data_type))
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('class {} :\n'.format(handler_name))
    fout.write('  public {}\n'.format(class_def.parent_class))
    fout.write('{\n')
    fout.write('public:\n')
    fout.write('\n')
    fout.write('  /// @brief コンストラクタ\n')
    fout.write('  /// @param[in] parser パーサー\n')
    fout.write('  {}(DotlibParser& parser);\n'.format(handler_name))
    fout.write('\n')
    fout.write('  /// @brief デストラクタ\n')
    fout.write('  ~{}();\n'.format(handler_name))
    fout.write('\n')
    fout.write('\n')
    fout.write('public:\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('  // 外部インターフェイス\n')
    fout.write('  //////////////////////////////////////////////////////////////////////\n')
    fout.write('\n')
    fout.write('  /// @brief \'{}\' Group Statement の記述をパースする．\n'.format(class_def.data_type))
    if is_list_type(class_def.data_type) :
        fout.write('  /// @param[in] dst_list 読み込んだ値を格納するリスト\n')
    else :
        fout.write('  /// @param[in] dst  読み込んだ値を格納する変数\n')
    fout.write('  /// @retval true 正しく読み込んだ．\n')
    fout.write('  /// @retval false エラーが起きた．\n')
    fout.write('  bool\n')
    if is_list_type(class_def.data_type) :
        fout.write('  parse_value(vector<const {}*>& dst_list);\n'.format(class_name))
    else :
        fout.write('  parse_value(const {}*& dst);\n'.format(class_name))
    fout.write('\n')
    fout.write('\n')
    class_def.gen_handler_func_decl(fout)
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
    fout.write('  /// @param[in] group_loc グループ全体のファイル上の位置\n')
    fout.write('  /// @retval true 正常にパースした．\n')
    fout.write('  /// @retval false パース中にエラーが起こった．\n')
    fout.write('  bool\n')
    fout.write('  end_group(const FileRegion& group_loc) override;\n')
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
    class_def.gen_handler_member(fout);
    for attr_name, attr_type, member in attr_list :
        attr_class = type_to_class(attr_type)
        if is_list_type(attr_type) :
            fout.write('  vector<const {}*> {}List;\n'.format(attr_class, member))
        else :
            fout.write('  const {}* {};\n'.format(attr_class, member))
    fout.write('\n')
    fout.write('  // 読み込んだ値\n')
    fout.write('  const {}* mValue;\n'.format(class_name))
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
    class_name = type_to_class(class_def.data_type)
    handler_name = type_to_handler(class_def.data_type)
    desc = class_def.desc
    attr_list = class_def.attr_list

    write_BOM(fout)
    fout.write('\n')
    fout.write('/// @file {}.cc\n'.format(handler_name))
    fout.write('/// @brief {} の実装ファイル\n'.format(handler_name))
    fout.write('/// @author Yusuke Matsunaga (松永 裕介)\n')
    fout.write('///\n')
    fout.write('/// Copyright (C) 2018 Yusuke Matsunaga\n')
    fout.write('/// All rights reserved.\n')
    fout.write('\n')
    fout.write('\n')
    fout.write('#include "dotlib/{}.h"'.format(handler_name))
    fout.write('\n')
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('// クラス {}\n'.format(handler_name))
    fout.write('//////////////////////////////////////////////////////////////////////\n')
    fout.write('\n')
    fout.write('// @brief コンストラクタ\n')
    fout.write('// @param[in] parser パーサー\n')
    fout.write('{0}::{0}(DotlibParser& parser) :\n'.format(handler_name))
    fout.write('  {}(parser)\n'.format(class_def.parent_class))
    fout.write('{\n')
    fout.write('  // パース関数の登録\n')
    for attr_name, attr_type, member in attr_list :
        attr_func = type_to_function(attr_type)
        fout.write('  reg_func(AttrType::{},\n'.format(attr_name))
        fout.write('           [=](DotlibParser& parser, AttrType attr_type, const FileRegion& attr_loc) -> bool\n')
        if is_list_type(attr_type) :
            fmt_str = '           {{ return parser.{}({}List, attr_type, attr_loc); }} );\n'
        else :
            fmt_str = '           {{ return parser.{}({}, attr_type, attr_loc); }} );\n'
        fout.write(fmt_str.format(attr_func, member))
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @brief デストラクタ\n')
    fout.write('{0}::~{0}()\n'.format(handler_name))
    fout.write('{\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @breif \'{}\' Group Statement の記述をパースする．\n'.format(class_def.data_type))
    if is_list_type(class_def.data_type) :
        fout.write('// @param[in] dst_list 読み込んだ値を格納するリスト\n')
    else :
        fout.write('// @param[in] dst 読み込んだ値を格納する変数\n')
    fout.write('// @retval true 正しく読み込んだ．\n')
    fout.write('// @retval false エラーが起きた．\n')
    fout.write('bool\n')
    if is_list_type(class_def.data_type) :
        fout.write('{}::parse_value(vector<const {}*>& dst_list)\n'.format(handler_name, class_name))
    else :
        fout.write('{}::parse_value(const {}*& dst)\n'.format(handler_name, class_name))
    fout.write('{\n')
    fout.write('  bool stat = parse_group_statement();\n')
    fout.write('  if ( stat ) {\n')
    if is_list_type(class_def.data_type) :
        fout.write('    dst_list.push_back(mValue);\n')
    else :
        fout.write('    dst = mValue;\n')
    fout.write('  }\n')
    fout.write('  return stat;\n')
    fout.write('}\n')
    class_def.gen_handler_func_impl(fout)
    fout.write('// @brief グループ記述の始まり\n')
    fout.write('void\n')
    fout.write('{}::begin_group()\n'.format(handler_name))
    fout.write('{\n')
    for attr_name, attr_type, member in attr_list :
        if is_list_type(attr_name) :
            fmt_str = '  {}.clear();\n'
        else :
            fmt_str = '  {} = nullptr;\n'
        fout.write(fmt_str.format(member))
    fout.write('\n')
    fout.write('  mValue = nullptr;\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('// @brief グループ記述の終わり\n')
    fout.write('// @param[in] group_loc グループ全体のファイル上の位置\n')
    fout.write('// @retval true 正常にパーズした．\n')
    fout.write('// @retval false パーズ中にエラーが起こった．\n')
    fout.write('bool\n')
    fout.write('{}::end_group(const FileRegion& group_loc)\n'.format(handler_name))
    fout.write('{\n')
    fout.write('}\n')
    fout.write('\n')
    fout.write('END_NAMESPACE_YM_DOTLIB\n')
