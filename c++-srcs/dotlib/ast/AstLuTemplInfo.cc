
/// @file AstLuTemplInfo.cc
/// @brief AstLuTemplInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AstLuTemplInfo.h"
#include "dotlib/AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AstLuTemplInfo
//////////////////////////////////////////////////////////////////////

// @brief 内容を設定する．
bool
AstLuTemplInfo::set(
  const AstValue* lut_val
)
{
  // 名前を得る．
  auto& header = lut_val->group_header_value();
  SizeType n = header.complex_elem_size();
  ASSERT_COND( n == 1 );
  mName = header.complex_elem_value(0).string_value();

  // 属性の辞書を作る．
  auto elem_dict = lut_val->gen_group_elem_dict();

  bool ok{true};

  if ( elem_dict.get_vartype("variable_1", mVar1) == AstElemDict::ERROR ) {
    ok = false;
  }
  if ( elem_dict.get_vartype("variable_2", mVar2) == AstElemDict::ERROR ) {
    ok = false;
  }
  if ( elem_dict.get_vartype("variable_3", mVar3) == AstElemDict::ERROR ) {
    ok = false;
  }
  if ( elem_dict.get_complex_float_vector("index_1", mIndex1) == AstElemDict::ERROR ) {
    ok = false;
  }
  if ( elem_dict.get_complex_float_vector("index_2", mIndex2) == AstElemDict::ERROR ) {
    ok = false;
  }
  if ( elem_dict.get_complex_float_vector("index_3", mIndex3) == AstElemDict::ERROR ) {
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
void
AstLuTemplInfo::add_lu_template(
  unique_ptr<CiCellLibrary>& library
)
{
  switch ( mDimension ) {
  case 1:
    library->add_lut_template1(mName, mVar1, mIndex1);
    break;
  case 2:
    library->add_lut_template2(mName, mVar1, mIndex1, mVar2, mIndex2);
    break;
  case 3:
    library->add_lut_template3(mName, mVar1, mIndex1, mVar2, mIndex2, mVar3, mIndex3);
    break;
  }
}

END_NAMESPACE_YM_DOTLIB
