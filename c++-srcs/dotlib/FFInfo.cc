
/// @file FFInfo.cc
/// @brief FFInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FFInfo.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 情報をセットする．
bool
FFInfo::set(
  const AstValue* ast_val
)
{
  bool ok{true};

  // 属性の辞書を作る．
  if ( !set_common(ast_val) ) {
    ok = false;
  }

  if ( !get_expr("clocked_on", mClockedOn) ) {
    // FF に clocked_on は必須
#warning "TODO: エラーメッセージ"
    ok = false;
  }

  if ( !get_expr("clocked_on_also", mClockedOnAlso) ) {
    // これはエラーではない．
    mClockedOnAlso = nullptr;
  }

  if ( !get_expr("next_state", mNextState) ) {
#warning "TODO: エラーメッセージ"
    ok = false;
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
