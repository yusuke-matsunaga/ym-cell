
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
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

ym_add_gtest ( cell_ClibArea_test
  # 実は ClibArea.h のみに依存している．
  ClibAreaTest.cc
  )

ym_add_gtest ( cell_ClibCapacitance_test
  # 実は ClibCapacitance.h のみに依存している．
  ClibCapacitanceTest.cc
  )

ym_add_gtest ( cell_ClibResistance_test
  # 実は ClibResistance.h のみに依存している．
  ClibResistanceTest.cc
  )

ym_add_gtest ( cell_ClibTime_test
  # 実は ClibTime.h のみに依存している．
  ClibTimeTest.cc
  )

ym_add_gtest ( cell_ClibCellLibrary_test
  ClibCellLibraryTest.cc
  $<TARGET_OBJECTS:ym_base_obj_d>
  $<TARGET_OBJECTS:ym_logic_obj_d>
  $<TARGET_OBJECTS:ym_cell_obj_d>
  DEFINITIONS
  "-DDATA_DIR=\"${PROJECT_SOURCE_DIR}/ym-cell/testdata\""
  )
