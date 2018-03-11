
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/private_include
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================

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

set (mislib_SOURCES
  src/mislib/read_mislib.cc
  src/mislib/MislibBop.cc
  src/mislib/MislibConst.cc
  src/mislib/MislibExpr.cc
  src/mislib/MislibGate.cc
  src/mislib/MislibMgr.cc
  src/mislib/MislibNode.cc
  src/mislib/MislibNot.cc
  src/mislib/MislibNum.cc
  src/mislib/MislibParser.cc
  src/mislib/MislibPhase.cc
  src/mislib/MislibPin.cc
  src/mislib/MislibScanner.cc
  src/mislib/MislibStr.cc
  src/mislib/MislibVarName.cc
  )

set (dotlib_SOURCES
  src/dotlib/read_liberty.cc
  src/dotlib/DotlibAttrMap.cc
  src/dotlib/DotlibMgr.cc
  src/dotlib/DotlibMgrImpl.cc

  src/dotlib/parser/AttrDic.cc
  src/dotlib/parser/DotlibParser.cc
  src/dotlib/parser/DotlibParserImpl.cc
  src/dotlib/parser/DotlibScanner.cc

  src/dotlib/handler/DotlibHandler.cc
  src/dotlib/handler/FhScanner.cc
  src/dotlib/handler/HandlerFactory.cc
  src/dotlib/handler/ComplexHandler.cc
  src/dotlib/handler/DefineHandler.cc
  src/dotlib/handler/ExprHandler.cc
  src/dotlib/handler/FuncHandler.cc
  src/dotlib/handler/GroupHandler.cc
  src/dotlib/handler/IndexHandler.cc
  src/dotlib/handler/PwComplexHandler.cc
  src/dotlib/handler/SimpleHandler.cc
  src/dotlib/handler/Str1ComplexHandler.cc
  src/dotlib/handler/TableHandler.cc
  src/dotlib/handler/UnitComplexHandler.cc
  src/dotlib/handler/ValuesHandler.cc

  src/dotlib/ast/DotlibAttr.cc
  src/dotlib/ast/DotlibCell.cc
  src/dotlib/ast/DotlibDelayModel.cc
  src/dotlib/ast/DotlibFF.cc
  src/dotlib/ast/DotlibFL.cc
  src/dotlib/ast/DotlibFloat.cc
  src/dotlib/ast/DotlibFloatVector.cc
  src/dotlib/ast/DotlibInt.cc
  src/dotlib/ast/DotlibLatch.cc
  src/dotlib/ast/DotlibLibrary.cc
  src/dotlib/ast/DotlibList.cc
  src/dotlib/ast/DotlibLut.cc
  src/dotlib/ast/DotlibNode.cc
  src/dotlib/ast/DotlibPin.cc
  src/dotlib/ast/DotlibPinDirection.cc
  src/dotlib/ast/DotlibStateTable.cc
  src/dotlib/ast/DotlibString.cc
  src/dotlib/ast/DotlibTemplate.cc
  src/dotlib/ast/DotlibTiming.cc
  src/dotlib/ast/DotlibTimingSense.cc
  src/dotlib/ast/DotlibTimingType.cc
  src/dotlib/ast/DotlibTechnology.cc
  src/dotlib/ast/DotlibUnit.cc
  src/dotlib/ast/DotlibVarType.cc
  )

set ( ym_cell_SOURCES
  ${main_SOURCES}
  ${ci_SOURCES}
  ${libcomp_SOURCES}
  ${mislib_SOURCES}
  ${dotlib_SOURCES}
  )


# ===================================================================
#  ターゲットの設定
# ===================================================================

ym_add_object_library ( ym_cell
  ${ym_cell_SOURCES}
  )


# ===================================================================
#  インストールターゲットの設定
# ===================================================================
