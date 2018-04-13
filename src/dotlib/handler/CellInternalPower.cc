
/// @file CellInternalPowerHandler.cc
/// @brief CellInternalPowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "CellInternalPower.h"
#include "dotlib/HandlerFactory.h"
#include "dotlib/AstAttr.h"
#include "SimpleHandler.h"
#include "ValuesHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief timing group 用のハンドラを作る．
// @param[in] parent 親のハンドラ
DotlibHandler*
HandlerFactory::new_cell_internal_power(DotlibParser& parser)
{
  GroupHandler* handler = new CellInternalPowerHandler(parser);

  return handler;
}


//////////////////////////////////////////////////////////////////////
// クラス CellInternalPowerHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
CellInternalPowerHandler::CellInternalPowerHandler(DotlibParser& parser) :
  Str1GroupHandler(parser)
{
  // simple attributes
  DotlibHandler* simple = new SimpleHandler(parser, false);
  DotlibHandler* values_handler = new ValuesHandler(parser);

  reg_handler(AttrType::related_inputs,  simple);
  reg_handler(AttrType::related_outputs, simple);

  reg_handler(AttrType::valueS,          values_handler);
}

// @brief デストラクタ
CellInternalPowerHandler::~CellInternalPowerHandler()
{
}

// @brief 値を作る．
const AstNode*
CellInternalPowerHandler::gen_node(const FileRegion& loc,
				   const AstString* name,
				   const vector<const AstAttr*>& attr_list)
{
  for ( auto attr: attr_list ) {
    if ( attr->attr_type() == AttrType::RELATED_pin ) {
    }
  }
#warning "TODO: 未完成"
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB
