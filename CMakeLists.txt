
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${PROJECT_SOURCE_DIR}/ym-common/include
  ${PROJECT_SOURCE_DIR}/ym-base/include
  ${PROJECT_SOURCE_DIR}/ym-logic/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/private_include
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================

add_subdirectory ( c++-test/libcomp )
add_subdirectory ( c++-test/cell_library )


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
  c++-src/ci/CiCellList.cc
  c++-src/ci/CiCellHash.cc
  c++-src/ci/CiCellClass.cc
  c++-src/ci/CiCellClassList.cc
  c++-src/ci/CiCellGroup.cc
  c++-src/ci/CiCellGroupList.cc
  c++-src/ci/CiCellLibrary.cc
  c++-src/ci/CiCellPin.cc
  c++-src/ci/CiCellPinList.cc
  c++-src/ci/CiCellPinHash.cc
  c++-src/ci/CiFFCell.cc
  c++-src/ci/CiFsmCell.cc
  c++-src/ci/CiLatchCell.cc
  c++-src/ci/CiLogicCell.cc
  c++-src/ci/CiLut.cc
  c++-src/ci/CiLutHash.cc
  c++-src/ci/CiLutTemplate.cc
  c++-src/ci/CiLutTemplateList.cc
  c++-src/ci/CiPatGraph.cc
  c++-src/ci/CiPatMgr.cc
  c++-src/ci/CiTiming.cc
  c++-src/ci/CiTimingList.cc
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
  c++-src/mislib/MislibMgr.cc
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
  c++-src/dotlib/parser/DotlibParser.cc
  c++-src/dotlib/parser/DotlibParser_read.cc
  c++-src/dotlib/parser/DotlibParser_simple.cc
  c++-src/dotlib/parser/DotlibParser_complex.cc
  c++-src/dotlib/parser/DotlibParser_group.cc
  c++-src/dotlib/parser/DotlibScanner.cc
  c++-src/dotlib/parser/FuncParser.cc
  c++-src/dotlib/parser/FuncScanner.cc

  c++-src/dotlib/handler/DotlibHandler.cc
  c++-src/dotlib/handler/header/ElemHandler.cc
  c++-src/dotlib/handler/header/EmptyHandler.cc
  c++-src/dotlib/handler/header/FloatFloatHandler.cc
  c++-src/dotlib/handler/header/FloatStrHandler.cc
  c++-src/dotlib/handler/header/FloatVectorHandler.cc
  c++-src/dotlib/handler/header/FloatVectorListHandler.cc
  c++-src/dotlib/handler/header/HeaderHandler.cc
  c++-src/dotlib/handler/header/IntFloatHandler.cc
  c++-src/dotlib/handler/header/IntFloatVectorHandler.cc
  c++-src/dotlib/handler/header/IntVectorHandler.cc
  c++-src/dotlib/handler/header/StrHandler.cc
  c++-src/dotlib/handler/header/StrIntHandler.cc
  c++-src/dotlib/handler/header/StrStrHandler.cc
  c++-src/dotlib/handler/header/StrStrIntHandler.cc
  c++-src/dotlib/handler/header/StrStrStrHandler.cc
  c++-src/dotlib/handler/header/StrFloatHandler.cc
  c++-src/dotlib/handler/header/StrListHandler.cc

  c++-src/dotlib/handler/group/GroupHandler.cc

  #c++-src/dotlib/handler/group/InternalPowerHandler.cc
  #c++-src/dotlib/handler/group/TimingHandler.cc

  #c++-src/dotlib/handler/group/CellHandler.cc
  #c++-src/dotlib/handler/group/CellDegradationHandler.cc
  #c++-src/dotlib/handler/CellInternalPower.cc
  #c++-src/dotlib/handler/group/DomainHandler.cc
  #c++-src/dotlib/handler/group/InputVoltageHandler.cc
  #c++-src/dotlib/handler/group/LibraryHandler.cc
  #c++-src/dotlib/handler/group/OutputVoltageHandler.cc
  #c++-src/dotlib/handler/group/PinHandler.cc
  #c++-src/dotlib/handler/group/TableHandler.cc
  #c++-src/dotlib/handler/group/TemplateHandler.cc
  #c++-src/dotlib/handler/group/FFHandler.cc
  #c++-src/dotlib/handler/group/LatchHandler.cc
  #c++-src/dotlib/handler/group/FFBankHandler.cc
  #c++-src/dotlib/handler/group/LatchBankHandler.cc

  #c++-src/dotlib/handler/DefineHandler.cc

  c++-src/dotlib/ast/AstBool.cc
  c++-src/dotlib/ast/AstCPType.cc
  c++-src/dotlib/ast/AstDelayModel.cc
  c++-src/dotlib/ast/AstDirection.cc
  c++-src/dotlib/ast/AstExpr.cc
  c++-src/dotlib/ast/AstFloat.cc
  c++-src/dotlib/ast/AstFloat2.cc
  c++-src/dotlib/ast/AstFloatStr.cc
  c++-src/dotlib/ast/AstFloatVector.cc
  c++-src/dotlib/ast/AstInt.cc
  c++-src/dotlib/ast/AstIntFloat.cc
  c++-src/dotlib/ast/AstIntFloatVector.cc
  c++-src/dotlib/ast/AstIntVector.cc
  c++-src/dotlib/ast/AstMgr.cc
  c++-src/dotlib/ast/AstNode.cc
  c++-src/dotlib/ast/AstStr2.cc
  c++-src/dotlib/ast/AstStr3.cc
  c++-src/dotlib/ast/AstStrFloat.cc
  c++-src/dotlib/ast/AstStrInt.cc
  c++-src/dotlib/ast/AstString.cc
  c++-src/dotlib/ast/AstStrList.cc
  c++-src/dotlib/ast/AstTimingSense.cc
  c++-src/dotlib/ast/AstTimingType.cc
  c++-src/dotlib/ast/AstTechnology.cc
  c++-src/dotlib/ast/AstVarType.cc

  #c++-src/dotlib/ast/AstCell.cc
  #c++-src/dotlib/ast/AstCellDegradation.cc
  #c++-src/dotlib/ast/AstDomain.cc
  #c++-src/dotlib/ast/AstFF.cc
  #c++-src/dotlib/ast/AstFFBank.cc
  #c++-src/dotlib/ast/AstInputVoltage.cc
  #c++-src/dotlib/ast/AstLatch.cc
  #c++-src/dotlib/ast/AstLatchBank.cc
  #c++-src/dotlib/ast/AstLibrary.cc
  #c++-src/dotlib/ast/AstLut.cc
  #c++-src/dotlib/ast/AstOutputVoltage.cc
  #c++-src/dotlib/ast/AstPin.cc
  #c++-src/dotlib/ast/AstStateTable.cc
  #c++-src/dotlib/ast/AstTemplate.cc
  #c++-src/dotlib/ast/AstTiming.cc
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
