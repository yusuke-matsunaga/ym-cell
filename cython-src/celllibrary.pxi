### @file celllibrary.pxi
### @brief ClibCellLibrary の cython インターフェイス
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2017 Yusuke Matsunaga
### All rights reserved.

from libcpp cimport bool
from libcpp.string cimport string
from CXX_ClibCellLibrary cimport ClibCellLibrary as CXX_ClibCellLibrary


### @brief ClibCellLibrary クラスの Python バージョン
cdef class CellLibrary :

    # C++ レベルのオブジェクト本体
    cdef CXX_ClibCellLibrary _this

    ### @brief mislib からの読み込み
    ### @param[in] filename ファイル名
    def read_mislib(CellLibrary self, filename) :
        cdef string c_filename = filename.encode('UTF-8')
        cdef bool stat = self._this.read_mislib(c_filename)
        return stat

    ### @brief dotlib(liberty) からの読み込み
    ### @param[in] filename ファイル名
    def read_liberty(CellLibrary self, filename) :
        cdef string c_filename = filename.encode('UTF-8')
        cdef bool stat = self._this.read_liberty(c_filename)
        return stat

    ### @brief 名前を返す．
    @property
    def name(CellLibrary self) :
        cdef string c_name = self._this.name()
        return c_name.decode('UTF-8')
