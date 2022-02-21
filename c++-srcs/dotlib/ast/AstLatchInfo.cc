
/// @file AstLatchInfo.cc
/// @brief AstLatchInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstLatchInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstElemDict.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 情報をセットする．
bool
AstLatchInfo::set(
  const AstValue* ast_val
)
{
  bool ok{true};

  // 属性の辞書を作る．
  auto elem_dict = ast_val->gen_group_elem_dict();
  if ( !set_common(ast_val, elem_dict) ) {
    ok = false;
  }

  switch ( elem_dict.get_expr("enable_on", mEnableOn) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    // ラッチの場合はエラーではない．
    mEnableOn = nullptr;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_expr("enable_on_also", mEnableOnAlso) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    // これはエラーではない．
    mEnableOnAlso = nullptr;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_expr("data_in", mDataIn) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    // これはエラーではない．
    mDataIn = nullptr;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
