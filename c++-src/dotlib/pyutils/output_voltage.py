#! /usr/bin/env python3

### @file output_voltage.py
### @brief OutputVoltageHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from strgroup import StrGroupClassDef


class OutputVoltageClassDef(StrGroupClassDef) :

    def __init__(self) :
        super().__init__()
        self.data_type = 'output_voltage'
        self.desc = 'output voltage'
        self.ast_class = 'AstOutputVoltage'
        self.group_class = 'OutputVoltageHandler'
        self.attr_list = [
            # ( 属性名,   属性の型,   メンバ変数名,  必須フラグ, 複数フラグ ) のリスト
            ( 'vol',      'expr',     'mVol',        True,       False ),
            ( 'voh',      'expr',     'mVoh',        True,       False ),
            ( 'vomin',    'expr',     'mVomin',      True,       False ),
            ( 'vomax',    'expr',     'mVomax',      True,       False ),
            ]


if __name__ == '__main__' :
    import gen_handler_code

    class_def = OutputVoltageClassDef()
    gen_handler_code.main(class_def)
