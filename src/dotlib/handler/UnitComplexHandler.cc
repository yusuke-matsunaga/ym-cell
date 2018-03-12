
/// @file UnitComplexHandler.cc
/// @brief UnitComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "UnitComplexHandler.h"
#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/DotlibNode.h"
#include "dotlib/DotlibInt.h"
#include "dotlib/DotlibFloat.h"
#include "dotlib/DotlibString.h"
#include "dotlib/DotlibUnit.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

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
// @param[in] value_list 値のリスト
DotlibNode*
UnitComplexHandler::gen_value(const vector<DotlibNode*>& value_list)
{
  if ( value_list.size() != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[0]->loc(), // TODO: 空の時に失敗する．
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, (number, string) pair expected.");
    return nullptr;
  }

  const DotlibNode* top = value_list[0];
  double unit_val = 0.0;
  const DotlibFloat* float_node = dynamic_cast<const DotlibFloat*>(top);
  if ( float_node != nullptr ) {
    unit_val = float_node->value();
  }
  else {
    const DotlibInt* int_node = dynamic_cast<const DotlibInt*>(top);
    if ( int_node != nullptr ) {
      unit_val = int_node->value();
    }
  }
  if ( unit_val == 0.0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, first element should be a number.");
    return nullptr;
  }

  const DotlibNode* next = value_list[1];
  const DotlibString* str_node = dynamic_cast<const DotlibString*>(next);
  if ( str_node == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    next->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, second element should be a string.");
    return nullptr;
  }
  ShString unit_str = str_node->value();
  return mgr()->new_unit(FileRegion(top->loc(), next->loc()), unit_val, unit_str);
}

END_NAMESPACE_YM_DOTLIB
