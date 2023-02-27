
/// @file FSMInfo.cc
/// @brief FSMInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FSMInfo.h"
#include "dotlib/AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FSMInfo
//////////////////////////////////////////////////////////////////////

// @brief 情報をセットする．
bool
FSMInfo::set(
  const AstValue* ast_val
)
{
  bool ok{true};

  // 属性の辞書を作る．
  if ( !set_common(ast_val) ) {
    ok = false;
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
