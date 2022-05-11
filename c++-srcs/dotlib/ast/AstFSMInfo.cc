
/// @file AstFSMInfo.cc
/// @brief AstFSMInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstFSMInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstElemDict.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstFSMInfo
//////////////////////////////////////////////////////////////////////

// @brief 情報をセットする．
bool
AstFSMInfo::set(
  const AstValue* ast_val
)
{
  bool ok{true};

  // 属性の辞書を作る．
  auto elem_dict = ast_val->gen_group_elem_dict();
  if ( !set_common(ast_val, elem_dict) ) {
    ok = false;
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB