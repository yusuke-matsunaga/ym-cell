#! /usr/bin/env python3

""" ClibDirectionのテストスクリプト

:file: py_ClibDirection_test.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2024 Yusuke Matsunaga, All rights reserved.
"""

import pytest
import ymcell

def test_clibdirection_input():
    val1 = ymcell.ClibDirection("input")
    assert val1 == ymcell.ClibDirection.input
    assert val1.__repr__() == "input"

def test_clibdirection_output():
    val1 = ymcell.ClibDirection("output")
    assert val1 == ymcell.ClibDirection.output
    assert val1.__repr__() == "output"

def test_clibdirection_inout():
    val1 = ymcell.ClibDirection("inout")
    assert val1 == ymcell.ClibDirection.inout
    assert val1.__repr__() == "inout"

def test_clibdirection_internal():
    val1 = ymcell.ClibDirection("internal")
    assert val1 == ymcell.ClibDirection.internal
    assert val1.__repr__() == "internal"

def test_clibdirection_none():
    val1 = ymcell.ClibDirection("none")
    assert val1 is None

    
