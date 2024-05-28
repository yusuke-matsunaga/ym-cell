#! /usr/bin/env python3

""" ClibTimingSenseのテストスクリプト

:file: py_ClibTimingSense_test.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2024 Yusuke Matsunaga, All rights reserved.
"""

import pytest
import ymcell

def test_clibtimingsense_positive_unate():
    val1 = ymcell.ClibTimingSense("positive_unate")
    assert val1 == ymcell.ClibTimingSense.positive_unate
    assert val1.__repr__() == "positive_unate"

def test_clibtimingsense_negative_unate():
    val1 = ymcell.ClibTimingSense("negative_unate")
    assert val1 == ymcell.ClibTimingSense.negative_unate
    assert val1.__repr__() == "negative_unate"

def test_clibtimingsense_non_unate():
    val1 = ymcell.ClibTimingSense("non_unate")
    assert val1 == ymcell.ClibTimingSense.non_unate
    assert val1.__repr__() == "non_unate"

def test_clibtimingsense_none():
    val1 = ymcell.ClibTimingSense("none")
    assert val1 is None

    
