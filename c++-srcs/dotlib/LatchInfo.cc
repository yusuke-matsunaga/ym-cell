
/// @file LatchInfo.cc
/// @brief LatchInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/LatchInfo.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief 情報をセットする．
bool
LatchInfo::set(
  const AstValue* ast_val
)
{
  bool ok{true};

  if ( !set_common(ast_val) ) {
    ok = false;
  }

  switch ( get_expr("enable_on", mEnableOn) ) {
  case OK:
    break;
  case NOT_FOUND:
    // ラッチの場合はエラーではない．
    mEnableOn = nullptr;
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_expr("enable_on_also", mEnableOnAlso) ) {
  case OK:
    break;
  case NOT_FOUND:
    // これはエラーではない．
    mEnableOnAlso = nullptr;
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_expr("data_in", mDataIn) ) {
  case OK:
    break;
  case NOT_FOUND:
    // これはエラーではない．
    mDataIn = nullptr;
    break;
  case ERROR:
    ok = false;
    break;
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
