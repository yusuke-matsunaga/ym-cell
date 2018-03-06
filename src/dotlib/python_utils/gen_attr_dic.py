#! /usr/bin/env python3
#
# @file gen.py
# @brief
# @author Yusuke Matsunaga (松永 裕介)
#
# Copyright (C) 2018 Yusuke Matsunaga
# All rights reserved.

from attr_list import attr_list

for attr_str in attr_list :
    attr_type = 'ATTR_{}'.format(attr_str.upper())
    print('  mDic.add("{}", {});'.format(attr_str, attr_type))
