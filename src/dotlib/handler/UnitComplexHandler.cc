
/// @file UnitComplexHandler.cc
/// @brief UnitComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "HandlerFactory.h"
#include "UnitComplexHandler.h"
#include "AstMgr.h"
#include "AstNode.h"
#include "AstInt.h"
#include "AstFloat.h"
#include "AstString.h"
#include "AstUnit.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief unit 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_unit(DotlibParser& parser)
{
  return new UnitComplexHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス UnitComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
UnitComplexHandler::UnitComplexHandler(DotlibParser& parser) :
  ComplexHandler(parser)
{
}

// @brief デストラクタ
UnitComplexHandler::~UnitComplexHandler()
{
}

// @brief 値を表すノードを作る．
// @param[in] value_loc ファイル上の位置
// @param[in] value_list 値のリスト
const AstNode*
UnitComplexHandler::gen_node(const FileRegion& value_loc,
			     const vector<const AstNode*>& value_list)
{
  if ( value_list.size() != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, (number, string) pair expected.");
    return nullptr;
  }

  const AstNode* top = value_list[0];
  const AstFloat* num_node = dynamic_cast<const AstFloat*>(top);
  if ( num_node == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, first element should be a number.");
    return nullptr;
  }
  double unit_val = num_node->value();

  const AstNode* next = value_list[1];
  const AstString* str_node = dynamic_cast<const AstString*>(next);
  if ( str_node == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    next->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, second element should be a string.");
    return nullptr;
  }
  ShString unit_str = str_node->value();

  return mgr().new_unit(value_loc, unit_val, unit_str);
}

END_NAMESPACE_YM_DOTLIB
