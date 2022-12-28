#! /usr/bin/env python3

"""py_ym_cell 用のテストプログラム

:file: read_mislib_test.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2022 Yusuke Matsunaga, All rights reserved.
"""

import sys
import io
import ym_cell

assert len(sys.argv) == 3
filename = sys.argv[1]
exp_filename = sys.argv[2]
lib = ym_cell.ClibCellLibrary.read_mislib(filename)
lines = lib.to_string_list()

with open(exp_filename, "rt") as exp_f:
    exp_lines = exp_f.readlines()

    assert len(lines) == len(exp_lines)
    n = len(lines)
    for i in range(n):
        line = lines[i]
        exp_line = exp_lines[i].rstrip('\n')
        if line != exp_line:
            print(f'"lines[{i}]     = {lines[i]}"')
            print(f'"exp_lines[{i}] = {exp_lines[i]}"')
            assert False
