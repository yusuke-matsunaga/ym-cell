#! /usr/bin/env python3

### @file strgroup.py
### @brief StrHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from basegroup import BaseGroupClassDef


class StrGroupClassDef(BaseGroupClassDef) :

    def __init__(self) :
        super().__init__()

    @property
    def ast_baseclass(self) :
        return 'AstNameNode'

    @property
    def header_class(self) :
        return 'StrHandler'
