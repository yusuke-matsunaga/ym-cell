#! /usr/bin/env python3

### @file base_curves.py
### @brief 'base_curves' のパース用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from gen_handler_code import type_to_ast

class BaseCurvesClassDef :

    def __init__(self) :
        self.data_type = 'base_curves'
        self.desc = 'base_curves'
        self.ast_class = 'AstBaseCurves'
        self.header_class = 'StrHeaderHandler'
        self.group_class = 'PinHandler'
        self.attr_list = [
            # ( 属性名, 属性の型, メンバ変数名 ) のリスト
            ( 'base_curve_type', 'str1header', 'mBaseCurveType', True, False ),
            ( 'curve_x', 'float_vector', 'mCurveX', True, False ),
            ( 'curve_y', 'int_float_vector', 'mCurveY', True, False ),
            ]

    ### @brief アクセッサー関数の宣言を生成する．
    def gen_accessor_decl(self, fout) :
        fout.write('\n')
        fout.write('  /// @brief 名前を返す．\n')
        fout.write('  const AstString*\n')
        fout.write('  name() const;\n')

    ### @brief メンバの初期化文を生成する．
    def gen_member_init(self, fout) :
        fout.write('  mName(header.value()),\n')

    ### @brief アクセッサー関数のインライン定義を生成する．
    def gen_accessor_impl(self, fout) :
        class_name = self.ast_class
        fout.write('\n')
        fout.write('// @brief 名前を返す．\n')
        fout.write('inline\n')
        fout.write('const AstString*\n')
        fout.write('{}::name() const\n'.format(class_name))
        fout.write('{\n')
        fout.write('  return mName;\n')
        fout.write('}\n')

    ### @brief メンバ定義を生成する．
    def gen_member_def(self, fout) :
        fout.write('\n')
        fout.write('  // 名前\n')
        fout.write('  const AstString* mName;\n')

    ### @brief メンバの初期化文を生成する．
    def gen_member_init2(self, fout) :
        pass
