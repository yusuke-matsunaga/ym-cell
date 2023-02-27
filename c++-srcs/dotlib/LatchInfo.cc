
/// @file LatchInfo.cc
/// @brief LatchInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/LatchInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/ElemDict.h"


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

  switch ( elem_dict().get_expr("enable_on", mEnableOn) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
    // ラッチの場合はエラーではない．
    mEnableOn = nullptr;
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict().get_expr("enable_on_also", mEnableOnAlso) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
    // これはエラーではない．
    mEnableOnAlso = nullptr;
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict().get_expr("data_in", mDataIn) ) {
  case ElemDict::OK:
    break;
  case ElemDict::NOT_FOUND:
    // これはエラーではない．
    mDataIn = nullptr;
    break;
  case ElemDict::ERROR:
    ok = false;
    break;
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
