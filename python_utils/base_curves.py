#! /usr/bin/env python3

### @file base_curves.py
### @brief 'base_curves' のパース用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from str1gropu import Str1GroupClassDef

class BaseCurvesClassDef(Str1GroupClassDef) :

    def __init__(self) :
        self.data_type = 'base_curves'
        self.desc = 'base_curves'
        self.ast_class = 'AstBaseCurves'
        self.group_class = 'BaseCurvesHandler'
        self.attr_list = [
            # ( 属性名, 属性の型, メンバ変数名 ) のリスト
            ( 'base_curve_type', 'str1header', 'mBaseCurveType', True, False ),
            ( 'curve_x', 'float_vector', 'mCurveX', True, False ),
            ( 'curve_y', 'int_float_vector', 'mCurveY', True, False ),
            ]
