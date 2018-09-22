#! /usr/bin/env python3

### @file domain.py
### @brief DomainHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from str1group import Str1GroupClassDef


class DomainClassDef(Str1GroupClassDef) :

    def __init__(self) :
        self.data_type = 'domain'
        self.desc = 'ドメイン'
        self.ast_class = 'AstDomain'
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
