
/// @file IndexHandler.cc
/// @brief IndexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "IndexHandler.h"
#include "HandlerFactory.h"
#include "AstList.h"
#include "AstFloatVector.h"
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
// @param[in] value_loc ファイル上の位置
// @param[in] value_list 値のリスト
const AstNode*
IndexHandler::gen_node(const FileRegion& value_loc,
		       const vector<const AstNode*>& value_list)
{
  if ( value_list.size() != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, singleton expected.");
    return nullptr;
  }

  const AstNode* elem = value_list[0];
  if ( dynamic_cast<const AstFloatVector*>(elem) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    elem->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, vector expected.");
    return nullptr;
  }
  // ここでは要素を直接返す．
  return elem;
}

END_NAMESPACE_YM_DOTLIB
