
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  include
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================


# ===================================================================
#  ソースファイルの設定
# ===================================================================

set (main_SOURCES
  read_liberty.cc
  )

set (parser_SOURCES
  parser/AttrDic.cc
  parser/DotlibParser.cc
  parser/DotlibScanner.cc
  )

set (handler_SOURCES
  handler/DotlibHandler.cc
  handler/FhScanner.cc
  handler/HandlerFactory.cc
  handler/CellInternalPower.cc
  handler/ComplexHandler.cc
  handler/DefineHandler.cc
  handler/DelayModelHandler.cc
  handler/ExprHandler.cc
  handler/FuncHandler.cc
  handler/GroupHandler.cc
  handler/LibraryHandler.cc
  handler/IndexHandler.cc
  handler/InputVoltageHandler.cc
  handler/InternalPowerHandler.cc
  handler/OutputVoltageHandler.cc
  handler/PinHandler.cc
  handler/PinDirectionHandler.cc
  handler/PowerHandler.cc
  handler/PwComplexHandler.cc
  handler/SimpleHandler.cc
  handler/Str1ComplexHandler.cc
  handler/TableHandler.cc
  handler/TechnologyHandler.cc
  handler/TemplateHandler.cc
  handler/TimingHandler.cc
  handler/TimingSenseHandler.cc
  handler/TimingTypeHandler.cc
  handler/UnitComplexHandler.cc
  handler/ValuesHandler.cc
  handler/VarTypeHandler.cc
  )

set (ast_SOURCES
  ast/AstAttr.cc
  ast/AstCell.cc
  ast/AstDelayModel.cc
  ast/AstExpr.cc
  ast/AstFF.cc
  ast/AstFL.cc
  ast/AstFloat.cc
  ast/AstFloatVector.cc
  ast/AstGenGroup.cc
  ast/AstInputVoltage.cc
  ast/AstInt.cc
  ast/AstLatch.cc
  ast/AstLibrary.cc
  ast/AstLut.cc
  ast/AstMgr.cc
  ast/AstNode.cc
  ast/AstOutputVoltage.cc
  ast/AstPieceWise.cc
  ast/AstPin.cc
  ast/AstPinDirection.cc
  ast/AstStateTable.cc
  ast/AstString.cc
  ast/AstTemplate.cc
  ast/AstTiming.cc
  ast/AstTimingSense.cc
  ast/AstTimingType.cc
  ast/AstTechnology.cc
  ast/AstUnit.cc
  ast/AstVarType.cc
  )


# ===================================================================
#  ターゲットの設定
# ===================================================================

ym_add_object_library ( ym_cell_dotlib
  ${main_SOURCES}
  ${ast_SOURCES}
  ${handler_SOURCES}
  ${parser_SOURCES}
  )


# ===================================================================
#  インストールターゲットの設定
# ===================================================================
