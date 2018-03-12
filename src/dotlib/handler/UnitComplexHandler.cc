
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
// @param[in] value_loc ファイル上の位置
// @param[in] value_list 値のリスト
DotlibNode*
UnitComplexHandler::gen_value(const FileRegion& value_loc,
			      const vector<DotlibNode*>& value_list)
{
  if ( value_list.size() != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, (number, string) pair expected.");
    return nullptr;
  }

  const DotlibNode* top = value_list[0];
  const DotlibNum* num_node = dynamic_cast<const DotlibNum*>(top);
  if ( num_node == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, first element should be a number.");
    return nullptr;
  }
  double unit_val = num_node->float_value();

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

  return mgr()->new_unit(value_loc, unit_val, unit_str);
}

END_NAMESPACE_YM_DOTLIB
