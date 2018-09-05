
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

  src/dotlib/handler/simple/SimpleHandler.cc
  src/dotlib/handler/simple/IntHandler.cc
  src/dotlib/handler/simple/FloatHandler.cc
  src/dotlib/handler/simple/StrBaseHandler.cc
  src/dotlib/handler/simple/BoolHandler.cc
  src/dotlib/handler/simple/DelayModelHandler.cc
  src/dotlib/handler/simple/PinDirectionHandler.cc
  src/dotlib/handler/simple/StringHandler.cc
  src/dotlib/handler/simple/TechnologyHandler.cc
  src/dotlib/handler/simple/TimingSenseHandler.cc
  src/dotlib/handler/simple/TimingTypeHandler.cc
  src/dotlib/handler/simple/VarTypeHandler.cc
  src/dotlib/handler/simple/ExprHandler.cc
  src/dotlib/handler/simple/FuncParser.cc
  src/dotlib/handler/simple/FuncScanner.cc
  src/dotlib/handler/simple/FuncHandler.cc

  src/dotlib/handler/complex/ComplexHandler.cc
  src/dotlib/handler/complex/IndexHandler.cc
  src/dotlib/handler/complex/PieceWiseHandler.cc
  src/dotlib/handler/complex/UnitHandler.cc
  src/dotlib/handler/complex/ValuesHandler.cc

  src/dotlib/handler/group/GroupHandler.cc
  src/dotlib/handler/group/EmptyGroupHandler.cc
  src/dotlib/handler/group/Str1GroupHandler.cc
  src/dotlib/handler/group/Str2GroupHandler.cc
  src/dotlib/handler/group/Str2IntGroupHandler.cc

  # EmptyGroupHandler
  src/dotlib/handler/group/InternalPowerHandler.cc
  src/dotlib/handler/group/TimingHandler.cc

  # Str1GroupHandler
  src/dotlib/handler/group/CellHandler.cc
  #src/dotlib/handler/CellInternalPower.cc
  src/dotlib/handler/group/InputVoltageHandler.cc
  src/dotlib/handler/group/LibraryHandler.cc
  src/dotlib/handler/group/OutputVoltageHandler.cc
  src/dotlib/handler/group/PinHandler.cc
  src/dotlib/handler/group/PowerHandler.cc
  src/dotlib/handler/group/TableHandler.cc
  src/dotlib/handler/group/TemplateHandler.cc

  # Str2GroupHandler

  # Str2IntGroupHandler
  #src/dotlib/handler/DefineHandler.cc

  src/dotlib/ast/AstAttr.cc
  src/dotlib/ast/AstBool.cc
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
