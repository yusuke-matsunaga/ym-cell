#! /usr/bin/env python3

### @file domain.py
### @brief DomainHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from strgroup import StrGroupClassDef


class DomainClassDef(StrGroupClassDef) :

    def __init__(self) :
        super(StrGroupClassDef, self).__init__()
        self.data_type = 'domain'
        self.desc = 'ドメイン'
        self.ast_class = 'AstDomain'
        self.group_class = 'DomainHandler'
        self.attr_list = [
            # ( 属性名,           属性の型,          メンバ変数名, 必須フラグ, 複数フラグ ) のリスト
            ( 'calc_mode',        'string',         'mCalcMode',   False, False ),
            ( 'coefs',            'coefs',          'mCoefs',      False, False ),
            ( 'orders',           'orders',         'mOrders',     False, False ),
            ( 'variable_1_range', 'variable_range', 'mVar1Range',  False, False ),
            ( 'variable_2_range', 'variable_range', 'mVar2Range',  False, False ),
            ( 'variable_3_range', 'variable_range', 'mVar3Range',  False, False ),
            ]


if __name__ == '__main__' :
    import gen_handler_code

    class_def = DomainClassDef()
    gen_handler_code.main(class_def)
