# ===================================================================
# CMAKE のおまじない
# ===================================================================


# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  )


# ===================================================================
#  マクロの定義
# ===================================================================


# ===================================================================
# サブディレクトリの設定
# ===================================================================

# テストデータのパス
set ( TESTDATA_DIR
  ${PROJECT_SOURCE_DIR}/ym-cell/tests/testdata
  )


add_executable ( read_mislib_test
  read_mislib_test.cc
  $<TARGET_OBJECTS:ym_cell_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_base_obj_d>
  )

target_link_libraries ( read_mislib_test
  ${YM_LIB_DEPENDS}
  )

target_compile_definitions ( read_mislib_test
  PRIVATE "-DTESTFILE=\"${TESTDATA_DIR}/lib2.genlib\""
  )


add_executable ( read_liberty_test
  read_liberty_test.cc
  $<TARGET_OBJECTS:ym_cell_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_base_obj_d>
  )

target_link_libraries ( read_liberty_test
  ${YM_LIB_DEPENDS}
  )

target_compile_definitions ( read_liberty_test
  PRIVATE "-DTESTFILE=\"${TESTDATA_DIR}/HIT018.typ.snp\""
  )