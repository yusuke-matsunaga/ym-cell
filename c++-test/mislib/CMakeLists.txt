
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ../../c++-src/mislib
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================


# ===================================================================
#  ソースファイルの設定
# ===================================================================



# ===================================================================
#  テスト用のターゲットの設定
# ===================================================================

ym_add_gtest ( cell_MislibScanner_test
  MislibScannerTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  DEFINITIONS
  "-DDATA_DIR=\"${PROJECT_SOURCE_DIR}/ym-cell/testdata\""
  )

ym_add_gtest ( cell_MislibParser_test
  MislibParserTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  DEFINITIONS
  "-DDATA_DIR=\"${PROJECT_SOURCE_DIR}/ym-cell/testdata\""
  )
