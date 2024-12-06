#! /usr/bin/env python3

""" ClibDelayModelのテストスクリプト

:file: py_ClibDelayModel_test.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2024 Yusuke Matsunaga, All rights reserved.
"""

import pytest
import ymcell

def test_clibdelaymodel_generic_cmos():
    val1 = ymcell.ClibDelayModel("generic_cmos")
    assert val1 == ymcell.ClibDelayModel.generic_cmos
    assert val1.__repr__() == "generic_cmos"

def test_clibdelaymodel_table_lookup():
    val1 = ymcell.ClibDelayModel("table_lookup")
    assert val1 == ymcell.ClibDelayModel.table_lookup
    assert val1.__repr__() == "table_lookup"

def test_clibdelaymodel_piecewise_cmos():
    val1 = ymcell.ClibDelayModel("piecewise_cmos")
    assert val1 == ymcell.ClibDelayModel.piecewise_cmos
    assert val1.__repr__() == "piecewise_cmos"

def test_clibdelaymodel_cmos2():
    val1 = ymcell.ClibDelayModel("cmos2")
    assert val1 == ymcell.ClibDelayModel.cmos2
    assert val1.__repr__() == "cmos2"

def test_clibdelaymodel_dcm():
    val1 = ymcell.ClibDelayModel("dcm")
    assert val1 == ymcell.ClibDelayModel.dcm
    assert val1.__repr__() == "dcm"

def test_clibdelaymodel_polynomial():
    val1 = ymcell.ClibDelayModel("polynomial")
    assert val1 == ymcell.ClibDelayModel.polynomial
    assert val1.__repr__() == "polynomial"

def test_clibdelaymodel_none():
    val1 = ymcell.ClibDelayModel("none")
    assert val1 is None

    
