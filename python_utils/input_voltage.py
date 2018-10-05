#! /usr/bin/env python3

### @file input_voltage.py
### @brief InputVoltageHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.


class InputVoltageClassDef :

    def __init__(self) :
        self.data_type = 'input_voltage'
        self.desc = 'input voltage'
        self.ast_class = 'AstInputVoltage'
        self.header_class = 'Str1HeaderHandler'
        self.group_class = 'InputVoltageHandler'
        self.attr_list = [
            # ( 属性名,           属性の型,          メンバ変数名, 必須フラグ ) のリスト
            ( 'vil',             'expr',            'mVil',       True ),
            ( 'vih',             'expr',            'mVih',       True ),
            ( 'vimin',           'expr',            'mVimin',     True ),
            ( 'vimax',           'expr',            'mVimax',     True ),
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