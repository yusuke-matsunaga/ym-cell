
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${GTEST_INCLUDE_DIR}
  ../../private_include/dotlib
  ../../c++-src/dotlib/parser
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

ym_add_gtest ( cell_DotlibScanner_test
  ScannerTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )

ym_add_gtest ( cell_FuncScanner_test
  FuncScannerTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )

ym_add_gtest ( cell_DotlibParser_test
  ParserTest_simple.cc
  ParserTest_complex.cc
  ParserTest_group.cc
  ParserTest_library_simple.cc
  ParserTest_library_default.cc
  ParserTest_library_k_process.cc
  ParserTest_library_k_temp.cc
  ParserTest_library_k_volt.cc
  ParserTest_library_complex.cc
  ParserTest_library_group.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )
