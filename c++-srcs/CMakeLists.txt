# ===================================================================
# パッケージの検査
# ===================================================================


# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================

add_subdirectory ( py_ym_cell )


# ===================================================================
#  ソースファイルの設定
# ===================================================================
set (main_SOURCES
  ClibCellLibrary.cc
  ClibIOMap.cc
  display.cc
  )

set (ci_SOURCES
  ci/CiBundle.cc
  ci/CiBus.cc
  ci/CiBusType.cc
  ci/CiCell.cc
  ci/CiFFCell.cc
  ci/CiFLCell.cc
  ci/CiLatchCell.cc
  ci/CiCellClass.cc
  ci/CiCellGroup.cc
  ci/CiCellLibrary.cc
  ci/CiPin.cc
  ci/CiLut.cc
  ci/CiLutTemplate.cc
  ci/CiPatGraph.cc
  ci/CiPatMgr.cc
  ci/CiTiming.cc
  ci/dump.cc
  ci/restore.cc
  )

set (cg_SOURCES
  cgmgr/CgMgr.cc
  cgmgr/CgSignature.cc
  cgmgr/CgSigRep.cc
  cgmgr/PatMgr.cc
  )

set (mislib_SOURCES
  mislib/read_mislib.cc
  mislib/MislibNode.cc
  mislib/MislibParser.cc
  mislib/MislibScanner.cc
  )

set (dotlib_SOURCES
  dotlib/read_liberty.cc

  dotlib/parser/FuncParser.cc
  dotlib/parser/FuncScanner.cc
  dotlib/parser/HeaderHandler.cc
  dotlib/parser/Parser.cc
  dotlib/parser/DotlibScanner.cc
  dotlib/parser/DotlibScanner_value.cc
  dotlib/parser/DotlibScanner_expr.cc

  dotlib/ast/AstExpr.cc
  dotlib/ast/AstValue.cc
  dotlib/ast/AstElemDict.cc
  dotlib/ast/AstCellInfo.cc
  dotlib/ast/AstFFInfo.cc
  dotlib/ast/AstFLInfo.cc
  dotlib/ast/AstFSMInfo.cc
  dotlib/ast/AstLatchInfo.cc
  dotlib/ast/AstLuTemplInfo.cc
  dotlib/ast/AstPinInfo.cc
  dotlib/ast/AstTableInfo.cc
  dotlib/ast/AstTimingInfo.cc
  )

set (cell_SOURCES
  ${main_SOURCES}
  ${ci_SOURCES}
  ${cg_SOURCES}
  ${patmgr_SOURCES}
  ${mislib_SOURCES}
  ${dotlib_SOURCES}
  )

# ===================================================================
#  ターゲットの設定
# ===================================================================

ym_add_object_library ( ym_cell
  ${cell_SOURCES}
  )


# ===================================================================
#  インストールターゲットの設定
# ===================================================================
