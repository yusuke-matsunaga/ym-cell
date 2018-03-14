
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/private_include
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================

add_subdirectory ( src/mislib )
add_subdirectory ( src/dotlib )
add_subdirectory ( gtest )


# ===================================================================
#  ソースファイルの設定
# ===================================================================
set (main_SOURCES
  src/ClibCellLibrary.cc
  src/ClibFFInfo.cc
  src/ClibLatchInfo.cc
  src/display.cc
  )

set (ci_SOURCES
  src/ci/CiBundle.cc
  src/ci/CiBus.cc
  src/ci/CiBusType.cc
  src/ci/CiCell.cc
  src/ci/CiCellList.cc
  src/ci/CiCellHash.cc
  src/ci/CiCellClass.cc
  src/ci/CiCellClassList.cc
  src/ci/CiCellGroup.cc
  src/ci/CiCellGroupList.cc
  src/ci/CiCellLibrary.cc
  src/ci/CiCellPin.cc
  src/ci/CiCellPinList.cc
  src/ci/CiCellPinHash.cc
  src/ci/CiFFCell.cc
  src/ci/CiFsmCell.cc
  src/ci/CiLatchCell.cc
  src/ci/CiLogicCell.cc
  src/ci/CiLut.cc
  src/ci/CiLutHash.cc
  src/ci/CiLutTemplate.cc
  src/ci/CiLutTemplateList.cc
  src/ci/CiPatGraph.cc
  src/ci/CiPatMgr.cc
  src/ci/CiTiming.cc
  src/ci/CiTimingList.cc
  src/ci/dump.cc
  src/ci/restore.cc
  )

set (libcomp_SOURCES
  src/libcomp/LcClass.cc
  src/libcomp/LcGroup.cc
  src/libcomp/LcPatMgr.cc
  src/libcomp/LcSignature.cc
  src/libcomp/LibComp.cc
  )


# ===================================================================
#  ターゲットの設定
# ===================================================================

ym_add_object_library ( ym_cell
  ${main_SOURCES}
  ${ci_SOURCES}
  ${libcomp_SOURCES}
  )


# ===================================================================
#  インストールターゲットの設定
# ===================================================================
