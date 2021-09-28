### @file CXX_ClibCellLibrary.pxd
### @brief ClibCellLibrary の cython インターフェイス
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2017 Yusuke Matsunaga
### All rights reserved.

from libcpp cimport bool
from libcpp.string cimport string

ctypedef unsigned int ymuint


cdef extern from "ym/ClibCellLibrary.h" namespace "nsYm::nsClib" :

    # ClibCellLibrary の cython バージョン
    cdef cppclass ClibCellLibrary:
        @staticmethod
        ClibCellLibrary read_mislib(const string&)
        @staticmethod
        ClibCellLibrary read_liberty(const string&)
        string name()
