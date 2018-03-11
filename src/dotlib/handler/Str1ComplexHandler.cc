
/// @file Str1ComplexHandler.cc
/// @brief Str1ComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014 Yusuke Matsunaga
/// All rights reserved.


#include "Str1ComplexHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス Str1ComplexHandler
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
// @param[in] parent 親のハンドラ
Str1ComplexHandler::Str1ComplexHandler(GroupHandler* parent) :
  ComplexHandler(parent)
{
}

// @brief デストラクタ
Str1ComplexHandler::~Str1ComplexHandler()
{
}

// @brief 値を表すノードを作る．
// @param[in] value_list 値のリスト
DotlibNode*
Str1ComplexHandler::gen_value(DotlibList* value_list)
{
  if ( value_list->list_size() != 1 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_list->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return false;
  }
  const DotlibNode* top = value_list->list_elem(0);
  const DotlibString* str = dynamic_cast<const DotlibString*>(top);
  if ( str == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, a string expected.");
    return false;
  }

  return str;
}

END_NAMESPACE_YM_DOTLIB
