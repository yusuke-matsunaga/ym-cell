
# ===================================================================
# インクルードパスの設定
# ===================================================================


# ===================================================================
# サブディレクトリの設定
# ===================================================================


# ===================================================================
#  ソースファイルの設定
# ===================================================================



# ===================================================================
#  テスト用のターゲットの設定
# ===================================================================

# ===================================================================
#  ClibArea_test
# ===================================================================
ym_add_gtest ( cell_ClibArea_test
  # 実は ClibArea.h のみに依存している．
  clib/ClibAreaTest.cc
  )


# ===================================================================
#  ClibCapacitance_test
# ===================================================================
ym_add_gtest ( cell_ClibCapacitance_test
  # 実は ClibCapacitance.h のみに依存している．
  clib/ClibCapacitanceTest.cc
  )


# ===================================================================
#  ClibResistance_test
# ===================================================================
ym_add_gtest ( cell_ClibResistance_test
  # 実は ClibResistance.h のみに依存している．
  clib/ClibResistanceTest.cc
  )

# ===================================================================
#  ClibSeqAttr_test
# ===================================================================
ym_add_gtest ( cell_ClibSeqAttr_test
  clib/ClibSeqAttrTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )


# ===================================================================
#  ClibTime_test
# ===================================================================
ym_add_gtest ( cell_ClibTime_test
  # 実は ClibTime.h のみに依存している．
  clib/ClibTimeTest.cc
  )


# ===================================================================
#  ClibCell_test
# ===================================================================
ym_add_gtest ( cell_ClibCell_test
  clib/ClibCellTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  DEFINITIONS
  "-DDATA_DIR=\"${TESTDATA_DIR}\""
  )


# ===================================================================
#  ClibCellLibrary_test
# ===================================================================
ym_add_gtest ( cell_ClibCellLibrary_test
  clib/ClibCellLibraryTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  DEFINITIONS
  "-DDATA_DIR=\"${TESTDATA_DIR}\""
  )


# ===================================================================
#  ClibIOMap_test
# ===================================================================
ym_add_gtest ( cell_ClibIOMap_test
  clib/ClibIOMapTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
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
  ../../c++-srcs/mislib
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
  ../../c++-srcs/mislib
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
  ../../c++-srcs/dotlib/parser
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
  ../../c++-srcs/dotlib/parser
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
  ../../c++-srcs/dotlib/parser
  )


# ===================================================================
#  CgLogicSig_test
# ===================================================================
ym_add_gtest ( cell_CgLogicSig_test
  cgmgr/CgLogicSig_test.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )

target_include_directories( cell_CgLogicSig_test
  PRIVATE
  ../../c++-srcs/cgmgr
  )

add_executable( foo_test
  cgmgr/foo.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )

target_compile_options ( foo_test
  PRIVATE "-g" "-fPIC"
  )

target_link_libraries( foo_test
  ${YM_LIB_DEPENDS}
  pthread
  )

target_include_directories( foo_test
  PRIVATE
  ../../c++-srcs/cgmgr
  )


# ===================================================================
#  CgGenLogicSig_test
# ===================================================================
ym_add_gtest ( cell_CgGenLogicSig_test
  cgmgr/CgGenLogicSig_test.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )

target_include_directories( cell_CgGenLogicSig_test
  PRIVATE
  ../../c++-srcs/cgmgr
  )


# ===================================================================
#  CgFFSig_test
# ===================================================================
ym_add_gtest ( cell_CgFFSig_test
  cgmgr/CgFFSig_test.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  )

target_include_directories( cell_CgFFSig_test
  PRIVATE
  ../../c++-srcs/cgmgr
  )

# ===================================================================
#  インストールターゲットの設定
# ===================================================================
