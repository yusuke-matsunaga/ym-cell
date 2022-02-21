
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${GTEST_INCLUDE_DIR}
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================

add_subdirectory( programs )

# ===================================================================
#  ソースファイルの設定
# ===================================================================



# ===================================================================
#  テスト用のターゲットの設定
# ===================================================================

# テストデータのパス
set ( TESTDATA_DIR
  ${PROJECT_SOURCE_DIR}/ym-cell/tests/testdata
  )


# ===================================================================
#  ClibArea_test
# ===================================================================
ym_add_gtest ( cell_ClibArea_test
  # 実は ClibArea.h のみに依存している．
  cell_library/ClibAreaTest.cc
  )


# ===================================================================
#  ClibCapacitance_test
# ===================================================================
ym_add_gtest ( cell_ClibCapacitance_test
  # 実は ClibCapacitance.h のみに依存している．
  cell_library/ClibCapacitanceTest.cc
  )


# ===================================================================
#  ClibResistance_test
# ===================================================================
ym_add_gtest ( cell_ClibResistance_test
  # 実は ClibResistance.h のみに依存している．
  cell_library/ClibResistanceTest.cc
  )


# ===================================================================
#  ClibTime_test
# ===================================================================
ym_add_gtest ( cell_ClibTime_test
  # 実は ClibTime.h のみに依存している．
  cell_library/ClibTimeTest.cc
  )


# ===================================================================
#  ClibCellLibrary_test
# ===================================================================
ym_add_gtest ( cell_ClibCellLibrary_test
  cell_library/ClibCellLibraryTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  DEFINITIONS
  "-DDATA_DIR=\"${TESTDATA_DIR}\""
  )


# ===================================================================
#  MislibScanner_test
# ===================================================================
ym_add_gtest ( cell_MislibScanner_test
  mislib/MislibScannerTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  DEFINITIONS
  "-DDATA_DIR=\"${TESTDATA_DIR}\""
  )

target_include_directories( cell_MislibScanner_test
  PRIVATE
  ../c++-srcs/mislib
  )


# ===================================================================
#  MislibParser_test
# ===================================================================
ym_add_gtest ( cell_MislibParser_test
  mislib/MislibParserTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  DEFINITIONS
  "-DDATA_DIR=\"${TESTDATA_DIR}\""
  )

target_include_directories( cell_MislibParser_test
  PRIVATE
  ../c++-srcs/mislib
  )


# ===================================================================
#  DotlibScanner_test
# ===================================================================
ym_add_gtest ( cell_DotlibScanner_test
  dotlib/ScannerTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )

target_include_directories( cell_DotlibScanner_test
  PRIVATE
  ../private_include/dotlib
  )


# ===================================================================
#  FuncScanner_test
# ===================================================================
ym_add_gtest ( cell_FuncScanner_test
  dotlib/FuncScannerTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )

target_include_directories( cell_FuncScanner_test
  PRIVATE
  ../c++-srcs/dotlib/parser
  )


# ===================================================================
#  DotlibParser_test
# ===================================================================
ym_add_gtest ( cell_DotlibParser_test
  dotlib/ParserTest_simple.cc
  dotlib/ParserTest_complex.cc
  dotlib/ParserTest_group.cc
  dotlib/ParserTest_library_simple.cc
  dotlib/ParserTest_library_default.cc
  dotlib/ParserTest_library_k_process.cc
  dotlib/ParserTest_library_k_temp.cc
  dotlib/ParserTest_library_k_volt.cc
  dotlib/ParserTest_library_complex.cc
  dotlib/ParserTest_library_group.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )

target_include_directories( cell_DotlibParser_test
  PRIVATE
  ../private_include/dotlib
  ../c++-srcs/dotlib/parser
  )


# ===================================================================
#  DotlibParser_test2
# ===================================================================
ym_add_gtest ( cell_DotlibParser_test2
  dotlib/ParserTest_ast.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  DEFINITIONS
  "-DDATA_DIR=\"${TESTDATA_DIR}\""
  )

target_include_directories( cell_DotlibParser_test2
  PRIVATE
  ../private_include/dotlib
  ../c++-srcs/dotlib/parser
  )


# ===================================================================
#  インストールターゲットの設定
# ===================================================================
