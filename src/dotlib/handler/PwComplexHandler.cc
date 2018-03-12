
/// @file PwComplexHandler.cc
/// @brief PwComplexHandler の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "PwComplexHandler.h"
#include "dotlib/DotlibNode.h"
#include "dotlib/DotlibInt.h"
#include "dotlib/DotlibFloat.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

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
DotlibNode*
PwComplexHandler::gen_value(const FileRegion& value_loc,
			    const vector<DotlibNode*>& value_list)
{
  if ( value_list.size() != 2 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    value_loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, (integer, float) pair expected.");
    return nullptr;
  }

  const DotlibNode* top = value_list[0];
  if ( dynamic_cast<const DotlibInt*>(top) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    top->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, first element should be an integer number.");
    return nullptr;
  }

  const DotlibNode* next = value_list[1];
  if ( dynamic_cast<const DotlibFloat*>(next) == nullptr ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    next->loc(),
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, second element should be a float number.");
    return nullptr;
  }

#warning "TODO: 未完成"
  // 本当は (integer, float) を表す DotlibNode の派生クラスを作ってそれを返す．
  return nullptr;

}

END_NAMESPACE_YM_DOTLIB
