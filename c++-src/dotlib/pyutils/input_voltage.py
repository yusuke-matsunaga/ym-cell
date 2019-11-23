#! /usr/bin/env python3

### @file input_voltage.py
### @brief InputVoltageHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from strgroup import StrGroupClassDef


class InputVoltageClassDef(StrGroupClassDef) :

    def __init__(self) :
        super().__init__()
        self.data_type = 'input_voltage'
        self.desc = 'input voltage'
        self.ast_class = 'AstInputVoltage'
        self.group_class = 'InputVoltageHandler'
        self.attr_list = [
            # ( 属性名,   属性の型,    メンバ変数名,  必須フラグ,  複数フラグ ) のリスト
            ( 'vil',      'expr',      'mVil',        True,        False ),
            ( 'vih',      'expr',      'mVih',        True,        False ),
            ( 'vimin',    'expr',      'mVimin',      True,        False ),
            ( 'vimax',    'expr',      'mVimax',      True,        False ),
            ]


if __name__ == '__main__' :
    import gen_handler_code

    class_def = InputVoltageClassDef()
    gen_handler_code.main(class_def)
