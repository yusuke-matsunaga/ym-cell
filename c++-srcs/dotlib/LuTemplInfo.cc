
/// @file LuTemplInfo.cc
/// @brief LuTemplInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/LuTemplInfo.h"
#include "dotlib/AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス LuTemplInfo
//////////////////////////////////////////////////////////////////////

// @brief 内容を設定する．
bool
LuTemplInfo::set(
  const AstValue* lut_val
)
{
  GroupInfo::set(lut_val);

  // 名前を得る．
  auto& header = lut_val->group_header_value();
  SizeType n = header.complex_elem_size();
  ASSERT_COND( n == 1 );
  mName = header.complex_elem_value(0).string_value();

  bool ok{true};

  if ( get_vartype("variable_1", mVar1) == ERROR ) {
    ok = false;
  }
  if ( get_vartype("variable_2", mVar2) == ERROR ) {
    ok = false;
  }
  if ( get_vartype("variable_3", mVar3) == ERROR ) {
    ok = false;
  }
  if ( get_complex_float_vector("index_1", mIndex1) == ERROR ) {
    ok = false;
  }
  if ( get_complex_float_vector("index_2", mIndex2) == ERROR ) {
    ok = false;
  }
  if ( get_complex_float_vector("index_3", mIndex3) == ERROR ) {
    ok = false;
  }

  if ( !ok ) {
    return false;
  }

  if ( mVar1 == ClibVarType::none || mIndex1.size() == 0 ) {
    // variable_1 か index_1 が未定義
#warning "TODO: エラーメッセージ"
    return false;
  }

  mDimension = 1;
  if ( mVar2 == ClibVarType::none ) {
    if ( mIndex2.size() > 0 ) {
      // variable_2 が定義されていないのに index_2 が定義されている．
#warning "TODO: エラーメッセージ"
      return false;
    }
    return true;
  }
  else if ( mIndex2.size() == 0 ) {
    // variable_2 が定義されているのに index_2 が未定義
#warning "TODO: エラーメッセージ"
    return false;
  }

  mDimension = 2;
  if ( mVar3 == ClibVarType::none ) {
    if ( mIndex3.size() > 0 ) {
      // variable_3 が定義されていないのに index_3 が定義されている．
#warning "TODO: エラーメッセージ"
      return false;
    }
    return true;
  }
  else if ( mIndex3.size() == 0 ) {
    // variable_3 が定義されているのに index_3 が未定義
#warning "TODO: エラーメッセージ"
    return false;
  }

  mDimension = 3;
  return true;
}

// @brief テンプレートを作る．
SizeType
LuTemplInfo::add_lu_template()
{
  SizeType tid{CLIB_NULLID};
  switch ( mDimension ) {
  case 1:
    tid = library()->add_lut_template1(mVar1, mIndex1);
    break;

  case 2:
    tid = library()->add_lut_template2(mVar1, mIndex1, mVar2, mIndex2);
    break;

  case 3:
    tid = library()->add_lut_template3(mVar1, mIndex1, mVar2, mIndex2, mVar3, mIndex3);
    break;

  default:
    ASSERT_NOT_REACHED;
    break;
  }
  return tid;
}

END_NAMESPACE_YM_DOTLIB
