
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

  src/dotlib/parser/AttrDic.cc
  src/dotlib/parser/DotlibParser.cc
  src/dotlib/parser/DotlibScanner.cc

  src/dotlib/handler/DotlibHandler.cc
  src/dotlib/handler/CellHandler.cc
  src/dotlib/handler/CellInternalPower.cc
  src/dotlib/handler/CGHandler.cc
  src/dotlib/handler/ComplexHandler.cc
  src/dotlib/handler/DefineHandler.cc
  src/dotlib/handler/DelayModelHandler.cc
  src/dotlib/handler/ExprHandler.cc
  src/dotlib/handler/FuncHandler.cc
  src/dotlib/handler/FuncParser.cc
  src/dotlib/handler/FuncScanner.cc
  src/dotlib/handler/GroupHandler.cc
  src/dotlib/handler/LibraryHandler.cc
  src/dotlib/handler/IndexHandler.cc
  src/dotlib/handler/InputVoltageHandler.cc
  src/dotlib/handler/InternalPowerHandler.cc
  src/dotlib/handler/OutputVoltageHandler.cc
  src/dotlib/handler/PinHandler.cc
  src/dotlib/handler/PinDirectionHandler.cc
  src/dotlib/handler/PowerHandler.cc
  src/dotlib/handler/PieceWiseHandler.cc
  src/dotlib/handler/SimpleHandler.cc
  src/dotlib/handler/StrBaseHandler.cc
  src/dotlib/handler/TableHandler.cc
  src/dotlib/handler/TechnologyHandler.cc
  src/dotlib/handler/TemplateHandler.cc
  src/dotlib/handler/TimingHandler.cc
  src/dotlib/handler/TimingSenseHandler.cc
  src/dotlib/handler/TimingTypeHandler.cc
  src/dotlib/handler/UnitHandler.cc
  src/dotlib/handler/ValuesHandler.cc
  src/dotlib/handler/VarTypeHandler.cc

  src/dotlib/ast/AstAttr.cc
  src/dotlib/ast/AstCell.cc
  src/dotlib/ast/AstDelayModel.cc
  src/dotlib/ast/AstExpr.cc
  src/dotlib/ast/AstFF.cc
  src/dotlib/ast/AstFL.cc
  src/dotlib/ast/AstFloat.cc
  src/dotlib/ast/AstFloatVector.cc
  src/dotlib/ast/AstInputVoltage.cc
  src/dotlib/ast/AstInt.cc
  src/dotlib/ast/AstLatch.cc
  src/dotlib/ast/AstLibrary.cc
  src/dotlib/ast/AstLut.cc
  src/dotlib/ast/AstMgr.cc
  src/dotlib/ast/AstNode.cc
  src/dotlib/ast/AstOutputVoltage.cc
  src/dotlib/ast/AstPieceWise.cc
  src/dotlib/ast/AstPin.cc
  src/dotlib/ast/AstPinDirection.cc
  src/dotlib/ast/AstStateTable.cc
  src/dotlib/ast/AstString.cc
  src/dotlib/ast/AstTemplate.cc
  src/dotlib/ast/AstTiming.cc
  src/dotlib/ast/AstTimingSense.cc
  src/dotlib/ast/AstTimingType.cc
  src/dotlib/ast/AstTechnology.cc
  src/dotlib/ast/AstUnit.cc
  src/dotlib/ast/AstVarType.cc
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
