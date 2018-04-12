
/// @file PwComplexHandler.cc
/// @brief PwComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "PwComplexHandler.h"
#include "dotlib/AstNode.h"
#include "dotlib/AstInt.h"
#include "dotlib/AstFloat.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief piece wise 用のハンドラを作る．
DotlibHandler*
HandlerFactory::new_piece_wise(DotlibParser& parser)
{
  return new PwComplexHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス PwComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
PwComplexHandler::PwComplexHandler(DotlibParser& parser) :
  ComplexHandler(parser)
{
}

// @brief デストラクタ
PwComplexHandler::~PwComplexHandler()
{
}

// @brief 値を表すノードを作る．
// @param[in] value_loc ファイル上の位置
// @param[in] value_list 値のリスト
const AstNode*
PwComplexHandler::gen_node(const FileRegion& value_loc,
			   const vector<const AstNode*>& value_list)
{
  if ( value_list.size() != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, (integer, float) pair expected.");
    return nullptr;
  }

  const AstNode* top = value_list[0];
  if ( dynamic_cast<const AstInt*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, first element should be an integer number.");
    return nullptr;
  }

  const AstNode* next = value_list[1];
  if ( dynamic_cast<const AstFloat*>(next) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    next->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, second element should be a float number.");
    return nullptr;
  }

#warning "TODO: 未完成"
  // 本当は (integer, float) を表す AstNode の派生クラスを作ってそれを返す．
  return nullptr;

}

END_NAMESPACE_YM_DOTLIB
