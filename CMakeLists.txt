
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/ym-common/include
  ${PROJECT_SOURCE_DIR}/ym-base/include
  ${PROJECT_SOURCE_DIR}/ym-logic/include
  include
  private_include
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================

add_subdirectory ( tests )


# ===================================================================
#  ソースファイルの設定
# ===================================================================
set (main_SOURCES
  c++-srcs/ClibCellLibrary.cc
  c++-srcs/ClibIOMap.cc
  c++-srcs/display.cc
  )

set (ci_SOURCES
  c++-srcs/ci/CiBundle.cc
  c++-srcs/ci/CiBus.cc
  c++-srcs/ci/CiBusType.cc
  c++-srcs/ci/CiCell.cc
  c++-srcs/ci/CiFFCell.cc
  c++-srcs/ci/CiFLCell.cc
  c++-srcs/ci/CiLatchCell.cc
  c++-srcs/ci/CiCellClass.cc
  c++-srcs/ci/CiCellGroup.cc
  c++-srcs/ci/CiCellLibrary.cc
  c++-srcs/ci/CiPin.cc
  c++-srcs/ci/CiLut.cc
  c++-srcs/ci/CiLutTemplate.cc
  c++-srcs/ci/CiPatGraph.cc
  c++-srcs/ci/CiPatMgr.cc
  c++-srcs/ci/CiTiming.cc
  c++-srcs/ci/dump.cc
  c++-srcs/ci/restore.cc
  )

set (cg_SOURCES
  c++-srcs/cgmgr/CgMgr.cc
  c++-srcs/cgmgr/CgSignature.cc
  c++-srcs/cgmgr/CgSigRep.cc
  c++-srcs/cgmgr/CgLogicSig.cc
  c++-srcs/cgmgr/CgTriLogicSig.cc
  c++-srcs/cgmgr/CgGenLogicSig.cc
  c++-srcs/cgmgr/CgFFSig.cc
  c++-srcs/cgmgr/CgLatchSig.cc
  )

set (libcomp_SOURCES
  c++-srcs/libcomp/LcPatMgr.cc
  c++-srcs/libcomp/LcSignature.cc
  c++-srcs/libcomp/LibComp.cc
  )

set (mislib_SOURCES
  c++-srcs/mislib/read_mislib.cc
  c++-srcs/mislib/MislibNode.cc
  c++-srcs/mislib/MislibParser.cc
  c++-srcs/mislib/MislibScanner.cc
  )

set (dotlib_SOURCES
  c++-srcs/dotlib/read_liberty.cc

  c++-srcs/dotlib/parser/FuncParser.cc
  c++-srcs/dotlib/parser/FuncScanner.cc
  c++-srcs/dotlib/parser/HeaderHandler.cc
  c++-srcs/dotlib/parser/Parser.cc
  c++-srcs/dotlib/parser/DotlibScanner.cc
  c++-srcs/dotlib/parser/DotlibScanner_value.cc
  c++-srcs/dotlib/parser/DotlibScanner_expr.cc

  c++-srcs/dotlib/ast/AstExpr.cc
  c++-srcs/dotlib/ast/AstValue.cc
  c++-srcs/dotlib/ast/AstElemDict.cc
  c++-srcs/dotlib/ast/AstCellInfo.cc
  c++-srcs/dotlib/ast/AstFFInfo.cc
  c++-srcs/dotlib/ast/AstFLInfo.cc
  c++-srcs/dotlib/ast/AstFSMInfo.cc
  c++-srcs/dotlib/ast/AstLatchInfo.cc
  c++-srcs/dotlib/ast/AstLuTemplInfo.cc
  c++-srcs/dotlib/ast/AstPinInfo.cc
  c++-srcs/dotlib/ast/AstTableInfo.cc
  c++-srcs/dotlib/ast/AstTimingInfo.cc
  )


# ===================================================================
#  ターゲットの設定
# ===================================================================

ym_add_object_library ( ym_cell
  ${main_SOURCES}
  ${ci_SOURCES}
  ${cg_SOURCES}
#  ${libcomp_SOURCES}
  ${mislib_SOURCES}
  ${dotlib_SOURCES}
  )


# ===================================================================
#  インストールターゲットの設定
# ===================================================================
