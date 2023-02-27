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


# ===================================================================
#  ソースファイルの設定
# ===================================================================
set (clib_SOURCES
  clib/ClibBundle.cc
  clib/ClibBus.cc
  clib/ClibCell.cc
  clib/ClibCellClass.cc
  clib/ClibCellGroup.cc
  clib/ClibCellLibrary.cc
  clib/ClibIOMap.cc
  clib/ClibLibraryPtr.cc
  clib/ClibLut.cc
  clib/ClibPatGraph.cc
  clib/ClibPin.cc
  clib/ClibTiming.cc
  clib/display.cc
  )

set (ci_SOURCES
  ci/CiCell.cc
  ci/CiFFCell.cc
  ci/CiFLCell.cc
  ci/CiLatchCell.cc
  ci/CiFsmCell.cc
  ci/CiCellLibrary.cc
  ci/CiPin.cc
  ci/CiLut.cc
  ci/CiLutTemplate.cc
  ci/CiPatMgr.cc
  ci/CiPatGraph.cc
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
  mislib/MislibNode.cc
  mislib/MislibParser.cc
  mislib/MislibScanner.cc
  mislib/MislibConv.cc
  )

set (dotlib_SOURCES
  dotlib/read_liberty.cc
  dotlib/CellInfo.cc
  dotlib/FFInfo.cc
  dotlib/FLInfo.cc
  dotlib/FSMInfo.cc
  dotlib/LatchInfo.cc
  dotlib/LuTemplInfo.cc
  dotlib/PinInfo.cc
  dotlib/TableInfo.cc
  dotlib/TimingInfo.cc

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
  )

set (cell_SOURCES
  ${clib_SOURCES}
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
