
/// @file IndexHandler.cc
/// @brief IndexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "IndexHandler.h"
#include "dotlib/HandlerFactory.h"
#include "dotlib/DotlibList.h"
#include "dotlib/DotlibFloatVector.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 'index_?' 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_index(DotlibParser& parser)
{
  return new IndexHandler(parser);
}

//////////////////////////////////////////////////////////////////////
// クラス IndexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
IndexHandler::IndexHandler(DotlibParser& parser) :
  ComplexHandler(parser, true)
{
}

// @brief デストラクタ
IndexHandler::~IndexHandler()
{
}

// @brief 値を表すノードを作る．
// @param[in] value_list 値のリスト
DotlibNode*
IndexHandler::gen_value(const vector<DotlibNode*>& value_list)
{
  if ( value_list.size() != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[0]->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, singleton expected.");
    return nullptr;
  }
  DotlibNode* elem = value_list[0];
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
