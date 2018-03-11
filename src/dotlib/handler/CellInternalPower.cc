
/// @file CellInternalPowerHandler.cc
/// @brief CellInternalPowerHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "CellInternalPowerHandler.h"
#include "dotlib/HanderFactory.h"


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

  reg_handler(ATTR_RELATED_INPUTS,  simple);
  reg_handler(ATTR_RELATED_OUTPUTS, simple);

  reg_handler(ATTR_VALUES,          values_handler);
}

// @brief デストラクタ
CellInternalPowerHandler::~CellInternalPowerHandler()
{
}

// @brief 値を作る．
DotlibNode*
CellInternalPowerHandler::gen_value(const DotlibList* value_list,
				    const DotlibAttr* attr_top)
{
  const DotlibString* name = value_list->get_string_from_value_list();
  for ( auto attr = attr_top; attr != nullptr; attr = attr->next() ) {
    if ( attr->attr_type() == ATTR_RELATED_PIN ) {
    }
  }
#warning "TODO: 未完成"
  return nullptr;
}

END_NAMESPACE_YM_DOTLIB