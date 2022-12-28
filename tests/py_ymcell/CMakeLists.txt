
# ===================================================================
# パッケージの検査
# ===================================================================


# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${Python3_INCLUDE_DIRS}
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================


# ===================================================================
#  ソースファイルの設定
# ===================================================================

set ( py_ymcell_SOURCES
  cell_module.cc
  py_ymcell.cc
  )


# ===================================================================
#  executable ターゲットの設定
# ===================================================================

add_executable( py_ymcell
  ${py_ymcell_SOURCES}
  $<TARGET_OBJECTS:py_ymcell_obj>
  $<TARGET_OBJECTS:ym_cell_obj>
  $<TARGET_OBJECTS:ym_logic_obj>
  $<TARGET_OBJECTS:ym_base_obj>
  )

target_compile_options( py_ymcell
  PRIVATE "-O3"
  )

target_compile_definitions( py_ymcell
  PRIVATE "-DNODEBUG"
  )

target_link_libraries ( py_ymcell
  ${YM_LIB_DEPENDS}
  ${Python3_LIBRARIES}
  )

add_executable( py_ymcell_d
  ${py_ymcell_SOURCES}
  $<TARGET_OBJECTS:py_ymcell_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_base_obj_d>
  )

target_compile_options( py_ymcell_d
  PRIVATE "-g"
  )

target_link_libraries ( py_ymcell_d
  ${YM_LIB_DEPENDS}
  ${Python3_LIBRARIES}
  )


# ===================================================================
# テストターゲット
# ===================================================================

add_test( py_ymcell_read_mislib_test
  py_ymcell
  ${CMAKE_CURRENT_SOURCE_DIR}/read_mislib_test.py
  ${CMAKE_CURRENT_SOURCE_DIR}/../testdata/lib2.genlib
  ${CMAKE_CURRENT_SOURCE_DIR}/../testdata/lib2.genlib.display
  )

add_test( py_ymcell_read_liberty_test
  py_ymcell
  ${CMAKE_CURRENT_SOURCE_DIR}/read_liberty_test.py
  ${CMAKE_CURRENT_SOURCE_DIR}/../testdata/HIT018.typ.snp
  ${CMAKE_CURRENT_SOURCE_DIR}/../testdata/HIT018.typ.snp.display
  )
