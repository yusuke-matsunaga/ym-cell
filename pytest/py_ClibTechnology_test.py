#! /usr/bin/env python3

""" ClibTechnologyのテストスクリプト

:file: py_ClibTechnology_test.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2024 Yusuke Matsunaga, All rights reserved.
"""

import pytest
import ymcell

def test_clibtechnology_cmos():
    val1 = ymcell.ClibTechnology("cmos")
    assert val1 == ymcell.ClibTechnology.cmos
    assert val1.__repr__() == "cmos"

def test_clibtechnology_fpga():
    val1 = ymcell.ClibTechnology("fpga")
    assert val1 == ymcell.ClibTechnology.fpga
    assert val1.__repr__() == "fpga"

def test_clibtechnology_none():
    val1 = ymcell.ClibTechnology("none")
    assert val1 is None

    
