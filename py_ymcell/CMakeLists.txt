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


# ===================================================================
#  ターゲットの設定
# ===================================================================

ym_add_object_library ( py_ymcell
  ymcell_module.cc
  PyClibTechnology.cc
  PyClibDelayModel.cc
  PyClibDirection.cc
  PyClibTimingSense.cc
  PyClibTimingType.cc
  PyClibCellType.cc
  PyClibCPV.cc
  PyClibVarType.cc
  PyClibCellLibrary.cc
  PyClibCell.cc
  PyClibPin.cc
  PyClibTiming.cc
  )

add_library ( py_ymcelllib
  SHARED
  $<TARGET_OBJECTS:py_ymcell_obj>
  $<TARGET_OBJECTS:py_ymlogic_obj>
  $<TARGET_OBJECTS:ym_cell_obj>
  $<TARGET_OBJECTS:ym_logic_obj>
  $<TARGET_OBJECTS:ym_base_obj>
  )

set_target_properties( py_ymcelllib
  PROPERTIES
  PREFIX ""
  OUTPUT_NAME "ymcell"
  )

target_link_libraries( py_ymcelllib
  ${YM_LIB_DEPENDS}
  ${Python3_LIBRARIES}
  )

# ===================================================================
#  インストールターゲットの設定
# ===================================================================
