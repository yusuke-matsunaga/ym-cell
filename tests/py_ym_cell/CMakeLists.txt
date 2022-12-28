
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

set ( py_ym_cell_SOURCES
  cell_module.cc
  py_ym_cell.cc
  )


# ===================================================================
#  executable ターゲットの設定
# ===================================================================

add_executable( py_ym_cell
  ${py_ym_cell_SOURCES}
  $<TARGET_OBJECTS:py_ym_cell_obj>
  $<TARGET_OBJECTS:ym_cell_obj>
  $<TARGET_OBJECTS:ym_logic_obj>
  $<TARGET_OBJECTS:ym_base_obj>
  )

target_compile_options( py_ym_cell
  PRIVATE "-O3"
  )

target_compile_definitions( py_ym_cell
  PRIVATE "-DNODEBUG"
  )

target_link_libraries ( py_ym_cell
  ${YM_LIB_DEPENDS}
  ${Python3_LIBRARIES}
  )

add_executable( py_ym_cell_d
  ${py_ym_cell_SOURCES}
  $<TARGET_OBJECTS:py_ym_cell_obj_d>
  ${YM_SUBMODULE_OBJ_D_LIST}
  )

target_compile_options( py_ym_cell_d
  PRIVATE "-g"
  )

target_link_libraries ( py_ym_cell_d
  ${YM_LIB_DEPENDS}
  ${Python3_LIBRARIES}
  )


# ===================================================================
# テストターゲット
# ===================================================================

add_test( py_ym_cell_read_mislib_test
  py_ym_cell
  ${CMAKE_CURRENT_SOURCE_DIR}/read_mislib_test.py
  ${CMAKE_CURRENT_SOURCE_DIR}/../testdata/lib2.genlib
  ${CMAKE_CURRENT_SOURCE_DIR}/../testdata/lib2.genlib.display
  )

add_test( py_ym_cell_read_liberty_test
  py_ym_cell
  ${CMAKE_CURRENT_SOURCE_DIR}/read_liberty_test.py
  ${CMAKE_CURRENT_SOURCE_DIR}/../testdata/HIT018.typ.snp
  ${CMAKE_CURRENT_SOURCE_DIR}/../testdata/HIT018.typ.snp.display
  )
