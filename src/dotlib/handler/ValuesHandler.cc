
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
// @param[in] loc ファイル上の位置
// @param[in] value_list 値のリスト
//
// 多次元の場合でも1次元の FloatVector に変換する．
DotlibNode*
ValuesHandler::gen_value(const FileRegion& loc,
			 const vector<DotlibNode*>& value_list)
{
  int n = value_list.size();
  if ( n == 0 ) {
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc,
		    kMsgError,
		    "DOTLIB_PARSER",
		    "Syntax error, list of one ore more vectors expected.");
    return nullptr;
  }

  vector<double> tmp_list;
  for ( int i = 0; i < n; ++ i ) {
    DotlibNode* elem = value_list[i];
    auto fv_node = dynamic_cast<DotlibFloatVector*>(elem);
    if ( fv_node == nullptr ) {
      MsgMgr::put_msg(__FILE__, __LINE__,
		      elem->loc(),
		      kMsgError,
		      "DOTLIB_PARSER",
		      "Syntax error, vector expected.");
      return nullptr;
    }
    vector<double> tmp_list1;
    fv_node->get_vector(tmp_list1);
    tmp_list.insert(tmp_list.end(), tmp_list1.begin(), tmp_list1.end());
  }

  return mgr()->new_vector(loc, tmp_list);
}

END_NAMESPACE_YM_DOTLIB
