#! /usr/bin/env python3

### @file strlistgroup.py
### @brief StrListHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from basegroup import BaseGroupClassDef

class StrListGroupClassDef(BaseGroupClassDef) :

    def __init__(self) :
        super().__init__()
        self.has_list = True

    @property
    def ast_baseclass(self) :
        return 'AstNameListNode'

    @property
    def header_class(self) :
        return 'StrListHandler'
