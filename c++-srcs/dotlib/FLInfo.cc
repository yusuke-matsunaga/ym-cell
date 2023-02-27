
/// @file FLInfo.cc
/// @brief FLInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/FLInfo.h"
#include "dotlib/AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス FLInfo
//////////////////////////////////////////////////////////////////////

// @brief 情報をセットする．
bool
FLInfo::set_common(
  const AstValue* val
)
{
  GroupInfo::set(val);

  // ヘッダ中の変数名を取り出す．
  auto& header = val->group_header_value();
  ASSERT_COND( header.complex_elem_size() == 2 );

  mVar1 = header.complex_elem_value(0).string_value();
  mVar2 = header.complex_elem_value(1).string_value();

  bool ok{true};

  switch ( get_expr("clear", mClear) ) {
  case OK:
    break;
  case NOT_FOUND:
    mClear = nullptr;
    break;
  case ERROR:
    ok = false;
    break;
  }

  switch ( get_expr("preset", mPreset) ) {
  case OK:
    break;
  case NOT_FOUND:
    mPreset = nullptr;
    break;
  case ERROR:
    ok = false;
    break;
  }

  auto ret1 = get_cpv("clear_preset_var1", mCpv1);
  auto ret2 = get_cpv("clear_preset_var2", mCpv2);
  if ( ret1 == ERROR || ret2 == ERROR ) {
    ok = false;
  }
  else if ( ret1 == OK ) {
    if ( ret2 == NOT_FOUND ) {
      // clear_preset_var1 が定義されているのに clear_preset_var2 が定義されていない．
      ok = false;
    }
  }
  else {
    if ( ret2 == OK ) {
      // clear_preset_var2 が定義されているのに clear_preset_var1 が定義されていない．
      ok = false;
    }
    else {
      // どちらも定義されていないので X を与える．
      mCpv1 = ClibCPV::X;
      mCpv2 = ClibCPV::X;
    }
  }

  return ok;
}

END_NAMESPACE_YM_DOTLIB
