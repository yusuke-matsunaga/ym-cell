#! /usr/bin/env python3

""" ClibCPVのテストスクリプト

:file: py_ClibCPV_test.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2024 Yusuke Matsunaga, All rights reserved.
"""

import pytest
import ymcell

def test_clibcpv_L():
    val1 = ymcell.ClibCPV("L")
    assert val1 == ymcell.ClibCPV.L
    assert val1.__repr__() == "L"

def test_clibcpv_H():
    val1 = ymcell.ClibCPV("H")
    assert val1 == ymcell.ClibCPV.H
    assert val1.__repr__() == "H"

def test_clibcpv_N():
    val1 = ymcell.ClibCPV("N")
    assert val1 == ymcell.ClibCPV.N
    assert val1.__repr__() == "N"

def test_clibcpv_T():
    val1 = ymcell.ClibCPV("T")
    assert val1 == ymcell.ClibCPV.T
    assert val1.__repr__() == "T"

def test_clibcpv_X():
    val1 = ymcell.ClibCPV("X")
    assert val1 == ymcell.ClibCPV.X
    assert val1.__repr__() == "X"

    
