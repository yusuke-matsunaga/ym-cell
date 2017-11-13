### @file celllibrary.pxi
### @brief ClibCellLibrary の cython インターフェイス
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2017 Yusuke Matsunaga
### All rights reserved.

from libcpp cimport bool
from libcpp.string cimport string
from CXX_ClibCellLibrary cimport ClibCellLibrary as CXX_ClibCellLibrary
from CXX_ClibCellLibrary cimport read_mislib as c_read_mislib
from CXX_ClibCellLibrary cimport read_liberty as c_read_liberty

### @brief ClibCellLibrary クラスの Python バージョン
cdef class CellLibrary :

    # C++ レベルのオブジェクト本体
    cdef CXX_ClibCellLibrary* _this_ptr

    ### @brief 初期化
    def __cinit__(CellLibrary self) :
        self._this_ptr = CXX_ClibCellLibrary.new_obj()

    ### @brief 終了処理
    def __dealloc__(CellLibrary self) :
        if self._this_ptr != NULL :
            del self._this_ptr

    ### @brief 名前を返す．
    @property
    def name(CellLibrary self) :
        cdef string c_name = self._this_ptr.name()
        return c_name.decode('UTF-8')


### @brief mislib からの読み込み
### @param[in] filename ファイル名
def read_mislib(filename) :
    cdef string c_filename = filename.encode('UTF-8')
    cdef bool stat
    obj = CellLibrary()
    stat = c_read_mislib(c_filename, obj._this_ptr)
    if stat :
        return obj
    else :
        return None

### @brief dotlib(liberty) からの読み込み
### @param[in] filename ファイル名
def read_liberty(filename) :
    cdef string c_filename = filename.encode('UTF-8')
    cdef bool stat
    obj = CellLibrary()
    stat = c_read_liberty(c_filename, obj._this_ptr)
    if stat :
        return obj
    else :
        return None
