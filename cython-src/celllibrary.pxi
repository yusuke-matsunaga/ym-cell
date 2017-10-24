### @file celllibrary.pxi
### @brief ClibCellLibrary の cython インターフェイス
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2017 Yusuke Matsunaga
### All rights reserved.

from libcpp cimpot bool
from CXX_ClibCellLibrary cimport ClibCellLibrary as CXX_ClibCellLibrary
from CXX_ClibCellLibrary cimport read_mislib

### @brief ClibCellLibrary クラスの Python バージョン
cdef class CellLibrary :

    # C++ レベルのオブジェクト本体
    cdef CXX_ClibCellLibrary* _this_ptr

    ### @brief 初期化
    def __cinit__(CellLibrary self) :
        self._this_ptr = CXX_ClibCellLibrary::new_obj()

    ### @brief 終了処理
    def __dealloc__(CellLibrary self) :
        if self._this_ptr != NULL :
            del self._this_ptr

    ### @brief mislib からの読み込み
    ### @param[in] filename ファイル名
    @staticmethod
    def read_mislib(filename) :
        cdef string c_filename = filename.encode('UTF-8')
        cdef bool stat
        obj = CellLibrary()
        stat = read_mislib(c_filename, obj._this_ptr)
        if stat :
            return obj
        else :
            return None
