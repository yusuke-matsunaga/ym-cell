#! /usr/bin/env python3

"""CodeGen で用いられる補助クラスの定義

:file: cgutils.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2024 Yusuke Matsunaga, All rights reserved.
"""


class NL:
    """改行を表すクラス"""
    def __init__(self):
        pass

    def gen(self, *, fout):
        fout.write('\n')

        
class Text:
    """テキストを表すクラス"""
    def __init__(self, body, *, replace_list = []):
        self.body = body
        self.replace_list = replace_list

    def gen(self, *, fout):
        """内容を出力する．"""
        body = self.body
        for key, value in self.replace_list:
            body = body.replace(key, value)
        fout.write(body)


class List:
    """リスト構造を表すクラス"""
    def __init__(self, body):
        self.body = body

    def gen(self, *, fout):
        """内容を出力する．"""
        for code in self.body:
            if code is not None:
                code.gen(fout=fout)
            
        
class Block:
    """ブロック構造を表すクラス"""
    def __init__(self, *, head=None, body=None, tail=None):
        list_body = [head, body, tail]
        self.body = List(list_body)
        
    def gen(self, *, fout):
        """内容を出力する．"""
        self.body.gen(fout=fout)
