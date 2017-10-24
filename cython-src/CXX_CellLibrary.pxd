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
    cdef cppclass ClibCellLibrary :

        @staticmethod
        ClibCellLibrary* new_obj()
        string name()

    bool read_mislib(const string&, ClibCellLibrary*)
    bool read_liberty(const string&, ClibCellLibrary*)
