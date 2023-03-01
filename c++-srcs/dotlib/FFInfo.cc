
/// @file FFInfo.cc
/// @brief FFInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FFInfo.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 情報をセットする．
void
FFInfo::set(
  const AstValue* ast_val
)
{
  // 属性の辞書を作る．
  set_common(ast_val);

  if ( !get_expr("clocked_on", mClockedOn) ) {
    // FF に clocked_on は必須
    auto label = "No 'clocked_on' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }

  if ( !get_expr("clocked_on_also", mClockedOnAlso) ) {
    // これはエラーではない．
    mClockedOnAlso = nullptr;
  }

  if ( !get_expr("next_state", mNextState) ) {
    auto label = "No 'next_state' attributes";
    MsgMgr::put_msg(__FILE__, __LINE__,
		    loc(),
		    MsgType::Error,
		    "DOTLIB_PARSER",
		    label);
    throw std::invalid_argument{label};
  }
}

END_NAMESPACE_YM_DOTLIB
