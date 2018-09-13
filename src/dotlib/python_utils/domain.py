#! /usr/bin/env python3

### @file domain.py
### @brief DomainHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

import sys
import argparse
import os.path

from gen_handler_code import gen_ast_header, gen_ast_source
from gen_handler_code import gen_handler_header, gen_handler_source
from gen_handler_code import type_to_class

class DomainClassDef :

    def __init__(self) :
        self.data_type = 'domain'
        self.desc = 'ドメイン'
        self.parent_class = 'Str1GroupHandler'
        self.attr_list = [
            # ( 属性名,           属性の型,          メンバ変数名, 必須フラグ ) のリスト
            ( 'calc_mode',        'string',         'mCalcMode',  False ),
            ( 'coefs',            'coefs',          'mCoefs',     False ),
            ( 'orders',           'orders',         'mOrders',    False ),
            ( 'variable_1_range', 'variable_range', 'mVar1Range', False ),
            ( 'variable_2_range', 'variable_range', 'mVar2Range', False ),
            ( 'variable_3_range', 'variable_range', 'mVar3Range', False ),
            ]

    ### @brief コンストラクタの引数の記述を生成する．
    def gen_constructor_arguments(self, fout, cspc) :
        fout.write('{}const AstString* name,\n'.format(cspc))

    ### @brief コンストラクタの引数の記述を生成する．
    def gen_constructor_arguments2(self, fout, cspc) :
        fout.write('{}name,\n'.format(cspc))

    ### @brief アクセッサー関数の宣言を生成する．
    def gen_accessor_decl(self, fout) :
        fout.write('\n')
        fout.write('  /// @brief 名前を返す．\n')
        fout.write('  const AstString*\n')
        fout.write('  name() const;\n')

    ### @brief メンバの初期化文を生成する．
    def gen_member_init(self, fout) :
        fout.write('  mName(name),\n')

    ### @brief メンバの初期化文を生成する．
    def gen_member_init2(self, fout) :
        pass

    ### @brief メンバ定義を生成する．
    def gen_member_def(self, fout) :
        fout.write('\n')
        fout.write('  // 名前\n')
        fout.write('  const AstString* mName;\n')

    ### @brief アクセッサー関数のインライン定義を生成する．
    def gen_accessor_impl(self, fout) :
        class_name = type_to_class(self.data_type)
        fout.write('\n')
        fout.write('// @brief 名前を返す．\n')
        fout.write('inline\n')
        fout.write('const AstString*\n')
        fout.write('{}::name() const\n'.format(class_name))
        fout.write('{\n')
        fout.write('  return mName;\n')
        fout.write('}\n')

    ### @brief ハンドラの関数宣言を生成する．
    def gen_handler_func_decl(self, fout) :
        pass

    ### @brief ハンドラのメンバ変数定義を生成する．
    def gen_handler_member(self, fout) :
        fout.write('  const AstString* mName;\n')

    ### @brief ハンドラの関数定義を生成する．
    def gen_handler_func_impl(self, fout) :
        pass

    ### @brief ハンドラの end_group() 中のヘッダ引数を生成する．
    def gen_handler_end_group_code(self, fout) :
        pass

    ### @brief ハンドラの end_group() 中のヘッダ引数を生成する．
    def gen_handler_arguments(self, cspc, fout) :
        fout.write('{}header_value(),\n'.format(cspc))


if __name__ == '__main__' :

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
    class_def = DomainClassDef()

    if args.ast_header :
        gen_ast_header(fout, class_def)
    elif args.ast_source :
        gen_ast_source(fout, class_def)
    elif args.handler_header :
        gen_handler_header(fout, class_def)
    elif args.handler_source :
        gen_handler_source(fout, class_def)
