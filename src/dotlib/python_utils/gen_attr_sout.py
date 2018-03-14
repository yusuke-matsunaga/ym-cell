#! /usr/bin/env python3
#
# @file gen_attr_sout.py
# @brief AttrType のストリーム出力演算子を作るスクリプト
# @author Yusuke Matsunaga (松永 裕介)
#
# Copyright (C) 2018 Yusuke Matsunaga
# All rights reserved.

from attr_list import attr_list, conv_to_type

for attr_str in attr_list :
    attr_type = conv_to_type(attr_str)
    print('  case {}: s << "{}"; break;'.format(attr_type, attr_str))
