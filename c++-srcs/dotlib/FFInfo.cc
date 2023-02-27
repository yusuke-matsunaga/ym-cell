
/// @file FFInfo.cc
/// @brief FFInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FFInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/ElemDict.h"


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

  switch ( elem_dict().get_expr("clocked_on", mClockedOn) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
    // FF に clocked_on は必須
#warning "TODO: エラーメッセージ"
    ok = false;
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict().get_expr("clocked_on_also", mClockedOnAlso) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
    // これはエラーではない．
    mClockedOnAlso = nullptr;
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict().get_expr("next_state", mNextState) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
#warning "TODO: エラーメッセージ"
    ok = false;
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
