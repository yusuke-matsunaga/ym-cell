#! /usr/bin/env python3

### @file domain.py
### @brief DomainHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.


class DomainClassDef :

    def __init__(self) :
        self.data_type = 'domain'
        self.desc = 'ドメイン'
        self.ast_class = 'AstDomain'
        self.header_class = 'Str1HeaderHandler'
        self.group_class = 'DomainHandler'
        self.attr_list = [
            # ( 属性名,           属性の型,          メンバ変数名, 必須フラグ ) のリスト
            ( 'calc_mode',        'string',         'mCalcMode',  False ),
            ( 'coefs',            'coefs',          'mCoefs',     False ),
            ( 'orders',           'orders',         'mOrders',    False ),
            ( 'variable_1_range', 'variable_range', 'mVar1Range', False ),
            ( 'variable_2_range', 'variable_range', 'mVar2Range', False ),
            ( 'variable_3_range', 'variable_range', 'mVar3Range', False ),
            ]

    ### @brief アクセッサー関数の宣言を生成する．
    def gen_accessor_decl(self, fout) :
        fout.write('\n')
        fout.write('  /// @brief 名前を返す．\n')
        fout.write('  const AstString*\n')
        fout.write('  name() const;\n')

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
    def gen_member_init(self, fout) :
        fout.write('  mName(header.value(),\n')

    ### @brief メンバの初期化文を生成する．
    def gen_member_init2(self, fout) :
        pass
