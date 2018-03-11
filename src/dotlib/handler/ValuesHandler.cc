
/// @file ValuesHandler.cc
/// @brief ValuesHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ValuesHandler.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス ValuesHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
ValuesHandler::ValuesHandler(GroupHandler* parent) :
  ComplexHandler(parent, true)
{
}

// @brief デストラクタ
ValuesHandler::~ValuesHandler()
{
}

// @brief 値を表すノードを作る．
// @param[in] value_list 値のリスト
DotlibNode*
ValuesHandler::gen_value(DotlibList* value_list)
{
  int n = value_list->list_size();
  if ( n == 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, list of one ore more vectors expected.");
    return nullptr;
  }
  for ( int i = 0; i < n; ++ i ) {
    const DotlibNode* elem = value_list->list_elem(i);
    if ( dynamic_cast<const DotlibNode*>(elem) == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      elem,
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error, vector expected.");
      return nullptr;
    }
  }
  return value_list;
}

END_NAMESPACE_YM_DOTLIB
