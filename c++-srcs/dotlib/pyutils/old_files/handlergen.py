#! /usr/bin/env python3
#
# @file handlergen.py
# @brief GroupHandler の実装コードを作るスクリプト
# @author Yusuke Matsunaga (松永 裕介)
#
# Copyright (C) 2018 Yusuke Matsunaga
# All rights reserved.

# 属性名をメンバ変数名に変換する．
def make_member_name(name) :
    upper = True
    ans = 'm'
    for c in name :
        if c == '_' :
            upper = True
        else :
            if upper :
                ans += c.upper()
            else :
                ans += c
            upper = False
    return ans


# メンバ変数の定義を作る．
def make_member_defition(data) :
    for name, handler in data :
        member = make_member_name(name)
        print('')
        print('  // {}'.format(name))
        if handler :
            print('  {} {}'.format(handler, member))


# コンストラクタ中の初期化構文を作る．
def make_constructor_definition(data) :
    for name, handler in data :
        member = make_member_name(name)
        if handler :
            print('  {}(parser),'.format(member))


# clear_value() を呼び出すコードを作る．
def make_clear_value(data) :
    for name, handler in data :
        member = make_member_name(name)
        if handler :
            print('  {}.clear_value();'.format(member))
