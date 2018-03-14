#! /usr/bin/env python3
#
# @file gen_attr_type.py
# @brief
# @author Yusuke Matsunaga (松永 裕介)
#
# Copyright (C) 2018 Yusuke Matsunaga
# All rights reserved.

from attr_list import attr_list

for attr_str in attr_list :
    print('  {},'.format(attr_str))
