
/// @file ValuesHandler.cc
/// @brief ValuesHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "ValuesHandler.h"
#include "dotlib/HandlerFactory.h"
#include "dotlib/DotlibMgrImpl.h"
#include "dotlib/DotlibFloatVector.h"
#include "dotlib/DotlibList.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'values' 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_values(DotlibParser& parser)
{
  return new ValuesHandler(parser);
}

//////////////////////////////////////////////////////////////////////
// クラス ValuesHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
ValuesHandler::ValuesHandler(DotlibParser& parser) :
  ComplexHandler(parser, true)
{
}

// @brief デストラクタ
ValuesHandler::~ValuesHandler()
{
}

// @brief 値を表すノードを作る．
// @param[in] value_list 値のリスト
DotlibNode*
ValuesHandler::gen_value(const vector<DotlibNode*>& value_list)
{
  int n = value_list.size();
  if ( n == 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[0]->loc(), // TODO 空の時に失敗する．
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, list of one ore more vectors expected.");
    return nullptr;
  }
  for ( int i = 0; i < n; ++ i ) {
    DotlibNode* elem = value_list[i];
    if ( dynamic_cast<DotlibFloatVector*>(elem) == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      elem->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error, vector expected.");
      return nullptr;
    }
  }
  return mgr()->new_list(value_list);
}

END_NAMESPACE_YM_DOTLIB
