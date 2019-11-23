#! /usr/bin/env python3

### @file basegroup.py
### @brief GroupHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2019 Yusuke Matsunaga
### All rights reserved.


class BaseGroupClassDef :

    def __init__(self) :
        self.has_list = False

    ### @brief アクセッサー関数の宣言を生成する．
    def gen_accessor_decl(self, fout) :
        pass

    ### @brief メンバの初期化文を生成する．
    def gen_member_init(self, fout) :
        pass

    ### @brief アクセッサー関数のインライン定義を生成する．
    def gen_accessor_impl(self, fout) :
        pass

    ### @brief メンバ定義を生成する．
    def gen_member_def(self, fout) :
        pass

    ### @brief メンバの初期化文を生成する．
    def gen_member_init2(self, fout) :
        pass
