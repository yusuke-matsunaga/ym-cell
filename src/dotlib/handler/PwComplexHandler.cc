
/// @file PwComplexHandler.cc
/// @brief PwComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "PwComplexHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス PwComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
PwComplexHandler::PwComplexHandler(GroupHandler* parent) :
  ComplexHandler(parent)
{
}

// @brief デストラクタ
PwComplexHandler::~PwComplexHandler()
{
}

// @brief 値を表すノードを作る．
// @param[in] value_list 値のリスト
DotlibNode*
PwComplexHandler::gen_value(DotlibList* value_list)
{
  if ( value_list->list_size() != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, (integer, float) pair expected.");
    return nullptr;
  }
  const DotlibNode* top = value_list->list_elem(0);
  if ( dynamic_cast<const DotlibInt*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, first element should be an integer number.");
    return nullptr;
  }
  const DotlibNode* next = value_list->list_elem(1);
  if ( dynamic_cast<const DotlibFloat*>(next) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    next->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, second element should be a float number.");
    return nullptr;
  }
  return value_list;

}

END_NAMESPACE_YM_DOTLIB
