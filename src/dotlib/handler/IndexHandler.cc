
/// @file IndexHandler.cc
/// @brief IndexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "IndexHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス IndexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
IndexHandler::IndexHandler(GroupHandler* parent) :
  ComplexHandler(parent, true)
{
}

// @brief デストラクタ
IndexHandler::~IndexHandler()
{
}

// @brief 値を表すノードを作る．
// @param[in] value_list 値のリスト
DotlibNode*
INdexHandler::gen_value(DotlibList* value_list)
{
  if ( value_list->list_size() != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, singleton expected.");
    return nullptr;
  }
  DotlibNode* elem = value_list->list_elem(0);
  if ( dynamic_cast<DotlibFloatVector*>(elem) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    elem->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, vector expected.");
    return nullptr;
  }
  // ここでは要素を直接返す．
  return elem;
}

END_NAMESPACE_YM_DOTLIB
