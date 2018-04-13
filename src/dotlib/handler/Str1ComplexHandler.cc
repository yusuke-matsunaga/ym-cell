
/// @file Str1ComplexHandler.cc
/// @brief Str1ComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/HandlerFactory.h"
#include "Str1ComplexHandler.h"
#include "dotlib/AstNode.h"
#include "dotlib/AstString.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief ダミーの complex ハンドラを作る．
DotlibHandler*
HandlerFactory::new_str1_complex(DotlibParser& parser)
{
  return new Str1ComplexHandler(parser);
}


//////////////////////////////////////////////////////////////////////
// クラス Str1ComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parser パーサー
Str1ComplexHandler::Str1ComplexHandler(DotlibParser& parser) :
  ComplexHandler(parser)
{
}

// @brief デストラクタ
Str1ComplexHandler::~Str1ComplexHandler()
{
}

// @brief 値を表すノードを作る．
// @param[in] value_list 値のリスト
const AstNode*
Str1ComplexHandler::gen_value(const vector<const AstNode*>& value_list)
{
  if ( value_list.size() != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[0]->loc(), // TODO: 空の時に失敗する．
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return nullptr;
  }
  const AstNode* top = value_list[0];
  if ( dynamic_cast<const AstString*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return nullptr;
  }

  return top;
}

END_NAMESPACE_YM_DOTLIB
