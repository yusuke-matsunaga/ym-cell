
/// @file Str1ComplexHandler.cc
/// @brief Str1ComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "Str1ComplexHandler.h"
#include "dotlib/DotlibNode.h"
#include "dotlib/DotlibString.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

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
DotlibNode*
Str1ComplexHandler::gen_value(const vector<DotlibNode*>& value_list)
{
  if ( value_list.size() != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list[0]->loc(), // TODO: 空の時に失敗する．
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return nullptr;
  }
  DotlibNode* top = value_list[0];
  DotlibString* str = dynamic_cast<DotlibString*>(top);
  if ( str == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return nullptr;
  }

  return str;
}

END_NAMESPACE_YM_DOTLIB
