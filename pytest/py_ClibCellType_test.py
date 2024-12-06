#! /usr/bin/env python3

""" ClibCellTypeのテストスクリプト

:file: py_ClibCellType_test.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2024 Yusuke Matsunaga, All rights reserved.
"""

import pytest
import ymcell

def test_clibcelltype_none():
    val1 = ymcell.ClibCellType("none")
    assert val1 is None

def test_clibcelltype_Logic():
    val1 = ymcell.ClibCellType("Logic")
    assert val1 == ymcell.ClibCellType.Logic
    assert val1.__repr__() == "Logic"

def test_clibcelltype_FF():
    val1 = ymcell.ClibCellType("FF")
    assert val1 == ymcell.ClibCellType.FF
    assert val1.__repr__() == "FF"

def test_clibcelltype_Latch():
    val1 = ymcell.ClibCellType("Latch")
    assert val1 == ymcell.ClibCellType.Latch
    assert val1.__repr__() == "Latch"

def test_clibcelltype_FSM():
    val1 = ymcell.ClibCellType("FSM")
    assert val1 == ymcell.ClibCellType.FSM
    assert val1.__repr__() == "FSM"

    
