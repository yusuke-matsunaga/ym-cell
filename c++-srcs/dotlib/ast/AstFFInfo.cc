
/// @file AstFFInfo.cc
/// @brief AstFFInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstFFInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstElemDict.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 情報をセットする．
bool
AstFFInfo::set(
  const AstValue* ast_val
)
{
  bool ok{true};

  // 属性の辞書を作る．
  auto elem_dict = ast_val->gen_group_elem_dict();
  if ( !set_common(ast_val, elem_dict) ) {
    ok = false;
  }

  switch ( elem_dict.get_expr("clocked_on", mClockedOn) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    // FF に clocked_on は必須
#warning "TODO: エラーメッセージ"
    ok = false;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_expr("clocked_on_also", mClockedOnAlso) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    // これはエラーではない．
    mClockedOnAlso = nullptr;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_expr("next_state", mNextState) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
#warning "TODO: エラーメッセージ"
    ok = false;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
