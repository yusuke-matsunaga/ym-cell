#! /usr/bin/env python3

"""ymcell パッケージのテストプログラム

:file: py_ymcell_test.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2022 Yusuke Matsunaga, All rights reserved.
"""

import pytest
import ymcell
import os
from pathlib import Path


def test_read_mislib():
    current_dir = os.path.dirname(__file__)
    data_dir = os.path.join(current_dir, os.pardir)
    lib2_filename = os.path.join(data_dir, 'testdata', 'lib2.genlib')
    exp_filename = os.path.join(data_dir, 'testdata', 'lib2.genlib.display')
    lib = ymcell.ClibCellLibrary.read_mislib(lib2_filename)
    lines = lib.to_string_list()
    n = len(lines)
    
    with open(exp_filename, "rt") as exp_f:
        exp_lines = exp_f.readlines()

        assert len(exp_lines) == n
        for i in range(n):
            line = lines[i]
            exp_line = exp_lines[i].rstrip('\n')
            assert exp_line == line

def test_read_liberty():
    current_dir = os.path.dirname(__file__)
    data_dir = os.path.join(current_dir, os.pardir)
    lib_filename = os.path.join(data_dir, 'testdata', 'HIT018.typ.snp')
    exp_filename = os.path.join(data_dir, 'testdata', 'HIT018.typ.snp.display')
    lib = ymcell.ClibCellLibrary.read_liberty(lib_filename)
    lines = lib.to_string_list()
    n = len(lines)
    
    with open(exp_filename, "rt") as exp_f:
        exp_lines = exp_f.readlines()

        assert len(exp_lines) == n
        for i in range(n):
            line = lines[i]
            exp_line = exp_lines[i].rstrip('\n')
            assert exp_line == line
