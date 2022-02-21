
/// @file AstFLInfo.cc
/// @brief AstFLInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstFLInfo.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstElemDict.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstFLInfo
//////////////////////////////////////////////////////////////////////

// @brief 情報をセットする．
bool
AstFLInfo::set_common(
  const AstValue* val,
  const AstElemDict& elem_dict
)
{
  // ヘッダ中の変数名を取り出す．
  auto& header = val->group_header_value();
  ASSERT_COND( header.complex_elem_size() == 2 );

  mVar1 = header.complex_elem_value(0).string_value();
  mVar2 = header.complex_elem_value(1).string_value();

  bool ok{true};

  switch ( elem_dict.get_expr("clear", mClear) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    mClear = nullptr;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  switch ( elem_dict.get_expr("preset", mPreset) ) {
  case AstElemDict::OK:
    break;
  case AstElemDict::NOT_FOUND:
    mPreset = nullptr;
    break;
  case AstElemDict::ERROR:
    ok = false;
    break;
  }

  auto ret1 = elem_dict.get_cpv("clear_preset_var1", mCpv1);
  auto ret2 = elem_dict.get_cpv("clear_preset_var2", mCpv2);
  if ( ret1 == AstElemDict::ERROR || ret2 == AstElemDict::ERROR ) {
    ok = false;
  }
  else if ( ret1 == AstElemDict::OK ) {
    if ( ret2 == AstElemDict::NOT_FOUND ) {
      // clear_preset_var1 が定義されているのに clear_preset_var2 が定義されていない．
      ok = false;
    }
  }
  else {
    if ( ret2 == AstElemDict::OK ) {
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
