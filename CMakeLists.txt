
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/ym-common/include
  ${PROJECT_SOURCE_DIR}/ym-base/include
  ${PROJECT_SOURCE_DIR}/ym-logic/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/private_include
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================

add_subdirectory ( c++-test/cell_library )
add_subdirectory ( c++-test/dotlib )
add_subdirectory ( c++-test/libcomp )


# ===================================================================
#  ソースファイルの設定
# ===================================================================
set (main_SOURCES
  c++-src/ClibCellLibrary.cc
  c++-src/ClibFFInfo.cc
  c++-src/ClibLatchInfo.cc
  c++-src/display.cc
  )

set (ci_SOURCES
  c++-src/ci/CiBundle.cc
  c++-src/ci/CiBus.cc
  c++-src/ci/CiBusType.cc
  c++-src/ci/CiCell.cc
  c++-src/ci/CiCellClass.cc
  c++-src/ci/CiCellGroup.cc
  c++-src/ci/CiCellLibrary.cc
  c++-src/ci/CiCellPin.cc
  c++-src/ci/CiCellPinHash.cc
  c++-src/ci/CiFFCell.cc
  c++-src/ci/CiFsmCell.cc
  c++-src/ci/CiLatchCell.cc
  c++-src/ci/CiLogicCell.cc
  c++-src/ci/CiLut.cc
  c++-src/ci/CiLutTemplate.cc
  c++-src/ci/CiPatGraph.cc
  c++-src/ci/CiPatMgr.cc
  c++-src/ci/CiTiming.cc
  c++-src/ci/dump.cc
  c++-src/ci/restore.cc
  )

set (libcomp_SOURCES
  c++-src/libcomp/LcClass.cc
  c++-src/libcomp/LcGroup.cc
  c++-src/libcomp/LcPatMgr.cc
  c++-src/libcomp/LcSignature.cc
  c++-src/libcomp/LibComp.cc
  )

set (mislib_SOURCES
  c++-src/mislib/read_mislib.cc
  c++-src/mislib/MislibBop.cc
  c++-src/mislib/MislibConst.cc
  c++-src/mislib/MislibExpr.cc
  c++-src/mislib/MislibGate.cc
  c++-src/mislib/MislibNode.cc
  c++-src/mislib/MislibNot.cc
  c++-src/mislib/MislibNum.cc
  c++-src/mislib/MislibParser.cc
  c++-src/mislib/MislibPhase.cc
  c++-src/mislib/MislibPin.cc
  c++-src/mislib/MislibScanner.cc
  c++-src/mislib/MislibStr.cc
  c++-src/mislib/MislibVarName.cc
  )

set (dotlib_SOURCES
  c++-src/dotlib/read_liberty.cc

  c++-src/dotlib/parser/AttrDic.cc
  c++-src/dotlib/parser/AttrType.cc
  c++-src/dotlib/parser/FuncParser.cc
  c++-src/dotlib/parser/FuncScanner.cc
  c++-src/dotlib/parser/HeaderHandler.cc
  c++-src/dotlib/parser/Parser.cc
  c++-src/dotlib/parser/Parser_complex.cc
  c++-src/dotlib/parser/Parser_group.cc
  c++-src/dotlib/parser/Parser_simple.cc
  c++-src/dotlib/parser/Scanner.cc
  c++-src/dotlib/parser/Scanner_value.cc
  c++-src/dotlib/parser/Scanner_expr.cc

  c++-src/dotlib/ast/AstAttr.cc
  c++-src/dotlib/ast/AstExpr.cc
  c++-src/dotlib/ast/AstValue.cc
  )


# ===================================================================
#  ターゲットの設定
# ===================================================================

ym_add_object_library ( ym_cell
  ${main_SOURCES}
  ${ci_SOURCES}
  ${libcomp_SOURCES}
  ${mislib_SOURCES}
  ${dotlib_SOURCES}
  )


# ===================================================================
#  インストールターゲットの設定
# ===================================================================
