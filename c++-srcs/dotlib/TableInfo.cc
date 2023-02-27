
/// @file TableInfo.cc
/// @brief TableInfo の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/TableInfo.h"
#include "dotlib/AstElemDict.h"
#include "dotlib/AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス TableInfo
//////////////////////////////////////////////////////////////////////

// @brief 内容をセットする．
bool
TableInfo::set(
  const AstValue* val
)
{
  // 名前を得る．
  auto& header = val->group_header_value();
  SizeType n = header.complex_elem_size();
  ASSERT_COND( n == 1 );
  mName = header.complex_elem_value(0).string_value();

  // 属性の辞書を作る．
  auto elem_dict = val->gen_group_elem_dict();

  bool ok{true};

  if ( elem_dict.get_complex_float_vector("index_1", mIndex1) == AstElemDict::ERROR ) {
    ok = false;
  }

  if ( elem_dict.get_complex_float_vector("index_2", mIndex2) == AstElemDict::ERROR ) {
    ok = false;
  }

  if ( elem_dict.get_complex_float_vector("index_3", mIndex3) == AstElemDict::ERROR ) {
    ok = false;
  }

  if ( elem_dict.get_complex_float_vector("values", mValues) != AstElemDict::OK ) {
    ok = false;
  }

  if ( elem_dict.get_value("domain", mDomain) == AstElemDict::ERROR ) {
    ok = false;
  }

  return ok;
}

SizeType
TableInfo::gen_lut(
  CiCellLibrary* library
) const
{
  if ( mValues.size() > 0 ) {
    return library->add_lut(mName, mValues, mIndex1, mIndex2, mIndex3);
  }
  return CLIB_NULLID;
}

END_NAMESPACE_YM_DOTLIB
